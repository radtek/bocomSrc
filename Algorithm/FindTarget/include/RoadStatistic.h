#ifndef ROAD_STATISTIC_H
#define ROAD_STATISTIC_H

#include <vector>
#include <map>
#include <list>
#include "StdAfx.h"
#include "CarInfo.h"
#include "MvChannelRegion.h"

//using namespace std;

// ͳ����������
enum STAT_TYPE
{
	STAT_FLUX,	       //��������
	STAT_SPEED_AVG,	   //ƽ������
	STAT_ZYL,		   //ƽ������ռ����
	STAT_QUEUE,		   //���г���
	STAT_CTJJ 	       //ƽ����ͷ���
};

//ͳ�ƽ���ṹ
typedef struct _STAT_RESULT
{
	int nChannelIndex;          //�������
	STAT_TYPE sRtype;		    //�������
	double value;				//ͳ��ֵ�����û�����ø�����ʾ��
	_STAT_RESULT ()
	{
		nChannelIndex = 0;
		value = -1;
	}
}STAT_RESULT;


//ͳ�ƽ������
typedef std::list< STAT_RESULT> StatResultList;



class RoadStatistic
{
public:
	
	RoadStatistic(const std::vector<ChannelRegion> &vecRoadChannels);


	void GetStatisticData(int nRoadIndex, float &fAvgSpd, float &fVehicleDis, float &fRoadOccPer, float &fQueueLength, float &fFlux);

	void GetStatisticData(StatResultList &ret);


	void OnCarPlateDetected(const CarInfo *pCarInfo);


	void Reset();


private:

	// ����
	std::vector<ChannelRegion> m_vecRoadChannels;


	std::map< int, std::vector<CarInfo> > m_mapPlateRecord;


	
};

#endif