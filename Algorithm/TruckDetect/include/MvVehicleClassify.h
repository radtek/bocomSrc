#ifndef MVVEHICLECLASSIFY__H__
#define MVVEHICLECLASSIFY__H__

#include <cv.h>
#include <highgui.h>
#include "ml.h"
#include <algorithm>
#include <vector>

using namespace std;
using namespace cv;

struct CARNUM_CONTEXT;
class MvVehicleClassifyDetail;

#ifndef OBJECTCAR
#define OBJECTCAR
typedef struct CAR_INFO   //�������ݽṹ��
{
	CvRect  plate_rect; //����λ��,�����ԭͼ
	CvRect  car_rect; //����λ��,�����ԭͼ
	int plate_color; //������ɫ��1�� 2�� 3�� 4�� 5������
	int carnumrow; //��˫�ƣ�1���� 2˫�� 3������
	int nCarNumDirection; //���Ƶķ���(0ǰ�� 1β�� 2δ֪)
	char carnum[7]; //���ƺ���
	CAR_INFO()
	{
		plate_rect = cvRect(0,0,0,0);
		car_rect = cvRect(0,0,0,0);
		plate_color = 5;
		carnumrow = 3;
		nCarNumDirection = 0;
		memset(carnum,0,sizeof(char)*7);
	}
} car_info;
#endif

class MvVehicleClassify  
{

public:

	MvVehicleClassify();
	~MvVehicleClassify();
		
	/*
	mvTruckDetect�����������ж�
	���룺	
	pImage����Ҫ�����ͼƬ�����ڳ����б�Ϳ�������ϸ���õĲ���ͬһ��ͼƬ���ڴ����ͼƬ��ͬʱ����Ҫ����ROI����
	Brand��������Ϣ
	IsDay������Ϊtrue,ҹ��Ϊfalse
	IsForeCarnum���Ƿ�Ϊǰ�ƣ�Ĭ��Ϊǰ�ƣ�
	IsMoreDetail���Ƿ�Ϊϸ�ֳ��ͣ�Ĭ��Ϊ��
	nMoreDetail��ϸ�ֳ��ͷ���ֵ
	����ֵ
	return����һ����
	nMoreDetail���ڶ����ࣨϸ�ֽ����
	*/
	int mvTruckDetect(const IplImage *pImage,const CARNUM_CONTEXT Brand,bool IsDay=true,
		bool IsForeCarnum=true,bool IsMoreDetail=false,int *nMoreDetail = NULL);

	/*
	mvTruckDetect�����������ж�(�Զ��峵���ṹ��)
	���룺	
	pImage����Ҫ�����ͼƬ�����ڳ����б�Ϳ�������ϸ���õĲ���ͬһ��ͼƬ���ڴ����ͼƬ��ͬʱ����Ҫ����ROI����
	Brand��������Ϣ
	IsDay������Ϊtrue,ҹ��Ϊfalse
	IsForeCarnum���Ƿ�Ϊǰ�ƣ�Ĭ��Ϊǰ�ƣ�
	IsMoreDetail���Ƿ�Ϊϸ�ֳ��ͣ�Ĭ��Ϊ��
	nMoreDetail��ϸ�ֳ��ͷ���ֵ
	����ֵ
	return����һ����
	nMoreDetail���ڶ����ࣨϸ�ֽ����
	*/
	int mvTruckDetect(const IplImage *pImage,const CAR_INFO *carInfo, bool IsDay=true,
		bool IsForeCarnum=true,bool IsMoreDetail=false,int *nMoreDetail = NULL);

	/*
	mvNonCardTruckDetect�����������ж�
	���룺	
	pImage����Ҫ�����ͼƬ�����ڳ����б�Ϳ�������ϸ���õĲ���ͬһ��ͼƬ���ڴ����ͼƬ��ͬʱ����Ҫ����ROI����
	Brand��������Ϣ
	IsDay������Ϊtrue,ҹ��Ϊfalse
	IsForeCarnum���Ƿ�Ϊǰ�ƣ�Ĭ��Ϊǰ�ƣ�
	IsMoreDetail���Ƿ�Ϊϸ�ֳ��ͣ�Ĭ��Ϊ��
	nMoreDetail��ϸ�ֳ��ͷ���ֵ
	����ֵ
	return����һ����
	nMoreDetail���ڶ����ࣨϸ�ֽ����
	*/
	int mvNonCardTruckDetect (const IplImage *pImage, CARNUM_CONTEXT Brand, bool IsDay=true, 
		bool IsMoreDetail=false, int *nMoreDetail = NULL);

	static char* GetVersion();
	
	//����ģ�ͳ�ʼ��·��
	void mvSetPath(char* strPath);

	void Truck_Destroy();

	int Truck_Init(char* strPath = NULL);

private:
	MvVehicleClassifyDetail *mvclsVType;
	
};

#endif
