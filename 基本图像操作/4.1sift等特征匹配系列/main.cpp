// 4.1sift������ƥ��ϵ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\legacy\legacy.hpp>

using namespace cv;
using namespace std;

void sift_test();//����sift�㷨
void sift_match_test();//����������ƥ��
void surf_test();
void surf_match_test();

int main()
{
	
//	sift_test();
//	sift_match_test();
	//surf_test();
	surf_match_test();
    return 0;
}

void sift_test()
{
	Mat src = imread("boldt.jpg");
	//��������������100������
	SIFT sift(300);
	//������
	vector<KeyPoint> key_point;
	//���������������
	
	//���
	Mat dst;
	//����������������
	sift.detect(src, key_point);
	

	drawKeypoints(src,//����
		key_point,//������ʸ��
		dst,//���ͼ��
		Scalar::all(-1),//����������������ɫ
		//��������Ϊ���Ļ�Բ��Բ�İ뾶��ʾ������Ĵ�С��ֱ�߱�ʾ������ķ���
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("sift_test", dst);
	waitKey(0);
}

void sift_match_test()
{
	Mat src1 = imread("test1.png");
	Mat src2 = imread("test2.png");
	//������
	Mat descriptors1, descriptors2;
	//�ؼ���
	cv::vector<KeyPoint> key_point1, key_point2;	
	SIFT sift(100);
	//����ؼ����������
	sift.detect(src1, key_point1);
	sift.detect(src2, key_point2);

	sift.compute(src1, key_point1, descriptors1);	
	sift.compute(src2, key_point2, descriptors2);

	Mat dst_matches;
	BFMatcher matcher;
	std::vector<DMatch> matches;//ƥ��������
	//ƥ��
	matcher.match(descriptors1, descriptors2, matches);

	nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��  
		matches.begin() + 29,     // ���������  
		matches.end());       // ����λ��  
							  //�޳��������ƥ����  
	matches.erase(matches.begin() + 30, matches.end());

	//����ƥ����
	drawMatches(src1, key_point1,//��һ��ͼ����������
				src2, key_point2,//�ڶ���ͼ
				matches,//ƥ��������
				dst_matches);//ƥ�����ͼ��

	imshow("sift_matches_test", dst_matches);
	waitKey(0);
}

void surf_test()
{//�÷���siftһ����һ��SURF��Ķ��󼴿ɽ������в�����
	SURF surf_handle;
	Mat src1 = imread("test1.png");

	//������,�ؼ���	
	vector<KeyPoint> key_point1;
	//���ؼ���,����������
	surf_handle.detect(src1, key_point1);
	

	Mat dst1;

	drawKeypoints(src1, key_point1, dst1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("sruf_test", dst1);
	waitKey(0);
}

void surf_match_test()
{

	Mat src1 = imread("test1.png");
	Mat src2 = imread("test2.png");
	//������
	Mat descriptors1, descriptors2;
	//�ؼ���
	vector<KeyPoint> key_point1, key_point2;
	SURF surf;
	//����ؼ����������
	surf.detect(src1, key_point1);
	surf.detect(src2, key_point2);

	surf.compute(src1, key_point1, descriptors1);
	surf.compute(src2, key_point2, descriptors2);

	Mat dst_matches;
	BFMatcher matcher;
	std::vector<DMatch> matches;//ƥ��������
								//ƥ��
	matcher.match(descriptors1, descriptors2, matches);

	nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��  
		matches.begin() + 29,     // ���������  
		matches.end());       // ����λ��  
							  //�޳��������ƥ����  
	matches.erase(matches.begin() + 30, matches.end());

	//����ƥ����
	drawMatches(src1, key_point1,//��һ��ͼ����������
		src2, key_point2,//�ڶ���ͼ
		matches,//ƥ��������
		dst_matches);//ƥ�����ͼ��

	imshow("sift_matches_test", dst_matches);
	waitKey(0);
	
}


