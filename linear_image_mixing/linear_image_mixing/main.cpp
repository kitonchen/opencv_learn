#include"mixing.h"
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
int main()
{
	
	RoiAddImage();//��ȡͼ��������Ӹ���Ȥ����

	RoiLinearMxing();
	Linear_Mixing();
	cvWaitKey(0);
	return 0;
}