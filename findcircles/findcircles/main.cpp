#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture cap(0);//������ͷ
	Mat in_img;//�洢֡
	Mat two_img;
	vector<cv::Vec3f> circles;//Բ����
	namedWindow("����ͷ");//��������
	if (cap.isOpened())//�ж�����ͷ�Ƿ��
	{
		cout << "����ͷ�ɹ��򿪣���ʼʶ��" << endl;
		while (1)//ѭ����ȡ֡����
		{
			cap >> in_img;//��ȡͼ�����е�һ֡
			two_img = in_img;
			GaussianBlur(in_img, in_img, Size(5, 5), 1.5);//��˹ƽ��ȥ��
			cvtColor(in_img, in_img, COLOR_BGR2GRAY);//��ֵ��ת�����ڰ�
			HoughCircles(in_img,circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 50, 100);//����ת����Բ����
			for (size_t i = 0; i < circles.size(); i++)//����Բ
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				circle(two_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				circle(two_img, center, radius, Scalar(0, 255, 0), 3, 8, 0);
			}
			imshow("����ͷ",two_img);//��ʾ�������
			waitKey(30);//��ʱ
		}
	}
	waitKey(0);
	return 0;
}
