// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   11:56
	filename: 	e:\BocomProjects\find_target_lib\include\MvFindTargetByVirtualLoop.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvFindTargetByVirtualLoop
	file ext:	h
	author:		Durong
	
	purpose:	��Ӧ�ö˵Ľӿ��Ѿ��㷨�����
*********************************************************************/
#ifndef MV_FIND_TARGET_BY_VIRTUAL_LOOP_H
#define MV_FIND_TARGET_BY_VIRTUAL_LOOP_H

#include <vector>
#include <deque>
#include <errno.h>
#include <fstream>
#include <cxcore.h>

#include "VibeModel.h"
#include "Calibration.h"
#include "IBackgroundModel.h"
#include "VirtualLoop.h"
#include "CarInfo.h"
//#include "BackgroundStatistic.h"
#include "MvPolygon.h"
#include "OpticalFlow.h"
#include "CarManager.h"
#include "OpticalFlowSift.h"
#include "DetectType.h"
#include "Mode.h"
#include "MvCornerLayer.h"
#include "MvLightStatusMem.h"
#include "MvTrackLayer.h"
#include "MvGroupLayer.h"
#include "ViolationInfo.h"
#include "MvMaxSize.h"
#include "MvLine.h"
#include "MvChannelRegion.h"
#include "SynCharData.h"
#include "MvRectTracker.h"
#include "VehicleFlowHelper.h"
//#include "BgStatistic.h"
#include "RoadStatistic.h"
#include "MvBgLine.h"
#include "MvLoopManager.h"
#include "MvUnionManager.h"
#include "CornerBackgroundModel.h"
#include "MvLightTwinklingPreventer.h"
#include "ColorRecognition.h"
#include "MvLineStorage.h"
#include "RoadTypeDetector.h"
#include "MvLineMerge.h"
//#include "OnBusVioDet.h"
#include "MvFixRedLight.h"
#include "MvRadarSpeed.h"
#include "Mv_LoopshutterLight.h"//ѡ����ͼƬ�����ͷ�ļ�
#include "MvSurf.h"
#include "MyVideoStabilizer4Client.h"
#include "Cshadow.h"

#include "OpticalFlowHelper.h"
#define MAP_TS_TO_FRAMESEQ_SIZE 8000




#ifndef LINUX
  #define Local_Test //���ؽ��в���
#else
   #undef Local_Test
   #define int64 long long
#endif

using namespace PRJ_NAMESPACE_NAME;



class MvUnionManager;
struct _LoopInfo;
//class MvViolationDetecter;
//class OnBusVioDet;
class MvPhysicLoop;
class MvRadarSpeed;
class Mv_LoopShutterLight;
class OpticalFlowHelper;


typedef struct _RedLightTwinkRgn
{
	int    nRoadIndex;
	int    nDriection;//-1��ת��0ǰ�У�1��ת
	CvRect redRgn;
	CvRect greenRgn;

	_RedLightTwinkRgn()
	{
		nRoadIndex = -2;
		redRgn.width = 0;
		greenRgn.width = 0;
	}
}RedLightTwinkRgn;

typedef struct _MVVIDEOSTD {	
	vector<CvPoint2D32f> vPList;	
	_MVVIDEOSTD()
	{		
		vPList.clear();
	}
}mvvideostd;

typedef struct _MVLOOPSTATUS{

	int nRoadIndex;
	bool status;
	_MVLOOPSTATUS()
	{
		nRoadIndex = -1;
		status = false;//false:�쳣��ture������
	}
}mvloopstatus;

typedef struct _MVOBJPAR{
		int  ParkId;
		CvRect paRec;
		_MVOBJPAR()
		{
			ParkId = -1;
			paRec  = cvRect(0,0,1,1);
		}

}mvobjpar;

//��Ŀ����&���Ӿ�����Ŀ��Ʋ������ɿͻ������ã�
typedef struct _ParaConfig
{
	//Ŀ���⣡
	bool      bDetectNonVehicle;              //�Ƿ���ǻ�����!    Ĭ��Ϊtrue!
	bool      bFilterSideVehicle;             //�Ƿ���˱��ϻ�����!   Ĭ��Ϊtrue!
	bool      bFilterSideVlpObj;              //�Ƿ���˳��Ƽ���������ߵ�*****Ŀ�꣡  Ĭ��Ϊfalse��
	bool      bUseSurf;                       //�Ƿ�ʹ��Surf������Ƶ���٣�  Ĭ��Ϊfalse!
	bool      bUseExternalCtrl;               //��Ƶ����ʱ���Ƿ��ⲿ���Ƴ��ƾ��������ظ߶�!  Ĭ��Ϊfalse!
	int       nCarPlateHeightOffGround;       //��Ƶ����ʱ�����ƾ�����ͼ��ͶӰ���ش�С��   ����ֵΪ70��
	int       nFramePlus;                     //��ȦĿ����������֡��������!   ����ֵΪ0��
	float     fLoopVehicleLenFix;             //��Ȧ����������!    ����ֵΪ1.0m��
	bool      bOutPutNonAutoMobile;           //�����Ƿ�����ź�Ŀ�꣬���Ǻ�Ŀ������ĵ�λ���й��ˣ�Ĭ��Ϊ���
	bool      bDoNonPlateDetect;              //�����Ƴ���⣬Ĭ�ϼ�⣬Ϊtrue��

	//���Ӿ��죡
	bool      bUseChongHongDeng;              //�Ƿ�ʹ�ó��ƹ��ܣ�Ĭ��Ϊfalse!
	bool      bUseJudgeTurning;               //�Ƿ�ʹ��ת������ֱ�д�������ƹ��ܣ�  Ĭ��Ϊfalse!
	bool      bUseMask;                       //�Ƿ�ʹ��Mask���ټ��㣡  Ĭ��Ϊfalse!
	int       nRedLightViolationAllowance;    //������źſ�ʼ���ӳ�����!   ����ֵΪ3��
	float     fRedLightVioPic[2];             //�����ȡͼ����!   far = fRedLightVioPic[0], near = fRedLightVioPic[1];  far��near�ĵ���ֵ�ֱ�Ϊ1.0��0.5��ע��˳��Ҫ�㷴��


	_ParaConfig()
	{
		bDetectNonVehicle           = true;
		bFilterSideVehicle          = true;
		bFilterSideVlpObj           = false;
		bUseSurf                    = false;
		bUseExternalCtrl            = false;
		bOutPutNonAutoMobile        = true;
		bDoNonPlateDetect           = true;
		nCarPlateHeightOffGround    = 70;
		nFramePlus                  = 0;
		fLoopVehicleLenFix          = 1.0;

		bUseChongHongDeng           = false;
		bUseJudgeTurning            = false;
		bUseMask                    = false;
		nRedLightViolationAllowance = 3;
		fRedLightVioPic[0]          = 1.0;
		fRedLightVioPic[1]          = 0.5;
	}
};

class MvFindTargetByVirtualLoop
{
public:

	// ���캯��
	MvFindTargetByVirtualLoop();

	~MvFindTargetByVirtualLoop();

	CvRect GetCarRec( CarInfo *pCarIf)const;

	IplImage **   GetSurfImage()
	{
		return m_PreviousImg;
	}
	int64 *       GetCorrectionTime()
	{
		return m_lastTimeStamp;
	}

	MvViolationDetecter* GetViolationDetctor()
	{
		return m_pViolationDetecter;
	}

#ifdef USE_DSP_CODE_FIND
	void mv_SetYdatetoIplImage( unsigned char *pYdate, int nWidth, int nHeight );
	IplImage *pYimage;	
#endif

	// -1δ֪��0�̵ƣ�1���/�Ƶơ�
	int LightColorDet(IplImage *img, IplImage *imgCmp, unsigned int uSeq);


	//dsp�ᴫ��������ͼƬ�Ƿ��Ǳ����Ƶ�ͼƬ���ڵ���DoAction֮ǰset�˱�־��Ϊ������ȡͼ��������
	//��ͼ��true����ͼ��false
	void SetShutterPictureFlag( bool ShutterFlag = false );

	//������Dsp�����������Ȧ����
	//��dsp��Ȧ������true����pc�ϵ���Ȧ������false
	void SetDspLoopShutter( bool bFlag = false );


	void SetRedLightStrenthForSingle( IplImage* img0, ChnFrmSignalStatusList cfss, int nShiftX, int nShiftY );

	void SetPressLineScale( float fscale = 0.2 );

	CvRect TransCheckShrinkToRio(CvRect Rec);//���ǵ�ѹ��ͼ���µ�����ת����ԭʼͼ��



	// 
	void DoAction(IplImage *img0, const std::vector<CarInfo> &vecCarNums, 
		ChnFrmSignalStatusList &sigStatusList, int64 ts, 
		unsigned int frameSeq, unsigned int uTimestamp, int imgIndex, 
		bool bCtrlCamera, std::vector<CarInfo> &ret, std::vector<ObjSyncData> &syncData, 
		std::vector<ViolationInfo> &vecElePoliceRet, StatResultList& listStatResult,
		int &bTrafficLightOn,
		unsigned int uMaxFrameSeq = 0, unsigned int uMinFrameSeq = 0); 

   void mvShowOutVio(const ViolationInfo &OutVio,char Imgpath[125],bool bSrcImg =true);
	

	// ��ȡ�����յ���ͼ��Ŀ��ߣ����أ�
	int       GetImageWidth() const;
	int       GetImageHeight() const;

	


	//ͨ���ͻ�������Ŀ����&�羯��Ҫ�Ĳ�����
	void      SetParaForVlpEle(const _ParaConfig &vlpPara);

	// ����ģʽ�����졢���ϡ�
	void      SetMode(Time_Mode mode);

	// ֡�ʡ�
	void      SetFrameRate(float fRate) const;
	

	// ������������
	void      SetInvalidRgns(std::list<MvPolygon> &rgns);

	void SetYelGridRgn(MvPolygon &YelGridrgn); 

	void SetVioRushTime(unsigned int uRushTime); 
	

	std::list<MvPolygon> GetInvalidRgns() const;


	void      SetCurrentAndModelGain( uchar uCurrentGain, uchar uModelGain );

	void      SetVideoStdlib( vector<mvvideostd> pVideoStd );



	// ����smear
	void      SetSmear(CvRect *pRects, int count);


	void      SetRedGreenScale( float fScale );


	


	// ���ü�����͡�
	// DO_CAR_NUM_DETECT���Ƽ�⡢DO_FIND_TARGET����Ŀ���⡢DO_ELE_POLICE���Ӿ��졣
	// ����SetDetectType(DO_CAR_NUM_DETECT | DO_FIND_TARGET);
	void      SetDetectType(unsigned int detType);

	//�����Ƿ�ʹ�ñ�����
	void SetLoopShutter( bool UseShutter );//true��ʾʹ�ã�Ĭ�ϲ�ʹ��

	void SetVideoShutter( bool UseShutter );//true��ʾʹ�ã�Ĭ�ϲ�ʹ��

	//void SetDropNonAutoMobile( bool bDrop );


	
	unsigned int GetDetectType() const;


	void      SetTrafficStatTime(const int nTrafficStatTime);

	// ���ñ궨��
	// nCount��corner������ÿ���ǵ�image,world����2ά��c1.x, c1.y, c2.x, c2.y.......
	void      SetCalibCorners(float *image, float *world, int nCount);


	// ����ͼ��ߴ�
	void      SetImageSize(int nWidth, int nHeight);

	// ���ó��Ƽ����ROI������������roi�趨�Լ���roi
	void      SetCarNumDetectROI(CvRect rectROI);
	
	// ���÷���
	// direction: 0��Զ������1�ɽ���Զ
	void      SetDirection(int direction=0);

	int       GetDirection() const
	{
		return m_nDirection;
	}
	

	void      SetColorDetector(ColorRecognisize *pColorDetector);




	//�����Ƿ���Ҫ�����ǿ�ͷ�������
	void      SetRedAndGreenStrongGlemd( bool bStrong, bool bGlemd, bool b_CheckLightByImage );

	//������Ƶ���������Ʒ���
	void      SetVideoShutterPar( vector<mvvideoshutterpar> videoshutterpar );

	// ���ó���
	void      SetChannels(const std::vector<ChannelRegion> &cs);

	// ����ֹͣ��
	void      SetStopLine(const MvLine &l);

	// ����ǰ�����
	void      SetForeLine(const MvLine &l);

	// �����Һ����
	void      SetRightLine(const MvLine &l);

	// ����������
	void      SetLeftLine(const MvLine &l);

	// ѹ��Υ���ߡ�
	void      SetYellowLine(const std::vector<MvLine> &vecYellowLines);

	// ѹ��ɫΥ���ߡ�
	void      SetWhiteLine(const std::vector<MvLine> &vecYellowLines);

	// ���ú�����򣬶��ڷ�Ƶ����Ʋ���Ҫ���á�
	void      SetRedLightRgn(RedLightTwinkRgn rgn);

	void      SetVideoShutterDelayFrame( int nDelayFrame = 3 );

	//��ȡΥ�¼������
	bool      GetViolationDetection()
	{
		return m_bViolationDetection;
	}

	// ������Ȧ��Ϣ���ڳ�ʼ��֮ǰ���á���ϵͳ������Ȧ���ɲ����á�
	// nDelay��ʾ���ڴ�����ʱ����ʱ��0
	void      SetPhysicLoop(const std::vector<_LoopInfo> &li, int nDelay = -92234);//-352000

	//�����״��⣡
	void      SetRadarDetection(CvRect rectROI, std::vector<int> radarRoadIndex);

	//�����״��ٶȣ�
	void      SetRadarSpeed(unsigned int frameSeq, long long timeStamp, double speed, double fastSpeed);
	// ÿ֡��֮��Ȧ״̬���ڵ���DoAction֮ǰ���á���ϵͳ������Ȧ���ɲ����á�
	// ����ж����������Ҫ��ε��á�
	// counterΪ������ֵ
	// tsΪϵͳʱ�䡣������DoAction��ts
	// b0��b1�ֱ�Ϊ���Ϊ0��1����Ȧ��״̬��true��ʾ�ߵ�ƽ
	void      SetPhysicLoopStatus(int nRoadIndex, bool b0, bool b1, long long counter, long long ts/*, unsigned int uFrameSeq*/);

	void      GetPhysicLoopStatus( vector<mvloopstatus> &nLoopStatus );

	void      _ScaleParas();
	// ��ʼ��
	void      Init();

	// destroy all the member objects.
	// invoke it after all operations have been done to release memory.
	void      Destroy();
	
	
	unsigned int GetMaxSeq() const
	{
		return m_uMaxSeq;
	}

	// ��ԭͼ�õ�check ������
	CvRect    GetCheckRoi() const;


	CvRect    GetVlpRoi() const;
	
	
	Time_Mode      GetMode() const;


	CvRect    GetCarNmRoi() const;

	void          GetCarNumRoiUpDownLines(MvLine &lnUp, MvLine &lnDown);

	MvPolygon  GetYelGridRgn()const; 

	unsigned int GetVioRushTime()const; 


	const std::vector<ChannelRegion>& GetChannels() const;


	void  mvGetSensObjChanel(CvRect Rgn ,int &nChanlIdex ,int &nChannelDir);


	


	//MvPhysicLoopManager* GetPhysicLoopManager() const;


	// 
	//void      TestOpticalFlowLK(IplImage *pCurFrame, IplImage *pLastFrame);
	
	
	// ����֡��ͼ��,���뵱ǰ֡ͼ��frameImage��
	// �÷����õ�ǰ֡����һ֡��������������䵽frameDiffImageͼ��
	void          GetFrameDiffImage(IplImage *frameImage, IplImage *frameDiffImage) const;


	// ��ȡͼ����С��������С��Ϊ�˼�����졣
	float         GetVlpScaleX() const;
	float         GetVlpScaleY() const;
	float         GetCheckScaleX() const;
	float         GetCheckScaleY() const;

	
	// �Ƿ���ǻ�������
	bool          GetDetectNonVehicle() const;
	void          SetDetectNonVehicle(bool bDetOrNot);

	
	// ��ȡ����ڴ���ͼ��ı궨����
	MyCalibration* GetCalibrationObject() const;


	MyCalibration* GetCheckImgCalibObj() const;


	VehicleFlowHelper* GetVehicleFlowHelper() const;


	MvPhysicLoop* GetPhysicLoopByRoadIndex(int nRoadIndex);


	MvBgLine* GetCheckImgLineBGM() const;


	ColorRecognisize* GetColorDetector() const;


	MvLineStorage *GetLineStorageObj() const;

	// ����ts��֡�š�����0��ʾ�ҵ�������-1��ʾ����tsС�ڼ�¼����С��ʱ�䣬����1��ʾts���ڼ�¼�е�����ʱ�䡣
	// tips������-1��ʾ������Ҫ�����¼����������1��ζ�Ź�һ����ȡ����ȡ����
	int          FindFrameSeq(int64 ts, unsigned int &seq, bool bBigOrSmall);

	int			 FindTimeByFrameSeq( unsigned int seq, int64 &ts, bool bBigOrSmall ) const;

	float GetEleScaleX() const
	{
		return m_fEleScaleX;
	}


	unsigned int GetDetype()const
	{
		return m_uDetectType;
	}
	float GetEleScaleY() const
	{
		return m_fEleScaleY;
	}

	int   GetCarPlateHeightOffGround() const
	{
		return m_nCarPlateHeightOFFGround;
	}
	// ��imgForegroundͼ���е�Ӱ��ȥ�������Ҽ�¼Ӱ������
	// imgCurFrame �ǵ�ǰ֡ͼ��imgBackground�Ǳ���ͼ��imgForeground�ǵ�ǰ֡�뱳���������ֵ���Ľ����
	// �÷�����imgForegroundͼ������Ӱ������ֵ��Ϊ0������¼��Ӱ����
	void          RemoveAndRecordShadow(IplImage *imgCurFrame, IplImage *imgBackground, 
									IplImage *imgForeground, std::vector<CvRect> &vecShadowRgn);


	// Rgb��֡���ǰ֡ͼ���뱳���Ƚϣ��������������������imgFore���أ�������û�б仯��������imgBack���ء�
	void          RgbDiff(const IplImage *imgCurFrame,const IplImage *imgBackGround, IplImage **imgFore, int nThreshold = 30, bool bMaxDiff = true, bool binv=false);


#ifdef   LGW_GOAL_IMG
	 static IplImage *gFramImg ;//��group�в���ʹ��
	 static CvRect    gcheckRegion;
	 // vlp ��֡ͼ���е�λ�ã������ԭͼ��
	 static CvRect    gvlpRegion;
	 static float Xsize;
	 static float Ysize;
#endif


	public:
		int64  m_Time;
		MvCorner **m_pCorPointerFm;//û�з���ռ�

		//Ϊ�������ԣ���Ȧ�����������ã���ֹ��Ȧ�����������
		float fLastSpeed;
		unsigned int m_nMinSeq;
	




private:

#ifdef SHOW_WINDOW
		void mvDescirGroupTrack(const IplImage* imgCornerRgb,const unsigned int frameSeq,
			const vector<MvTrack*> &vecTracks,const list<CvRect> &lstRectForDebug,
		const list<MvPolygon> &lstPolyForDebug,const vector <CvRect> &CarGroupParkRect,const vector<CarInfo> &vecCarNums);
#endif
   

	void mvDetCartype( IplImage*imgCornerRgb,  MyCalibration*pCalibCommon,const unsigned int frameSeq);

	void mvLineSegModel(IplImage* imgCorner,const unsigned int frameSeq);

	void mvGetTrackByDervieConer(vector<MvTrack*> &vecTracks,
		vector<MvTrack*> &vecEleTracks,
		MvCorner **vCorPointer,int &nCornerCount, 
		IplImage *imgGrayFrm, const unsigned int uFrameSeq,const int64 ts, const unsigned int uTimestamp,
		const  MyCalibration *pCalib, const MvMaxSize* pMaxSize,   const bool bVio_Target,
		const std::vector<CvRect> &CarGroupPark);

	//��ȡ�羯Υ���г���ͣ������Ϣ
	void GetVioPark(vector <CvRect> &CarGroupParkRect);

	//�������ǵ����
	void SetMaxCorner(int &nMaxCornerCount,const bool bViolation_Target);

	//��ȡ��Ӧͼ������
	void GetImg(IplImage *img0,IplImage * &vlpImage,IplImage * &imgCorner,IplImage * &imgCornerRgb);

	//��¼֡�ź�ʱ����Ϣ
	void RecordTimeAndSeq(const unsigned int frameSeq,const int64 ts);

	void VideoShutRecod(IplImage *img0,const unsigned int frameSeq,const int64 ts);

	//����Xml��¼��Ϣ
	void SaveDatabyXml( IplImage *img0,const vector<CarInfo> &vecTrueCarNums
		,const ChnFrmSignalStatusList &sigStatusList,const unsigned int frameSeq,const unsigned int uTimestamp
		,const int64 ts,const bool bCtrlCamera) ; 

	//��ȡ��������Ϣ
	void GetNoPlate(vector<CarInfo> &vecTrueCarNums, vector<CvRect> &vecDirtyPlates,const vector<CarInfo> &vecCarNums
		,unsigned int frameSeq,unsigned int uTimestamp);

	void      SetMaxMinSeq( unsigned int &uMaxFrameSeq, unsigned int uMinFrameSeq,unsigned int frameSeq);

	
	void mvGetParkTrackData(int &nParkingShortTrackAroundLongTracks,int &nLongTrackCount,
		int &nParkingLongTrackCount, const vector<MvTrack*> &vecTracks,unsigned int frameSeq,
		const bool bDoTarDet,const IplImage *imgCornerRgb);



	bool IsCameraTuned(IplImage *imgFrame);




	// ���ظ���Ȧ�����Ϣ�ͳ��Ƽ�SensedObj������
	void AssocPhyLoopInfoToCarSensedObj();

	void PhysicLoopOutput(unsigned int uFrameSeq, int64 ts, std::vector<CarInfo> &ret, std::vector<ObjSyncData> &syncData);


	//�ж�ͬһ�����Ƿ��ڲ�ͬ�����ȼ�����ƣ��ּ��*+++*����������򷵻�true������false��
	bool IsSameCarOnTwoLoops(const CarInfo &car, const vector<Car*> &cars, const vector<ChannelRegion> &cr, _MvUnion **pUnion, Car **pRetCar);


	//�����Ƿ񿿽���·�м���ʻ��
	bool IsCarOnBetweenRoads(const Car *pCar, int nCurRoad, int nLoopRoad, const vector<ChannelRegion> &cr);

	void          DoTargetDetect( IplImage *vlpImage, IplImage* pCheck, IplImage* pRgbCheck, 
								std::vector<MvTrack*> vecTracks, MvCorner* vCors[], int nCorCount, 
								int nLongTrackCount, int nParkingLongTrackCount, int nParkingShortTrackAroundLongTracks,
								unsigned int uFrameSeq,
								unsigned int uMaxFrameSeq, int64 ts, 
								unsigned int uTimestamp, int nImageIndex, bool bCtrlCamera, 
								std::vector<CarInfo> &ret, std::vector<ObjSyncData> &syncData );


	void          DoElePolice();

	
	// ��ͼ�ϻ����Ӿ���������ߺͳ�����һ�����ڵ��ԡ�
	void          DrawLinesAndChannelRegion(IplImage *img);


	//
	void          DrawChannelRegions(IplImage *img);

	







	// ����sobel��Եͼ��
	//void          GetSobelImage(IplImage *frameImage, IplImage **sobelImage);


	// ��ȡ������Ȧ��λͼ��
	IplImage*     GetVlpImage(IplImage *frame,CvPoint TranPoint= cvPoint(0,0));


	// ��ȡcheck��λͼ��
	void          GetCheckImage(IplImage *img0Resized, IplImage **imgCheckGray, IplImage **imgCheckRgb
		,CvPoint TranPoint= cvPoint(0,0));

	// ����ͼ��rect���ڵ����ء�ʹ��Ϊ0
	//void          ClearRects(IplImage *img, const vector<CvRect> &rects);

	// ����vlp��ԭͼ�е�λ��
	//void          SetVlpRegion(const CvRect &vlpRegion, const CvRect &sobelRegion);

	

	// ���ڲ����κγ�����ĳ���������һ�³�����Ϣ��ѡ��һ���������ĳ�����
	void          FixRoadIndex(CarInfo &ci);

	void          FixSpeed(CarInfo &ci);


	// sobel image OR diff image
	//void          CombineSobelAndFrameDiffImage(IplImage* sobelImage, IplImage *frameDiffImage, IplImage **destImage);


	// check foreground rects using checking rects
	//void          CombineForegroundRectsAndCheckRects(vector<CvRect> foregroundRects, vector<CvRect> checkRects, vector<CvRect> &result);

	// map the rects in check image to vlp image
	void          MapCheckRects(std::vector<CvRect> &rects);

	// find lines in img using hough transform
	//void          GetLines(IplImage *img, vector<CvPoint> &ret);

	// clear lines in image
	//void          ClearAlongLines(IplImage *img, vector<CvPoint> lines); 

	// �����ڷ�����������Ƶ�����֡�ű�С�����³�ʼ������������������б���Init�����Զ���ReInit
	void          ReInit();

	// �ڴ���ͼ�����Сͼ��ԭͼ����checkscale��С���Ͻ���������Ϳ�ڡ�
	void          ZeroUsingInvalidRgn(IplImage *img,CvPoint TranPoint= cvPoint(0,0));

	//Ϊ�������ȡ�ǵ�׼��Maskͼ�������Ч�ʣ�
	bool          _GetMaskForCornersExtraction(IplImage *maskImg);

	//void          GetCarNumRoiUpDownLines(MvLine &lnUp, MvLine &lnDown);

	//�жϺ�ѡ���Ƴ��ǲ������������Ƶ��µģ�
	bool          GetLikelyDirtyPlate(const SensedObject *pOutputObj, CvRect objPos, map<int, vector<CvRect> > mapDirtyPlates);

	
	public:

	    IplImage *m_pInVaildMaskImg;

		MvMaxSize*     GetMaxSize()
		{
			return m_pMaxSizeCommon;
		}
			CvRect m_ParkRec ;
			int m_nVlpCarWidth;
			bool m_bNOParBacUpd;


			// �ں������֮���m_nRedLightViolationAllowance֡����һ��ʱ�䴳��ƵĲ��㡣
			int                 m_nRedLightViolationAllowance;
		OpticalFlowHelper *      m_pOpticalFlowHeler;
		inline bool mvGetDoEleVio()
		{
			return m_bVioRedLightWithViolation;
		}
		// �羯Υ�¼������
		MvViolationDetecter  * mvGetEleObject()
		{
			return m_pViolationDetecter;
		}

#ifdef TRACK_GROUP_LGW
		void mvGroupUpdatCar(const unsigned int frameSeq);
		void mvGroupAssoCar(const unsigned int frameSeq,vector<MvTrack*> &vecTracks,vector<OpticalFlowHelper::FlowSetInfo>&vecFlowSets);
#endif

private:
	
	IplImage           *m_preditImg;
	//int              m_nLastCID;
	CvRect             m_VlpAradRec;

	int                m_nDelayFrame;

	bool               bDspLoopFlag;//dsp������־
	bool               bShutterFlag;//Ϊdsp��������ͼ�Ƿ��Ǳ����Ƶ�ͼ��ǡ�dspר��
	
	ColorRecognisize * m_pColorDetector;

	//ΪSurfƥ�仺����֡ͼ���ܲ�������m_pLastFrame?����Сͼ��
	IplImage         *m_PreviousImg[2];  //��ǰͼ���ǰ��֡ͼ�񣬻Ҷ�ͼ����ʱ��ԭͼ��
	int64			  m_lastTimeStamp[2];  //ʱ�䣡
	unsigned int      m_uLastFrm[2];   //��֡֡�ţ�

	//////////////////////////////////////////////////////////////////////////
	//                         ����ģʽ�޹ص�
	//////////////////////////////////////////////////////////////////////////



	//
	unsigned int     m_uCornerBgmLastUpdateSeq;


	bool             m_UseShutter;
	bool             m_UseVideoShutter;

	uchar			 m_ModelGain;
	uchar			 m_CurrentGain;


	int64           m_FramCout;

	float           m_fScale; 

	//
	//int              m_nLastOutputId;
	bool             m_bRoadStat;


	// ����ԭͼ�Ŀ��
	int              m_nImageWidth;


	// ����ԭͼ�ĸ߶�
	int              m_nImageHeight;



	// �궨�ǵ����ꡣ����ڴ���ͼ��
	double           m_calibCornerImage[20];
	double           m_calibCornerWorld[20];
	int              m_nCalibCornerCount;


	// 춷崫�ݸ��ҵĳ��Ƽ����
	CvRect           m_roiCarNum;


	// 춷崫�ݸ��ҵĳ��Ƽ����
	MvPolygon           m_YelGridRgn;
    unsigned int     m_VioRushTime;        //��Ϊ��λ


	//�״���ٵļ��������Ӧ�ö˴��룡
	CvRect           m_rectOverlap;
	std::vector<int> m_vecRadarDetectionRoadIndex;  //�״︲�ǵļ�⳵����
	// ����ģʽ��ҹ��or���졣0���죬1ҹ��
	Time_Mode             m_mode;

	//Time_Mode             m_prevMode;


	// ����ǰ�ƣ���Զ������Ϊ0�����棨�ӽ���Զ��Ϊ1
	int              m_nDirection;


	

	// ��������
	std::list<MvPolygon>  m_lstInvalidRgns;


	// ��������Ϊ0������������Ϊ1.
	//IplImage*        m_pValidMask;


	//mask��������ȡ�ǵ㣬��ʱֻ���ڴ�����������ǰ���ߡ���ת�ߡ���ת�߹������
	IplImage         *m_maskGrayImg;
	bool              m_bUseMaskImg;
	bool              m_bGotMaskImg;
	// ������ʽ.�μ�DetectType.h
	unsigned int     m_uDetectType;

	RoadStatistic*   m_pRoadStat;


	int              m_nTrafficStatTime;

	int              m_nLastOutputTimestamp;




	//
	//MvPhysicLoopManager* m_pPhysicLoopManager;
	MvLoopManager*   m_pLoopManager;
	bool             m_bDoPhysicLoop;
	std::vector<_LoopInfo> m_vecLoopInfo;
	int              m_nLoopDelay;
	bool             m_bMultiChannels;  //�Ƿ�Ϊ�೵�������ڽ��ͬһ�����ڲ�ͬ�����ȼ�����ƣ��ּ��*+++*�����⣡
	//�״����
	MvRadarSpeed *   m_pRadarSpeed;  //�ٶ�map!
	bool m_bDoRadarSpeed;  //�״���٣�
	bool m_bRadarParaValid;  //�״���������Ƿ���Ч����Ч�����״��⣡
	

	//// ts->uFrameSeq
	//std::map<int64, unsigned int> m_mapTsToSeq;
	std::deque<int64> *m_ts;
	std::deque<unsigned int> *m_seq;

	//MvDeque<int> *m_queue;


	MvUnionManager *         m_pUnionManager;


	std::map<int, int> m_mapUnionIdToObjId;
	int m_nNextObjId;

	// �Ѿ�����˵ĳ�����
	std::map<int, _CarInfo> m_mapOutputedVehicle;

	//��¼ÿ֡����������ƣ������ж����Ƴ��Ƿ���ţ�
	std::map<int, vector<CvRect> > m_mapDirtyPlates;

	// ��¼Ӧ�ô����������ݵ��ļ�����
	std::ofstream*          m_ofsRecordParas;
	std::ofstream          *m_ofsDirtyPlates;  //��¼��������Ϣ�������ж����Ƴ���


	// �ǵ㡢�켣�㡣
	MvCornerLayer*          m_pCornerLayerCommon;
	MvTrackLayer*           m_pTrackLayerCommon;
	MyCalibration*          m_pCalibCommon;
	MvMaxSize*              m_pMaxSizeCommon;

	VibeModel  m_VibelModel;
	IplImage   *m_VlpBakImg;
	IplImage   *m_vlpForImg;



	


	



	// ���ǵ��ͼ����С�ģ��ϵ�ֱ�߱���ģ�͡�
	MvBgLine*         m_pLineBGM;
	


	MvLineMerge*      m_pLineMerge;
	

	
	bool              m_bFilterSideVlpObj;  //�Ƿ����Ʊ߽߱ǽǵ�*****Ŀ�꣡

	
	//////////////////////////////////////////////////////////////////////////
	//                       ���Ӿ����
	//////////////////////////////////////////////////////////////////////////

	// ���Ӿ���ĸ����ߣ�����ڵ羯��Сͼ��
	MvLine           m_stopLine;
	MvLine           m_foreLine;
	MvLine           m_rightLine;
	MvLine           m_leftLine;


	MvLine           m_stopLineOri;
	MvLine           m_foreLineOri;
	MvLine           m_rightLineOri;
	MvLine           m_leftLineOri;

	std::vector<MvLine> m_vecYellowLine;

	std::vector<MvLine> m_vecWhiteLine;


	std::vector<MvLine> m_vecBianDaoXian;


	// �羯Υ�¼������
	MvViolationDetecter  *m_pViolationDetecter;

	// �羯ͼ�ϵ�maxsize
	MvMaxSize*       m_pMaxSize;

	// ���Ӿ���ǵ㡢��ȡͼ�����űȡ�
	float            m_fEleScaleX;
	float            m_fEleScaleY;

	// ���Ӿ���ı궨����
	//MyCalibration*   m_pEleCalib;



	// ���Ӿ���
	//MvCornerLayer       *m_pCornerLayer;

	// ���Ӿ���
	//MvTrackLayer        *m_pTrackLayer;

	// ���Ӿ���
	MvGroupLayer        *m_pGroupLayer;

	// ���Ӿ���
	MvLightStatusMem    *m_pLightStatusMem;


	CMyVideoStabilizer4Client m_videostabilizer;

	//CVideoStabilizer  m_cStab;

	// 
	//MvCarPlateTracker   *m_pCarPlateTracker;


	//��û����Υ�¼�⣡
	bool                m_bViolationDetection;
	bool                m_bVioRedLightWithViolation;
	bool                m_bElepoliceParaValid;  //Υ������û�����úõȣ�
	//////////////////////////////////////////////////////////////////////////
	//                       ������ص�
	//////////////////////////////////////////////////////////////////////////
	
	RoadTypeDetector* m_pRoadTypeDet;



	// ����ģ��״̬��1�ڣ�2�ڣ�3�ڡ�
	int               m_nBgmStatus;
	unsigned int      m_uLastCameraControlSeq;

	
	// Ŀ�����õĽǵ����켣�㡣
	// ������ã����ܽ��������Ϊ���Ӿ���Ϳ��ڹ��á���ʱ�����š�
	//MvCornerLayer*    m_pCornerLayerFtg;


	//MvTrackLayer*     m_pTrackLayerFtg;

	// checkͼ��ı궨��Сͼ����
	//MyCalibration*    m_pCalibCheck;


	// stores smear position.��ʱû��ʹ�á�
	//std::vector<CvRect>    m_vecSmear;


	//unsigned int      m_uLastBgmUpdateSeq;

	

	//Surfƥ��������Ƶ�ٶȣ�
	MvSurf			*m_pSurf;
	int             m_nCarPlateHeightOFFGround;  //�����������ͼ��߶�!

      

	
	// �궨����, ����ڴ���ԭͼ��
	MyCalibration*    m_pCalibOri;


	// checkͼ�ϵ�maxsize��
	MvMaxSize*       m_pMaxSizeFtg;

	// ����ģ�Ͷ���
	IBackgroundModel* m_bgm;

	unsigned int      m_uBgmLastUpdatedSeq;


	float m_fScalWidht;//����ѹ���ϵİٷֱ�


	//tmp
	//bool m_bBgmValid;


	IBackgroundModel* m_pLongTermBgm;
	unsigned int      m_uLastUpdateLongTermBgmSeq;


	// ������Ȧ����
	VirtualLoop*      m_vlp;

	//int               m_nBgUpdateRate;


    
	// check ���������ԭͼ������ǵ������ͨ����ԭͼ����2/3
	CvRect            m_checkRegion;
	
	// vlp ��֡ͼ���е�λ�ã������ԭͼ��
	CvRect            m_vlpRegion;
	
	// ��һ֡ͼ������֡����
	IplImage*         m_pLastFrame;

	// ���ͼ��Buffer
	IplImage*         m_diffImage;

	// checkImage���ű���x
	double            m_dCheckImageScaleX;
	
	// checkImage���ű���y
	double            m_dCheckImageScaleY;

	// vlp image�Ŵ�ϵ��
	double            m_dVlpImageScaleX;
	
	// vlp image�Ŵ�ϵ��
	double            m_dVlpImageScaleY;


	// �������Ƿ���ǻ����������Ϊfalse������ǻ���
	bool              m_bDetectNonVehicle;

	//�Ƿ������Ƴ���
	bool              m_bDoNonPlateDetect;

	// 
	VehicleFlowHelper* m_pVehicleFlowHelper;


	// ���Ը����жϱ����Ƿ�ͻ�䣨ʧЧ��
	//BgStatistic*      m_pBgStatistic;

	

	//��ȡֱ�ߵĸ��ã�
	MvLineStorage    *m_pLineStorage;

	// ֱ�߱���ģ���Ƿ���ù����º�����
	bool              m_bCheckImgLineBgmUpdated;

	unsigned int      m_uLastCheckImgLineBgmUpdatedSeq;


	CornerBackgroundModel<CvPoint2D32f> *m_pCornerBGM;


	//��Ȧ�쳣������
	int m_nLoopCounters[ROADINDEX_BUFFER_SIZE][4];//���֧��5������,ÿ��������Ȧ���ĸ�״̬0������ 1����Ȧ0�쳣 2����Ȧ1�쳣 3����Ȧȫ���쳣


	Cshadow m_shadow;


	//////////////////////////////////////////////////////////////////////////
	// ��ֹ��������ܡ�
	//////////////////////////////////////////////////////////////////////////

	//MvLightTwinklingPreventer* m_pLightTwinklingPreventer;
	//CvRect                     m_TwinklingRgn;
	MvLightTwinklingPreventer* m_redLightHelper;
	MvLightTwinklingPreventer* m_greenLightHelper;


	// �Ƿ�����ֹ�������ܡ�
	//bool              m_bPreventLightFlash;

	// Ϊ�����Ŀ��ʱ��ӣ���Ҫ���ơ���ͨ�����෽�򣬶��ֺ����ʻ��
	//CvRect            m_RedLightRegion;


	// �������Ҷȡ�
	//std::vector<float>  m_vecLightRgnGrayRecord;

	//int               m_lightThreshold;

	// ֡��->���Ƿ��������ܺ��̣�
	//std::map<unsigned int, bool>  m_mapLightOn;

public:

		CarManager*       m_pCarManager; 
		vector<ViolationInfo> m_vecarViocod;//������¼����û�й���Group��ɾ���ó��Ƶı���
	  // ����,�羯�á���С�ġ�
	  std::vector<ChannelRegion> m_vecChannels;

		//���ұ�����ͼƬ
		Mv_LoopShutterLight*  m_pLoopShutterLight;

		bool m_bStrong;
		bool m_bGlemd;
		bool m_bCheckLightByImage;

		//������ص�
		int m_RegNum;
		int *pPointNumber;
		CvPoint2D32f **pPointStorage;
		std::ofstream*          m_ofsSpeedParas;
		MvGroupLayer    *GetGroupLayer()
		{
			return	m_pGroupLayer;
		}


public :
	vector<CvRect> m_GroupArea;
	// �������³�ʼ��
	unsigned int     m_uLastFrameSeq;
	mvobjpar   m_ParObj;
	bool       m_bInitBacSuc;
	bool       m_vlPark;
	unsigned int  m_LastUpDataParkTime;
	bool         m_bFulDark;
	bool      m_bigPass;
	bool GetMostCloseLightOnFrame(unsigned int uFrameSeq, unsigned int &uLightOnSeq);
	// ����,û��С��
	std::vector<ChannelRegion> m_vecChannelsOri;
	IplImage *m_pinValidImg;
	bool  m_bTailMov;

private:

    CvRect TransHeadPsToNoVelPos(CvRect Headpos,bool bForPlat);
	void SaveSettings();

	void mvGetX86Version(char *ver);

	// pCalib����ڴ����ͼ�ı궨��
	void _InitCheckRgnAndVlpRgn(MyCalibration* pCalib);

	void _InitSaveCalibCorners();




	// ͬʱ��⿨����羯ʱ��Ϊ�˹��ù켣�����ڵļ�������Զ�����
	// ��ʱ��������ɲ�߲�û�о������Ƽ������Ķ౨��
	// �ú����жϵ��Ƿ���������౨���򡱡�
	// tips�����������С��ͼ����ͬʱ���ʱ����С������ͬ��
	bool IsPointInExRgn(int x, int y);

	// ���������Ȧ�ϵġ��౨���򡱡�
	// vlpImage����С��ġ�
	void ClearVlpExRgn(IplImage* vlpImage);

	

public:
	void SetBianDaoXian(const std::vector<MvLine> &vecBianDaoXian);

private:

	// ���ͬ�������ǲ��Ǵ���
	bool m_bSyncOn;

	// �Ƿ����ͼ��������Ŀ����ˡ�
	// �����������Ը���ֱ�ߺ�ȷ�����ж���С������͡������Ĺ��˵����������
	bool m_bFilterOutSideMotorizedVehicle;


public:

	// ��֪���ͬ����û�д򿪡�False��û�򿪡�
	void SetSyncSwitch(bool bOnOrOff = false);

	// ����m_bFilterOutSideMotorizedVehicle����
	bool GetFilterOutSide();

	void ClearObjPar();
	unsigned int mvGetReasonFram(unsigned int uFram)const;


	CvRect GetCarNumRoi() const
	{
		return m_roiCarNum;
	}
private:

	


	unsigned int m_uMaxSeq;

	float        m_fFixedVeilcheLength;


	//OnBusVioDet* m_pOnBusVioDetector;


	bool      m_bOutPutNonAutoMobile;

private:

	void mvJudeOutPut(SensedObject* pOutputObj,vector<CarInfo> &ret, vector<ObjSyncData> &syncData,unsigned int frameSeq);
	void mvSenseOutPut(SensedObject* pOutputObj,vector<CarInfo> &ret, vector<ObjSyncData> &syncData,unsigned int frameSeq);

	bool DetermineWhetherOutputForFtgObj(SensedObject* pObj, MyCalibration* pCalib);
	
	//����Tsai�궨��ó���������ͼ��߶ȣ�
	void _CalcCarPlateHeightOffGround();

	void mvSetCorossLineByCarRio();

private:
	RedLightTwinkRgn m_RPTR;  //û�ã�

//	std::vector<RedLightFixer*> m_pRLF;
	_ParaConfig m_InputParas;


public:
	RedLightFixer** m_pRLF; 
	//�洢SensedObjectĿ����ٶȣ�
	FILE *m_pFILESaveSpeed;
	map <int,int64>m_PassChanlTime;
	
public:
	MvLine m_CrossSedLin;//��������������-����ѹ�ڶ��� --���ǰ��
	MvLine m_CrossFriLin;//��������������--����ѹ��һ��---���ǰ��

	MvLine m_EleCrossSedLin;//��������������-�羯�ڶ��� --���β��
	MvLine m_EleCrossFriLin;//��������������--�羯ѹ��һ��---���β��


	CvRect m_CheckCarNumRio;
	CvMemStorage* m_pstorage; 
	CvSeq* m_point_seq; 
	float m_fline[2];
	bool  m_bLoopLearnSucces;
	IplImage *m_pChanlImg;
	IplImage *m_pLasCarGrayImg;
	int   m_CarRioY;//����������������cheakͼ�ϵ�
	vector<int> m_vecplatWid;//ͳ�Ƴ��ƵĴ�С;
	int m_CarMidWidth;
	unsigned int m_presFram[STORE_FRAMES];
	int m_Stroepos;

	
	

};

#endif



















