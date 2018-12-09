#ifndef MV_UION_MANAGER
#define MV_UION_MANAGER

#include <map>
#include <vector>
#include "CarManager.h"
#include "MvLoopManager.h"
#include "MvUnion.h"
#include "MvFindTargetByVirtualLoop.h"

using namespace PRJ_NAMESPACE_NAME;


class MvLoopManager;

class MvUnionManager
{
public:

	// 
	MvUnionManager(CarManager *pCarManager, MvLoopManager* pLoopManager, VirtualLoop *pVlp, MvFindTargetByVirtualLoop *pFtg);

	~MvUnionManager();

	// �����ơ���ȦĿ�ꡢvlpĿ���ȡ�����γɽ���塣
	void Update(unsigned int uFrameSeq, int64 ts);


	// ��ȡ��Ҫ�����union������ret
	void Output( std::vector<_MvUnion*> &ret, unsigned int uFrameSeq, int64 ts );


	//



	// ɾ����Ҫɾ����Union
	void Delete(unsigned int uFrameSeq, int64 ts);

private:


	// �����Id-> ����塣�洢�����е�union
	std::map<int, _MvUnion*> m_mapUnions;


	//
	CarManager*    m_pCarManager;
	MvLoopManager* m_pLoopManager;
	MvFindTargetByVirtualLoop* m_pFtg;
};

#endif
