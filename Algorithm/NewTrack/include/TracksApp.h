#ifndef __TRACKS_APP_H
#define __TRACKS_APP_H

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
typedef struct StructTracksInAreaApp
{
public:
	//��ȡ���ڸ����Ķ���������ڵĹ켣���
	static bool mvGetInPolygonTracks(
			vector<int> &vecInAreaTrIdx,  //�������ڵĹ켣���
			int nGiveTrNum,				  //��ǰ�ǿչ켣��Ŀ
			int *nAGiveTrIdx,			  //��ǰ�ǿչ켣���
			MyTrackElem **pATrPointer,	  //���й켣�ĵ�ַ 
			int nPolygonPtCnt,            //����εĶ�����
			CvPoint2D32f *pPolygonPts,    //����εĵĸ�����
			int nMinTrLenThresh			  //�켣����С��¼����Ҫ��
		);

	//��ȡ�ڸ����ĳ����������ڵĹ켣���
	static bool mvGetInRectangleTracks(
			vector<int> &vectInAreaTrIdx,	   //�������ڵĹ켣���
			CvPoint &ptTracksLt,				   //�������ڵĹ켣�γɵ����ϵ�
			CvPoint &ptTracksRb,				   //�������ڵĹ켣�γɵ����µ�
			const vector<int> &vectGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,		   //���й켣�ĵ�ַ 
			const CvPoint &ptLt,		       //����εĶ�����
			const CvPoint &ptRb,		       //����εĵĸ�����
			int nMinTrLenThreshold		       //�켣����С��¼����Ҫ��
		);

}AnTrsInAreaApp;


//�켣�����Ӧ��
typedef struct StructTracksAreaApp
{
public:
	//��ȡ�����Ĺ켣���γɵ����ϵ�����µ�(ͼ�����������)
	static bool mvGetLtRbPt4Tracks(
			CvPoint &ptTracksLtImg,		//�������ڵĹ켣�γɵ�ͼ���������ϵ�
			CvPoint &ptTracksRbImg,		//�������ڵĹ켣�γɵ�ͼ���������µ�
			CvPoint2D32f &ptTracksLtWor,  //�������ڵĹ켣�γɵ������������ϵ�
			CvPoint2D32f &ptTracksRbWor,  //�������ڵĹ켣�γɵ������������µ�
			const vector<int> &vectGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,	//���й켣�ĵ�ַ 
			IplImage *pXWorCImg,		//X��������ֵ��ͼ��
			IplImage *pYWorCImg			//Y��������ֵ��ͼ��
		);

	//��ʾ�����켣
	static void mvShowGiveTracks(
			const vector<int> &vectGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,		   //���й켣�ĵ�ַ 
			IplImage *pShowRgbImg,             //��ʾ��rgbͼ��
			CvRect rectShowRoi,         //��ʾ�ڵ�ROI����
			CvScalar ColorVal,          //��ɫ       
			int nRadius,                //�뾶
			int nThickness              //���
		);

}AnTrsAreaApp;

//�켣���ٶ�Ӧ��
typedef struct StructTracksVelocityApp
{
public:
	//����������Ĺ켣��x,y����������ٶ�
	static bool mvCalcTracksWorVeloXY(	
			vector<CvPoint2D32f> &vectWorVeloXYVal,  //���������XY�����ٶ�ֵ(���)
			const vector<int> &vecGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,		  //���й켣�ĵ�ַ 
			int nMaxCalcTrLen,				  //����Ĺ켣����
			IplImage *pXWorCImg,			  //X��������ֵ��ͼ��
			IplImage *pYWorCImg				  //Y��������ֵ��ͼ��
		);

	//����������Ĺ켣��x,y��������İ�ֱ��ͼ�ֲ��ľ����ٶ�
	static bool mvCalcTracksAbsWorVeloXY4Distribute(	
			vector<CvPoint2D32f> &vectWorVeloXYVal,  //���������XY�����ٶ�ֵ(���)
			const vector<double> &vectGiveDistVal,   //�����������ķֲ�����ֵ
			const vector<int> &vecGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,		  //���й켣�ĵ�ַ 
			int nMaxCalcTrLen,				  //����Ĺ켣����
			IplImage *pXWorCImg,			  //X��������ֵ��ͼ��
			IplImage *pYWorCImg				  //Y��������ֵ��ͼ��
		);

	//��ȡ�õ��ٶȽ����Ĺ켣(�ų�������켣)
	static bool mvGetSlowTracks(	
			vector<int> &vectSlowTrIdx,        //��ȡ�����ٶȽ����Ĺ켣���
			const vector<int> &vectGiveTrIdx,  //�����Ĺ켣���
			MyTrackElem **pATrPointer,		   //���й켣�ĵ�ַ 
			IplImage *pXWorCImg,               //ͼ�������Ӧ��X��������
			IplImage *pYWorCImg,               //ͼ�������Ӧ��Y�������� 
			float fVeloTh4Slow,                //��Ϊ�������ٶ���ֵ
			IplImage *m_pInteMvStCntImg        //�����˶���ֹͣ�ĵ�Ļ���ͼ
		);

}AnTrsVelocityApp;


//end-----------

#endif