#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImg, histImg;
	vector<Mat> rgbChannels;//��ͨ������
	
	// �趨ֱ��ͼά��
	int histSize = 255;
	// �趨ȡֵ��Χ ( R,G,B) )
	//��0~255��Χ��ͳ��
	float range[] = { 0, 255 };
	const float* histRange = { range };
	//
	bool uniform = true; bool accumulate = false;
	//����
	Mat rHist,gHist,bHist;
	//��ȡͼ��
	srcImg = imread("boldt.jpg");
	//��ʼ����
	//����ͼ����Ϊopencv�洢ͼ���˳��ΪBGR�����Է�������˳��ҲΪBGR
	split(srcImg, rgbChannels);
	//�ο�opencv������վ
	/*&rgb_planes[0]: ��������(�����鼯)
		1 : ��������ĸ���(��������ʹ����һ����ͨ��ͼ������Ҳ�����������鼯)
		0 : ��Ҫͳ�Ƶ�ͨ��(dim)���� ����������ֻ��ͳ���˻Ҷ�(��ÿ�����鶼�ǵ�ͨ��)����ֻҪд 0 �����ˡ�
		Mat() : ����(0 ��ʾ���Ը�����)�� ���δ���壬��ʹ������
		r_hist : ����ֱ��ͼ�ľ���
		1 : ֱ��ͼά��
		histSize : ÿ��ά�ȵ�bin��Ŀ
		histRange : ÿ��ά�ȵ�ȡֵ��Χ
		uniform �� accumulate : bin��С��ͬ�����ֱ��ͼ�ۼ�*/
	calcHist(&rgbChannels[0], 1, 0, Mat(), bHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgbChannels[1], 1, 0, Mat(), gHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgbChannels[2], 1, 0, Mat(), rHist, 1, &histSize, &histRange, uniform, accumulate);
	//����ֱ��ͼ
	//��ʼ��ֱ��ͼ�Ĵ�С��Ϊ400*400�����ؾ���
	int histWidth = 400, histHeight = 400;
	//����ÿһά����ֵ��ֱ��ͼ�еĿ��
	int binWidth = round((double)histWidth / histSize);
	histImg = Mat(histWidth, histHeight, CV_8UC3,Scalar(0,0,0));
	//��ֱ��ͼ֮ǰ�����ݹ�һ����[0,hisImg�ĸ߶�]
	normalize(bHist, bHist, 0,histImg.rows, NORM_MINMAX);
	normalize(gHist, gHist, 0,histImg.rows, NORM_MINMAX);
	normalize(rHist, rHist, 0,histImg.rows, NORM_MINMAX);
	//����ֱ��ͼ
	for (int i = 1; i < histSize; ++i) {
		line(histImg, Point(binWidth*(i - 1),
			histHeight - round(rHist.at<float>(i - 1))),
			Point(binWidth*(i),
			histHeight - round(rHist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
		line(histImg, Point(binWidth*(i - 1),
			histHeight - round(gHist.at<float>(i - 1))),
			Point(binWidth*(i),
			histHeight - round(gHist.at<float>(i))),
			Scalar(0, 255,0), 2, 8, 0);
		line(histImg, Point(binWidth*(i - 1),
			histHeight - round(bHist.at<float>(i - 1))),
			Point(binWidth*(i),
			histHeight - round(bHist.at<float>(i))),
			Scalar(255, 0,0), 2, 8, 0);
	}
		imshow("��ȡ��ͼ��", srcImg);
		imshow("ֱ��ͼ", histImg);
		imshow("��ɫ����", rgbChannels[2]);
		imshow("��ɫ����", rgbChannels[0]);
		imshow("��ɫ����", rgbChannels[1]);
	waitKey(0);
	return 0;
}