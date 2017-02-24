#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/imgproc/threshold/threshold.html 
//阈值化即使设定一个值，通过比较每个像素和该值的大小来进行剔除，通常用来分割东西
//教程说阈值化的类型有多种类型不一一叙述
Mat input,temp, out;
const short max_type = 5;
const short max_value = 255;
int Ttype;

static double getThreshVal_Otsu_8u(const Mat& _src)//从源码中拉取得计算自适应阈值算法
{
	Size size = _src.size();
	int step = (int)_src.step;
	if (_src.isContinuous())
	{
		size.width *= size.height;
		size.height = 1;
		step = size.width;
	}

#if IPP_VERSION_X100 >= 801 && !defined(HAVE_IPP_ICV_ONLY)
	CV_IPP_CHECK()
	{
		IppiSize srcSize = { size.width, size.height };
		Ipp8u thresh;
		CV_SUPPRESS_DEPRECATED_START
			IppStatus ok = ippiComputeThreshold_Otsu_8u_C1R(_src.ptr(), step, srcSize, &thresh);
		CV_SUPPRESS_DEPRECATED_END
			if (ok >= 0)
			{
				CV_IMPL_ADD(CV_IMPL_IPP);
				return thresh;
			}
		setIppErrorStatus();
	}
#endif

	const int N = 256;
	int i, j, h[N] = { 0 };
	for (i = 0; i < size.height; i++)
	{
		const uchar* src = _src.ptr() + step*i;
		j = 0;
#if CV_ENABLE_UNROLLED
		for (; j <= size.width - 4; j += 4)
		{
			int v0 = src[j], v1 = src[j + 1];
			h[v0]++; h[v1]++;
			v0 = src[j + 2]; v1 = src[j + 3];
			h[v0]++; h[v1]++;
		}
#endif
		for (; j < size.width; j++)
			h[src[j]]++;
	}

	double mu = 0, scale = 1. / (size.width*size.height);
	for (i = 0; i < N; i++)
		mu += i*(double)h[i];

	mu *= scale;
	double mu1 = 0, q1 = 0;
	double max_sigma = 0, max_val = 0;

	for (i = 0; i < N; i++)
	{
		double p_i, q2, mu2, sigma;

		p_i = h[i] * scale;
		mu1 *= q1;
		q1 += p_i;
		q2 = 1. - q1;

		if (std::min(q1, q2) < FLT_EPSILON || std::max(q1, q2) > 1. - FLT_EPSILON)
			continue;

		mu1 = (mu1 + i*p_i) / q1;
		mu2 = (mu - q1*mu1) / q2;
		sigma = q1*q2*(mu1 - mu2)*(mu1 - mu2);
		if (sigma > max_sigma)
		{
			max_sigma = sigma;
			max_val = i;
		}
	}

	return max_val;
}

void set_type(int type, void *)//设置类型
{
	system("cls");//清楚控制台输出的信息
	int Ovalue;
	Ttype = type;
	switch (type)
	{
	case 0:cout << "目前该类型为二值阈值化" << endl; break;
	case 1:cout << "目前该类型为反向二值阈值化" << endl; break;
	case 2:cout << "目前该类型为截断阈值化" << endl; break;
	case 3:cout << "目前该类型为超过阈值被置0" << endl; break;
	case 4:cout << "目前该类型为低于阈值被置0" << endl; break;
	case 5:cout << "目前该类型为自适应阈值" << endl; 
		Ovalue = getThreshVal_Otsu_8u(out);
		setTrackbarPos("阈值", "阈值化测试", Ovalue);
		cout << "自适应阈值结果：" << Ovalue << endl;
		threshold(out, temp, Ovalue, 255, CV_THRESH_BINARY); 
		imshow("阈值化测试", temp);break;
		/*这里输出一下信息*/
		//可以注释掉上面值调用下面的东西
		//threshold(out, temp, value, 255, CV_THRESH_OTSU);//调用自适应阈值，输入的阈值会无效

	default:
		break;
	}
}

void set_value(int value, void* img)//设置阈值并显示
{
	if (Ttype ==5){//不进行操作
		
	}else{
		threshold(out, temp, value, 255, Ttype);//非自适应阈值
	}
	
	imshow("阈值化测试",temp);
}

int main()
{
	input = imread("测试.jpg");
	namedWindow("阈值化测试");
	cvtColor(input, out,CV_BGR2GRAY);//将原图转成灰度图
	createTrackbar("类型", "阈值化测试",0, max_type,set_type);//创建滚动条
	createTrackbar("阈值", "阈值化测试",0, max_value,set_value);
	set_type(0,0);//调用回调函数
	set_value(180, 0);
	imshow("原图", input);	
	waitKey(0);
	return 0;
}