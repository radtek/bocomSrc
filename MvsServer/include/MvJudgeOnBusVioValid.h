#pragma once
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

class MvJudgeOnBusVioValid
{
public:
	MvJudgeOnBusVioValid(void);
	~MvJudgeOnBusVioValid(void);

private:
	CvHaarClassifierCascade* m_pPlateCascade;			//�Ƿ����������

	bool verifySizesRt(CvRect rt);			            //�жϳ��������Ƿ�Ϻ�Ҫ��

public:
	bool mvOnBusVioValidInit(const char *pName);
	void mvOnBusVioValidUnInit();

	//�ֶ�λ
	vector<CvRect> mvDetectPlatePos(const IplImage *pImage);

	//�ж����г���rt�ұ��Ƿ��г���
	bool IsHaveCarInPlateRight(const IplImage *pImg, vector<CvRect> &vecRt, CvRect rt);

	//�ж���ͼ���Ұ���Ƿ��г���
	bool IsHavePlateInImgRight(const IplImage *pImg, vector<CvRect> &vecRt);

	bool mvOnBusVioValidJudge(const IplImage *pImage1,vector<CvRect> &vecRt1,
		                	  const IplImage *pImage2,vector<CvRect> &vecRt2,
		                      const IplImage *pImage3,vector<CvRect> &vecRt3,
							  CvRect plateRt);
};