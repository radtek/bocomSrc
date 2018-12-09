#ifndef _Mv_CarnumDetect_H_
#define _Mv_CarnumDetect_H_

#pragma once

#include "cv.h"

#ifndef CARNUMPARM
#define CARNUMPARM
//����ʶ�����
typedef struct carnum_parm
{	
	int img_angle;//ͼ����ת�Ƕȣ�Ĭ������0��
	int isday; //1: ����, 0: ���ϣ����ü���ͼƬ������Ƶ�ǰ��컹�����ϡ�
	int direction; //������ǰ�Ż���β�ƣ����Ӧ�ó����޷��ж��������ó�β��ģʽ��//0��ʾǰ��,1 ��ʾ����.
}carnum_parm_t;
#endif

//#define ER_CI_SHI_BIE //����ʶ�𿪹�

#ifndef _CARNUMPARAMETER_H_
#define _CARNUMPARAMETER_H_


//#define CARNUMPARAMETER_DEBUG_PRINTF_PLATELOCATION
#ifndef MAXPLATENUMBERPERPICTURE
#define MAXPLATENUMBERPERPICTURE
#define MAX_PLATE_NUMBER_PERPICTURE 30
#endif


class Mv_Vehicle;

enum carnumdirection{ frontcarnum, backcarnum, unknow };

//�����涨��ĳ�����ɫ
#ifndef CARCARD_COLOR
#define CARCARD_COLOR
enum CARNUM_COLOR
{
	CARNUM_BLUE=1,
	CARNUM_BLACK,
	CARNUM_YELLOW,
	CARNUM_WHITE,
	CARNUM_OTHER
};
#endif

#ifndef CARNUMROW
#define CARNUMROW
enum CARNUM_ROW{ listrow=1, doublerow, other };
#endif

#ifndef CARNUMCONTEXT
#define CARNUMCONTEXT
typedef struct CARNUM_CONTEXT
{
	char    carnum[7];             //���ƺ���

	double	confidence[7];		   //λ���Ŷ�

	CvRect  position;              //����λ��,�����ԭͼ

	CARNUM_COLOR   color;          //������ɫ

	int     vehicle_type;          //��������	

	float	iscarnum;              //��ƥ�������Ƿ��ǳ���

	double     mean;               //��������

	double     stddev;			   //���Ʒ���	

	char    wjcarnum[2];           //�侯���м������С��

	CARNUM_ROW   carnumrow;        //���Ż���˫�ų���

	CvRect    smearrect[20];        //��������λ��

	int       smearnum;				//��Ӧ�ĳ������

	int      VerticalTheta;         //��ֱ��б��,�ԽǶ�Ϊ��λ

	int      HorizontalTheta;       //ˮƽ��б��,�ԽǶ�Ϊ��λ

	carnumdirection     nCarNumDirection;    //���Ƶķ���֪ͨ������ǰ�ƻ���β��

	bool     bIsMotorCycle;          //�Ƿ�ΪĦ�г���


}carnum_context;
#endif

typedef struct ROAD_CONTEXT
{
	double     mean;               //����ƽ������

	double     stddev;				//���򷽲�

	double  carnummean;             //����ƽ������

	double  carnumstddev;           //���Ʒ���

	CvRect    smearrect[20];         //��������λ��

	int       smearnum;				//��������Ŀ

}road_context;

#ifndef CARNUMPARM
#define CARNUMPARM
//����ʶ�����
typedef struct carnum_parm
{	
	int img_angle;//ͼ����ת�Ƕ�
	int isday; //1: day, 0: night
	int direction; //��·����
}carnum_parm_t;
#endif


#ifndef OBJ_TYPE_FOR_OUTPUT
#define OBJ_TYPE_FOR_OUTPUT
enum ObjTypeForOutput
{
	OTHER = 1,     // δ֪
	PERSON,        // ����5
	TWO_WHEEL,     // ���ֳ�
	SMALL,         // С 1
	MIDDLE,        // �� 2
	BIG,           // �� 3
};

#endif

//�Ű���
enum mvCARCOLOR_NUMBER { YELLOW_N, WHITE_N, RED_N, BLACK_N, BLUE_N};

#ifndef NVISE_LIGHT
#define NVISE_LIGHT
enum mvNvise_light{ NORMAL, STRONGNVISE, LIGHTNVISE, LIGHTTOWARDS };//����,ǿ��,����,˳��;
#endif

#ifndef REALLOOP
#define REALLOOP
typedef struct LOOP_PARMARER
{
	CvPoint pStart_point;
	CvPoint pEnd_point;
	int     iNvise_light;
	LOOP_PARMARER()
	{
		pStart_point = cvPoint( 0, 0 );
		pEnd_point = cvPoint( 0, 0 );
		iNvise_light = -1;
	}

}loop_parmarer;
#endif

//struct carnum_context;
#ifndef CARCONTEXT
#define CARCONTEXT
typedef struct CAR_CONTEXT
{
	CvRect position;
	carnum_context* carnum;
	carnumdirection direction;
	double reliability;
	bool haveplate;
	bool isTaxiCar;

}car_context;
#endif

//struct object_context;
#ifndef OBJECTCONTEXT
#define OBJECTCONTEXT
#define object_Info char
enum OBJECT_TYPE
{	VEHICLE_TYPE = 0,       /* = 0 ������     */
    TAXI_VEHICLE,           /* = 1 ���⳵     */
    MOTOR_VEHICLE,          /* = 3 Ħ�г�     */
	AGRICULTURAL_VEHICLE,   /* = 2 ũ�ó�     */
	TRICYCLE,               /* = 4 ���ֳ�     */
	PEDESTRIANER_TYPE,      /* = 5 ����       */	
	OTHRE_0,                /* = 6 ����0      */
	OTHRE_1,                /* = 7 ����1      */
	ERROR_TYPE              /* = 8 ����       */};
typedef struct OBJECT_CONTEXT
{
	CvRect position;
	object_Info* objInfo;
	carnumdirection direction;
	double reliability;
	OBJECT_TYPE objecttype;

}object_context;
#endif

#ifndef  CARNUMCONFIG
#define CARNUMCONFIG
typedef  struct  CARNUM_CONFIG
{
	int  pAlgEnable; 		   //�㷨ʹ��, 0 ��������, 1 ������
	int  pMotorEnable;  	   //0������Ħ����, 1 ����
	int  pTaxiEnable;          //���⳵�ж�ʹ��
	int  pTricycleEnable;      //���ֳ����ʹ��
	int  pPedestrianerEnable;  //���˼��ʹ��
	int  pAgriculturalVehiclePlateEnable;  //ũ�ó�����ʶ��ʹ��

	char sCharForce;        //�ַ�ǿ��
	int  bBackLight;  	//���״̬ 1-���

	int  sSmallRect;  	//�궨С����
	int  sBigRect;    	//�궨����

	CARNUM_CONFIG()
	{
		pAlgEnable = 0;
		pMotorEnable = 0;
		pTaxiEnable = 0;  
		pTricycleEnable = 0;  
		pPedestrianerEnable = 0;  
		pAgriculturalVehiclePlateEnable = 0;  

		sCharForce = '0';        //�ַ�ǿ��
		bBackLight = 0;  

		sSmallRect = 0;  
		sBigRect = 0;  
	}
} CARNUM_Config;

#define SET_PLR_ENABLE	  		    0x001           // �����㷨ʹ��
#define SET_MOTOR_ENABLE			0x002           // ����Ħ����ʹ�� 
#define SET_TAXI_ENABLE				0x004			// ����TAXI���ʹ��
#define SET_NEW_CALIBRATION			0x008           // �������ñ궨
#define SET_CHAR_FORCE				0x010           // ����ǿ���ַ�
#define SET_BACKLIGHTING_OP			0x020			// �Ƿ������ģʽ
#endif


#endif


#ifndef REALLOOP
#define REALLOOP
typedef struct LOOP_PARMARER
{
	CvPoint pStart_point;
	CvPoint pEnd_point;
	int     iNvise_light;
	LOOP_PARMARER()
	{
		pStart_point = cvPoint( 0, 0 );
		pEnd_point = cvPoint( 0, 0 );
		iNvise_light = -1;
	}

}loop_parmarer;
#endif

#ifndef NVISE_LIGHT
#define NVISE_LIGHT
enum mvNvise_light{ NORMAL, STRONGNVISE, LIGHTNVISE, LIGHTTOWARDS };//����,ǿ��,����,˳��;
#endif

using namespace std;

class Mv_PLR_New;
class Mv_NoPlateVehicleDetector;
class Mv_VehicleDetector;

//class _declspec(dllexport) Mv_CarnumDetect
class Mv_CarnumDetect
{
public:
	Mv_CarnumDetect(void);
	~Mv_CarnumDetect(void);

	/*
	mvGet_BoostVision�����ʶ���ֿ�İ汾�ż�ʡ��
	���룺	
	char* strPath:����ʶ���ֿ����ڵ�·��
	���
	cProvince�����ص��ֿ�ʡ�ݣ�Ϊ�ַ�����Ҫ�ַ����ձ������Ӧ��ʡ��
	fVision���汾�š�
	����ֵ
	1:��ʾ�����°汾,�Ǿɵ��ֿ⣬��Ҫ�����ֿ�
	2:��ʾ�����·���ֿⲻ����
	0:��ʾ�ɹ�������ȡֵ�����ֿ��ж�
	*/
	int mvGet_BoostVision(char* strPath, char &cProvince, float &fVision);

	/*
	carnum_init������ʶ��ģ���ʼ��
	���룺	
	char* strPath:����ʶ���ֿ����ڵ�·��
	float homo[3][3]���궨��Ϣ��ͼ����汾��ʹ�ã������ֵ�Ϳ��ԡ�
	nWidth��������ͼ��Ŀ�
	nHeight��������ͼ��ĸ�
	����ֵ
	���޶���
	*/
	int carnum_init(char* strPath, float homo[3][3], int nWidth, int nHeight );

	/*
	mv_SetCarnumHeight��ͼ��Ŀ�͸߼�Ҫ���ĳ��Ƶ�ʵ�ʸ�
	���룺	
	nWidth��������ͼ��Ŀ�
	nHeight��������ͼ��ĸ�
	nCarnumHeight������⳵�Ƶĸ�	
	����ֵ
	���޶���
	*/
	int mv_SetCarnumHeight( int nWidth, int nHeight, int nCarnumHeight );

	/*
	mv_SetPredectCarnumWidth�����ڶ���ʶ������Ч�������������У�Ԥ֪���Ƴ��ƿ�
	���룺	
	small_width�����ƿ�����
	big_width�����ƿ�����
	����ֵ
	0 ��ȷ
	1 �������Ϸ��������޴���70���ҷ�Χ������100 ��
	*/
	int mv_SetPredectCarnumWidth( const int small_width, const int big_width );

	/*
	set_carnum_parm�����ü�����
	���룺	
	carnum_parm_t�����ýṹ��˵��
	*/
	void set_carnum_parm(carnum_parm_t *p);

	void set_carnum_parm(unsigned int m_Config);


	/*
	set_vedio�����ü���Դ�ǵ��ŵ�ͼƬ��������������Ƶ��
	���룺	
	input_type��//1Ϊ��Ƶ��2Ϊͼ��
	*/
	void set_vedio(int input_type);

	/*
	GetSeqandTs������Ƶ���ʱ�����֡�ź�ʱ���
	���룺	
	seq_input��//�����֡��
	ts_input�������ʱ���
	number��ÿ֡�ĳ���ɫ����
	�����
	seq�������֡��
	ts�������ʱ���
	*/
	void GetSeqandTs(unsigned int *seq,int64 *ts, unsigned int seq_input,int64 ts_input, int number );

	/*
	mvSetNonplateDetect�������Ƿ������Ƴ���Ĭ�ϲ����
	���룺	
	bFlag��//ture��⣬false�����
	*/
	void mvSetNonplateDetect( bool bFlag = false );


	/*
	mvSetDoMotorCarCarnum�������Ƿ���Ħ�г��ƣ�Ĭ�����óɲ����
	���룺	
	bFlagDo��//ture��⣬false�����
	*/
	void mvSetDoMotorCarCarnum( bool bFlagDo = false );


	/*
	CalibrationSet�����������ID,����ͼ�����У����֪����ЩͼƬ�������Ǹ����ID����Ѹ������IDҲ���룬���ٳ�ʼ���Ĵ�����
	���룺	
	ID��//�����ID��
	*/
	void CalibrationSet(unsigned int ID);


	/*
	find_carnum������ʶ��ģ�����������
	���룺		
	char *filename�������壬����ΪNULL��
	IplImage *imgsrc����ʶ���ͼ��
	char *ref��δʹ�ã�����ΪNULL��
	IplImage **wb�������壬����ΪNULL��
	CvRect valid_rect�����Ƽ�����򣬼������imgsrc���ĸ�λ�ý��г��Ƽ�⡣���cvrcet=��0,0,0,0��������Ĭ�ϵļ�����򣬱���ͼƬ������ͼ�����80%������Ƶ������ͼ�����35%���򣻸���ͼƬ������ͼƬ��50%����
	int indeinterlace��ͼ��֡����־��֡ͼ��Ϊ1����ͼ��Ϊ2
	carnum_context* vehicle_result������ʶ�������ṹ��ͷ�ļ�˵����
	road_context* road_result��·��ľ�ֵ����Ƚ�����ṹ��ͷ�ļ�˵����
	CvSeq *Indeterminobject�������壬����ΪNULL��
	LOOP_PARMARER loopparemar����Ȧ�ĳ�����ʼλ�ã�ͼ���ϵͳ�У���ʹ�ã�����������뼴��
	����ֵ��
	��ʾʶ����ĳ��Ƹ��������� 0��ʾδʶ������ƣ�1��ʾʶ���1�ţ��Դ����ơ�
	*/
	//����ԭͼ�����������Ҫ������ͳ��Ƽ��
	int find_carnum(char *filename, IplImage *imgsrc, char *ref, IplImage **wb, CvRect valid_rect, int indeinterlace, 
		carnum_context* vehicle_result, road_context* road_result, CvSeq *Indeterminobject, LOOP_PARMARER loopparemar);


	//��Υͣ�õĽӿ�,�����ο�����
	//����ԭͼ�������������賵��ͳ��Ƽ��
	int find_carnum( IplImage *imgsrc, CvRect valid_rect, carnum_context* vehicle_result );

	//�����������ʶ����Ľӿڣ�ֻ�ڸ��������������Ƽ���ʶ��
	//����ԭͼ���ͳ��Ƽ������
	int find_carnum( IplImage *imgsrc, CvRect valid_rect, carnum_context& vehicle_result );


	//��ͼ�졢�羯�����ã��������죬��Ӧ�ö˴���
	//����ԭͼ��������� �Լ� ������Ϣ��VV����ֻ�������Ƽ��
	int find_carnum( IplImage *imgsrc, CvRect valid_rect, carnum_context* vehicle_result, vector<Mv_Vehicle>& VV );


	/* ���Ŀ� 2014.8.11
	adjust_detectarea�� ͨ�����������������
	���룺
	car_rect�� ��ͷλ��
	detectarea�� �ϵļ������
	New_detectarea�� ������ļ������
	����ֵ��
	0��û�н���
	1���н���
	*/
	int adjust_detectarea( CvRect car_rect, CvRect detectarea, CvRect &New_detectarea );


	/* ���Ŀ� 2014.8.9
	get_NonplateCar�� ������Ƴ�����
	���룺
	vector<CAR_CONTEXT>&����ͷ����������
	*/
	int get_NonplateCar( vector<CAR_CONTEXT>& );

	/* ���Ŀ� 2014.8.9
	get_NonplateCar�� ������Ƴ�����
	���룺
	vector<CAR_CONTEXT>&����ͷ����������
	*/
	int get_HaveplateCar( vector<CAR_CONTEXT>& );

	/* ���Ŀ� 2015.3.6
	get_NonplateCar�� ������Ƴ�����
	���룺
	vector<CAR_CONTEXT>&����ͷ����������
	*/
	int get_CarInfo( vector<CAR_CONTEXT>& );

	int get_ObjInfo ( vector<OBJECT_CONTEXT>& );

	/* ���Ŀ� 2015.3.11
	get_VelocpedeInfo�� ������ֳ�����
	���룺
	vector<CAR_CONTEXT>&����ͷ����������
	*/
	int get_VelocpedeInfo( vector<CAR_CONTEXT>& );

	/* ���Ŀ� 2015.3.11
	Enable_Velocpede�� �������ֳ�
	���룺

	*/
	int Enable_Velocpede();

	/* ���Ŀ� 2015.3.11
	Diaable_Velocpede�� �ر����ֳ�
	���룺

	*/
	int Diaable_Velocpede();

	/*
	carnum_quit������ʶ��ģ����ͷź���	
	*/
	int carnum_quit();

	
	
	/*
	GetVersion����ÿ�汾��	
	���أ�static char Version[] = { "Carnum Recognition Version x.x.x.x" " "  __DATE__ " " __TIME__ };
	*/
	static char* GetVersion();


	

private:
	Mv_PLR_New *m_pMv_PLR_New;
	Mv_NoPlateVehicleDetector *m_pVehivleDetect;
	Mv_VehicleDetector *m_pVelocpedeDetect;

	int m_iSmall_Width;
	float m_Rate_Resize;
	bool m_bIsPrePlateWidth;
	bool nFlagNonPlate;
	bool m_bEnableVelocpede;
	CARNUM_CONFIG m_Config;
	vector<CAR_CONTEXT> m_vVehicles;
	vector<CAR_CONTEXT> m_vVelocpede;
	vector<OBJECT_CONTEXT> m_oObjects;

};

#endif