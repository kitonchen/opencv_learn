#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImg, histImg;
	vector<Mat> rgbChannels;//单通道向量
	
	// 设定直方图维数
	int histSize = 255;
	// 设定取值范围 ( R,G,B) )
	//在0~255范围内统计
	float range[] = { 0, 255 };
	const float* histRange = { range };
	//
	bool uniform = true; bool accumulate = false;
	//分量
	Mat rHist,gHist,bHist;
	//读取图像
	srcImg = imread("boldt.jpg");
	//开始计算
	//分离图像，因为opencv存储图像的顺序为BGR，所以分离结果的顺序也为BGR
	split(srcImg, rgbChannels);
	//参考opencv中文网站
	/*&rgb_planes[0]: 输入数组(或数组集)
		1 : 输入数组的个数(这里我们使用了一个单通道图像，我们也可以输入数组集)
		0 : 需要统计的通道(dim)索引 ，这里我们只是统计了灰度(且每个数组都是单通道)所以只要写 0 就行了。
		Mat() : 掩码(0 表示忽略该像素)， 如果未定义，则不使用掩码
		r_hist : 储存直方图的矩阵
		1 : 直方图维数
		histSize : 每个维度的bin数目
		histRange : 每个维度的取值范围
		uniform 和 accumulate : bin大小相同，清楚直方图痕迹*/
	calcHist(&rgbChannels[0], 1, 0, Mat(), bHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgbChannels[1], 1, 0, Mat(), gHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&rgbChannels[2], 1, 0, Mat(), rHist, 1, &histSize, &histRange, uniform, accumulate);
	//创建直方图
	//初始化直方图的大小，为400*400的像素矩阵
	int histWidth = 400, histHeight = 400;
	//计算每一维像素值在直方图中的宽度
	int binWidth = round((double)histWidth / histSize);
	histImg = Mat(histWidth, histHeight, CV_8UC3,Scalar(0,0,0));
	//画直方图之前将数据归一化到[0,hisImg的高度]
	normalize(bHist, bHist, 0,histImg.rows, NORM_MINMAX);
	normalize(gHist, gHist, 0,histImg.rows, NORM_MINMAX);
	normalize(rHist, rHist, 0,histImg.rows, NORM_MINMAX);
	//画出直方图
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
		imshow("读取的图像", srcImg);
		imshow("直方图", histImg);
		imshow("红色分量", rgbChannels[2]);
		imshow("蓝色分量", rgbChannels[0]);
		imshow("绿色分量", rgbChannels[1]);
	waitKey(0);
	return 0;
}