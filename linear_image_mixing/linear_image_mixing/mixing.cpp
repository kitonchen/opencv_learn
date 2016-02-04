#include<opencv2\opencv.hpp>
#include"mixing.h"
#include<iostream>
using namespace std;
using namespace cv;

void RoiAddImage()//读取图像函数，添加感兴趣区域
{
	Mat in_image = imread("input.jpg");
	Mat mix_image = imread("mix.jpg");
	if (!in_image.data){
		printf("打开图像失败");
	}if (!mix_image.data){
		printf("打开图像失败"); 
	 }
	//定义一个Mat类型并给其设定ROI区域
	Mat imageROI = in_image(Rect(200, 250, mix_image.cols, mix_image.rows));
	//加载掩膜，必须为灰度图
	Mat mask = imread("mix.jpg", 0);
    //讲掩膜拷贝到ROI
	mix_image.copyTo(imageROI, mask);
	//显示结果
	namedWindow("ROI叠加");
	imshow("ROI叠加", in_image);

}

void Linear_Mixing()//线性混合实现函数
{
	double alphavalue = 0.5;
	double betvalue;
	Mat in_put, in_put2, dstImage;
	//加权操作
	in_put = imread("input.jpg");
	in_put2 = imread("input2.jpg");
	betvalue = 1.0 - alphavalue;
	addWeighted(in_put, alphavalue, in_put2, betvalue,0 , dstImage);
	//创建窗口显示原图
	imshow("线性混合原图", in_put);
	imshow("线性混合结果", dstImage);

}

void RoiLinearMxing()//感兴趣区域线性混合
{
	Mat in_image,in_image2;
	//读取图像
	in_image = imread("input.jpg");
	in_image2 = imread("mix.jpg");

	if (!in_image.data){
		cout << "打开图像失败" << endl;
    }if (!in_image2.data){
		cout << "打开图像失败" << endl;
	 }

	//定义一个Mat类型并给其设定ROI区域
	Mat imageROI;
	imageROI = in_image(Rect(250,250,in_image2.cols,in_image2.rows));

	addWeighted(imageROI, 0.5, in_image2, 0.3, 0, imageROI);

	imshow("感兴趣区域线性混合", in_image);

}
