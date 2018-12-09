#ifndef MV_FACE_TRACK_SEARCH_H
#define MV_FACE_TRACK_SEARCH_H

#include <cv.h>
#include <vector>
#include <string>

using namespace std;

class MvFaceSearchImpl;

#ifndef MV_ST_FS_PARAM
#define MV_ST_FS_PARAM
//������������
typedef struct stFaceSearchParam
{
	string  m_strFaceDetectorFileName; //"./FaceDetector.xml"
	string	m_strASModelFileName; //"./asmmodel";
	string	m_strFeatModelFileName; //"./Gabor_model.txt"
} mv_stFSParam;
#endif

#ifndef MV_ST_FACE_FEATURE
#define MV_ST_FACE_FEATURE
//��������
typedef struct stFaceFeature
{
	char* 	m_pFaceFeature;
	int 	m_nSize;

	stFaceFeature()
	{
		m_pFaceFeature= NULL;
		m_nSize= 0;
	}

} mv_stFaceFeature;

//�����������
typedef struct stFaceMathRes
{
	float 	m_fDistance; //��ο�ͼ��ľ���
	CvRect 	m_rect;     //��ƥ��ͼ�е�λ��
	stFaceMathRes()
	{
		m_fDistance 	= -1.0f;
		m_rect			= cvRect(0,0,0,0);
	}
} mv_stFaceMathRes;
#endif

//�����켣�����ӿ�
class MvFaceTrackSearch
{
public:
	MvFaceTrackSearch();
	~MvFaceTrackSearch();

	//��ʼ���ӿ�
	bool mv_Initial(mv_stFSParam& param);

	//�ͷ�
	bool mv_UnInitial();

	//�������ӿ�,������߲�С��120x120
	bool mv_DetectFaces(IplImage* pImage, vector<CvRect>& facePos);

	//������ȡ�ӿ�, bExt=trueʱ����ȡ��������������ٶȻ����
	//����Ƶ������ȡʱbExt=false,
	//��ƥ��������ȡʱ��ѡ��bExt=true�����ƥ��׼ȷ��
	//**vImages��vFacePos�����ͼ��;�����һһ��Ӧ�ģ�����Щ���ݱ���������ͬһ���켣����������**
	bool mv_ExtractFeatureFromTrackImages(vector<IplImage*>& vImages, vector<CvRect>& vFacePos,
										  mv_stFaceFeature& faceFeatures, vector<CvRect> vOriFacePos=vector<CvRect>(), 
										  bool bTrack=true, bool bExt=false);

	//�����켣����ͼ�����������ӿ�
	bool mv_MatchTrackFeature(vector<mv_stFaceFeature>& targetFeatures, 
							  mv_stFaceFeature& queryFeature,
							  vector<mv_stFaceMathRes>& matchRes, bool bTrack=true);

private:
	MvFaceSearchImpl*	m_pFaceSearchImpl;	
};


#endif