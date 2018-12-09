// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   15:00
	filename: 	e:\BocomProjects\find_target_lib\include\MvTrackPair.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvTrackPair
	file ext:	h
	author:		Durong
	
	purpose:	��ʾһ�Թ켣�Ľṹ�塣������û��ʹ��
*********************************************************************/


#ifndef MV_TRACK_PAIR_H
#define MV_TRACK_PAIR_H

typedef struct _MvTrackPair
{
	int nIndex1;
	int nIndex2;
	float fDis;

	int nDSIndex1;
	int nDSIndex2;

public:
	_MvTrackPair(int i1, int i2, float fd, int nDSIndex1, int nDSIndex2)
	{
		nIndex1 = i1;
		nIndex2 = i2;
		fDis    = fd;
		this->nDSIndex1 = nDSIndex1;
		this->nDSIndex2 = nDSIndex2;
	}

	static bool IsPaDisLessThanPb(const _MvTrackPair& pa, const _MvTrackPair& pb);
}MvTrackPair;

#endif

