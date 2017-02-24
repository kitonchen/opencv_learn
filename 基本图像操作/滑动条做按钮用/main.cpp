#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

void switch_on(Mat* input)//开关开启执行的函数
{
	cout << "开关开启" << endl;
	imshow("滑动条做开关用", *input);
}

void switch_off(Mat* input)//开关关闭执行的函数
{
	Mat offimg = *input;
	offimg = Mat(offimg.rows,offimg.cols,CV_8UC3,Scalar(0,0,0));
	cout << "开关关闭" << endl;
	imshow("滑动条做开关用",offimg);
}

static void switch_trackbar(int position,void *userdata)//滑动条的函数
{	
	if (position==1){//开启
		switch_on((Mat*)userdata);
	}else{
		switch_off((Mat*)userdata);
	}
}

int main()
{
	int colse = 0;
	Mat img = imread("beach.jpg");//读取图片
	namedWindow("滑动条做开关用");
	createTrackbar("开关", "滑动条做开关用", &colse, 1, switch_trackbar, (void*)&img);//输入数据先取地址在转换成空指针类型
	waitKey(0);
	return 0;
}