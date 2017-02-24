#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;

Rect box;//���ζ���
bool drawing_box;//��¼�Ƿ��ڻ����ζ���

void onmouse(int event, int x, int y, int flag, void *img)//����¼��ص��������������ִ�е�����Ӧ�ڴ�
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://�����������¼�
			drawing_box = true;//��־�ڻ���
			box = Rect(x, y, 0, 0);//��¼���εĿ�ʼ�ĵ�
			break;
	case CV_EVENT_MOUSEMOVE://����ƶ��¼�
		if (drawing_box){//������һֱ���ţ�������ڻ�����
			box.width = x - box.x;
			box.height = y - box.y;//���³���
		}
			break;
	case CV_EVENT_LBUTTONUP://�������ɿ��¼�
		drawing_box = false;//���ڻ�����
		//�������û����
		if (box.width<0){//�ų���Ϊ����������������ж���Ϊ���Ż����㣬�������ƶ�ʱÿ�θ��¶�Ҫ���㳤��ľ���ֵ
			box.x = box.x + box.width;//����ԭ��λ�ã�ʹ֮ʼ�շ������Ͻ�Ϊԭ��
			box.width = -1 * box.width;//���ȡ��
		}
		if (box.height<0){//ͬ��
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
	Mat img = imread("beach.jpg");//��ȡͼ��
	Mat temp;
	namedWindow("��껭����");//����
	setMouseCallback("��껭����", onmouse,&img);//ע������¼�������껭���򡱴��ڣ���ʹ�ڸô����³�������¼���ִ��onmouse����������,���һ������Ϊ��������ݡ�������ʵû���õ�
	imshow("��껭����", img);
   //img.copyTo(temp);��������������Ӱ��������Ϊ��һ�λ��ľ��β�û�б�����
	while (1)
	{
		//img.copyTo(temp);//��仰����if�⣬ע�͵�if�����Ǿ�.����û�����⣬��ÿ�α���ѭ��ʱ����ִ��һ��ͼ�����ݵĸ��ƴ��ݲ��������ǲ���Ҫ���ڸ��ٵ�PC��û��ϵ������Ƕ��ʽϵͳ��ʱ�����ܻ���ΪӲ�����ܶ��޷�����ʵʱ������˲���������￩
		//ֻҪ���ٴΰ��������������¼�,�������ʾ��һֱ��if�������汻���κ����������tempͼ������ٴΰ����������ͽ���if�����ϸ��±������κ����������temp����Ϊ�����ٶȿ����Կ����������εĹ�����������û�п��٣���Ϊÿ�����»�������û�п�Ļ����ϻ����µĿ���Ϊ���۵Ĳ�Ӱ�ӳ����Բ�������Ӱ����ÿ�θ��¾��ο�Ĵ������������±�img��û�п򣩵����ݸ��ǵ�temp����img.data==temp.data����ͨ���ص����������˵�Box��¼����������ݡ�
		//���������������򵱻���һ�����κ�����ڵ���һ��������(û���϶�),��drawing_box==true,��ΪBox��¼������������ݼ�������ĳ���Ϊ0����Ϊδ�����϶�,box.width,box.heightΪ0���򻭾��κ���rectangle����������ڶ��������������Խǵ�Ĳ�����������ȵģ����Ծ��εĶԽ�����0���޷��������Σ�������ʾ����û�п��ԭͼ����ʱ��ʾ��temp������Ӧ�Ǻ�img��ȵ�
		if (drawing_box){//���ϸ������ڻ��ľ���
			img.copyTo(temp);//�����������Ǳ�֤��ÿ�θ��¾��ο�����û��ԭͼ�Ļ����ϸ��¾��ο�
			rectangle(temp,Point(box.x, box.y),Point(box.x+box.width,box.y+box.height),Scalar(255,255,255));
			imshow("��껭����",temp);//��ʾ
		}
		 
		if (waitKey(30) == 27) {//����Ƿ��а����˳���
			break;//�˳�����
		}
	}
	
	return 0;
}