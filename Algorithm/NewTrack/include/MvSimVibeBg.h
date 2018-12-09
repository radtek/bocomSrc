// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef	SIM_VIBEMODEL_H
#define SIM_VIBEMODEL_H

#include "libHeader.h"

class MvSimVibeModel
{
public:
	MvSimVibeModel(void);

	~MvSimVibeModel(void);

	void mvUninitVibeModel(void);
	
	// �������ܣ��õ���ǰ��vibeģ��
	bool mvGetVibeModel(
			IplImage *pCurRgbImg,			//����ĵ�ǰ��ɫͼ��
			const int &nSameColorDist=2,	//��ɫ���Ƶľ�����ֵ
			const float &fSameColorRate=0.1f, //��ɫ���Ƶı�����ֵ
			const int &nBgUpdateFre=16,		//�������������Ƶ��
			const int &nBkPtCntTh=1,	    //��ΪΪ����ʱ���Ƶĵ�����ֵ
			const int &nSampleCnt=5,	    //��������Ŀ
			const int &nNerbor=2,		    //������
			IplImage *pFkMaskImg=NULL       //���ݽ�����ǰ��mask
		);

	// �������ܣ��õ���ǰ��vibeģ�͵�ǰ��
	IplImage *mvGetFkImg4VibeModel(
				IplImage *pCurRgbImg,
				bool bAddFkMask=false );

public:
	IplImage *m_bgrImg; //��ǰ֡��ɫͼ��
	IplImage *m_fkImg;  //��ǰ֡ǰ��ͼ��
	
private:
	void mvInitVibeModelVar( );

	void mvCreateImages(void);

	void mvAllocVariable(const IplImage *pImg, 
		const int &nSameColorDist, const float &fSameColorRate,
		const int &nBgUpdateFre, const int &nBkPtCntTh, 
		const int &nSampleCnt, const int &nNerbor);

	//���γ�ʼ������ģ�͵�m_N����������ͼ��  
	bool mvInitSampleBgImgs(IplImage *img);

	//������ǰ������
	void mvUpdateVibeModel(IplImage *pCurRgbImg, 
		          IplImage *pFkMaskImg=NULL);

	//��ɫͼ��ı���ģ�͸���
	void mvUpdate8uC3VibeModel(IplImage *pBgrImg,
			 IplImage *foreImg, int nBgUpdateFre);

	//�����ɫ����
	inline unsigned short mvEuclidDist_L_Inf(const uchar *pSrcB,
		const uchar *pSrcG, const uchar *pSrcR, const uchar *pOutB,	
		const uchar *POutG, const uchar *pOutR) const;

private:
	//�������ܣ���ɫͼ��ı���ģ�͸���
	void mvUpdateBgSamples(IplImage *pBgrImg, int nBgUpdateFre,
		                   IplImage *pFkMaskImg );
		
	//�������ܣ�����ģ������ȡ��ǰ��ɫͼ����Ӧ��ǰ��ͼ
	void mvGetFkImgFromModel(IplImage *pBgrImg, IplImage *foreImg);


private:
	bool m_bHadInit; //�Ƿ���й���ʼ����

	unsigned short m_nNerborRadius; //����뾶

	short m_BOUND_UP;  //����������Ŀ��Ͻ�
	short m_BOND_DOWN; //����������ı��½�

	IplImage **m_samImgs; //����ģ������ͼ��



	IplImage *m_rndNbrImg;		//����� �����ͼ��
	IplImage *m_rndSampleImg;   //������ �����ͼ��
    IplImage *m_rndUpdateImg;   //�������� �����ͼ��

	CvSize m_imgSize;      
	int m_width, m_height; //������ģͼ����,�߶�
	bool m_bIsResize;      //�Ƿ���Ҫ����

	int m_chnnls;       //��ɫͨ����Ŀ

	int m_nSampleCnt;   //ÿ�����ص���������
	int m_nBgUpdateFre; //�������µ�Ƶ��(����֡һ��)
	int m_nMinN;		//��С�Ļ���

	int   m_nSameColorDist;  //��Ϊ��ɫ���Ƶľ�����ֵ
	float m_fSameColorRate;  //��Ϊ��ɫ���Ƶı�����ֵ

	int m_nRunCount;    //����֡����ͳ��

	CvRNG m_rnd_state; //�����������		
};

#endif
