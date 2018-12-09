#ifndef __TRACK_PROPERTY_H
#define __TRACK_PROPERTY_H

#include "libHeader.h"

#include "sift_descr.h"
#include "MvSiftDescr.h"
#include "MvKeyPtExtract.h"

#include "BaseStruct.h"

#include "comHeader.h"  //�����

using namespace std;
using namespace MV_IMGPRO_UTILITY;
using namespace MV_AN_ANLGORITHM;
using namespace MV_SMALL_FUNCTION;

#define PT_SQUARES(a,b) ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))

//��ΪΪֹͣ�켣����ֵ��
typedef struct StructStopTrackThresholdSet
{
	int    nTrCalcLenTh;    //�켣����С��¼����Ҫ��
	double dPassTimeTh;     //�켣����Сʱ����Ҫ�� 
	int    nImgMoveDistTh;  //�켣�����ͼ��λ��Ҫ�� 

	int  nMatchRadius4ML;  //���м��ʱƥ��İ뾶
	int  nSaveRadius4ML;   //���м��ʱ����İ뾶

	StructStopTrackThresholdSet()
	{
		nTrCalcLenTh = 10;
		dPassTimeTh = 3.0;
		nImgMoveDistTh = 5;

		nMatchRadius4ML = 3; 
		nSaveRadius4ML = 2;   
	}
}AnStTrThSet;


//�ǵ���뵽�����ģʽ
enum ENUM_KEYPT_ADD2GRID_MODE
{
	ADD_ALL_PTS_TOGRID = 0,  //���еĽǵ�
	ADD_NOMATCH_PTS_TOGRID,  //δƥ���ϵĽǵ�
	ADD_MATCH_LTR_PTS_TOGRID //ƥ�䵽���켣�ϵĽǵ�
};

//�漰����ǰ֡��Ϣ
typedef struct _AN_FRAME_INFO
{
	int nIndex;			//֡��
	int ts;				//ʱ���(�Ժ���Ϊ��λ)
	int bDay;           //�Ƿ�Ϊ����

	_AN_FRAME_INFO()
	{
		initVar( );
	}

	void initVar( )
	{ 
		nIndex	= -1;
		ts		= -1;	
		bDay = true;
	}
}AnFrameInfo;


//ȫ�ֵĲ���
typedef struct _AN_TR_GLOBAL_PARA
{
	AnFrameInfo m_FrameInfo;

	int m_nPointsCount;
	CvPoint2D32f m_pPoints[MAX_SIFT_CORNERS];
	uchar m_pFeature[MAX_SIFT_CORNERS][SIFT_DIMS];	//�������ǵ�һһ��Ӧ

	_AN_TR_GLOBAL_PARA()
	{
		m_nPointsCount	= 0;
	}

}AnTrGlobalPara;


typedef struct _AN_TRACK_POINT
{
	CvPoint corner;

	int ts;			//ʱ�������ȷ������
	int nStatus;	//0�ǹ��ƣ�1��ȷ��

	_AN_TRACK_POINT()
	{
		ts = -1;
		nStatus = 0;
	}

}AnTrackPoint;

typedef struct _AN_POINT_TRACK
{
	int nTrackId;	//�켣��ţ�Ψһ
	uchar feature[SIFT_DIMS];

	vector<AnTrackPoint> vecTrackPoint;

	CvPoint ptPredict;

	int nEstTimes;

	_AN_POINT_TRACK( )
	{
		nTrackId = -1;
		nEstTimes = 0;
	}

}AnPtTrack;

typedef struct _MV_OPTIFLOW_PT
{
	int     nTrackNo;	//��Ӧ�Ĺ켣���
	CvPoint ptTrPt;

	int     nPtNo;      //��Ӧ�Ľǵ����
	CvPoint ptMatchPt;

	_MV_OPTIFLOW_PT( )
	{

	}

	_MV_OPTIFLOW_PT( int n1,CvPoint pt1, int n2, CvPoint pt2 )
	{
		nTrackNo = n1;	
		ptTrPt = pt1;

		nPtNo = n2;    
		ptMatchPt = pt2;
	}	

}MvOptiFlowPt;


//-----------��ȡ���ɽ���Զ�ĵ���ŵĽṹ��------------//
typedef struct StruPointsNear2FarSort
{
public:
	bool m_bVaildNow;            //��ǰ�Ƿ���Ч

	int m_nCnt;					//��ȡ�ĵ���Ŀ
	int *m_nACorIdx;			//��Ӧ�ĵ����
	int *m_nACorSortCnt;		//������㰴��������ĵ���
	IplImage *m_pCorSortIdxImg; //������㰴��������ĵ����ͼ��

	int m_nMaxPtCnt;		    //���ĵ���
	int *m_nAAllCor2Sort;		//���е� �� �������� ��Ӧ��ϵ

public:
	StruPointsNear2FarSort( );

	void mvInitVar( );   
	void mvUninit( );

	void mvInitPointsNear2FarSort(int nMaxPtCnt);
	void mvUninitPointsNear2FarSort( );

	//��ȡ��ǰ��������
	void mvGetNowSortResult( int _nCnt,	//��ȡ�ĵ���Ŀ
			int *_nACorIdx,				//��Ӧ�ĵ����
			int *_nACorSortCnt,			//������㰴��������ĵ���
			IplImage *_pCorSortIdxImg   //������㰴��������ĵ����ͼ��
		);

	//�õ������������Ӧ��������
	bool mvGetN2FResultOfGiveIdx( int nIdx,
			int &nCnt, int **ppCorIdx );

}PtsNear2FarSort;


//-----------�����ڵĵ�켣��Ϣ��ȡ�ʹ洢�Ľṹ��------------//
//����ͼ�����켣ͼ��Ŀ�߱���
#ifndef AN_GRID_PTTR_RATE
	#define AN_GRID_PTTR_RATE 2
#endif
typedef struct _StruAreaPointTrackInfo
{
public:
	bool m_bInit;          //�Ƿ���ɳ�ʼ��
	bool m_bAddThisFrame;  //��֡�Ƿ������Ϣ

	int  m_nGrid2PtTrRate; //��������õ��ĵ�켣ͼ��Ŀ��֮��
	CvSize  m_szImg;	   //����ͼ���С(Ϊ���ټ�������Ϊʵ��ͼ��n��֮һ)

	//�˶��ٶ�
	IplImage *m_pInteTrImgVeloX;  //�켣��ͼ��X�ٶȻ���ͼ
	IplImage *m_pInteTrImgVeloY;  //�켣��ͼ��Y�ٶȻ���ͼ

	IplImage *m_pInteTrCntImg;    //�켣��Ŀ����ͼ

	//�ǵ�ƥ��
	IplImage *m_pInteAllKeyptCntImg;      //���нǵ�mapͼ�����ͼ
	IplImage *m_pInteUnmatchKeyptCntImg;  //δƥ���ϵĽǵ�mapͼ�����ͼ
	IplImage *m_pInteMatchLTrKeyptCntImg; //ƥ�䵽���켣�Ľǵ�mapͼ�����ͼ

	//��������ͼ
	IplImage *m_pTrImgMaxMvD;  //�켣���λ�Ƶ�ͼ��(ֻ�Ǹ�ָ�룬������)

public:
	_StruAreaPointTrackInfo( )
	{
		initVar( );
	}

	void initVar( );

	//��ʼ�������켣��Ϣ�ṹ��
	void mvInitAreaPointTrackInfo( int nGrid2PtTrRate, CvSize sz );

	//�ͷ������켣��Ϣ�ṹ��
	void mvUninitAreaPointTrackInfo( );

	//������ͼ��
	void mvClearResultImage( );

	//�������ͼ��Ļ���ͼ
	void mvBuildIntegalImage( );

	//����һ���켣��Ϣ
	void mvAddOnePointTrackInfo( 
			const CvPoint &ptTr,            //�켣��ǰ���ͼ��λ��
			const CvPoint2D32f &fptImgVelo, //�켣��ǰ��ͼ���ٶ�
			const CvPoint2D32f &fptLtMv,    //�켣�������˶��������ϵ�
			const CvPoint2D32f &fptRbMv     //�켣�������˶��������µ�
		 );

	//����һ���ǵ㼰��ƥ����Ϣ
	void mvAddOnePointMatchInfo( CvPoint ptTr,	int nPtAddToGridMode );

private:
	//�˶��ٶ�
	IplImage *m_pTrImgVeloX;  //�켣��ͼ��X�ٶ�
	IplImage *m_pTrImgVeloY;  //�켣��ͼ��Y�ٶ�

	IplImage *m_pTrCntImg;    //�켣��Ŀ

	//�ǵ�ƥ��
	IplImage *m_pAllKeyptCntImg;      //���нǵ�mapͼ��
	IplImage *m_pUnmatchKeyptCntImg;  //δƥ���ϵĽǵ�mapͼ��
	IplImage *m_pMatchLTrKeyptCntImg; //ƥ�䵽���켣�Ľǵ�mapͼ��

}StruAreaPointTrackInfo, AreaPtTrInfo;


//��켣���Խṹ��
typedef struct AN_POINT_TRACK_PROPERTY
{
public:
	AN_POINT_TRACK_PROPERTY( )
	{
		initVar( );
	}
	
	//��ʼ������
	void initVar( );
		
	//��ʼ����켣���Խṹ��
	void mvInitPointTrackProperty( );

	//�ͷŵ�켣���Խṹ��
	void mvUnnitPointTrackProperty( );

	//��ȡ��켣���Խṹ��
	void mvGetPtTrBasicProperty( 
			double dTsNow,      //��ǰ��ʱ���
			int nNoNullTrNum,	  //�ǿչ켣��Ŀ
			int *nANoNullTrIdx,   //�ǿչ켣����Ӧ�����
			MyTrackElem **pATrPointer, //�켣��Ӧ�ĵ�ַ(ָ��)
			int nImgW, int nImgH,  //ͼ��Ŀ�Ⱥ͸߶�
			IplImage *pCarWImg,	   //�������maxsizeͼ��
			IplImage *pCarHImg,	   //�����߶�maxsizeͼ��
			IplImage *pGrayImg,	   //��ǰ�Ҷ�ͼ
			PtsNear2FarSort &struTrPtsN2FResult  //�켣���ɽ���Զ������
		);

	//��ȡ��켣���Խṹ��
	void mvGetPointTrackProperty(
			float fAhomography_w2i[3][3],  //���絽ͼ�������Homography   
			float fAhomography_i2w[3][3],  //ͼ�����������Homography
			IplImage *pCalOriImage,  //����ͼ�����귽��ͼ��
			IplImage *pVaildOriImg,        //����ͼ�������귽���Ƿ���Ч
			PtsNear2FarSort &trPtsN2FResult  //�켣���ɽ���Զ��������ͼ
		);
public:
	float *m_fARealWorldOri;  //�켣�����緽��(����)
	float *m_fARealImageOri;  //�켣��ͼ����(����)
	int   *m_nATrAgainst;     //�켣�Ƿ�Ϊ����
	int   *m_nATrCross;       //�켣�Ƿ�Ϊ�ᴩ
	
	//�ṩ��һЩ����ľ�̬����(��ʱΪ��̬��������Ҫ�����Ϊ˽��)
public:

	//��ȡ��켣���˶�״̬����
	static bool mvGetPtTrMoveStatus( MyTrack &tr, 
			int nCalcLenTh,      //�켣�������ĳ�����ֵ
			double dCalcTimeTh,  //�켣��������ʱ����ֵ
			CvPoint2D32f &fptImgVelo  //�켣��ͼ���ٶ�
		);

private:
	bool   m_bInit;        //�Ƿ��ʼ����

	double m_dTsNow;         //��ǰʱ���
	double m_dTsLast1Frame;  //��һ֡��ʱ���
	double m_dTsLast2Frame;  //����֡��ʱ���

	int  m_nNoNullTrNum;    //�ǿչ켣��Ŀ
	int  *m_nANoNullTrIdx;  //�ǿչ켣����Ӧ�����
	MyTrackElem **m_pATrPointer;   //�켣��Ӧ�ĵ�ַ(ָ��)

	int   m_nImgWidth;     //ͼ����
	int   m_nImgHeight;	   //ͼ��߶�
	IplImage *m_pCarWImg;  //ͼ����maxsizeͼ��
	IplImage *m_pCarHImg;  //ͼ��߶�maxsizeͼ��
	IplImage *m_pGrayImg;  //��ǰ�ĻҶ�ͼ��

private:

	//------��ȡ��켣�ɽ���Զ�Ĺ켣���
	bool mvGetNear2FarTracks( 
			int &nTrCnt,		//��ȡ�Ĺ켣��Ŀ
			int **nACorTrIdx,   //�켣��Ӧ�����
			int **nACorSortCnt,	//������켣����������Ĺ켣��
			IplImage **pCorSortIdxImg   //������켣����������Ĺ켣���ͼ��
		);

	//��ʾ��켣�ɽ���Զ�Ĺ켣��ŵĽ��
	void mvShowNear2FarResult( 
			int nTrCnt,		//��ȡ�Ĺ켣��Ŀ
			int *nACorTrIdx,   //�켣��Ӧ�����
			int *nACorSortCnt,    //������켣����������Ĺ켣��
			IplImage *pCorSortIdxImg  //������켣����������Ĺ켣���ͼ��
		);


	//-------�жϹ켣�Ƿ�Ϊ����(����Χ�켣�����һ��)
	void mvIsDifferentTrack( 
			int nTrCnt,		   //��ȡ�Ĺ켣��Ŀ
			int *nACorTrIdx,   //�켣��Ӧ�����
			int *nACorSortCnt,    //������켣����������Ĺ켣��
			IplImage *pCorSortIdxImg  //������켣����������Ĺ켣���ͼ��
		);
		
	//-------�켣�˶�һ�����ж�
	bool mvGetMotionConsistency( MyTrack& tr );

	//-------��ȡ�õ�����Ϊ�쳣�Ĺ켣
	void mvGetDirUnusualTracks(
			float fAhomography_w2i[3][3],  //���絽ͼ�������Homography   
			float fAhomography_i2w[3][3],  //ͼ�����������Homography
			IplImage *pCalOriImage,		   //����ͼ�����귽��ͼ��
			IplImage *pVaildOriImg         //����ͼ�������귽���Ƿ���Ч
		);

	//�켣�˶��������ж�
#ifdef DEBUG_SHOW_AGAINST_CROSS_TR
	float m_fRoadImgOri; //��·���򻡶�
	float m_fMoveAngle1, m_fMoveAngle2; //˳�л���
	float m_fAgainstAngle1, m_fAgainstAngle2; //���л���	

	//��ʾ�������켣
	void mvShowUnusualTracks( 
			const CvPoint2D32f &fpt, float fRealImgOri,
			bool bGet, bool bAgainst, bool bCross,
			IplImage *pOriImg, IplImage *pRgbImg    
		);
#endif

	//�жϹ켣�˶������Ƿ�Ϊ����
	bool mvIsTrackDirUnusual( CvPoint2D32f point,  //�켣�ĵ�ǰ������
			float fRealImgOri,       //�켣�ĵ�ǰ�˶�ͼ����
			float fAhomography_w2i[3][3],  //���絽ͼ�������Homography   
			float fAhomography_i2w[3][3],  //ͼ�����������Homography   
			IplImage *oriImage,      //����ͼ�����귽��ͼ��
			IplImage *pVaildOriImg,  //����ͼ������Ƿ���Ч
			bool &bAgainst,			 //����
			bool &bCross			 //�ᴩ
		);


	//-------��ȡ�õ��켣���ܵ��˶�����
	void mvGetMoveAreaOfTracks( );

	//-------�Թ��Ƶ��ͼ�������������
	void mvRecorrectCoordOfEstPt(
			float fAhomography_i2w[3][3]  //ͼ�����������Homography
		);

	//-------�Ե�������������ƽ��
	void mvSmoothWorldCoord(
			float fAhomography_i2w[3][3]  //ͼ�����������Homography
		);

	//-------�Թ켣�����������ٶ�
	void mvCalcWorldVelocity( );

	//-------����켣�ķ���
	void mvCalcOrientation( );

	//����켣�ĵ�ǰͼ����Ƕ�(����)
	bool mvCalcRecentImgDir( MyTrack &tr, int nRecTrLen );

	//����켣��׼ȷͼ������緽��Ƕ�(����)
	bool mvGetRealTrackWorImgDir(		
		float &fRealWorldori,  //���������������Ƕ�
		float &fRealImageOri,  //�������ͼ������Ƕ�
		MyTrack &tr,     //�켣
		double dTsNow,    //��ǰ��ʱ���
		double dEstshift, //��ǰ׷�ݵ�ʱ��
		float fCalDistTh  //����������ֵ
		);


	//-------��ȡ�õ��켣��һЩ��ʧ�����Ϣ
	void mvGetDisappearPtInfo( );

	//-------��ȡ�õ��ɶ������Ĺ켣
	void mvGetMove2StopTracks(  );

	
	//�������е��ɶ������Ĺ켣���õ��ɶ�����Ŀ��ľ�ֹ�켣
	void mvGetRecStop4M2STr( 	
			int nMv2StopTrNum,   //�ɶ������Ĺ켣��Ŀ
			IplImage *pMapImg,	 //�ɶ������Ĺ켣mapͼ
			int nGray2MapRate,   //�Ҷ�ͼ��mapͼ�Ĵ�С��
			int nAroundM2SPtTh,  //��Χ���ɶ������ĵ����
			IplImage *pShowImg   //�����ʾͼ
		);

	//�жϹ켣����Ƿ�Ϊ�ɶ�����
	void mvIsTrackRecentMove2Stop(
			vector<int> &vectTrIdx,
			int nRecLenThresh = 10,
			IplImage *pShowImg = NULL 
		);

}StruPtTrProperty;


#ifdef TEST_SIFT_THROD
    //SIFTƥ���ϵĵ�����Խṹ��
	typedef struct _MATCH_TRACK_POINT
	{
		CvPoint2D32f pointtracked;  //ƥ���ϵ������
		double dMinDist;		    //ƥ���ϵ����С����
		float fMin2SecRate;			//ƥ���ϵ���С�������С����ı���
		_MATCH_TRACK_POINT()
		{
			pointtracked.x = 0.0f;
			pointtracked.y = 0.0f;
			dMinDist = 1.2e7;
			fMin2SecRate = 1.0f;
		}
	}Matchtrackpoint;
#endif


#endif