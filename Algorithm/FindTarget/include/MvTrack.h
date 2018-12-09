#ifndef MV_TRACK_H
#define MV_TRACK_H

#include <list>
#include <map>
#include <fstream>
#include "MvCorner.h"
#include "MvCornerLayer.h"

#include "MyKalman.h"
#include "MvMaxSize.h"



#define TRACK_MAX_CORNERS 200
#define MIN_TRACK_CORNUM 3 //�켣���������ٽǵ���Ŀ



enum Drive_Dir
{
	Come =0,
	Leave,
	Horizon,
	UnKnow

};

typedef struct _RelativDis
{
	float fWorDis;
	int   nImgDis;
	_RelativDis()
	{
		fWorDis = 0.0; 
		nImgDis = 0;
	}

}RelativDis;






typedef struct _MvTrack
{

public:

	_MvTrack()
	{

	}
	// ���캯��
	_MvTrack(MvCornerLayer *pCorLayer)
	{
		m_nTakedPosCount   = 0;
		m_nNextStorPos     = 0;
		m_nTrackIndex      = -1;
		m_pCornerLayer     = pCorLayer;
		memset(m_CornerIndex, 0, TRACK_MAX_CORNERS * sizeof(int));

		m_uLastUpdateSeq   = 0;

		m_fTravX           = 0.0;
		m_fTravY           = 0.0;

		m_nGroupId         = 0;

		m_nInformalTimes   = 0;
		m_bFormal          = true;
		m_nFormNum         = 0;


		m_nEstTimes        = 0;


		m_nTotalEstTimes   = 0;


#ifdef TRACK_GROUP_LGW
		 m_fJoinGroupSim =  100.0;
		 m_nGropFolwId  = 0;
		 m_nCarCol = -1;
		 m_uCarId = 0;
		 m_DisPlatPoint = cvPoint(MAX_INT,MAX_INT);
		 m_bBusTop = false;
#endif

	}

#ifdef TRACK_GROUP_LGW
	
	inline void SetBusTop(bool bBusTop) 
	{
		m_bBusTop = bBusTop;
	}


	inline void ClearGroupPropter()
	{
		m_nGropFolwId  = 0;
		m_fJoinGroupSim = 100.0;
		m_nCarCol = -1;
		m_uCarId = 0;
		m_DisPlatPoint = cvPoint(MAX_INT,MAX_INT);
		m_bBusTop = false;

	}

	inline void ClearTrackPropter()
	{
		m_nTakedPosCount   = 0;
		m_nNextStorPos     = 0;
		m_nTrackIndex      = -1;
		memset(m_CornerIndex, 0, TRACK_MAX_CORNERS * sizeof(int));

		m_uLastUpdateSeq   = 0;

		m_fTravX           = 0.0;
		m_fTravY           = 0.0;

		m_nGroupId         = 0;

		m_nInformalTimes   = 0;
		m_bFormal          = true;
		m_nFormNum         = 0;


		m_nEstTimes        = 0;


		m_nTotalEstTimes   = 0;

		m_nGropFolwId  = 0;
		m_fJoinGroupSim = 100.0;
		m_nCarCol = -1;
		m_uCarId = 0;
		m_DisPlatPoint = cvPoint(MAX_INT,MAX_INT);
		m_bBusTop = false;

	}

	inline bool GetBusTop() const
	{
		 return m_bBusTop;
	}

	inline int GetCarCol() const
	{
		return m_nCarCol;
	}
	inline void SetCarCol(int nCol) 
	{
		 m_nCarCol = nCol;
	}

	inline CvPoint GetPlatDis() const
	{
		return m_DisPlatPoint;
	}
	void SetPlatDis( CvPoint PlatPoint);

	inline unsigned int GetTrackCarId() const
	{	 
		return m_uCarId;
	}
	inline void SetTrackCarId(unsigned int uCarId) 
	{
		m_uCarId = uCarId;
	}

	// ��ȡ�켣������Ŀ�����Group��š�
	inline int GetFlowGroupId() const
	{
		return m_nGropFolwId;
	}
	inline void  SetTrackGrouFlowId(int nID)
	{ 
		m_nGropFolwId = nID;
	}


	inline float GetJoinGroupSim() const
	{
		return m_fJoinGroupSim;
	}

	void  SetJoinGroupSim(float fsim) 
	{
		 m_fJoinGroupSim = fsim;
	}

	void GetMotionDirection(double &fDx, double &fDy, CvRect GroupRec) const;
#endif
	// Ԥ��켣��uFrameSeq֡ʱ��λ�á�
	MvCorner Predict(const unsigned int uFrameSeq,const int64 ts, const unsigned int uTimestamp, const MyCalibration *pCalib, 
		int &nGateSize, const MvMaxSize *p_Maxsize);

	void Speed_Predict(const unsigned int uFrameSeq,const int64 ts, const unsigned int uTimestamp, const MyCalibration *pCalib, 
		int &nGateSize, const MvMaxSize *p_Maxsize ,MvCorner &PreditCor);

	// ������ΪnCornerIndex�Ľǵ���¹켣��
	// ����ʱ�п��ܽ����ϵĹ켣��ӹ켣��¼��ɾ��������������ýǵ��ɾ����Ӧ�Ľǵ㡣
	// ���ƵĽǵ�Ҳͨ���ú������½��켣��
	void Update(int nCornerIndex);


	// �ڽǵ�vecCors����ƥ����õ�
	bool FindMatch(const std::vector<MvCorner*> &vecCors, const MvCorner &center, 
		int radius, int &nIndex, int &nDis, MySIFT1 *pSift);

	bool Speed_FindMatch( MvCorner** vCorPointer, MvCorner** tmp_cors, int nCorCount, 
		const MvCorner *pcenter,int radius, int &nIndex, int &nDis );

	bool FindMatch(MvCorner** pCors, MvCorner** tmp_cors, int nCorCount, const MvCorner &center,
		int radius, int &nIndex, int &nDis, MySIFT1 *pSift);

	bool Speed_CheckForMatch( const MvCorner *pCor, MvCorner** pCors, int nCount, int &nMatchedIndex, int &nDis);

	bool CheckForMatch( const MvCorner *pCor, MvCorner** pCors, int nCount, int &nMatchedIndex, int &nDis);

	 int SurfDist(unsigned char *p1, unsigned char *p2);
	// ��ȡ���һ���ǹ��Ƶ��������
	bool GetLastNonEstimateCorIndex(int &nIndex);

	// ��ȡ���������ǵ���˶��������dis���ף��Ĵ�����
	int GetMovedCornerCount(float dis) const;
	


	// ��ȡ�켣���һ���ǵ��������
	int GetLastCorner() const;
	

	// ��ȡ�켣��һ���ǵ��������
	int GetFirstCorner() const;


	// ��ȡ�켣�ĵڵ���N���ǵ㡣��������ֵ��ǵ�һ����������ֵ������һ������
	// ����켣û����ô��ǵ㣬�����Ѿ�û�м�¼�ˣ�����false
	bool GetReverseNthCorner(int n, MvCorner **pCor) const;


	// ��ȡ��¼�е������ֵĽǵ��ָ�롣
	MvCorner* GetRecerseNCornerPointer(int n) const;

	// ��ȡ�켣�ܹ����˶�Զ����λ�ס�ÿ�����½ǵ���붼���ۼӸ�ֵ��
	float GetTravelLength() const;


	// ��ȡ�켣ͼ����롣
	int GetTravelImgDis() const;


	// ��ȡ�켣��ͼ���ϵ��˶��������һ���ǵ��ix, iy���һ���ǵ��ix, iy��Ƚϡ�
	void GetMotionDirection(double &fDx, double &fDy, int nRecFrames = -1) const;


	// ��ȡ�켣����������ϵ�е��˶�����
	void GetMotionDirectionWorld(float &fDx, float &fDy, int nRecFrames = -1) const;

	//MvCorner* GetCornerByFrameSeq()


	// �ҳ��켣ĳһ֡ʱ�Ľǵ����ݡ�����Ҳ�������false
	bool GetCornerByFrameSeq(unsigned int uFrameSeq, MvCorner **pCorner, bool bAllowEstimate = true) const;


	// ��ȡ��¼��������ֵĽǵ��ָ�롣
	MvCorner* GetFirstCornerPointer() const;

	// ��ȡ���һ���ǵ��ָ�롣
	MvCorner* GetLastCornerPointer() const;


	// ���ӹ켣���ƴ�����
	void IncEstTimes()
	{
		// �ܹ��ƴ���
		m_nTotalEstTimes++;

		// �������ƴ���
		m_nEstTimes++;
	}

	// ��ȡ�������ƴ���
	int GetEstTimes() const
	{
		return m_nEstTimes;
	}

	// ��ȡ�ܹ��ƴ���
	int GetTotalEstTimes() const
	{
		return m_nTotalEstTimes;
	}

	bool GetFormTrack()const
	{
		return m_bFormal;
	}
	// ����������ƴ��������зǹ��ƽǵ����ʱ���ͻ�����������ƴ�����
	void ClearEstTimes()
	{
		m_nEstTimes = 0;
	}


	// ����켣��ǰ��˲ʱ�˶�����
	//bool GetTrackInstantMotionDirectionWorld(float &vx, float &vy, int nFrames=4);

	

	// ��ȡ�����ڶ����ǵ��ָ�롣
	MvCorner* GetSecLastCornerPointer() const;


	
	// ��ȡ��ǰ�켣�͹켣t��֡�Ľǵ�������յ㡣
	bool GetCommonFrameStartEndCorners(const _MvTrack &t, MvCorner *vMyCors[2], MvCorner *vTCors[2]);




	// ��ȡ��ǰ�켣�͹켣t��֡�Ľǵ�
	//void GetCommonFrameCorners(const _MvTrack &t, MvCorner *vMyCors[TRACK_MAX_CORNERS], 
	//	MvCorner *vTCors[TRACK_MAX_CORNERS], int &nCommonCount);


	// ���������켣��֡���ֵ������յ㡣�Ƚ������켣����������켣���������򷵻�0.
	// û���õ���
	//static double CompareMotion1(MvCorner *vMyCors[2], MvCorner *vTCors[2]);


	// �������켣�Ľǵ�֮������Ƿ񱣳ֺ㶨��
	//static double CompareMotionLongTerm(MvCorner *vMyCors[TRACK_MAX_CORNERS], MvCorner *vTCors[TRACK_MAX_CORNERS],
	//	int nCommonCount, int nLeastCommonFrames = 2, int nFrom = 0);

	// 
	//static double CompareMotionLength(MvCorner *vMyCors[TRACK_MAX_CORNERS], MvCorner *vTCors[TRACK_MAX_CORNERS],
	//	int nCommonCount, int nLeastCommonFrames = 2, int nFrom = 0);


	// �Ƚ������켣���˶����ȣ��ӵ�����nBack���ǵ㵽���µ�һ���ǵ㡣
	double CompareMotionLength2(const _MvTrack &t, int nBack);

	int   CalTrackDis(const _MvTrack *t,bool bXDir =false);


	// �Ƚ������켣���˶�һ���ԡ���С�ηֱ��Ӧ�Ƚϡ����ظ��β�������ֵ��
	// nFromָ�����ĸ��ǵ㿪ʼ�Ƚϡ�
	// ����ֵ��[0-1]��Խ���������Խ��
	// tips: ���������Ĺ켣����ֵΪ0
	/*static double CompareMotionShortTerm(MvCorner *vMyCors[TRACK_MAX_CORNERS], MvCorner *vTCors[TRACK_MAX_CORNERS], 
		int nCommonCount, int nLeastCommonFrames = 2, int nFrom = 0);*/

	
	// �Ƚ������켣���˶�����һ���ԡ��ӵ�nFrom�ǵ㣬��nCommonCount-1�Ľǵ��������Ƚϡ�
	//static double ComareMotionByDirection(MvCorner *vMyCors[TRACK_MAX_CORNERS], MvCorner *vTCors[TRACK_MAX_CORNERS],
	//	int nCommonCount, int nLeastCommonFrames = 2, int nFrom = 0);

	
	double ComareMotionByDirection2(const _MvTrack &t, int nBack,bool bNoVehicle = true);


    double ComareMotionByDis( const _MvTrack &t,const MvMaxSize *p_Maxsize);



	// ��֡�Ƚ��˶��ٶȷ���һ���ԡ�[0-1]��ʾ�����С
	//double CompareMotion2(const _MvTrack &t, int nLeastCommonFrames = 5);



	// �Ƚ������켣���µ�nSeg��С�ε��˶�һ���ԡ���С�ηֱ��Ӧ�Ƚϡ����ظ��β�������ֵ��
	double CompareMotionShortTerm2(const _MvTrack &t, int nSeg = -1);


	// �������켣�Ľǵ�֮������Ƿ񱣳ֺ㶨��
	double CompareMotionLongTerm2(const _MvTrack &t, int nCors = -1);


	//�ٶȹ�ϵ
	double MotionSpeed(const _MvTrack *t);

	void  GetTrackMotinVec(int &ndx, int &ndy,bool bFul =true);
	void  GetTrackMotinDis(float &fWodis,int n);


	// ���αȽϡ�
	// ���ȿ����µĽǵ��֡���Ƿ�һ�£������һ������Ϊ�����ƣ� ���ء�
	// Ȼ��ȡ����֡���ܳ��ȡ�����ܳ���С��nSize������Ϊ�����ƣ����ء�
	// ��Ȼ�󣬴ӵ�ǰ֡��ʼ����nSizeΪ�δ�С��ȡ�������켣����һ��ʱ���ڵ��˶���
	// ������µĶ������켣��û��,��Ŵ�nSize��nSize + nStep����ȡ�˶���
	// ���һ����һ����������Ϊ�����ƣ����ء�
	// ���������������Ƚ������ε��˶������ԣ������ء�
	// nSize �δ�С��
	double CompareMotion3(const _MvTrack &t, int nSize = 5, int nStep = 2, int nRecursTimes = 0);


	





	// ��ȡ�켣�Ľǵ����С�
	void GetTrackCorners(int corners[TRACK_MAX_CORNERS], int &nCornerCount) const;

	// 
	void GetTrackCorners(MvCorner* vCorners[TRACK_MAX_CORNERS], int &nCount) const;


	// ��ȡ�켣�������Ľǵ������
	int GetTrackCornerCount() const;
	
	// 
	void Destroy();


	// ��ȡ���һ�θ��µ�֡�š�
	unsigned int GetLastUpdateFrameSeq() const;


	// �жϹ켣�Ƿ����
	bool IsTrackReasonable(int nBack=-1);


	// ���켣��
	void DrawTrack(IplImage *img,  int nTrackIndex, CvScalar color) const;

	// ���켣��
	void DrawTrack(IplImage *img, CvScalar color ,CvPoint offpoint = cvPoint(0,0),bool bShowIndex=false ) const;


	// 
	void WriteTrackToTxt(std::ofstream &ofs);


	// ��ȡ�켣�������ƵĴ�����
	int GetContEstTimes();


	// ��ȡ��track��cvset���index
	int GetTrackIndex()const;

	int GetIndex();

	// ��ȡ�켣������Group��š�
	int GetGroupId() const;


	// �Թ��Ƶ�����������
	void RefineCorners(const MyCalibration *pCalib);

	// ��ȡ���n֡���˶���
	bool GetRecentNFrameMovingDis(int n, float &idis, float &wdis) const;

	// �������켣�Ľǵ�֮������˶����롣
	RelativDis RelativeMotionWDis(const _MvTrack *t);




	//
	//bool IsFormalTrack() const;


	//void ResetInformalTimes();


	//void IncInformalTimes();


	//void SetFormal(bool bFormal);


	// MvTrackLayer��track����Ԫ��
	friend class MvTrackLayer;
	friend struct _MvGroup;
	friend class MvGroupLayer;
	
private:
	
	// ���ù켣��������group��š�
	void SetGroupId(int nId);
	
	// ֪ͨ�ǵ��ɾ�����켣�����нǵ㡣
	void RemoveAllCorners();
	


	


	// �����Ƿ���Ա�ɾ����
	//void SetCanDel(bool bCanDel);
	

private:

#ifdef TRACK_GROUP_LGW

	float m_fJoinGroupSim;
	int m_nGropFolwId;
	int m_nCarCol;
	unsigned int m_uCarId;
	CvPoint m_DisPlatPoint;//���복�Ƶĵ�ƫ����
	bool  m_bBusTop;

#endif

	MvCornerLayer *m_pCornerLayer;

	// ��track�Ƿ���Ա�ɾ����
	//bool m_bCanDel;


	// track��CvSet����ı�š�
	int m_nTrackIndex;


	// ��¼һ���켣�Ľǵ������
	int m_nTakedPosCount;


	// ��һ���ǵ���corners��Ӧ��ռ��λ�á�
	int m_nNextStorPos;

	
	// �켣���ݡ���¼��ɹ켣�Ľǵ��������
	// corners�Ǹ�ѭ�����У���������ʱ�Ὣ
	// ������ɾ�����ǵ���ɾ��ʱ֪ͨ�ǵ��ɾ���ǵ㡣
	int m_CornerIndex[TRACK_MAX_CORNERS];


	//int m_CornerIndexL[];
	//int m_nTakedPosCountL;
	//int m_nNextStorPosL;


	// �켣���ƵĴ���������õ��ǹ��ƽǵ�����0
	int m_nEstTimes;



	// �켣�ܹ����ƵĴ���������0.
	int m_nTotalEstTimes;


	unsigned int m_uLastUpdateSeq;

	// �켣������Group�ı�š�
	// ��ʼֵΪ0
	int m_nGroupId;


	// �Ƿ��ǹ켣����ʽ�켣�����������ʽ�켣������һ������m_nInformalTimes
	bool m_bFormal;
	int  m_nFormNum;

	// ����ʽ�켣�Ĵ�����
	int m_nInformalTimes;

	bool m_bUpData;

	// �켣�ƶ����롣�������ꡣ(m)
	float m_fTravX;
	float m_fTravY;

	MvCorner m_PredCorn;


	

	

} MvTrack;


// MvTrack��CvSet����Ĵ洢�ṹ��
typedef struct _MvTrackElem : CvSetElem
{
	_MvTrack track;
	_MvTrackElem(const _MvTrack &t):track(t)
	{
	}

} MvTrackElem;



#endif