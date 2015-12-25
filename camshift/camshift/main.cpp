#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

    Mat image;

	bool backprojMode = false; //表示是否要进入反向投影模式，ture表示准备进入反向投影模式

	bool selectObject = false;//代表是否在选要跟踪的初始目标，true表示正在用鼠标选择

	int trackObject = 0; //代表跟踪目标数目

	bool showHist = true;//是否显示直方图

	Point origin;//用于保存鼠标选择第一次单击时点的位置

	Rect selection;//用于保存鼠标选择的矩形框

	int vmin = 10, vmax = 256, smin = 30;


void onMouse(int event,int x,int y,void*)
{
	if (selectObject)//当鼠标左键按下去时才有效，然后通过if里面的代码确定所选择的矩形区域的选择了
	{
		selection.x = MIN(x, origin.x);//鼠标左上角的顶点X坐标，此操作无论是从上往下拉出矩形或反之都可以得到左上角的坐标
		selection.y = MIN(y, origin.y);//同上

		selection.height = abs(x - origin.x);//计算矩形的宽
		selection.width = abs(y - origin.y);//矩形的高

		selection &= Rect(0, 0, image.cols, image.rows);//用于确保矩形区域在图片范围内
	}

	switch (event)
	{
	  case CV_EVENT_LBUTTONDOWN:
		      origin = Point(x, y);
			  selection = Rect(x, y, 0, 0);//鼠标刚按下去时就初始化一个矩形区域
			  selectObject = true;//正在用鼠标选择
			  break;
	  case CV_EVENT_LBUTTONUP  :
		      selectObject = false;//选择完毕
			  if (selection.width > 0 && selection.height > 0) {
				  trackObject = -1;//如果初始化一个矩形成功，则开始追踪。取值-1代表不限定追踪目标
			  }
			  break;
	}
}

void help()
{
	cout << "本程序为测试camshfit的一个例程" << endl << "用鼠标选择出一个矩形区域来选定追踪目标";
}

int main()
{
	help();
	VideoCapture cap;//摄像头对象
	Rect trackWindow;
	RotatedRect tracBox;//旋转的矩阵类
	int hsize = 16;
	float hranges[] = { 0,180 };//计算直方图函数中使用
	const float* phranges = hranges;
	cap.open(0);//打开摄像头
	if (!cap.isOpened())
	{
		cout << "摄像头打开失败" << endl;
		return -1;
	}
	namedWindow("直方图", 0);

	namedWindow("追踪颜色", 0);

	setMouseCallback("追踪颜色", onMouse, 0);//消息相应机制

	createTrackbar("Vmin", "追踪颜色", &vmin, 256, 0);//创建滑动条，最小值为256

	createTrackbar("Vmax", "追踪颜色", &vmax, 256, 0);//最后一个参数为0代表没调用滑动拖动的响应函数

	cvCreateTrackbar("Smin", "追踪颜色", &smin, 256, 0);//vmin，vmax，smin初始值为10，256，30
	Mat frame, hsv, hue, mask, hist, histing = Mat::zeros(200, 320, CV_8UC3), backproj;

	bool paused = false;

	while (1)
	{
		if (!paused)//没有暂停
		{
			cap >> frame;//从摄像头读取一帧
		}
	}


	return 0;
}