// ����Ȥ����ROI.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{   
	namedWindow("����Ȥ����");
	Mat orignimg = imread("beach.jpg");//��ȡͼƬ
	Mat logoimg = imread("logo.jpg");
	Mat imgroi = orignimg(Rect(30,30, logoimg.cols, logoimg.rows));//����orignͼƬ������Ϊ��100��100���������logoimg��ȵ�����Ϊ����Ȥ����PS:Mat,Rect,Point���ݽṹ������ԭ�㶼�������Ͻ�
    ///opencv3�е�������Ӧ����ǰ�汾�ĸ߶�height��������Ӧ���
	Mat mask = imread("logo.jpg");
	logoimg.copyTo(imgroi,logoimg);
	cout << "orignimg��������" << orignimg.rows << "������" << orignimg.cols << endl;
	cout << "logoimg��������" << logoimg.rows << "������" << logoimg.cols << endl;
	imshow("����Ȥ����", orignimg);
	waitKey(0);
    return 0;
}

