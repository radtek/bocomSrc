// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/************************************************************************/
/* ������                                                               */
/************************************************************************/

#ifndef MEDIANBG_WRAPPER_H
#define MEDIANBG_WRAPPER_H

#include "IBackgroundModel.h"
#include "MedianBG.h"

class MedianBGWrapper: public IBackgroundModel
{
public:
    MedianBGWrapper();
	virtual ~MedianBGWrapper();

	virtual  bool IsInitialized();
	virtual  void Init(IplImage *img);
	virtual  void Update(IplImage *img, int count, const CvRect * ObjRect, bool updateInRect);
	virtual  void Update(IplImage* img , IplImage* mask);

	virtual  void GetBackground(IplImage **background);
	virtual  void GetForeGround(IplImage *frame, IplImage **foreground);
	//virtual  void RemoveShadows();
	
	virtual  void Invalidate();
	virtual  void SetObjectRgn(const int count, const CvRect * ObjRect);

	virtual  bool IsReGenBackground();
	virtual  bool ReGenBackground(IplImage *img);
	virtual  void SetUpdateWeight(double weight);
private:
	CMedianBG2 *_bgm;
	bool m_bIsBufferCreated;
	int  m_nReGenBackgroundTimeLeft;
};

#endif
