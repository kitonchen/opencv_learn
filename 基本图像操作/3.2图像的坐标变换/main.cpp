#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
// ����任�Ļ��������Ǽ���һ��ͼ���з������ص㵽����������ص�ľ��룬Ҳ���ǵ������ص����̾��롣
int main()
{
	int distanceMod;
	Mat readimg;
	Mat tempimg;
	Mat outimg;
	Mat oneimg, twoimg, threeimg;
	readimg =imread("����.jpg");//��ȡͼ��
	cvtColor(readimg,tempimg, CV_BGR2GRAY);//ת�Ҷ�ͼ
    threshold(tempimg, tempimg,200,255,CV_THRESH_OTSU);//����Ӧ��ֵ��
	
	   //��һ������,imshow�ķ�Χ������0��255֮�䣬���ھ���任������ֵ�ı仯����ں�С��һ�������ڣ�һ�㲻����10
		//opencv�е�imshow��ʾ�����ݸ�ʽ��float��char����һ��֮�����ֵΪ32λ�����ͣ�ʹ�����ؼ���ݶȱ仯��������
		//����仯��Ч���������
		while (1)
		{
			system("cls");
			cout << "1.ŷ����¾���.2.���о��� 3.���̾���" << endl;
			cout << "���������ģʽ��";
			cin >> distanceMod;
			switch (distanceMod)
			{		//���빫ʽ������ŷ����þ��룬ģ���С3��3
			case 1:distanceTransform(tempimg, oneimg, DIST_L2, 3);
				   normalize(oneimg, oneimg,1.0,0.0,NORM_MINMAX);//��һ������
				   imshow("����Ӧ��ֵ���", tempimg);
				   imshow("����任���", oneimg);
				cout << "ŷ����þ���" << endl; 
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//�����پ��루���о��룩|x1-x2|+|y1-y2|
			case 2:distanceTransform(tempimg, twoimg, DIST_L1, 3);
				normalize(twoimg, twoimg, 1.0, 0.0, NORM_MINMAX);
				imshow("����Ӧ��ֵ���", tempimg);
				imshow("����任���", twoimg);
				cout << "���о������" << endl; 
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//�б�ѩ����루���̾��룩
			case 3:distanceTransform(tempimg, threeimg, DIST_C, 3);
				normalize(threeimg, threeimg, 1.0, 0.0, NORM_MINMAX);
				imshow("����Ӧ��ֵ���", tempimg);
				imshow("����任���", threeimg);
				cout << "���̾���" << endl;
				if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
				}
				//��������
			default:
				break;
			}
			
		}
		
	return 0;
}