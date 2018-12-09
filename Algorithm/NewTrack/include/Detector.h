//Ŀ����
#ifndef _MV_DETECTOR_H_
#define _MV_DETECTOR_H_

#include "libHeader.h"
#include "comHeader.h"  

#include "MatchTrack.h"
#include "ConstructGroup.h"

//class CDetector
//{
//public:
//	CDetector(void);
//	~CDetector(void);
//
//	//��ȡ�õ�Ŀ��Ĵ�Сͼ��
//	void mvGetObjSzImg( IplImage *pHImg, IplImage *pWImg )
//	{
//		m_pObjHImg = pHImg,	m_pObjWImg = pWImg;
//	};
//
//	////��ȡ�õ���ǰ����Ϣ
//	//void mvGetNowInfo( int dTs, 
//	//		map<int, AnPtTrack> *p_mapTrack, 
//	//		vector<AnPtTrack> *p_vecTrack, 
//	//		vector<MvGroup> *p_vecGroup, 
//	//		vector<MvSimpleObject> *p_vecObject )
//	//{
//	//	m_tsNow = dTs;
//	//	m_p_mapTrack = p_mapTrack; 
//	//	m_p_vecTrack = p_vecTrack;
//
//	//	m_p_vecGroup = p_vecGroup;
//
//	//	m_p_vecObject = p_vecObject;
//
//	//	m_bGetInfo = true;
//	//};
//
//public:
//	bool m_bGetInfo;
//
//	int m_tsNow;
//
//	//map<int, AnPtTrack> *m_p_mapTrack;   //trackID ��track��Ӧ��ϵ
//	//vector<AnPtTrack> *m_p_vecTrack;	   //���track
//
//	//vector<MvGroup> *m_p_vecGroup;	   //���group
//
//	//vector<MvSimpleObject> *m_p_vecObject;   //���object
//	
//	IplImage *m_pObjHImg, *m_pObjWImg;
//};


//----------------------StruTrackUtility-------------------------//

typedef struct StruTrackUtility
{
	//����켣��ͼ���˶��Ƕ�
	static bool mvCalTrValidMvImgAngle( float &fTrMvImgAngle,
			MyTrack &tr, double dTsNow, float fTrMvDistThres );

	//����켣��ͼ���˶��Ƕ�
	static bool mvCalTrValidMvImgAngle( float &fTrMvImgAngle,
			const simpleTrInfo &simTr, float fTrMvDistThres );

}MvTrackUtility;


//----------------------StruObjectUtility-------------------------//

typedef struct StruObjectUtility
{
	//��ȡĿ������Ч�Ĺ켣(Ŀǰָ�۲�)�����
	static int mvGetVaildTrsOfObj( int *nAVaildTrIdx,
				 MyGroup &obj, simpleTrInfo ASimTrs[] );

	//����Ŀ��켣����/�δ�λ��
	static void mvGetObjectTracksDist( 
		MyGroup &obj, simpleTrInfo ASimTrs[], 
		float &fMaxDist, float &fSecMaxDist );

	//�������nCalcLen֡��,Ŀ��켣����/�δ�λ�Ƽ�ƽ��λ��
	static bool mvGetObjectTracksDist4FixTrLen( 
		MyGroup &obj, simpleTrInfo ASimTrs[], int nCalcLen,
		float &fMaxDist, float &fMaxDist2, float &fMeanDist );

	//Ŀ���й켣�Ĺ۲��������������������Ӧ�Ĺ켣�ĵ���
	static void mvGetMaxWatchTimeOfObjTrack( 
		MyGroup &obj, simpleTrInfo ASimTrs[], 
		int &nMaxWatchTime, int &nCorTrPtCnt );

	//��ȡĿ������õ�3���켣(Ҳ��������3��)�����
	static void mvGetBest3TrsOfObj( 
		int &nBestTrNum, int nABestTrIdx[3], 
		MyGroup &obj, simpleTrInfo ASimTrs[] );	

	//���ø����Ĺ켣����ȡĿ�����Чͼ���˶�����
	static bool mvGetVaildImgMvAngleWithGiveTrs( 
		float &fObjMvImgAngle, int nTrCnt, int *nATrIdx,
		simpleTrInfo *pSimTrs, float fDistThres );

}MvObjectUtility;


//---------------------------------------------------------------//
//Ŀ���λ�û�����Ϣ
typedef struct StruObjLocationBasicInfo
{
	StruObjLocationBasicInfo( ) { mvInitVar( ); }

	double   m_dTs;

	CvPoint	 m_ptObjCet;
	CvPoint  m_ptObjLtPt;
	CvPoint  m_ptObjRbPt;

	void mvInitVar( );

	//��ȡĿ���λ�û�����Ϣ
	void mvGetInfo( MyGroup &obj, double dTsNow );

}MvObjLocationBasicInfo;


//Ŀ�����maxsize�Ļ�����Ϣ
typedef struct StruObjMaxsizeBasicInfo
{
	StruObjMaxsizeBasicInfo( ) { mvInitVar( ); }

	double   m_dTs;

	CvSize  m_szCar;
	CvSize  m_szPeo;

	CvSize  m_szCar4MvAngle;

	void mvInitVar( );

}MvObjMaxsizeBasicInfo;


//Ŀ��Ĺ켣������Ϣ(��켣�����Ĺ켣)
#define OBJINFO_TRDIST_CALCLEN 5   //Ŀ����Ϣ�й켣λ�Ƽ����֡��
#define OBJ_BEST_TRACK_CNT 3	   //Ŀ������õļ����켣
typedef struct StruObjTrackBasicInfo
{
	StruObjTrackBasicInfo( ) { mvInitVar( ); }

	double   m_dTs;

	double 	 m_dTsAdd;
	int      m_nHistoryLen;
	
	int		 m_nTracksCnt;
	int		 m_nVaildTracksCnt;
	
	float    m_fTrMaxDist;
	float    m_fTrSecMaxDist;

	int		 m_nTrCalcLen;
	float    m_fMaxDist4CalcLen;
	float    m_fSecMaxDist4CalcLen;
	float    m_fMeanDist4CalcLen;

	int		 m_nTrMaxWatchTime, m_nCorTrPtCnt;

	int      m_nBestTrCnt;
	int      m_nABestTrIdx[OBJ_BEST_TRACK_CNT];

	void  mvInitVar( );

	void  mvGetInfo(MyGroup &obj, simpleTrInfo ASimTrs[], double dTsNow);

}MvObjTrackBasicInfo;


//Ŀ��ĽǶȻ�����Ϣ
typedef struct StruObjAngleBasicInfo
{
	StruObjAngleBasicInfo( ) { mvInitVar( );	}

	double   m_dTs;

	float m_fImgMvAngle;	 //�˶��Ƕ�(��)
	float m_fImgArc4RoadOri; //����Ӧ�ĵ�·����(����)

	void mvInitVar( );

}MvObjAngleBasicInfo;


//Ŀ����ٶȻ�����Ϣ
typedef struct StruObjVelocityBasicInfo
{
	StruObjVelocityBasicInfo( ) { mvInitVar( );	}

	double   m_dTs;

	CvPoint2D32f m_fptWroVelocity;  //�����ٶ�

	void mvInitVar( );

}MvObjVelocityBasicInfo;


//����Ļ��ֽ��
typedef struct StruAreaInteResult
{	
	float fGrayVal;		//����ǰ�Ҷ�ֵ
	float fBgGrayVal;	//���򱳾��Ҷ�ֵ
	float fDiffPtRate;  //�����ֵ����ֵ
	float fForePtRate;  //����ǰ�������ֵ
	float fHSobDiffPtRate;  //����ˮƽsobel��(��������)����ֵ
	float fVSobDiffPtRate;  //������ֱsobel��(��������)����ֵ

}MvAreaInteResult;

//����Ķ�߶Ƚṹ��
typedef struct StruMultiScaleArea
{
	int    m_nLevelCnt;  //�߶���(���ܶ���10��)
	float  m_fRate;      //���ڳ߶ȱ�������Ӧ��ϵ��
	
	float  m_fAScale[10];   //���߶ȵ�ֵ

	double   m_dTsCalcAreaLoc;	//���������λ�õ�ʱ���
	double   m_dTsCalcAreaInte;	//�����������ֵ�ʱ���

	CvPoint  m_ptAAreaLt[10];  //�������ϵ�
	CvPoint  m_ptAAreaRb[10];  //�������µ�

	MvAreaInteResult m_areaInteResA[10];

	StruMultiScaleArea( );

	void mvInitVar( );

	//��������Ķ���߶ȿռ�
	void mvSetScaleValue( );
	void mvSetScaleValue( int nLevelCnt, 
		    float fRate, float fScale0 );

	//��ȡ������߶������ָ��
	int mvGetClosestScaleIdx( float fScale );

	//��ȡ��һ����������߶ȴ��ָ��
	int mvGetSmallestIdxBigGiveScale( float fScale );

	//���ø������������Ӧ�Ķ���߶�����
	bool mvSetObjMultiScaleAreaValue(
		    double dTsNow,           //��ǰ��ʱ���
			const MyGroup &obj,		 //������Ŀ��
			const CvSize &szStd,	 //��׼��С������Ӧ�߶�Ϊ1
			const CvSize &szImg,	 //ͼ��Ĵ�С
			bool bCalcObjLargeArea   //�Ƿ�Ϊ����Ŀ��Ĵ����� 
		);

	//���ø������������Ӧ�Ķ���߶�����
	bool mvSetObjMultiScaleAreaValue(   
			double dTsNow,            //��ǰ��ʱ���
			CvPoint2D32f &fptAreaLt,  //��������������ϵ�
			CvPoint2D32f &fptAreaRb,  //��������������µ�
			const CvSize &szStd,	  //��׼��С������Ӧ�߶�Ϊ1
			const CvSize &szImg,	  //ͼ��Ĵ�С
			bool bCalcObjLargeArea    //�Ƿ�Ϊ����Ŀ��Ĵ����� 
		);

	//�������߶�����Ļ���ֵ
	void mvGetInteImgValueOfAreaMultiScale( double dTsNow,
			IplImage *pIntGrayImg, IplImage *pIntBgGrayImg, 
			IplImage *pIntDiff2VImg, IplImage *pIntFore2VImg,
			IplImage *pIntHSobDiffImg, IplImage *pIntVSobDiffImg
		);

}MvMultiScaleArea;


//Ŀ���������Ļ�����Ϣ
typedef struct StruObjAreaBasicInfo
{
	StruObjAreaBasicInfo( ) { mvInitVar( ); }

	double   m_dTs;

	MvMultiScaleArea  m_area4MSPeo;  //��߶ȵ���������
	MvMultiScaleArea  m_area4MSCar;  //��߶ȵĳ�������

	MvMultiScaleArea  m_area4MSLargePeo;  //��߶ȵĴ���������
	MvMultiScaleArea  m_area4MSLargeCar;  //��߶ȵĴ�������


	bool     m_bVaildImgA;
	CvPoint  m_ptImgACarLt, m_ptImgACarRb; //���Ƕȷ���ĳ�������
	CvPoint  m_ptLargeImgACarLt, m_ptLargeImgACarRb; 
	

	CvPoint  m_ptVehBotHalfLt, m_ptVehBotHalfRb; //���°벿

	void mvInitVar( );

	//Ŀ����������λ�û�����Ϣ
	void mvGetObjAreaLocInfo( const MyGroup &obj,
			const CvSize &szPeo, const CvSize &szCar,
			const CvSize &szImgACar, const CvSize &szImg,
			double dTsNow );

	//Ŀ���������Ļ���ͼ������Ϣ
	void mvGetObjAreaInteInfo( const MyGroup &obj, double dTsNow,
			IplImage *pIntGrayImg, IplImage *pIntBgGrayImg, 
			IplImage *pIntDiff2VImg, IplImage *pIntFore2VImg,
			IplImage *pIntHSobDiffImg, IplImage *pIntVSobDiffImg );

}MvObjAreaBasicInfo;
	

//HoG�����жϵĽ��
typedef struct StruHoGPeoDetRes
{
	int  m_nHoGMode;    //�����õ�HoGģ�͵�ģʽ

	CvRect  m_rectBestPeoDetArea;  //����HoG���˼�������

	int     m_nDetectedHoGPeoNum;  //��⵽��HoG���˸���
	float   m_fAHoGPeoScore[10];   //��⵽��HoG���˵ĵ÷�
	CvRect  m_rectAHoGPeo[10];     //��⵽��HoG���˵�rect

	void mvInitVar( ); 

	void mvSaveDetRes( CvRect rectBestPeoArea,			
				   vector<float> &vctPeoScore,   
				   vector<CvRect> &vctRectPeoDst );    
	
}MvHoGPeoDetRes;


//Ŀ����������жϵĻ�����Ϣ
typedef struct StruObjTypeJudgeBasicInfo
{
	StruObjTypeJudgeBasicInfo( ) { mvInitVar( ); }
	
	MvHoGPeoDetRes  m_HoGPeoDetRes;

	void mvInitVar( )
	{ 
		m_HoGPeoDetRes.mvInitVar( );
	}

}MvObjTypeJudgeBasicInfo;

//Ŀ��Ļ�����Ϣ
typedef struct StruObjBasicInfo
{
	double   m_dTs;

	StruObjLocationBasicInfo m_BI4ObjLocation;
	StruObjMaxsizeBasicInfo  m_BI4ObjMaxsize;
	StruObjTrackBasicInfo    m_BI4ObjTrack;
	StruObjAngleBasicInfo    m_BI4ObjAngle;
	StruObjVelocityBasicInfo m_BI4ObjVelocity;
	StruObjAreaBasicInfo	 m_BI4ObjArea;

	//Ŀ�������ж���Ϣ
	MvObjTypeJudgeBasicInfo  m_BI4ObjTypeJudge;

	void mvInitVar( );

}MvObjBasicInfo;


//��֡����Ӧ��Ŀ����Ϣ
typedef struct StruSingleFrameObjInfo
{
	bool    m_bEmpty;       //�Ƿ�Ϊ��

	double  m_dTs;			//��֡��Ӧ��ʱ���
	int     m_nMaxObjIdx;   //��֡Ŀ����ŵ����ֵ

	MvIdx2IdMap    *m_pObjIdx2IdMap;  //Ŀ����ŵ�ID��ӳ���ϵ
	MvObjBasicInfo *m_pObjBasicInfo;  //Ŀ��Ļ�����Ϣ

	StruSingleFrameObjInfo( )
	{
		m_bEmpty = true;		//�Ƿ�Ϊ��

		m_dTs = -10000.0;		//��֡��Ӧ��ʱ���
		m_nMaxObjIdx = -10000;	//��֡Ŀ����ŵ����ֵ

		m_pObjIdx2IdMap = NULL;  //Ŀ����ŵ�ID��ӳ���ϵ
		m_pObjBasicInfo = NULL;  //Ŀ��Ļ�����Ϣ
	}

	void mvSetValue( double dTsNow, int nMaxObjIdx,
					 MvIdx2IdMap   *pObjIdx2IdMap, 
					 MvObjBasicInfo *pObjBasicInfo )
	{
		m_bEmpty = false;			//�Ƿ�Ϊ��

		m_dTs = dTsNow;				//��֡��Ӧ��ʱ���
		m_nMaxObjIdx = nMaxObjIdx;	//��֡Ŀ����ŵ����ֵ

		m_pObjIdx2IdMap = pObjIdx2IdMap;  //Ŀ����ŵ�ID��ӳ���ϵ
		m_pObjBasicInfo = pObjBasicInfo;  //Ŀ��Ļ�����Ϣ
	}

}MvSingleFrameObjInfo;


//��֡����Ӧ��Ŀ����Ϣ
#define  OBJINFO_MAX_MULTI_FRAME 100  //Ŀ����Ϣ����֡��
typedef struct StruMultiFrameObjInfo
{
	vector<int> m_vectVaildIdx;      //Ŀ����Ϣ�ӽ���Զ��֡

	CycleReplace m_nFObjInfoStoreCR; //��֡Ŀ����Ϣ��ѭ��������

	MvSingleFrameObjInfo m_ASFrameObjInfo[OBJINFO_MAX_MULTI_FRAME];

	StruMultiFrameObjInfo( )
	{ 
		m_vectVaildIdx.clear( );
		m_nFObjInfoStoreCR.mvGiveMaxSize(OBJINFO_MAX_MULTI_FRAME);
	}
}MvMultiFrameObjInfo;


//Ŀ���¼������Ľṹ��
typedef struct StruObjEventAlert
{
	int  m_nObjIdx;  //Ŀ�����
	bool m_bShow;    //�Ƿ�Ϊ��ʾ

	StruObjEventAlert( int nObjIdx, bool bShow )
	{
		m_nObjIdx = nObjIdx;  //Ŀ�����
		m_bShow  = bShow;     //�Ƿ�Ϊ��ʾ
	}

	void mvSetValue( int nObjIdx, bool bShow )
	{
		m_nObjIdx = nObjIdx;  //Ŀ�����
		m_bShow  = bShow;     //�Ƿ�Ϊ��ʾ
	}
}MvObjEventAlert;

#endif