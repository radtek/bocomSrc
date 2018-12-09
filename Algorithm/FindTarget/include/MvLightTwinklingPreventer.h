#ifndef MV_LIGHT_TWINKLING_PREVENTER
#define MV_LIGHT_TWINKLING_PREVENTER


#include <map>
#include <vector>
#include <string>
#include "cxcore.h"

// ��ֹ���̵���˸����,��һ���ƽ����жϣ��Ƿ�����
class MvLightTwinklingPreventer
{
public:
	MvLightTwinklingPreventer(CvRect lightRgn);

	MvLightTwinklingPreventer(CvRect lightRgn, float fThreshold);

	bool Process(unsigned int uSeq, IplImage* img);

	bool GetNearestLightOnFrame(unsigned int src, unsigned int &ret, bool bBigOrSmall);


	CvRect GetRgn() const;

	void SetName(std::string name);

private:

	// ֡�ţ��Ƶ�״̬��
	std::map<unsigned int, bool> m_mapLightStatus;

	// ������Ҷ���ʷ��¼��
	std::vector<int> m_vecLightRgnGrayRecord;


	CvRect m_rgn;

	// ��ֵ
	float m_fLighRgnGrayMean;

	// ��׼��
	float m_fLightRgnGrayStdVar;

	// 
	float m_fThreshold;

private:
	std::string m_strName;

};

#endif