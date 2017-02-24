#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

void switch_on(Mat* input)//���ؿ���ִ�еĺ���
{
	cout << "���ؿ���" << endl;
	imshow("��������������", *input);
}

void switch_off(Mat* input)//���عر�ִ�еĺ���
{
	Mat offimg = *input;
	offimg = Mat(offimg.rows,offimg.cols,CV_8UC3,Scalar(0,0,0));
	cout << "���عر�" << endl;
	imshow("��������������",offimg);
}

static void switch_trackbar(int position,void *userdata)//�������ĺ���
{	
	if (position==1){//����
		switch_on((Mat*)userdata);
	}else{
		switch_off((Mat*)userdata);
	}
}

int main()
{
	int colse = 0;
	Mat img = imread("beach.jpg");//��ȡͼƬ
	namedWindow("��������������");
	createTrackbar("����", "��������������", &colse, 1, switch_trackbar, (void*)&img);//����������ȡ��ַ��ת���ɿ�ָ������
	waitKey(0);
	return 0;
}