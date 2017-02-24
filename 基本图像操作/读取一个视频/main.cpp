#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;


VideoCapture MyCap;//��Ƶ����
int sildp = 0;//��������ʼλ��

 static void ontrackslide(int pos,void *)//posΪ֡�����������������Ĭ��ΪcreateTrackbar������������ֵ
{
	MyCap.set(CAP_PROP_POS_FRAMES, pos);//������Ƶ��ǰ֡��
	//MyCap.set(CAP_PROP_POS_AVI_RATIO, pos);//��AVI���ȱ���
}
 
int main()
{
	int frames;//��¼��Ƶ֡��
	Mat ReadImage;
	namedWindow("��ӹ�����", CV_WINDOW_AUTOSIZE);//����һ����Ƶ����С����Ӧ
	//��ȡ��Ƶ,���ִ򿪷�ʽ�����ֶ�ȡ·�����κ�һ�ִ򿪷�ʽ����Ӧ���ֶ�ȡ·��
	//��һ�֣�ͨ����ʼ�������
	//VideoCapture MyCap("E:\\ѧϰ����\\learn_opencv\\����ͼ�����\\��ȡһ����Ƶ\\bike.avi");//ȫ��·��
	//�ڶ��֣�ͨ��open�����򿪣���ȡ�ļ�·���ο�����
	MyCap.open("bike.avi");   	
	assert(MyCap.isOpened());//�Ƿ�ɹ���

	frames = MyCap.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ��֡��

	if (frames != 0) {//����1�����������ı���2�����õĴ�����,3����ʼֵ,4:���ֵ,5:�ص�����
		createTrackbar("֡��", "��ӹ�����", &sildp, frames, ontrackslide);//����������Ϊȫ�ֱ����ǣ����Բ������һ��������û�������userdata��������������û������ص�����������
	}
	while (1)
	{
		MyCap >> ReadImage;//��ȡ��һ֡����

		if (ReadImage.empty()) break;//�����Ƶ�Ѿ������ꡣ����Ϊ��ʱ,�ж�����Ҳ������data��Ա

		setTrackbarPos("֡��", "��ӹ�����", sildp);//���ù�������ǰλ�ã����Ｔ֡��

		imshow("��ӹ�����", ReadImage);//��ʾ
		
		waitKey(30);//�ӳ�30���룬�����
		
		sildp++;//֡����1����ѭ���оͿ���ʵ�ֹ�����֡������Ƶ���Ź���
		
		char c = waitKey(33);//�ӳ�33�������Ƿ����˳�����

		if (c == 27) break;//�������ESC�����ͻ��˳�
	}
	  
	return 0;
}