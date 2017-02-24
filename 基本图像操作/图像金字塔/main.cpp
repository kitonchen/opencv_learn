#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//图像金字塔说白了就是放大缩小图片 http://blog.csdn.net/poem_qianmo/article/details/26157633
int main()
{
	//Resize()函数 可以任意指定大小
	Mat input = imread("beach.jpg");
	imshow("原图", input);
	//用法1
	//Mat out = Mat::zeros(520,520, CV_8UC3);//新建一个大小为520*520的图片
	//resize(input,out, out.size());
	//imshow("更新大小", out);
	//用法2
	Mat tempimg, outimg;
	tempimg = input;//将原图复制给临时变量
	resize(tempimg, outimg, Size(tempimg.cols * 2, tempimg.rows * 2));//面积放大为原来4倍
	imshow("放大", outimg);
	resize(tempimg, outimg, Size(tempimg.cols / 2, tempimg.rows / 2));//缩小
	imshow("缩小", outimg);
	//另有pyrup()放大，prydown()缩小这两个函数可以用
	waitKey(0);
	return 0;
}