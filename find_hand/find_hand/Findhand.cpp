#include"Findhand.h"
#include<iostream>
#include<opencv2\opencv.hpp>
FindHand::FindHand()
{
	findCapture.open(0);
	if (!findCapture.isOpened()){//如果摄像头打开失败
		std::cout << "摄像头初始化失败" << std::endl;
		throw  INIT_ERRO ;
	}

}

FindHand::~FindHand()
{

}

void FindHand::FilterImage()
{
	findCapture >> inputI;
	if (!inputI.data){//如果数据为空
		std::cout << "接收到一帧空数据" << std::endl;
	}
	//manageI = inputI;//将接受帧数据传送给处理帧
	bilateralFilter(inputI,manageI, 5, 100, 100);//双边滤波保护边缘
}

void FindHand::HsvHandle(Scalar High, Scalar Low)
{
	
	cvtColor(manageI, manageI, CV_BGR2HSV);//将RGB空间转换到HSV空间	
	
    inRange(manageI,Low,High,manageI);//根据颜色分布初步分离皮肤和其他颜色

	//imshow("手部提取效果", manageI);
}


void FindHand::ShapeManage()
{
	
	morphologyEx(manageI, manageI, MORPH_CLOSE , Mat(5,5, CV_8U));//形态学闭运算
	
	medianBlur(manageI, manageI, 3);//中值滤波
	
	//imshow("腐蚀操作", manageI);
	findContours(manageI, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);//寻找轮廓
	drawContours(inputI, contours, -1, Scalar(100, 100, 100),2);//画出轮廓
	imshow("寻找凸包",inputI);
}

void FindHand::DrawShow()
{

}
