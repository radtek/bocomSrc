#ifndef DSIFT_H_
#define DSIFT_H_

class opencv;

class CDSIFT
{

public:
	CDSIFT();
	~CDSIFT();

	int m_ScrWidth;					// ����ͼ��/ɨ���ͼ��
	int m_ScrHeight;				// ����ͼ��/ɨ���ͼ��
	int m_GridWidth;				// �����
	int m_GridHeight;				// �����
	int m_gridstep;					// ���񲽳�
	int m_PatchSize;				// Patch�߶�

	CvMat* m_grad_x;				// x�����ݶ�
	CvMat* m_grad_y;				// y�����ݶ�
	CvMat* m_DSIFT_Mat;				// ����Mat
	CvMat* m_Kernal;				// Ȩֵ��
	CvMat* ydest;					// �Ƕ�x��Ȩ
	CvMat* xdest;					// �Ƕ�y��Ȩ
	CvMat** m_EeightOrient_Mat;		// �˷����ݶ�

	
	/*
	�������ܣ�ͨ�������ʼ����m_DSIFT_Mat ��ĳ�Ա������
	���룺һ��ͼ����ÿ�����ص�x������ݶȾ���grad_x,
	     ��y������ݶȾ���grad_y, �Լ����񲽳�gridstep.
	������ޡ�
	����ֵ��0��ʾ�� ������
			-1��ʾ�� �����������
	*/
	int init(CvMat* grad_x, CvMat* grad_y, int gridstep);

	/*
	�������ܣ����ͼƬ����������
	���룺��
	�����������
	����ֵ��0
	*/
	int getGrid(int& GridWidt, int& GridHeight); // 0, 0, 0, 0, 0.125, 0.375, 0.625, 0.875

	/*
	�������ܣ�DSIFT������ȡAPI
	���룺��
	�����DSIFT����Mat
	����ֵ��0��ʾ�� ������ȡ����
			-1��ʾ������������� 
	*/
	int getDSIFT(CvMat* DSIFT_Mat);

	/*
	�������ܣ�����m_DSIFT_Mat���鵽������ļ����С�
	���룺�ļ���filename.
	������ޡ�
	����ֵ��-2��ʾ������Ĳ���Ϊ�ա�
			-1��ʾ���ļ����ܴ򿪡�
			0��ʾ��Ҫ����ĳ�Ա����m_DSIFT_MatΪ�ա�
			1��ʾ���洢�ɹ���
	*/
	int save(char* dir);

	/*
	�������ܣ��ͷ�init�п��ٵ��ڴ档
	���룺�ޡ�
	������ޡ�
	����ֵ�������塣
	*/
	int clean();

	/*
	�������ܣ�����ѷ����ݶȴ�С��
	���룺��
	������ޡ�
	����ֵ��-1��ʾ���ݶ�ͼΪ��
			0��ʾ������ɹ�
	*/
	int getEeightOrientation();

	/*
	�������ܣ������ݶ�����Ȩֵ
	���룺��
	�������
	����ֵ��0��ʾ��Ȩֵ�������
			1��ʾ���˷���ͼ��Ϊ��

	*/
	int calculateWeight();

	/*
	�������ܣ���һ��
	���룺��
	�������
	����ֵ��0��ʾ����һ�����

	*/
	int Normalization();


};


#endif