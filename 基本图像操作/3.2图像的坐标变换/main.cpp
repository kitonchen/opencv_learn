#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
// 距离变换的基本含义是计算一个图像中非零像素点到最近的零像素点的距离，也就是到零像素点的最短距离。
int main()
{
	int distanceMod;
	Mat readimg;
	Mat tempimg;
	Mat outimg;
	Mat oneimg, twoimg, threeimg;
	readimg =imread("手掌.jpg");//读取图像
	cvtColor(readimg,tempimg, CV_BGR2GRAY);//转灰度图
    threshold(tempimg, tempimg,200,255,CV_THRESH_OTSU);//自适应阈值化
	
	   //归一化处理,imshow的范围区间在0到255之间，而在距离变换上像素值的变化大概在很小的一个区间内，一般不超过10
		//opencv中的imshow显示的数据格式是float或char，归一化之后的数值为32位浮点型，使得像素间的梯度变化差异增大
		//距离变化的效果变得明显
		while (1)
		{
			system("cls");
			cout << "1.欧几里德距离.2.城市距离 3.棋盘距离" << endl;
			cout << "请输入距离模式：";
			cin >> distanceMod;
			switch (distanceMod)
			{		//距离公式，经典欧几里得距离，模板大小3×3
			case 1:distanceTransform(tempimg, oneimg, DIST_L2, 3);
				   normalize(oneimg, oneimg,1.0,0.0,NORM_MINMAX);//归一化处理
				   imshow("自适应阈值结果", tempimg);
				   imshow("距离变换结果", oneimg);
				cout << "欧几里得距离" << endl; 
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//曼哈顿距离（城市距离）|x1-x2|+|y1-y2|
			case 2:distanceTransform(tempimg, twoimg, DIST_L1, 3);
				normalize(twoimg, twoimg, 1.0, 0.0, NORM_MINMAX);
				imshow("自适应阈值结果", tempimg);
				imshow("距离变换结果", twoimg);
				cout << "城市距离距离" << endl; 
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//切比雪夫距离（棋盘距离）
			case 3:distanceTransform(tempimg, threeimg, DIST_C, 3);
				normalize(threeimg, threeimg, 1.0, 0.0, NORM_MINMAX);
				imshow("自适应阈值结果", tempimg);
				imshow("距离变换结果", threeimg);
				cout << "棋盘距离" << endl;
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//其他距离
			default:
				break;
			}
			
		}
		
	return 0;
}