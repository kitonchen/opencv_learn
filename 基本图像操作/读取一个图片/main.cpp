#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat read = imread("ɽ.jpg");//ʵ����һ��Mat����
	assert(read.data);//�������Ϊ�վ���ִֹ��
	namedWindow("ɽ",CV_WINDOW_AUTOSIZE);//����һ�����ڣ���С����ӦͼƬ
	imshow("ɽ", read);
	waitKey(0);
	return 0;
}