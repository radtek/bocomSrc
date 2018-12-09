// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#include "cxcore.h"

// ����ͳ�������ж�ͼ������ǲ��Ƿǻ�������ǰ�ƣ��������ұ��ǲ��Ƿǻ�������β�ƣ���
class RoadTypeDetector
{
public:
	// ǰ��nDirection=0, β��nDirection=1
	RoadTypeDetector(int nDirection, int nImageWidth, int nImageHeight);

	// 0���ǣ� 1�ǣ�-1δ֪
	int IsRightNonMotorizedVehicleRoad();

	// 0���ǣ� 1�ǣ�-1δ֪
	int IsLeftNonMotorizedVehicleRoad();


	void Update(CvRect rgn);



private:

	int m_nDirection;
	int m_nLeftCount;
	int m_nRightCount;

	int m_nImageWidth;
	int m_nImageHeight;
};