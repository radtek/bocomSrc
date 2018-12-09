// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <map>
#include <vector>

#include "Car.h"
#include "Calibration.h"
#include "SynCharData.h"
#include "MvFindTargetByVirtualLoop.h"
#include "MvTrack.h"
#include "MvSurf.h"

//class Car;
class MvFindTargetByVirtualLoop;

class CarManager
{
public:

	CarManager(MvFindTargetByVirtualLoop *pFtg, MvSurf *pSurf);

	~CarManager();
	
	std::vector<Car*> lastFrameCars;

	// ��ʱ��˳���ȼ������ĳ��Ʒ���ǰ�档����ķ��ں��档
	std::vector<Car*> cars;


	void UpdateCar(const std::vector<CarInfo>& vecCarNums, unsigned int frameSeq, FindTargetElePolice::MyCalibration *pCalib, const std::vector<MvTrack*> &tracks, IplImage *previousImage[], int64 *lastTimeStamp, unsigned int *lastFrm);

	


	void Delete(int64 timestamp);

	//void Output(int64 timestamp, unsigned int frameSeq, std::vector<CarInfo> &output, std::vector<ObjSyncData> &vecObjSyncData);

	void SetDirection(int nDirection=0);//direction: 0��Զ������1�ɽ���Զ 

	Car* GetCarById(unsigned int id) const;

	// ��pSrc�ϲ���pDest��ɾ��pSrc
	//void MergeCars(Car *pDest, Car *pSrc);

	//void ClearAll();
	void WriteCarsToFile(unsigned int uFrameSeq);

	// ���ض��������ض��ķ�Χ���ѳ��Ƽ�¼������
	int CountCars(std::vector<Car*>::const_iterator from, int nLeftPos, int nRightPos);

	// ɾ��������ĳ��ƣ�������Ƽ���������٣�����������һ�����ƽ��������м䣬�򲻺���
	void RmUnresonableCars(int64 ts);


	//bool HasBigVehAfter(int64 ts);

	//�õ���ĳһ֡����ĳ��ӣ�
	std::vector<Car *> GetCarsNearFrame(unsigned int uFrame);

private:
	Car* AddCar(CarInfo cn, MyCalibration *pCali);

	// ���ڣ��羯��
	void _UpdateCar(const std::vector<CarInfo>& vecCarNums, unsigned int frameSeq, FindTargetElePolice::MyCalibration *pCalib, const std::vector<MvTrack*> &tracks, IplImage *previousImg[], int64 *lastTimeStamp, unsigned int *lastFrm);

	// ����Υ�¼����
	void _UpdateCarOnBusVioDet(const std::vector<CarInfo>& vecCarNums, unsigned int frameSeq, FindTargetElePolice::MyCalibration *pCalib, const std::vector<MvTrack*> &tracks);


	// CarId��pCar��map
	std::map<unsigned int, Car*> mapCarIdToPointer;
	
	//direction: 0��Զ������1�ɽ���Զ 
	int m_nDirection;

	MvFindTargetByVirtualLoop* m_pFtg;
	
	MvSurf *m_pSurf;


#ifdef DES_ROAD_STAT
public:
	void mvDesCarRoadState();
#endif
};

#endif
