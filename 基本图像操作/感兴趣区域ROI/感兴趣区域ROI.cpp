// 感兴趣区域ROI.cpp : 定义控制台应用程序的入口点。
//

#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;

int main()
{   
	namedWindow("感兴趣区域");
	Mat orignimg = imread("beach.jpg");//读取图片
	Mat logoimg = imread("logo.jpg");
	Mat imgroi = orignimg(Rect(30,30, logoimg.cols, logoimg.rows));//设置orign图片上坐标为（100，100），长宽和logoimg相等的区域为感兴趣区域。PS:Mat,Rect,Point数据结构的坐标原点都是在左上角
    ///opencv3中的行数对应于以前版本的高度height，列数对应宽度
	Mat mask = imread("logo.jpg");
	logoimg.copyTo(imgroi,logoimg);
	cout << "orignimg的行数：" << orignimg.rows << "列数：" << orignimg.cols << endl;
	cout << "logoimg的行数：" << logoimg.rows << "列数：" << logoimg.cols << endl;
	imshow("感兴趣区域", orignimg);
	waitKey(0);
    return 0;
}

