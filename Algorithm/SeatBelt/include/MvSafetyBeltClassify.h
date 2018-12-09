/* ��Ȩ���� 2009 �Ϻ�����������Ϣ�������޹�˾
* Copyright (c) 2009��Shanghai Bocom Intelligent Information Technologies Ltd
* �������ܹ�˾����
* Bocom Intelligent Confidential Proprietary
* �ļ����ƣ�MvSafetyBeltClassify.h
* ժҪ: ��Ҫ�������ļ�������
* �汾: V1.9
* ����: �ᆴ�������� 
* �������: 2014��12��01��
*/

#ifndef MVSAFETYBELTCLASSIFY__H__
#define MVSAFETYBELTCLASSIFY__H__

#include <cv.h>
#include <highgui.h>
#include "ml.h"
#include <algorithm>
#include <vector>
#include "cvaux.h" 
#include "cxcore.h" 

//--------------���ƺ�Ķ���------------ 
//#define MV_SHOWIMG //
#define MV_SAVEIMG_DEBUG
//#define MV_PHONE_TWICE
//#define MV_MULTTHREAD
//����ص��¾䣬��û���κ�debug��¼
//#define  DEBUG_TYPE_ON

using namespace std;
using namespace cv;

struct CARNUM_CONTEXT;
struct Target;

class MvImgEnhance_HandOver;
class Seatbelt;
class Phone;
class MvDriverDetect;

#ifndef OBJECTFACERT
#define OBJECTFACERT
typedef struct stFaceRt
{
	cv::Rect VehicleRect;		//��ʻԱ����
	double Weight;			//��ʻԱ���Ŷ�
	int label_type;			//��ȫ���ж�
	float fCLP;				//��ȫ�����Ŷ�
	float fblur;			//ͼ��ģ����
	int nPhone_type;		//�ֻ��ж�
	float fPhone_CLP;		//�ֻ����Ŷ�
	int nSunVisor_type;		//�������ж�
	float fSunVisor_CLP;	//���������Ŷ�
	bool bguess;			

	stFaceRt()
	{
		VehicleRect = cv::Rect(0,0,0,0);
		Weight = 0.0;
		label_type = 0;
		fCLP = 0.0;
		fblur = 0.0;
		nPhone_type = 0;
		fPhone_CLP = 0.0;
		nSunVisor_type = 0;
		fSunVisor_CLP = 0.0;
		bguess = false;
	}
}FaceRt;
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

class MvSafetyBeltClassify  
{
public:
	
	MvSafetyBeltClassify();
	virtual ~MvSafetyBeltClassify();
	
	//=================================================================
	//��  ��: ��ȫ��ģ���ʼ��
	//��  ��: strPathΪģ��·��
	//����ֵ: ������
	//=================================================================
	int SafetyBelt_Init( char *strPath = NULL );//��ʼ��




	//=================================================================
	//��  ��: ��ȫ��ģ������������������ȫ����⣬���ֻ��������壩
	//��  ��: pImage��������Ҫ�����ͼƬ
	//        vehicle_info:���복����Ϣ
	//        isDayByTime���������Ϊ1,ҹ��Ϊ0��Ĭ������1
	//        vecP�����������Ա����
	//        ncartype�����복����Ϣ
	//        bIsSafetyBelt������ʻ��ȫ�����ģ�鿪��
	//        bIsAideBelt������ʻ��ȫ�����ģ�鿪��  
	//        bIsPhone�����ֻ����ģ�鿪��
	//        bIsSunVisor����������ģ�鿪��
	//����ֵ: �Ƿ�ϵ��ȫ�����Ƿ���ֻ����Ƿ���������
	//=================================================================
	int mvSafetyBelt(IplImage *pImage,const CARNUM_CONTEXT *vehicle_info,int isDayByTime
		,vector<FaceRt> &vecP, bool bIsSafetyBelt, int ncartype, bool bIsAideBelt = false,
		bool bIsPhone = false, bool bIsSunVisor = false);
	
	
	//=================================================================
	//��  ��: ��ȫ��ģ��汾�Ż�ȡ
	//��  ��: ��
	//����ֵ: ������
	//=================================================================
	static char* GetVersion();//��ȫ��ģ��汾


	//=================================================================
	//��  ��: ��������������
	//��  ��: pImage������ͼƬ
	//        rtF�������ʻԱ����
	//        fCLP����������������Ŷ�
	//        nIsAideSunVisor���������⿪�أ�0Ϊ����ʻ��1Ϊ����ʻ
	//����ֵ: ������
	//=================================================================
	int mvFindSunVisor(IplImage *pImage, CvRect rtF, float *fCLP, int nIsAideSunVisor);//������


	//=================================================================
	//��  ��: ���ֻ����������
	//��  ��: pImage������ͼƬ
	//        rtF�������ʻԱ����
	//        fCLP����������������Ŷ�
	//        nIsAidePhone�����ֻ���⿪�أ�0Ϊ������ݴ��ֻ���1Ϊ��⸱��ʻ���ֻ�
	//����ֵ: ������
	//=================================================================
	int mvPhoneDL(IplImage *pImage, CvRect rtF, float *fCLP, int nIsAidePhone);//���ֻ�


	//=================================================================
	//��  ��: ��ȫ�����������
	//��  ��: pImage������ͼƬ
	//        rtF�������ʻԱ����
	//        fACLP�������ȫ��������Ŷ�
	//        nIsAideBelt����ȫ����⿪�أ�0Ϊ������ݰ�ȫ����1Ϊ��⸱��ʻ��ȫ��
	//        *fblur��ͼ��ģ����
	//����ֵ: ������
	//=================================================================
	int mvIsSafetyBelt(IplImage *pImage, CvRect rtF, int nIsAideBelt, float *fACLP, //��ȫ��
		float *fblur, int ncartype);


	//=================================================================
	//��  ��: ��ȫ��ģ���ͷź���
	//��  ��: ��
	//����ֵ: ������
	//=================================================================
	void SafetyBelt_Destroy();//�ͷ�



	//=================================================================
	//��  ��: ��������ͼ����Ȥ������
	//��  ��: src������ͼƬ
	//        Brand:����λ��
	//        m_RectROI�������ROI����
	//        ncartype������ĳ�����Ϣ
	//����ֵ: ROI����
	//=================================================================
	IplImage* mvCreateROI(IplImage *src, CvRect Brand, CvRect &m_RectROI, int ncartype);


	MvDriverDetect *PeopleDet;

private:

	//=================================================================
	//��  ��: ����ͼ��ģ���Ⱥ���
	//��  ��: pbeltImage������ͼƬ        
	//����ֵ: ģ����
	//=================================================================
	float mvblur(IplImage* pbeltImage);//ͼ��ģ���ȼ���


	//=================================================================
	//��  ��: �ж�����ͼƬ������ʻ���Ǹ���ʻ
	//��  ��: src������ͼƬ
	//        nmul:���������Ĭ��Ϊ1
	//����ֵ: ģ����
	//=================================================================
	IplImage* Transpolt(IplImage *src, float nmul);//�ж�������ʻ


	//=================================================================
	//��  ��: ��������ͼ����Ȥ������
	//��  ��: pImage������ͼƬ
	//        rt������λ��
	//        bAllGuess������ļ�ʻԱ��������Ƿ�ȫ�ǲµĽ��
	//        ncartype������ĳ�����Ϣ
	//����ֵ: ROI����
	//=================================================================
	vector<FaceRt> mvHeadDetect(IplImage *pImage, CvRect rt, int ncartype,bool& bAllGuess);//��ʻԱ���

private:
	char buffer_path[512];
	
	
	int first;

	Seatbelt *net_Belt;

	Seatbelt *net_SunVisor;

	Seatbelt *net_Phone;
	
	MvImgEnhance_HandOver *mvEnhance;
};

#endif 
