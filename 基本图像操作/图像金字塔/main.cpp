#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//ͼ�������˵���˾��ǷŴ���СͼƬ http://blog.csdn.net/poem_qianmo/article/details/26157633
int main()
{
	//Resize()���� ��������ָ����С
	Mat input = imread("beach.jpg");
	imshow("ԭͼ", input);
	//�÷�1
	//Mat out = Mat::zeros(520,520, CV_8UC3);//�½�һ����СΪ520*520��ͼƬ
	//resize(input,out, out.size());
	//imshow("���´�С", out);
	//�÷�2
	Mat tempimg, outimg;
	tempimg = input;//��ԭͼ���Ƹ���ʱ����
	resize(tempimg, outimg, Size(tempimg.cols * 2, tempimg.rows * 2));//����Ŵ�Ϊԭ��4��
	imshow("�Ŵ�", outimg);
	resize(tempimg, outimg, Size(tempimg.cols / 2, tempimg.rows / 2));//��С
	imshow("��С", outimg);
	//����pyrup()�Ŵ�prydown()��С����������������
	waitKey(0);
	return 0;
}