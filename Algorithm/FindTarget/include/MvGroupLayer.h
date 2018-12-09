#ifndef MV_GROUP_LAYER_H
#define MV_GROUP_LAYER_H

#include <list>
#include <vector>
#include <map>
#include "MvTrackLayer.h"
#include "MvGroup.h"
#include "MvMaxSize.h"
#include "disjoint-set1.h"
#include "MvPolygon.h"
#include "MvRectTracker.h"
#include "MvFindTargetByVirtualLoop.h"
#include "MvRelabelEventHandler.h"


//using namespace std;
using namespace PRJ_NAMESPACE_NAME;

//class MvRectTracker;
class CarManager;
class MvFindTargetByVirtualLoop;
//struct _MvGroup;

class MvGroupLayer
{

public:
	
	// ���캯����
	MvGroupLayer(MvCornerLayer *pCornerLayer, MvTrackLayer* m_pTrackLayer, MvMaxSize *pMaxSize,
		MyCalibration *pCalib, MvFindTargetByVirtualLoop *pFtg);
	
	// ��������
	~MvGroupLayer();

	
	// �켣�����ࡣ�洢��һЩ�켣�����յ�����
	typedef struct _TrackSet
	{
		std::vector<MvTrack*> tracks;//�������Ĺ켣
		CvRect rect;// �켣������

		// ���㼯���й켣������group��
		bool GetTrackSetGroupId(int &nGroupId, int &nCount) const;

		int GetTracksCount() const;

		void mvGetMedainDirection( double &fx, double &fy ) const;

	} TrackSet;


	// ��tracks���зָ�ָ��һЩ���ϡ�
	void SegTracks( const std::vector<MvTrack*> &tracks, std::vector<TrackSet> &sets, 
		int nLeastCommonFrames = 3, float fPhyDis = 3.0, float fMotionSimility = 0.4 ,bool bPlate =false,CvRect 
		 PlateRec =cvRect(0,0,1,1),unsigned int uCarId =-1);



	// ���������
	_MvGroup* OnCarDetected( const std::vector<MvTrack*> &tracks, CvRect rgn, unsigned int uFrameSeq);


	// ���Ƴ��֡�
	void OnCarNumDetected(std::vector<ViolationInfo> &vis,const std::vector<MvTrack*> &vecTracks, const std::vector<Car*> vecCars, 
		unsigned int uFrameSeq, float fScaleX, float fScaleY, CarManager *pCarManager, 
		std::list<CvRect> &lstRectForDebug, std::list<MvPolygon> &lstPolyForDebug,const IplImage *img =NULL);


	// ɾ��һЩû�õ�Group
	void DeleteGroups(unsigned int uFrameSeq, unsigned int uInterval,std::vector<ViolationInfo> &vis);


	void MergeGroups(CarManager *pCarManager, unsigned int uFrameSeq,std::vector<ViolationInfo> &vis);


	_MvGroup* GetGroupById(int nGroupId);


	// ��trackset����groups��
	void UpdateGroups(unsigned int uFrameSeq, const std::vector<MvTrack*> &tracks, IplImage *img);

	//�õ�Group�˶�������ֹͣ�߷��ߵļнǣ�Ҫ��ֹͣ��Ҫ���ã�
	bool GetGroupMotionDir(_MvGroup *pGroup, /*unsigned int uStartFrmSeq, unsigned int uFinishFrmSeq,*/ const MvLine *stopLine, float fMinDis, float &motionAngle);
	// 
	bool GetGroupMotDirByRectTracker(MvGroup* pGroup, float fMinDis, float &vx, float &vy) const;

	bool GetGroupMotDir(_MvGroup *pGroup, double &fTrackMotX, double &fTrackMotY) const;

	bool IsGroupExist(int nGroupId);


	// �ж�group���һ�θ���ʱ���ǲ���ѹ��ĳ����
	MvLine* IsGroupOnLine(MvLine *pForeLine, MvLine *pLeftLine, MvLine *pRightLine, _MvGroup* pGroup,bool &bTurnState) const;

	bool IsGroupOnLine(_MvGroup *pGroup, const MvLine *pLine) const;

	// ��group������ĳ������Ǵ��ĸ������������ġ�
	bool GetGroupRoadIndex(_MvGroup *pGroup, std::vector<ChannelRegion> m_lstChannelsInfo, int &nRoadIndex, bool bFlag = false ) const;

	
	// ��Groups
	void DrawGroups(IplImage *img, unsigned int uFrameSeq,const std::vector<MvTrack*> &vecTracks);


	const MvRectTracker* GetPlateTracker() const;

	const MvRectTracker* GetCarTracker() const;


	void AddRelabelEvtListener(MvRelabelEventHandler *listener);


	MvMaxSize* GetMaxSize() const;
	void InformTrackTrans( unsigned int uFrameSeq, const vector<MvTrack*> &allTracks, IplImage *img );


	friend class MvViolationDetecter;
	// 
	//void BeforeTrackDeleteEventHandler(int nTrackIndex);

private:


	

	// ���²������Ƶ�groups
	void _UpdateNonPlateGroups(unsigned int uFrameSeq, const std::vector<MvTrack*> &allTracks, IplImage *img);

	// ���´����Ƶ�groups
	void _UpdatePlateGroups(unsigned int uFrameSeq, const std::vector<MvTrack*> &allTracks, IplImage *img);

	//
	bool SelectTracks(const Car *pCar, const std::vector<TrackSet> &sets, const CvRect &rectSelSetRgn,
		const std::vector<MvTrack*> &tracks, const MvPolygon &polySelTracksRgn, TrackSet &selSet);



	// ��������λ��ѡ��set����һϵ��set��ѡ��һ����rectSelRgnλ�ñȽ�ƥ���set��
	bool SelectSet(const std::vector<TrackSet> &sets, CvRect rectSelRgn, TrackSet &set ,bool MotoStyle = false);


	// ��tracks���зָ��ѡ��켣����set�����
	bool FormAndSelectSet(const std::vector<MvTrack*> &tracks, TrackSet &set, float dx = 0.0f, float dy = 0.0f);

	// ��set�γ�MvGroup
	void FormAddGroupByCarNum(TrackSet &set, unsigned int uFrameSeq, Car *pCar, CvRect carNumPos);


	
	// ɾ��group,����ֵ���group�Ƿ���ڡ�
	bool DeleteGroup(int nGroupId,std::vector<ViolationInfo> &vis);

	// 
	//static Universe* GenTrackUniverse(const vector<MvTrack*> &tracks);

	// ����groupӦ�þ��еĹ켣�������ٶ�������total�е�λ��Ϊpos������total��ʶ����������ȡnMaxCorners���ǵ㡣
	static int EstimateGroupTrackCount(CvRect pos, CvRect total);


	// ���ݳ��ƹ��Ƴ���ͼ����Ķ���Ρ�
	MvPolygon EstimateCarPolyByCarNum(CvRect rectCarNum, float fWidth, float fLength);


	
private:

	// group�������е�groups��int��ʾgroup�ı�š�
	std::map<int, _MvGroup> m_Groups;


	// �켣�����
	MvTrackLayer* m_pTrackLayer;


	// �ǵ�����
	MvCornerLayer *m_pCornerLayer;


	//
	MvMaxSize *m_pMaxSize;


	// Group�γ�ʱm_pCarPlateTracker��ʼ��¼����λ�á�Groupɾ��ʱ��Ӧ��plate��¼ɾ����
	MvRectTracker *m_pCarPlateTracker;

	// 
	MvRectTracker *m_pCarTracker;


	MyCalibration *m_pEleCalib;


	MvFindTargetByVirtualLoop *m_pFtg;



private:


	// ά��m_mapLastTryGenGroupSeq��¼������ɾ���ĳ��ƣ���m_mapLastTryGenGroupSeq��¼��ɾ����
	// ��ֹһЩ��¼��m_mapLastTryGenGroupSeqһֱ�ò���ɾ����
	// m_mapLastTryGenGroupSeq������������CarManager���Car������һЩ��ʱ��û�кܸߵļ�ʱ��Ҫ��
	// ���������Ѿ�ɾ����m_mapLastTryGenGroupSeq�ﻹ���ڸó�������Ҳ���ԡ�
	// ���Ե��ø÷���û���ϸ��λ��Ҫ��
	void KeepCarLastTryGenGroupSeq(CarManager* pCarManager);


	// CarId, frameSeq. �ϴ�ΪidΪcarid�ĳ����Բ���group��֡�ţ�������û�в���Group��
	// carɾ��ʱ��Ӧ�ļ�¼Ҫɾ����
	std::map<int, unsigned int> m_mapLastTryGenGroupSeq;



private:// ���±�����

	// ���±�������š�
	std::vector<MvRelabelEventHandler*> m_vecRelabelEvtListener;
	void BroadCastRelabelEvt( int nOldId, int nNewId );

};

#endif