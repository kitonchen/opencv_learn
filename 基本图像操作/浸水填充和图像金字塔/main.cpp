#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//http://blog.csdn.net/poem_qianmo/article/details/28261997
int main()
{   //��ˮ��������ڻ�ͼ�е����
	
	Mat input = imread("beach.jpg");
	imshow("ԭʼͼ", input);
	Rect rect;
	//����Ĥ�汾
	floodFill(input, Point(0,0), Scalar(155, 255, 55), &rect, Scalar(100, 200,100), Scalar(10,10,10));
	imshow("����Ч��", input);
	waitKey(0);
	return 0;
}