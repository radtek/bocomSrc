#ifndef LOOP_OBJ
#define LOOP_OBJ

#include "cxcore.h"
#include "MvUnion.h"
#include "MvLine.h"
#include "CarInfo.h"
#include "MvFindTargetByVirtualLoop.h"


//struct _MvUnion;
//class MvFindTargetByVirtualLoop;

// ��Ȧ�����Ŀ��
typedef struct _LoopObj
{
public:
	int64 st;          // ѹ�ϴ�����Ȧ��ʱ�䣬us
	int64 et;          // �뿪������Ȧ��ʱ�䣬us
	float spd;         // km/h С��0��ʾδ֪���ٶȷ�����dir������
	int   dir;         // ����0��ʾ��Զ������С��0��ʾ�ӽ���Զ������0��ʾ��֪����
	int   id;          // ���
	int   nRoadIndex;  // ��·��š�

	bool  loop0_triggered;  //��������Ȧ0��
	bool  loop1_triggered;  //��������Ȧ1��
	bool  haveVeto; //�Ƿ��Ѿ���һ������Ȧ0���㣡

public:

	_LoopObj(int nRoadIndex);
	

	// ���ù�����Union
	void SetAssocUnion(_MvUnion *pUnion)
	{
		AssocUnion = pUnion;
	}

	// ��ȡ������Union
	_MvUnion* GetAssocUnion() const
	{
		return AssocUnion;
	}

	// ���øտ�ʼѹ��������Ȧ��ʱ��
	void SetEnterTime(int64 st)
	{
		if (this->st != st)
		{
			this->st = st;
			OnDataChanged();
		}
	}

	// �����뿪������Ȧ��ʱ��
	void SetLeaveTime(int64 et)
	{
		if (this->et != et)
		{
			this->et = et;
			OnDataChanged();
		}
	}

	// �����ٶ�
	void SetSpeed(float fSpd)
	{
		if (this->spd != fSpd)
		{
			this->spd = fSpd;
			OnDataChanged();
		}
	}

	// ����
	void SetDir(int nDir)
	{
		if (this->dir != nDir)
		{
			this->dir = nDir;
			OnDataChanged();
		}
	}


	// ����Ѿ�������Union����ֹ���뵼�¶౨��
	void SetEnterUnionList()
	{
		bEnterUnionList = true;
	}

	// ��ȡ�Ƿ�����Union
	bool GetEnterUnionList() const
	{
		return bEnterUnionList;
	}

	// �жϳ����ܲ��ܼ��
	//bool IsPlateCanBeDetected(int64 ts, MvLine l0, MvLine l1, CvRect roiCarNum);

	// ���㳵��
	bool GetPlateDetectdTimePeriod(MvLine l0, MvLine l1, MvLine lnUp, MvLine lnDn, /*CvRect roiCarNum, */int64 &tf, int64 &tt);

	// fLen ������m��
	bool GetVehicleLength(float &fLen);


	// �ж��Ƿ����ɾ��
	bool CanDelete() const;


	// ��ȡ�����Ϣ���洢��ci����
	void GetOutput(MvLine l0, MvLine l1, MvFindTargetByVirtualLoop *pFtg, CarInfo &ci) const;


	// ��ȡ��������������Union������car����
	std::vector<Car*> GetAssocCars() const;


private:

	_MvUnion *AssocUnion;// �����Ľ����


	// �Ƿ�����union��
	bool bEnterUnionList;

	void OnDataChanged();



	
private:

	static int nIdGen;





} LoopObj;




#endif
