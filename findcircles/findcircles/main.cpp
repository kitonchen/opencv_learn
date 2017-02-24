#include<iostream>
#include<time.h>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	clock_t stime, etime;
	//VideoCapture cap("��Դ����.avi");//����Ƶ
	VideoCapture cap("����.avi");//����Ƶ
	Mat in_img;//�洢֡
	Mat two_img;
	int		findcount = 0;//������ȷʶ�������֡��
	double avgtime=0;
	vector<cv::Vec3f> circles;//Բ����
	namedWindow("����ͷ");//��������
	if (cap.isOpened())//�ж�����ͷ�Ƿ��
	{
		cout << "����ͷ�ɹ��򿪣���ʼʶ��" << endl;
		int framecount = cap.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ֡��
		bool learnflag = false;
		Mat Roitrack;
		while (framecount)//ѭ����ȡ֡����
		{

			cap >> in_img;//��ȡͼ�����е�һ֡
			two_img = in_img;
			stime = clock();
			GaussianBlur(in_img, in_img, Size(5,5), 2,2);//��˹ƽ��ȥ��
			cvtColor(in_img, in_img, COLOR_BGR2GRAY);//ת���ɻҶȣ��ڰ�			
			HoughCircles(in_img,circles, CV_HOUGH_GRADIENT, 2,100,150, 100, 50,200);//����ת����Բ����
			etime = clock();
				for (size_t i = 0; i < circles.size(); i++)//����Բ
				{					
					findcount++;
					Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
					int radius = cvRound(circles[i][2]);
					circle(two_img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
					circle(two_img, center, radius, Scalar(0, 255, 0), 3, 8, 0);
					cout << "Բ������:(" << center.x << "," << center.y << ")" << ",�뾶:" << radius << endl;
					cout << "��ʱ:" << (double)(etime - stime) / CLOCKS_PER_SEC << "��" << endl;
					avgtime += (double)(etime - stime) / CLOCKS_PER_SEC;
				}
				imshow("����ͷ", two_img);//��ʾ�������			
			    cv::waitKey(30);//��ʱ
				framecount--;
		}
		cout << "ʶ����" << (findcount / (float)cap.get(CV_CAP_PROP_FRAME_COUNT)) * 100 << "%" << endl;
		cout << "ƽ��֡ʶ��ɹ���ʱ:" << avgtime / findcount << "��" << endl;
	}
	cv::waitKey(0);
	return 0;
}
