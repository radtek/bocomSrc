/* ��Ȩ���� 2009 �Ϻ�����������Ϣ�������޹�˾
* Copyright (c) 2009��Shanghai Bocom Intelligent Information Technologies Ltd
* �������ܹ�˾����
* Bocom Intelligent Confidential Proprietary
* �ļ����ƣ�MvVehicleClassifyDetail.h
* ժҪ: ��Ҫ�������ļ�������
* �汾: V1.9
* ����: ��� 
* �������: 2009��9��15��
*/

#ifndef MVVEHICLECLASSIFYDETAIL__H__
#define MVVEHICLECLASSIFYDETAIL__H__

#include <cv.h>
#include <highgui.h>
#include "ml.h"
#include <algorithm>
#include <vector>
#include "cvaux.h" 
#include "cxcore.h" 

#include "MvLineSegment.h"
#include "Mv_CarnumDetect.h"
#include "MvTypeUtility.h"
#include "MvTruckBusClassify.h"


//--------------���ƺ�Ķ���------------ 
#define VERSION_NUBER ("Version2014.06.21\n") //�汾���

#ifndef LINUX
//#define  MV_WIN_VER
#endif

//#ifndef MV_WIN_VER
//#include "cal_main.h"
//#endif

//#define MV_FROE_NEWVEHICLETYPE
//#define MV_NONCARD_NEWVEHICLETYPE
#define NEWVEHICLETYPE
#define MV_SAVEIMG_DEBUG
#define MV_MULTTHREAD
#define COMPRESSSVM   //svmѹ��ģ��
//����ص��¾䣬��û���κ�debug��¼
//#define  DEBUG_TYPE_ON


#ifdef DEBUG_TYPE_ON
	#define DEBUGSAVE
	#define  DEBUG_TRUCK
#endif

#ifndef DEBUG_TRUCK
	#define SET_TYPECODE(x)
#else
	#define SET_TYPECODE(x) m_nStatus=x
#endif

#ifdef DEBUG_TYPE_ON
	#ifdef LINUX
		#include <dirent.h>
		#include <unistd.h>
		#include <sys/stat.h>
		#include <sys/types.h>
		#define _chdir(a) chdir(a)
		#define _mkdir(a) mkdir(a, 0777)
		#include <stdio.h>
	#else
		#include <direct.h>
	#endif
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

#ifndef MV_WIN_VER
#define  USE_RGB_PIC
#endif

using namespace std;
using namespace cv;


typedef struct stVehicleRegion
{
	CvRect VehicleRect;	//����������������

	CvRect HeadRect;	//

	CvRect BrandRect;	//���ײ������Ƹ�������
	CvRect FaceRect;	//
	CvRect WindowRect;
	CvRect BodyRect;	//��������
	CvRect ForeHeadRect;	//�߳��������������ڿ���

	TypicalEdge tpEdge[4];
	stVehicleRegion()
	{
		VehicleRect = cvRect(0,0,0,0);
		HeadRect = cvRect(0,0,0,0);
		BrandRect = cvRect(0,0,0,0);
		FaceRect = cvRect(0,0,0,0);
		WindowRect = cvRect(0,0,0,0);
		BodyRect = cvRect(0,0,0,0);
		ForeHeadRect = cvRect(0,0,0,0);
	}
}VehicleRegion;



class MvVehicleClassifyDetail  
{
private:
	IplImage *m_pImage,*m_pGrayImage;
	IplImage *m_pIntegrateImage;	//����ͼ��
 	IplImage *m_pRImage,*m_pGImage,*m_pBImage;
	BLine * m_pLines;
	int m_nLines;

	float m_f_arHomography[3][3];

#ifndef  MV_WIN_VER
	//cal m_cal;
#endif

	int m_nLeft,m_nTop,m_nRight,m_nBot;	//�������
	int m_nBrandColor;	//������ɫ
	int m_nSmearNum;
	CvRect m_pSmearRect[20];	//�������20
	
	int m_nLightLevelHight;	//���Ƶĸ߶�
	int m_nLightDis;	//����֮��ľ���(�������Ƴ���),ֻ�ʺ�ҹ��ģʽ
	int m_nVehicleLampType;	//�������ͣ�������������ԣ�ֻ�����г��Ƶ������Ӧ��

	CvMemStorage *m_pStorage;
	CvSeq * m_pHLines,*m_pVLines;	//ˮƽ�߶μ���,��ֱ�߶μ���
	CvSeq * m_pSortHLines,*m_pSortVLines;	//������ˮƽ�߶κʹ�ֱ�߶μ���
	
	int m_nMinBusWidth;		//bus�Ĳο����
	int m_nMinCarWidth,m_nMaxCarWidth;		//С���Ŀ�ȷ�Χ
	
	double m_fZXScale;
	bool m_bIsNight;		//�Ƿ�����

	float m_fUptoLine;	//��������ֻ��¼y����


	int m_nStat_LongLine ;
	int m_nStat_BusBot ;	//bus��������
	int m_nStat_WinBot ;	//������������
	int m_nStat_WinTop ;	//��������������

	MvTruckBusClassify* m_pTBC;

	MvTruckBusClassify* m_pTBCBlue;//���Ƴ����ͷ���

	bool mvCenterAligned(stTypicalEdge e, stTypicalEdge f, int maxSizeWidth, double thres);
	void DeleteBGLine(bool bIsNight = false);
	void Orientation();
	
	static int y2cmp_func( const void* _a, const void* _b, void* userdata );
	static int bcmp_func( const void* _a, const void* _b, void* userdata );
	static int ycmp_func(const void *_a, const void *_b, void* userdata);
	static int LenCmp_func(const void *_a, const void *_b, void* userdata);

	CvSeq* GetHLines(const double thres);	//ȡ��ˮƽ�߶�
	CvSeq* GetVLines(const double thres);
	bool CheckBusBottomLine(stTypicalEdge e,int nH);	//�ж�һ�����Ƿ���һ��busͷ���ĵ���
	bool CheckWinBottomLine(stTypicalEdge e,int nH);	//�ж��Ƿ񳵴��ĵ���
	bool CheckWinTopLine(stTypicalEdge e,int nH);	//�ж��Ƿ񳵴��Ķ���
	float grayEdgeDiff(stTypicalEdge e,int nH);
	bool CheckTopSideLine(stTypicalEdge e,stTypicalEdge f,int nW);	//
	bool CheckBusBodyLine(stTypicalEdge e,int nW);	//�ж��Ƿ���ڽϳ��ĳ�����
	bool ExistDoubleLongBodyLine(stTypicalEdge e,int nW);  //
	bool ExistTruckBox(TypicalEdge edgeWinTop,int nW);	//�Ƿ���ڼ�װ�䳵��
	bool CheckFaceLine(stTypicalEdge e,int nW,int nMidX=0);  //����Ƿ���ڼ���ͷ���ĳ�ֱ�ߴ���	
	bool IsVehicleWindow(CvRect rect,int thesh=70);	//�ж�ָ�������Ƿ�Ϊ����
	bool IsRGBRegion(int nStartX,int nStartY,int nWidth,int nHeight);  //�ж�ָ�������Ƿ�Ϊ�����������
	bool IsBlueRegion(int nStartX,int nStartY,int nWidth,int nHeight);
	void JoinLine(TypicalEdge *HLine1,TypicalEdge *HLine2);	//��������ˮƽֱ��
	bool CanBeJoin(TypicalEdge HLine1,TypicalEdge HLine2);
	void AjustVehicleBottomEdge(const CvRect VRect,TypicalEdge *edgeBusBot);	//������������λ��
	int FindWindowLowPos(int nVehicleLen,TypicalEdge edgeWinBot,const CvRect VRect);
	int FindCarWindowPos(TypicalEdge tpEdge[4],int nVehicleLen);
	int mvFindEdgeIntersection(TypicalEdge e,BLine f,double *intersection);

	
	int GetVehicleWidthByVLine(stTypicalEdge *e);
	int GetEstimateLen(const TypicalEdge e, const int nH,const CvRect VRect);
	bool GetLampInfo(CvRect VBrandRect);	//ȡ����س�����Ϣ
	bool FindRectStruct(stTypicalEdge e,CvPoint *rectVertex,const int nDrct=1,int nW=0);	//Ѱ��һ�����Ϸ������·����ڵ����ƾ��νṹ
	

	
	bool FindOtherBrandFeature(CvSeq * linesgroup,bool bCheck[4],TypicalEdge tpEdge[4]);
	int DetectVehicle(CvRect *VehicleRects,bool bVBrand=false);	//�������
	int DetectVehicleNightMode(CvRect *VehicleRects); //ҹ���������ģʽ
	bool BrandAtMiddle(const bool bExist[4],const stTypicalEdge tpEdge[4],const CvRect VRect,const int nVehicleLen);
	bool ExistVertex(const stTypicalEdge e,float fThresh=0.25);
	bool ExistVertexAndLongVLine(const TypicalEdge edgeWintop,const int nVehicleLen,float fTresh=0.15);
	bool FindVehicleRegion(const CvRect VRect,VehicleRegion *VRegion);
	bool ExistLongVLine(const TypicalEdge e, const TypicalEdge f,const int nW);
	bool ExistLongTruckVLine(const TypicalEdge e, const TypicalEdge f,const int nW);
	bool ExistMoreShortVLines(const TypicalEdge e,const TypicalEdge f,int minx,int maxx,const int nThresh= 5);
	int FindWinTopEdge_YellowBrand(CvSeq *linesgroup,int nVehicleLen,bool bCheck[4],TypicalEdge tpEdge[4]);

	void PadEdge(const CvRect VRect, TypicalEdge * e);
	void InitRect(CvRect &rect);
	CvPoint2D32f GetWorldCoordinate(const CvPoint2D32f &pt);	//ȡ��ͼ�����������
	
	bool ExistDoubleRect(const stTypicalEdge e);
	bool FindRectEdge(stTypicalEdge e,stTypicalEdge rectEdge[4]);
	
	int mvTruckDetect(const IplImage *pImage,const CvRect rect,bool IsNight=false);		//�����ж�

	bool ExistTruckVLine(bool bExist[4],TypicalEdge tpEdge[4]);
	bool ExistMoreTruckVLine(bool bExist[4],TypicalEdge tpEdge[4]);
	bool ExistDoubleTruckVLine(bool bExist[4],TypicalEdge tpEdge[4]); 
	bool ExistVLine(TypicalEdge Edge1,TypicalEdge Edge2,float fThresh=.3f);
	bool ExistBetweenLine(const TypicalEdge e,const TypicalEdge f);
	bool ExistLongBiasLine(const TypicalEdge hLine,const CvRect VRect);

	bool ExistTowTruck(bool bCheck[4],TypicalEdge tpEdge[4],const int nVehicleLen);
	bool ExistMiniBusTop(const TypicalEdge e,const int nVehicleLen);
	bool ExistSUNVTop(const TypicalEdge edgeWinTop);

	bool IsExistBlueRegion(bool bCheck[4],TypicalEdge tpEdge[4],const int nStarty,const int nVehicleLen);
	bool IsExistVLine(const int nStartX,const int nStartY,const int nEndX,const int nEndY);
	bool ExistContainerTop(TypicalEdge edgeTop,const int nVehicleLen,const float fThresh=.3f);
	
	bool IsOtherVehicleLine(TypicalEdge edge);
	bool ExistBiasVLine(TypicalEdge Edge1,TypicalEdge Edge2,float fThresh=.2f);

	int GetInitLen(const CvRect VRect);			//���ݳ�����ɫ�ͳ��ƿ�Ȼ�ȡ�����ĳ�ʼ���ƿ��
	int GetSymmetryLen(const CvRect VRect, const TypicalEdge e) const;

	int m_nBDHeight,m_nBDWidth;
	bool m_bGACard;		//�Ƿ�Ϊ�۰���

	vector<TypicalEdge> m_vecHLines;
	vector<TypicalEdge> m_vecVLines;


#ifdef DEBUGSAVE
	char  m_szSaveFileName[256];
#endif
    
	int m_nStatus;			//�ж�״̬

	bool m_bIsForCarnum;	//�Ƿ���ǰ�Ƽ��

	bool m_pbCheck[4];
	TypicalEdge m_tpEdge[4];

	int m_nVehicleType;
	int m_nWidth;		//������ȣ�
	
	//====================================================================================
	//���������õ��ĳ���
#ifdef DEBUGSAVE
	void SaveDebugImage(const CvRect VRect, bool bChek[4],TypicalEdge tpEdge[4]); 
#endif
	//
	int FindBottomEdge(CvSeq *lineGroups,const CvRect VRect,TypicalEdge &botEdge);
	bool AjustUpThresh(const TypicalEdge e, int &nUpThresh);
	//====================================================================================
	//ǰ��

	int DetectTruckByBrand(const CvRect VRect);
	
	int DetectYellowBrand(const CvRect VRect, CvSeq* lineGroups, bool bCheck[4], TypicalEdge tpEdge[4]);
	int DetectOtherBrand(const CvRect VRect, CvSeq* lineGroups, bool bCheck[4], TypicalEdge tpEdge[4]);

	int DetectTruckByBrandNightMode(const CvRect VRect);

	int ClassifyYellowBrandNightMode(bool bCheck[4],TypicalEdge tpEdge[4],const CvRect VRect,
		int nVehicleLen,VehicleRegion vRegion);
	int ClassifyOtherBrandNightMode(bool bCheck[4],TypicalEdge tpEdge[4],const CvRect VRect,
		const int nVehicleLen,VehicleRegion vRegion);
	int ClassifyOtherBrand(bool bCheck[4],TypicalEdge tpEdge[4],const CvRect VRect,VehicleRegion vRegion);
	int ClassifyYellowBrand(bool bCheck[4],TypicalEdge tpEdge[4],const CvRect VRect,VehicleRegion vRegion);

	
	//===================================================================================
	//β�Ƽ��
	int DetectTruckByTailBrand(const CvRect VRect);
	
	int newTruckType(IplImage *pImage, const CvRect rt);
	int newTailTruckType(IplImage *pImage, const CvRect rt);
	int newTruckTypeBlue(IplImage *pImage, const CvRect rt);
#ifdef NEWVEHICLETYPE
private:
	char buffer_path[512];
	//////////////////////
	HOGDescriptor *hog;
	int nImgNum;
	int dim;
	////��������nImgNum�������������������� WIDTH * HEIGHT������������������ͼ���С  
	int PCAdi;
	CvSVM svm;
	CvMat* pMean ;
	CvMat* pEigVecs ;
#ifndef MV_MULTTHREAD
	CvMat* SVMtrainMat;
	CvMat* pResult;
	IplImage* ResizeImg;
	vector<float> descriptors;
#endif	
	//���Ƴ�ʼ��
	int first;

#ifdef MV_FROE_NEWVEHICLETYPE
	CvSVM svm_fore;
	CvMat* pMean_fore ;
	CvMat* pEigVecs_fore ;
#endif

#ifdef MV_NONCARD_NEWVEHICLETYPE
	CvSVM svm_NonCard;
	CvMat* pMean_NonCard ;
	CvMat* pEigVecs_NonCard ;
#endif
#endif

public:
	
	MvVehicleClassifyDetail();
	virtual ~MvVehicleClassifyDetail();
	

	void SetHomograph(float homography_image_to_world[3][3]);	//���ñ궨����
	void FindHomography(float *image,float *world);

	//����TSAI�궨����
#ifndef MV_WIN_VER
	//void mvSetTSAIData(int width,int height,int nCount,float *ptImg,float *ptWorld);
#endif

	void SetNightMode(bool bMode);	//����ҹ��ģʽ
	
			
#ifdef DEBUGSAVE
	void SetSaveFileName(const char * fileName);
#endif
	int mvTruckDetect(const IplImage *pImage,const CARNUM_CONTEXT Brand, bool IsDay=true,
		bool IsForeCarnum=true,bool IsMoreDetail=false,int *nMoreDetail = NULL); //�����ж�

	int mvTruckDetect(const IplImage *pImage,const CAR_INFO *carInfo, bool IsDay=true,
		bool IsForeCarnum=true,bool IsMoreDetail=false,int *nMoreDetail = NULL); //�����ж�, �Զ��峵���ṹ��

	/*
	mvNonCardTruckDetect�����������ж�
	���룺	
	pImage����Ҫ�����ͼƬ�����ڳ����б�Ϳ�������ϸ���õĲ���ͬһ��ͼƬ���ڴ����ͼƬ��ͬʱ����Ҫ����ROI����
	Brand��������Ϣ
	IsDay������Ϊtrue,ҹ��Ϊfalse
	IsMoreDetail���Ƿ�Ϊϸ�ֳ��ͣ�Ĭ��Ϊ��
	nMoreDetail��ϸ�ֳ��ͷ���ֵ
	����ֵ
	return����һ����
	nMoreDetail���ڶ����ࣨϸ�ֽ����
	*/
	int mvNonCardTruckDetect (const IplImage *pImage, CARNUM_CONTEXT Brand, bool IsDay=true, 
						bool IsMoreDetail=false, int *nMoreDetail = NULL);

	int mvGet_Vision( char* strPath  );//ģ�Ͱ汾

	void Truck_Destroy();
	int Truck_Init( char* strPath = NULL );

#ifdef NEWVEHICLETYPE
	//����ģ�ͳ�ʼ��·��
	void mvSetPath(char* strPath);
#endif
	int mvMoreInfo();
};

#endif 
