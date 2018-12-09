#ifndef __CAM_SHIFT_DEMO_H
#define __CAM_SHIFT_DEMO_H

#include "libHeader.h"

#define MAX_HIST_CNT 100


//��ѭ��ʹ�õĴ洢����
typedef struct StruCycleSaveArray 
{
public:
	StruCycleSaveArray( ){ mvInitVar( ); };

	void mvInitVar( );

	//��ȡ����id�ڴ洢�е����
	int mvFindSaveIdx( 
			bool &bFitstApp,      //�Ƿ�Ϊ��һ�γ���
			int  nRectId,		   //������ID
			double dTsNow,		   //��ǰ��ʱ���-s
			double dClearTime=60.0 //�������ʱ��-s
		);

private:
	int     m_nARectID[MAX_HIST_CNT]; 
	double  m_dAAppTs[MAX_HIST_CNT]; 

}MvCycleSaveArray;


class MvClassCamShift
{
public:
	MvClassCamShift( ) { mvInitVar( ); };

	~MvClassCamShift( ){ mvUninitCamShift( ); };

	//CamShift�������ӿ�
	void mvCamShift( 
			vector<CvRect> &trackResult, //OUT:���ٵõ��Ĵ���
			vector<CvRect> &vRectS,		 //IN:ѡ���Ҫ���ٵ�����
			vector<int> &vRectId,		 //IN:ѡ���Ҫ���ٵ�����
			vector<bool> &vJustCalcHist, //IN:ֻ����Ҫ���������ֱ��ͼ
			IplImage *image,         //IN:����ͼ��
			double   dTsNow,		 //IN:��ǰ��ʱ���-s	
			IplImage *pFkMask=NULL   //IN:ǰ��maskͼ������
		);

	//�Ҷȵ�CamShift�������ӿ�
	void mvGrayCamShift( 
			vector<CvRect> &vTrackRes,   //OUT:���ٵõ��Ĵ���
			vector<CvRect> &vRectS,		 //IN:ѡ���Ҫ���ٵ�����
			vector<int> &vRectId,		 //IN:ѡ���Ҫ���ٵ�����
			vector<bool> &vJustCalcHist, //IN:ֻ����Ҫ���������ֱ��ͼ
			IplImage *image,		 //IN:����ͼ��
			double   dTsNow,		 //IN:��ǰ��ʱ���-s
			IplImage *pFkMask=NULL   //IN:ǰ��maskͼ������	
		);

	//�ͷ�
	void mvUninitCamShift( );

private:
	//��ʼ������
	void mvInitVar( );

   //�Ը����������CamShift����
    bool mvRectCamShift( 
		   CvRect &trackResult,   //OUT:���ٵõ��Ĵ���
		   CvRect &selection,     //IN:ѡ���Ҫ���ٵ�����
		   int    nRectId,        //IN:�����ID
		   double dTsNow,         //IN:��ǰ��ʱ���
		   bool  bJustCalcHist    //IN:�Ƿ�ֻ���㵱ǰ���hist
	   );

private:
	bool   m_bInit;     //�Ƿ�����˳�ʼ��
	bool   m_bUseMask;  //�Ƿ����mask������
	CvRect m_rectTrack;
	
	MvCycleSaveArray  m_IdSaveArray;  //id�洢��

private:
	IplImage *m_hsv, *m_hue;
	IplImage *m_pMask, *m_backproject;

	int      m_nARectID[MAX_HIST_CNT]; 
	CvHistogram *m_histA[MAX_HIST_CNT];
	CvHistogram *m_hist;

	CvBox2D m_track_box;
	CvConnectedComp m_track_comp;
};


#endif