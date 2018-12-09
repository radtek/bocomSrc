// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#ifndef DEBUG_BACKGROUND_LIGHT_H
#define DEBUG_BACKGROUND_LIGHT_H
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <vector>
//#include "ColorCommon.h"
#include "Mv_CarnumDetect.h"
//#include "MvDayNight.h"
#include "CameraCrtStruct.h"
using namespace std;

#define     JUDGING_CLOUD_NUM (120)
#define     IMAGE_NUM (9) 
#define     LIGHT_HIST_DIMENTION (900)
#define     CARD_CAR_DIM (40) //40
#define     ISNIGHT_DIM (1800) //60
#define     ILLU_DIM (1800)


#ifndef USE_DSP_CODE
//#define USE_DSP_CODE
#endif


typedef struct tagBACKGROUND_INFO
{
	double mean;
	double stdDev;
	tagBACKGROUND_INFO()
	{
		mean = 0.0;
		stdDev = 0.0;
	}
}bg_info;


class BGLight
{

public:
	BGLight(void);

	~BGLight(void);

	void mvInit_bglight( IplImage *image, CvRect &detectRt,bool bIsFaceCrt=false );

	void mvGetCamCrtBgLight(IplImage* image, road_context& road_Info, carnum_context* vehicle_Information,
						int nCarNumResult, bool &bisChangeByCloud, int colorMode, int isDayByTime=C_DAY); //1 ��ʾ����
	
private:
	void mvGetCardBGLight( IplImage* image, CvRect rtRoi );
				
	void mvGetNoCardBGLight( IplImage* image, int nCarNumResult );

	void mvComputeLightHist( road_context& road_Info, const int &frameCount );
	
	int mvMedian( double arr[], int dim, int count );

	void mvInverseOrSide(carnum_context vehicle_Info, int leftRightLight[3], int *cardLeftRight_Hist,
						int* cardToward_Inv_Hist, int *lightResut, const int &nDimention, const int &nCounts);

	void mvBgChangeByCloud(carnum_context* vehicle_Information, int nCarNumResult, bool &bIsCloud);

	void mvIsInverseLight(const carnum_context &vehicle_Info, int leftRightLight[3],
							int *inverseHist, int &isInverse, const int &nDimention, const int &nCounts);

	int mvComputeMedianIllum(IplImage *image, int nCounts);

	void mvRestrictRectangelByImage( const IplImage *image, CvRect &rect);

	void mvRestrictROIByImage( CvRect &rect, const IplImage *image );

	int mvIsNight(int bgLightMean, char *lightBG_Hist, int lightCrt, int dim, int nCounts);

	int mvIIlu(IplImage *grayImg, float scale_W, float scale_H, double dExpoIndex);



public:
	int m_IsDayByLight;//0Ϊ���ϣ�1Ϊ����

	int m_IsDayByTime;

	int m_SideTowards[2];

	int m_Bg_CardDiff;

	int m_IsInverseLight;


private:
	/*�����Ƿ����Ƶı仯*/
	char m_histVec[JUDGING_CLOUD_NUM];

	carnum_context m_vehicle_Info;

	CvRect m_CardRect;

	CvRect m_RtRoi;

	double m_LightBgMean;

	double m_LightBgStd;
	
	int m_leftRightLight[3];
	
	double m_LightMeanHist[LIGHT_HIST_DIMENTION];

	double m_LightStdHist[LIGHT_HIST_DIMENTION];

	double m_CardLightHist[CARD_CAR_DIM];

	int m_LeftRightHist[CARD_CAR_DIM];

	int m_TowardInvHist[CARD_CAR_DIM];

	int m_InverseHist[CARD_CAR_DIM];

	char m_NightHist[ISNIGHT_DIM];

	unsigned short m_IlluHist[ILLU_DIM];

	double m_PreRoadMean;

	int m_PreCarnumColor;

	int m_ColorMode; //��ɫͨ��˳��

	int64 m_Counts; //�������

	int64 m_InSiCounts; //�������˳��������

	int64 m_CdInvCounts; //���Ƽ��˳��������

	IplImage **m_subGrayImage; //û�м�⳵�Ƶ�9��ͼ������ [IMAGE_NUM]

	int m_sizeX;

	int m_sizeY;

	double m_CloudRoadM;

	bool isCloudChanging;

	int counts;

	int nIntervalCounts;

	bool m_bIsFaceCrt; //�Ƿ�����������������


};



#endif
