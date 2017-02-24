#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;


VideoCapture MyCap;//视频对象
int sildp = 0;//滚动条初始位置

 static void ontrackslide(int pos,void *)//pos为帧数，如果不调用设置默认为createTrackbar第三个参数的值
{
	MyCap.set(CAP_PROP_POS_FRAMES, pos);//设置视频当前帧数
	//MyCap.set(CAP_PROP_POS_AVI_RATIO, pos);//按AVI长度比例
}
 
int main()
{
	int frames;//记录视频帧数
	Mat ReadImage;
	namedWindow("添加滚动条", CV_WINDOW_AUTOSIZE);//声明一个视频，大小自适应
	//读取视频,两种打开方式，两种读取路径，任何一种打开方式都对应两种读取路径
	//第一种：通过初始化对象打开
	//VideoCapture MyCap("E:\\学习资料\\learn_opencv\\基本图像操作\\读取一个视频\\bike.avi");//全局路径
	//第二种：通过open函数打开，读取文件路径参考上面
	MyCap.open("bike.avi");   	
	assert(MyCap.isOpened());//是否成功打开

	frames = MyCap.get(CV_CAP_PROP_FRAME_COUNT);//读取视频的帧数

	if (frames != 0) {//参数1：滚动条的文本，2：作用的窗口名,3：初始值,4:最大值,5:回调函数
		createTrackbar("帧数", "添加滚动条", &sildp, frames, ontrackslide);//第三个参数为全局变量是，可以不管最后一个在这里没有输入的userdata参数，这参数是用户传给回调函数的数据
	}
	while (1)
	{
		MyCap >> ReadImage;//读取第一帧数据

		if (ReadImage.empty()) break;//如果视频已经播放完。数据为空时,判断条件也可以是data成员

		setTrackbarPos("帧数", "添加滚动条", sildp);//设置滚动条当前位置，这里即帧数

		imshow("添加滚动条", ReadImage);//显示
		
		waitKey(30);//延迟30毫秒，后更新
		
		sildp++;//帧数加1，在循环中就可以实现滚动条帧数随视频播放滚动
		
		char c = waitKey(33);//延迟33毫秒检测是否有退出操作

		if (c == 27) break;//如果按下ESC键，就会退出
	}
	  
	return 0;
}