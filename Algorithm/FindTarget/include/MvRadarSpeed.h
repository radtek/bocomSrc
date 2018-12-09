// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
// author: wyj!
// date: 2010��10��13

// MvRadarSpeed�๦��:ͨ��Radar���ٵķ�ʽ�����������ٶȣ��޷�ʵ�־�ȷ��λ��
// �������˺ͷǻ�����������Ƶ�ٶȣ�

#ifndef MV_RADAR_SPEED
#define MV_RADAR_SPEED

#include "Mode.h"
#include "SensedObject.h"
#include "CarManager.h"
#include "Car.h"
#include "cxcore.h"
#include <map>

class CarManager;
class Car;

class MvRadarSpeed
{
public:

	MvRadarSpeed();

	~MvRadarSpeed();

	void Init(MvFindTargetByVirtualLoop *ftgVlp, CarManager *carManager, VirtualLoop *vlp, CvRect detectionRgn, std::vector<int> vecRoadIndex, Time_Mode mode, int delay = 0);

	void Destroy();
	
	//���浱ǰ�״��ٶȣ�
	void SetRadarSpeed(unsigned int frameSeq, int64 timeStamp, double speed, double fastSpeed);

	//�����״��ٶȼ���speed map��
	void UpdateRadarSpeedList();

	//����speed map����car�ٶȣ�
	bool CalcSpeed(void *pObj, int objType, double &retSpd);

	//�жϵ�ǰ�״��ٶ��ǲ����������ӵ��ٶȣ������Ա߳������ӵĸ��ţ�
	bool IsRadarSpdForThisCar(Car *pCar,  FILE *pFile, double videoSpd, double radarSpd);

	//�����ڼ���������ҳ��ƣ��������*****������Ŀ��û��ͬ�����£������Ժ������Ҫע�⣡
	void TestIsHaveCarInDetectRgn(const IplImage *imgSrc, unsigned int frameSeq);

private:

	bool _CalcCarSpeed(const Car *pCar, double &retSpd); 
	bool _CalcSensedObjSpeed(SensedObject *pSensedObj, double &retSpd);

	//ȷ�����Ƽ�������Ƿ���Car�������У�������״ﴫ�����ٶȸ����ٶ�map��
	bool _IsHaveCarInDetectionRgn();
	bool _IsHaveVlpCarInDetectionRgn();

	//����ת����ԭͼ->Checkͼ!
	void _OriCoordinate2CheckCoordinate(const CvRect rectSrc, CvRect &rectDst);
	void _Vlp2Original(CvRect &rectDst);

private:

	unsigned int m_frameSeq;
	int64 m_timeStamp;
	double m_dSpeed;
	std::map<unsigned int, double> m_mapRadarSpeed;  //speed map!
	CarManager *m_pCarManager;
	MvFindTargetByVirtualLoop * m_pFtgVlp;
	VirtualLoop *m_pVlp;
	
	std::vector<ChannelRegion> m_vecChannelRegion;
	std::vector<int> m_vecChannelIndex;  //�״︲�ǵĳ���������


	CvRect m_rectPlateDetection;  //���Ƽ������
	CvRect m_rectOverlap;  //���Ƽ��������״��Ӧ�غ�����
	int m_nDelay;
	Time_Mode m_nMode;

	FILE *m_pRadarDataFILE;
	FILE *m_pFILERadarSpdmapValue;
};
#endif