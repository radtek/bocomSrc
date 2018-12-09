// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   15:08
	filename: 	e:\BocomProjects\find_target_lib\include\VehicleFlowHelper.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	VehicleFlowHelper
	file ext:	h
	author:		Durong
	
	purpose:	����Ŀ���⣬���ݱ궨��������ͳ�����ʱ��������ֵ��
*********************************************************************/


#ifndef VEHICLE_FLOW_HELPER_H
#define VEHICLE_FLOW_HELPER_H

#include "cxcore.h"
#include "Calibration.h"

using namespace PRJ_NAMESPACE_NAME;

class VehicleFlowHelper
{
public:
	VehicleFlowHelper();

	~VehicleFlowHelper();

	void Init(CvSize imgSize, CvRect vlpRoi, MyCalibration*pCalib);

	// ����С����������������ֵ
	float GetCarSealFlow(int nVlpPos) const;

	// ����С���������ֵ
	float GetCarMaxFlow() const;

	// ����С������С��ֵ
	float GetCarMinFlow() const;

	// ����ǻ���������Ӧ�þ��е���ֵ��
	float GetNonvSealFlow(int nVlpPos) const;


	// ���ճ�����ͼ����ռ�Ĵ�С��������������
	static float CalcFlowByPos(CvRect r, MyCalibration *pCalib);

	// ���������ĳ���ߣ��Լ����ĵ���ͼ���е�λ�ã����������ͼ���е�λ�á�
	static CvRect GetVehicleImagePos(CvPoint pt, MyCalibration* pCalib, int nVehType);


	// ����һ��С����ģ��
	static void GetCarModel(float modelCarBottom[12], float modelCarMid[12], float modelCarTop[12]);

	// ����һ���ǻ�������ģ��
	static void GetNonVModel(float modelBottom[12], float modelMid[12], float modelTop[12]);


private:

	// �洢����vlp�ϴ�����С��Ӧ�þ��е�����ֵ�����Ǹ߶ȣ�
	float *m_pCarFlow;
	
	// 
	float *m_pNonvFlow;


	int m_nVlpWidth;

};



#endif