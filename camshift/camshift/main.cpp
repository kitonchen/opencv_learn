#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

    Mat image;

	bool backprojMode = false; //��ʾ�Ƿ�Ҫ���뷴��ͶӰģʽ��ture��ʾ׼�����뷴��ͶӰģʽ

	bool selectObject = false;//�����Ƿ���ѡҪ���ٵĳ�ʼĿ�꣬true��ʾ���������ѡ��

	int trackObject = 0; //�������Ŀ����Ŀ

	bool showHist = true;//�Ƿ���ʾֱ��ͼ

	Point origin;//���ڱ������ѡ���һ�ε���ʱ���λ��

	Rect selection;//���ڱ������ѡ��ľ��ο�

	int vmin = 10, vmax = 256, smin = 30;

void onMouse(int event,int x,int y,void*)
{
	if (selectObject)//������������ȥʱ����Ч��Ȼ��ͨ��if����Ĵ���ȷ����ѡ��ľ��������ѡ����
	{
		selection.x = MIN(x, origin.x);//������ϽǵĶ���X���꣬�˲��������Ǵ��������������λ�֮�����Եõ����Ͻǵ�����
		selection.y = MIN(y, origin.y);//ͬ��

		selection.height = abs(x - origin.x);//������εĿ�
		selection.width = abs(y - origin.y);//���εĸ�

		selection &= Rect(0, 0, image.cols, image.rows);//����ȷ������������ͼƬ��Χ��
	}

	switch (event)
	{
	  case CV_EVENT_LBUTTONDOWN:
		      origin = Point(x, y);
			  selection = Rect(x, y, 0, 0);//���հ���ȥʱ�ͳ�ʼ��һ����������
			  selectObject = true;//���������ѡ��
			  break;
	  case CV_EVENT_LBUTTONUP  :
		      selectObject = false;//ѡ�����
			  if (selection.width > 0 && selection.height > 0) {
				  trackObject = -1;//�����ʼ��һ�����γɹ�����ʼ׷�١�ȡֵ-1�����޶�׷��Ŀ��
			  }
			  break;
	}
}

void help()
{
	cout << "������Ϊ����camshfit��һ������" << endl << "�����ѡ���һ������������ѡ��׷��Ŀ��";
}

int main()
{
	help();
	MouseCallback onMouse;
	VideoCapture cap;//����ͷ����
	Rect trackWindow;
	RotatedRect tracBox;//��ת�ľ�����
	int hsize = 16;
	float hranges[] = { 0,180 };//����ֱ��ͼ������ʹ��
	const float* phranges = hranges;
	cap.open(0);//������ͷ
	if (!cap.isOpened())
	{
		cout << "����ͷ��ʧ��" << endl;
		return -1;
	}
	namedWindow("ֱ��ͼ", 0);

	namedWindow("׷����ɫ", 0);

	setMouseCallback("��ɫ׷��", onMouse, 0);//��Ϣ��Ӧ����

	createTrackbar("Vmin", "׷����ɫ", &vmin, 256, 0);//��������������СֵΪ256

	createTrackbar("Vmax", "׷����ɫ", &vmax, 256, 0);//���һ������Ϊ0����û���û����϶�����Ӧ����

	cvCreateTrackbar("Smin", "׷����ɫ", &smin, 256, 0);//vmin��vmax��smin��ʼֵΪ10��256��30
	Mat frame, hsv, hue, mask, hist, histing = Mat::zeros(200, 320, CV_8UC3), backproj;

	bool paused = false;

	while (1)
	{
		if (!paused)//û����ͣ
		{
			cap >> frame;//������ͷ��ȡһ֡
			if (frame.empty()) {//�������Ϊ��
				break;
			}
			frame.copyTo(image);
			if (!paused) {//û�а���ͣ��
				cvtColor(image, hsv, CV_BGR2HSV);//����֡RGB�ռ�תΪHSV�ռ�
				if (trackObject) {//��ʼ��Ϊ0�����߰�����̵�'c'����ҲΪ0����굥����Ϊ-1
					int _vmin = vmin, _vmax = vmax;
					//inRange�����Ĺ����Ǽ����������ÿ��Ԫ�ش�С�Ƿ���2��������ֵ֮�䡣�����ж�ͨ����mask����0ͨ������Сֵ������h����
					//����������HSV��3��ͨ�����Ƚ�H��0~180��S,Smin~256,V,min(vmin,vmax),max(vmin,vmax)���3��ͨ�����ڶ�Ӧ�ķ�Χ�ڣ���msak��Ӧ���Ǹ����ֵΪ1��0XFF��������Ϊ0��0X00��
					inRange(hsv, Scalar(0, smin, min(_vmin, _vmax)), Scalar(180, 256, max(_vmin, _vmax)), mask);	
					int ch[] = { 0,0 };
					hue.create(hsv.size(), hsv.depth());//HUE��ʼ��Ϊһ����HSV��С���һ���ľ���ɫ���Ķ������ýǶȱ�ʾ�ģ�������֮�����120�ȣ���ɫ���180��
					mixChannels(&hsv, 1, &hue, 1, ch, 1);//��HSV�ĵ�һ��ͨ����Ҳ����ɫ���������Ƶ�HUE�У�0�������飩
					if (trackObject < 0) {
						//�˴��Ĺ��캯��ROI�õ���Mat hue�ľ���ͷ����roi������ָ��ָ��hue,��������ͬ�����ݣ�selectΪ�����Ȥ������
						Mat roi(hue, selection), maskroi(mask, selection);//mask�����HSV����Сֵ
						//calchist()������һ������Ϊ����������У���2��������ʾ����ľ�����Ŀ��������������ʾ��������ֱ��ͼά��ͨ�����б���4��������ʾ��ѡ�����뺯��
						//��5�������������ֱ��ͼ����6��������ʾֱ��ͼ��ά������7������Ϊÿһάֱ��ͼ����Ĵ�С����8������Ϊÿһάֱ��ͼbin�ı߽�
						calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//����roi��0ͨ������ֱ��ͼ��ͨ��mask����hist�У�hsizeΪÿһάֱ��ͼ�Ĵ�С
					}
				}
			}
		}
	}


	return 0;
}