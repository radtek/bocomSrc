// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010/03/13
	created:	13:3:2010   22:44
	filename: 	e:\BocomProjects\find_target_lib\include\MvPhysicLoop.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvPhysicLoop
	file ext:	h
	author:		Dur
	
	purpose:	˫��Ȧ�����ࣨ���������һ����Ȧ���д������ܣ�
*********************************************************************/

#ifndef MV_PHYSIC_LOOP
#define MV_PHYSIC_LOOP


#include <fstream>
#include "MvLine.h"
#include "LoopObj.h"

//#define DEBUG_SAVE_TS_COUNTER_PAIR

struct _LoopObj;

#ifndef  MAXINT
#define MAXINT 65536
#endif



// ����ǰ��β�ƣ�Զ����ȦΪ���Ϊ0��������Ȧ���Ϊ1
typedef struct _LoopInfo
{
	int nRoadIndex;        // �������
	MvLine line0;          // ���Ϊ0����Ȧ��ͼ���е�λ��
	MvLine line1;          // ���Ϊ1����Ȧ��ͼ���е�λ�á�
	float  dis;            // ��Ȧ���루m��
}LoopInfo;



#define EAT 40              // counter <-> ts�Լ�¼�ĸ�����

#define NEW_METHOD          // ֧�ֳ�������Ȧ��5m����ࣩ

class MvPhysicLoop
{
public:

	//
	MvPhysicLoop(const MvFindTargetByVirtualLoop *pFtg, int nRoadIndex, MvLine line0, MvLine line1, float fLineDis, int nDefaultDir = 1);

	//
	~MvPhysicLoop();

	//
	bool Process(bool b0, bool b1, int64 counter, int64 ts, _LoopObj **vli);

	//
	void SetDelay(int nDelay);

	// 
	int GetDelay() const;


	// ��ȡ��Ȧ��λ��
	void GetLoopPos(MvLine &l0, MvLine &l1) const;

	// ��ȡ������Ȧ��֮��ľ��룬һ��3.5m��4m��5m
	float GetDistance() const;


	void SetTsCounterPair(const std::vector<int64> &ts, const std::vector<int64> & counter);

private:

	//
	void RecordCounterTimePair(int64 counter, int64 ts);

	//
	int64 GetErrorCorrectedTime(int64 counter);
	

private:

	// ������Ƕ����VehicleLoopInfo
	typedef struct _VehicleLoopInfo
	{
		typedef enum _VehicleStatus
		{
			UNKNOWN_STATUS, PRESS_ONE, PRESS_TWO, LEAVE_ONE, LEAVE_TWO
		} VehicleStatus;


		int64 st0;                // ��ʼѹ��0��ʱ�䡣��λus
		int64 st1;                // ��ʼѹ��1��ʱ��
		int64 et0;                // �뿪0��ʱ��
		int64 et1;                // �뿪1��ʱ�䡣
		VehicleStatus status;     // 
		bool  dirFlag;            // ��ѹ0������ѹ1
		float spd;                // �ٶȣ�km/h
		float length;             // ������m
		int  nSerZero;            //����00״̬�ĸ���
		int  nforwardSerZero;            //��Ȧ00->10��01ǰ״̬Ŀ�����00״̬�ĸ���
		int64 nTcounter0;          //��ʼѹ��0��ʱ�䡣����λһ����������
		int64 nTcounter1;          //��ʼѹ��1��ʱ�䡣����λһ����������
		      




		_VehicleLoopInfo()
		{
			st0        = -1;
			st1        = -1;
			et0        = -1;
			et1        = -1;
			status     = UNKNOWN_STATUS;
			dirFlag    = true;
			spd        = 0.0;
			length     = 0.0;
			nSerZero = 0;
			nforwardSerZero = MAXINT;
			nTcounter0 = 0 ;
			nTcounter1 = 0;

		}

	}VehicleLoopInfo;


private:

	int m_nDefaultDir;

	// ��Ȧ��ͨ����
	int m_nRoadIndex;

	// ������Ȧ��ͼ���е�λ�á�
	MvLine m_line0;
	MvLine m_line1;

	// ������Ȧ֮���������루m��
	float  m_fLineDis;


     int  m_nSerzero;

	// ֮ǰ������Ȧ��״̬��
	bool m_lb0;
	bool m_lb1;

	// ֮ǰ�յ���ts��counter�ԡ���ֹ�ظ�����
	int64 m_lts;
	int64 m_lcounter;


	// �Ƿ��Ѿ��õ���ʼ���ݡ���һ�����ݲ�����һ��������ֻ������ʼ����
	bool m_bRecFirstData;

	// ������ʱʱ��(us)
	int m_nDelay;

	// ��������ֵ
	int64 m_counter[EAT];

	// ʱ�䣨us��
	int64 m_ts[EAT];

	int m_nNextPos;
	int m_nCount;


	// ���ֱ�߲�����
	double m_k;
	double m_b;

	// �Ƿ���Ҫ������ϣ���ֹ�����ͬ������������˷�ʱ�䡣
	bool m_bNeedReCalc;
	map<int , bool> m_nRoadIndexUpdata;


	//
	_LoopObj* m_pLoopObj;


#ifdef NEW_METHOD
	int64 m_nLastLoop0; //��һ����Ȧ0�����ط���ʱ��
	int64 m_nLastLoop1;
#endif


	//Ϊ��׼ȷ�ж���ȦĿ��ĳ�ʼ���򣬱�����һ�����������Ϣ,Note������Ƕ೵������Ȧ���ܲ����ã�����
	int m_lastVehDir;  //��һ������ʻ����-1����β�ƣ�0����δ֪��1����ǰ�ƣ�
	bool m_bPressTwo;  //�Ƿ�ͬʱѹ��������Ȧ��
	bool m_bLastVehPressTwo;  

	VehicleLoopInfo *m_pVLI1;
	VehicleLoopInfo *m_pVLI2;



	#ifdef DEBUG_SAVE_TS_COUNTER_PAIR
		std::ofstream m_ofs;
	#endif

	int m_nRoadDir;  //��·����
	const MvFindTargetByVirtualLoop * m_pFtg;
};



#endif
