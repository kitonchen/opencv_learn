#include<iostream>
#include"Findhand.h"
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	FindHand test;//ʵ����һ��Ѱ���ֲ���������
	Scalar H_hsv, L_hsv;
	bool flag = true;
	L_hsv =Scalar(0,26,20);
	H_hsv = Scalar(50,200,200);

	while(1){

						
			try {            
					test.FilterImage();//�˲�
					test.HsvHandle(H_hsv,L_hsv);//��ɫ�ռ�ת�������Ҷȷֲ�����
					test.ShapeManage();
					//test.DetermineImage();//�жϴ���
					waitKey(30);//�ӳ�30����
			}catch(int){
				cout << "��ʼ������ʧ��" << endl;
				return -1;
			 }
	}
	return 0;
}