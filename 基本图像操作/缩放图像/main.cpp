#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	Mat begin, result;//��ʼ��һ��ԭͼ�����ͼ����
	Size half;//��ʼ��һ���������
	namedWindow("ԭͼ");//����
	namedWindow("Ч��ͼ");
	begin = imread("ɽ.jpg");//��ȡͼƬ
	assert(begin.rows % 2 == 0 && begin.cols % 2 == 0);//�ж��Ƿ��ʺ�ת��
	half.height = begin.rows / 2;//���ոĸ��ı���Ϊԭ����һ��
	half.width = begin.cols / 2;
	pyrDown(begin, result,half);//��С����
	imshow("ԭͼ", begin);//��ʾ
	imshow("Ч��ͼ", result);
	waitKey(0);

	return 0;
}