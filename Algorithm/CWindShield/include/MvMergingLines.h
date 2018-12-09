// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
/*
 *���๦�ܣ�ʵ�ֶ�ֱ�ߵĺϲ���
 */

#ifndef	MV_MERGING_LINES_H
#define MV_MERGING_LINES_H

#include <vector>
#include "MvLineSegment.h"

using std::vector;


#ifndef	PI
#define PI 3.1415926
#define HALF_PI PI/2
#endif


typedef struct _MergingLine{
	double x1;
	double y1;
	double x2;
	double y2;
	double tangent_x;
	double tangent_y;
	double orientation;//0-180
	double length;
	bool   bMerging;//�ϲ�����ֱ��
	bool   bMerged;//���ϲ�
	int    type; //0-ˮƽ�ߣ�1-��ֱ��
}MergingLine;


class MvMergeLines
{
public:
	MvMergeLines(void);

	~MvMergeLines(void);

	void mvMergingLineSegment(const vector<LSDLine> &lineVec,	 vector<LSDLine> &MergedLines, const int &thetaTh=5,
		const int &disTh_H=8, const int &disTh_V=7, const int &interval_H=10, const int &interval_V=10, const int &interval_O=10);

	
private:
	inline void mvTransformLineToLSD(const MergingLine &mergLine, LSDLine &lsdLine);

private:



};

#endif