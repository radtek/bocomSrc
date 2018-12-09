// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef CAR_H
#define CAR_H

#include <fstream>
#include <string>
#include <list>
#include "Calibration.h"
#include "CarInfo.h"
#include "MvChannelRegion.h"
#include "Mode.h"
#include "MvSurf.h"

using namespace PRJ_NAMESPACE_NAME;

class SensedObject;

struct _LoopObj;
struct _MvGroup;
struct _MvUnion;

class Mv_LoopShutterLight;
class MvFindTargetByVirtualLoop;

// �������͵��¹淶��
#define VEHICLE_TYPE_WJS    0x00000000 // δ����
#define VEHICLE_TYPE_UN     0x10000000 // δ֪

#define VEHICLE_TYPE_LARGE  0x00000001 // ��
#define VEHICLE_TYPE_MIDDLE 0x00000002 // ��
#define VEHICLE_TYPE_SMALL  0x00000004 // С
#define VEHICLE_TYPE_OTHER  0x00000008 // ����

#define VEHICLE_TYPE_XR     0x00000010 // ����
#define VEHICLE_TYPE_LL     0x00000020 // ����
#define VEHICLE_TYPE_SL     0x00000040 // ����
#define VEHICLE_TYPE_HC     0x00000080 // ����
#define VEHICLE_TYPE_KC     0x00000100 // �ͳ�

#define VEHICLE_TYPE_JZ     0x00010000 // ��װ�����


typedef std::vector<std::pair<CvPoint, CvPoint> > vecCvPointPair;
typedef std::vector<std::pair<float, float> > vecFloatPair;
typedef std::vector<std::pair<CvPoint2D64f, CvPoint2D64f> > vecCvPoint2D64fPair;


class Car
{
public:
	SensedObject * AssocSensedObj;

	std::list<CarInfo> trackRecord;

    //�洢Ŀ����
	std::vector<int> ObjHis;
	

	// ����泵�Ƶ�֡�š�
	unsigned int m_uGettingRealCarFrameSeq;

	//������Ƶ���ٵ����Ż���ͼƬ֡��,�����Ϊ-1��ʾ�ó�����Ƶ�ٶȲ���ͨ��Surfƥ���ã�
	unsigned int m_uLastFrm[2];

	int m_nHitBusNum;
	

public:

	Car(MvFindTargetByVirtualLoop *pFtg);

	MvFindTargetByVirtualLoop * m_pFtg;


	void SetVehicleType(int nVT)
	{
		m_nVehicleType = nVT;
	}

	int GetVehicleType() const
	{
		return m_nVehicleType;
	}

	//��������ͼ��֡�ţ�ȥ�����Ƿ��Ѿ��ڳ��Ƶ�list�У���Ӧ�ķ��س�λ��

	bool Mvgetshuttercarnumpos(MvFindTargetByVirtualLoop* pFtg, unsigned int uSeq, Time_Mode mode, CarInfo &ci );

	bool Mv_Getmorelihgetbycarnum( int64 st, int64 et, Mv_LoopShutterLight *p_mLoopShutter, CarInfo &ci );

	bool mvModfiyCarInfo( CarInfo &ci );

	bool mvModfiyCarInfo_ForEle( CarInfo &ci, unsigned int uFreq );



	// �жϳ����Ƿ���������
	// �����������췵��false��
	// ������ƿ��ܻ�����,���Ҽ������С��15������false��
	// ���򷵻�true
	bool CanOutput(unsigned int uFrameSeq) const;

	// ������Ŀ�ϵ� 
	bool CanOutputOnBus(unsigned int uFrameSeq) const;

	// ��Union���й���
	void SetAssocUnion(_MvUnion *pUnion)
	{
		m_pAssocUnion = pUnion;
	}

	// ��ȡ��������Union
	_MvUnion* GetAssocUnion() const
	{
		return m_pAssocUnion;
	}

	// ���Car������û�н���Union�б�
	// ��CanOutput����trueʱ��Car����ͻ�����б�����Car�Ѿ�������ˡ�
	void SetEnterUnionList()
	{
		m_bEnterUnionList = true;
	}

	// �����Ƿ�����UnionList����ֹ���������
	bool GetEnterUnionList() const
	{
		return m_bEnterUnionList;
	}

	// ��������UnionList�ļ�¼����������������ģ�����øú��������������������
	// ����UnionList
	void ClearEnterUnionList()
	{
		m_bEnterUnionList = false;
	}

	// �жϳ��������ܲ��ܸ���AABBģʽ�ֳ��������ơ�
	int GetSplitPosOtsu() const;

	// ���������нضϣ�β�ʹ���t�ﷵ�ء�
	void Split(int nPos, std::list<_CarInfo> &t);

	//bool GetPlatePosBySeq(unsigned int uSeq, CvRect &rect) const;

	
	// ��ȡ�����ID
	unsigned int  GetCarId() const;


	// be ����0ǰ�ƣ�С��0β�ƣ�����0��֪��
	std::string        GetMostLikelyCarNum(int be, int count) const;
	
	// �����侯����С�֡�
	std::string        GetMostLikelyWjNo() const;
	
	bool GetPlatePosBySeq(unsigned int uSeq, CvRect &rect) const;

	// ���ݳ���carnum�ж����͵�ǰʵ���ǲ���ͬһ����.Ĭ�ϲ�ʹ�������ַ���Ҫ����ڵ���6λ��ͬ��
	bool          IsSameCar(std::string carnum, bool bUseSimilar = false, int nCount = 6) const;

	// ��λ�Ƚϳ��������ԡ����Է�ֹ���ƶ�λ��ʱ��λƫ����ɵ���������
	bool          IsSmaeCarWithOffset(std::string carnum, int nOffset, bool bUseSimilar = false, int nCount = 6);

	// ����λ���ж��Ƿ�Ϊͬһ�����ĳ���
	bool          IsSameCarByPos(CvRect carnumPos, unsigned int frameSeq, int direction, MyCalibration *pCalib) const;

	bool          IsSameCarByPosOnBus(CvRect carnumPos, MyCalibration *pCalib);

	//ĳ������ĳ��ʱ�����Ƿ���ֹ���
	bool          IsPresent(int64 startTime, int64 endTime);

	//void          SetNeedReport();

	// �趨�Ѿ��������ֹ�������
	void          SetReported(unsigned int frameNo);

	bool          GetReported() const;

	// �����Ƿ���Ҫ��������ڼ���������٣��������ŶȽϵ͵���Ϊ����죬����false��
	bool          GetNeedReport() const;

	// ����й�����Group��Union����ɾ��������ܽ�UnionList�����ǻ�û����Ҳ��ɾ��
	bool          CanDelete(int64 ts) const;

	// ���ݶ�γ��Ƽ���λ�ù��Ƴ����˶�����
	// ����<0��ʾδ֪��0��Զ������ǰ�ƣ���1�ɽ���Զ��β�ƣ� 
	int           EstimateDirUsingPlateTrack() const;

	// ��������ڵ�n��n+k֡���������Թ�����n,n+k)������ĳ֡����λ�á�
	bool          EstimatePlatePos(unsigned int uSeq, CvRect &ret) const;

	// ���س����˶�����ʸ��
	void          GetMotionDirection(float &dx, float &dy) const;

	// ���µĳ���λ�ø��±������������
	void          UpdateCar(CarInfo cn, FindTargetElePolice::MyCalibration *pCali);

	//����Surfƥ��õ��ĵ�ԣ����Ǹ߶����أ�Ӧ����ֵ�˲��ķ���������������Ƶ�ٶȣ�
	float		  CorrectVideoSpdBySurf(IpPairVec vecPair, int64 *lastTimeStamp, bool bUseRemoveDisturbing, vecCvPointPair &img_coor, vecFloatPair &vecDeltaY, vecCvPointPair &corrected_img_coor, vecCvPoint2D64fPair &world_coor, std::vector<float> &corrected_spd);

	// ��ȡCar�����г��Ƽ������
	int           GetTrackCount() const;

	// �����Ŷ���õ�һ��ֵ����ԽСԽ�ã�
	float         GetBestIsCarNum() const;
	
	// ���ݳ��ƺ����¼���������Լ����ƶȺ����Ŷ��жϵ�ǰʵ���ǲ�������ǳ��ƣ������ǵ���֮�������������
	bool          IsRealCar() const;

	// ��ȡ������ĳ�����ϢCarInfo
	CarInfo       GetLastTrack() const;

	// ��ȡ�����Ϣ��
	bool          GetOutput(int direction, unsigned int uFrameSeq, unsigned int uMaxSeq, _LoopObj *pLoopObj, CarInfo &ret);

	// ���ù�����OBJ�������á�
	void          SetAssocSensedObject(SensedObject *pSensedObj);


	SensedObject* GetAssocSensedObj() const;
	
	
	void          ClearAssocSensedObj();


	// ���ù���Group��
	void          SetAssocGroup(_MvGroup *pGroup);


	// ��ȡ����Groupd��
	_MvGroup*     GetAssocGroup() const;


	// ֪ͨsensedobj���ƶ���ɾ��
	void          NotifyDelete() const;

	

	// ���Ƴ�����timestampʱ����ͼ���е�λ��   
	//CvPoint       EstimatePosition(int64 timestamp, FindTargetElePolice::MyCalibration *cal) const;

	// ��ȡ�������һ�ε�λ�á�ͼ�����ꡣ
	CvRect        GetLastPosition() const;


	CvRect        GetFirstPosition() const;

	// ��ȡ��һ�γ��ֵ�ʱ��ts��
	int64		  GetFirstTime() const;

	// ��ȡ���һ�θ��µ�ʱ��ts��
	int64         GetLastUpdateTime() const;

	// ��ȡ��һ�ε�֡�ţ�
	unsigned int GetFirstFrameSeq() const;

	// ��ȡ���һ�θ���ʱ��֡�š�
	unsigned int  GetLastUpdateFrameSeq() const;

	//��ȡ�������ʱ�����õ��ı�����֡�ţ�
	unsigned int  GetShutterFrame() const
	{
		return m_uShutterFrame;
	}
	//�����������ʱ�����õ��ı�����֡�ţ�����Ϊ��ʼֵ0��
	void          SetShutterFrame(unsigned int uFrame)
	{
		m_uShutterFrame = uFrame;
	}

	// ��ȡ�ó��������֡�š�
	//unsigned int  GetOutputFrameNo() const;


	void          WriteCarToFile(std::ofstream &fs) const;

	// 
	void          MergeCar(Car* pCar, int nDirection);


	//void          IncRefCount();


	//void          DecRefCount();


	float         GetSpeed() const;

	float         GetCorrectedSpd() const
	{
		return    sqrtf(m_fSpdX_Correction*m_fSpdX_Correction + m_fSpdY_Correction*m_fSpdY_Correction);
	}

	// �жϳ��������ĸ��������������-1����ʾ�������κγ�����
	int           GetRoadIndex(const std::vector<ChannelRegion> &rd) const;

	// �ж���from��toʱ���ڣ�������û�м����
	bool          IsDetectedInTimePeriod(int64 from, int64 to) const;


	//�ж��Ƿ�Ħ�г���
	bool          IsMotorCycle() const;

	// ���ݳ�����ɫ�ж��Ƿ�Ϊ�󳵡���ɫ��ѧΪ�󳵡�
	bool          IsBigVehicle() const;


	// ���ݳ�����ɫ�ж��Ƿ�Ϊ��
	static bool    IsBigVehicle(const CarInfo &ci);
	
	//�ж��Ƿ�Ϊ��Ĵ󳵣����ܵ�һ�α����������ˣ�
	bool		   GetRealBigVehicle() const
	{
		return m_bRealBigVehicle;
	}
	void		   SetRealBigVehicle()
	{
		m_bRealBigVehicle = true;
	}
	int			   GetCheckBigVehicleNum() const
	{
		return m_nCheckBigVehicleNum;
	}
	void           UpdateCheckBigVehicleNum()
	{
		m_nCheckBigVehicleNum++;
	}
	//static bool    IsNotYellowPlate(const CarInfo &ci);

	CvRect           GetCarVlpRec()const
	{
		 return m_CarVLpRec;
	}

	void   SetCarVlpRec(CvRect rect)
	{
		m_CarVLpRec = rect;

	}

	void SetCarAwayStat()
	{
       m_CarDirveAway = true;
	}

	bool GetCarWayStat()
	{
		return m_CarDirveAway;
	}

	void SetCarInStat()
	{
		m_CarDirveAway = false;
	}

	void SetCarCutStat()
	{
		m_CarCut = true;
	}

	bool GetCarCutStat()
	{
		return m_CarCut;
	}

	// ������������7λ������/ͬ��λ��    
	int static    CalcCarNumDis(const std::string &num1, const std::string &num2, bool useSimilarChar = false);

private:
	bool    m_CarDirveAway;


	bool   m_CarCut;

	CvRect  m_CarVLpRec;

	// ���˳��Ƶ�һλ�����֣���
	char          GetMostLikelyChnCharacter(int be, int count) const;


	// ���˳��ƺ���λ��
	std::string   GetMostLikelyCharacter(int be, int count) const;

	// �Ƿ��Ѿ������
	bool          m_bReported;

	// �������֡��
	unsigned int  m_uOutputFrameNo;


	// ���������������group�ı�š�ÿ��group��һ����š����Ӿ����á�
	_MvGroup*     m_pAssocGroup;

	// ÿ��car������һ��Ψһ�ı��
	unsigned int  m_uCarId;


	// ���Ƽ��ʱ�жϳ������͡���ʱֻ���ڵ羯��������
	int           m_nVehicleType;


	static unsigned int uCarIdGenerater;



	// �ٶȣ�km/h��ÿ�μ��ʱ���¡�
	float     m_fSpdX;
	float     m_fSpdY;
	// ���Ǹ߶Ⱥ��У����Ƶ�ٶȡ�
	float     m_fSpdX_Correction;
	float     m_fSpdY_Correction;

	int       m_nImageHeight;
	FindTargetElePolice::MyCalibration *m_pCalib;
	//�ж��Ƿ�����Ļ��Ƴ����жϴ�����ǰ����ֻҪ��һ�μ��ɣ�����β�Ƴ��ͣ�
	bool      m_bRealBigVehicle;
	int       m_nCheckBigVehicleNum;

public:
	bool    m_Bus;
	unsigned int uShutBriFrm;
	int64     m_SerStr;
	int64     m_SerEnd;	
	bool     m_bStoreCar;
	bool     m_bViolation;//״̬����Ҫ���ڱ����ʱ���������Υ���ˣ�����Υ����ɾ��
	
	
private:
	_MvUnion* m_pAssocUnion;

	bool      m_bEnterUnionList;

	int       m_nCarPlateHeightOffGround;

	unsigned int m_uShutterFrame;  //���ʱ������Ȧ����ʱ���õı�����֡�ţ�
private:
	char     static GetMostLikelyChar(int index, const std::list<CarInfo> &lst);
	char     static GetMostLikelyChar(int index, const std::list<std::string> &lst);
	bool     static IsSimilar(const char &c1, const char &c2);

	// �����nStart��ʼ�Ĺ�nLen���ַ����м���һ���ģ����ƣ���
	int      static GetSameCount(char* str1, char* str2, int nStart, int nLen, bool bUseSimilar);


	
};

#endif
