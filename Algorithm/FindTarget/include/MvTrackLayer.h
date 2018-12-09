#ifndef MV_TRACK_LAYER_H
#define MV_TRACK_LAYER_H

#include <fstream>
#include <vector>
#include "MvCornerLayer.h"
#include "MvTrack.h"

#include "MvPolygon.h"
#include "disjoint-set1.h"
#include "OpticalFlowHelper.h"
#include "StdAfx.h"

using namespace std;

#define TRACK_MAX_NUM 1024


class MvTrackLayer
{
public:

	MvTrackLayer(MvCornerLayer *pCornerLayer);

	~MvTrackLayer();

	// ���¡�����track
	void UpdateTracks(const std::vector<MvCorner*> &vecCornerIndex, const unsigned int uFrameSeq,const  int64 ts, const unsigned int uTimestamp,
		const MyCalibration *pCalib,const  MvMaxSize *p_Maxsize);

	void Speed_UpdateTracks(MvCorner** pCors, int nCount, const unsigned int uFrameSeq, const int64 ts,const  unsigned int uTimestamp,
		const MyCalibration *pCalib, const MvMaxSize *p_Maxsize);

	void UpdateTracks(MvCorner** pCors, int nCount, const unsigned int uFrameSeq, const int64 ts,const  unsigned int uTimestamp,
		const MyCalibration *pCalib, const MvMaxSize *p_Maxsize);

	// ɾ��������Ĺ켣��
	void RmErrorTrack(const unsigned int uDelta,const unsigned int uFrameSeq,const CvRect MaskRect);

	// ɾ��û�õ�track
	void RmUselessTracks();

	//
	void SetPreitCornImgs(IplImage *PredImg, const unsigned int uFrameSeq, const int64 ts,
		const unsigned int uTimestamp,
		const FindTargetElePolice::MyCalibration *pCalib,const  MvMaxSize *p_Maxsize,CvRect CarRioRec
		,const vector<CvRect> &GrouArea);


	// ɾ��������Ĺ켣��
	void RmUnreasonableTrack();

	// ɾ�����һ�θ��±�uFrameSeqС�Ĺ켣
	void RmTracksBefore(unsigned int uDelta, unsigned int uFrameSeq);

	void RmTracksBeyondMask(CvRect MaskRect);
	
	void MoveTrackAddress(int nTrackIndex);


	// ��tracks
	void DrawTracks(IplImage* img, unsigned int uFrameSeq);

	void DrawCurrenTracks(IplImage* img, unsigned int uFrameSeq);


	// ��ȡ���һ�θ��¹켣ʱ����Ծ���õ�����,�����¼Ӻ͹��Ƶģ��Ĺ켣������
	//void GetLastTracks(std::vector<int> &lstTrackIndex);

	
	// ��ȡ���һ�θ��¹켣ʱ����Ծ���õ�����,�����¼Ӻ͹��Ƶģ��Ĺ켣��ָ�롣
	
	void GetLastTracks(const  MvMaxSize *p_Maxsize,unsigned int uFrameSeq, std::vector<_MvTrack*> &lstTrackPointer, std::vector<_MvTrack*> &lstEleTrackPointer,bool bIsDay);


	// ����������ȡ�ù켣
	  _MvTrack* GetTrackPointerByIndex(int index);

	// GetLastFrameTracks();

	// 

	void WriteTracksToTxt(std::ofstream &ofs);


	// ����켣֮����벻���ԡ�ͬһ�����ϵķ������켣Ӧ�þ��нϺõľ��벻���ԡ�
	static void DisKeeplity(std::vector<MvTrack*> &tracks, float& vec, float &scalar);


	// ��һ��track��universe����±�����tracks����±���ͬ��
	static Universe* GenTracksUniverse(const std::vector<MvTrack*> &tracks);


	


	// ����ÿ��track���һ��λ�õ���ɵļ��ϵ����rect
	static CvRect GetBoudingRect(const std::vector<MvTrack*> &tracks);

	// ����ÿ��track���һ��λ�õ���ɵļ��ϵ����rect
	static CvRect GetBoudingRect(const std::vector<MvTrack*> &tracks1, const std::vector<MvTrack*> &tracks2);
	
	// ����ÿ��track�����ڶ���λ�õ���ɵļ��ϵ����rect
	static CvRect GetSecBoudingRect(const std::vector<MvTrack*> &tracks);

	// �ӹ켣����src����ȡ������һ���ǵ���rgn������Ĺ켣��
	static void GetTracksInRegion(const std::vector<MvTrack*> &src, std::vector<MvTrack*> &dest, CvRect rgn);
	static CvRect GetRecTracksInRegion(const std::vector<MvTrack*> &src, CvRect rgn);

	
#ifdef TRACK_GROUP_LGW

	// �ӹ켣����src����ȡ������һ���ǵ���rgn������Ĺ켣��
	static void GetTracksInRegion(const std::vector<MvTrack*> &src,std::vector<MvTrack*> &RemainTrack,
		std::vector<MvTrack*> &dest, CvRect rgn);

	// �ӹ켣����src����ȡ������һ���ǵ���rgn������Ĺ켣��
	static void GetTracksInRegion(const std::vector<MvTrack*> &src, std::vector<MvTrack*> &dest, CvRect rgn,int nID);
	static void SetTracksDisToPlate( std::vector<MvTrack*> &src,CvPoint Plate);
	static void GetPlateByTracksDis(const MvMaxSize *pMaxSize,const std::vector<MvTrack*> &src,
		GroupFlow *pGrowFlow,CvPoint &Plate);
	static void SetTracksCarIdAndPlateDis(std::vector<MvTrack*> &src,unsigned int uCarId,CvPoint Plate,bool bPark =false);


#endif
	
	//��ȡ�켣������������ҵĹ켣��false��ȥ����ߵ�
	static _MvTrack* GetSideTrack( std::vector<MvTrack*> &tracks,bool RigTrack= true);

	// ��ȡ�켣�����һ�����ǵ�����ࡣ
	static _MvTrack* GetLongestTrack(const std::vector<MvTrack*> &tracks);

	// �ӹ켣����src����ȡ������һ���ǵ���poly������Ĺ켣��
	static void GetTracksInRegion(const std::vector<MvTrack*> &src, std::vector<MvTrack*> &dest, const MvPolygon &poly);


	static void RemoveTracksInRgn(const std::vector<MvTrack*> &src, std::vector<MvTrack*> &dest, CvRect rgn);

	// �Թ켣���պ�ѡ������������
	static void SortTrackByInformalTimes(std::vector<MvTrack*> &tracks);

	// �ж�pTrackA�ĺ�ѡ�����ǲ��Ǵ���pTrackB
	static bool IsTrackAHaveMoreInformalTimesThanTrackB(const MvTrack* pTrackA, const MvTrack *pTrackB);

	// �ж�pTrack��X��С��������
	static bool IsTrackXUp(const MvTrack* pTrackA, const MvTrack *pTrackB);
	

	// ��ȡts�й켣���һ���ǵ㵽pt��y��������ƽ��ֵ��
	static float GetTracksToPointDis(const std::vector<MvTrack*> &ts, CvPoint pt);


	 void DrawTracks(const std::vector<MvTrack*> &tracks, IplImage *img, CvScalar color=CV_RGB(0, 0, 0)
		,bool bDiscFront = false);

	// ��ȡ�켣�˶�����ķ���
	static float GetTrackDirVar(const std::vector<MvTrack*> &tracks);

	// ͳ��tracks�У�travelLength����fTravLen�����ҽǵ��������fCorCount�Ĺ켣������
	static int CountTracks(const std::vector<MvTrack*> &tracks, float fTravLen, float fCorCount);


	// ��֪ĳ��Ŀ����x֡��λ��rect���Լ�Ŀ����x֡�������Ĺ켣������Ŀ����x-1��x-2��x-3...֡��λ�á�
	static std::map<unsigned int, CvRect> GoBack(MvMaxSize *pMaxSize, unsigned int x, CvRect rect, const std::vector<MvTrack*> &tracks);

	

private:

	MvTrackLayer(const MvTrackLayer& l);

	MvTrackLayer & operator = (const MvTrackLayer &l);

	// ����µĹ켣��nIndex�ǵ㡣�����¹켣��������
	int AddNewTrackByCornerIndex(int nIndex);

	// 
	int AddTrack(const _MvTrack &t);

	void SetTrackIndex(_MvTrack *pTrack, int nIndex);
	


private:
	
		
	// �洢���һ�θ��¹켣ʱ����Ծ���õ�����,�����¼Ӻ͹��Ƶģ��Ĺ켣������
	std::vector<int>     m_vecLastTrackIndex;

	// �洢���һ�θ��¹켣ʱ����Ծ���õ�����,�����¼Ӻ͹��Ƶģ��Ĺ켣��ָ�롣
	std::vector<_MvTrack*> m_vecLastTrackPointer;


	// �洢���һ�θ��¹켣ʱ����Ծ���õ�����,�����¼Ӻ͹��Ƶģ��Ĺ켣��ָ�롣
#ifdef SPEED_UP
       _MvTrack** m_vecLastTracksAll;
	   int m_LastTracksNum;
#else
	std::vector<_MvTrack*> m_vecLastTracksAll;
#endif
	


	// �ǵ�����
	MvCornerLayer *m_pCornerLayer;
	


	// memory storage
	CvMemStorage *m_pMem;

	// �洢�켣
	CvSet        *m_pTrackSet;

	int  *g_pTrack_Index;//�洢�켣�����ţ�0~1024��

	_MvTrack  *g_Track;
	int m_TrackPos; //ָ��켣���洢����һ��λ��
	
};



#endif