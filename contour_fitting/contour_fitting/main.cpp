#include<iostream>
#include<opencv2\opencv.hpp>
   
using namespace std;
using namespace cv;



int main()
{

	VideoCapture cap(0);
	Mat img_show;

	Mat img_manage;

	vector<vector<Point>> contours;

	//namedWindow("显示");
	//namedWindow("显示2");
	if (cap.isOpened())
	{
		cout << "打开" << endl;
		while (1)
		{
			cap >> img_show;
			if (img_show.data == NULL)
				continue;
			img_manage = img_show;
			GaussianBlur(img_manage, img_manage, Size(5, 5), 1.5);
			cvtColor(img_manage, img_manage, CV_RGB2GRAY);
			Canny(img_manage, img_manage, 50, 150);
			findContours(img_manage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
			cout << "num" << contours.size() << endl;
			drawContours(img_show, contours, -1, Scalar(255), 2);
			imshow("已经处理图像",img_manage);
			waitKey(30);
		}
		
	}

   

	return 0;
}
