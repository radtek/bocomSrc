// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#ifndef VIRTUALLOOP_H
#define VIRTUALLOOP_H

#include <vector>
//#include <set>
#include <map>
#include <errno.h>

#include "SensedObject.h"
#include "disjoint-set1.h"
#include "Calibration.h"
#include "IBackgroundModel.h"
#include "CarManager.h"
#include "OpticalFlow.h"
#include "OpticalFlowSift.h"
#include "MvLineSegment.h"
#include "SynCharData.h"
#include "MvTrack.h"
#include "OpticalFlowHelper.h"
#include "VehicleFlowHelper.h"
#include "MvLine.h"
#include "MvLineStorage.h"
#include "MvBgLine.h"
#include "functions.h"
#include "MvLineMerge.h"

#define FTG_USE_HOG

#ifdef FTG_USE_HOG
#include "hog.h"
#endif


typedef struct _FloatRect
{
	float x;
	float y;
	float width;
	float height;
} MvFloatRect;




typedef struct _BUSTOPINF
{ 
	char SerSliSum;
	double fBusTopAvg;
	CvRect  BusVlpRect;
	bool   bBusRepted;
	bool   bBusAwayVlp;
	unsigned int  nFramNum;


	_BUSTOPINF()
	{
		BusVlpRect = cvRect(0,0,0,0);
		SerSliSum = 0;
		bBusRepted = false;
		bBusAwayVlp = false;  
	}


}MvBusTopInf;



class MvFindTargetByVirtualLoop;
class CarManager;
class VehicleFlowHelper;

class VirtualLoop  
{
private:
	VehicleFlowHelper *m_pVehicleFlowHelper;
	//MvLineStorage *m_pVirtualLoopLineStorage;

	#ifdef FTG_USE_HOG
		MvHOGDescriptor* m_pHogDet;
	#endif

    

	//NoCardColor *m_pNoCard_Color;

	#ifdef DO_DONGS_CODE
public:
		//�������
		int m_N;

		//��¼��ʷ�ľ�ֵ�뷽��
		//ǰһ֡
		double *oldMean;
		double *oldDev;
		//ǰ��֡
		double *oldMean2;
		double *oldDev2;

		
		//��¼�������
		CvRect *subRoi;		
		
		//��¼�ϴε��õ�֡��
		int m_oldFrame;

	#endif

public:
	std::vector<SensedObject*> objs;

	std::vector<SensedObject*> lastFrameObjs;

	int m_nCarWidth; 
	

	unsigned int m_nBuSApNum;
	CvRect       m_BuSRec;
	int          m_nVlpCarWidth;
	CvRect       m_AddParRec;
	CvRect       m_vlpRec;
	

	


	// ���캯��
	VirtualLoop(MvFindTargetByVirtualLoop *pFtgVlp, CarManager *pCarManager);
	
	// ��������
	~VirtualLoop();

	// ���ʺ����ڵ羯���ٵ�Ŀ���ҳ���
	void GetObjsForEle(unsigned int uFrameSeq, std::vector<SensedObject*> &objs, IplImage *dimg = NULL);


	// ��pObj
	void SealObject(SensedObject *pObj);

	// ��������Ȧ�ϵ�rectת������������ϵ��
	// rectδ��С��
	MvFloatRect ConvertVlpRect2World(const CvRect &rect) const;

	// ��rect��ͼ������ת���������ꡣ
	// rect�����ԭͼ���꣨����ԭͼ��û��С��1600*1200����
	MvFloatRect ConvertRectFromImageToWorld(const CvRect &rect) const;
	

	//�����checkimgת������������ϵ
	CvPoint2D64f CvtPointFromCheckImg2World(CvPoint2D64f checkImgPoint);


	//��������Ź���roiת����checkImg
	CvPoint2D64f CvtPointFromCheckImgRoi2CheckImg(CvPoint2D64f checkImgRoiPoint, CvRect roi);


	// �ж�check image����С�ģ��ϵ�ֱ���Ƿ�ѹ��Ȧ��
	bool IsLineCrossLoop(int x1, int y1, int x2, int y2, float decratio = 0);
	bool IsLineCrossLoop2(int x1, int y1, int x2, int y2, float dec);


	// ��ԭͼ�ϵ�rectת����check image�ϡ�
	// ���罫���ƺ����rectת��check image�ϡ�
	CvRect CvtRectFrOriImgToChkImg(const CvRect &rect) const;


	// ��vlp�ϵ�rectת��Check�ϡ�tips��vlp��check�������ԭͼ��
	void ConvertRectFromVlpToCheck(CvRect &rect) const;

	// ��check roi���ϵ�rectת����ԭͼ��û�о�����С
	void CvtRectFromCheckToOri(CvRect &rect) const;





	//��ͼ������rect
//	void Sense(IplImage *img0, IBackgroundModel *bgm, unsigned int imgId, int64 ts, vector<CvRect> &rects, IplImage **vlpImage);


//	void Update(/*CarManager* pCarManager, const MvFindTargetByVirtualLoop *pFtgVlp, */IplImage* checkOriRgb, 
//		vector<Flow> flowField, int64 nOpticalFlowDeltaTimestamp, vector<CvRect> &newRects,
//		vector<CvRect> &invalidRegion, unsigned int frameSeq, int64 ts, bool bBackgroundSuddenChanged, 
//		MyCalibration *pCali,  int imgIndex, unsigned int uTimestamp,CvRect vlpRect, CvRect checkImageRect,  
//		const OpticalFlowSift *pSift, IplImage* bkImg, const IplImage *imgCheck);

	void Update(unsigned int frameSeq, int64 ts, int imgIndex, unsigned int uTimestamp, MyCalibration *pCali, IplImage* imgCheckRgb, 
				std::vector<CvRect> &bgRects, bool bBackgroundSuddenChanged,IplImage* bkImg,  IplImage *imgCheck, const std::vector<MvTrack*> &tracks, 
				const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSets, const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSetsProx,
				std::vector<CvRect> &invalidRegion, MvCorner*pCorners, int nCount, std::vector<CvRect> vecAbsBg,vector<CvRect>VlpObjBacRec,
				IplImage *ShadowImg =NULL ,IplImage *VlpForEsImg =NULL,IplImage *DarkVlpForImg = NULL);
	void Update(unsigned int frameSeq, int64 ts, unsigned int uTimestamp
		,const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSets,IplImage *imgCheckRgb
		,IplImage *imgCheck);
	void SetFakeObj(int nFlowGropId);

	void SetSenObjForType(int nFlowGropId,int nType);

	void SetObjNearCarState(unsigned int frameSeq);

	bool  JudgeShadow(CvRect ObjPos,IplImage *ShadowImg);

	bool  GroupByRoad(CvRect GroupRec,IplImage *RecImg);

	int  mvGetSensObjChanel(CvRect Rgn);



	// �ж�Ŀ���Ƿ�����ĳ���󳵡�
	// �󳵳���ʱ�п��ܷ��飬������漸֡�������ˡ�����԰���ǰ����ĺϲ�������
	bool IsObjBelongToBigVeh(SensedObject* pObj);

	

	//void UpdateNight(CarManager *pCarManager, const MvFindTargetByVirtualLoop *pFtgVlp, IplImage* checkOriRgb,
	//				vector<Flow> flowFieldOri, int64 nOpticalFlowDeltaTimestamp,  vector<CvRect> &bgRects, 
	//				vector<CvRect> &invalidRegion, unsigned int frameSeq, int64 ts, bool bBackgroundSuddenChanged,
	//				MyCalibration *pCali, int imgIndex, unsigned int uTimestamp, CvRect vlpRect, CvRect checkImageRect,
	//				/*const OpticalFlowSift *pSift,*/ IplImage* bkImg, IplImage *imgCheck, const vector<MvTrack*> &tracks,
	//				const vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSets);
	
  
    void SegObjRect(const vector<OpticalFlowHelper::FlowSetInfo> &VlpFlowSets,const std::vector<CvRect> &newRects, std::vector<CvRect> ForRects, std::vector<CvRect> &DstRects);

	// ����õĶ�Ӧ������Munkres�㷨
	static std::map<int, int> GetBestAssoc(const std::vector<CvRect> &newRects, const std::vector<SensedObject*> &objs);

	
	// ÿ֡���ã���SensedObject�ͳ��ƹ���
	void Assoc(const vector<CvRect> &SrcUinVlpRec,unsigned int ts, CarManager* pCarManager, IplImage *Test =NULL);

	Car* Assoc(unsigned int uCarId,SensedObject *pSensObj);
	void mvSeTracksCarPlat(SensedObject *pSensObj,vector<MvTrack*>tracks,CvPoint PlateCen);
	
	//��ýϽ���VlpĿ�꣡
	std::vector<SensedObject *> GetNearSensedObjs();

	// ÿ֡����һ�Σ�ɾ��һЩ����Ҫ����Ϣ
	void Delete(int64 ts, unsigned int uFrameSeq, VehicleFlowHelper *pFlowHelper);
	
	// �����ÿ֡���á��������Ҫ����Ķ���ͨ��ret�����
	//void Output(int64 ts, unsigned int frameSeq, std::vector<CarInfo> &otput, std::vector<ObjSyncData> &vecSyncData );

	void Output(int64 ts, unsigned int uFrameSeq,  VehicleFlowHelper *pFlowHelper, std::vector<SensedObject*> &vecOutput, std::map<int, _CarInfo> m_mapOutputedVehicle, Time_Mode mode);

	//�ж�*****��Ŀ���Ƿ�����ͬ����ǰ��󳵣�
	bool CheckObjBelongToBigVeh(SensedObject *pObj, ObjType vehType, std::map<int, _CarInfo> m_mapOutputedVehicle, unsigned int frameSeq, int64 ts);

	//void TestSobel(IplImage *img0);
	
	// ��vlp������������������ö�Ӧ�����ڴ��ݸ���ɫ��
	static std::map<int, int> GetBestVlpRectToFlowFieldRectAssign(const std::vector<CvRect> &vlpRects, const std::vector<CvRect> &flowRects);
	
	// �������ѹ�ߣ����������²�����uSeq���ĳ��ǲ���ռ������������Ȧ�Ĵ󳵡�
	bool IsLastBigVehAndTakeFullVlp(unsigned int uSeq);

	MvFindTargetByVirtualLoop *m_pFtgVlp;
private:

	//MvLineMerge *m_pLineMerge;
	unsigned int m_nBusNigfram;
	unsigned int m_BusNowAway;
	map<int,MvBusTopInf>  m_MapBusInf;
	map<int,vector< unsigned int > > m_ChalCarFram;
	void RecodNearVehicFram(int nChanl,unsigned int frameSeq);
	bool GetNearVehicl(int nChanel, unsigned int frameSeq,bool bCom =true );
	void mvCorrecHisTrackRec(SensedObject*pSenObj,const vector<MvTrack*> &pTrack,CvRect &SensObjRec);
	void StorelasTrackIndex(SensedObject*pSenObj,const vector<MvTrack*> &pTrack);
	

	

	CarManager *m_pCarManager;
	
	// ��ȡobject��flag=-1����Ŀ�ꡣflag=0û�жϵ�Ŀ�ꡣflag=1���˵�Ŀ�ꡣ
	void GetObjects(std::vector<SensedObject*> &objs, int flag);

	// ��������Ŀ���Ŀ��ͷλ�á�
	void UpdateObjectsHeadPos(const std::vector<MvTrack*> &tracks/*, CvPoint offset*/);

	
	// ����ǿ�ϣ���Ȼ�ϣ�������
	void SealObjectsByFlowCarNumNat(CarManager *pCarManager, unsigned int frameSeq,
		const MvFindTargetByVirtualLoop *pFtgVlp, const IplImage *imgCheck, const IplImage *imgCheckRgb);
	
	// �������0�����켣��Ŀ��ϵ���
	void SealObjectWithManyZeroFlowTrack(unsigned int uFrameSeq, const IplImage *imgCheck, 
		const std::vector<MvTrack*> &vecTracks, bool bIsDay, std::vector<CvRect> &sealedRgn);

	//void SealByCarNumAndFLow(CarManager *pCarManager);

	
	// ͳ��ͼ��img��roi������RGB����ͨ���ľ�ֵ�뷽�
	//static void StColor(IplImage *img, CvRect roi, float mean[3], float var[3]);

	
	void SealObjectByVlpColor();



	void CloseToMergeObjs();


	// ��������ڱ�֡�м����������������һ��sensed obj��
	// ������obj���ұ�֪�������Ͳ��ֵõ������ж����ұ�
	// �ͳ����Ƿ�Գƣ�����Գƣ����������ұ�λ���е�ǰ��֪��������
	// ����г���������Ƚϴ������У�����г����ıȽ�С���������
	void SplitUsingPlateAndVehicleRgn(std::vector<CvRect> &vlpRects, unsigned int uFrameSeq);


	//����жϳ��Ƶĸ���
    int DetectLigSum(IplImage *imgN,int threshold);

	// ��䣬���Ƴ���ʱ�ó����жϳ��͡�-2�в�����1�󳵡�2С����
	int DetectVeichleTypeByHeadLight(IplImage *imgN, CvRect rectCarNum, unsigned int uFrameSeq, int threshold = 200);


	// ���Ѿ���ȷ����Ŀ��ȥ����ǰ����
	void SplitForeRectsByObject(std::vector<CvRect> &rects, std::vector<CvRect> rectsByCarNum, const std::vector<MvTrack*> &tracks) const;



	void SplitForeAccordingMotionDiff(const std::vector<MvTrack*> &tracks, 
		const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSets, 
		const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSetsProx, 
		std::vector<CvRect> &rects, MyCalibration *pCalibCheckImg, 
		unsigned int uFrameSeq, IplImage *imgCheck);


	// ���³��Ƴ���ʱ������һЩobjs������һЩ������ϲ���
	void ReviseByCarNum(unsigned int uFrameSeq);


	// ��һ�ε���Update��seq
	unsigned int m_uLastFrameSeq;


	// �����޲������������ƣ�����vlp�ϱ���һ��ѹ��
	void FixByCarNum(const CarManager *pCarManager, std::vector<CvRect> &rects) ;


	void FixByHistory(IplImage* imgCheckRgb, IplImage* imgCheck, const std::vector<CvRect> &vlpRects, std::vector<CvRect> &rects, const std::vector<MvTrack*> &tracks,
		const std::vector<OpticalFlowHelper::FlowSetInfo> &vecFlowSets,const vector<CvRect> &foreRgnByFlow,IplImage *ForVlpImg
		,const std::vector<CvRect> &VlpObjBacRec) const;
	

	void GroupContourRects(CvSeq *contour, std::vector<CvRect> &bigRectContainer);


	void GroupRectsInRects(std::vector<CvRect> &rects, std::vector<CvRect> bigRects);

	
	SensedObject* GetLastFrameObject(CvRect rect, int64 ts);

	// ���ݳ���λ�ã����������ѹ��λ��
	CvRect CalcVeichlePosInVlpByCarNum(CvRect rectCarNum, CvRect vlpRoi, FindTargetElePolice::MyCalibration *pCalib, float veichleWidth) const;

	// ���ݳ���λ�á�����vlp�ϵ�ѹ��λ�ü�������������ͼ���е�λ��
	// TODO: ���߶ȺͿ�ĵĹ�ϵ
	CvRect CalcVeichlePosInImgByCarNum(CvRect rectCarNum, CvRect vlpRoi, FindTargetElePolice::MyCalibration *pCalib, 
							CvRect rectCarOnVlp, float fVeichleLengthWidthRatio = 3.0f) const;


	// ���ݳ�����������vlp�ϵ�ѹ��λ�ü�������������ͼ���е�λ��
	// TODO: ���߶ȺͿ�ĵĹ�ϵ
	CvRect CalcVeichlePosInImgByFlow(CvRect vlpRoi, CvRect rectCarOnVlp, FindTargetElePolice::MyCalibration* pCalib, float flow, float fVeiLenWidRat = 3.0f);


	

	

	//IplImage *GetVlpImage(IplImage *frame);
	void GetSobelEdgeGroups(IplImage *frame, std::vector<CvRect> &sobelRects);

	// ��֪��һ֡ĳ�������ѹ��λ�á����ݱ�֡������Ԥ���䱾֡ѹ��λ�á�
	// ����ֱ�е�Ŀ�ꡣǰ����֡λ��Ӧ�ò�ࡣ�������������Ϊ�˽����
	// ֱ��Ŀ�ꡣ
	void PredictVlpRectByFlow(CvRect &rect, const Flow &flow) const;


	// ��psobj�ڲ���lastFrameObj������
	bool IsLastFrameObj(SensedObject *psobj);

	// �ж�������Ȧ������rect�Ƿ񿿽�
	bool IsTwoVlpRectsClose(const CvRect &r1, const CvRect &r2);


	void  GroupRectsOnVlp(std::vector<CvRect> src, std::vector<CvRect> &dest);



	


	void  GroupFlowField(const std::vector<Flow> &flowFieldWorld, std::vector<CvRect> &rects);

#ifdef TRACK_GROUP_LGW
		void DetObjCol(SensedObjectTrackData * psotd,IplImage *pChecRgbImg);
#endif

    void DetectVehicType(SensedObject *pSensObj,IplImage *imgCheckRgb,IplImage *imgCheck,unsigned int frameSeq,
		const std::vector<MvTrack*> &track);


	// ������ֱ��һˮƽ���жϳ�������
	static int DetectVeichleTypeByLines( IplImage* img, CvRect roi, MvLine *pLines, int nLineCount, MvFindTargetByVirtualLoop *pFtg, int direction, bool bRealCar, CvRect &rectVehicleRgn, unsigned int uFrameSeq) ;
	

	//
	static int DetectVehicleTypeByLinesWeak(IplImage *img, MvLine *lines, int nLineCount, MvFindTargetByVirtualLoop *pFtg);
	
	
	static bool   IsBigVeichleByLines(MyCalibration *pCalib, int nVlpY, MvLine *pLines, int nLineCount, MvLine **pRetHorLine, MvLine **pRetLeftVerLine, MvLine **pRetRightVerLine);

	
	
	static bool   IsSmallVeichleByLines(MvLine *pLines, int nLineCount, MvLine **pRetHorLine, MvLine **pRetLeftVerLine, MvLine **pRetRightVerLine);

	
	
	static bool   IsBigVehicleByBackLines(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, \
		                                    MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, MvFindTargetByVirtualLoop *pFtg, bool bRealCar);
	
	static bool   IsSmallVehicleByBackLines(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, \
											MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, MvFindTargetByVirtualLoop *pFtg, bool bRealCar);
	static bool   IsVehicleByBackLines(MvLine *pLines, int nLineCount, bool bIsCar);

	static bool   IsGotBackWindow(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, \
								  MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr);
	static bool   IsGotTwoSidelinesAndOneHorline(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, \
												 MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine,  float fHorLineLenThr, float fSideLineLenThr, MvFindTargetByVirtualLoop *pFtg, bool bRealCar);
	static bool   IsHaveManySideLines(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, \
												 MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine,float fSideLineLenThr, MvFindTargetByVirtualLoop *pFtg);
	
	static float  CalcObjInstantMotionDirection(const std::vector<MvTrack*> &track, CvRect trackRegion, IplImage *img, unsigned int uFrameSeq);  //����Ŀ���˶���������
	
     static  float CalcObjInstantMotionDirection(const std::vector<MvTrack*> &track, IplImage *img, unsigned int uFrameSeq);
	#ifdef FTG_USE_HOG
	static int DetectVehicleTypeByHog(IplImage* detectImg, MvHOGDescriptor* hog, std::vector<CvRect> &found);
	#endif


	#ifdef DO_DONGS_CODE
		
		// ����־
		//��ֱ���жϱ�Ե��
		//static bool   IsBigVeichleByLinesSide(unsigned int uFrameSeq, bool bIsDay, const IplImage* img, CvRect roi);
		bool   IsBigVeichleByLinesSide(unsigned int uFrameSeq,
											  bool bIsDay, const IplImage* img, 
											  CvRect roi, const MvFindTargetByVirtualLoop *pFtgVlp,
											  CvRect MyVirtualLoopRect,
  											  float &fRemainFlow);



		// ����־
		//��������¼����ڵ�С�������
		//�������ֵΪ�棬��Ͽ������
		//�������ֵΪ�٣�����ݷ��ص�����ֵ���жϸò��öϣ���ʱ���
		bool IsCutBigCarTail(unsigned int uFrameSeq, 
								bool bIsDay, const IplImage* img,
								CvRect roi, const MvFindTargetByVirtualLoop *pFtgVlp,
								CvRect MyVirtualLoopRect,
								float &fRemainFlow);


		// ����־
		//���ϼ����ڵ�С�������
		//�������ֵΪ�棬��Ͽ������   
		//�������ֵΪ�٣�����ݷ��ص�����ֵ���жϸò��öϣ���ʱ���.

		bool IsCutBigCarTailNight(unsigned int uFrameSeq,
												  bool bIsDay, const IplImage* img, 
												  CvRect roi,const MvFindTargetByVirtualLoop *pFtgVlp,
												  CvRect MyVirtualLoopRect,
												  float &fRemainFlow);

		// ����־
		// ���ϼ����ڵ�С�������
		// �������ֵΪ�棬��Ͽ������   
		// ע���˺������ݻҶȵľ�ֵ�ͷ�����м���
		bool IsCutBigCarTailNight2(unsigned int uFrameSeq,
												  bool bIsDay, const IplImage* img, 
												  CvRect roi,const MvFindTargetByVirtualLoop *pFtgVlp,
												  CvRect MyVirtualLoopRect
												  );


	#endif

public:
	// ������ⲿ�ͷš�
	static void GetLines( MyCalibration *pCalib,MvBgLine *pLineBGM, IplImage* img, CvRect roi, MvLine **pLines, int &nCount, \
							MvLine **pMvBgLine, int &nBgLineNum, unsigned int uFrameSeq, MvLineStorage *pLineStorage, MvLineMerge *pLineMerge);
};

#endif
