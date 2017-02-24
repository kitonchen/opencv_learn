#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat testimg = imread("test.jpg");//读取
	Mat out_img;//输出结果的对象
	//多种滤波效果，滤波处理可以理解为多图像进行相应的模糊处理，让特定的信息在对图像分析中的某些影响弱化或强化，甚至去除（个人理解不保证对）
	//http://blog.csdn.net/zouxy09/article/details/49080029 的大神有讲解滤波的数学原理
	//滤波核的大小应该是奇数，这样才会出现中心点
	//滤波核（矩阵）的所有元素和等于1，处理后图像亮度不变，大于1处理后图像变亮，小于1处理后图像变暗。处理后若像素点数值不在0~255内可以断截也可以做相应数学处理将其映射回0~255区间内，例如对于负数取绝对值
	//滤波核所有元素和等于0，可以找边缘
	//以下常用滤波器大小都取3*3
	//imshow("未处理效果", testimg);
	//滤波
	////1.均值滤波。平滑
	//blur(testimg, out_img, Size(3, 3));
	//imshow("均值滤波效果", out_img);
	////2.中值滤波。处理椒盐效果或细线的效果好
	//Mat midimg = imread("中值滤波测试.jpg");
	//medianBlur(midimg, out_img, 7);//这里用7效果明显
	//imshow("中值滤波未处理效果", midimg);
	//imshow("中值滤波效果", out_img);
	////3.高斯滤波,加大方差会滤的更平滑些，但会损失更多细节
	//GaussianBlur(testimg, out_img, Size(3, 3), 0);
	//imshow("高斯滤波效果", out_img);
	////4.双边滤波，边缘保护滤波
	//bilateralFilter(testimg, out_img, 3, 2, 2);//输入，输出，算子半径，颜色空间方差，坐标空间方差
	//imshow("双边滤波效果", out_img);
	////5.通用滤波器,自定义滤波核
	//Mat kernel = (Mat_<int>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);//这里的核做了边缘锐化处理
	//filter2D(testimg, out_img, testimg.depth(), kernel);
	//imshow("通用滤波器效果", out_img);
	////6.可分离滤波器,特点计算快，传入两个1维的滤波核
	//kernel = getGaussianKernel(7, 1.5, CV_32F);//方差为1.5
	//sepFilter2D(testimg,out_img,testimg.depth(),kernel, kernel);//相当于进行了一次高斯滤波GaussianBlur(image, result,Size(7, 7), 1.5);
	//imshow("可分离滤波效果", out_img);
/**************************************************************************************************************/
	testimg = imread("形态学处理测试.jpg");
	imshow("未处理效果", testimg);
	Mat ker = getStructuringElement(MORPH_RECT, Size(3, 3));//获得一个矩形的掩模
	//形态学运算  可以消除噪声或分割出独立的图像元素，也可用于寻找极值为值和求出图像的梯度
	//图像和核进行卷积
	//二值图像的效果最明显
	//1.膨胀（填补凹洞） 做卷积计算核覆盖的区域的最大值，并把最大值赋值给制定参考点
	dilate(testimg, out_img,ker);
	imshow("膨胀效果", out_img);
	//2.腐蚀(消除细的凸起) 计算原理和膨胀相反去最小值
	erode(testimg, out_img, ker);
	imshow("腐蚀效果", out_img);
	//3.通用运算
		//i.开运算(先腐蚀后膨胀)消除小物体、在纤细点处分离物体、平滑较大物体的边界的同时并不明显改变其面积
	     morphologyEx(testimg, out_img, MORPH_OPEN, ker);
		 imshow("开运算结果", out_img);
		//ii.闭运算(先膨胀后腐蚀)排除小型黑洞(黑色区域)
		 morphologyEx(testimg, out_img, MORPH_CLOSE, ker);
		 imshow("闭运算结果", out_img);
		//iii.形态学梯度(膨胀图-腐蚀图)可以将团块的边缘突出出来,保留边缘
		 morphologyEx(testimg, out_img, MORPH_GRADIENT, ker);
		 imshow("形态学梯度结果", out_img);
		//iiii.顶帽(原图-开运算结果)分离比邻近点亮一些的斑块。当一幅图像具有大幅的背景的时候，而微小物品比较有规律的情况下适用
		 morphologyEx(testimg, out_img, MORPH_TOPHAT, ker);
		 imshow("顶帽运算结果", out_img);
		//iiiii.黑帽(原图-闭运算结果)分离比邻近点暗一些的斑块
		 morphologyEx(testimg, out_img, MORPH_BLACKHAT, ker);
		 imshow("黑帽运算结果", out_img);
	waitKey(0);
	return 0;
}