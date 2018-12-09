// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef BRANDSUBSECTION_H
#define BRANDSUBSECTION_H

#include <vector>
#include "cv.h"
#include "cxcore.h"
#include "ml.h"

using namespace cv;
using namespace std;

#define MV_SAVEIMG_DEBUG //�����洢�꿪��

#define LABELNUM 1828  //����ɼ���������

class Carlogo;

struct CARNUM_CONTEXT;

//�������ö��
enum TRUCK_LABEL
{
	LARGEBUS = 1,                //���Ϳͳ�     1
	LARGEVAN,                    //���ͻ���     2
	MEDIUMBUS,                   //���Ϳͳ�     3
	SMALLCAR,					//С�Ϳͳ�		4
	UNKNOW,						//δ֪			5
	MISS,						//δ֪			6
	SMALLVAN,                   //С�ͻ���		7
	SUV,                        //suv           8
	MBC,                        //�����         9
	YVK,                        //��ά��        10
	MPV,                        //MPV          11
	SMALLTRUCK,                //Ƥ��           12

};

#ifndef OBJECTLABEL
#define OBJECTLABEL
typedef struct OBJ_LABEL
{
	int plabel; //�����������

	int plabel_G; //����������

	int plabel_Y;  //������ݱ��

	float fCLP; //���Ŷ�

	float fCLP_G; //���Ŷ�

	OBJ_LABEL()
	{
		plabel = 500000;

		plabel_G = 500000;

		plabel_Y = 500000;

		fCLP = 0.f;

		fCLP_G = 0.f;
	}

}object_label;
#endif

#ifndef OBJECTCAR 
#define OBJECTCAR 
typedef struct CAR_INFO //�������ݽṹ�� 
{ 
	CvRect plate_rect; //����λ��,�����ԭͼ 
	CvRect car_rect; //����λ��,�����ԭͼ 
	int plate_color; //������ɫ��1�� 2�� 3�� 4�� 5������ 
	int carnumrow; //��˫�ƣ�1���� 2˫�� 3������ 
	int nCarNumDirection; //���Ƶķ���(0ǰ�� 1β�� 2δ֪) 
	char carnum[7]; //���ƺ��� 
	CAR_INFO() 
	{ 
		plate_rect = cvRect(0,0,0,0); 
		car_rect = cvRect(0,0,0,0); 
		plate_color = 5; 
		carnumrow = 3; 
		nCarNumDirection = 0; 
	} 
} car_info; 
#endif

class CarLabel
{

public:
	CarLabel();

	~CarLabel();

	/************************************************************************/
	/*�����ʼ��*/
	/************************************************************************/
	int label_Init(char* strPath = NULL);	
	
	/************************************************************************/
	//���������ѯ�����ӿ�
	/************************************************************************/
	int label_subclass(int carnum,string &subclassstr);

	/************************************************************************/
	/*�����ͷź���*/
	/************************************************************************/
	int label_Destroy();

	/************************************************************************
	DL����ʶ��������������ʶ����ýӿڣ�
	IplImage *img�������ͼ������
	carnum_context *vehicle_Info������ĳ�����Ϣ������������NULL��
	CvRect *rtRoi������ĳ�����������������NULL��
	object_label *objLabel������ĳ������
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	/************************************************************************/
	int mvDLCardCarLabel( IplImage *img, CARNUM_CONTEXT *vehicle_Info, CvRect *rtRoi, 
		object_label *objLabel, int isDayByTime=1);
	

	/************************************************************************
	GetVersion����ð汾��	
	���أ�static char Version[] = { "color Recognition Version x.x.x.x" " "  __DATE__ " " __TIME__ };
	/************************************************************************/
	static char* GetVersion();

	/************************************************************************/
	//����ģ�ͳ�ʼ��·��
	/************************************************************************/
	void mvSetPath(char* strPath);

	/************************************************************************
	��ͼ�����ղ�ͬ������������ޣ�
	���룺
	IplImage *img��ԭʼͼ��
	IplImage *psubimage���ֲ�ͼ�񣨳�����
	carnum_context *vehicle_Info������ĳ�����Ϣ������������NULL��
	char path[512]����ͼ·��
	int nsort����ͼ����
	CvRect rtV���ֲ�ͼ����ԭʼͼ���е�λ�ã�������
	int nTh���������ޣ�ÿ��1000��
	/************************************************************************/
	void mvSaveImage( IplImage *img, IplImage *psubimage,CARNUM_CONTEXT *vehicle_Info, char path[512], int nsort, CvRect rtV, int nTh = 10000 );


	/************************************************************************/
	//�����б��������
	/************************************************************************/
	void TruckOutStyleput( int classfication, CARNUM_CONTEXT *vehicle_Info, int &nTruckDetect);
	


protected:	


private:
	char buffer_path[512]; 
	int label[LABELNUM];            //ǰ���������ӳ���
	vector<string>vSubclass;     //��������������
private:

	//���Ƴ�ʼ��
	int first;
	int m_nWidht;
	int m_nHeight;
	IplImage *m_oriImg;
	
	Carlogo *net; //�����ʼ��
	
};

#endif