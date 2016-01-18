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
	MouseCallback onMouse;
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

	setMouseCallback("颜色追踪", onMouse, 0);//消息相应机制

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
			if (frame.empty()) {//如果数据为空
				break;
			}
			frame.copyTo(image);
			if (!paused) {//没有按暂停键
				cvtColor(image, hsv, CV_BGR2HSV);//将该帧RGB空间转为HSV空间
				if (trackObject) {//初始化为0，或者按完键盘的'c'建后也为0，鼠标单击后为-1
					int _vmin = vmin, _vmax = vmax;
					//inRange函数的功能是检查输入数组每个元素大小是否在2个给定数值之间。可以有多通道，mask保存0通道的最小值，就是h分量
					//这里利用了HSV的3个通道，比较H，0~180，S,Smin~256,V,min(vmin,vmax),max(vmin,vmax)如果3个通道都在对应的范围内，则msak对应的那个点的值为1（0XFF），否则为0（0X00）
					inRange(hsv, Scalar(0, smin, min(_vmin, _vmax)), Scalar(180, 256, max(_vmin, _vmax)), mask);	
					int ch[] = { 0,0 };
					hue.create(hsv.size(), hsv.depth());//HUE初始化为一个与HSV大小深度一样的矩阵，色调的度量是用角度表示的，红绿蓝之间相差120度，反色相差180度
					mixChannels(&hsv, 1, &hue, 1, ch, 1);//将HSV的第一个通道（也就是色调的数复制到HUE中，0索引数组）
					if (trackObject < 0) {
						//此处的构造函数ROI用的是Mat hue的矩阵头，且roi的数据指针指向hue,即共用相同的数据，select为其感兴趣的区域
						Mat roi(hue, selection), maskroi(mask, selection);//mask保存的HSV的最小值
						//calchist()函数第一个参数为输入矩阵序列，第2个参数表示输入的矩阵数目，第三个参数表示将被计算直方图维数通道的列表，第4个参数表示可选的掩码函数
						//第5个参数表述输出直方图，第6个参数表示直方图的维数，第7个参数为每一维直方图数组的大小，第8个参数为每一维直方图bin的边界
						calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//建行roi的0通道计算直方图并通过mask放入hist中，hsize为每一维直方图的大小
					}
				}
			}
		}
	}


	return 0;
}