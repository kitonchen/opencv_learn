#include"Findhand.h"
#include<iostream>
#include<opencv2\opencv.hpp>
FindHand::FindHand()
{
	findCapture.open(0);
	if (!findCapture.isOpened()){//�������ͷ��ʧ��
		std::cout << "����ͷ��ʼ��ʧ��" << std::endl;
		throw  INIT_ERRO ;
	}

}

FindHand::~FindHand()
{

}

void FindHand::FilterImage()
{
	findCapture >> inputI;
	if (!inputI.data){//�������Ϊ��
		std::cout << "���յ�һ֡������" << std::endl;
	}
	//manageI = inputI;//������֡���ݴ��͸�����֡
	bilateralFilter(inputI,manageI, 5, 100, 100);//˫���˲�������Ե
}

void FindHand::HsvHandle(Scalar High, Scalar Low)
{
	
	cvtColor(manageI, manageI, CV_BGR2HSV);//��RGB�ռ�ת����HSV�ռ�	
	
    inRange(manageI,Low,High,manageI);//������ɫ�ֲ���������Ƥ����������ɫ

	//imshow("�ֲ���ȡЧ��", manageI);
}


void FindHand::ShapeManage()
{
	
	morphologyEx(manageI, manageI, MORPH_CLOSE , Mat(5,5, CV_8U));//��̬ѧ������
	
	medianBlur(manageI, manageI, 3);//��ֵ�˲�
	
	//imshow("��ʴ����", manageI);
	findContours(manageI, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);//Ѱ������
	drawContours(inputI, contours, -1, Scalar(100, 100, 100),2);//��������
	imshow("Ѱ��͹��",inputI);
}

void FindHand::DrawShow()
{

}
