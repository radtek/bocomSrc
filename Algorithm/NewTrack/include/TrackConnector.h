//�ж��Ƿ�ΪͬһĿ��ļ����
#ifndef __TRACK_CONNECTOR_H
#define __TRACK_CONNECTOR_H

#include "libHeader.h"

#include "sift_descr.h"
#include "MvSiftDescr.h"
#include "MvKeyPtExtract.h"

#include "BaseStruct.h"

#include "comHeader.h"  //�����

#ifndef MAX_M2S_PT_CNT
	#define MAX_M2S_PT_CNT 2000  //�����ɶ������ĵ���
#endif

enum EnumMove2Stop
{ 
	SURE_MOVE2STOP_MODEL = 0,
	RECENT_IS_STOP_MODEL,
};

////�ɶ������Ĺ켣�ǵ�
//typedef struct StructPointMove2Stop
//{
//	double  dTsNow;
//
//	int     nPtCnt;
//	CvPoint ptAStop[100];
//
//}MvPtMove2Stop;


//�ɶ������Ĺ켣�ǵ�
typedef struct StructPointMove2Stop
{
public:
	StructPointMove2Stop( );
	void mvInitVar( );

public:
	bool   bVaild;   //�Ƿ���Ч 

	double dTsStartStop;   //��ʼ��ֹͣʱ���
	double dTsUpdateStop;  //���µ�ֹͣʱ���

	int      nSaveCnt;      //�ýǵ㱣��Ĵ���
	siftFeat pSiftFeat[3];  //�ýǵ��SIFT����

}MvPtMove2Stop;


typedef struct StruMove2StopTrackConnector
{
public:
	StruMove2StopTrackConnector( );
	~StruMove2StopTrackConnector( );

	void mvInitMove2StopTrackConnector( CvSize szImg );
	void mvUninitMove2StopTrackConnector( );

	//������Щ��ʱ��û�и��µģ���ȡ�õ�ĿǰΪ��&�ɶ������ĵ�
	void mvClearAndGetEmpty( double dTsNow, double dLongTimeTh );

	//��ӻ����
	bool mvAddOrUpdate( double dTsNow, EnumMove2Stop nModel,        
				  CvPoint2D32f &fpt, uchar cSift[SIFT_DIMS] );

	//��ʾ�ɶ������ĵ�
	void mvShowMove2StopPts( );


	//��ȡ�ڸ����㸽����������ǵ�����
	bool mvGetIndexOfSavePts( 
			CvPoint2D32f &fpt,   //��ǰ�Ľǵ�λ��
			int &nFindCnt,		 //Ѱ�ҵ��ĵ����
			int nAFindIdx[]		 //Ѱ�ҵ��ĵ����
		  );

	 //��ȡ�õ�ĿǰΪ�յ��ɶ������ĵ�
	 void mvGetMove2StopPt(
			int &nPtCnt,     //�ؼ������Ŀ
			int nAPtIdx[],   //�ؼ�������
			CvPoint ptALoc[] //�ؼ��������
		  );

private:
	void mvInitVar( );

	//��ȡ�õ�ĿǰΪ�յ��ɶ������ĵ�
	void mvGetEmptyMove2StopPt(	);

	//����һ����ļ�¼
	void mvClearOnePointRecord( MvPtMove2Stop &ptMove2Stop );


	//����µĽڵ�
	bool mvAddM2SPtToSaveResult( 
			double dTsNow,         //��ǰ��ʱ���
			CvPoint &ptNow,        //��ǰ�Ľǵ�λ��
			uchar cSift[SIFT_DIMS] //��ǰ�ǵ��SIFT����
		);


	//��ȡ�õ���õ�ƥ����
	bool mvGetBestSiftMatchResult( 
			int  &nBestPtIdx,        //ƥ��õ�����õ����
			int  &nBestSaveIdx,      //ƥ��õ�����õ�ĵڼ��ڵ��
			uchar cSift[SIFT_DIMS],  //��ǰ�ǵ��SIFT����
			int  nFindCnt,           //Ѱ�ҵ��ĵ���
			int  nAFindIdx[]         //Ѱ�ҵ��ĵ����
		);

	//����ƥ���������и���
	bool mvUpdateWithMatchResult( 
			double  dTsNow,          //��ǰ��ʱ���
			CvPoint ptNow,           //��ǰ�ǵ�λ��
			int  &nBestPtIdx,        //ƥ��õ�����õ����
			int  &nBestSaveIdx,      //ƥ��õ�����õ�ĵڼ��ڵ��
			uchar cSift[SIFT_DIMS]   //��ǰ�ǵ��SIFT����
		);

private:
	bool    m_bInit;    //�Ƿ���й���ʼ��

	MvPtMove2Stop *m_pPtMove2Stop;      //���˶�����ֹ�ĵ�
	IplImage      *m_pMove2StopPtIdImg;	//�ɶ������ĵ��Idͼ��	

	int		m_nEmptyCnt;				   //�յ����
	int		m_nAEmptyIdx[MAX_M2S_PT_CNT];  //�յ����
	int     m_nFillIdx4EmptyArray;     //��ǰ���ĵ����(����ڿ�����)

}MvM2STrConnector;

////////////////////////////////////////////
#endif