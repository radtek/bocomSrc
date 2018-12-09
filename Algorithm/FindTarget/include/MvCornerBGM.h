// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   11:53
	filename: 	e:\BocomProjects\find_target_lib\include\MvCornerBGM.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvCornerBGM
	file ext:	h
	author:		Durong
	
	purpose:	ԭ����ʵ��һ����sift�����Ľǵ㱳��ģ�͡�û����ȫʵ�֡�
	Ŀǰ�����κ����á�
*********************************************************************/


#ifndef MV_CORNER_BGM_H
#define MV_CORNER_BGM_H


#include "MvCorner.h"


// �����ǵ�
typedef struct _MvBGCorner
{
	MvCorner   corner;
	int          nTimes;
	unsigned int uLastAppearFrameSeq;
	struct _MvBGCorner   *pNext;

	_MvBGCorner()
	{
		nTimes = 0;
		uLastAppearFrameSeq = 0;
		pNext = NULL;
	}
} MvBGCorner;




// �ǵ㱳��ģ��
class MvCornerBGM
{
private:

	// �����ǵ�
	MvBGCorner *pBGCornerHead;
	

public:
	MvCornerBGM();
	~MvCornerBGM();

	void Input(MvCorner *pCorners, int nCount);
	void GetForeCorners(MvCorner *pCorners, int &nCount);
	void Update();


}; 


#endif