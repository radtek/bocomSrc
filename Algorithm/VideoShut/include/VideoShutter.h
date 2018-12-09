// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary

#ifndef _VIDEO_SHUTTER_H_
#define _VIDEO_SHUTTER_H_
#include <vector>
using  namespace std;

#define MAX_OF_TWO max
#define MIN_OF_TWO min

#define  BUFFERSIZE   20

#include <algorithm>

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

#ifdef LINUX
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/vfs.h>
#include <sys/statvfs.h>
#else
#include <io.h>
#include <direct.h>
#endif


typedef struct CHANLL_FIL
{		
	int  nChanIndex;     //����������	 
	int64 nFramSeq;   //֡��	
}ChanlFil;


typedef struct CAR_FIL_AREA 
{		
	CvRect nFilCarPal;     //��shringkѹ��ͼ�ϵ�����	 
	int64 nFramSeq;   //���һ�μ�⵽��֡��
	int   nAvgMovDis;
	int   nDisAppearFram; //Ԥ�⳵����֡��Ҫ��ʧ
	bool  bCalDisappearTrd;
	CAR_FIL_AREA()
	{
		nFilCarPal =cvRect(0,0,1,1);
		nFramSeq = 0;
		nAvgMovDis = 0;
		nDisAppearFram = 20;
		bCalDisappearTrd = false;

	}
}car_filarea;



typedef struct ENERGY_m_SumPixel 
{		
	int nFlag;     //�Ƿ��Ѿ����������	 
	double nEnergy;   //����	
}energy_m_SumPixel;


//������ṹ��
typedef struct _SKIP_VIDEO_OUT_RESULT
{	    
	int nChannel;//���������

	_SKIP_VIDEO_OUT_RESULT()
	{	
		nChannel = -1;		
	}
}skip_video_out_result;


typedef struct _MVVIDEORGNSTRU {	
	vector<CvPoint2D32f> pPoints;	
	int nChannel;
	int nChanlIndex;
	_MVVIDEORGNSTRU()
	{	nChannel  = -1;	
	    nChanlIndex = -1;
		pPoints.clear();		
	}
}mvvideorgnstru;


typedef struct _MVPARK {	
	CvRect PaRec;
	int64  nFramSeq;
	bool  bShut;
	bool bPark;
	int  nBehdpakSum;
	int64 nParkFram;
	_MVPARK()
	{
		PaRec = cvRect(0,0,1,1);
		nFramSeq = 0;
		bShut = false;
		bPark = false;
		nBehdpakSum = 0;
		nParkFram =0;

	}
}mvPark;


//���ƽ���ṹ��
typedef struct _CHANL_DATA
{
	int nChanlIndex;//�������� -��0��ʼ
	int nChanlNum;//������-��Ӧʵ��·��ĳ���

}ChanlData;
//���ƽ���ṹ��
typedef struct _SKIP_CARNUM_RESULT : CvSetElem
{	
	CvRect  carnumpos[BUFFERSIZE];//��Զ�ԭʼ������Ĵ�С
	int     number;
	int64   ts[BUFFERSIZE];
	int64   FramSeq[BUFFERSIZE];
	bool    IsCausedByLig[BUFFERSIZE];
	int  nuPSimPlat ;
	bool bPark;
	ChanlData nChanl;

	CvRect FistcarRect;
	int nForCarAvg;
	int nFirstAvg; //0;
	bool IsNoFirSet;
	bool IsShut ;
	bool  bNearCar;
	bool  bLigAndCar;
	bool  bLitConer;
	
	
	_SKIP_CARNUM_RESULT()
	{		
		//carnumpos = cvRect( 0, 0, 0, 0 );
		FistcarRect =cvRect( 0, 0, 1, 1 );
		nForCarAvg = 0;
		nFirstAvg = 0;
		IsNoFirSet = true;
		IsShut = false;
		for (int i =0; i<BUFFERSIZE;i++)
		{
			carnumpos[i] = cvRect( 0, 0, 0, 0 );
			ts[i] = 0;
			FramSeq[i] = 0;
			IsCausedByLig[i] = false;
			bPark = false;
		}
		number = 0;
		nuPSimPlat = 0;
		nChanl.nChanlIndex = 0;
		nChanl.nChanlNum = 0;
		bNearCar = false;
		bLigAndCar = false;
		bLitConer = false;
		
		
	}
}skip_carnum_result;

typedef struct CAR_CURRENT_INF
{
	CvRect CarRec;
	int64  ts;
	int64  FramSeq;
	bool   IsCasdLig;
	bool    CasLigAddPlat;
	CAR_CURRENT_INF()
	{
		IsCasdLig = false;
		CasLigAddPlat = false;
	}

}car_current_inf;

typedef struct CIRCLE_ATTRIBUTION
{
	 int center_x;
	 int center_y;
	 int radius;
	 CvRect LigRec;
}circle_attribution;

typedef struct LIGWORLD_INF
{
	 double CirlWoldPosX;
	 double CirlWoldPosY;
	 int nLabNum;

}ligworld_inf;

typedef struct LIGMATCH_INF
{
	int nNum;
	int nMatchNum;

}ligmatch_inf;

typedef struct RECT_LIG
{
	CvRect  CaRect;
	bool    ISCasByLig;
	bool    CasLigAndPlat;
	RECT_LIG()
	{
		ISCasByLig = false;
		CasLigAndPlat = false;
	}
         
}rect_lig;

typedef struct LINE_INF
{
	CvPoint  StartPoi;
	CvPoint  EndPoi;
    int      nLeng;
	LINE_INF()
	{
		nLeng = 1;
		StartPoi = cvPoint(0,0);
		EndPoi  = cvPoint(0,0);

	}


}Line_inf;

typedef struct _ChANLVEHIC
{

	int64 nPassFram;
	_ChANLVEHIC()
	{
		
		nPassFram = 0;
		
	}

}ChanlVeh;
typedef struct _PEEKINF 
{		
	CvPoint Pos;     //�Ƿ��Ѿ����������	 
	int  nHig;   //����
	CvPoint MovePoint;
	_PEEKINF()
	{
		Pos = cvPoint(0,0);
		MovePoint = cvPoint(0,0);
		nHig = 0;
	}
}Peekinf;


typedef struct _MOVE_OBJ
{
	CvRect ObjRec;
	int64  nFramSeq;

	bool   bCauByCar;

	bool   bCauByLig;
	CvRect RecByLig;

	_MOVE_OBJ()
	{
		ObjRec = cvRect(0,0,1,1);
		nFramSeq = 0;
		bCauByCar = false;
		RecByLig = cvRect(0,0,1,1);
		bCauByLig =false;
	}

}MovObj;

typedef struct _CAR_HIT
{
	CvRect ShutRec;
	int nHitSerNum;
	_CAR_HIT()
	{
        ShutRec = cvRect(-10,-10,1,1);
		nHitSerNum = 0;
	}
}CarHit;

//�˶�ǰ��Ŀ��ṹ��
typedef struct _SKIP_MOVOBJ_RESULT : CvSetElem
{	
	CvRect  MovPos[BUFFERSIZE]; //���ѹ�������������ͼ������
	int     number;
	int64   FramSeq[BUFFERSIZE];
	CvRect    RecCausedByLig[BUFFERSIZE];
	int       nLigLapNum;
	ChanlData nChanl;
	bool IsShut;
	bool   bSerHig;
	bool   bSerYAdd;
	int   nTrackNum;
	int   nShutTracNum;
	bool  IsMeetSHut;
	uchar   nGrayVal;




	_SKIP_MOVOBJ_RESULT()
	{		

		for (int i =0; i<BUFFERSIZE;i++)
		{
			MovPos[i] = cvRect( 0, 0, 1, 1 );
			FramSeq[i] = 0;
			RecCausedByLig[i] = cvRect( 0, 0, 1, 1 );


		}
		number = 0;
		nChanl.nChanlIndex = 0;
		nChanl.nChanlNum = 0;
		nLigLapNum = -1;
		IsShut = false;
		bSerHig = false;
		bSerYAdd = false;
		nTrackNum = 0;
		nShutTracNum = 0;
		IsMeetSHut = false;
		nGrayVal = 255;

	}
}skip_movobj_result;




#endif
