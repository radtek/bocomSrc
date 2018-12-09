#ifndef MV_LOOP_MANAGER
#define MV_LOOP_MANAGER


#include <vector>
#include <map>
#include "LoopObj.h"
#include "MvLine.h"
#include "MvPhysicLoop.h"


struct _LoopInfo;
struct _LoopObj;
class MvPhysicLoop;


// ����������LoopObj����
class MvLoopManager
{
public:

	// 
	void Init(const MvFindTargetByVirtualLoop *pFtg, const std::vector<_LoopInfo> &li, int nDelay);

	// 
	void Destroy();

	// ��ʱ���tf��tt�ڼ����Ŀ�������
	int CountObjDuring(int nRoadIndex, int64 tf, int64 tt, float fOverlapRatio);


	// ������Ȧ�źŽ��д���
	void Process(int nRoadIndex, bool b0, bool b1, int64 counter, int64 ts);


	// ɾ������Ҫ�ġ��ϵ�LoopObj
	void Delete(int64 ts);


	// ����Ȧ����ͼ�ϡ�
	void DrawLoops(IplImage *img);


	// ��ȡ��Ȧ��ͼ����������ϵ���λ��
	void GetLoopPos(int nRoadIndex, MvLine &l0, MvLine &l1);


	// ��ȡ����LoopObj
	const std::map<int, _LoopObj*>& GetLoopObjs() const;


	// ���ݳ����ŵõ���Ӧ������MvPhysicLoop����
	MvPhysicLoop* GetPhysicLoopByIndex(int nIndex);


private:

	// ��ȦĿ���¼��Ŀ���idΪ��������¼����LoopObj����
	std::map<int, _LoopObj*> m_mapLoopObjs;


	// ͨ����<->��Ȧ����¼����MvPhysicLoop����
	std::map<int, MvPhysicLoop*>   m_mapLoops;

};



#endif
