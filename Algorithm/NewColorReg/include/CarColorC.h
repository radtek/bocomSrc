// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef BC_COLORRECOGNITION_C
#define BC_COLORRECOGNITION_C

#ifdef __cplusplus 
#define EXTERN_C extern "C" 
#else 
#define EXTERN_C 
#endif 

#if defined WIN32 || defined _WIN32 
/* win32 dll export/import directives */ 
#ifdef LIBRARY_EXPORTS 
#define BC_COLOR_API //EXTERN_C __declspec(dllexport) 
#else 
#define BC_COLOR_API //EXTERN_C __declspec(dllimport) 
#endif 
#else 
/* unix needs nothing */ 
#define BC_COLOR_API EXTERN_C 
#endif 

typedef long long bc_handle_c;    //�㷨���
typedef int bc_result_c;      //�������صĴ����������
#define BC_OK (0)             //��������
#define BC_E_IMAGE (-1)       //��ͼƬ
#define BC_E_PLATE (-2)       //�޳���
#define BC_E_RECT (-3)        //�޳���
#define BC_E_HANDLE (-4)      //�������
#define BC_E_FAIL (-5)        //��������

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef OBJECTCOLOR
#define OBJECTCOLOR
typedef struct OBJECT_COLOR   //��ɫ���ݽṹ��
{
	int  nColor1;       //��ɫ1
	int  nColor2;	    //��ɫ2
	int  nColor3;       //��ɫ3

	int  nWeight1;    //��ɫȨ��1
	int  nWeight2;    //��ɫȨ��2
	int  nWeight3;    //��ɫȨ��3

	float fCLP1;       //��ɫ���Ŷ�
	float fCLP2;       //��ɫ���Ŷ�
	float fCLP3;       //��ɫ���Ŷ�

	OBJECT_COLOR()
	{
		nColor1 = 11;
		nColor2 = 11;
		nColor3 = 11;
		nWeight1 = 0;
		nWeight2 = 0;
		nWeight3 = 0;
		fCLP1 = 0.0;
		fCLP2 = 0.0;
		fCLP3 = 0.0;
	}
} object_color;
#endif

#ifndef BCRECT
#define BCRECT
//ͼ���о�������
struct BCRect
{
	int x;				//����x����
	int y;				//����y����
	int width;			//���ο���
	int height;			//���ο�߶� 
};
inline BCRect bcRect( int x, int y, int width, int height )
{
	BCRect r;
	r.x = x;
	r.y = y;
	r.width = width;
	r.height = height;
	return r;
}
#endif

#ifndef OBJECTCAR
#define OBJECTCAR
typedef struct CAR_INFO   //�������ݽṹ��
{
	BCRect  plate_rect; //����λ��,�����ԭͼ
	BCRect  car_rect; //����λ��,�����ԭͼ
	int plate_color; //������ɫ��1�� 2�� 3�� 4�� 5������
	int carnumrow; //��˫�ƣ�1���� 2˫�� 3������
	int nCarNumDirection; //���Ƶķ���(0ǰ�� 1β�� 2δ֪)
	char carnum[7]; //���ƺ���
	CAR_INFO()
	{
		plate_rect = bcRect(0,0,0,0);
		car_rect = bcRect(0,0,0,0);
		plate_color = 5;
		carnumrow = 3;
		nCarNumDirection = 0;
		memset(carnum,0,sizeof(char)*7);
	}
} car_info;
#endif

/*��ɫ�����������ʼ��
handle: ��ʼ���ĳ�����ɫʵ�����
strPath������ģ�ͳ�ʼ��·��
*/
BC_COLOR_API bc_result_c bc_Color_Init_C( bc_handle_c &handle, char *strPath = NULL );

/*
GetVersion����ð汾��
���أ�char Version[] = { "ColorRecog Version x.x.x.x" " "  __DATE__ " " __TIME__ };
*/
BC_COLOR_API const char* bc_Color_GetVersion_C( bc_handle_c handle );

/*��ɫ�ͷź���*/
BC_COLOR_API bc_result_c bc_Color_Destroy_C( bc_handle_c &handle );

/*��ɫʶ����������char*�ӿڣ�
handle: ����ɳ�ʼ���ĳ�����ɫʵ�����
Image�������ͼ������
nWidth�������ͼ��Ŀ�
nHeight�������ͼ��ĸ�
nChannels����ɫͼ��ͨ��
carInfo������ĳ�����Ϣ
objColor���������ɫ���
isDayBytime��ʹ��Ĭ��ֵ1�����죩
*/
BC_COLOR_API bc_result_c bc_Color_Recognition_C( bc_handle_c handle, const unsigned char *imageData, int nWidth, int nHeight, 
	int nChannels, CAR_INFO *carInfo, OBJECT_COLOR *objColor, int isDayByTime = 1 );

/*��ȡ������Ϣ*/
BC_COLOR_API const char* bc_Color_GetErrMsg_C(bc_result_c nErrCode);

//////////////////////////////////////////////////////////////////////////
//����Ϊ���������ӿ�

/*����ģ�ͳ�ʼ��·��*/
BC_COLOR_API bc_result_c bc_Color_SetPath_C( bc_handle_c handle, char* strPath );

#endif
