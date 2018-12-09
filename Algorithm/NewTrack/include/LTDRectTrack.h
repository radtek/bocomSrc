#ifndef __LTD_RECT_TRACK_H
#define __LTD_RECT_TRACK_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "libHeader.h"

#include "comHeader.h"  //�����

using namespace std;
using namespace MV_IMGPRO_UTILITY;
using namespace MV_AN_ANLGORITHM;


enum ENUM_TLD_TRACK
{
	MV_TLD_COUNT=1, //!< the maximum number of iterations or elements to compute
	MV_TLD_MAX_ITER = MV_TLD_COUNT, //!< ditto
	MV_TLD_EPS = 2  //!< the desired accuracy or change in parameters
	                //       at which the iterative algorithm stops
};


//�������TLD���ٵĽ��
#ifndef MAX_TLD_TRACK_LEN
	#define MAX_TLD_TRACK_LEN 100
#endif
typedef struct StruOneTLDTrackResult
{ 
	int  nTldRectId;  //��Tld�����id
	int  nCurLenIdx;  //��ǰ���ȵ�ָʾ

	CvRect rectA[MAX_TLD_TRACK_LEN];			//���ٵõ�������
	CvPoint2D32f fptAOffset[MAX_TLD_TRACK_LEN]; //����֡�ĵ㼯ƫ����ֵ

	//���ӵ�������Ϣ
	float  fAHoGPeoScore[MAX_TLD_TRACK_LEN];  //HoG���˵ĵ÷�
	float  fAFkPtsRate[MAX_TLD_TRACK_LEN];    //����ǰ����ı���
	float  fADiffPtsRate[MAX_TLD_TRACK_LEN];  //�����ֵ�ı���

public:
	StruOneTLDTrackResult( );

	//�ƶ�һ���ڵ㣬�������
	void mvMoveOneNode( );

}OneTLDTrackResult;



//����LTD����rect������ٵĽṹ��
typedef struct StruTLDRectTrack
{
public:	
	StruTLDRectTrack( );

	//��ʼ������
	void initVar( );
	
	//��ʼ��rect����ƥ�������	
	void mvInitTLDRectTrack( int nW, int nH );	
	
	//�ͷ�rect����ƥ�������
	void mvUninitTLDRectTrack( );	

	//�Ը���rect�������ƥ�����
	bool mvTLDTrack(
			IplImage *img1,  //ͼ��1
			IplImage *img2,  //ͼ��2
			IplImage *p2VFkImg4Give, //ͼ1����Ӧ��ǰ��
			IplImage *p2VFkImg4Pred, //ͼ2����Ӧ��ǰ��
			IplImage *pEigImg4Give,  //ͼ1����Ӧ������
			const CvRect &rectGive,  //ͼ1��Ҫ���ٵ�rect����
			vector<CvPoint2D32f> &points1,  //ͼ1��ƥ��ĵ�
			vector<CvPoint2D32f> &points2,  //ͼ2ƥ���ϵĵ�
			CvRect &rectPredict,     //ͼ��2�Ķ�ͼ��1��rect�ĸ��ٽ��
			CvPoint2D32f &fptOffset  //�㼯ƥ������ֵλ��
		);  

	//����ǰ��TLD���ٽ��
	static void mvProcessTLDRectResultEveryFrame( 
			vector<StruOneTLDTrackResult> &vectTLDReulst,
			vector<CvRect> &vectLastFindRects,
			vector<int> &vectLastFindRectIdxs,
			vector<CvPoint2D32f> &vFptOffset, //�����ƥ���ƫ��ֵ��ֵ
			int  nRecNoPeoCntDelTh = -1000,  //�����Ϊ���˵�ɾ����ֵ
			bool bDelLongTimeOverLap = true //�Ƿ�ɾ����ʱ���ص���Ŀ��
		);

	//ɾ���ص���Ŀ��
	static void mvDeleteOverlap(
			vector<StruOneTLDTrackResult> &vectTLDReulst //IN+OUT
		);

	//��ȡҪɾ���ص���Ŀ�����
	static void mvGetWantDeleteOverlapIdx( int &nDelIdx,  //OUT:
			int i, const OneTLDTrackResult &TLDR_i, //IN:
			int j, const OneTLDTrackResult &TLDR_j  //IN:
		);

public:
	bool m_bTValid;   //���ٵĽ���Ƿ���Ч
	bool m_bTracked;  //TLD�����Ƿ������

private:
	//��ȡ�õ�����rect�ڵ����ص�
	void mvGetPoints4GiveRect(
			vector<CvPoint2D32f> &points, //OUT:�㼯��
			const CvSize &szImg,		  //IN:ͼ���С
			const CvRect &rectGive,		  //IN:�����ĵ���ȡ����
			IplImage *p2VFkImg4Give=NULL, //IN:ǰ��2ֵͼ��
			IplImage *pEigImg4Give=NULL   //IN:�ݶ�����ͼ��
		);


	//����֡ͼ����и���
	bool mvTrackFrame2Frame(
			IplImage *img1, IplImage *img2,
			vector<CvPoint2D32f> &points1, 
			vector<CvPoint2D32f> &points2, 
			IplImage *p2VFkImg2 = NULL  //ǰ��2ֵͼ��
		);

	//������֡ƥ���������
	void mvCalcNormCrossCorrelation(
			IplImage *img1, IplImage *img2, 
			int nPtcnt,	char *chMatchStatus, 
			CvPoint2D32f *pts1, CvPoint2D32f *pts2,
			float *fSimilarity 
		);

	//�Ե�ƥ��Ľ�����й���
	bool mvFilterMatchPts( int &nPariCnt,
			CvPoint2D32f *pts1, CvPoint2D32f *pts2,
			char *FBStatus, float *fFBError, 
			float *fSimilarity 
		);

	//���˱�����
	void mvFilterBgPts(	
			vector<CvPoint2D32f> &pts1,
			vector<CvPoint2D32f> &pts2,
			IplImage *p2VFkImg2 = NULL  //ǰ��2ֵͼ��
		);

	//Ԥ��rect
	void mvPredictRect(
			float &dx,	  //OUT: �㼯��xλ����ֵ
			float &dy,	  //OUT: �㼯��yλ����ֵ
			CvRect &bb2,  //OUT: Ԥ����Ŀ���
			const vector<CvPoint2D32f>& points1,
			const vector<CvPoint2D32f>& points2,
			const CvRect& bb1
		);

	//��ȡ�������ֵ
	float mvMedian(vector<float> v);

	//��ȡ����������ǰ�ٷֱȵ�ֵ
	float mvGetSortValue(vector<float> v, float f);

	//���ظ�����ķ���
	float mvPointNorm(CvPoint2D32f v);

private:
	CvTermCriteria m_term_criteria;

	CvSize m_window_size;
	int   m_level;
	float m_lambda;

	IplImage *m_opticalFlowPyr;			
	IplImage *m_opticalFlowPyrLast;	

}TLDRectTracker;


#endif