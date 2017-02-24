#pragma once
#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>
using namespace cv;
using namespace std;

const int INIT_ERRO = -1;//初始化失败异常
class FindHand
{
public:
	FindHand();
	FindHand(Mat &input);
	~FindHand();
	void FilterImage();
	void HsvHandle(Scalar High, Scalar Low);
	void ShapeManage();
	void DrawShow();
	
private: Mat inputI;
		 Mat manageI;
		 VideoCapture findCapture;		
		 Mat Hhsv, Lhsv;
		 vector<vector<Point>> contours;//contours的每个元素都是一个向量，每个元素本身也是一个向量储存了一个轮廓的点集
		
};
