#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat testimg = imread("test.jpg");//��ȡ
	Mat out_img;//�������Ķ���
	//�����˲�Ч�����˲�����������Ϊ��ͼ�������Ӧ��ģ���������ض�����Ϣ�ڶ�ͼ������е�ĳЩӰ��������ǿ��������ȥ����������ⲻ��֤�ԣ�
	//http://blog.csdn.net/zouxy09/article/details/49080029 �Ĵ����н����˲�����ѧԭ��
	//�˲��˵Ĵ�СӦ���������������Ż�������ĵ�
	//�˲��ˣ����󣩵�����Ԫ�غ͵���1�������ͼ�����Ȳ��䣬����1�����ͼ�������С��1�����ͼ��䰵������������ص���ֵ����0~255�ڿ��ԶϽ�Ҳ��������Ӧ��ѧ������ӳ���0~255�����ڣ�������ڸ���ȡ����ֵ
	//�˲�������Ԫ�غ͵���0�������ұ�Ե
	//���³����˲�����С��ȡ3*3
	//imshow("δ����Ч��", testimg);
	//�˲�
	////1.��ֵ�˲���ƽ��
	//blur(testimg, out_img, Size(3, 3));
	//imshow("��ֵ�˲�Ч��", out_img);
	////2.��ֵ�˲���������Ч����ϸ�ߵ�Ч����
	//Mat midimg = imread("��ֵ�˲�����.jpg");
	//medianBlur(midimg, out_img, 7);//������7Ч������
	//imshow("��ֵ�˲�δ����Ч��", midimg);
	//imshow("��ֵ�˲�Ч��", out_img);
	////3.��˹�˲�,�Ӵ󷽲���˵ĸ�ƽ��Щ��������ʧ����ϸ��
	//GaussianBlur(testimg, out_img, Size(3, 3), 0);
	//imshow("��˹�˲�Ч��", out_img);
	////4.˫���˲�����Ե�����˲�
	//bilateralFilter(testimg, out_img, 3, 2, 2);//���룬��������Ӱ뾶����ɫ�ռ䷽�����ռ䷽��
	//imshow("˫���˲�Ч��", out_img);
	////5.ͨ���˲���,�Զ����˲���
	//Mat kernel = (Mat_<int>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);//����ĺ����˱�Ե�񻯴���
	//filter2D(testimg, out_img, testimg.depth(), kernel);
	//imshow("ͨ���˲���Ч��", out_img);
	////6.�ɷ����˲���,�ص����죬��������1ά���˲���
	//kernel = getGaussianKernel(7, 1.5, CV_32F);//����Ϊ1.5
	//sepFilter2D(testimg,out_img,testimg.depth(),kernel, kernel);//�൱�ڽ�����һ�θ�˹�˲�GaussianBlur(image, result,Size(7, 7), 1.5);
	//imshow("�ɷ����˲�Ч��", out_img);
/**************************************************************************************************************/
	testimg = imread("��̬ѧ�������.jpg");
	imshow("δ����Ч��", testimg);
	Mat ker = getStructuringElement(MORPH_RECT, Size(3, 3));//���һ�����ε���ģ
	//��̬ѧ����  ��������������ָ��������ͼ��Ԫ�أ�Ҳ������Ѱ�Ҽ�ֵΪֵ�����ͼ����ݶ�
	//ͼ��ͺ˽��о��
	//��ֵͼ���Ч��������
	//1.���ͣ�������� ���������˸��ǵ���������ֵ���������ֵ��ֵ���ƶ��ο���
	dilate(testimg, out_img,ker);
	imshow("����Ч��", out_img);
	//2.��ʴ(����ϸ��͹��) ����ԭ��������෴ȥ��Сֵ
	erode(testimg, out_img, ker);
	imshow("��ʴЧ��", out_img);
	//3.ͨ������
		//i.������(�ȸ�ʴ������)����С���塢����ϸ�㴦�������塢ƽ���ϴ�����ı߽��ͬʱ�������Ըı������
	     morphologyEx(testimg, out_img, MORPH_OPEN, ker);
		 imshow("��������", out_img);
		//ii.������(�����ͺ�ʴ)�ų�С�ͺڶ�(��ɫ����)
		 morphologyEx(testimg, out_img, MORPH_CLOSE, ker);
		 imshow("��������", out_img);
		//iii.��̬ѧ�ݶ�(����ͼ-��ʴͼ)���Խ��ſ�ı�Եͻ������,������Ե
		 morphologyEx(testimg, out_img, MORPH_GRADIENT, ker);
		 imshow("��̬ѧ�ݶȽ��", out_img);
		//iiii.��ñ(ԭͼ-��������)������ڽ�����һЩ�İ߿顣��һ��ͼ����д���ı�����ʱ�򣬶�΢С��Ʒ�Ƚ��й��ɵ����������
		 morphologyEx(testimg, out_img, MORPH_TOPHAT, ker);
		 imshow("��ñ������", out_img);
		//iiiii.��ñ(ԭͼ-��������)������ڽ��㰵һЩ�İ߿�
		 morphologyEx(testimg, out_img, MORPH_BLACKHAT, ker);
		 imshow("��ñ������", out_img);
	waitKey(0);
	return 0;
}