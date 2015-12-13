#include<iostream>
#include<opencv2\opencv.hpp>
   
using namespace std;
using namespace cv;



int main()
{
   
	VideoCapture cap(0);//��������ͷ

	Mat img_show;//���ղ���ʾ֡

	Mat img_manage;//����֡

	vector<vector<Point>> contours;//��������

	namedWindow("������ȡ");//��������
	namedWindow("��Ե����");
	if (cap.isOpened())
	{
		cout << "����ͷ�Ѿ��򿪣���ʼ��ȡ"<<endl;
		while (1)
		{
			cap >>img_show;
			if (img_show.data == NULL)//��������֡��ϢΪ�����½���
			{
				continue;
			}
			img_manage = img_show;//��ʾ֡��ֵ������֡
			GaussianBlur(img_manage, img_manage, Size(5, 5), 1.5);//��˹ȥ�룬����ϸ����Ϣ������������Ϣ
			cvtColor(img_manage, img_manage, CV_RGB2GRAY);//��ֵ������
			Canny(img_manage, img_manage,50,150);//��Ե����
			findContours(img_manage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);//������,�ҳ�������������������������
			cout << "ʶ������������:" << contours.size()<<endl;
			drawContours(img_show, contours,-1,Scalar(255),2);//������������
			imshow("������ȡ", img_show);//��ʾ���ϵ�����
			imshow("��Ե����", img_manage);//��ʾ��Ե�����Ľ���
			waitKey(30);
		}

	}
	return 0;
}
