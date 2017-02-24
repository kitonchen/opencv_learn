#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	Mat begin, result;//初始化一个原图和输出图对象
	Size half;//初始化一个面积对象
	namedWindow("原图");//窗口
	namedWindow("效果图");
	begin = imread("山.jpg");//读取图片
	assert(begin.rows % 2 == 0 && begin.cols % 2 == 0);//判断是否适合转化
	half.height = begin.rows / 2;//接收改更改倍数为原来的一半
	half.width = begin.cols / 2;
	pyrDown(begin, result,half);//缩小函数
	imshow("原图", begin);//显示
	imshow("效果图", result);
	waitKey(0);

	return 0;
}