#ifndef VEHICLEDETECTOR_H_
#define VEHICLEDETECTOR_H_

using namespace std;

struct Target;
class MvMulObjDetect;

enum VehicleClass
{
	VEHICLE = 0,                /* = 0 ������     */
	BICYCLE_VEHICLE ,           /* = 1 �ǻ�����   */
	PEDESTRIANER,               /* = 2 ����       */	
	ERROR_VEHICLE               /* = 3 ����       */
};

#ifndef MV_VEHICLE_
#define MV_VEHICLE_
class Mv_Vehicle
{

public:
	Mv_Vehicle() : m_dConfidece( 0.0 ), m_dPlate_Confidece(0.0), m_dTaxi_Confidece(0.0), m_Plate( -1 ), m_Taxi( -1 )
	{
		memset( &m_Position, 0, sizeof(CvRect) );
		memset( &m_Plate_Position, 0, sizeof(CvRect) );
		memset( &m_Taxi_Position, 0, sizeof(CvRect) );
		m_VehicleClass = VEHICLE;
	}

	CvRect m_Position;			// ����λ��
	double m_dConfidece;		// �������Ŷ�
	int m_Plate;				// -1 δ��⣻0 ���ƣ�1 ����
	CvRect m_Plate_Position;	// ����λ�� ȫ������ ������ڳ���������
	double m_dPlate_Confidece;	// ���ƿ��Ŷ�
	int m_Taxi;				    // ���⳵ -1 δ��⣻0 ���ƣ�1 ����
	CvRect m_Taxi_Position;	    // ���⳵λ�� ȫ������ ������ڳ���������
	double m_dTaxi_Confidece;	// ���⳵���Ŷ�

	VehicleClass m_VehicleClass;//��������ǩ�����2���������޳�����Ϣ

};
#endif

class Mv_VehicleDetector
{

public:

	Mv_VehicleDetector();

	~Mv_VehicleDetector();

	int mvInit( char* );

	int mvUninit();

	virtual int mvDetectVehicle( const IplImage* src, const CvRect detect_area,	vector<Mv_Vehicle>& Vehicle_Result, double thresh, bool bresize = true  );

	//new add
	virtual int mvDetectVehicle(const IplImage* src,vector<Mv_Vehicle>& Vehicle_Result, double* thresh);

	virtual char* mvGetVersion();

protected:

	MvMulObjDetect *m_pVehicleDetector;

	double m_Resize_Rate;

protected:

	// �ϲ�Ŀ�������
	int TargetGroup( vector<Target>& );         

	// �Ƿ������ص�����
	bool isOverLap( const cv::Rect, const cv::Rect );
	
	// �ϲ�Ŀ���
	Target CombinTarget( const Target, const Target );

	// ��ȡ����λ��
	int GetVehicles( const const vector<Target>, vector<Mv_Vehicle>& );


	//new add 
	int GetVehicles( const const const vector<vector<Target> >, vector<Mv_Vehicle>& );

};

class Mv_NoPlateVehicleDetector : public Mv_VehicleDetector
{

public:

	Mv_NoPlateVehicleDetector();

	~Mv_NoPlateVehicleDetector();

	int mvInit( char*, char* );
	int mvInitTaxiDetect( char* );

	//�����³�ʼ���ӿڣ�nDetectClassĬ��Ϊ1�����Ϊ3��Ĭ��ֻ��⳵
	int mvInit( char*,int nDetectClass=1);

	int mvUninit();

	//����������
	int mvDetectNoPlateVehicle( const IplImage* src, const CvRect detect_area, vector<Mv_Vehicle>& Vehicle_Result, double thresh );

	//�������Ƴ�����,�����⣬�������������ԭ����ͬ
	int mvDetectNoPlateVehicle( const IplImage* src, const CvRect detect_area,vector<Mv_Vehicle>& Vehicle_Result, double* thresh,bool bDetectMotoPlate = false );

	//�������Ƴ����ܣ������˳�����Ϣ������������
	int mvDetectNoPlateVehicle( const IplImage* src, const CvRect detect_area, vector<Mv_Vehicle>& Vehicle_Result );

	
	int mvDetectPlate( const IplImage* src, const CvRect detect_area, vector<Mv_Vehicle>&, double thresh );

	int mvDetectPlate( const IplImage* src, Mv_Vehicle&, double thresh );

	int mvDetectPlateSupply( const IplImage* src, const CvRect detect_area, vector<Mv_Vehicle>&, double thresh );

	int mvSetNotTaxiDetect();


protected:

	MvMulObjDetect *m_pPlateDetector;

	MvMulObjDetect *m_pTaxiDetector;

	double m_Vehicle_Resize_Rate;

	bool NeedDetectPlate( const CvRect detect_area,  const Mv_Vehicle _Vehicle );


//Add by ly 2015��6��23��,�����صĺ���
private:

	int nClasses; 

	//new add for multiclass plate detect
	int mvDetectPlates( const IplImage* src, const CvRect detect_area,vector<Mv_Vehicle>&, bool bDetectMotoPlate);

	//Ϊ��ͬ�����ߴ�������
	int mvDetectPlates( const IplImage* src, Mv_Vehicle&, double thresh ,bool bIsMotor=false );

	//�жϳ��⳵
	int mvJudgeTaxi( const IplImage* src, const CvRect detect_area, vector<Mv_Vehicle>&_vVehicles );

};


#endif