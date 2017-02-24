#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//http://blog.csdn.net/poem_qianmo/article/details/28261997
int main()
{   //浸水填充类似于画图中的填充
	
	Mat input = imread("beach.jpg");
	imshow("原始图", input);
	Rect rect;
	//无掩膜版本
	floodFill(input, Point(0,0), Scalar(155, 255, 55), &rect, Scalar(100, 200,100), Scalar(10,10,10));
	imshow("处理效果", input);
	waitKey(0);
	return 0;
}