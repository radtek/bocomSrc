//// ����������Ƶ���ʶ����� V2.0
//// Bocom Intelligent Video Detection & Recognition Software V2.0
//// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
//// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
//// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
////
//#ifndef OPTICAL_FLOW_SIFT_H
//#define OPTICAL_FLOW_SIFT_H
//
//#include <cxcore.h>
//#include "OpticalFlow.h"
//#include <vector>
//#include "sift_descr1.h"
//#include "Calibration.h"
//#include "MvPolygon.h"
////#include "MyCorner.h"
//
//#include "CornerBackgroundModel.h"//�ǵ㱳��ģ��
//
//using namespace std;
//
//class OpticalFlowSift
//{
//public:
//	OpticalFlowSift();
//	~OpticalFlowSift();
//	
//
//	
//	//void      ExtractCornersAndCompDescr(IplImage *pCurFrame, MyCorner** corners, int& cornerSize);
//
//
//	// ���нǵ�ƥ�䣬���ƥ���ϼ�¼��vecFlows���棬����pCurCorners�̳�����ƥ��Ľǵ���ƶ��ԡ�
//	//void      GenerateOpticalFlow(MyCorner* pLastCorners, int nLastCornerSize, MyCorner* pCurCorners, int nCurCornerSize, vector<Flow> &vecFlows);
//
//
//	// 
//
//	
//
//	void      GetOpticalFlowAndGroupBySift(IplImage *pCurFrame, int64 nCurTimestamp, int64 &dt, 
//									 vector<Flow>& flowFiled, int sizeThresh, float lengthThresh,unsigned int uFrameSeq);
//
//	// ��ֵ�˲���������r��������
//	float     static CalcFlowInRegion(vector<Flow> flowField, CvRect r);
//
//
//	// ��ֵ�˲���������r��������
//	float     static CalcFlowInRegion(vector<Flow> flowField, CvRect r, FindTargetElePolice::MyCalibration* pCalib,  CvPoint offset);
//
//
//	//Flow      static CalcFlowInRegion(const vector<Flow> flowField, CvRect r);
//
//	// ������ֵȷ��һЩ�������ٰ��Ƕ���ֵ��ѡ��һ��������Ϊ��Ҫ������
//	bool      static GetMainFlowInRegion(vector<Flow> flowField, CvRect r, Flow &ret);
//
//
//	bool      IsHaveMoveFeaturesInRegion(CvRect r) const;
//
//
//
//	void      GetFlowGroups(vector<CvRect> &groups) const;
//
//	// ������ֵȥ��������û�п��Ƿ���    
//	void      static RemoveNoise(vector<Flow> &flowField);
//
//
//	void      static ClearFlowInRegion(vector<Flow> &flowField, const CvRect &rgn);
//
//
//	//void      static CalcSpeedByFlow
//
//	void      static GroupFlowField(const vector<Flow> &flowField, vector<CvRect> &rect, int sizeThresh, float lengthThresh);
//
//
//	CvPoint2D32f* GetCorners(int &nSize) const;
//	
//	//void      static GetFlowFieldRect(const vector<Flow> &flowField,  vector<CvRect> &rect, int sizeThresh, float lengthThresh);
//private:
//
//	void      GenOpticalFlowGroup(const vector<Flow> &flowField, vector<int> vecEndPointKey, 
//										  vector<CvRect> &rect, int sizeThresh, float lengthThresh);
//
//
//
//	CvPoint2D32f*     m_pLastFrameCorners;
//	int               m_nLastFrameCornerCount;
//	MyDescriptor*     m_pLastFrameDescriptor;
//
//	bool*             m_bCornerHasMoved;
//
//	int64             m_nLastFrameTimestamp;
//
//	vector<Flow>      m_vecFlowFiled;
//
//	vector<CvRect>    m_vecFlowFieldGroup;
//
//
//	CornerBackgroundModel<CvPoint2D32f> *m_pCornerBGM;
//
//
//};
//#endif
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
