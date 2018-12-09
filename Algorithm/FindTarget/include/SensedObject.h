// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef SENSEDOBJCT_H
#define SENSEDOBJCT_H

#include <vector>
#include <cxcore.h>

#include "StdAfx.h"
#include "ObjectColor.h"
//#include "MvLineSegment.h"
#include "SynCharData.h"
#include "CarInfo.h"
#include "MvChannelRegion.h"
//#include "MvGroup.h"
#include "Mode.h"



//using namespace std;
//#include<map>

struct _MvGroup;
class Car;
class VirtualLoop;
class VehicleFlowHelper;
class OpticalFlowHelper;

typedef struct _TrackIndexGrop
{
	vector<int> TrackIdex;
	CvRect  FlowRec;
	_TrackIndexGrop()
	{
		FlowRec =cvRect(0,0,1,1);
	}
}MvTrackIndexGrop;


#define MAXLIGSUM  7

typedef struct _SenesedObjectTrackData
{
	unsigned int  uTimestamp;//for yufeng
	unsigned int  frameNo;
	CvRect        pos;
	CvRect        LastByFlowPos;//���vlp��ûѹ��������
	int64         ts;
	//int           imgIndex;  //for yufeng
	float         dflow;

	// ��ɫ����ɫ���Ŷȡ�
	object_color  objColor;
	float         fObjColorCredit;
	
	float         fSpeedX;
	float         fSpeedY;

	CvRect        headPos;

	// Ϊ�ù켣�����׵ģ����û�У���ȫ0
	CvRect        flowRect;
	float         fMovLen;
	int           nTrackNum;
	CvPoint       CarPlatCen;


	std::vector<unsigned short> colorHist;


	_SenesedObjectTrackData()
	{
		//bTrustable = false;
		dflow   = 0.0f;
		fSpeedX = 0.0f;
		fSpeedY = 0.0f;
		objColor.nColor1 = 0;
		flowRect = cvRect(0, 0, 0, 0);
		LastByFlowPos = cvRect(0, 0, 0, 0);
		uTimestamp = 0;
		ts = 0;
		fMovLen =0.0;
		nTrackNum = 0;
		CarPlatCen = cvPoint(0,0);
	}


} SensedObjectTrackData;


typedef struct _BusTopInf
 {
	
	 bool TopStart;
	 double TopCol;
	 bool bAwayVlp;
	 _BusTopInf()
	 {
		 TopCol = 0;
		 TopStart = false;
		 bAwayVlp = false;
	 }
	 

}BusTopInf;

enum ObjType
{
	UNKONOWN, NONVEICHLE, CAR, BUS
};


class SensedObject
{

public:

	#ifdef DO_DONGS_CODE

		// ���ϵĴ�β�� -1δ���㡣0���ǡ�1�ǡ� 2��ȷ����
		int m_nBigCarTailN;

		//�Ƿ��Ǵ󳵵ĳ�β��-1δ���㡣0���ǡ�1�ǡ� 2��ȷ����
		int m_nBigCarTail;

		// �Ƿ��Ǳ��ϵĴ󳵡�-1δ���㡣0���ǡ�1�ǡ�
		int m_nSideBigVeichle;

		//�����м����ϱ���ֹ������
		float m_fFAN;

		//�м��ʣ�������
		float m_fFBN;

		//�м����ϱ���ֹʱ������
		float m_fFA;

		//�м��ʣ�������
		float m_fFB;

		// ���ϴ���ϵ�����ֹʱ�̵�������
		float m_fSiderBigVeichleFlowA;

		// ���ϴ���ϵ�����ֹʱ�̼��������ϸó���Ӧ���ۼƵ�������
		float m_fSideBigVeichleLeftFlow;

	#endif
	int          m_nSerZeroFlow;
	bool         m_bPark;
	bool         m_CarSpeedCut;
    bool         m_CarNearBus;

    bool         m_bReltionWithBehind;

    CvRect        m_FiStCarVlprect;

	bool          m_bCarVary;
	BusTopInf     m_BusTopinf;
	int           m_nShadowNum;
	vector <CvRect>  m_forSortRgn;
	bool       m_bPermiAssocCar;

	int m_nTrackSize;
	bool m_ArodExObj;//ҹ���
	bool m_bLap;
	bool m_bNearObj;
	bool m_bNearCar;
	int  m_CutbyFlow;
	int  m_nForType;

	MvTrackIndexGrop TrackInf;

	bool m_bBus;
	int  m_nFlowNum;
	int  m_nAppearNum;


	// Ŀ��ͷλ�ã������ԭͼ��
	CvRect m_rectHeadPos;

	//object_color color;//��color
	bool   m_bBelongsToPreviousObj;
	//int    m_nCenter;           //����
	//int    m_nWidth;            //���
	//CvRect   m_rectMostLikelyPos; //obj��vlp�����п��ܵ�λ�á�ÿ������µĹ켣ʱ���¡�

	double fObjTotalFlow;//����
	
	int    id;
	Car*   AssocCar;

	int   m_LigApearSum[MAXLIGSUM];
	int   m_nLastlig;
	int   m_nSerNoLig;
	bool  m_bicyle;
    CvRect  m_MaxWidRect;
	float   m_Angle;

	float m_fSpdX;
	float m_fSpdY;
	int  m_nObjWidth;
	int  m_nCArWidNum;

	// ����HOG�г��͡�����ֻ�������ǲ��Ƿǻ���
	int      m_nVehicleTypeByHog;//-2�����ǣ�-1δ���㣬0�ǻ���1�󳵣�2С����


	// ������ֱ���жϳ��͡�-2�����ǣ�-1δ���㣬0�ǻ���1�󳵣�2С��
	int      m_nVeichleTypeByLines;

	// ������ֱ���жϳ��͡�-2�����ǣ�-1δ���㣬0�ǻ���1�󳵣�2С��
	int      m_nVehicleTypeByLinesWeekModel;

	
	// ����ó����жϳ��͡�-2�в�����-1δ�С�1�󳵡�2С����
	// ֻ�ڳ��Ƴ���ʱ�ж�һ�Ρ�
	int      m_nVeichleTypeByHeadLight;

	float    m_aColorMean[3];
	float    m_aColorVariance[3];

	/*
	��ʾ��obj�����ٱ����¹켣
	*/
	bool isSealed;


	// ֱ���г���ʱ�õ��ĳ�������λ�á�
	int           vt_x1;
	int           vt_x2;

    //
	// ����ģʽ��ҹ��or���졣1���죬0ҹ��
	bool    ObjSenDay;

    bool          IsBusPart(); 
	void          GetObjAvgSpeed(float &vx, float &vy) const;
	
	bool          IsBelongsToPreviousObj();
	void          SetBelongsToPreviousObj();

	int           GetRoadIndex(const std::vector<ChannelRegion> &channelOri, CvRect vlpRegion) const;

	bool          IsDetectedInTimePeriod(int64 from, int64 to) const;


	std::vector<SensedObjectTrackData> track;


	// ���ڹ���ͼ�����߻�������
	bool          m_bSideMotorized;

	int          m_Dirction;


	//���ڹ���*****Ŀ��౨��
	bool          m_bFirstOutput;
	int64         m_firstTime;
	bool          m_bOverTime;  //�ȴ���һ������ʱ���Ƿ�ʱ��
	bool          m_bLongTimeZeroFlowSeal;  //���*******�����ǲ����ɳ�ʱ���������ϵģ������������Ƴ���*******�౨��
	bool		  m_bReviseCarNumSeal;  //���*******�����ǲ�����ReviseCarNum�ϵģ������������Ƴ��౨��

	bool          m_bAssocCarHis;  //Ŀǰÿ��Carֻ�ܹ���һ��SensedObject���Ϳ�����ɶ౨����˼�һ���ж��Ƿ���������ӵı����������ƶ౨��

	bool          m_bAwayVlp;
	bool          m_AssocCut;
	bool          m_bMayAwayVlp;
	unsigned int  m_nBusAwayfmq;
	int           m_BicyWidSum;

   
public:


	SensedObject(VirtualLoop* vlp);
	~SensedObject();

	void          NotifyDelete() const;
	void          ClearAssocCar();
	Car*          GetAssocCar() const;

	int           GetTrackCount() const;
	void          SetAssocCar(Car* pCar);
	int           GetMosLikyLig()const;
	void          SetAssocCarHis()
	{
		m_bAssocCarHis = true;
	}

	bool          GetCarMayAwayStat()const
	{
		 return m_bMayAwayVlp;
	}

	void          SetCarMayAwayStat()
	{
		m_bMayAwayVlp = true;
	}

	bool          GetCarAssocCutSate() const
	{
		return    m_AssocCut;
	}

	void          SetCarAssocCutSate() 
	{
		         m_AssocCut = true;
	}
	bool          GetCarAwaySate() const
	{
		return    m_bAwayVlp;
	}

	void          SetCarAwaySate()
	{
		   m_bAwayVlp = true;
	}

	bool          GetAssocCarHis() const
	{
    	return m_bAssocCarHis;
	}

	object_color  GetMostLikelyColor(std::vector<unsigned short> &uColorResult) const;

	void          AppendTrack(const SensedObjectTrackData &track);

	// �������ͬ��
	void          GetSyncData(ObjSyncData &objSyncData ) const;

	
	//void MergeSensedObj();

	//��������ȷ����ʻ����
	int			  JudgeDirectionByFlow();

	// �ڹ켣�����ʺ���Ϊ����ļ�¼����ֹ���ص�֡�Ѿ�����Ӧ�ó��򻺴���
	bool          GetOutputTrack(unsigned int uCurFrameSeq, SensedObjectTrackData &ret) const;

	// �ڹ켣�����ʺ���Ϊ����ļ�¼����ֹ���ص�֡�Ѿ�����Ӧ�ó��򻺴���
	void          GetOutputTrack (SensedObjectTrackData &ret) const;
	//����ʱȡͼ��
	void		  GetOutputTrackForShutter(unsigned int uBrightFrmSeq, SensedObjectTrackData &ret) const;
	bool          GetReported() const;
	void          SetReported();
	bool          GetNeedReport(unsigned int nFrameSeq, VehicleFlowHelper *pFlowHelper,bool bShut =false) ;
	void          SetNeedReport();
	unsigned int  GetLastUpdateFrameSeq() const;
	int64         GetLastUpdateTimestamp() const;

	
	// ���ݿ�ȼ���Ŀ�����͡�
	ObjType       GetObjType() const;

	//���ۺ�ֱ�ߡ�HOG����ȡ��ƹ⡢���ơ��жϳ��͡�
	ObjType       GetObjType2(Time_Mode mode) const;


	CvRect        GetFirstTrackRect() const;

	int           GetSensedObjWidth() const;

	CvRect        GetMostWideRect() const;

	//void          CombineAnother(SensedObject *pObj);


	int64         GetFirstTrackTs() const;

	int64         GetLastTrackTs() const;


	// ����켣��Ⱦ�ֵ��
	float         GetTrackWidthMean() const;

	// ����켣��ȵķ��
	float         GetTrackWidthVariance(float fMean) const;

	// �����ж�Ŀ���Ƿ������0������¼ʹ�á����ڷ�ֹͣ��ʱÿ֡���������˷�ʱ�䡣����ֻÿ��һ��֡�����жϡ�
	unsigned int uLastFrameSeqManyZeroFlowTrack;


	// Ŀ���Ƿ������0�����ļ�¼��
	bool          IsObjectHaveManyFlowZeroTrack(int thresh, unsigned int uFrameSeq);

	// ȡ��bus��ǰѹ�ߵ�λ�á�
	bool          GetBusCurMostLikelyPos(CvRect &ret);
	

	//bool          TryCombineAnotherObj(SensedObject* pObjB);

	SensedObjectTrackData GetFirstTrack() const;
	SensedObjectTrackData GetLastTrack() const;
	SensedObjectTrackData GetFlowFirstTrack() const;
	SensedObjectTrackData GetVlpFlowLastTrack() const;

	// ��ȡ��÷�ӦsensedObject��������Ȧ��λ�õ�Rect
	bool          GetMostLikelyRect(CvRect &ret) const;

	CvRect        GetCodeRect() const;

	static  bool  IsTwoObjCloseByPos(const SensedObject& obj1, const SensedObject &obj2);
	
	void          SetTimeOutDrop();
	bool          GetTimeOutDrop();

	void          WriteObject(std::ofstream &ofs);


	bool          IsColorChanged(IplImage *imgCheck);

	bool          GetIsWaitColorChangeSeal() const;

	void          SetWaitColorChangeSeal();


	void          SetWaitColorChangeSealRgn(const std::vector<CvRect> &rgn, IplImage* img);

	void          DrawWaitColorChangeSealRgn( IplImage *img , CvScalar color);

	bool          GetFlowRectMeanVar(int nCount, CvRect &mean, float &var1, float &var2, float &var3, float &var4);


	bool          GetLastFlowRect(CvRect &rect) const;

	// ��ÿһ֡��flowRect����ͼ�ϡ�
	void          DrawFlowRectHistory( IplImage* img, int nCount, float sx = 1.0, float sy = 1.0 );
	bool          IsGettingWide() const;

public:

	_MvGroup*     GetAssocGroup() const
	{
		return AssocGroup;
	}

	void          SetAssocGroup(_MvGroup *group)
	{
		AssocGroup = group;
	}


    bool          m_bTrackLRSim;
	int           m_nAwaCarRioNum;
	bool          m_bVlpLow;
    bool          m_DriCom;  
	int           m_nType;//-1δ֪��0�ǻ�������1��������2�����ͳ���3��
	bool          m_bTochBtm;//�ж��Ƿ�Ӵ��ײ�
	unsigned int  m_TochBotmFram;
	bool          m_bFake;
	bool          m_bParkIng;
	int  m_nCodeIndex;
	int  m_nTempCodeIndex;
	int m_nChanel;
	int m_nChanDir;
	int           m_nLigNum;
	vector<int> m_LastTrack;
	

private:	

	CvRect        CalcMostLikelyRect() const;
	
	// ���Ŀ���ǲ��Ǵ��ڵ���ɫ�仯�Ͷϵ�״̬��
	bool          m_bWaitColorChangeSeal;

	std::vector<CvRect> m_vecStatColorRgn;

	//
	std::vector<float>   m_vecColorRed;

	//
	std::vector<float>   m_vecColorGreen;

	//
	std::vector<float>   m_vecColorBlue;

	std::vector<float>   m_vecColorHue;
	std::vector<float>   m_vecColorSat;
	std::vector<float>   m_vecColorLig;

	bool          m_bNeedReport;

	bool          m_bReported;

	bool          m_bTimeOutDrop;

	static int m_nIdCount;	

	VirtualLoop* m_pVlp;


	OpticalFlowHelper *m_pOpticlFlowHer;

private:
	_MvGroup *AssocGroup;
public:
		unsigned  int nBrigShutFrem; 
		int64  m_nSerStrat;
		int64  m_nSerEnd;

};

#endif
