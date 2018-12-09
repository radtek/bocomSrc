#ifndef __MATCHTRACK_H
#define __MATCHTRACK_H

#include "TrackProperty.h"
#include "TrackConnector.h"

using namespace std;
using namespace MV_IMGPRO_UTILITY;
using namespace MV_AN_ANLGORITHM;
using namespace MV_SMALL_FUNCTION;



//��ƥ����м�켣�ṹ
typedef struct StrutPtMatchMidLevelInfo
{
	bool m_bVaild;   //�ýڵ��Ƿ���Ч

	CvPoint m_ptNow;        //�켣�ĵ�ǰ��
	uchar   m_ucASiftDsc[SIFT_DIMS];   //�켣��sift����

	CvPoint m_ptMinLt;    //�켣�˶��������ϵ�
	CvPoint m_ptMaxRb;    //�켣�˶��������µ�	

	double m_dTsAdd;      //�켣�ĸ���ʱ���
	double m_dTsUpdate;   //�켣�����ʱ���

	int m_nUpdatTime; //�ýڵ㹲���¶��ٴ�

	StrutPtMatchMidLevelInfo( )
	{
		m_bVaild = false;
	}
}PtMatchMidLevelInfo;


//��ƥ��Ĺ켣ƥ���м��
//��֤���켣(λ�Ƴ�����ʷ��)��������ƥ�䲻��
typedef struct StrutPtMatchMidLevel
{
public:
	StrutPtMatchMidLevel( );
	~StrutPtMatchMidLevel( );

	void mvInitVar( );

	void mvInitPtMatchMidLevel( const CvSize &szImg );
	void mvUninitPtMatchMidLevel( );

	//�Ե����ƥ��ʹ洢
	void mvPtMatchAndSave(	
			double dTsNow,              //��ǰ��ʱ���
			int nPtCnt,					//���������������
			CvPoint2D32f *pPts,			//������������λ��
			uchar **ucSift,				//�������������sift����ֵ
			int nNoNullTrNum,				//�ǿչ켣��Ŀ
			int *nANoNullTrIdx,			//�ǿչ켣����Ӧ�����
			MyTrackElem **pATrPointer     //�켣��Ӧ�ĵ�ַ(ָ��)
		);

public:
	IplImage *m_pHMvNStImg;  //��ʷ�ϴ����˶�/���ھ�ֹ�Ĺ켣ͼ��


private:
	//��ӻ����һ��Ԫ��
	int mvAddOrUpdateOneElem(	
			double dTsNow,   //��ǰ��ʱ���
			CvPoint ptNow,	 //������������λ��
			CvPoint ptTrMvLt, //������������켣�˶��������ϵ�
			CvPoint ptTrMvRb, //������������켣�˶��������µ�
			uchar ucASift[],  //�������������sift����ֵ
			int nMaxMatchPtCnt,  //ƥ�������ֵ
			const CvPoint *ptAMatchMv, //ƥ��λ��(��Ը�����)
			bool *bAMatched,     //�õ�λ���Ƿ�ƥ����
			int nTrAddMinMvDistTh = 5,   //�켣���ʱ��С��λ�ƾ���Ҫ��
			int nMaxSaveCnt4OnePt = 25   //���ֻ����Χ���ٸ������Ӱ��
		);

	//ɾ����ʱ��δ���µ�Ԫ��
	int mvDeleteLongTimeNoUpdateElem(	
			double dTsNow, 
			double dUpdateTimeTh 
		);

	//��ȡ��ʷ�ϴ����˶�/���ھ�ֹ�Ĺ켣ͼ��
	IplImage* mvGetHistoryMoveNowStopTrImg( );

private:
	IplImage *m_pPtLoc2TrIdxImg;  //�õ�λ������Ӧ�켣���ͼ

	vector<int> m_vectNullIdx;
	vector<int> m_vectUsedIdx;
	PtMatchMidLevelInfo *m_pPtMatchMLInfo;

}PtMatchMidLevel;

//��ƥ��������ṹ��
typedef struct AN_POINT_MATCH_TRACK
{
public:
	AN_POINT_MATCH_TRACK()
	{
		initVar();
	}	

	//��ʼ������
	void initVar( );

	//��ʼ����ƥ�������
	void mvInitPointMatchTracker( AnGlobalSet *pGlobalSet );
	
	//�ͷŵ�ƥ�������
	void mvUninitPointMatchTracker( );

	//���ƥ�����
	void mvPointMatchTrack(	int nPtCnt,  //�ǵ���Ŀ
			CvPoint2D32f *pPts, //�ǵ�λ��
		    uchar **ucSiftDesc, //�ǵ�sift������
		    double dTsNow,		//��ǰʱ���
			AreaPtTrInfo &struAreaPtTrInfo, //�����켣��Ϣ
			StruPtTrProperty &struPtTrProperty,  //��켣�����ж�
			PtsNear2FarSort &struTrPtsN2FResult, //�켣���ɽ���Զ�����Ľ��
			bool bEasyMatchMode	 //IN:�Ƿ���ü�ƥ��ģʽ
		);

	//��ȡ�õ���ƥ��������ṹ���й켣����ָ��
	CvSet * mvGetTrackSetPointer( ) { 
			return m_pPtTrackSet;
		}

	//����kalman���Թ켣���е�Ԥ��
	bool mvPredictPtWithKalman(
			CvPoint2D32f &fptPred,	//�õ���Ԥ���
			const MyTrack &tr,		//�����켣
			int nPredNextCnt,		//Ԥ���¼�����
			IplImage *pShowImg=NULL	//��ʾͼ��
		);

	//�����ѵĹ켣��������
	void mvConnectTrack( MvM2STrConnector &M2STrConnector );

	//���ù켣��ǰ��ǰ����ʶֵ
	void mvSetTrackFkLabel( IplImage *pFkLabelImg );

public:
	int m_nNoNullTrNum;    //�ǿչ켣��Ŀ
	int *m_nANoNullTrIdx;  //�ǿչ켣����Ӧ�����

	MyTrackElem **m_pATrPointer;   //�켣��Ӧ�ĵ�ַ(ָ��)

	vector<int> m_vectNoMatchPtIdx;    //δƥ���ϵĵ����
	vector<int> m_vectLongTrackPtIdx;  //���켣�ϵĵ����

	PtMatchMidLevel m_ptMatchMidLevel;  //��ƥ���м��

#ifdef TEST_SIFT_THROD
	Matchtrackpoint matchPoint;    //ƥ���ϵĵ������
	vector<Matchtrackpoint> matchPointSet;  //ƥ���ϵ�ü���
#endif

private:
	//�켣ƥ��ǰ��Ԥ�ȴ���
	void mvTrackMatchPreProcess( bool bFirst );

	//��ȡ�õ��켣�����еķǿչ켣
	void mvGetNonullTrack( bool bAll = true );

	//��ʼ���켣����Ϣ
	void mvNewTrackInit( MyTrackElem &trElem, double dTsNow );

	//�Թ켣�ĵ�ǰ֡��Ϣ���г�ʼ��
	void mvInitTrackCurFrameInfo( );

	//�Թ켣�ϵĽڵ�����ƶ�
	void mvShiftTrackNodes( );

	//�ѽǵ��Ϊ�켣
	void mvSavePtsAsTrack( int nPtCnt,  //�ǵ���Ŀ
			CvPoint2D32f *pPts, //�ǵ�λ��
			uchar **ucSiftDesc, //�ǵ�sift������
			double dTsNow       //��ǰʱ���
		);

	//���켣���뵽�켣������
	int mvAddTrackToTrackSet( MyTrackElem &trElem );

	//���Ƶ�ǰ֡�Ĺ켣���꼰ƥ�䴰��
	void mvEstimateTrImgPtLocAndMatchWin(
			CvPoint2D32f *ptAPredict,  //Ԥ���λ��
			CvRect *rectAMatch,		//ƥ���
			bool *bAHadGoodMatchWin //�Ƿ���ںõ�ƥ�䴰��
		);

	//������С���˷�Ԥ��켣��ͼ������
	bool mvGetPredictPtOfTrack(
			MyTrack& track,		//��ǰ�켣 
			double tsdiff,		//��ǰ֡����һ֡��ʱ���
			CvPoint2D32f &ptPredict //Ԥ���			
		);

	//��ȡ�õ�Ԥ����ڱ�֡��ƥ������
	CvRect mvGetMatchRect(
			bool bCanPredict,        //�Ƿ���Ԥ��
			CvPoint2D32f ptPredict,  //Ԥ���
			double tsdiff			 //��֡�ͱ�֡��ʱ����
		);

	//Ԥ�Ƚ��й켣ƥ��
	void mvPtSiftMatch( 
			vector<trMatchStru> &vctMatchResult, //OUT:ƥ����
			bool *bHadGoodMatchWin,   //IN:�Ƿ���ڽϺõ�ƥ�䴰��
			CvRect *rectAPtMatch,     //IN:���ƥ�䴰��
			bool bMatchAllPt,		  //IN:�Ƿ�����е����ƥ��
			bool bEasyMatchMode=false //IN:�Ƿ���ü�ƥ��ģʽ
		);

	//ÿ֡�Թ켣�ͽǵ����siftƥ��,���жϹ켣�Ƿ�ɾ��
	void mvFiltrateMatchResult(
			vector<trMatchStru> &vctMatchResult, //ƥ����
			int nPtCnt, //�ǵ���Ŀ
			int* nAPtIdx2TrIdx //�ǵ�����Ӧ�Ĺ켣���
		);

	//���ǵ���뵽�켣��
	void mvAddKeyPtsToTracks(
			int nPtCnt,			  //�ǵ���Ŀ
			CvPoint2D32f *ptALoc, //�ǵ�����
			uchar **pSiftDesc,	  //�ǵ�sift����������
			int* nAPtIdx2TrIdx	  //�ǵ�����Ӧ�Ĺ켣���
		);

	//��ȡ��֡�ǵ��ƥ�����(����Щƥ������,��Щ�ͽϳ��켣ƥ������)
	void mvGetKeyPtsMatchedInfo(
			int nPtCnt,			  //�ǵ���Ŀ
			CvPoint2D32f *ptALoc, //�ǵ�����
			int* nAPtIdx2TrIdx,   //�ǵ�����Ӧ�Ĺ켣���
			int nLongTrackThres,  //���켣����ʷ����Ҫ����ֵ
			vector<int> &vectNoMatchPtIdx,   //δƥ���ϵĵ����
			vector<int> &vectLongTrackPtIdx  //���켣�ϵĵ����
		);

	//�Թ켣�ͽǵ�ƥ���,�Թ켣���д���
	void mvProcessTracksAfterPtMatch( 
			CvPoint2D32f *ptAPreidct //�켣��֡��Ԥ���
		);
	
	//�жϺ�ɾ���ϲ�Ĺ켣(�϶�֡��ϳ�ʱ��ƥ�䲻��)
	int mvJudgeDeleteBadTracks( 
			int nTrIdx,				 //�켣���
			MyTrackElem *pTrackElem, //�켣Ԫ��ָ��
			IplImage *pRoadMask = NULL  //��·mask
		);

	//�ӹ켣������ɾ���켣
	void mvDeleteTrack(	int nTrIdx,	MyTrackElem *pTrackElem );
	

	//��ȡ�㣬ƥ��͹켣��Ϣ���뵽AreaPtTrInfo�ṹ��
	void mvGetPointMatchTrackInfo(
			AreaPtTrInfo &struAreaPtTrInfo,  //�����ڵĵ�켣��Ϣ�ṹ
			vector<int> &vectNoMatchPtIdx,   //δƥ���Ϲ켣�ĵ����
			vector<int> &vectLongTrackPtIdx, //ƥ�䵽���켣�ϵĵ����
			IplImage *pHMvNStImg  //��ʷ�ϴ����˶�/���ھ�ֹ�Ĺ켣ͼ��
		);

	//��ʾ�켣
	void mvShowTracks(char *cWinName, int nShowMod, 
		  int nKeyPtCnt, CvPoint2D32f  *ptKeyptLoc);

	//��ʾ���ƥ�����
	void mvShowPtsMatchInfo(char *cWinName,
		  int nKeyPtCnt, CvPoint2D32f  *ptKeyptLoc, //��ǰ�Ľǵ�
		  vector<int> &vectNoMatchPtIdx,   //δƥ���Ϲ켣�ĵ����
		  vector<int> &vectLongTrackPtIdx  //ƥ�䵽���켣�ϵĵ����
		);
private:
	bool  m_bFrist;        //�Ƿ�Ϊ��һ֡
	CvSet *m_pPtTrackSet;  //�켣����
	CvMemStorage *m_pMemStorage;  //���ٵ��ڴ�

	AnGlobalSet  *m_pGlobalSet;  //ָ��ȫ�ּ�

	int m_nTrackId;   //�켣��Id��

private:
	//�ǵ���Ϣ(���ⲿ����)
	int    m_nKeyPtCnt;
	CvPoint2D32f  *m_p_ptKeyptLoc;
	uchar  **m_pp_chSiftDesc;
	//-----------------------

	double m_dTsNow;  //��ǰ��ʱ���
	double m_dTsLast; //��һ֡��ʱ���

}StruPtMatchTracker;


//��ļ�SIFTƥ��Ӧ��
typedef struct StruPtSimpleSIFTMatchApp
{
	//һ�Զ�������SIFTƥ��,�����Ƿ�ƥ��ɹ�
	static bool mvSiftMatchOne2Much( 
			const CvPoint &ptGive,      //�����ĵ�
			uchar *giveSiftFeat,		//������sift����
			const int nComPtNum,        //���бȽϵĵ���Ŀ
			siftFeat *pComPtSiftFeat,	//���бȽϵ����е�sift����
			const CvPoint &ptMatchWH,	//ƥ��Ŀռ����Ҫ��
			const int nSiftMatchDistTh  //�趨��SIFTƥ����ֵ
		);

	//һ�Զ�������SIFTƥ��,�����Ƿ�ƥ��ɹ�
	static bool mvSiftMatchOne2Much( 
			siftFeat &givePtSiftFeat,   //�����ĵ�sift����
			const int nComPtNum,        //���бȽϵĵ���Ŀ
			siftFeat *pComPtSiftFeat,   //���бȽϵ����е�sift����
			const CvPoint &ptMatchWH,	//ƥ��Ŀռ����Ҫ��
			const int nSiftMatchDistTh  //�趨��SIFTƥ����ֵ
		);
}PtSimSIFTMatchApp;





#endif