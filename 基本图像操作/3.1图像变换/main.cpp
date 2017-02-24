#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
// 直线，圆形检测原理解析引用参考浅墨大神的教程 http://blog.csdn.net/poem_qianmo/article/details/26977557
//仿射变换 参考 http://blog.csdn.net/poem_qianmo/article/details/33320997


int main()
{
	char choose;//选择参数
	Mat Circle, Line, Shift;//存放图片	
	Mat show;//显示
	vector<Vec4i> lines;//存放直线参数的向量,起点和终点的X,Y坐标数据
	vector<Vec3f> circles;//存放圆心坐标X,Y和半径
	//仿射变换
	Point2f orignTriangle[3];//声明两组点存放三角形
	Point2f targetTriangle[3];
	Point center;
	double angle;//顺时针旋转
	double scale;//缩放系数
	Mat rofMat(2, 3, CV_32FC1);//旋转矩阵
	Mat warpMat(2, 3, CV_32FC1);//变换矩阵
	
	while (true)
	{
		system("cls");
		cout << "按1：显示圆形检测\n按2:显示直线检测\n按3:显示仿射变换\n";
		cin >> choose;
		switch (choose)
		{
		case '1':
				Circle = imread("圆形检测.jpg");//读取图片	
				cvtColor(Circle, show, CV_BGR2GRAY);//转化为灰度图
				GaussianBlur(show, show, Size(5,5),1.5,1.5);//高斯滤波
				HoughCircles(show, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 25, 100);//霍夫梯度，累加器/原图分辨率倒数1，圆心最小距离50，边缘检测阈值100，累加器阈值100,最小半径30，最大半径100
			for (size_t i = 0; i < circles.size(); i++) {
				Point center(round(circles[i][0]), round(circles[i][1]));//读取圆心坐标
				int radius = round(circles[i][2]);//读取半径
				circle(Circle, center, 2, Scalar(255, 255, 255), 2);//画圆心
				circle(Circle, center, radius, Scalar(255, 255, 255), 2);//画圆轮廓
				cout << "圆心坐标:(" << center.x << "," << center.y << "),半径:" << radius << endl;
			}
				imshow("圆形检测结果", Circle);
					if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
					}
		case '2':Line = imread("直线检测.jpg");
				cvtColor(Line,show, CV_BGR2GRAY);//转化为灰度图
				Canny(show,show, 125,250);//做边缘检测
				imshow("边缘", show);
				//普通霍夫直线变换效果比较渣，所以用概率霍夫变换
				HoughLinesP(show, lines, 1, CV_PI / 180,50,120,10);//径向精度1，角度精度π/180,累计点数目阈值50，最低显示长度120，允许点点之间连接起来的最大距离10
				show = Scalar(0, 0, 0);
			for (size_t i = 0; i < lines.size(); i++) {	
				Point x1, x2;//储存概率直线检测后的两个重点
				x1.x = lines[i][0]; x1.y = lines[i][1];//存放起点
				x2.x = lines[i][2]; x2.y = lines[i][3];//存放终点
				line(show,x1,x2,Scalar(255, 255, 255));
				line(Line,x1,x2,Scalar(255, 255, 255),1,CV_AA);
			}
				imshow("直线检测结果灰度显示", show);
				imshow("直线检测结果彩色显示", Line);
					if (waitKey(0) == 13) {
				destroyAllWindows();
				break;
				}		
		case '3':Shift = imread("仿射变换.jpg");
				 show = Mat::zeros(Shift.size(), Shift.type());//将目标图像设置成全黑，格式与输入图像相等
				 //设置仿射三角形的点
				 orignTriangle[0] = Point2f(0, 0);				
				 orignTriangle[1] = Point2f(static_cast<float>(Shift.cols - 1),0);//static_cast为C++的强制转换算符
				 orignTriangle[2] = Point2f(0,static_cast<float>(Shift.rows - 1));
				 targetTriangle[0] = Point2f(static_cast<float>(Shift.cols*0.0), static_cast<float>(Shift.rows*0.33));
				 targetTriangle[1] = Point2f(static_cast<float>(Shift.cols*0.65), static_cast<float>(Shift.rows*0.35));
				 targetTriangle[2] = Point2f(static_cast<float>(Shift.cols*0.15), static_cast<float>(Shift.rows*0.6));
				 //求解仿射变换矩阵
				 warpMat = getAffineTransform(orignTriangle, targetTriangle);
				 //
				 warpAffine(Shift, show, warpMat, show.size());
				 imshow("原图", Shift);
				 imshow("仿射变换后的结果", show);
				 center = Point(show.cols / 2, show.rows / 2);
				 angle = -30;//顺时针旋转
				 scale = 0.6;//缩放系数
				 rofMat = getRotationMatrix2D(center, angle, scale);//计算旋转矩阵
				 warpAffine(show, show, rofMat, show.size());
				 imshow("仿射变换和旋转后的结果", show);
				 if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
					}
		default:
			break;
		}
	}

	return 0;
}