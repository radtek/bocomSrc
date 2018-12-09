#ifndef MV_PHYSIC_LOOP_MANAGER
#define MV_PHYSIC_LOOP_MANAGER

#include <map>
#include <vector>
#include "MvLine.h"
#include "MvPhysicLoop.h"
#include "Calibration.h"

//using namespace std;
using namespace PRJ_NAMESPACE_NAME;



// ����ǰ��β�ƣ�Զ����ȦΪ���Ϊ0��������Ȧ���Ϊ1
typedef struct _LoopInfo
{
	int nRoadIndex;        // �������
	MvLine line0;          // ���Ϊ0����Ȧ��ͼ���е�λ��
	MvLine line1;          // ���Ϊ1����Ȧ��ͼ���е�λ�á�
	float  dis;            // ��Ȧ���루m��
}LoopInfo;



class MvPhysicLoopManager
{
public:

	MvPhysicLoopManager();

	~MvPhysicLoopManager();

	void SetLoopInfo(const std::vector<LoopInfo> &li, int nDelay);


	void Update(int nRoadIndex, bool b0, bool b1, int64 counter, int64 ts);

	// ����2��ʱ�䣬����㲻���򷵻�-1.
	// t1�ǳ��Ƹ��ܼ����ʱ�䡣t2�ǳ������һ���ܼ����ʱ�䡣
	// lnUp, lnDn�ֱ�Ϊ���Ƽ����������ߺ����ߡ�
	// ʱ�䵥λ��Ϊus��
	bool ComputerPlateDetectTime(const VehicleLoopInfo &vli, MvLine lnUp, MvLine lnDn, int64 &t1, int64 &t2);


	// ���㳵����һ��ѹ������Ȧ��ʱ������һ��ѹ������Ȧ��ʱ�䡣
	// vlpLine Ϊvlp����ͼ���е�λ�á�
	bool ComputerPressVlpTime(const VehicleLoopInfo &vli, MvLine lnUp, int64 &t1, int64 &t2);


	MvLine GetLoopImagePos(int nRoadIndex, bool bNo0OrNo1);


	void* GetAssocObject(int nVliId) const;


	int   GetAssocType(int nVlidId) const;


	void  Delete();


	void  SetLoopWorldCoordinate(MyCalibration *pCalib);

	// ����Ȧ����ͼ�ϡ�
	void DrawLoops(IplImage *img);


public:

	
	// ����ѹ��Ȧ��Ϣ��
	std::map<int, VehicleLoopInfo> m_mapVehicles;

	//
	std::map<int, int>             m_mapStatus; //1��������ԣ�>=2���ȴ�ɾ��

	// int��vli->id�� void*����vli�����Ķ���
	std::map<int, void*>           m_mapVliAssoc;

	// �������͡��복�ƹ���ȡ1�� ��Ŀ�����ȡ2��û�й���ȡ0
	std::map<int, int>             m_mapAssocType;


	std::map<void*, int>           m_mapVliAssocV;

	

	// �����ٶ�״̬�ºͳ��ƻ�Ŀ��ƥ���ϣ�֮���ƻ�Ŀ������ɾ���ˡ�
	// ���������ɾ����֮��������������ܵ��¶౨�����������������
	// ��ʱ����m_mapVehicles����Ϣɾ��������m_vecWaitDelete����һ����¼��
	// �ڳ�����Ϣ���ֺ󣬻��߱�ĳ���ѹ��Ȧ��Ϣ���ֺ󣬽����Ǵ�m_mapVehicles
	// ��ɾ������Ϊ��ʱ���ǲ����ٸ����ˡ�
	// vector<int>               m_vecWaitDelete;

private:

	// ͨ����<->��Ȧ��
	std::map<int, MvPhysicLoop*>   m_mapLoops;

	// ͨ����
	std::map<int, LoopInfo>        m_mapLoopInfo;


	
};


#endif