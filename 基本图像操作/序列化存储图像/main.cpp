#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{ 
	Mat wirteimg = Mat::eye(10, 10, CV_8UC2);//生成一个100*100的对角矩阵
	Mat readimg;
	//imwrite("对角矩阵.jpg", img);//保存为jpg格式。测试时删除原文件可查看效果，用全局路径可以保存到特定路径
	//imread()函数可以进行读取
	//imwrite函数只支持CV8U类型的数据（使用OpenCV保存其他类型Mat的时候，程序不会报错，但是无法生成结果文件）可以用FileStorage类,来保存为XML/YAML文件（一种采用标记语言编码数据的文件格式）
	FileStorage fw("对角矩阵.xml", FileStorage::WRITE);//做输出
		fw << "Mat" << wirteimg;//通过输出流写文件，给定MAT标签
			fw.release();//释放文件流对象
	FileStorage fr("对角矩阵.xml", FileStorage::READ);//做读取
	//读取并打印XML文件
		fr["Mat"] >> readimg;//通过输入流读取数据，读取时也要先用标签
			fr.release();//调用这个函数后	
	cout << readimg;		
return 0;
}