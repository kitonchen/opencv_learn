#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat read = imread("山.jpg");//实例化一个Mat对象
	assert(read.data);//如果数据为空就终止执行
	namedWindow("山",CV_WINDOW_AUTOSIZE);//建立一个窗口，大小自适应图片
	imshow("山", read);
	waitKey(0);
	return 0;
}