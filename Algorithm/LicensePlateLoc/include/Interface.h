#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "ConvNet.h"

#ifdef _WINDLL
#define LPLOC_API __declspec(dllexport)
#else
#define LPLOC_API
#endif

const int g_nLPNetNum = 6;  //���ڳ��Ƶ㶨λ�����������
const int g_nLayerNum = 3;  //��˫���־����������
class licensePlateLoc
{
public:
	LPLOC_API licensePlateLoc();
	LPLOC_API ~licensePlateLoc();

	LPLOC_API int dlInit(char* filename_loc[g_nLPNetNum], char* filename_class, bool bUseFineTuning = true, int nIterNum = 3);
	LPLOC_API float dlForward( IplImage *pImgSrc, CvRect rectRoi, vector<CvPoint> &vecPts, int &nLayer);
	LPLOC_API CvMat* GetShape();

private:
	bool dlImgPreprocess(IplImage *pImgSrc, CvRect &rectRoi);
	bool dlSubImgPreprocess(IplImage *pImgSrc, CvPoint ptPredict, float fLPWidth, CvRect &rectRoi);
	bool dlGetRslt(float *pLocNet, CvRect rectRoi, int nPtNum, vector<CvPoint> &vecPts);
	//�������磡
	bool dlFineTuning(IplImage *pImgSrc, const vector<CvPoint> &vecPts, vector<CvPoint> &vecRectfPts);
	//�жϵ���˫���ƣ�0�����㣬1��˫�㣬-1������
	int JudgeLayer(IplImage *pImgSrc, const vector<CvPoint> &vecPts, float *fSingleProb);
	//ͼ��Ԥ�����߽��жϣ�resize������ֵ��
	bool dlImgPreprocess4LayerNet(IplImage *pImgSrc, const vector<CvPoint> &vecPts, CvRect &rectRoi);
	//���أ�0�����㣬1��˫�㣬2����ȷ����-1������
	int GetLayerLabel(float *fProb, string strLayer2Extr, float *fSingleProb);
	bool GetUnionRect1(CvRect r1, CvRect r2, CvRect &ret);
	bool expandRegion(CvRect region1, CvRect &region2, float fXScale, float fYScale);
private:
	vector<vector<ConvNet*> > m_convnet;
	ConvNet *m_convnet4LayerClass;//�б�˫�㣻
	vector<CvPoint2D32f> m_point;
	CvMat* m_matFaceShape;
	vector<CvRect> m_rect;

	IplImage* m_imgShowResult;

	//wyj
	int m_nIterNum;
	bool m_bUseFineTuning;
};

#endif/*__DEEP_FACIAL_POINT_H__*/
