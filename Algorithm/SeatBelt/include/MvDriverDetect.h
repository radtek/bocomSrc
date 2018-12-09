#ifndef MV_DriverDetect_H_
#define MV_DriverDetect_H_

#define DETECT_WINDOW_SHOULDER


#include<opencv2/opencv.hpp>
#include "MvMulObjDetect.h"  //�����ͷ�ļ�
#include "MvSafetyBeltClassify.h"

using namespace std;
using namespace cv;

#ifndef WINDOW_AREA
#define WINDOW_AREA

struct WindowArea
{
	Target tWindow;

	Target tPilot;			//����ʻԱλ�ã����ڰ�ȫ�����ֻ���������

	bool bPilotByDetect;	//����ʻ�Ƿ��ɼ�����

	Target tCopilot;		//����ʻԱλ�ã����ڰ�ȫ����������

	bool bCopilotByDetect;  //����ʻ�Ƿ��ɼ�������Ϊ������ȫ��ʶ��

	bool bAllByGuess;       //���ݺͳ�����δ��⵽������λ����Ϣ��������

	WindowArea()
	{
		tWindow.dConfidece = 0.0;
		tPilot.dConfidece = 0.0;
		tCopilot.dConfidece = 0.0;

		bPilotByDetect = true ;	 //��ʼ������λ���ɼ����������ǳ������ƶ���

		bCopilotByDetect = true; //��ʼ������λ���ɼ����������ǳ������ƶ���
		
		bAllByGuess = false;     //��Ϊtrue����ֱ�ӷ��ز����κ�ʶ�� 
	}

};

#endif


class MvDriverDetect
{
public:
	MvDriverDetect(void);
	~MvDriverDetect(void);

public:
	bool mvInit( char* );

	bool mvInit( char* chhead = NULL, char* chVisor = NULL, char* chPhone = NULL );

	void mvUnInit();

	int mvWindowShoulderDetect(IplImage* src ,CvRect rROI, WindowArea& tArea,int ncartype );

	vector<Rect> mvMainDriverDetect(IplImage *pImage,const double dBigSideLength=200.00,const double dThres=0.0 );

	vector<Rect> mvBeltDetect(IplImage *pImage,float *fvaulS,const double dBigSideLength=150.00,
		const double dThres = 0.0, int ncartype = 1, int *nsize = NULL);
	
	vector<FaceRt> mvSvmDetect(IplImage *pImage,CvRect position,int ncartype,
		const double dBigSideLength=250.00,const double dThres=0.0 );

	vector<Target> mvVisorDetect(IplImage *pImage, int &nID,const double dBigSideLength=150.00 );

	vector<Rect> mvPhoneDetect(IplImage *pImage, float *fvaulS,const double dBigSideLength=150.00,const double dThres=0.0);

	Rect mvPossibleDriverPos(IplImage* pImg,CvRect position, int ncartype);

	vector<Target> mvWinDetect(IplImage *pImage, int &nID, const double dBigSideLength =200.00 );

private:
	HOGDescriptor* hog_driver;

	HOGDescriptor* hog_Phone;

	//ͷ��
	MvMulObjDetect *objhead;

	//������
	MvMulObjDetect *objSunVisor;

	//add by liuyang �²��ԣ�����ͷ��һ����
	MvMulObjDetect *pWindow_Shoulder;

	Target MvDriverDetect::mvBiggestOne(vector<Target> vTarget);

	int mvRationality( WindowArea& tW, IplImage* pImage );



	double mvRectCoverRate( Rect r1, Rect r2 );   //�����������ε��ص���

	bool mvIsVerticalShift( Rect r1, Rect r2 );  // ˮƽ����

	Rect mvRectCombineSmall( Rect r1, Rect r2 );     //�ϲ��������� խ����

	Rect mvRectCombineBig( Rect r1, Rect r2 );     //�ϲ��������� �����

	int mvRectGroup( vector<Rect>& V_R, vector<double>& V_W,const double dThres );        // һ��Rect�����ϲ�

	vector<Rect> mvRationality( vector<Rect> V, const IplImage* pImage );		// �������ж�

	vector<FaceRt> mvFaceRationality( vector<FaceRt> V, const IplImage* pImage );		// �������ж�

	//void mvDriverDetect(IplImage *pImage,const double dBigSideLength=200.00, Rect& rLRect=Rect(0,0,0,0),Rect& rRRect=Rect(0,0,0,0) );

	FaceRt mvGetHighScoreRect(const vector<Rect> V_R, const vector<double> V_W);

	float mvGetHighScorevaule(const vector<double> V_W);

	int mvEdgeSelect(IplImage *src,IplImage *dst);

};

#endif

