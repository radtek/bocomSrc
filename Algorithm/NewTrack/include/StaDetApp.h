#ifndef __STA_DET_H
#define __STA_DET_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "libHeader.h"

#include "comHeader.h"  //�����

using namespace std;
using namespace MV_IMGPRO_UTILITY;
using namespace MV_AN_ANLGORITHM;
using namespace MV_SMALL_FUNCTION;


//��ȡ�������ڵĹ켣��Ӧ��
typedef struct StructQueueLenStaApp
{
public:
	//�Խ����Ŷӳ��ȼ����������й���
	static void mvGetFiltrateQueueLenghtGrids(	
			vector<int> &vectOutQLGridIdx,
			AnImgGridsStru *pImgGrid, 
			vector<int> *pVectGiveGridIdx,
			double dTsNow,
			bool bFiltrateNoExistMove,
			double dPreTh,
			bool bFiltrateIsolate, 
			vector<int> *pVecInAreaGridIdx,
			IplImage *pShowRgbImg
		);

	//��ȡ���ڸ����Ķ���������ڵĹ켣���
	static void mvGetGridsSegmentResult(	
			vector< vector<int> > &vectGridsIdxGroups,  //�����Ľ��(���)
			vector<CvRect> &vectRectImg,  //������ͼ��rect���(���)
			vector<CvRect> &vectRectWor,  //����������rect���(���)
			AnImgGridsStru *pImgGrid,     //����������
			int nChanDirMod,              //��������ģʽ
			const vector<int> &vectGiveGridIdx,  //�������������
			float fMinGroupDist2GridSz,   //���ľ����������С����С����
			IplImage *pXWorCImg,     //X��������ֵ��ͼ��
			IplImage *pYWorCImg      //Y��������ֵ��ͼ��
		);

}AnQueueLenStaApp;



//end-----------

#endif