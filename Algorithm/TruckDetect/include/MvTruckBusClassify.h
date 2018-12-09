#ifndef DETECTONLINE_H_ 
#define DETECTONLINE_H_

#include "MvTruckBusClassify.h"

class opencv;
class CIOG;
class CDSIFT;
class CPyramid;
class CvSVM;

//--------------���ƺ�Ķ���------------ 
#define AN_VERSION_NUBER ("Version2014.04.03") //�汾���

class MvTruckBusClassify
{
public:

	MvTruckBusClassify();
	~MvTruckBusClassify();

	CIOG* iog;
	CDSIFT* dsift;
	CPyramid* pyramid;

	int m_num_words;
	int m_gridstep;
	int m_num_layar;
	int m_LengthofPyramid;
	int m_RoiHeight;
	int m_RoiWidth;
	CvMat* m_Dict_Mat;
	CvMat* m_Pyramid_Mat;
	CvSVM* svm;

	FILE *m_fpTexture;//������־
	 
	int init(char* dir_global , int num_levels = 2);
	int mvTruckBusClassify(IplImage* img, CvRect position, int max_size = 250);
	int mvTruckBusClassifyBlue(IplImage* img, CvRect position, int max_size = 250);//���Ƴ���
	int clean();

private:
	IplImage* createSample(IplImage* img, int max_size = 1000);
	int generateIndex(IplImage* roi, int max_size = 1000);
	int detect(CvRect rect); // ������
	int detectclean();
};

#endif