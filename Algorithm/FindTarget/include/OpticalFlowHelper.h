#ifndef OPTICAL_FLOW_HELPER_H
#define OPTICAL_FLOW_HELPER_H


#include <vector>
#include "MvTrack.h"
#include "disjoint-set1.h"

#include "OpticalFlow.h"
#include "Mode.h"
#include "Car.h"
class MvTrackLayer;
class VirtualLoop;

using namespace std;

#ifdef TRACK_GROUP_LGW

#ifndef  MAXINT
#define MAXINT 65536
#endif

#define MIN_GROUP_TRACKNUM 3 //Group������С�Ĺ켣����
#define PERMIT_DISAPE_MAXFRAMNUM  12 //������ʧ��֡��

enum GroupType
{
    Motocycl_Group=0,
    CAR_Group,
	MIDBUS_Group,
	BUS_Group
};

typedef struct _ForObj
{
	CvRect ForRec; //ǰ��Ŀ��
	unsigned int upDatDetFramSeq;
	unsigned int uFristFramSeq;
	unsigned int uId;
	unsigned int type;
	
	_ForObj()
	{
		ForRec = cvRect(0,0,0,0);
		upDatDetFramSeq = 0;
		uFristFramSeq = 0;
		uId = 0;
		type = 0;
	}

}ForObj;
typedef struct _GroupFlow
{

	unsigned int nGropFolwId;//Group���
	CvRect   GropRec;//Group����
	bool bTrackUpdat;//�Ƿ�õ��켣����
	int  nPlatcolor;//������ɫ
	unsigned int  uCarId;//��ǰ���Ʊ��
	unsigned int  uHistoyCarId;//��ʷ���Ʊ��
	CvRect CarRec;//��������λ��
	CvRect CarPlateRec;//���Ƶ�λ��
	unsigned int ulstCarFremseq;//���������µ�֡��
	Drive_Dir Dir;//0Ϊ��Զ����������ǰ�ƣ�,1Ϊ�ɽ���Զ���羯β�ƣ�,2ˮƽ����
	CvPoint  PreditPlatePoi;//����λ��
	unsigned int uPrediPlateFram;
	bool     bPrediState;//�����Ƿ�õ�Ԥ�⳵��
	float    fPlateSlope; //���Ƶ�ƫ��б��
	int      nHitMidBus;//���ͳ�
	int      nSegY;//����ָ���
	int      nDisAppearNum;//����Ŀ�공ͷʻ��ͼ������Ĵ���
	int      nHitVehicl;//��Ϊ�ǻ������Ĵ���
	int     nEnterBusTop;//�󳵽��복������
	bool    bPark;//���Ƿ����ͣ��״̬
	bool    bMov;//���Ƿ�����˶�״̬
	//std::vector<CvPoint> GroupTrack; //Ŀ���ȶ����Track��һ��ͻ��ͽ������
	CvRect HistRec;
	std::vector<MvTrack*> *pvecTracks;
	bool  bFake;//�Ƿ�Ϊ��Ŀ��
	unsigned int uLastupFram;//���µ����һ��֡��
	int       nLigNum;//ҹ��Ƶĸ���
    unsigned int nAppearNum;
	bool     bReported; //ֻ���β���������Ϊ���������


	_GroupFlow()
	{

		nGropFolwId = 0;
		nPlatcolor = -1;
		bTrackUpdat = false;
		Dir = UnKnow;
		uCarId = 0;
		uHistoyCarId = 0;
		CarRec = cvRect(0,0,1,1);
		CarPlateRec = cvRect(0,0,1,1);
		PreditPlatePoi = cvPoint(MAX_INT,MAX_INT);
		ulstCarFremseq = 0;
		fPlateSlope = 1;
		nHitMidBus = 0;
		nSegY = 0;
		bPrediState = false;
		nDisAppearNum = 0;
		nHitVehicl = 0;
		nEnterBusTop = 0;
		bPark = false;
		bMov  = false;
		pvecTracks = NULL;
		bFake = false;
		uLastupFram = 0;
		nLigNum = 0;
		nAppearNum = 0;
		uPrediPlateFram = 0;
		bReported = false;

	}

}GroupFlow;

typedef struct _MotionVect
{
   int dx;
   int dy;
   _MotionVect()
   {
	   dx = 0 ;
	   dy = 0 ;
   }

}MotionVect; 

typedef struct _Group //������¼��ʷĿ����Ϣ
{
	GroupType type; //��������
	MotionVect vec;  //�����˶�ʸ��
	float   fWDis;  //�ڽ�MIN_TRACK_NUM�³����˶��������-
	CvRect  Rgn;   //����
	unsigned int uLastUpFram;//���һ�θ��µ�ʱ��
	unsigned int uFrisFram;//��һ��һ�θ��µ�ʱ��
	unsigned int  uCarId;//��ʷ���Ʊ��
	unsigned int  nGropFolwId;//��ʷ���Ʊ��
	_Group()
	{
		type = CAR_Group;
		fWDis = 0.0;
		Rgn = cvRect(0,0,1,1);
		uLastUpFram = 0;
		uFrisFram = 0;
		uCarId = 0;
		nGropFolwId = 0;

	}

}Group;

typedef struct _TrackCluster
{
	vector<MvTrack*> pVecTrack;
	int nGropFolwId; 
	_TrackCluster()
	{
		nGropFolwId = 0;
	}

}TrackCluster;

#endif

// һЩ�켣�ģ������ģ���ɵļ��ϡ�


class OpticalFlowHelper
{
public:
	typedef struct _FlowSetInfo
	{

		std::vector<MvTrack*> vecTracks;
		std::vector<Flow>     vecFlows;
		CvRect           rgn;
		double           dMainFlowX;
		double           dMainFlowY;
		int              nGropFolwId; 
		unsigned int    uCarId;
		CvRect          CarRec;
		Drive_Dir       Dir;
		float    fPlateSlope; //
		int       nPaletCol;
		bool      bFake;
		int       nAppearNum;
		bool      bTouchBom;
		int       nType;//-1δ֪��0�ǻ�������1��������2�����ͳ���3��
		int      nLigNum;
		bool     bPark;
		CvPoint  PlatePoi;//����λ��

		_FlowSetInfo()
		{
			dMainFlowX = 0.0;
			dMainFlowY = 0.0;
			nGropFolwId = 0;
			uCarId = 0;
			rgn = cvRect(0,0,0,0);
			CarRec = cvRect(0,0,1,1);
			Dir = Come;
			fPlateSlope = 1;
			nPaletCol = 0;
			bFake = false;
			nAppearNum = 0;
			bTouchBom = false;
			nType = -1;
			nLigNum = 0;
			bPark =false;
			PlatePoi = cvPoint(0,0);

		}

		void GetMainDirection(float &dDirX, float &dDirY);
	} FlowSetInfo;

#ifdef  TRACK_GROUP_LGW
	 static unsigned int m_GenId;
	 vector<GroupFlow> m_GroupFlow;
	 map<unsigned int,Group> m_HistGroup;
	 vector<Group> m_HistBusGroup;
	 MvMaxSize* m_pMaxSize;
	 MvTrackLayer* m_pTrackLayer;
	 unsigned int m_uFramSeq;
	 int m_nCarWidth;
#endif
	 VirtualLoop *m_pVirLoop;
	//static void GetMotionRegion( const std::vector<MvTrack*> &tracks, std::vector<FlowSetInfo> &vecFlowSetsInfo,
	//							float fDisXThresh = 0.6, float fDisYThresh = 1.5, Time_Mode mode = DAY);

	 OpticalFlowHelper();
	 ~ OpticalFlowHelper();
	 void GetMotionRegion(MvMaxSize* pMaxSize,const std::vector<MvTrack*> &tracks, IplImage* img, 
		std::vector<FlowSetInfo> &vecFlowSetsInfo1, std::vector<FlowSetInfo> &vecFlowSetsInfo2,
		float fDisXThresh1 = 0.6, float fDisYThresh1 = 1.5, float fSimility1 = 0.3, 
		float fDisXThresh2 = 0.8, float fDisYThresh2 = 1.8, float fSimility2 = 0.4, 
		Time_Mode mode = DAY, bool bDoTwice = false,bool bBuSNear = false);


	 void GetCompensRegion(const std::vector<FlowSetInfo> &vecFlowSrcInfo1, 
		const std::vector<FlowSetInfo> &vecFlowSrcInfo2, std::vector<FlowSetInfo> &vecFlowDstInfo2);


	 void GetMainFlow(const std::vector<Flow> &vecFlows, double &dx, double &dy);

	// ������ֵȥ��������û�п��Ƿ���    
	 void RemoveNoise(std::vector<Flow> &flowField);


	 bool HaveMovedFeaturesInRegion(const std::vector<FlowSetInfo> &vecFlowSetsInfo, CvRect rgn, int nSizeThresh);

	//static bool HaveMovedFeaturesInRegion(const vector<MvTrack*> &tracks, CvRect rgn, int nSizeThresh);

	 bool GetMainFlowInRegion(const std::vector<MvTrack*> &tracks, CvRect rgn, Flow &ret,Time_Mode mode = DAY);


	 void GetMaxLengFlowInRegion(const std::vector<MvTrack*> &tracks,Flow &ret);


	// �ж������ǲ��ǳ��ƴ��ڵ����γɵġ�
	 bool IsRgnLight(IplImage *img, MyCalibration*pCalib, CvRect rgn);

#ifdef TRACK_GROUP_LGW

	 void  mvDiffImg();
	 bool mvNearBus(CvRect rec,unsigned int nRecAppearFramSeq);
	 //��Track��Group������������
	 void mvProcessFlowGroup(VirtualLoop *pVriLoop,MvTrackLayer* pTrackLayer,MvMaxSize* pMaxSize,vector<MvTrack*> vecTracks,
		                     unsigned int uFrameSeq,int64 ts,vector<FlowSetInfo> &vecFlowSets,Time_Mode mode,
							 bool bTailMove = false); 

	 RelativDis mvCalGroupStaEndVarWDis(const MvTrack* pSrcTrack,const MvTrack *pDstTrack);

	 //�����µ�Group
	 void mvGenerateGroup(vector<MvTrack*> &vecNoGroupTracks,vector<TrackCluster> &ObjCluterTrack);

	 void mvSetFlowSetInfo(FlowSetInfo &vecFlowSets,GroupFlow *pGrowFlow);

	 bool mvCombineOterhGroup(FlowSetInfo SrcFlowSets);
	 void mvOterhCarGroup(GroupFlow *pCarGroup);

	 CvPoint mvGetCenPoin(const vector<MvTrack*> &ObjTrack);
	 
	 void mvDelSmallDisTrack(vector<MvTrack*> &Tracks);

	 Drive_Dir mvGetDirByTrack(const vector<MvTrack*> &Track);

	 void     mvCountGroupDisApearNum(GroupFlow *pGrowFlow);//��¼Ŀ����ʧ�Ĵ�����

	 //��JoinGroupTrack�б������뵽��pDst�����й켣���һ�µ�
	 void mvUpdatGroupByTrack(TrackCluster *pDst,GroupFlow *pGrowFlow,vector<MvTrack*> &JoinGroupTrack);

	 //ͳ���¼��뵽Group�Ĺ켣��ͬʱ���µ�ǰGroup�Ƿ����¹켣�����״̬
	 void mvGetJoinGroupTrack(TrackCluster *pSrc, const map<int ,int> &MapGroupToPos,vector<MvTrack*> &GroupTrack,unsigned int uFramSeq);

	 CvRect mvGetGroupSearcRec(GroupFlow *pGrpFlow,unsigned int uFramSeq,TrackCluster *pGroupTrack,CvRect &EnterBusopRec
		 ,int &nDx);

	 bool  mvGetBusToptrackCen(const vector<MvTrack*> &Track,CvPoint &point);

	 //ɾ��Group�²�����Ĺ켣
	 void mvDelUnResonGrpTrck(TrackCluster *pSrc,GroupFlow *pGroFlow);

	 //���ù켣�ĳ�������
	 void  mvSetTrackCarInf(vector<MvTrack*> &Track,GroupFlow *pGroFlow,bool bCurrectCar =false
		 ,CvPoint Plat =cvPoint(MAX_INT,MAX_INT));

	 void mvSetTrackVirtualCarInf(vector<MvTrack*> &Track,GroupFlow *pGroFlow,bool bHeadToBom = false);

	 void mvKmeanHalfTrack(TrackCluster *pSrc,bool bXSeg ,GroupFlow *pGroFlow,int nMaxSize,bool Bicycel = false);

	 bool mvTrackSegDis(const vector<MvTrack*> pSrcTrack);

	 bool mvSplitGroup(TrackCluster *pSrc,Drive_Dir Dir,int nMaxSize,TrackCluster *pDst);

	 void mvYDirCombinGroup(TrackCluster *pSrc,GroupFlow*pSrcGrFlow,TrackCluster *pDst,GroupFlow*pDstGrFlow,CvRect SrcMaxSize);

	 //У��Group
	 void mvCorrectGroupTrack(TrackCluster *pSrc, const map<int ,int> &MapGroupToPos);

	 //Group֮��Ĺ켣�ϲ�
	 void mvCombineGroupTrack(TrackCluster *pSrc,TrackCluster *pDst);

	 //���ƵĹ켣�ϲ�
	 void mvCombineSimTrack(TrackCluster *pSrc,TrackCluster *pDst,bool bYelPal =false);

	 int  mvGetMapGrouPos(const map<int ,int> &MapGroupToPos,int nGropFolwId);

	 void mvCorrectBigSizeGroup(TrackCluster *pSrc, const map<int ,int> &MapGroupToPos);

	 float mvCalSimTrack( MvTrack* pSrcTrack, const vector<MvTrack*> &vecCompaTracks,CvRect GropRec, CvRect MaxSizeRec);

	 void  mvTrackSetFlowGroupId(vector<MvTrack*> &Track,int nId);

	 bool  mvGroupTrackParkState( TrackCluster *pSrcTrack,bool &bMov);

	 bool mvAddToHistoryGroup(vector<MvTrack*> &ObjTrack,const GroupFlow &ObjGroup);

	 //����ͼ�۷ָ�
	 void mvSegmentGraph(Universe *pUniver, int num_vertices, int num_edges, Edge *edges);

	 //���ö��ַ���w����
	 void mvBinSort(Edge *data, int n);

	 void mvSetClusterTrackGroupId( Universe *pUniver,vector<TrackCluster> &ObjCluterTrack);

	 void mvSetGroupFlowByCar( GroupFlow *pGroFlow, vector<MvTrack*> pTrack,
		 int GropFolwId,vector<OpticalFlowHelper::FlowSetInfo>&vecFlowSets, Car *pCar=NULL ,CvRect CarRec =cvRect(0,0,1,1),CvRect paltRec= cvRect(0,0,1,1) );

	 void  mvClearTrackLoacInCar(vector<MvTrack*> &Track,CvRect CarRec);
	 
	 void  mvFindFakeGroup(vector<FlowSetInfo> &vecFlowSets);//Ѱ��αĿ�ꣻ��Ҫ�����ϳ���ǰ����·��ļ�Ŀ��

	  float  mvCalBrightRate(CvRect Rec,int nBrightness);

	 void  mvUpadtHistGroup();//������ʷĿ��

	  void  mvDelHistGroup();//ɾ����ʷĿ��--��Ժܽ�û���µ�

	  bool mvDetLig(const CvRect &Rec, vector<CvRect> &LigRec);
	  
	  void upDateDiffObj(const CvRect &Rec,bool bMayAdd = true);

	  void DelDiffObjByFram();
	  
	  bool bOutDiffArea(CvRect Rec);

	  void DelDiffObjByGrowId(unsigned int uId);

	  void SetDiffObjId(FlowSetInfo &vecFlowSets);
	  void SetDiffType();
	  ForObj *DiffObExis(unsigned int uId);
	  void  DelDiffObExis(unsigned int uId);

	  
	  void DrawDiffObj();

	  void SetObjFakeByCar(CvRect CarRec);
	  unsigned int mvSameCarWithDiffGrop(unsigned int uCarId);
	  void AssoCarByCarCoren(FlowSetInfo &vecFlowSets,GroupFlow &ObjNewGroup);
	  void SetGrowFlowReported(unsigned int uGrouFlowId);


	 IplImage *m_pRgbImg;
	 IplImage *m_pGrayImg;
	 CvRect  m_DiffRec;
	 IplImage *m_pLastGrayImg;
	 int   m_StartTrackYpos;
	 Time_Mode m_Mode;
	 vector<int> m_relivGroup;
	 int m_CrossFrisY;
	 int m_EleCrossSedY;
	 CvRect m_CarNumDetRgn;
	 vector<ForObj> m_ForObj;//β�Ƽ�¼��֡��Ŀ�ꣻ
#endif


};



#endif