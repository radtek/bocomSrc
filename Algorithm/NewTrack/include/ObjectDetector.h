//Ŀ����
#ifndef _MV_OBJECT_DETECTOR_H_
#define _MV_OBJECT_DETECTOR_H_

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <map>

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"

#include "MvMathUtility.h"

#include "MatchTrack.h"
#include "ConstructGroup.h"

#include "ConfigStruct.h"

#include "Detector.h"

#include "comHeader.h"  //�����

using namespace std;
using namespace MV_MATH_UTILITY;

typedef struct  _CHANNEL_OBJDETECT_PARAM
{
	int     nChannelID;         //����ID
	int     nChannelMod;		//����ģ��:0-��������,1-�ǻ�����,2-��ϳ���
	int     m_nAngle;           //�Ƕ�

	bool    bShow;              //�Ƿ�Ϊͣ����ʾ��1-ͣ����ʾ�¼�,0-��ʵ�¼�

	//----------------------�¼��������------------------------//
	//���Ŀ��	
	bool   bObjectAppear;        //�Ƿ���Ŀ�����
	int64  nShowTime;            //ͬһĿ����ֱ�������ʾʱ��(ms)
	int64  nSameObjAppearIgn;    //ͬһĿ����ֱ����ĺ���ʱ��(ms)	
	int64  nSameEventAlertIgn;   //����ͬ���¼�(Ŀ�����)�����ĺ���ʱ��(ms)	

	int64 ts_appear_alert;        //�ó����ϴγ��ֱ�����ʱ��

	int  nObjeceDetectMod;    

	_CHANNEL_OBJDETECT_PARAM( )
	{
		nChannelID = 0;
		nChannelMod = 0;		   	
		m_nAngle = 0;
		bShow = false;            //��ʵ�¼�

		//----------------------�¼��������------------------------//
		bObjectAppear = false;   
		nShowTime = (int64) 30e3;             //ͬһĿ�걨����ʾ15s
		nSameObjAppearIgn = (int64) 300e3;    //ͬһĿ��5������ֻ��һ��
		nSameEventAlertIgn = 0;	        //�����¼�һ���־ͱ���������

		ts_appear_alert = -1000000;       //�ó����ϴγ��ֱ�����ʱ��

		nObjeceDetectMod = DETECT_ALL_OBJECT;   
	}
}MVChannelObjDetParam;


class CObjectDetector /*: public CDetector*/
{

public:
	CObjectDetector(void);
	~CObjectDetector(void);

	//�����
	bool mvDetectShips( DetectResultList& outList, 
			int nPtCnt, CvPoint2D32f *ptAObjDetPloy, IplImage *pShowImg=NULL );

private:
	//��ʾ�����
	void mvShowDetectResult( int nPtCnt, CvPoint2D32f *ptAObjDetPloy, 
				DetectResultList objDectOutList, IplImage *pShowImg );

	void mvShowEllipseFiting( int nRandPt, CvPoint2D32f *p_ptRand,
							  CvSize imgSz=cvSize(200,150) );

private:
	MVChannelObjDetParam m_chanelObjDetParam;

};


#endif