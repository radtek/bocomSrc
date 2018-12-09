#ifndef MV_CHANNEL_FRAME_SIGNAL_STATUS
#define MV_CHANNEL_FRAME_SIGNAL_STATUS

#include <list>


/*
 һ��ͨ����һ֡�ĺ��״̬��
*/
typedef struct _VTS_SIGNAL_STATUS
{
     int  nRoadIndex;	   //�������
	 unsigned int uFrameSeq;

     bool bLeftSignal;     //��ת��״̬.���true���̵�false��
     bool bStraightSignal; //ֱ�е�״̬
     bool bRightSignal;    //��ת��״̬

     _VTS_SIGNAL_STATUS()
     {
		 uFrameSeq       = 0;
         nRoadIndex      = -1;
         bLeftSignal     = false;
         bStraightSignal = false;
         bRightSignal    = false;
     }

}VTS_SIGNAL_STATUS, MvChannelFrameSignalStatus;

//�������Ƶ�״̬����
typedef std::list<MvChannelFrameSignalStatus> ChnFrmSignalStatusList;
typedef std::list<MvChannelFrameSignalStatus>::iterator ChnFrmSignalStatusListIt;
typedef std::list<MvChannelFrameSignalStatus>::const_iterator ChnFrmSignalStatusListConIt;

#endif