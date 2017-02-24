#include<iostream>
#include"Findhand.h"
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	FindHand test;//实例化一个寻找手部操作对象
	Scalar H_hsv, L_hsv;
	bool flag = true;
	L_hsv =Scalar(0,26,20);
	H_hsv = Scalar(50,200,200);

	while(1){

						
			try {            
					test.FilterImage();//滤波
					test.HsvHandle(H_hsv,L_hsv);//颜色空间转换并作灰度分布处理
					test.ShapeManage();
					//test.DetermineImage();//判断处理
					waitKey(30);//延迟30毫秒
			}catch(int){
				cout << "初始化对象失败" << endl;
				return -1;
			 }
	}
	return 0;
}