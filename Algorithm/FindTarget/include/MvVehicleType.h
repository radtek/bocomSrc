/*
 *��Ĺ��ܣ�ʵ�ֳ���ϸ�֣���͡�����ֿ�����Ҫ����ֱ�ߣ�
 */
#ifndef MV_VEHICLE_TYPE
#define MV_VEHICLE_TYPE

#include <string>
#include <vector>

#include "MvLine.h"
#include "MvLineStorage.h"
#include "MvLineMerge.h"
#include "Car.h"

#include "Calibration.h"
#include "functions.h"
#include "MvBgLine.h"

//#include "MvFindTargetByVirtualLoop.h"

using namespace std;
using namespace PRJ_NAMESPACE_NAME;

typedef struct _CarWindow
{
	MvLine *pUpperHorLine;
	MvLine *pLowerHorLine;
	MvLine *pLeftSkewLine;
	MvLine *pRightSkewLine;

	_CarWindow()
	{
		pUpperHorLine = NULL;
		pLowerHorLine = NULL;
		pLeftSkewLine = NULL;
		pRightSkewLine = NULL;
	}

	//_CarWindow(const _CarWindow &cw)
	//{
	//	pUpperHorLine = NULL;
	//	pUpperHorLine = NULL;
	//	pLeftSkewLine = NULL;
	//	pLeftSkewLine = NULL;
	//}


}CarWindow;

class MvVehicleType
{
public:
	typedef struct _CarPlateInfo
	{
		Car    *pCar;
		CvRect rectPos;  //����λ��!
		int    nDirection;  //��ʻ����0��ǰ�ƣ�1��β�ƣ�
		int    nColor;  //������ɫ��
		std::string strCarNum;  //���ƺ��룡

		_CarPlateInfo();

		_CarPlateInfo(Car *car, CvRect pos, int  direction, int  color, string carNum):pCar(car),rectPos(pos),nDirection(direction),nColor(color),strCarNum(carNum){};
	}CarPlateInfo;
	
public:
	MvVehicleType(void);
	~MvVehicleType(void);
	static int  GetVehicleType( IplImage *img, MyCalibration *pCalib, CarPlateInfo carPlateInfo, int objMotionAngle, MvBgLine *pLineBGM, \
								unsigned int frame, MvLineStorage *pLineStorage, MvLineMerge *pLineMerge);    //return��0x00000080��������0x00000100���ͳ���
	static void JudgeBusOrVan(IplImage *img, CvRect region, MvLine *pLines, int nLineCount, MvLine *pBgLinesForVehType, int nBgLineCount, unsigned int uFrameSeq, Car *pCar, int nCarColor, std::string strCarNum, float objMotionDirection, CvRect rectCarPlatePos, int &nVehicleType);
	static int IsBus(IplImage *img, Car *pCar, MvLine *pLines, int nLineCount, MvLine *pBgLines, int nBgLineCount, MvLine **pRetUpperHorLine, MvLine**pRetLowerHorLine, MvLine**pRetLeftSkewLine, MvLine**pRetRightSkewLine, \
						CvRect &window, CvRect &topOfWind, CvRect &bottomOfWind, HslQuad &windMeanHSL, HslQuad &topMeanHSL, HslQuad &bottomMeanHSL, int &nHaveWind, int &nHaveThreeBranch, int &nHavePartWindow,  int &nWhich, float objMotionDirection, CvRect rectCarPlatePos);
	static bool IsGot_TwoWindow(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine**pRetLowerHorLine, MvLine**pRetLeftSkewLine, MvLine**pRetRightSkewLine, float fHorLineLenThr, float objMotionDirection, CvRect platePos);
	static bool IsGot_VerLines_OnCarPlate(MvLine *pLines, int nLineCount, CvRect rectCarPlatePos);
	static bool IsGot_3LineWindow_1(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, float objMotionDirection, CvRect rectCarPlatePos, vector<CarWindow> vecWind1, bool bRealCar);
	static bool IsGot_3LineWindow_2(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, float objMotionDirection, CvRect rectCarPlatePos, vector<CarWindow> vecWind2);
	static bool IsGot_3LineWindow_3(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, float objMotionDirection, CvRect rectCarPlatePos, vector<CarWindow> vecWind3);
	static bool IsGot_3LineWindow_4(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, float objMotionDirection, CvRect rectCarPlatePos, vector<CarWindow> vecWind4, bool bRealCar);
	static bool IsGot_3LineWindow(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, int &nWhich, float objMotionDirection, CvRect rectCarPlatePos, vector< vector<CarWindow> > vec3LineWind, bool bRealCar);
	static bool IsGot_BUS_BackWindow(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, bool bIsRealCar, vector<CarWindow> vecCarWindow, float objMotionDirection, CvRect rectCarPlatePos);
	static bool IsGot_Three_Branch(MvLine *pLines, int nLineCount, MvLine **pRetUpperHorLine, MvLine **pRetLowerHorLine, MvLine **pRetLeftSkewLine, MvLine **pRetRightSkewLine, float fHorLenThr, bool &bLeft, float objMotionDirection, vector<CarWindow> vec3Branch);
	static bool IsWindByColor(IplImage *img, CvRect rectWind, CvRect &window, CvRect &topOfWind, CvRect &bottomOfWind, HslQuad &windMeanHSL, HslQuad &topMeanHSL, HslQuad &bottomMeanHSL);
	static CvPoint ExpandXScale(const MyCalibration *pCalib, CvPoint pt, float expandWid);  //����ָ�����X����
	static CvPoint ExpandYScale(const MyCalibration *pCalib, CvPoint pt, float expandLen);  //����ָ������Y����
	//�в�����ʱ����һ���ǲ��ǡ��񡱴����
	static bool IsTruckByBackLines(MvLine *pLines, int nLineCount, float objMotionDirection);

	// Ŀ�ģ�����ֱ�߽�ͼ�����ߴ��϶��ǻ������ĳ������˵����ù�����Ҫһ�����ص�
	// �жϳ��͵ĺ������������
	static bool IsSideMotorizedVehicle(MvLine* pLines, int nCount, CvSize imgSize);
};

#endif
