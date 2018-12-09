// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   14:24
	filename: 	e:\BocomProjects\find_target_lib\include\MvRectTracker.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvRectTracker
	file ext:	h
	author:		Durong
	
	purpose:	��¼һ��rect��ÿһ֡��λ�á��ڵ羯�У����rect�����ǿ�ס���Ƶ�rect��Ҳ����
	�ǿ�ס����������rect��
*********************************************************************/


#ifndef MV_RECT_TRACKER
#define MV_RECT_TRACKER


#include <map>
#include "cxcore.h"


//using namespace std;

// ��¼ÿһ֡��ÿ������----��group��ʼ����
class MvRectTracker
{
public:

	// ����µĳ��ƽ��г���λ�ø��١�
	void AddNewRect(CvRect rectPos, int nRectId, unsigned int uFrameSeq);

	// ���¸����еĳ���λ��
	void UpdateRect(int nRectId, CvRect pos, unsigned int uFrameSeq);


	// ��ȡ���Ƶ�λ�á�
	bool GetRectPos(unsigned int uFrameSeq, int nRectId, CvRect &ret) const;


	// ��ȡ�������һ�θ��µ�λ��
	bool GetRectLastPos(int nRectId, CvRect &pos) const;

	//��ó������ϵ�һ��
     bool GetRectFristPos(int nRectId, CvRect &pos) const;

	 //��ȡͬһ���Ƽ��λ�õĸ���
	 int  GetRectNum(int nRectId) const;

	// ��ȡ���Ƶ����ڶ��θ��µ�λ��
	bool GetRectSecLastPos(int nRectId, CvRect &pos) const;


	unsigned int GetFirstTrackFrameSeq(int nRectId) const;

	unsigned int GetLastTrackFrameSeq(int nRectId) const;


	// ɾ��ĳһID��rect�ļ�¼
	void DeleteRectTrack(int nPlateId);


	// �ж�ĳһID��rect�Ƿ����ڼ�¼��
	bool IsRectTracking(int nRectId);

	// ��ĳһID��rect��λ�ü�¼����������
	void CopyRectPosTrack(int nRectId, std::map<unsigned int, CvRect> &t) const;

	// ��λ�ü�¼��Ϣ��䵽ĳһID��rect����֮��
	void FillRectTrack(int nRectId, const std::map<unsigned int, CvRect> &t);


	//void Delete(unsigned int uFrameSeq, CarManager *pCarManager);


private:

	


	// ֡��->λ��
	typedef std::map<unsigned int, CvRect> RectTrackRecord;
	typedef std::map<unsigned int, CvRect>::const_iterator TrackRecordConstIt;
	typedef std::map<unsigned int, CvRect>::const_reverse_iterator RevTrackRecordConstIt;
	typedef std::map<unsigned int, CvRect>::iterator TrackRecordIt;
	typedef std::map<unsigned int, CvRect>::reverse_iterator TrackRecordRIt;
	typedef std::map<int, RectTrackRecord>::const_iterator TracksConstIt;
	typedef std::map<int, RectTrackRecord>::const_reverse_iterator RevTracksConstIt;
	typedef std::map<int, RectTrackRecord>::iterator TracksIt;


	// PlateId to its tracks
	std::map<int, RectTrackRecord> m_tracks;

	

	



};

#endif