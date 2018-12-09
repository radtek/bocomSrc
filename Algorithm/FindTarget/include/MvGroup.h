#ifndef MV_GROUP_H
#define MV_GROUP_H



#include <map>
#include <vector>
#include "cxcore.h"
#include "Car.h"
//#include "SensedObject.h"
#include "MvTrackLayer.h"
#include "MvViolationDetecter.h"
#include "ViolationInfo.h"



//using namespace std;

//struct SensedObject;

#define  BINDA_MAX_NUM 10


typedef struct _MvGroup
{

public:
	
	_MvGroup() {};
	// ���캯��
	_MvGroup(MvTrackLayer *pTrackLayer, unsigned int uFrameSeq/*, CvRect rectCarPosWhenGroupFormed*/);


	// ��ȡgroup�ı�š�ÿ��group��һ��Ψһ�ı�š�
	int GetGroupId() const;

	inline void SubId()
	{
		_MvGroup::nGroupIdUsed--;
	}
	inline void SetId(int id)
	{
		_MvGroup::nGroupIdUsed = id;
		m_nGroupId = id;

	}

	// ���ݹ켣���Ƴ���֮ǰλ��
	void GoBackward(FindTargetElePolice::MyCalibration *pCalib, MvMaxSize *pMaxSize);


	// ����group�������ĳ��ơ�
	void SetCar(Car *pCar);

	// 
	Car* GetCar() const;


	SensedObject* GetAssocSensedObj() const;

	void SetAssocSensedObj(SensedObject* pObj)
	{
		m_pAssocSensedObj = pObj;
	}


	// ��Group��ɾ��ǰ��group��Ҫ�����ƺ�����
	void Delete();


	// ����group��uFrameSeq֡��λ�á��������Ĺ켣�������ù켣��m_nGroupId.
	void Update(unsigned int uFrameSeq, CvRect rectGroup, const std::vector<MvTrack*> &vecTracks);

	//��ȡָ��֡��Groupλ�ã�
	bool GetGroupPos(unsigned int uFrmSeq, CvRect &rectPos) const;

	// ��ȡgroup���һ�θ���ʱ��ͼ��������λ�á�
	CvRect GetGroupLastPos() const;


	// ��ȡgroup��һ�θ���ʱ��λ��
	CvRect GetFirstPos() const;


	// ȡ��group����ʱ�̵�֡�š�
	unsigned int GetGroupGenFrameSeq() const;


	// Group�γ���һ֡Group��ͼ���е�λ�á�
	CvRect GetGroupGenPos() const;


	// Group�γ���һ֡������ͼ���е�λ�ã����ݳ��Ʋ²�ģ���
	//CvRect GetGroupGenCarPos() const;
	

	// ��ȡgroup�����ڶ��θ���ʱ��λ��
	CvRect GetGroupSecLastPos() const;


	// ��ȡ��Ĺ켣��
	MvTrack* GetLongestTrack() const;

    


	// ��ȡgroup��һ�θ���ʱ�������Ĺ켣��
	void GetGroupLastTracks(std::vector<int> &vecTracks) const;

	
	// 
	void GetGroupLastTracks(std::vector<MvTrack*> &vecTracks) const;


	


	// 
	int GetGroupLastTrackCount() const;

	unsigned int GetFirstFrameSeq() const;
	unsigned int GetlastSecdFrameSeq() const;
	


	int GetGroupHistorySize() const;


	// ��ȡgroup��һ�θ���ʱ��֡�š�
	unsigned int GetLastUpdateFrmSeq() const;

	// ��group�Ŀ�򻭵�img�ϣ�����������Ĺ켣����ͼ�ϡ�
	void DrawGroup(IplImage *img, unsigned int uFrameSeq) const;

	void DrawGroupRet( IplImage *img,CvPoint point =cvPoint(0,0) ) const;

	// ����groupλ����ʷ��¼��
	void CopyHistory(std::map<unsigned int, CvRect> &mapHist);

	// ��mapHist����ļ�¼��䵽m_history���棬���m_history�Ѿ��еľͲ�����ˡ�
	void FillHist(std::map<unsigned int, CvRect> &mapHist);


	


	friend class MvViolationDetecter;

private:
	
	// Group�γ���һ֡������ͼ���е�λ�ã����ݳ��Ʋ²�ģ���
	//CvRect m_rectCarPosWhenGroupFormed;

	// group id��������
	static int nGroupIdUsed;


	// group�ı�š���1��ʼ��
	int m_nGroupId;


	// group������֡�š�������һ����m_history��begin().
	// ��Ϊgroup����ʱ�������������ʱ�䵹�ˣ��²����ڽ���ʱ��λ�á�	
	unsigned int uGenFrameSeq;


	// ��һ�θ���ʱ��֡�š�
	unsigned int m_uLastUpdateFrmSeq;


	// Group�������ĳ��ƺ��롣
	Car *m_pCar;


	// ������������ȦĿ�ꡣ
	SensedObject *m_pAssocSensedObj;


	// Group�������Ĺ켣
	std::vector<int> m_vecTracks;





	// 
	//bool m_bViolationDetectIgnore;


	// ���м����ԡ�
	//bool m_bReverseViolationIgnore;


	// �켣�����
	MvTrackLayer *m_pTrackLayer;

	CvPoint   m_LastTrackVec;

	
	
	// group��֡��ͼ���ϵ�λ�õļ�¼��
	std::map<unsigned int, CvRect> m_history;
    int  m_BiandDaoDir[BINDA_MAX_NUM];

	


	// 
	typedef std::map<unsigned int, CvRect>::iterator GroupHistoryIt;
	typedef std::map<unsigned int, CvRect>::const_iterator GroupHistoryConstIt;


	// ����group id
	//void SetGroupId(int nId);

public:
	// Group�������Ĺ켣
	std::vector<MvTrack*> m_vecTracksPointer;
	bool m_bDelayedOutput;  //Group��ǰ�Ƿ��ڴ���Ƶȴ�����׶Σ�
	bool m_bMetReServe;//�Ƿ���������
	bool m_bUseCarFram;

	

} MvGroup;


#endif