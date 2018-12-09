/* ��Ȩ���� 2009 �Ϻ�����������Ϣ�������޹�˾
* Copyright (c) 2009��Shanghai Bocom Intelligent Information Technologies Ltd
* �������ܹ�˾����
* Bocom Intelligent Confidential Proprietary
* �ļ����ƣ�StabilizeImage.h
* ժҪ: ���ھֲ�����SIFTƥ�������
* �汾: V1.1
* ����: ����
* �������: 2010��01��19��
*/

#ifndef __MYVIDEOSTABILIZER_H
#define __MYVIDEOSTABILIZER_H

#ifdef LINUX
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define _chdir(a) chdir(a)
#define _mkdir(a) mkdir(a, 0777)
#define  MAXLINENUMFORCALSHADOW 500
#else
#include <direct.h>
#define  MAXLINENUMFORCALSHADOW 200
#endif


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
#include <time.h>
//#include <sys/utime.h>

#ifndef __CV__H__
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#endif

#ifndef __SIFT__H__
#include "sift_descr.h"
#endif


#define MAX_CORNERS 400

// ����ģ�͵�����
#define TRANSLATION_MODEL      0
#define AFFINE_MODEL           1
#define SIMPLE_AFFINE_MODEL    2

// for sift matching
#ifndef SIFT_DIMS
#define SIFT_DIMS     128 
#endif
#ifndef SIFT_WIN_SIZE
#define SIFT_WIN_SIZE    4
#endif
#ifndef SIFT_BINS
#define SIFT_BINS     8
#endif


#define MAX_REGIONS 10 //���ͼ�������

// for debug
//#define DEBUG1
//#define DEBUG_CORNERMAP
// #define DEBUG_CORNERUPDATE
// #define DEBUG_DISPLAY
// #define DEBUG_SAVE_RESULTS 
// #define TIME
// #define DEBUG_PSNR

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

typedef struct MyAffParams
{
	float theta; // ��ת�Ƕ�
	float scale; // ���ų߶�
	float dx;    // x����ƽ����
    float dy;    // y����ƽ����
}MyAffParams;

typedef struct CMyorners 
{
	CvPoint2D32f pos; // λ������
	uchar *siftVal; // SIFT������
	int isMatched; // SIFTƥ���Ƿ�ɹ�
	int bkgrdTimes; // ��Ϊ�����ǵ�ƥ��ɹ���������ͳ�ơ����±�����ʱʹ��
    
	CMyorners()
	{
		pos        = cvPoint2D32f(0, 0);
		siftVal    = NULL;
		isMatched  = 0;
		bkgrdTimes = 0;
	}

}CMyorners;

class CMyVideoStabilizer4Client
{
	
public:

	CMyVideoStabilizer4Client();
	~CMyVideoStabilizer4Client(); // virtual?

	//��ʼ����������ƥ���������ɣ�����n֡ͼ���ʼ������ͳ�ƣ����ض������Ӿ��Ρ����ڶ�����ڵĽǵ�λ�á�SIFTֵ���ǵ����
	bool mvInitial( IplImage *pFrame, int nAreaNum, const int *nPolySize, const CvPoint2D32f **fPolyPts, 
								 int nRadius, uchar AffModel, int nFrameNum, float fCornerQuality, int nCornerMinDist );//, bool bInitBkCal )

	// �������£��³��ֵĽǵ��Ƿ������ο��ǵ���
	bool mvUpdateBkCorners( void );

	// �ο�������SIFT����
	bool mvUpdateSIFT( void );

	// SIFT����ƥ�����sift��������
	int mvSIFTMatch( void );
//	int mvNewSIFTMatch( void );

	// ��ȡͼ��ǵ㼰SIFTֵ
    int mvGetRefCornersSIFT( IplImage *pFrame, float fCornerQuality, int nCornerMinDist,
										const int *nPolySize, const CvPoint2D32f **fPolyPts );

	// ��ȡͼ��ǵ㼰SIFTֵ
    int mvGetCurCornersSIFT( IplImage *pFrame, float fCornerQuality, int nCornerMinDist,
		                                const int *nPolySize, const CvPoint2D32f **fPolyPts );

	// ��ÿ�ƥ���������,�������ⲿ��������ʾ���
	CvRect mvGetMaskROI(void); 

	// Ransac����ƥ��
	MyAffParams mvRANSAC(
				   int nSelectNum, // ÿ�����ѡ������
				   int nNum, // ransac��������
				   float fThrd, // ��ֵ
				   int nMinMatchNum, // ��Сƥ����
				   uchar uAffModel   // ����ģ������
				   );
    // �������͵�ƫ��������ԭͼ�񣬻��ƽ�ƺ��ͼ��
	void mvTranslation( const IplImage *src, IplImage *dst, int dx, int dy );
	// �����˶�������ͼ��,�������ⲿ��������ʾ���
	void mvStabilized( const IplImage *pFrame, IplImage *pStbFrame );

    
    //�жϵ��Ƿ��ڶ������, �ڶ���������Ϊconst��ԭ������ͬ
	bool mvIsPointInPolygon(int nPolySize, const CvPoint2D32f *pts, CvPoint2D32f pt);
    
	// ��ȡ������ķ������
	MyAffParams mvGetAffParams( void );

	// ��ȡ������Ĳο��ǵ�λ��
	CMyorners* mvGetRefCorners( void );

	// ��ȡ������ĵ�ǰ�ǵ�λ��
	CMyorners* mvGetCurCorners( void );

	// ����������ͼ����
	void mvSaveTestImage( char cTopDir[50], char cType[10], char *infoStr, long &nImgCount );

	// ����ROI���ν�ͼ
	void mvCutImage( const IplImage* src, IplImage* dst, CvRect rect );

	// ����2��ͼ��ķ�ֵ�����PSNR
	float mvPSNR( const IplImage* pTestImg, const IplImage* pSrcImg );
	float mvMSE( const IplImage* pTestImg, const IplImage* pSrcImg );

	// Function radnLocs() generates unique numbers.
    void mvRandLocs( int nSelectNum, int nRange, int *pLocs );

	// ����Ӧ�ĵ���з���任
    void mvAffTform( const CvPoint2D32f* src, int numSrc, CvPoint2D32f* dst, MyAffParams affParams, uchar mode );

	// Function DLT calculates the transformation matrix that best describes
	// the geometric transformation between the points.
	// Note: numPts seems the same as selecNum, maybe one of those params can be removed 
	MyAffParams mvXform( const CvPoint2D32f* Pts1, // current frame
		               const CvPoint2D32f* Pts2, // reference frame 
	   	               int           numPts,
			           uchar         mode );

//  �ӿں���
//  IplImage *imgSrc  	    	-- Դͼ��
//  int nAreaNum   	         	-- ͼ����ѡ��������������ĸ���
//  int *nPolySize              -- �������������Ķ�����Ŀ
//  CvPoint2D32f **fPolyPts     -- �������������Ķ�������
//  uchar uAffModel             -- ����ģ�͵����ͣ�
//	                                   0 -- ��ƽ��ģ��
//	                                   1 -- �򻯷���ģ��
//	                                   2 -- ��׼����ģ��
//  MyAffParams &params           -- �������
//  int nMaxStbRadius           -- �������뾶��user define����Ĭ��7
    int mvGetImgOffSet4Client( IplImage     *pFrame, 
		                 int                nAreaNum, 
						 const int          *nPolySize,
						 const CvPoint2D32f **fPolyPts, 
						 uchar              uAffModel, 
						 MyAffParams          &params, 
		                 int                nMaxStbRadius = 12,
                         float              fCornerQuality = 0.05f );

    // ���³�ʼ��������
    bool mvReInitialBkGrd( IplImage *pFrame, float fCornerQuality,
									                	const int *nPolySize, const CvPoint2D32f **fPolyPts );

private:

	// SIFT�ֲ�ƥ��뾶��������������ȣ������ƫ�������
	int m_nRadius;
	bool m_bUpdateCorners; // ���±�����?

	// sift���������sift������ȡ��ƥ��
    MySIFT m_SIFT;
		
	CvRect m_nRectMask[MAX_REGIONS]; // �˹�ָ��������������Ӿ��Σ�mask���򣬼�Ϊ��ƥ�����򣩣�����������ͼ

#ifdef DEBUG_CORNERMAP
	IplImage *m_pNewCorMap;// �µ���ִ���ͳ��ͼ
#endif

	CMyorners *m_pRefCorners, *m_pCurCorners, *m_pNewCorners;// [2*MAX_CORNERS]

	long m_nRefCorNum, m_nCurCorNum, m_nSIFTMatchNum, m_nRANSACMatchNum , 
		 m_nBeforeImgCount, m_nAfterImgCount, m_nFrameCout, m_nAreaNum, m_nUpdateNum, m_nNewCorNum;

	CvPoint2D32f m_fCurSiftMatchPts[MAX_CORNERS], m_fRefSiftMatchPts[MAX_CORNERS], m_fCurRANSACMatchPts[MAX_CORNERS], 
		         m_fRefRANSACMatchPts[MAX_CORNERS] ;

	CvSize m_nImgSize;

	MyAffParams m_fAppParams;

#ifdef DEBUG_PSNR
	IplImage *m_pStbImg;
    bool m_bIsStbImgSaved;
#endif

	uchar m_uAffModel;
};

#endif