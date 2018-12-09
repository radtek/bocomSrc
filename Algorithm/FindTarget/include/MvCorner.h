#ifndef MV_CORNER_H
#define MV_CORNER_H

#include "cxcore.h"
#include "cv.h"
#include "StdAfx.h"

#ifdef SPEED_UP
#define SIFT_DESC_DIMENTION 64
#else
#define SIFT_DESC_DIMENTION 128
#endif



// �ǵ㡣�洢��һ���ǵ��λ�á�sift��������Ϣ��
typedef struct _MvCorner
{
public:
	// �ǵ��ͼ������x
	int ix;

	// �ǵ��ͼ������y
	int iy;

	// �ǵ����������x
	double wx;

	// �ǵ����������y
	double wy;

	// �ǵ����������z
	double wz;

	// �Ƿ񱳾��ǵ㡣
	bool bIsBgCorner;

	bool bIsEstimate;

	unsigned int uFrameSeq;

	int64 ts;
	
	unsigned int uTimestamp;

	// �ǵ��SIFT descriptor

	uchar feature[SIFT_DESC_DIMENTION];
	
	unsigned int uCarId;

	



	_MvCorner()
	{
		ix = 0;
		iy = 0;
		wx = 0.0;
		wy = 0.0;
		wz = 0.0;
		uFrameSeq   = 0;
		bIsEstimate = false;
		bIsBgCorner = false;
		memset(feature, 0, SIFT_DESC_DIMENTION);
		nIndex = -1;
		uCarId = 0;
	}

	
	// ���㵱ǰ����c2��ͼ����롣
	double GetImageDistance(const _MvCorner &c2)
	{
		return sqrt((double)(c2.ix-ix)*(c2.ix-ix) + (c2.iy-iy)*(c2.iy-iy));
	}


	double GetWorldDistance(const _MvCorner &c2)
	{
		return sqrt((c2.wx - wx)*(c2.wx - wx) + (c2.wy - wy) * (c2.wy - wy));
	}


	double GetWorldL1Dis(const _MvCorner &c2)
	{
		return fabs(c2.wx - wx) + fabs(c2.wy - wy);
	}

	// ���㵱ǰ���c2ͼ�������ĵ�
	CvPoint GetImgCenter(const _MvCorner &c2)
	{
		return cvPoint((ix + c2.ix)/2, (iy + c2.iy)/2);
	}


	void SetuCarId(int nIndex)
	{
		this->uCarId = nIndex;
	}

	void SetIndex(int nIndex)
	{
		this->nIndex = nIndex;
	}

	int  GetIndex() const
	{
		assert(this->nIndex != -1);
		return this->nIndex;
	}




private:

	// �ǵ��ڱ���֮ǰ����Ϊ-1.
	int nIndex;
public:
	int m_PerIndex;

} MvCorner;

struct MvCornerElem: CvSetElem
{
	_MvCorner corner;

	MvCornerElem(const _MvCorner &c):corner(c)
	{
	}
};

#endif