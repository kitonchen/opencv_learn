#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
// ֱ�ߣ�Բ�μ��ԭ��������òο�ǳī����Ľ̳� http://blog.csdn.net/poem_qianmo/article/details/26977557
//����任 �ο� http://blog.csdn.net/poem_qianmo/article/details/33320997


int main()
{
	char choose;//ѡ�����
	Mat Circle, Line, Shift;//���ͼƬ	
	Mat show;//��ʾ
	vector<Vec4i> lines;//���ֱ�߲���������,�����յ��X,Y��������
	vector<Vec3f> circles;//���Բ������X,Y�Ͱ뾶
	//����任
	Point2f orignTriangle[3];//�����������������
	Point2f targetTriangle[3];
	Point center;
	double angle;//˳ʱ����ת
	double scale;//����ϵ��
	Mat rofMat(2, 3, CV_32FC1);//��ת����
	Mat warpMat(2, 3, CV_32FC1);//�任����
	
	while (true)
	{
		system("cls");
		cout << "��1����ʾԲ�μ��\n��2:��ʾֱ�߼��\n��3:��ʾ����任\n";
		cin >> choose;
		switch (choose)
		{
		case '1':
				Circle = imread("Բ�μ��.jpg");//��ȡͼƬ	
				cvtColor(Circle, show, CV_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ
				GaussianBlur(show, show, Size(5,5),1.5,1.5);//��˹�˲�
				HoughCircles(show, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 100, 25, 100);//�����ݶȣ��ۼ���/ԭͼ�ֱ��ʵ���1��Բ����С����50����Ե�����ֵ100���ۼ�����ֵ100,��С�뾶30�����뾶100
			for (size_t i = 0; i < circles.size(); i++) {
				Point center(round(circles[i][0]), round(circles[i][1]));//��ȡԲ������
				int radius = round(circles[i][2]);//��ȡ�뾶
				circle(Circle, center, 2, Scalar(255, 255, 255), 2);//��Բ��
				circle(Circle, center, radius, Scalar(255, 255, 255), 2);//��Բ����
				cout << "Բ������:(" << center.x << "," << center.y << "),�뾶:" << radius << endl;
			}
				imshow("Բ�μ����", Circle);
					if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
					}
		case '2':Line = imread("ֱ�߼��.jpg");
				cvtColor(Line,show, CV_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ
				Canny(show,show, 125,250);//����Ե���
				imshow("��Ե", show);
				//��ͨ����ֱ�߱任Ч���Ƚ����������ø��ʻ���任
				HoughLinesP(show, lines, 1, CV_PI / 180,50,120,10);//���򾫶�1���ǶȾ��Ȧ�/180,�ۼƵ���Ŀ��ֵ50�������ʾ����120��������֮������������������10
				show = Scalar(0, 0, 0);
			for (size_t i = 0; i < lines.size(); i++) {	
				Point x1, x2;//�������ֱ�߼���������ص�
				x1.x = lines[i][0]; x1.y = lines[i][1];//������
				x2.x = lines[i][2]; x2.y = lines[i][3];//����յ�
				line(show,x1,x2,Scalar(255, 255, 255));
				line(Line,x1,x2,Scalar(255, 255, 255),1,CV_AA);
			}
				imshow("ֱ�߼�����Ҷ���ʾ", show);
				imshow("ֱ�߼������ɫ��ʾ", Line);
					if (waitKey(0) == 13) {
				destroyAllWindows();
				break;
				}		
		case '3':Shift = imread("����任.jpg");
				 show = Mat::zeros(Shift.size(), Shift.type());//��Ŀ��ͼ�����ó�ȫ�ڣ���ʽ������ͼ�����
				 //���÷��������εĵ�
				 orignTriangle[0] = Point2f(0, 0);				
				 orignTriangle[1] = Point2f(static_cast<float>(Shift.cols - 1),0);//static_castΪC++��ǿ��ת�����
				 orignTriangle[2] = Point2f(0,static_cast<float>(Shift.rows - 1));
				 targetTriangle[0] = Point2f(static_cast<float>(Shift.cols*0.0), static_cast<float>(Shift.rows*0.33));
				 targetTriangle[1] = Point2f(static_cast<float>(Shift.cols*0.65), static_cast<float>(Shift.rows*0.35));
				 targetTriangle[2] = Point2f(static_cast<float>(Shift.cols*0.15), static_cast<float>(Shift.rows*0.6));
				 //������任����
				 warpMat = getAffineTransform(orignTriangle, targetTriangle);
				 //
				 warpAffine(Shift, show, warpMat, show.size());
				 imshow("ԭͼ", Shift);
				 imshow("����任��Ľ��", show);
				 center = Point(show.cols / 2, show.rows / 2);
				 angle = -30;//˳ʱ����ת
				 scale = 0.6;//����ϵ��
				 rofMat = getRotationMatrix2D(center, angle, scale);//������ת����
				 warpAffine(show, show, rofMat, show.size());
				 imshow("����任����ת��Ľ��", show);
				 if (waitKey(0) == 13) {
					destroyAllWindows();
					break;
					}
		default:
			break;
		}
	}

	return 0;
}