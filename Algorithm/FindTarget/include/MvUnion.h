#ifndef MV_UNION
#define MV_UNION

#include <vector>
#include "SensedObject.h"
#include "Car.h"
#include "MvFindTargetByVirtualLoop.h"
#include "MvLine.h"
#include <iomanip>
//#include "MvLoopManager.h"

struct _LoopObj;
class MvLoopManager;
class MvRadarSpeed;
class Mv_LoopShutterLight;
//class MvFindTargetByVirtualLoop;

//class Car;
//class SensedObject;

typedef struct _MvUnion
{
public:

	// union������car���󼯺�
	std::vector<Car*> cars;

	// û��ʹ��
	std::vector<SensedObject*> vlpObjs;

	// union������loopObj
	_LoopObj* loopObj;	


	// union��id
	int id;




	int64 tsOutput; // ���һ�����ʱ�䡣��ʼ-1

	unsigned int uLastOutputSeq;//���һ�����ʱ֡�š�

	int nOutputTimes;  //���������

	// ��ǽ��������һ�����֮�����������ݡ��������˱仯
	bool fresh;

	bool bDroppedForShutter;  //�ֶ����ڣ���β�Ʊ�����ȡ������ͼ���߿��������ƣ��������

	_MvUnion()
	{
		loopObj        = NULL;
		fresh          = true;
		tsOutput       = -1;
		uLastOutputSeq = 0;
		nOutputTimes   = 0;
		bDroppedForShutter = false;	

		_MvUnion::nIdGen += 1;
		id = _MvUnion::nIdGen;
		bUnionStat = false;
	}


	// ȡ����Ӧ�����������
	bool GetOutput(int nDirection, MvLoopManager *pLoopManager, MvFindTargetByVirtualLoop* pFtg, MvRadarSpeed *pRadar, FILE *pFile, Mv_LoopShutterLight *p_mLoopShutter,bool bFlagDsp,/*�Ƿ���dsp��Ȧ����*/ unsigned int uFrameSeq, Time_Mode mode, CarInfo &ci);


	void SetFresh()
	{
		fresh = true;
	}


	//�����Ѿ�union�Ѿ��ҵ���ͼ
	void SetUnionStat( bool bStat);
	//�����Ƿ��Ѿ���Ӧ��ͼ
	bool GetUnionStat();

	Car* GetAssocCar();

private:

	static int nIdGen;
	bool   bUnionStat;

}MvUnion;

#endif
