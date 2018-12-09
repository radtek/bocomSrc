/*
 *���๦�ܣ�ʵ�ֶ�ֱ�ߵĺϲ���
 */
#ifndef	MV_LINE_MERGE
#define MV_LINE_MERGE

#include "MvLineSegment.h"
#include "MvLine.h"
#include "Calibration.h"
#include "MvMaxSize.h"


#ifndef	PI
#define PI 3.1415926
#define HALF_PI PI/2
#endif

#define MERGE_LINE_NUM 500

typedef struct _MergeLine{         //�Ϻص�ֱ�����ݽṹ��
	double x1;
	double y1;
	double x2;
	double y2;
	double ori;  //0-180
	double length;
	//double dRatio;  //���maxsizeXY�Ĵ�С
	bool   bMerge;	//�ϲ�
	bool   bBeMerge;	//���ϲ�
	int    type;		//0-ˮƽ�ߣ�1-��ֱ��
	//bool   bUsed;	//�Ѿ�ʹ��
	//bool   bEdge;	//�Ƿ��Ǳ�
}MergeLine;

class MvLineMerge
{
public:
	MvLineMerge(void);
	~MvLineMerge(void);

public:
	void MvLine2MergeLine(const MvLine **pSrcMvLines, int nLineNum);
	void MergeLine2MvLine();
	void Init(FindTargetElePolice::MyCalibration *pCalib, CvSize imgSize);
	void Destroy();
	void TestMvLineMerge(IplImage *img, unsigned int uFrame);
	void MyLinesMerge(BLine *lpBline, int nNonBgLineNum, MvLine **pRetMergedLine, int &nRetNum);
	
private:
	void MvSegmentUnite(BLine *lpBline, int nNoBgLineNum);
	//void QuickSort(double *data,int *index, int l, int r, bool bSmallToBig);
	void QuickSort(double *data,int *index, int l, int r);

private:
	//MergeLine *m_pSrcMergeLines;
	//int m_nSrcMergeLineNum;
	//MvLine *m_pMvLine[3];  
	MergeLine *m_pMergeLines[3];  //ָ��ˮƽ����ֱ����б���ֽṹ��ֱ�ߣ�
	MvLine *m_pAllMvLine;
	BLine *m_pSrcBLine;
	int m_nSrcBLineNum;
	int m_nMvLineNum[3];
	int m_nAllMvLineNum;
	FindTargetElePolice::MyCalibration *m_pCalib;

	IplImage *max_sizex;
	MvMaxSize *m_pMvMaxSize;
};

#endif