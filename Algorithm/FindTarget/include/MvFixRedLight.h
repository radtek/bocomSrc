#ifndef MV_FIX_RED_LIGHT_H
#define MV_FIX_RED_LIGHT_H

//#include <time.h>
#include <string>
#include <vector>
#include <stdio.h>
#include "MvChannelFrameSignalStatus.h"
#include "MvLightTwinklingPreventer.h"
#include "cxcore.h"
#include "cv.h"
#include "Mode.h"
#include "MvChannelRegion.h"
#include "MyVideoStabilizer4Client.h"

using namespace std;
/*
//#ifndef MIN
//#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
//#endif
//#ifndef MAX
//#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
//#endif
//#ifndef min
//#define min(a,b)            (((a) < (b)) ? (a) : (b))
//#endif
//#ifndef max
//#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#endif
*/
//#define DrawRedGreenRegion    //�����Ƿ񻭳����õ��ĺ��̵�����Ŀ���

enum LIGHTSTAT{ L_RED, L_GREEN, L_YELLOW, L_OTHRE };

#define MAXSECOND    500

#define LOOPCOUNTER   10

/*
�Գ�ɳ����������500�������Ʋ�����������޲���


<FixRedLight>
	<RoadIndex></RoadIndex>
	<LeftLight x="" y="" w="" h="" />
	<MidLight x="" y="" w="" h="" />
	<RightLight x="" y="" w="" h="" />
	<TurnAroundLight x="" y="" w="" h="" />

	<OnOffRed x="" y="" w="" h="" />
	<OnOffGreen x="" y="" w="" h="" />
</FixRedLight>

*/
class RedLightFixer
{

public:
	int nRoadIndex;

	float fRedPar, fGreenPar;//���̵���ǿ����

	bool nFlagStrongRed;//�Ƿ���Ҫ���к��̵�����
	bool nFlagGleam;    //�Ƿ���Ҫ���̵Ʒ�������

	bool bLastStatus;

	CvRect OnOffRed;
	CvRect OnOffGreen;	


	//��ͼ��
	CvRect roiLeftLight;
	CvRect roiMidLight;
	CvRect roiRightLight;
	CvRect roiTurnAroundLight;

	//�����ǿ�õ�
	CvRect roiLeftLight_red, roiLeftLight_green;
	CvRect roiMidLight_red, roiMidLight_green;
	CvRect roiRightLight_red, roiRightLight_green;
	CvRect roiTurnAroundLight_red, roiTurnAroundLight_green; 

	//���̵���ɫ��������
	int VarIniRedH;
	int VarIniRedL;
	int VarIniGenH;
	int VarIniGenL;
	float fScale;


private:
	int64 m_Lastts;
	bool bFirstProcess;
	int m_position;
	int m_Last_Light_Status;
	int m_Current_Light_Status;
	int m_Start_Light_Status;
	int64 m_start_time;
	int64 m_yellow_time;

	int64 m_MidNumber;
	int64 m_LeftNumber;
	int64 m_RightNumber;

	int64    nCounter;
	int      nLeftFlag[LOOPCOUNTER];
	int      nStrightFlag[LOOPCOUNTER];
	int      nRightFlag[LOOPCOUNTER];	
	int      nFlagRect; //�Ƿ��ཻ��־ 1Ϊ�ཻ��0Ϊ���ཻ



private:

	typedef struct _ImgHolder
	{
		IplImage *redimg[MAXSECOND];
		IplImage *greenimg[MAXSECOND];

		_ImgHolder()
		{
			memset( redimg, NULL, MAXSECOND * sizeof(IplImage*) );
			memset( greenimg, NULL, MAXSECOND * sizeof(IplImage*) );
		}


		bool GenRedImg( IplImage** pDest, int nIndex )
		{
			if ( nIndex >= MAXSECOND || !redimg[nIndex] )
			{
				return false;
			}
			*pDest = cvCreateImage(cvGetSize( redimg[nIndex]), 8, 3);
			cvCopy( redimg[nIndex], *pDest);
			return true;
		}

		bool GenGreenImg( IplImage** pDest, int nIndex )
		{
			if (nIndex >= MAXSECOND || !greenimg[nIndex] )
			{
				return false;
			}

			*pDest = cvCreateImage(cvGetSize(greenimg[nIndex]), 8, 3);
			cvCopy(greenimg[nIndex], *pDest);
			return true;
		}

		bool AddImg( IplImage* img, bool bRedOrGreen, int nIndex )
		{
			if ( nIndex >= MAXSECOND )
			{
				return false;
			}
			if (bRedOrGreen)
			{
				if ( redimg[nIndex] )
				{
					cvReleaseImage(&redimg[nIndex]);
				}
				redimg[nIndex] = img;
			}
			else
			{
				if ( greenimg[nIndex] )
				{
					cvReleaseImage(&greenimg[nIndex]);
				}
				greenimg[nIndex] = img;
			}
			return true;

// 			if (redimg.size() > 10)
// 			{
// 				cvReleaseImage(&(*(redimg.begin())));
// 				redimg.erase(redimg.begin());
// 			}
// 			if (greenimg.size() > 10)
// 			{
// 				cvReleaseImage(&(*(greenimg.begin())));
// 				greenimg.erase(greenimg.begin());
// 
// 			}
		}

		~_ImgHolder()
		{
			for ( int i = 0; i < MAXSECOND; i++ )
			{
				if ( redimg[i] )
				{
					cvReleaseImage(&redimg[i]);
				}
				if ( greenimg[i] )
				{
					cvReleaseImage(&greenimg[i]);
				}
			}
// 			vector<IplImage*>::iterator it;
// 			for (it = greenimg.begin(); it!=greenimg.end(); it++)
// 			{
// 				cvReleaseImage(&(*it));
// 			}
// 			for (it = redimg.begin(); it!=redimg.end(); it++)
// 			{
// 				cvReleaseImage(&(*it));
// 			}
		}

	}ImgHolder;

	ImgHolder imgHolderLeft;
	ImgHolder imgHolderMid;
	ImgHolder imgHolderRight;
	ImgHolder imgHolderAround;
	
	

	MvLightTwinklingPreventer *pOnOffStatRed;
	MvLightTwinklingPreventer *pOnOffStatGreen;


	void Process(int64 timestamp,unsigned int uSeq, IplImage* img0, bool bTurnLeft, bool bFoward, bool bTurnRight, Time_Mode nDay, MyAffParams m_affparams);

	bool LoadFromXML();

	void mvImageProcessRedLight( IplImage *image, CvRect rect, Time_Mode mode, int nRedLight );

	void LigCorrect(IplImage *ImgData, CvRect RecLig, int nLghtSort);	

	bool Filter( IplImage *pimg, CvRect vRect, long* kernel, long Ksize, long Kfactor, long Koffset );


	//��ӵ���ͷ���̵Ƽ�⡪��ͳ�ƺ졢�̸���ɫ�ĸ���
    //void MvSingleLightRGNumStatc(IplImage*SrcImg, CvRect SingleLightRegion, int* nRGNumPin, int nImgSeq );
	int MvSingleLightRGNumStatc(IplImage*SrcImg,int Width,int Height,CvRect SingleLightRegion,int* nRGNumPin, int nFlagOverLap, int nFlagRedReg/*���������Ǻ�ƻ����̵�����*/ );


    void MvDrawSingleLightRG(IplImage*SrcImg, CvRect SingleLightRegion, int* nRGNumPin, int nImgSeq, int nSaveRoadSevLight );


	void ProcessSinglePic( IplImage* img0, bool bTurnLeft, bool bFoward, bool bTurnRight, MyAffParams m_affparams );

	void CheckImageLight(IplImage* img0, bool &bLeft, bool &bForeward, bool &bRight, Time_Mode nDay, int nImgSeq );

	void mvFillHoleImage( IplImage *pImage );
     

	

	
	

public:

	

	RedLightFixer();
	RedLightFixer( ChannelRegion &m_channlregion, bool bFlagStrongRed, bool bFlagGleam );

	~RedLightFixer();

    void SetLigPrama(float f_Scale);
	void Process( int64 timestamp,unsigned int uSeq, IplImage* img0, ChnFrmSignalStatusList cfss, Time_Mode nDay, MyAffParams m_affparams);

	void ProcessSinglePic( IplImage *img0, ChnFrmSignalStatusList sigStatusList, MyAffParams m_affparams );

	void CheckImageLightProcess(IplImage* img0, ChnFrmSignalStatusList &cfss, Time_Mode nDay, int nImgSeq);
};



#endif
