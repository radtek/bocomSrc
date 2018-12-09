#pragma once
#include <cv.h>

using namespace std;
using namespace cv;

//���Կ���
#define MV_DRAW_DEBUG_LINUX //Linux�½����ļ��п��� 
//#define MV_SAVE_RESULT_IMG  //������ͼƬ

class MvPlateDetector
{
public:
	MvPlateDetector(void);
	~MvPlateDetector(void);

private:
	CvHaarClassifierCascade * m_pVehicleCascade;	//���������
	CvHaarClassifierCascade* m_pCascade;			//�Ƿ����������

	bool verifySizes(Rect mr);			//�жϳ��������Ƿ�Ϻ�Ҫ��

public:
	bool mvInit(const char * pName);
	void mvUnInit();

	bool m_bDebugOn;
	//�ֶ�λ
	vector<CvRect> mvDetectPos(const IplImage *pImage);

	vector<CvRect> mvDetectPos_Ext(const IplImage *pImage);
	//
	vector<Rect> VerifyPos(const Mat input);
	//���ڵ���
	bool IsCarWithPlate(const IplImage * pImg, CvRect rt);
	//Υ�µ���,��������������Ƿ�����ĳ������Ƿ���true�����Ƿ���false
	bool JudgeIsRealVehicle(const IplImage * pImg, CvRect rt);
};

