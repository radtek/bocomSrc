#ifndef MV_VIOLATION_DETECTER_H
#define MV_VIOLATION_DETECTER_H

#include <vector>
#include "MvGroup.h"
#include "MvLine.h"
#include "MvChannelRegion.h"
#include "MvLightStatusMem.h"
#include "ViolationInfo.h"
#include "CarInfo.h"
#include "MvRelabelEventHandler.h"
#include "StdAfx.h"



//using namespace std;

class MvGroupLayer;
 typedef struct VIO_GROUP
 {
	 unsigned int GroupId;
	 bool bTurn; 
	 bool bTouchOtherLine;
	 MvLine *passLine;
	 bool bDir;
	 Car *pCar;
	 vector<MvCorner> Corner;
	 CvRect ParkRec;
	 bool   bMetPreLinout;
	 bool   bMetReverseDir; //��������
	 VIO_GROUP()
	 {
		 GroupId = -1;
		 bTurn = false;
		 bTouchOtherLine = false;
		 passLine = NULL;
		 pCar = NULL;
		 bDir = false;//β��//1:ǰ��
		 bMetPreLinout = false;
		 bMetReverseDir = false;

	 }


 }VioGroup;

class MvViolationDetecter : public MvRelabelEventHandler
{
public:

	MvViolationDetecter(const MvFindTargetByVirtualLoop *pFtg, MvLightStatusMem *pLightStatusMem, MvGroupLayer* pGroupLayer, 
		MvLine *pLnStop, MvLine *pLnFore, MvLine *pLnRight, MvLine *pLnLeft, const std::vector<MvLine> &vecYellowLine,
		const std::vector<MvLine> &vecBianDaoXian, const std::vector<MvLine> &vecWhiteLine,
		const std::vector<ChannelRegion> &lstChannelsInfo, int nRedLightVioDelayFrames, bool doVioDetect, bool doVioRedLight);
	~MvViolationDetecter();


	// ���й�����
	void Process( std::vector<ViolationInfo> &vis, unsigned int uFrameSeq, MyCalibration *pCalib, unsigned int uMinBufferFrm, unsigned int uMaxBufferFrm );

	
	// ��ͬһ������group����ѡ��ʱ��֪ͨMvViolationDetecter����һЩά��������
	// ��Ҫ�������С�ѹ���¼��Ķ౨��
	virtual void OnRelabeled(int nOldId, int nNewId);


	// ���ÿ����uFrameSeq֡�õ����µ�group�Ƿ񴳺�ơ�
	//void CheckForRedLightViolation(std::vector<ViolationInfo> &rlvis, unsigned int uFrameSeq, MyCalibration* pCalib, int nRedLightViolationAllowance = 0);


	

	

	

	// ���У��ص�ʱ��Σ�
	//void CheckFor();



	//�õ���������ʻ����
	int GetChannelDriveDir(int nRoadIndex);

	//�õ������Ƿ�Ϊ��������
	bool GetChannelHoldStopReg(int nRoadIndex);

	int GetChannelRedLightTime(int nRoadIndex);

	//�ж��Ƿ��е���������ǰ���ߣ�
	bool IsHaveChannelForeLine();

	//�õ�ÿ��������ǰ���ߣ�
	MvLine * GetChannelForeLine(int nRoadIndex);

	MvLine *MvGetChannelStopLine( int nRoadIndex );

	CvRect *MvGetChannelrectMedianPos( int nRoadIndex );

	void MvSetHoldStopLine( int nRoadIndex ,MvLine **HoldForeLineFirst, MvLine **HoldForeLineSecond,
		MvLine **HoldStopLineFirst, MvLine **HoldStopLineSecond );

	MvLine* GetStopLine() const;

	MvLine* GetForeLine() const;


	MvLine* GetLeftLine() const;

	MvLine* GetRightLine() const;

	std::vector<MvLine> GetYellowLine() const;
	std::vector<MvLine> GetWhiteLine() const;
	std::vector<MvLine> GetBiandLine() const;


	int MvGetmapVioGroup(int id)
	{
		return m_mapVioToGroup[id].GroupId;
	}

	void  mvSetYelGridPoly(const MvPolygon Ploy);
    void MvMakeYelGridImg(CvSize ImgSize);
	map<unsigned int ,unsigned int> m_mapcodeImg;
	


private:
	
	// �ж�һ��group��û�д���ơ�
	// �ں������֮���nRedLightViolationAllowance֡����һ��ʱ�䴳��ƵĲ��㡣
	//bool CheckForRedLightViolation(_MvGroup &g, unsigned int uFrameSeq, std::vector<ViolationInfo> &vis, MyCalibration* pCalib, int nRedLightViolationAllowance = 0);

	//ֹͣ��ʻ
	void CheckForStopViolation( _MvGroup* pGroup, std::vector<ViolationInfo> &vis, unsigned int uFrameSeq );

	void UpdatParkViolation(_MvGroup* pGroup, std::vector<ViolationInfo> &vis);


	bool ParkState(vector<MvCorner> &ParkConer, CvRect ParkRec);


	// �����
	void CheckForRedLightViolation2( _MvGroup* pGroup, std::vector<ViolationInfo> &rlvis, std::vector<ViolationInfo> &vis,
									unsigned int uFrameSeq, MyCalibration* pCalib, vector<_MvGroup *>&Viogroup,
									int nRedLightViolationAllowance = 0, unsigned int uMinBufferFrm = 0, unsigned int uMaxBufferFrm = 0);

	// ������ҡ�
	void CheckForNoTurnLeftRightViolation( _MvGroup* pGroup, std::vector<ViolationInfo> &vis,
									unsigned int uFrameSeq, MyCalibration* pCalib, unsigned int uMinBufferFrm = 0, unsigned int uMaxBufferFrm = 0);



	// ����Υ��
	void CheckForRetrogradeViolation( _MvGroup* pGroup, std::vector<ViolationInfo> &vis, unsigned int uFrameSeq );
	int  LocalInChanleNum(CvRect GroupRec,int nChaneIndex);

	//������ͣ��
	void CheckYelGridForParkViolation(_MvGroup* pGroup, std::vector<ViolationInfo> &vis, unsigned int uFrameSeq );


	//����Υ�»�����״̬
	 void UpdatRushYelGridVio(_MvGroup* pGroup, std::vector<ViolationInfo> &vis,unsigned int uFramseq);

	// ѹ��Υ��
	void CheckForPressLineViolation( _MvGroup* pGroup, 
					std::vector<ViolationInfo> &vis,
					unsigned int uFrameSeq,
					bool isYellowLine = true
					);

	// ���Υ��
	void CheckForBianDaoViolation( _MvGroup* pGroup, 
					std::vector<ViolationInfo> &vis,
					unsigned int uFrameSeq,
					MyCalibration* pCalib);

	void mvRecDirToLine(CvPoint p1,CvPoint p2,CvRect rect,int *nDriNum);


	// ����Υ�¼��
	void CheckForNoPassingViolation( _MvGroup* pGroup, std::vector<ViolationInfo> &vis, unsigned int uFrameSeq );





	// ȷ��group�Ǵ��ĸ������������ġ�false��ʾ��֪����
	//bool GetGroupChannelSource(const _MvGroup &g, int &nChnIndex);

	//�Ƿ񴳺���ݻ������
	bool IsViolationWait(_MvGroup *pGroup);

	// �ж�ĳһ��group֮ǰ�Ƿ��Ѿ�����ĳ�����͵�Υ�¡�
	bool IsVoilationIgnored(int nGroupId, VIO_EVENT_TYPE evt);

	// �ж�ĳһ��group֮ǰ�Ƿ��Ѿ���¼ѹ�ߡ�
	bool IsVoiPressRecode(int nGroupId, VIO_EVENT_RECORD evt);

	// ɾ��Group��Ӧ��Υ�¡�
	bool DelVoilationIgnored(int nGroupId, VIO_EVENT_TYPE evt);

	// ɾ��Group��Ӧ��Υ�¡�
	bool DelVoilationHist(int nGroupId, VIO_EVENT_TYPE evt);

    
	bool IsViolationDetected(int nGroupId, VIO_EVENT_TYPE evt) const;

	//�ҵ羯��һ��ͼ�ĺ���λ�ã�
	bool FindProperFstPos(bool bBreakTrafficLight, _MvGroup *pGroup, unsigned int uFstFrame, unsigned int uMinBufFrm, unsigned int uMaxBufFrm, \
		unsigned int uFirstRedLight, unsigned int &uProperFrame, unsigned int &uUpperFrm, unsigned int &uLowerFrm);
	
private:// ���״̬���
	
	// ���true���̵ƻƵ�false  �Ƶ�Ϊfalse�𣿲�һ���ɣ���
	bool GetLightStatus(MvChannelFrameSignalStatus cfss, MvLine* pTouchLine) const;

	bool GetLightStatus(MvLine* pTouchLine, unsigned int uSeq, int nRoadIndex) const;
	
	//�õ�ĳһ����ĳһ֡ĳ������ĺ���źţ�nDriveDir = -1,��ת�ƣ�0��ֱ�еƣ�1����ת�ƣ�
	bool GetLightStatus(int nRoadIndex, unsigned int uSeq, int nDriveDir) const;

	unsigned int GetFirstRedLightFrameSeq(MvLine* pTouchLine, unsigned int uSeq, int nRoadIndex) const;

private: //λ����ء�

	bool IsGroupUnderStopLine(unsigned int uFrameSeq, _MvGroup* pGroup, MvLine *pStopLine, MyCalibration* pCalib, CvRect *pRectMedain,
		float *pFirstPlateDist = NULL, bool bFlagViolation = false,bool bNoTurnLefRig = false) const;

	bool IsGroupPassStopLineXm(unsigned int uFrameSeq, _MvGroup* pGroup, MvLine *pStopLine, MyCalibration* pCalib, float fFirstPlateDist, float fPassLen = 1.0) const;

	bool IsGroupInChannel(unsigned int uSeq, _MvGroup* pGroup, int nRoadIndex);

	unsigned int GetFrameSeq( _MvGroup* pGroup, unsigned int uStartSeq, unsigned int uFinishSeq, float fRatio, unsigned int uUnderStopLineSeq) const;

	//ȡ�ô���ƺͽ��󡢽��ҡ���ǰ�ĵڶ���ͼ��֡�ţ�
	bool GetMedianFrame(_MvGroup *pGroup, unsigned int uFirstFrm, unsigned int uLastFrm, unsigned int uRoadIndex, unsigned int &uMedianFrm, bool bFlagStopLine = false);

private:

	bool GetCarInfo(_MvGroup* pGroup, unsigned int uFrameSeq, CarInfo &ci) const;

	void KeepHistAndIgnoreRecord(std::vector<ViolationInfo> &vis);


	void _UpdateDelayedGroups(unsigned int uMinBufferFrm, std::vector<ViolationInfo> &rlvis);


	bool GetDelayFrameSeqStatus( unsigned int uFrameSeq, ViolationInfo *pViolation );



	
	bool MvGetTrackTrunState (_MvGroup *pGroup);//�ж�Ŀ���Ƿ���ڹ���״̬
	bool mvGetCarTurn(Car *pCar,_MvGroup *pGroup,bool bTurnLef = true);
	int  mvGetOutState(const int nGrouId,const VIO_EVENT_TYPE &evtType);

	void mvCodeImg(std::vector<ViolationInfo> &vis,VIO_EVENT_TYPE evtType,unsigned int Fram0,unsigned int Fram1,unsigned int Fram2);
	

	



public:
	  void GetParkViol(std::vector<ViolationInfo> &vis, unsigned int uFrameSeq);

	  //Ϊѹ�ߡ������Υ����ʱȡ������ͼ
	  void MvGetVioFrame(std::vector<ViolationInfo> &vis,unsigned int uFrameSeq);

	  //��Ŀ����ʧʱ��Υ�±���--�漰Υ�·ּ�
	  void MvGetViolat (std::vector<ViolationInfo> &vis,unsigned int uFrameSeq);

	  void mvDelCode(std::vector<ViolationInfo> &vis,unsigned int Fram0,unsigned int Fram1,unsigned int Fram2);
		float  m_fScalWidht;
		VioGroup* GetVioId(int VioId)
		{
          return &m_mapVioToGroup[VioId];
		}
		std::vector<ViolationInfo>* GetParkVec()
		{
			return &m_villegParkOutput;
		}
		inline 	MvPolygon MvGetYelGridPoly()
		{
			return m_YelGridPoly;
		}

private:



	//vector<ViolationInfo> vStopCheck;//Ϊ���������ã����κ�ʵ�ü�ֵ



	std::vector<ViolationInfo> vDelayRedLightOutput;

	std::vector<ViolationInfo> m_villegParkOutput;

	

	MvGroupLayer *m_pGroupLayer;

	int m_nRedLightDelay;

	// �����ߡ�
	MvLine *m_pLnStop;
	MvLine *m_pLnFore;
	MvLine *m_pLnRight;
	MvLine *m_pLnLeft;


	//������������
	MvLine *m_pLnHoldForeFirst;
	MvLine *m_pLnHoldForeSecond;
	MvLine *m_pLnHoldStopFirst;
	MvLine *m_pLnHoldStopSecond;


	



	// ����
	std::vector<MvLine> m_vecYellowLines;

	// ����
	std::vector<MvLine> m_vecWhiteLines;


	// �����
	std::vector<MvLine> m_vecBianDaoXian;

	// ������Ϣ
	std::vector<ChannelRegion> m_lstChannelsInfo;

	bool m_bHaveChannelForeLine;

	// ���״̬��¼��
	MvLightStatusMem *m_pLightStatusMem;

	//�Ƿ�����Υ�¼�⣡
	bool m_bViolationDetection;
	//�Ƿ����˴���ƣ�
	bool m_bViolateRedLight;

	// ���Ա꣬���ڷ�ֹ��һ�������ж��Υ�������
	// ע�⣺��Ҫѡ��һ��ǡ����ʱ�̽��ر��ϵļ�¼��ɾ��
	std::map< int, std::vector<VIO_EVENT_TYPE> > m_mapViolationIgnore; 

	// Υ�¼�¼����ֹ������
	std::map< int, std::vector<VIO_EVENT_TYPE> > m_mapViolationHist;

	// ��¼Groupѹ�����
	std::map< int, std::vector<VioPressRecode> > m_mapVioPressRecode;

	//Ϊ�˽����ת����ת����������ǰ���߶��󱨴���Ƶ����⣬�������±��������ã�
	bool m_bUseNewViolationRules;
	bool m_bUseChongHongDeng;

	std::map<_MvGroup *, ViolationInfo> m_mapVioRedLightDelay;

	std::map<int, VioGroup> m_mapVioToGroup;//Υ�±����Group��IDӳ���ϵ����ֻ��¼������ת���Ĵ���ơ����󡢽��ҡ���ǰ��
	

	const MvFindTargetByVirtualLoop *m_pFtg;

	std::vector<ViolationInfo> m_Violation;//���û�����У�ֻ��¼������ת���Ĵ���ơ����󡢽��ҡ���ǰ��


	unsigned int m_unID;
	int nTestFlag;
	IplImage *m_pYelGridImg;
	MvPolygon m_YelGridPoly;
};




#endif
