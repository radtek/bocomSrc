// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef BC_VEHICLETYPE
#define BC_VEHICLETYPE

#ifdef __cplusplus 
#define EXTERN_C extern "C" 
#else 
#define EXTERN_C 
#endif 

#if defined WIN32 || defined _WIN32 
/* win32 dll export/import directives */ 
#ifdef LIBRARY_EXPORTS 
#define BC_VEHICLETYPE_API //EXTERN_C __declspec(dllexport) 
#else 
#define BC_VEHICLETYPE_API //EXTERN_C __declspec(dllimport) 
#endif 
#else 
/* unix needs nothing */ 
#define BC_VEHICLETYPE_API EXTERN_C 
#endif 

using namespace cv;
using namespace std;

typedef long long bc_handle_v;    //�㷨���

typedef int bc_result_v;      //�������صĴ����������
#define BC_OK (0)             //��������
#define BC_E_IMAGE (-1)       //��ͼƬ
#define BC_E_PLATE (-2)       //�޳���
#define BC_E_RECT (-3)        //�޳���
#define BC_E_HANDLE (-4)      //�������
#define BC_E_FAIL (-5)        //��������

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

/*���ʹ����������ʼ��
handle: ��ʼ���ĳ���ʵ�����
strPath������ģ�ͳ�ʼ��·��
*/
BC_VEHICLETYPE_API bc_result_v bc_Truck_Init( bc_handle_v &handle, char *strPath = NULL );

/*
mvTruckDetect�����������ж�(IplImage*�ӿ�)
���룺
handle: ����ɳ�ʼ���ĳ�������ʵ�����
pImage����Ҫ�����ͼƬ�����ڳ����б�Ϳ�������ϸ���õĲ���ͬһ��ͼƬ���ڴ����ͼƬ��ͬʱ����Ҫ����ROI����
carInfo������ĳ�����Ϣ
IsDay������Ϊtrue,ҹ��Ϊfalse
IsForeCarnum���Ƿ�Ϊǰ�ƣ�Ĭ��Ϊǰ�ƣ�
IsMoreDetail���Ƿ�Ϊϸ�ֳ��ͣ�Ĭ��Ϊ��
nMoreDetail��ϸ�ֳ��ͷ���ֵ,�ڶ����ࣨϸ�ֽ����
nTruck�����ͷ��ص�һ����
*/
BC_VEHICLETYPE_API bc_result_v bc_Truck_Recognition( bc_handle_v handle, IplImage *Image, CAR_INFO *carInfo, 
	bool bIsDay=true, bool bIsForeCarnum=true, bool bIsMoreDetail=false, int *nMoreDetail = NULL, int *nTruck = NULL );

/*
GetVersion����ð汾��
���أ�char Version[] = { "color Recognition Version x.x.x.x" " "  __DATE__ " " __TIME__ };
*/
BC_VEHICLETYPE_API const char* bc_Truck_GetVersion( bc_handle_v handle );

/*�ͷź���*/
BC_VEHICLETYPE_API bc_result_v bc_Truck_Destroy( bc_handle_v &handle );

/*��ȡ������Ϣ*/
BC_VEHICLETYPE_API const char* bc_Truck_GetErrMsg(bc_result_v nErrCode);

//////////////////////////////////////////////////////////////////////////
//����Ϊ���������ӿ�

//����ģ�ͳ�ʼ��·��
BC_VEHICLETYPE_API bc_result_v bc_Truck_SetPath(bc_handle_v handle, char* strPath);

#endif
