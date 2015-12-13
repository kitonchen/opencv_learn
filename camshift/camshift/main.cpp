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
	VideoCapture cap;//����ͷ����
	Rect trackWindow;
	RotatedRect tracBox;

	int hsize = 16;
	
	return 0;
}