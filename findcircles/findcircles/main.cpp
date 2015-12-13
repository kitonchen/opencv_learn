#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture cap(0);//打开摄像头
	Mat in_img;//存储帧
	Mat two_img;
	vector<cv::Vec3f> circles;//圆向量
	namedWindow("摄像头");//创建窗口
	if (cap.isOpened())//判断摄像头是否打开
	{
		cout << "摄像头成功打开，开始识别" << endl;
		while (1)//循环读取帧序列
		{
			cap >> in_img;//读取图像流中的一帧
			two_img = in_img;
			GaussianBlur(in_img, in_img, Size(5, 5), 1.5);//高斯平滑去噪
			cvtColor(in_img, in_img, COLOR_BGR2GRAY);//二值化转化，黑白
			HoughCircles(in_img,circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 50, 100);//霍夫转化找圆向量
			for (size_t i = 0; i < circles.size(); i++)//绘制圆
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				circle(two_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				circle(two_img, center, radius, Scalar(0, 255, 0), 3, 8, 0);
			}
			imshow("摄像头",two_img);//显示处理后结果
			waitKey(30);//延时
		}
	}
	waitKey(0);
	return 0;
}
