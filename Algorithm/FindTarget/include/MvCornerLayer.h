// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   11:56
	filename: 	e:\BocomProjects\find_target_lib\include\MvCornerLayer.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MvCornerLayer
	file ext:	h
	author:		Durong
	
	purpose:	�ǵ��
*********************************************************************/


#ifndef MV_CORNER_LAYER_H
#define MV_CORNER_LAYER_H

#include <list>
#include <vector>
#include "cxcore.h"
#include "cv.h"

#include "sift_descr1.h"
#include "MvCorner.h"
#include "MvCornerBGM.h"
#include "Calibration.h"
#include "CornerBackgroundModel.h"

//#include <xmmintrin.h>



//using namespace std;

using namespace PRJ_NAMESPACE_NAME;

// ÿ����ȡ�ǵ��������ô���
#define FRAME_MAX_CORNER_COUNT 200
#define FRAME_MAX_CORNER_COUNT_FOR_ELE 300

#define SIFT_DESCR_WIDTH 4
#define SIFT_BINS        8 //SIFT_DESCR_WIDTH * SIFT_DESCR_WIDTH * SIFT_BINS = 128
//
//typedef struct _CorIndexMap
//{
//	int nMapWidth;
//	int nMapHeight;
//	int *pIndex;
//
//	_CorIndexMap(int nW, int nH)
//	{
//		pIndex      = new int[nW*nH];
//		if (!pIndex)
//		{
//			printf("");
//			exit(-1);
//		}
//		nMapWidth   = nW;
//		nMapHeight  = nH;
//	}
//
//
//	~_CorIndexMap()
//	{
//		if (pIndex)
//		{
//			delete [] pIndex;
//			pIndex = NULL;
//		}
//	}
//
//
//	void SetMap(int val)
//	{
//		for (int i=0; i<nMapWidth * nMapHeight; i++)
//		{
//			pIndex[i] = val;
//		}
//	}
//
//}CorIndexMap;



typedef struct  _MV_CORNER_HARIS
{
	int x;
	int y;
	int val;
	_MV_CORNER_HARIS()
	{
		x = 0;
		y = 0;
		val = 0;

	}
} MvCornerHaris;

class MvCornerLayer
{
public:

	// ���캯��
	//MvCornerLayer(MvCornerBGM *pCornerBGM/*, MyCalibration *pCalib*/);

	MvCornerLayer(CornerBackgroundModel<CvPoint2D32f> *pCornerBGM);



	// ��������
	~MvCornerLayer();

	// ��ͼ������ȡ�ǵ��γ�MvCorner
	void ExtractCorners( IplImage *imgGrayFrm, const unsigned int uFrameSeq,const int64 ts, const unsigned int uTimestamp,bool bDay,
		const  MyCalibration *pCalib, MvCorner corners[FRAME_MAX_CORNER_COUNT_FOR_ELE], int &nPtsCount,const bool bVio_Target,
		const std::vector<CvRect> &CarGroupPark,const IplImage* predimg =NULL);
	
	// ����ǵ�
	//void SaveCorners(MvCorner corners[FRAME_MAX_CORNER_COUNT], int nCount);

	// ����ǵ�.�����ر�����ͼ����set���index
	//void SaveCorners(MvCorner corners[FRAME_MAX_CORNER_COUNT], int nCount, std::vector<int> &vecIndex);
	void SaveCorners(MvCorner corners[FRAME_MAX_CORNER_COUNT], int nCount, std::vector<MvCorner*> &vecCorners);


	void SaveCorners(MvCorner corners[FRAME_MAX_CORNER_COUNT], int nCount, MvCorner* cor_pointer[FRAME_MAX_CORNER_COUNT]);


	// ����һ���ǵ㣬������������
	int SaveOneCorner(const MvCorner &corner);

	// ��������ȡ�ǵ㡣
	//MvCorner GetCorner(int nIndex);

	// ��������ȡ�ǵ��ָ�롣
	MvCorner* GetCornerPointer(int nIndex);

	// ��������ɾ���ǵ㡣
	void RemoveCorner(int nIndex);

	
	// ��֡��ȡ�ǵ㡣��ʱ
	//void GetCorners(unsigned int uFrameSeq, vector<MvCorner> &ret);

	// ��֡��ȡ�ǵ㡣��ʱ
	//void GetCorners(unsigned int uFrameSeq, vector<int> &ret);

	// ���ر궨����
	//MyCalibration* GetCalibrationObj();

	// ��ȡ�ǵ��������Ľǵ������
	int GetCornerCount() const;


	void DebugCorners(const std::vector<int> &vecIndex);


	static void DrawCorners(const std::vector<int> &vecIndex, IplImage* img, MvCornerLayer *pCorLayer);

	// ������
	void MyFastFeaturesToTrack(const IplImage* pSrcImg, 
		CvPoint2D32f* _corners,
		int* _corner_count, double  quality_level,
		double  min_distance,
		int block_size,  //FileBox�����õ�
		const IplImage* pMaskImg CV_DEFAULT(NULL) //����Ȥ����ͼ
		,const IplImage* predimg CV_DEFAULT(NULL));//�켣Ԥ��λ��ͼ

	void MycalcMinEigenVal(const CvMat* _cov,CvMat *_dst);

	void MycornerMinEigenVal(const IplImage * src, CvMat* dst, int blockSize);

private:
	
	// memory storage
	CvMemStorage *m_pMem;

	// �洢�ǵ�
	CvSet        *m_pCornerSet;
	int        m_nCornerThresh;



private:
	
	// �ǵ㱳��ģ��
	CornerBackgroundModel<CvPoint2D32f> *m_pCornerBGM;
	void CalculateHarrisResponse(const IplImage *pGrayImg,const IplImage *pWeightimg, MvCornerHaris *harris_response,int num);
	void CalculateHarrisResponse(const IplImage *pGrayImg,const IplImage *pWeightimg,const int *tp,MvCornerHaris *harris_response,int num);
	int CornerResponseRestrain(MvCornerHaris * corner_pass,
		MvCornerHaris ** corner_max,int num_pass,int numMax);
	int CornerResponseRestrain2(MvCornerHaris * corner_pass,
		MvCornerHaris ** corner_max,int num_pass,int numMax);
	void compute_descriptors(uchar *descriptor,IplImage* image,CvPoint2D32f *corners,int nPtCnt ); 
	void ComputeSingleSurfDescriptor(IplImage *puImgGray,  CvPoint2D32f *pPoint, unsigned char *descriptor);
	
	 



public:
	bool  m_bEleDec;//���β�����羯���
	bool  m_bDay;  //����


	//// sift��ʱ����
	//float***   histgram;
	//float*     float_descr;
	//int*       gradFlag;
	//float*     gradmag;
	//float*     gradori;

	

	// �궨����
	//MyCalibration   *m_pCalib;
};


#endif
