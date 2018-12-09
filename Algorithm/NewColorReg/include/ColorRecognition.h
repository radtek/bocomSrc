// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef COLORRECOGNITION_H
#define COLORRECOGNITION_H
#include <vector>
#include "cv.h"
#include "cxcore.h"
#include "ml.h"

using namespace cv;
using namespace std;

class Carcolor;
class MvMulObjDetect;

struct Target;
struct CARNUM_CONTEXT;

#define MV_SAVEIMG_DEBUG
//#define MV_CARDETECTION //�������

#ifndef OBJECTCOLOR
#define OBJECTCOLOR
typedef struct OBJECT_COLOR
{
	int  nColor1;       //��ɫ1
	int  nColor2;	    //��ɫ2
	int  nColor3;       //��ɫ3

	int  nWeight1;    //��ɫȨ��1
	int  nWeight2;    //��ɫȨ��2
	int  nWeight3;    //��ɫȨ��3

	float fCLP1;       //��ɫ���Ŷ�
	float fCLP2;       //��ɫ���Ŷ�
	float fCLP3;       //��ɫ���Ŷ�

	OBJECT_COLOR()
	{
		nColor1 = 11;
		nColor2 = 11;
		nColor3 = 11;
		nWeight1 = 0;
		nWeight2 = 0;
		nWeight3 = 0;
		fCLP1 = 0.0;
		fCLP2 = 0.0;
		fCLP3 = 0.0;
	}
} object_color;
#endif

#ifndef OBJECTCAR
#define OBJECTCAR
typedef struct CAR_INFO   //�������ݽṹ��
{
	CvRect  plate_rect; //����λ��,�����ԭͼ
	CvRect  car_rect; //����λ��,�����ԭͼ
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
		memset(carnum,0,sizeof(char)*7);
	}
} car_info;
#endif

////������ɫ
//#ifndef __COLORTYPE
//#define __COLORTYPE
//enum MVCOLOR
//{
//	WHITE, //= 0 by default
//	SILVER,
//	BLACK,
//	RED, //3
//	PURPLE,
//	BLUE,
//	YELLOW,
//	GREEN,
//	BROWN, //��ɫ
//	PINK, //�ۺ�ɫ
//	GRAY,  //10
//	UNKNOWN
//};
//#endif

class ColorRecognisize
{

public:
	ColorRecognisize();

	~ColorRecognisize();
	
	/*��ɫ��ʼ��*/
	int color_Init( char *strPath = NULL );	

	/*��ɫ�ͷź���*/
	void color_Destroy();

	/*����ͼ���͸�	
	mvSetImageWidthandHeight������ͼ���͸ߣ�����mvGetClassifyEHDTexture�������imageDataΪchar*ʱʹ��
	int nWidth�������ͼ��Ŀ�
	int nHeight�������ͼ��ĸ�
	*/
	void mvSetImageWidthandHeight( int nWidth, int nHeight );

	/*DL��ɫʶ��������������ʶ����ýӿڣ�
	IplImage *img�������ͼ������
	CARNUM_CONTEXT *vehicle_Info������ĳ�����Ϣ������������NULL��
	CvRect *rtRoi������ĳ�����������������NULL��
	object_color *objColor���������ɫ���
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	int mvDLCardCarColor( IplImage *img, CARNUM_CONTEXT *vehicle_Info, CvRect *rtRoi, 
		object_color *objColor, int isDayByTime=1);
	
	/*DL��ɫʶ����������춷��x86ϵͳ�ã�
	IplImage *img�������ͼ������
	CARNUM_CONTEXT *vehicle_Info������ĳ�����Ϣ������������NULL��
	CvRect *rtRoi���������Ƴ���������ӿڣ�����������NULL��
	vector<Target> vTarget������ĳ�������
	object_color *objColor���������ɫ���
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	int mvDLCardCarColor( IplImage *img, CARNUM_CONTEXT *vehicle_Info, CvRect *rtRoi, 
		vector<Target> vTarget, object_color *objColor, int isDayByTime=1);

	/*DL��ɫʶ��������������ʶ����ýӿ�,�Զ��峵���ṹ�壩
	IplImage *img�������ͼ������
	CAR_INFO *car_Info������ĳ�����Ϣ
	object_color *objColor���������ɫ���
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	int mvDLCardCarColor( IplImage *img, CAR_INFO *carInfo, object_color *objColor, int isDayByTime=1);

	/*DL��ɫʶ����������춷��x86ϵͳ��,�Զ��峵���ṹ�壩
	IplImage *img�������ͼ������
	CAR_INFO *car_Info������ĳ�����Ϣ
	vector<Target> vTarget������ĳ�������
	object_color *objColor���������ɫ���
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	int mvDLCardCarColor( IplImage *img, CAR_INFO *carInfo, 
		vector<Target> vTarget, object_color *objColor, int isDayByTime=1);

	vector<Target> mvCarDetection(IplImage *img);

	CvRect mvCarLocation(IplImage *img, vector<Target> CarIn, CvRect vPlate);

	bool mvIntersect(const CvRect rt1, const CvRect rt2, float *fThresh = NULL);

	/*
	GetVersion����ð汾��	
	���أ�static char Version[] = { "color Recognition Version x.x.x.x" " "  __DATE__ " " __TIME__ };
	*/
	static char* GetVersion();

	//����ģ�ͳ�ʼ��·��
	void mvSetPath(char* strPath);

	//��ʾģ�Ͱ汾
	int mvGet_Vision( char* strPath  );

	IplImage* mvCreateROI(IplImage *src, CvRect Brand, CvRect &m_RectROI, float fsize = 200);

	/*��ͼ�����ղ�ͬ������������ޣ�
	���룺
	IplImage *img��ԭʼͼ��
	IplImage *psubimage���ֲ�ͼ�񣨳�����
	char path[512]����ͼ·��
	int nsort����ͼ����
	CvRect rtV���ֲ�ͼ����ԭʼͼ���е�λ�ã�������
	int nTh���������ޣ�ÿ��1000��
	*/
	void mvSaveImage( IplImage *img, IplImage *psubimage, char path[512], object_color *objColor, CvRect rtV, int nTh = 1000 );

protected:	


private:
	char buffer_path[512];

			
private:

	//���Ƴ�ʼ��
	int first;
	int m_nWidht;
	int m_nHeight;
	IplImage *m_oriImg;

//DLL
	Carcolor *net;
#ifdef MV_CARDETECTION
	MvMulObjDetect *carD;
#endif
};

#endif
