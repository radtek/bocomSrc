// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef CLASSIFY_EHD_TEXTURE
#define CLASSIFY_EHD_TEXTURE

#include <vector>
#include "cv.h"
#include "cxcore.h"
#include "ml.h"
#include "Mv_CarnumDetect.h"//���ƿ������ͷ�ļ�
#include "CarLabel.h"

using namespace cv;
using namespace std;

#define LABELNUM 809  //DL��ʶ��ĳ����������
#define TruckDetect   //���㷨���Ƴ����꿪��
#define OLDCARDETECT  //�������Ƴ�����꿪�أ�ǰ�� or β�ƣ�
#define Labelpf

class Carlogo;
//class Carlabel;

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

};

#ifndef OBJECTLABEL
#define OBJECTLABEL
typedef struct OBJ_LABEL
{
	int plabel; //���������

	float fCLP; //���Ŷ�

	OBJ_LABEL()
	{
		plabel = OTHERS;

		fCLP = 0.f;
	}

}object_label;
#endif


#define MV_SAVEIMG_DEBUG

class CarLabel
{

public:
	CarLabel();

	~CarLabel();
	
	/*�����ʼ��*/
	void label_Init();	

	/*�����ͷź���*/
	void label_Destroy();
	

	/*����ͼ���͸�	
	mvSetImageWidthandHeight������ͼ���͸ߣ�����mvGetClassifyEHDTexture�������imageDataΪchar*ʱʹ��
	int nWidth�������ͼ��Ŀ�
	int nHeight�������ͼ��ĸ�
	*/
	void mvSetImageWidthandHeight( int nWidth, int nHeight );

	/*DL����ʶ��������������ʶ����ýӿڣ�
	IplImage *img�������ͼ������
	carnum_context *vehicle_Info������ĳ�����Ϣ������������NULL��
	CvRect *rtRoi������ĳ�����������������NULL��
	object_label *objLabel������ĳ������
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	int mvDLCardCarLabel( IplImage *img, carnum_context *vehicle_Info, CvRect *rtRoi, 
		object_label *objLabel, int isDayByTime=1);
	
	/*DL����ʶ����������춷��x86ϵͳ�ã�
	IplImage *img�������ͼ������
	carnum_context *vehicle_Info������ĳ�����Ϣ������������NULL��
	CvRect *rtRoi���������Ƴ���������ӿڣ�����������NULL��
	vector<Target> vTarget������ĳ�������
	object_label *objLabel������ĳ������
	int isDayBytime��ʹ��Ĭ��ֵ1�����죩
	*/
	/*int mvDLCardCarLabel( IplImage *img, carnum_context *vehicle_Info, CvRect *rtRoi, 
		vector<Target> vTarget, object_label *objLabel, int isDayByTime=1);

	vector<Target> mvCarDetection(IplImage *img);

	CvRect mvCarLocation(IplImage *img, vector<Target> CarIn, CvRect vPlate);
*/
	bool mvIntersect(const CvRect rt1, const CvRect rt2, float *fThresh = NULL);


	/*
	GetVersion����ð汾��	
	���أ�static char Version[] = { "color Recognition Version x.x.x.x" " "  __DATE__ " " __TIME__ };
	*/
	static char* GetVersion();

	//����ģ�ͳ�ʼ��·��
	void mvSetPath(char* strPath);

	IplImage* mvCreateROI(IplImage *src, CvRect Brand, CvRect &m_RectROI, float fsize = 200);

	/*��ͼ�����ղ�ͬ������������ޣ�
	���룺
	IplImage *img��ԭʼͼ��
	IplImage *psubimage���ֲ�ͼ�񣨳�����
	carnum_context *vehicle_Info������ĳ�����Ϣ������������NULL��
	char path[512]����ͼ·��
	int nsort����ͼ����
	CvRect rtV���ֲ�ͼ����ԭʼͼ���е�λ�ã�������
	int nTh���������ޣ�ÿ��1000��
	*/
	void mvSaveImage( IplImage *img, IplImage *psubimage,carnum_context *vehicle_Info, char path[512], int nsort, CvRect rtV, int nTh = 10000 );

	//�����б��������
	void TruckOutStyleput( int classfication, int &nTruckDetect);

	//������������ϸ��
	//int LabelOutput_sub(int classfication);

#ifdef TruckDetect
	//����truck�����
	int TruckOutput(int classfication);	
	int LabelOutput_sub(int classfication);
	int LabelOutput_bsub(int classfication);
#endif
	

protected:	


private:
	char buffer_path[512];
	int label[LABELNUM];	
private:

	//���Ƴ�ʼ��
	int first;
	int m_nWidht;
	int m_nHeight;
	IplImage *m_oriImg;

#ifdef TruckDetect
	int n;
	IplImage* Original;
	HOGDescriptor *hogT;
	int nImgNumT;
	int dimT;
	////��������nImgNum�������������������� WIDTH * HEIGHT������������������ͼ���С  
	int PCAdiT;
	CvSVM svmT;
	CvMat* pMeanT;
	CvMat* pEigVecsT;
#ifdef OLDCARDETECT
	//ǰ��ģ�ͼ���
	HOGDescriptor *hog;
	int nImgNum;
	int dim;
	////��������nImgNum�������������������� WIDTH * HEIGHT������������������ͼ���С  
	int PCAdi;
	CvSVM svm;
	CvMat* pMean;
	CvMat* pEigVecs;

	//β��ģ�ͼ���
	HOGDescriptor *hogB;
	int nImgNumB;
	int dimB;
	////��������nImgNum�������������������� WIDTH * HEIGHT������������������ͼ���С  
	int PCAdiB;
	CvSVM svmB;
	CvMat* pMeanB;
	CvMat* pEigVecsB;
#endif
#endif

	
	//DLL
	Carlogo *net;

	
};
#endif
