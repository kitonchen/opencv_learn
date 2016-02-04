#include"mixing.h"
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
int main()
{
	
	RoiAddImage();//读取图像函数，添加感兴趣区域

	RoiLinearMxing();
	Linear_Mixing();
	cvWaitKey(0);
	return 0;
}