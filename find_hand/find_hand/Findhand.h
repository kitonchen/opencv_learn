#pragma once
#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>
using namespace cv;
using namespace std;

const int INIT_ERRO = -1;//��ʼ��ʧ���쳣
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
		 vector<vector<Point>> contours;//contours��ÿ��Ԫ�ض���һ��������ÿ��Ԫ�ر���Ҳ��һ������������һ�������ĵ㼯
		
};
