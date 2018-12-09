#ifndef  CORNER_H
#define  CORNER_H


#include "declare.h"
#include "fast.h"
#include "Mem_Alloc.h"
#include "MvSift.h"
#include "MvUtility.h"

#include "sift_descr.h"

using namespace siftdes;

namespace Shut_Corner
{

	typedef struct  _MV_CORNER
	{
		int x;
		int y;
		int val;
		_MV_CORNER()
		{
			x = 0;
			y = 0;
			val = 0;

		}
	} MvCorner;


	typedef struct  _MV_CORNER_PARM
	{
		int nConerCnt;
		CvPoint *pCornPos;
		unsigned char **pFeature;
		char *pMatchStatus;

		_MV_CORNER_PARM()
		{
			nConerCnt = 0;
			pCornPos = NULL;
			pFeature = NULL;
			pMatchStatus = NULL;

		}

	} MvCornerParm;



	class  Corner
	{

	private:
		int m_nPointsCount;  //�ǵ�����
		CvPoint *m_pCornPoints;  //�ǵ�����λ�� 

		//sift������
		int *m_pSiftHistogram;  //�ǵ�Ĺ�һ��ǰ��sift����
		uchar **m_pFeature;  //�ǵ��sift������

		uchar* m_pCornerBackImage;
		MvCorner *m_pCornerPass; //ͨ���ǵ��⡢�ֲ�����ֵ���ơ��ǵ㱳��ģ�͡��߽����ƵĽǵ���Ϣ
		MvCorner *m_pCornerMax;
		xy       *m_pCornerBg;

		char  *m_pMatchStatus;  //�ǵ��ƥ��״̬
		MvInputData  m_inputData;
		CvSize  m_ImgSize;
		bool    m_bInit;

		MySIFT m_sift;

	public:
		void mvInit(CvSize ImgSize);
		void mvGetImageConer(const IplImage *pGrayImage,bool bDay);
		int mvGetConerNumInRgn(CvRect Rgn);
		MvCornerParm  mvGetConerPram();
		void mvUnit();
		Corner();
		~Corner();
		
	private:

		void  mvCalculateHarrisResponseOptimize(unsigned char *srcImg,
			int width,
			int height,
			int *tp,
			MvCorner *harris_response,
			int num);

		void mvCalculateHarrisResponse(unsigned char *srcImg,
			CvSize size,
			MvCorner *harris_response,
			int num);

		void mvCornerResponseRestrain(MvCorner *corner_pass,
			MvCorner *corner_max,
			int num_pass,
			int *num_max,
			int max_num);




	};

};
#endif