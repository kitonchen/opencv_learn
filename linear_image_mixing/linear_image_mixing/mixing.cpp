#include<opencv2\opencv.hpp>
#include"mixing.h"
#include<iostream>
using namespace std;
using namespace cv;

void RoiAddImage()//��ȡͼ��������Ӹ���Ȥ����
{
	Mat in_image = imread("input.jpg");
	Mat mix_image = imread("mix.jpg");
	if (!in_image.data){
		printf("��ͼ��ʧ��");
	}if (!mix_image.data){
		printf("��ͼ��ʧ��"); 
	 }
	//����һ��Mat���Ͳ������趨ROI����
	Mat imageROI = in_image(Rect(200, 250, mix_image.cols, mix_image.rows));
	//������Ĥ������Ϊ�Ҷ�ͼ
	Mat mask = imread("mix.jpg", 0);
    //����Ĥ������ROI
	mix_image.copyTo(imageROI, mask);
	//��ʾ���
	namedWindow("ROI����");
	imshow("ROI����", in_image);

}

void Linear_Mixing()//���Ի��ʵ�ֺ���
{
	double alphavalue = 0.5;
	double betvalue;
	Mat in_put, in_put2, dstImage;
	//��Ȩ����
	in_put = imread("input.jpg");
	in_put2 = imread("input2.jpg");
	betvalue = 1.0 - alphavalue;
	addWeighted(in_put, alphavalue, in_put2, betvalue,0 , dstImage);
	//����������ʾԭͼ
	imshow("���Ի��ԭͼ", in_put);
	imshow("���Ի�Ͻ��", dstImage);

}

void RoiLinearMxing()//����Ȥ�������Ի��
{
	Mat in_image,in_image2;
	//��ȡͼ��
	in_image = imread("input.jpg");
	in_image2 = imread("mix.jpg");

	if (!in_image.data){
		cout << "��ͼ��ʧ��" << endl;
    }if (!in_image2.data){
		cout << "��ͼ��ʧ��" << endl;
	 }

	//����һ��Mat���Ͳ������趨ROI����
	Mat imageROI;
	imageROI = in_image(Rect(250,250,in_image2.cols,in_image2.rows));

	addWeighted(imageROI, 0.5, in_image2, 0.3, 0, imageROI);

	imshow("����Ȥ�������Ի��", in_image);

}
