#ifndef _MVPLR_NEW_H_
#define _MVPLR_NEW_H_

#include "Interface.h"
#include "Mv_CarnumDetect.h"

//using namespace caffe;

#define DEBUG
//#define ZRG_DEBUG

#ifdef DEBUG
//#define TIME_START
//#define SAVE_RESULT 
//#define SAVE_FAKE_PLATE
//#define SAVE_SAMPLE //��������
//#define MVPLR_NEW_SAVEIMAGE
//#define MVPLR_NEW_SHOWIMAGE
//#define PLATELOCATIONOLDMETHOD_DEBUG //�Ϸ������ƶ�λ�㷨����
//#define LIUYANG_SHOW_CARandPLATE
//#define PRINTF_DETECT_AND_KEYPOINT
//#define DEBUG_SHOW_FINAL_RESULT
#endif

#ifdef TIME_START
#define TIME_COUNT
#ifndef TIME_COUNT
#define TIME_ALL_COUNT
#endif
#endif

#define CHANGE_O_T_D //ǿ�Ƹı�'O'��'D'

enum plate_colors { blue, yellow, army, police, white, unknown, wj, yue, sg, ling, falsecolor };

static char charLabels[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','1', 'J',
	'K', 'L', 'M', 'N','0', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z','-','+','#','$',
	'2', '3','4', '5', '6', '7', '8', '9' 
};

static char charLabels_cn[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v',
	'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E'
};

#ifdef CHANGE_O_T_D
static char charLabels_letter[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J',
	'K', 'L', 'M', 'N', 'D','P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z'
};
#else
static char charLabels_letter[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J',
	'K', 'L', 'M', 'N', 'O','P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z'
};
#endif

typedef struct MV_PLATEINFO
{
	char    carnum[7];             //���ƺ���

	double	confidence[7];		   //λ���Ŷ�

	CvRect  position;              //����λ��,�����ԭͼ

	plate_colors   color;                 //������ɫ

	int     vehicle_type;          //��������	

	float	iscarnum;              //��ƥ�������Ƿ��ǳ���

	double     mean;               //��������

	double     stddev;				//���Ʒ���	

	char    wjcarnum[2];           //�侯���м������С��

	int     carnumrow;             //���Ż���˫�ų���

	CvRect    smearrect[20];         //��������λ��

	int       smearnum;				//��������Ŀ

	int      VerticalTheta;          //��ֱ��б��,�ԽǶ�Ϊ��λ

	int      HorizontalTheta;          //ˮƽ��б��,�ԽǶ�Ϊ��λ

	int      nCarNumDirection;         //���Ƶķ���֪ͨ������ǰ�ƻ���β��

	bool     bIsMotorCycle;          //�Ƿ�ΪĦ�г���

}MvPlateinfo;

class Mv_VehicleDetector;
class Mv_NoPlateVehicleDetector;
//class licensePlateLoc;
class ConvNet;
class Mv_Vehicle;
class MVPLR_Memory;


class Mv_PLR_New
{
public:
	Mv_PLR_New();
	~Mv_PLR_New();

	int mv_Init( char* strPath );
	int mv_UnInit();
	//int mv_PLRmain(  IplImage* InImg, CvRect detectRect,vector<MvPlateinfo> &PLR_result);
	//int mv_PLRmain(  IplImage* InImg, Mv_Vehicle *VehicleDet,int VehicleNum,vector<MvPlateinfo> &PLR_result );
	//int mv_PLRmain(  IplImage* InImg, CvRect *PlateRect,int PlateNum,vector<MvPlateinfo> &PLR_result);
	int mv_PLRmain(  IplImage* InImg, CvRect detectRect,vector<carnum_context> &PLR_result);
	int mv_PLRmain(  IplImage* InImg, Mv_Vehicle *VehicleDet,int VehicleNum,vector<carnum_context> &PLR_result );
	int mv_PLRmain(  IplImage* InImg, CvRect *PlateRect,int PlateNum,vector<carnum_context> &PLR_result);

private:
	//int mv_PLR_Recognition( IplImage*, CvRect*, int, MvPlateinfo& );
	int mv_PLR_Recognition( IplImage*, CvRect*, int, carnum_context& );
	int mv_PLR_Judge( carnum_context& PLRresult );

	// ����ע��DL����
	void initializeDL();
	void initializeDL_letter();
	void initializeDL_cn();

	IplImage *pCovnetImage;
	int nImgSize;
	// CNN�������


	// ���ֺ���ĸDL������
	ConvNet* mv_DbnRec;	
	CvMat* convetdst;

	// ��ĸDL������
	ConvNet* mv_DbnRec_letter;	
	CvMat* convetdst_letter;
	
	// ����DL����������
	ConvNet* mv_DbnRec_cn;
	CvMat* convetdst_cn;


	Mv_NoPlateVehicleDetector* mv_detector;
	licensePlateLoc/*<float>*/ pll;
	//MVPLR_Memory *pLocMemory;
};

#endif