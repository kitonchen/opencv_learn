#include<iostream>
#include<time.h>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	clock_t stime, etime;
	//VideoCapture cap("光源充足.avi");//打开视频
	VideoCapture cap("红球.avi");//打开视频
	Mat in_img;//存储帧
	Mat two_img;
	int		findcount = 0;//计算正确识别出来的帧数
	double avgtime=0;
	vector<cv::Vec3f> circles;//圆向量
	namedWindow("摄像头");//创建窗口
	if (cap.isOpened())//判断摄像头是否打开
	{
		cout << "摄像头成功打开，开始识别" << endl;
		int framecount = cap.get(CV_CAP_PROP_FRAME_COUNT);//获取视频帧数
		bool learnflag = false;
		Mat Roitrack;
		while (framecount)//循环读取帧序列
		{

			cap >> in_img;//读取图像流中的一帧
			two_img = in_img;
			stime = clock();
			GaussianBlur(in_img, in_img, Size(5,5), 2,2);//高斯平滑去噪
			cvtColor(in_img, in_img, COLOR_BGR2GRAY);//转化成灰度，黑白			
			HoughCircles(in_img,circles, CV_HOUGH_GRADIENT, 2,100,150, 100, 50,200);//霍夫转化找圆向量
			etime = clock();
				for (size_t i = 0; i < circles.size(); i++)//绘制圆
				{					
					findcount++;
					Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
					int radius = cvRound(circles[i][2]);
					circle(two_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
					circle(two_img, center, radius, Scalar(0, 255, 0), 3, 8, 0);
					cout << "圆心坐标:(" << center.x << "," << center.y << ")" << ",半径:" << radius << endl;
					cout << "用时:" << (double)(etime - stime) / CLOCKS_PER_SEC << "秒" << endl;
					avgtime += (double)(etime - stime) / CLOCKS_PER_SEC;
				}
				imshow("摄像头", two_img);//显示处理后结果			
			    cv::waitKey(30);//延时
				framecount--;
		}
		cout << "识别率" << (findcount / (float)cap.get(CV_CAP_PROP_FRAME_COUNT)) * 100 << "%" << endl;
		cout << "平均帧识别成功用时:" << avgtime / findcount << "秒" << endl;
	}
	cv::waitKey(0);
	return 0;
}
