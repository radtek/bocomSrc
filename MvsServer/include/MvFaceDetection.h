#ifndef MV_FACE_DETECTION_H
#define MV_FACE_DETECTION_H

#include <cv.h>
#include <highgui.h>
#include <vector>

using namespace std;

class MvFaceDetectionImpl;

//����������
typedef struct stFaceDetectionParam
{
	int		m_nMinFaceSize;
	int		m_nMaxFaceSize;

	string  m_strFFaceDetectorModelFileName;	//����
	string	m_strLPFaceDetectorModelFileName;	//���
	string	m_strRPFaceDetectorModelFileName;	//�Ҳ�
	string	m_strLRFaceDetectorModelFileName;	//����
	string	m_strRRFaceDetectorModelFileName;	//����
} mv_stFDParam;

//�����켣
typedef struct stFaceTrackNode	//�����켣�ڵ�
{
	int64		m_nTime;		//�ڵ������ͼ������Ƶ�е�ʱ��(ms)��
	int64		m_nFrameNo;		//�ڵ������ͼ������Ƶ�е�֡�ţ�
	IplImage*	m_pFaceImage;	//ÿ���ڵ������ͼ��Ϊ�˺����Ķ��봦����Щͼ��ȼ���������ͼ���Դ�
	CvRect		m_faceRect;		//ÿ���ڵ��������ͼ���е�λ��

	stFaceTrackNode() 
	{
		m_nTime		= -1;
		m_nFrameNo	= -1;
		m_pFaceImage= NULL;
	}
} mv_stFaceTrackNode;

typedef struct stFaceTrack		//�����켣
{
	IplImage*			m_pRepImage;			//ÿ���켣һ��ȫͼ
	vector<CvRect>		m_vRepImageRects;		//����ʱ�ǹ켣������ȫͼ�е�λ�ã�ֻ��һ�����Σ���֡���ʱ�������λ��
	int64				m_nTime;				//�켣ȫͼ��Ӧʱ��(����)

	vector<mv_stFaceTrackNode>	m_vTrack;		//�켣��ÿ���ڵ�����ͼ���ڶ�Ӧ��λ����Ϣ

	stFaceTrack()
	{
		m_pRepImage = NULL;
	}
} mv_stFaceTrack;

bool mv_ReleaseFaceTrack(mv_stFaceTrack& track);
bool mv_ReleaseFaceTracks(vector<mv_stFaceTrack>& vTracks);

class MvFaceDetection
{
public:
	MvFaceDetection();
	~MvFaceDetection();

public:
	//��ʼ��
	bool mv_Init(mv_stFDParam& param);

	//�ͷ�
	bool mv_UnInit();

	//�������ӿ�
	bool mv_DetectFaces(IplImage* pImage, int64 ts, int64 nFrameNo, vector<mv_stFaceTrack>& vFaceTracks, 
						bool bTrack=true, bool bLastFrame=false);
	
	//��֡�������ӿ�
	bool mv_DetectFaces(IplImage* pImage, vector<CvRect>& vFacePos);

private:
	MvFaceDetectionImpl*	m_pFaceDetectionImpl;
};

#endif