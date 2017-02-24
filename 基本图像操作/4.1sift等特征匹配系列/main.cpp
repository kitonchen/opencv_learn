// 4.1sift等特征匹配系列.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\legacy\legacy.hpp>

using namespace cv;
using namespace std;

void sift_test();//测试sift算法
void sift_match_test();//测试特征点匹配
void surf_test();
void surf_match_test();

int main()
{
	
//	sift_test();
//	sift_match_test();
	//surf_test();
	surf_match_test();
    return 0;
}

void sift_test()
{
	Mat src = imread("boldt.jpg");
	//限制特征点检测在100个左右
	SIFT sift(300);
	//特征点
	vector<KeyPoint> key_point;
	//描述符，掩码矩阵
	
	//输出
	Mat dst;
	//计算特征和描述子
	sift.detect(src, key_point);
	

	drawKeypoints(src,//输入
		key_point,//特征点矢量
		dst,//输出图像
		Scalar::all(-1),//随机绘制特征点的颜色
		//以特征点为中心画圆，圆的半径表示特征点的大小，直线表示特征点的方向
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("sift_test", dst);
	waitKey(0);
}

void sift_match_test()
{
	Mat src1 = imread("test1.png");
	Mat src2 = imread("test2.png");
	//描述符
	Mat descriptors1, descriptors2;
	//关键点
	cv::vector<KeyPoint> key_point1, key_point2;	
	SIFT sift(100);
	//计算关键点和描述符
	sift.detect(src1, key_point1);
	sift.detect(src2, key_point2);

	sift.compute(src1, key_point1, descriptors1);	
	sift.compute(src2, key_point2, descriptors2);

	Mat dst_matches;
	BFMatcher matcher;
	std::vector<DMatch> matches;//匹配器算子
	//匹配
	matcher.match(descriptors1, descriptors2, matches);

	nth_element(matches.begin(),     //匹配器算子的初始位置  
		matches.begin() + 29,     // 排序的数量  
		matches.end());       // 结束位置  
							  //剔除掉其余的匹配结果  
	matches.erase(matches.begin() + 30, matches.end());

	//绘制匹配结果
	drawMatches(src1, key_point1,//第一幅图，及特征点
				src2, key_point2,//第二幅图
				matches,//匹配器算子
				dst_matches);//匹配输出图像

	imshow("sift_matches_test", dst_matches);
	waitKey(0);
}

void surf_test()
{//用法和sift一样。一个SURF类的对象即可进行所有操作。
	SURF surf_handle;
	Mat src1 = imread("test1.png");

	//描述符,关键点	
	vector<KeyPoint> key_point1;
	//检测关键点,计算描述符
	surf_handle.detect(src1, key_point1);
	

	Mat dst1;

	drawKeypoints(src1, key_point1, dst1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("sruf_test", dst1);
	waitKey(0);
}

void surf_match_test()
{

	Mat src1 = imread("test1.png");
	Mat src2 = imread("test2.png");
	//描述符
	Mat descriptors1, descriptors2;
	//关键点
	vector<KeyPoint> key_point1, key_point2;
	SURF surf;
	//计算关键点和描述符
	surf.detect(src1, key_point1);
	surf.detect(src2, key_point2);

	surf.compute(src1, key_point1, descriptors1);
	surf.compute(src2, key_point2, descriptors2);

	Mat dst_matches;
	BFMatcher matcher;
	std::vector<DMatch> matches;//匹配器算子
								//匹配
	matcher.match(descriptors1, descriptors2, matches);

	nth_element(matches.begin(),     //匹配器算子的初始位置  
		matches.begin() + 29,     // 排序的数量  
		matches.end());       // 结束位置  
							  //剔除掉其余的匹配结果  
	matches.erase(matches.begin() + 30, matches.end());

	//绘制匹配结果
	drawMatches(src1, key_point1,//第一幅图，及特征点
		src2, key_point2,//第二幅图
		matches,//匹配器算子
		dst_matches);//匹配输出图像

	imshow("sift_matches_test", dst_matches);
	waitKey(0);
	
}


