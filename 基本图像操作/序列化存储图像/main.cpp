#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

int main()
{ 
	Mat wirteimg = Mat::eye(10, 10, CV_8UC2);//����һ��100*100�ĶԽǾ���
	Mat readimg;
	//imwrite("�ԽǾ���.jpg", img);//����Ϊjpg��ʽ������ʱɾ��ԭ�ļ��ɲ鿴Ч������ȫ��·�����Ա��浽�ض�·��
	//imread()�������Խ��ж�ȡ
	//imwrite����ֻ֧��CV8U���͵����ݣ�ʹ��OpenCV������������Mat��ʱ�򣬳��򲻻ᱨ�������޷����ɽ���ļ���������FileStorage��,������ΪXML/YAML�ļ���һ�ֲ��ñ�����Ա������ݵ��ļ���ʽ��
	FileStorage fw("�ԽǾ���.xml", FileStorage::WRITE);//�����
		fw << "Mat" << wirteimg;//ͨ�������д�ļ�������MAT��ǩ
			fw.release();//�ͷ��ļ�������
	FileStorage fr("�ԽǾ���.xml", FileStorage::READ);//����ȡ
	//��ȡ����ӡXML�ļ�
		fr["Mat"] >> readimg;//ͨ����������ȡ���ݣ���ȡʱҲҪ���ñ�ǩ
			fr.release();//�������������	
	cout << readimg;		
return 0;
}