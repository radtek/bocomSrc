// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#if !defined(AFX_POLYGON_H__07674F13_FDD1_4483_A554_504BE8732732__INCLUDED_)
#define AFX_POLYGON_H__07674F13_FDD1_4483_A554_504BE8732732__INCLUDED_




#include <vector>
#include <cxcore.h>
#include <list>

class MvPolygon  
{
public:

	// ����εĶ���
	std::vector<CvPoint> points;
	
	// ���캯��
	MvPolygon() {};
	MvPolygon(CvPoint pts[], int ptCount);
	MvPolygon(const std::vector<CvPoint> &pts);
	MvPolygon(const std::list<CvPoint> &pts);

	// �жϵ��ڲ��ڶ�������档
	int IsPointInPoly(const CvPoint &pt) const;
	
	//��ȡ������Ƕ�
	float  GetMainAngle();
	CvRect GetBoudingRect();

	void   DrawPoly(IplImage *img, CvScalar color)const;

	// ��ȡ����εĶ��㡣��һ�������һ������ͬһ�㡣�ⲿ�ͷ�
	CvPoint *GetPointPointer(int &nCount);

};

#endif
