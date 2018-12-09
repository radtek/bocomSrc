// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary


#ifndef CARDETECT_H
#define CARDETECT_H

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "ipp.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include "VideoShutter.h"
#include "MvLine.h"
#include "MvUtility.h"
#include "cal_main.h"

#define  TRACK


#ifdef TRACK
#include "CSiftTrack.h"
#include "Corner.h"

//#define TRACK_SHOW
//#define IMGSUB              //�۲�Ŀ��ǰ���˶�-��Էǻ�����
//#define TRACK_TIME 

#endif





using namespace std;

#ifdef TRACK
using namespace Shut_Corner;
using namespace Shut_Track;
#endif

#define  MAXCHALNUM 10



         

class mvvideoshutter
{

public:

	mvvideoshutter();

	~mvvideoshutter();

	//VideoRect:����������
	//nWidth:����������������Ŀ�
	//nHeight:����������������ĸ�
	//vector<mvvideorgnstru> mChannelReg ��������
	bool mv_Init( CvRect VideoRect, int nWidth, int nHeight, vector<mvvideorgnstru> &mChannelReg,
		int nImgWidth,int nImgHight, int ncount,float *ptImage_cord, float *ptWorld_cord );

	//pOriImage:ԭʼͼ��,ΪBGR��ʽ
	//ts:ͼƬʱ��� ��λ��ms

	//���Ƽ������庯����main��
	bool mv_DetectEveryFrame( IplImage *pImage,long long FramTime,bool bIsDay = false);

	//vResult��������
	bool mv_GetVideoResult( vector<skip_video_out_result> &vResult);

	//���ͷź���
	bool mv_UnInit();

private:

	//Ѱ�ҳ���������������ཻ��
	void  MvInTerSerctLine();

	//�жϵ��Ƿ��ڶ����������
	bool mv_is_point_in_polygon(const mvvideorgnstru &Chanlpos,const CvPoint2D32f pt);

	//otsu��ֵ
	unsigned int mvgetotsuthershold(const IplImage *simg, const unsigned int nWidSample,const unsigned int nHigSample );

	//������ֵ
	int mvInteratonThershold( const IplImage *pImg, int nWidSample,int nHigSample);


	//ֱ��ͼƽ����
	void mvHistogSmooth( int *Grayhist, int histNum,int teringNum);


	//��ȡ����ҶȻ�
	void mvDetcAreaImgGray(IplImage *pImage);

	void mvGrayImgMorTop(const IplImage *pGrayImage,IplImage *pHatImage);

	//���˺���
	bool mvCarRectTell ( IplImage* GrayImage,const  CvRect CarRect ,bool bKmean = false);

	//�Ҷ��ݶȺ���
	bool mvGraySub (const IplImage* pGrayImg,int &nHigEnd);

	//sobel����
	bool mvGetSobelImage( const IplImage *pImage,int &ImgCarHigStart,int &ImgCarHigEnd);

	//Ѱ�Ҳ��岨�Ⱥ���
	bool mvSeekPeakVallegPos(const int *Grayhist, int histNum,int *PeekPos, int *valPos);

	//�Թ��˺���ھӳ���������б��
	void mvCombineCarRect(vector <CvRect> CarRec, int *pCarLab,const int pCarInital);

	//��ȡ���ճ���
	void mvFinalCarDerive(const vector <rect_lig> &Rec , vector <rect_lig> &CarRec);

	//����ͬһʱ��ĳ������ֻ������һ������
	void mvControlOneCarInChal(vector <rect_lig> &DstCarRec);

	//���Ƴ��Ƽ�����һ�����
	void mvControlCarDis(vector <rect_lig> &DstCarRec);

	//��ӵ�ǰ���Ƶ�ʱ����Ϣ�洢��m_CarnowInf��
	void mvAddCarTime(const vector <rect_lig> &Rec);

	//�ѵ�ǰ��⵽�ĳ�����Ϣ���뵽������
     void InserCarToChain();

    //��Գ������,������ʱ�̳��ƽڵ㸳�ϳ��Ƹ���ʱ����Ϣ
	int mvCalUpdaTime(const skip_carnum_result *pElem ,int &nForCarAvg,int nFrstAvg, CvRect FirstCarRect,int CarSpeed);
    
	//�ж��Ƿ�ΪҹĻ��ͼ������ơ������ⶼ�ܺڣ�
	void mvGetImgDark(const IplImage* pGrayImg);

	//ǰ�����������ȱȽϵĹ���
	void mvCarLigComp(const IplImage* pGrayImg,vector <rect_lig> &DstCarRec);

	//���㳵��
	void mvGetCarSpeed(const skip_carnum_result *pElem,int &Speed);

    //�Ҷ��ݶ���ֵ����
	bool mvGrayThred(const IplImage* pGrayImg,int &nHigEnd);

	bool MvBocPix(const IplImage* pGrayImg);

	//���Ƽ��
	bool mvGetLight(const IplImage *pGrayImage);

	//ǰ����ȡ�˶�Ŀ��*******************************************
	void mvGetObjForSub(const IplImage *pForImage, const vector <rect_lig> &CarPlat,bool bChange = false);


	//��ȡ�˶�Ŀ��
	void MvGetMovObj(const vector<Peekinf> &Peek,int *nProjX,vector <MovObj> &Obj);

	//�������ص��Ľ��кα�
	void MvFilObjByPlate(vector <MovObj> &Obj);

	//�������ص��Ľ��кα�
	void MvComBinObj(vector <MovObj> &Obj);

	//ͨ�����ƣ���������Ŀ��״̬
	void  MvSetObjSta(vector <MovObj> &Obj,const vector <rect_lig> &CarPlat);

	//���³��ƹ�����Ϣ
	void  MvCarFilUpdat(const vector <rect_lig> &CarPlat);

	//����ǰ��
	void  MvUpdatMovObj(const vector <MovObj> &Obj);


	 void MvUpdatMovObjChain(const MovObj *Obj);

	 //
	 void  MvReslByMove(vector<skip_video_out_result> &vResult);

	//Բ����ϼ��
	void MvLightDetct(IplImage *image ,CvSeq* result_seq,CvSeq *CriclArr,vector<CvRect> BriArea,
		const vector<circle_attribution> &CirByBig,int nXZoom = 1, int nYZoom =1);


	//�Ƶ�ͼ���������ӱ�ǩ
	void mvChagLigToWorldPos(CvSeq *CriclArr,vector<ligworld_inf>&CirlWoldpos);

	//�ҳ�����ƥ�����
	void mvFindLigMatchNum(vector<ligworld_inf>CirlWoldpos,vector<ligmatch_inf> &Ligmatch);

	//ƥ��ƵĻҶȾ���
	int mvLigGraySub(const IplImage*pGrayImage,CvRect Ligrect, CvRect MatLigRec);

	//ƥ��Ƶ�ǰ���ҶȾ�ֵ
	int mvLigUpGray(const IplImage*pGrayImage,CvRect Ligrect);

	//�ǻ������ж�
	bool mvJueSigLig( IplImage*pGrayImage,CvRect Ligrect);

	//�жϳ����Ƿ���һ������
	void mvDeriveSigLigInChal(CvSeq *CriclArr,uchar *nMachLig,vector <int>&nSigLig);
    
	//���Ʊ���
	bool mvShutContol( int &nFirstAvg,bool &IsFirstSet,int i,bool IsCausedByLig, skip_carnum_result *pElem,int Graysub,vector<skip_video_out_result> &vResult);


	//���Ƽ������庯����main��
	void mv_LocatPlat( IplImage *pImage,const CvRect Carplat, vector <CvPoint> &CarLineOut);

	//
	bool mvKmean(const IplImage *pImage,int nHigEnd);

	bool mvPlateByKmean(IplImage *pImage);

	bool mvGetSlope(const IplImage *TrdImg);
	
	//�ж����Ƶĳ�����Ϣ
	void mvJudgeChanl(skip_carnum_result *pElem);

	//CarRect���꣺���ԭʼ---�������---����
	ChanlData mvJudgeChanlByRec(CvRect CarRect);

	//���---����---�ҳ�����ɵ�·��ǰ������
	void   mvGetChanlCasByRoad(vector<CvRect> &RecByRoad) ;

	void   MvFilObjByRoadChanlLig(vector <MovObj> &Obj);

#ifdef TRACK
	//��ȡ�켣�ṩ���˶�
	void  MvAddShurObjByTrack(const vector <MovObj> &Obj);
#endif
	

	//ͨ�����ȿ�Ѱ�ҳ���
	void MvLightByRec( vector<CvRect> &BigRec,vector<circle_attribution> &CirByBig,int nRidusTrd);

	static bool IsYHig(const CvRect &r1, const CvRect &r2);
	
	void mvFilCarLin(vector<CvPoint> &CarOuLine,const CvRect &Carplat);

    void mvSegRectUnit(vector <CvRect> &SegRect,int nDisTrd);
	
	bool mvRemoPlaByRoadLig(CvRect CarRec);

	bool MeetNOVehicShut(int nMovDis);
      



private:

#ifdef TRACK
      CsiftTrack m_SifTrack;
	  Corner     m_Corner;
#endif

	vector<Line_inf> m_IntesecLine; //��Ӧ��ѹ����m_ShrinkGrayimage��������ȥ��
	vector<car_filarea> m_CarFile;
	bool m_bSaveImg;
	bool m_bSavPtintTime;
	bool m_bShutOut;
	IplImage *m_Grayimage;
	IplImage *m_ShrinkGrayimage;
	IplImage *m_SwapImg;
	IplImage *m_LastImg;
 
	// �궨���
	//MyCalibration_New m_calibration;
	cal  m_calibration;
	vector <int> m_LigColum;

	CvRect m_VideoRect;
	int m_nWidth;
	int m_nHeight;
	int m_detareYmov;
	int m_carintegralHig;
	int m_detareXmov;
	int m_carintegralWid;
	
	vector<mvvideorgnstru> m_ChannelReg;
	//vector<int> m_LigColum;
	int64 m_nFramSeq;

	IplImage *m_pMaskImg;
	IplConvKernel *m_kernel5x5;	
	IplImage *m_tempimage;
	IplImage *m_pForImg;

	


	CvMemStorage* m_storage;
	CvMemStorage* m_Movstorage;
    CvSet   *m_MovResu;

	CvSet   *m_CarNumResu;
	vector<car_current_inf> m_CarnowInf;
	int64 m_FramTime;
	int m_IsWhite;
	bool m_Dark; //�����Ƿ�

	bool m__IsInitSucs;
	
	bool m_IsImgDark; //ͼ���Ƿ��ں�ҹ
	vector<rect_lig> m_LigResRect;
	vector<CvRect>  m_LigByRoad;
	CvRect m_LigRect;
	int64 m_HiShut[MAXCHALNUM];
	unsigned int *m_BusPass;
	int *m_HiShutIndex;
    mvPark m_ChanlPark[MAXCHALNUM];
	int m_CarAvg;
	int m_nLigRiX;
	int m_nLigRiY;
	bool m_bNoObj;
	uchar m_DetAreAvg;
	vector <ChanlFil> m_FilChanl;
	ChanlVeh m_ChanVel[MAXCHALNUM];
	CarHit m_CarHit[MAXCHALNUM];
	public:
	vector<skip_video_out_result> m_AddResult;
	


protected:

};

#endif

