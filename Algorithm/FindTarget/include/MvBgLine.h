// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   11:46
	filename: 	e:\BocomProjects\find_target_lib\include\MvBgLine.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvBgLine
	file ext:	h
	author:		Durong
	
	purpose:	ֱ�߱���ģ�ͣ������ڽǵ㱳��ģ�͡�
*********************************************************************/



#ifndef MV_BG_LINE_H
#define MV_BG_LINE_H


#include "MvLineSegment.h"

class MvBgLine
{

public:
	// ��ʼ������֮ͼ������߶ȡ�
	// nIntervalΪͳ�ƵĴ�����ͳ������ÿ�ﵽnInterval�Σ��������±����������¿�ʼͳ�ơ�
	void Init( int width, int height, int nInterval );

	void Destroy();

	// ���ͳ������
	void Update(BLine *pLines, int nCount);

	// ������ֱ��pAllLines����Ϊ����ֱ����Ǳ���ֱ�ߡ�
	void SepBgLines(BLine *pAllLines, int nAllCount, BLine *pNonBgLine, int &nNonBgLineCount, BLine *pBgLine, int &nBgLineCount);

	// �汳��ֱ��ͼ�����ڹ۲�ֱ�߱���Ч����Ρ�
	void SaveBgImage() const;

private:

	// ��Ϊһ�������Ǳ����ĸ���Ҫ��
	// ֱ�ߵ��������ص��б������ص�ռ�����߶ε����ص�ı�������p2������Ϊ�߶��Ǳ�����
	bool IsBgLine(BLine *pLine, float p1, float p2);

private:
	int m_nWidth;
	int m_nHeight;
	int m_nCount;
	int m_nInterval;

	int *m_pMapStat;
	int *m_pMapBg;


	int *m_pTemp;
	int m_nTmpSize;

};

#endif