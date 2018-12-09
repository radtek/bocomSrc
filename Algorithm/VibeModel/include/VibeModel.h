// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef	VIBEMODEL_H
#define VIBEMODEL_H

#ifdef  OPENCV245
	#include "opencv2/opencv.hpp"
	#include "opencv2/objdetect/objdetect.hpp" 
	#include "opencv2/features2d/features2d.hpp" 
	#include "opencv2/highgui/highgui.hpp" 
	#include "opencv2/calib3d/calib3d.hpp" 
	#include "opencv2/imgproc/imgproc_c.h" 
	#include "opencv2/imgproc/imgproc.hpp"   
	#include "opencv2/nonfree/features2d.hpp"
	#include "opencv2/legacy/legacy.hpp"
	#include "opencv2/legacy/compat.hpp"

	#include <wtypes.h>
	using namespace cv; 
#else
	#include "cv.h"
	#include "highgui.h"
	#include "cxcore.h"
#endif

#include "Ultility.h"

#ifndef PI
	#define PI (3.1415926)
#endif
#define ILLUM_DIM (60)
#define	FORIMAGE_NUM (3)
#define PI_HALF (PI*0.5f)
#define BK_SHORT_DIM (8)
#define BK_LONG_DIM (12)
#define INTERVAL_BK (180)


class VibeModel
{
public:
	VibeModel(void);

	~VibeModel(void);

	void libVibeModel_Release_8u(void);
	
	bool libVibeModel_Init_8u(IplImage *img, IplImage *grayImg, const int &dim=3, const int &R=8, 
								const int &seta=16, const int &min=1, const int &N=5, 
								const int &colorMode=V_BGR, const bool bIsResize=false, 
								const int &wScale=1, const int&hScale=1, const int &nNerbor=2);

	void libVibeModel_Update_8u(IplImage *img, IplImage *grayImg, IplImage *bgForeImg,
									IplImage *bkImg=NULL, int nSmoothTypes=V_SM_ORIGINAL);
	

private:
	void libVibe_AllocImages(void);

	void libVibe_AllocVariable(const int &w, const int &h, const int &dim, const int &R,
				const int &seta, const int &min, const int &N, const int &colorMode,
				const bool bIsResize, int wScale, int hScale, int nNerbor);

	void libVibe_AllocBkImages(void);

	bool libVibe_ModelInit(IplImage *img, IplImage *grayImg, bool bIsChange=false);

	void vibeModelUpdate_8u_C1R( IplImage *oriGrayImg, IplImage *foreImg, bool bIsChanged=false );

	void vibeModelUpdate_8u_C3R(IplImage *oriImg, IplImage *foreImg, bool bIsChanged=false);

	inline int mvGetRandomNumber(const int &min, const int &max) const;

	inline unsigned short mvEuclidDist_GRAY(const BYTE &a, const BYTE &b) const;

	inline int mvEuclidDist_RGB( BYTE *a, BYTE *b );

	inline unsigned short mvEuclidDist_L_Inf(const BYTE *pSrcB, const BYTE *pSrcG, const BYTE *pSrcR, const BYTE *pOutB,
									const BYTE *POutG, const BYTE *pOutR) const;

	IplImage **mvEuclidDist_L_Inf(IplImage *bgrImg) const;

	inline void mvGetRandomNeighbrXCoordinate(const int &x, int &nb_x) const;

	inline void mvGetRandomNeighbrYCoordinate(const int &y, int &nb_y) const;

	void mvFittering(IplImage *bgForeImg, const int nSmoothTypes, const int nSize=36) const;

	bool mvIsSuddenIlluminance(IplImage *grayImg, IplImage *foreImg);

	void mvGetStopForeground(IplImage *bgForeImg);

	void mvUpdateIlluForeground(IplImage *lstGrayImg, IplImage *foreLstImg, IplImage *grayImg, 
		IplImage *bgForeImg, const bool &bIsChange);

	int mvComputeIIlluminan(IplImage *grayImg, float scale_W=0.25f, float scale_H=0.25f, double dExpoIndex=0.5);

	void mvMoveShadowsByHSV(IplImage *bgrImg, IplImage *bgrBgImg, IplImage *bgForeImg) const;

	void mvMoveShadowsByConstancy(IplImage *foreLstImg, IplImage *bgrImg, IplImage *bgrBgImg, IplImage *bgForeImg);

	void mvMoveShadowsByTexture(IplImage *bgrImg, IplImage *bgrBgImg, IplImage *grayImg, IplImage *bgForeImg);

	void mvMoveShadowsByRatio(IplImage *bgrImg, IplImage *bgrBgImg, IplImage *grayImg, IplImage *bgForeImg);

	void mvComputeNoiseDeviation(IplImage *oriImg, CvScalar &noiseDv) const;

	void mvComputeRatio(IplImage *bgrImg, IplImage *bgrBgImg, IplImage *shadowImg, IplImage *foreUpdtImg,
							IplImage *shdwUpdtImg, CvScalar &noiseDv, const int &W_R, const float &fLamda, const float &TR);
	
	void mvGetIntensityMskImg(IplImage *bgrImg, IplImage *bgrBgImg, IplImage *bgForeImg, IplImage *cmpMskImg) const;

	bool mvRemoveShadowByHist(IplImage *roiImg, CvRect &rect) const;

	IplImage *mvCreateIntegrayImg( IplImage *binaryImg ) const;

	inline void mvErodeByNbr(IplImage *binaryImg, int wx_R, int wy_R) const;

	void mvUpdateMedianBk(const IplImage *img, IplImage *pMedianBg, BYTE ***pList, int nDim, int nChnnls);

	void mvGetBkImg(IplImage *img, IplImage *longBkImg);

	void mvSmoothByContours(IplImage *bgForeImg, const int nSmoothTypes, int nSize) const;

	void mvSmoothByMedian(IplImage *bgForeImg) const;

	void mvSobelHorizontal(IplImage *grayImg, IplImage *sobelImg, const int MIN_THRESHOLD_SOBEL) const;

	inline long	mvGetIppSumInRect(IplImage* integrayImg, CvRect rect) const;

	void mvRemovalSmear(IplImage *grayImg) const;

	IplImage *mvFilterExposurePixels(IplImage *grayImg) const;

	void mvGetSobel(IplImage *grayImg, IplImage *sobelImg) const;

	void mvGetVSobel(IplImage *srcImg, IplImage *dstImg) const;

	void mvGetHSobel(IplImage *srcImg, IplImage *dstImg) const;

	void mvGetBkDiffImg(const IplImage *grayImage, const IplImage *bgImage, 
							IplImage *diffImg, int nDiffThres, int nMinDiffThres, float fThres);

	void mvVibeSobel( IplImage *src, IplImage *dst, const int xorder, const int yorder, const int aperture_size ) const;

private:
	unsigned short m_skpFram;

	unsigned short m_NG_C; //2 ��Ӧ��4��ͨ�� 3��Ӧ��8��ͨ��

	short m_BOUND_UP; //����������Ŀ��Ͻ�

	short m_BOND_DOWN; //����������ı��½�

	const unsigned short THRESHOLD;


private:
	IplImage **m_samImgs; //����ģ��ͼ��

	IplImage *m_foreLstImg; //����ǰ��mapͼ��

	IplImage *m_bgrImg; //��ǰ֡��ɫͼ��

	IplImage *m_bgrLstImg; //ǰһ֡��ɫͼ��

	IplImage *m_grayImg; //��ǰ֡�Ҷ�ͼ��

	IplImage *m_lastImg; //�Ҷ�ǰ֡ͼ��

	IplImage **m_foreImgSet; //ǰ��֡ǰ��ͼ�񼯺�

	IplImage *m_upForImg; //��֡�����ǰ��ͼ��

	IplImage *m_sitaThImg; // ǰ������Ӱ��ֵͼ��

	IplImage *m_rndNbrImg; //�����ͼ��

	BYTE ***m_pLongBkSet; //���ڱ���ͼ��ģ��

	BYTE ***m_pBkSet; //���ڱ���ͼ��ģ��

	IplImage *m_bkImg; //���ڱ���ͼ��

	IplImage *m_bkLongImg; //���ڱ���ͼ��

	int m_width; //������ģͼ����

	int m_height; //ͼ��߶�

	CvSize m_imgSize;

	int m_nN; //��������

	int m_nSubN; //�������µ�ʱ����

	int m_nMinN; //��С�Ļ���

	int m_nR; //��뾶R

	int m_chnnls; //��ɫͨ��ģʽ ֧�ֵ�ͨ������ͨ��

	int m_nInitCount; //��ʼ��֡����ͳ��

	int m_nLChangHist[ILLUM_DIM]; //ͳ�ƶ�֡����

	int m_nLastIllu; //ǰһ֡���ն�

	float m_fRatio; //�նȱ�ֵ

	bool m_bIsChanged; //�ж��Ƿ��նȸı�

	bool m_bIsUpdate; //ǰ���Ƿ�Ҫ����

	int m_colorMode; //bgr �� rgb��ɫģʽ

	CvRNG m_rnd_state; //��ʼ�������������

	unsigned int m_frmCount; //֡��ͳ��
	
	bool m_bIsLongBk; //�Ƿ���ڳ��ڱ���

	bool m_bIsFirtTime; //�Ƿ��ǵ�һ�����б�lib��

	bool m_bIsFirstUpdate; //�Ƿ��ǵ�һ�ε��ø��³���

	float m_resizeRatio; //���ű���

	bool m_bIsResize; //�Ƿ���Ҫ����

	float m_lstNotZeroRatio; //ǰһ֡ǰ���ı���

	bool m_bIsAllFore; //�Ƿ���ȫ��ǰ��

	int m_seta; //����ĳ���������ֵ

	int m_countSud;

	#ifndef LINUX
		char *m_buffer;
	#endif

};

#endif