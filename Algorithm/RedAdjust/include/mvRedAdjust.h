//��ģ���ʵ�ֺ�������У��
#include "cv.h"
#include "ml.h"
#include "highgui.h"
#include "cxcore.h"
#include <iostream>
#include <fstream>

using namespace std;

const int nHsize = 37; //H��bin����//0~360,��opencv��180/10
const int nSsize = 32; //S��bin����//0~1,��opencv��256/32

//#define testzch  //���ز���
#define handzch  //�ύ����
//#define jinan_yellow //���Ϻ�����ã��Ƽܱ���Ϊ��ɫ
#define historyTest
//#define expTest //�ع����
//ע�⣺rRedrect���ο��ǻ���ͼ��ģ�������ͼ��������ӵ�ͼ����Ϣ��ǿ�
#define liuyang //�����Ŀ-ѧ��һ����ɫ����

//#define MV_LOWLIGHT_OLD   //���ն��Ϸ���
#define MV_LOWLIGHT_NEW   //���ն��·���

//#define MV_COLOR_JUDGE_OLD  //�������-�Ϸ���
#define MV_COLOR_JUDGE_NEW  //�������-�·���


#ifndef _LightExpHeader
typedef struct  _LightExpHeader
{
	CvRect LightRegion;//������ͷ��������λ��
	int nColorFlag;//�ع���̵Ƶ���ɫ��Ϣ��0-��ƣ�1-�̵ƣ�2-�Ƶ�; -1-û�е���
	CvRect rLightRect;//���λ��
	CvRect gLightRect;//�̵�λ��
	CvRect yLightRect;//�Ƶ�λ��

	_LightExpHeader()
	{
		LightRegion = cvRect(0,0,0,0);
		nColorFlag = 0;
		rLightRect = cvRect(0,0,0,0);
		gLightRect = cvRect(0,0,0,0);
		yLightRect = cvRect(0,0,0,0);
	
	}
}LightExpHeader;//�ƿ�Ĵ����
#endif



class MvRedLightAdjust
{
public:
	MvRedLightAdjust(CvRect rRedrect[], int nRednum);//���̵�ƫɫ

	MvRedLightAdjust(LightExpHeader rLightrect[], int nLightnum, int LightInf[]);//���̵��ع�

	~MvRedLightAdjust();
	//�汾��
	char *GetVersion();
	//�����ӿ�
	int mvRedLightAdjust(IplImage *pImage);
	int mvRedLightAdjustNew(IplImage *pImage, int LightInf[]);
	//���̵��ع�
	int mvLightExposureAdjust(IplImage *srcImg, int LightInf[]);
	int mvLightRedcastAdjust(IplImage *pImage);
	
	//hsѧϰ
	void mvRedHSTrain();
	void mvHSMatSave();

	void mvHSMatRead();
	IplImage *pSaveImg;
	
	//���ƫɫ����
	void mvRedRevise_zch(IplImage *srcImg, CvRect rectSrc);
	void mvLightRevise(IplImage *srcImg, CvRect rectSrc);//���㷨�������˺��̵�ͷ��λ����Ϣ
	void mvHSRevise(IplImage *pImgHsv, IplImage *pdIS, IplImage *pdISMask);//dis����
	void mvHSReviseByMask();//ģ������
	void mvRedReviseSubPix();
	float ThresholdOtsu(IplImage* grayim, CvRect rect, IplImage *mask); //ostu��ֵ�ָ�
	bool mvColorDis(CvScalar sRed, CvScalar sLargex);
	void mvImgMoment(IplImage *Pimage, CvRect *rect, CvPoint2D32f *centerNow);

	bool mvJudgeValidRect(IplImage *pSrcImg);

	void mvGetMinMaxArea(LightExpHeader LightTotalRect, float *fMin, float *fMax);
	
	//��������
	void mvLightExpRegionDetect(int nColorFlg, float fMin, float fMax, CvRect rLHRegion);
	//����Graph�ָ�-�·���
	void mvLightExpRegionDetectNewSegment(int nColorFlg, float fMin, float fMax, CvRect rLHRegion);

	void mvContourAnalysisBound(IplImage *pMsk);

	//����ɫ��ǿ
	void mvLightExpColorRevise(int nColorFlag, IplImage* pHistoryMsk, CvRect rectR);
	void mvLightExpColorReviseNew(int nColorFlag, IplImage* pHistoryMsk, CvRect rectR);
	
	void mvRemoveByInit(IplImage *plightMsk, IplImage *pMsk);

	//���̵���ǿ
	int mvLightColorcastAdjust(IplImage *pImage);

	int mvLightColorcastAdjustNew(IplImage *pImage);

	void mvGreenHSTrain();//�̵�ѧϰ
	void mvGreenHSMatSave();//�̵�ģ��
	void mvRedRevise(IplImage *srcImg, CvRect rectSrc, float fTh);//���ƫɫ����
	void mvGreenRevise(IplImage *srcImg, CvRect rectSrc, float fTh);//�̵�	
	void mvContourAnalysis(IplImage *colorMsk, IplImage *srcImg, CvRect rectSrc);//��������
	void mvComputeDisimage(IplImage *pMsk, int nColor);//����ͼ��
	void mvColorRevise(IplImage *phls, IplImage *pdis, IplImage *pMsk, int nColor);//��ɫ��ǿ

	void mvRedGreenRevise(int *rgbPt, IplImage *pHisRed, IplImage *pHisGreen, int &xCenterAxisRect);//���̵�

	void mvRedGreenReviseNew();

	bool mvContourAnalysisRGY(IplImage *colorMsk, int *rgbPt);

	void mvContourAnalysisBoundaryNew(IplImage *colorMsk);

	void mvContourAnalysisOnly(IplImage *colorMsk, bool flag, int xCenterAxisRect);

	void mvContourAnalysisOnlyNew(IplImage *colorMsk, int nColorPixNum, int nColorFlag);


	void mvHistorySeq(IplImage *pLightMask, IplImage* pHistoryMsk);
	
public:
	CvRect rRedRect[10];//��Ƶ�roi,ע�⣺�þ��ο��ǻ���ͼ��ģ�������ͼ��������ӵ�ͼ����Ϣ��ǿ�
	int nRedNum;//��Ƶ�roi���������Ϊ10��
	
	LightExpHeader LightRect[10];//�Ƶľ��ο�ע�⣺�þ��ο��ǻ���ͼ��ģ�������ͼ��������ӵ�ͼ����Ϣ��ǿ�
	int LightRectInf[10];//�ź�
	int nExpLightNum;//ͼ�����ع���̵ƴ��������

private:
	
	int64 start;//������ģ�����ʱ��
	int64 updateTh;//����ģ���ʱ������������Ϊ30����
	int64 updateTime;//���ڽ�����ģ���ʱ�䣬�����趨Ϊ2����
	int64 TimeLast;//�����׶Σ�ǰһ��hs��ѧϰ����ʱ��
	
	bool bInit;//��ʼ���Ƿ����
	bool bInitLast;//ǰһ����ɫģ��ѵ����ϵ�ʱ��
	bool bLearn;//ѧϰģ��
	bool bLearnOK;//ѧϰ��ϣ��������hs
	bool bTest;//hs�������
	bool bisFirst;//�Ƿ��һ��ѧϰ
	
	IplImage *pRedRect; //���
	IplImage *pRedMask; //��Ƶ���Ĥ
	IplImage *pRedHS; //�������hsv�ռ�ͼ
			
	CvSize sizei;//���ͼ��Ĵ�С
	CvRect biglightRect;

	float mPDH[nHsize][nSsize];//��Ƶ������ֲ�ֱ��ͼ
	float mPDHN[nHsize][nSsize];//�Ǻ�Ƶ������ֲ�ֱ��ͼ
	float mHSPDH[nHsize][nSsize];//��ɫ���ʷֲ�

	//int nHTh; 
	int nHThLow; //��Ϊ�Ǻ��h����ֵ
	int nHThHigh;//��Ϊ�Ǻ��h����ֵ
	int nSTH; //��Ϊ�Ǻ�Ƶ�s����ֵ
	int nVTH; //��Ϊ�Ǻ�Ƶ�v����ֵ
	
	int nHcosnt;//��׼��Ƶ�hֵ
	double dVmean;//��ƹ��յľ�ֵ
	double dVmax;//��ƹ��յ����ֵ
	double dSmean;//��ƹ��յľ�ֵ
	double dSmax;//��ƹ��յ����ֵ
	float WHratio;//�������
	float WHth;
	float fMaxDis;//��������ֵ
	bool bDisMethod;//�Ƿ���ùǼ���Ϣ

	//
	IplImage *pGreenMask; //��Ƶ���Ĥ
	int nGThLow;//�̵�
	int nGThHigh;
	int nGHconst;//��׼�̵Ƶ�hֵ
	float mPDHG[nHsize][nSsize];//�̵Ƶ������ֲ�ֱ��ͼ
	float mPDHNG[nHsize][nSsize];//���̵Ƶ������ֲ�ֱ��ͼ
	float mHSPDHG[nHsize][nSsize];//��ɫ���ʷֲ�

	int64 TimeLastG;//�����׶Σ�ǰһ��hs��ѧϰ����ʱ��

	bool bInitG;//��ʼ���Ƿ����
	bool bInitLastG;//ǰһ����ɫģ��ѵ����ϵ�ʱ��
	bool bLearnG;//ѧϰģ��
	bool bLearnOKG;//ѧϰ��ϣ��������hs
	bool bTestG;//hs�������
	//bool bIsRedRevise;//
	
	//�ع�
	int nHexpConst[2];//�ع���ǿ����
	CvPoint ptRGY[4];//���̻ƵƵľ��ο�����

	//���̵�ͬʱ��ǿ
	int RGYcenter[20][6];//����ο�ͬ��
	//float fLightArea;//�Ƶ����


	IplImage *phistoryRed[10];//���ģ��
	IplImage *phistoryGreen[10];//�̵�ģ��
	int xCenterAxis[10];//�����λ�ã��𶯻����ƫ�ƣ�
	int nUpdateRatio;//��ʷģ��ĸ�����
	int nHistoryInitial;//��ʷѧϰ������

	bool bSaveImg;      //������ն��м���
	IplImage *pexpSave;//�м�������
	int expNum;//�����ͼ��֡��
	char cbufExp[256];	//����·��

	int nSetRedH;
	int nSetRedS;
	int nSetRedV;

};