// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


/* 
* �ļ����ƣ�MedianBG.h
* ժҪ: ��ֵ������ģ
* �汾: V2.2
* ����: ����
* �������: 2009��8��7��
*/

#ifndef __MEDIANBG2_H
#define __MEDIANBG2_H

#include <cv.h>
#include <highgui.h>

class CMedianBG2
{

public:

	bool m_bGenBackground; // ��֪�ⲿ�����ʼ�����Ƿ�����

	CMedianBG2();
	virtual ~CMedianBG2();

	/* �趨ȡ���� */
	void FillViewRgn(CvPoint pt[4]);	

	/* ���뵱ǰ֡������ǵ�һ֡���ʼ�� */
	void Input(const IplImage *frame);

	/* ��ʼ��������������ֵ�˲���*/
	bool GenBackGround(int frameNum, int sampleRate);

	/* ��ʼ��������ֱ�ӽ���ǰ֡��Ϊ�����������ⲿ������¸Ľ���*/
	bool GenBackGround_Simple();

	/* ���ӵ������µı�����ʼ��������֡���ַ� */
	bool GenBackGround_InterFrameDiff(int frameNum, int sampleRate, int Thd_diff);

	/* �������� */
	void Update(void);

	/* ����ָ��������Ϣ�Ա������и��� */
	void Update_ShortTermBg(const int count, const CvRect * ObjRect, bool updateInRect);

	/* ����ָ��������Ϣ�Ա������и��� */
	void Update_LongTermBg(const int count, const CvRect * ObjRect, bool updateInRect);

	
	IplImage * GetBackground();
	IplImage * GetBackground_LongTrem();

	IplImage * GetForeground();
	IplImage * GetProFg();
	IplImage * GetCurrentFrame();
	IplImage * GetFilteredFg();
	IplImage * GetLastFrame();

	// ��ñ������صı�׼��ֵ
	IplImage * GetPixelSDV();
	
	/* ȥ����Ӱ����ǰ������Ӱ���ظ�ֵΪ(0,0,ShadowValue) */
	void RemoveShadow(int ShadowValue);

	void RemoveShadow(int nShadowValue, IplImage* imgForeground);

	/* ��ȡǰ���е����� */
	bool ExtractObject(int Thd_bgSub, int Thd_RectSize, bool shadowRemove, int *RectNum, CvRect *rects);

	/* ����ȡ��������з��� */
	int CheckObject(CvRect *rects, int rectNum, int Thd_InterDiff, int min_cornerNum);

	/* ���ñ��������ٶȣ���ǰ֡Ȩ�أ�*/
	void SetUpdateWeight(float alpha);

	/* ���ⲿ�����л�ȡǰ��������Ϣ */
	void ObjectRgn(const int count, const CvRect * ObjRect);

	/* ��õ�ǰ֡��� */
	long GetFrameNum();

	/* �����������ǰ��ͼ��ǰ����ͨ��GetForeground()��� */
	bool bgSubtraction( int Thd_bgSub );

	/* ��ȡ����ǵ���Ϣ */
	CvPoint *GetCorners(int *cornerNum);



private:

	CvPoint m_pViewRgn[4];		// ȡ����

	IplImage * m_pMaskImg;		//
	IplImage * m_pBackGround;	//����ģ�ͣ����ڣ�
	IplImage * m_pBackGround_LongTerm; // ���ڱ���ģ��
	IplImage * m_pForeGround;	//ǰ��
	IplImage * m_pFilteredFg;	//���������ǰ��
	IplImage * m_pFrame;			//���ڱ�����ǰ֡
	IplImage * m_pLastFrame;		//


	// ���ڱ�������
	IplImage * m_pNewFgImg;
	IplImage * m_pNewBgImg;
	IplImage * pFgProImg;

	int m_nWidth,m_nHeight;		//���Ϳ�

	long m_nFrames;				//����ͳ�ƽ��յ�����Ƶ֡���������ڳ�ʼ������ǰ���������input()���������ʼֵ��Ϊ-2��

	int m_nMaskPixels;	//mask������Ŀ

	//������ģ����
	int m_nInitFrames;	// �ܹ����ڱ�����ģ��֡��
	int m_nDT;			// ������ʼ���в��õ�֡�ʣ�ÿ��m_nDT֡��
	int m_nBuffLen;     // ����������

	bool m_bObjects; // ǰ�����Ƿ�������
	int m_nObjectsNum; // �ϲ������������
	CvRect* m_pObjRects; // ��������
	
	//��������ϵ��
	float m_fbgalpha;

	//��ģ�����buff
	int *indexj;
	int *indexi;
	int **buffb, **buffg, **buffr;

	// �ǵ����
	int m_nCornerNum;
	CvPoint *m_pCorners;


	int Median(int** buffb, int** buffg, int** buffr, long k, int n);
	int max3(int a, int b, int c);
	int min3(int a, int b, int c);
	float max3f(float a, float b, float c);
	float min3f(float a, float b, float c);
	int minArr(int* dis, int n);
	bool thresholdFg();	
	void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
	bool interROIDiff(CvRect Rect, int Ti_roi);
	bool checkROI(CvRect Rect);
	void setFrame(IplImage *pForeGround);
	void updateBgModel(CvRect Rect);
	void getIntensityChange(int* mdv_b,  int* mdv_g, int* mdv_r);
	bool cornerTest(CvRect Rect, int min_cornerNum);
	

	/* �Զ���ֵ��ͼ�� ����Otsu�� */
	float AutoThersholding(int minvalue, int maxvalue);

};

#endif // 
