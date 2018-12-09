#ifndef IOG_H_
#define IOG_H_

class opencv;

class CIOG 
{
	
public:

	static CIOG* getInstance(void);					// ��̬sʵ��������
	static void deleteInstance(void);				// ��̬�ͷŶ���

	int m_Width;
	int m_Height;

	IplImage* m_pGray;								// BGRתGRAY�ĻҶ�ͼ��
	CvMat* m_pGrayMat;								// �Ҷ�Mat	
	CvMat* m_pKxMat;								// x�����ݶ��˲���
	CvMat* m_pKyMat;								// y�����ݶ��˲���

	
	int init();										// ��ʼ���ڴ����
	int getIOG(IplImage* img, CvMat* x, CvMat* y);	// ����x,y�����ݶȣ�����img ������ ��x,y�������
	int clean();									// �ͷ��ڴ�

private:
	CIOG();
	~CIOG();

	CIOG (const CIOG&) {}

	static CIOG* m_ciog;							// ���ڶ���

};


#endif

