// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef BC_SEATBELTCLASSIFY
#define BC_SEATBELTCLASSIFY

#ifdef __cplusplus 
#define EXTERN_C extern "C" 
#else 
#define EXTERN_C 
#endif 

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined WIN32 || defined _WIN32 
/* win32 dll export/import directives */ 
#ifdef LIBRARY_EXPORTS 
#define BC_SEATBELTCLASSIFY_API //EXTERN_C __declspec(dllexport) 
#else 
#define BC_SEATBELTCLASSIFY_API //EXTERN_C __declspec(dllimport) 
#endif 
#else 
/* unix needs nothing */ 
#define BC_SEATBELTCLASSIFY_API EXTERN_C 
#endif 

using namespace cv;
using namespace std;

typedef long long bc_handle_s;    //�㷨���

typedef int bc_result_s;      //�������صĴ����������
#define BC_OK (0)             //��������
#define BC_E_IMAGE (-1)       //��ͼƬ
#define BC_E_PLATE (-2)       //�޳���
#define BC_E_RECT (-3)        //�޳���
#define BC_E_HANDLE (-4)      //�������
#define BC_E_FAIL (-5)        //��������
#define BC_E_DIRECTION (-6)   //ǰβ�ƴ���

#ifndef OBJECTFACERT
#define OBJECTFACERT
typedef struct stFaceRt
{
	cv::Rect VehicleRect;		//��ʻԱ����
	double Weight;			//��ʻԱ���Ŷ�
	int label_type;			//��ȫ���ж�
	float fCLP;				//��ȫ�����Ŷ�
	float fblur;			//ͼ��ģ����
	int nPhone_type;		//�ֻ��ж�
	float fPhone_CLP;		//�ֻ����Ŷ�
	int nSunVisor_type;		//�������ж�
	float fSunVisor_CLP;	//��������Ŷ�
	bool bguess;			

	stFaceRt()
	{
		VehicleRect = cv::Rect(0,0,0,0);
		Weight = 0.0;
		label_type = 0;
		fCLP = 0.0;
		fblur = 0.0;
		nPhone_type = 0;
		fPhone_CLP = 0.0;
		nSunVisor_type = 0;
		fSunVisor_CLP = 0.0;
		bguess = false;
	}
}FaceRt;
#endif


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

/*��ȫ�������������ʼ��
handle: ��ʼ���İ�ȫ��ʵ�����
char *strPath������ģ�ͳ�ʼ��·��
*/
BC_SEATBELTCLASSIFY_API bc_result_s bc_Seatbelt_Init( bc_handle_s &handle, char *strPath = NULL );

/*
mvSafetyBelt����ʻԱ��ȫ�����(IplImage *�ӿ�)
���룺
handle: ����ɳ�ʼ���İ�ȫ��ʵ�����
pImage����Ҫ�����ͼƬ��
carInfo������ĳ�����Ϣ
isDayByTime������Ϊ1,ҹ��Ϊ0
vecP����ʻԱ���ݽṹ��
bIsSafetyBelt���Ƿ�������ʻԱ��ȫ��
ncartype��������Ϣ
bIsAideBelt���Ƿ��⸱��ʻԱ��ȫ��
bIsPhone���Ƿ�������ʻԱ���ֻ�
bIsSunVisor���Ƿ�������ʻ������
����ֵ
return���������صĴ����������
*/
BC_SEATBELTCLASSIFY_API bc_result_s bc_Seatbelt_Recognition(bc_handle_s handle, IplImage *Image,
	CAR_INFO *carInfo,int isDayByTime, vector<FaceRt> &vecP, bool bIsSafetyBelt,
	int ncartype, bool bIsAideBelt = false,	bool bIsPhone = false, bool bIsSunVisor = false);

/*
GetVersion����ð汾��
���أ�char Version[] = { "Seatbelt Version x.x.x.x" " "  __DATE__ " " __TIME__ };
*/
BC_SEATBELTCLASSIFY_API const char* bc_Seatbelt_GetVersion( bc_handle_s handle );

/*��ɫ�ͷź���*/
BC_SEATBELTCLASSIFY_API bc_result_s bc_Seatbelt_Destroy( bc_handle_s &handle );

/*��ȡ������Ϣ*/
BC_SEATBELTCLASSIFY_API const char* bc_Seatbelt_GetErrMsg(bc_result_s nErrCode);

//////////////////////////////////////////////////////////////////////////
//����Ϊ���������ӿ�

//����ģ�ͳ�ʼ��·��
BC_SEATBELTCLASSIFY_API bc_result_s bc_Seatbelt_SetPath(bc_handle_s handle, char* strPath);

#endif
