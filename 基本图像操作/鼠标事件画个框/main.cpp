#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

Rect box;//矩形对象
bool drawing_box;//记录是否在画矩形对象

void onmouse(int event, int x, int y, int flag, void *img)//鼠标事件回调函数，鼠标点击后执行的内容应在此
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下事件
			drawing_box = true;//标志在画框
			box = Rect(x, y, 0, 0);//记录矩形的开始的点
			break;
	case CV_EVENT_MOUSEMOVE://鼠标移动事件
		if (drawing_box){//如果左键一直按着，则表明在画矩形
			box.width = x - box.x;
			box.height = y - box.y;//更新长宽
		}
			break;
	case CV_EVENT_LBUTTONUP://鼠标左键松开事件
		drawing_box = false;//不在画矩形
		//这里好像没作用
		if (box.width<0){//排除宽为负的情况，在这里判断是为了优化计算，不用再移动时每次更新都要计算长宽的绝对值
			box.x = box.x + box.width;//更新原点位置，使之始终符合左上角为原点
			box.width = -1 * box.width;//宽度取正
		}
		if (box.height<0){//同上
			box.y = box.y + box.height;
			box.height = -1 * box.width;
		}	
		break;
	default:
		break;
	}
}
int main()
{
	Mat img = imread("beach.jpg");//读取图像
	Mat temp;
	namedWindow("鼠标画个框");//窗口
	setMouseCallback("鼠标画个框", onmouse,&img);//注册鼠标事件到“鼠标画个框”窗口，即使在该窗口下出现鼠标事件就执行onmouse函数的内容,最后一个参数为传入的数据。这里其实没有用到
	imshow("鼠标画个框", img);
   //img.copyTo(temp);放在这里会出现拖影的现象，因为上一次画的矩形并没有被更新
	while (1)
	{
		//img.copyTo(temp);//这句话放在if外，注释掉if里面那句.程序没有问题，但每次遍历循环时都会执行一次图像数据的复制传递操作，这是不必要。在高速的PC上没关系，但在嵌入式系统中时，可能会因为硬件性能而无法满足实时需求。因此不建议放这里咯
		//只要不再次按下鼠标左键触发事件,则程序显示的一直是if条件里面被矩形函数处理过的temp图像，如果再次按下鼠标左键就进入if，不断更新被画矩形函数处理过的temp，因为处理速度快所以看起来画矩形的过程是连续的没有卡顿，因为每次重新画都是在没有框的基础上画出新的框因为人眼的残影延迟所以不会有拖影现象。每次更新矩形框的传入数据是重新被img（没有框）的数据覆盖的temp（即img.data==temp.data）和通过回调函数更新了的Box记录的坐标点数据。
		//依照上面所述，则当画完一个矩形后，如果在单击一下鼠标左键(没有拖动),则drawing_box==true,因为Box记录到的坐标点数据计算出来的长宽为0（因为未进行拖动,box.width,box.height为0，则画矩形函数rectangle（）所传入第二第三个参数即对角点的参数两个是相等的，所以矩形的对角线是0就无法画出矩形），则显示的是没有框的原图，此时显示的temp的数据应是和img相等的
		if (drawing_box){//不断更新正在画的矩形
			img.copyTo(temp);//这句放在这里是保证了每次更新矩形框都是在没有原图的基础上更新矩形框。
			rectangle(temp,Point(box.x, box.y),Point(box.x+box.width,box.y+box.height),Scalar(255,255,255));
			imshow("鼠标画个框",temp);//显示
		}
		 
		if (waitKey(30) == 27) {//检测是否有按下退出键
			break;//退出程序
		}
	}
	
	return 0;
}