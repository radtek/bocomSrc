// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#if !defined(AFX_STDAFX_H__1C7A72A5_FA7D_4E8B_979A_4D0AE3C54735__INCLUDED_)
#define AFX_STDAFX_H__1C7A72A5_FA7D_4E8B_979A_4D0AE3C54735__INCLUDED_

#pragma warning(disable: 4786)

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers




#include <stdio.h>
#include "cxcore.h"

// TODO: reference additional headers your program requires here

#define DO_COL_DET//��ɫ���
#define  SHUT_REC//��Գ��Ʊ���λ������
#define SPEED_UP  //���٣����ر��˲ɱ궨;�ر����߶μ�⣬��getimg���˴���

#ifdef SPEED_UP //
//#define USE_DSP_CODE_FIND //����Yͨ�����٣�
//#define CORNER_UP //�ǵ����
//#undef  SHUT_REC//ȡ�����Ʊ���λ������
//#undef DO_COL_DET //�ر���ɫ���
#endif

#define TRACK_GROUP_LGW //�켣���ٿ��� ---����vlp

//#define TURNON_EXCEDSPEED //����������/


//#define  VIO_RANK_OUT//Υ�µȼ�����--���--��2���ط������ˣ�


//������Կ��Թرգ�ƽʱ����
//#define  CONTRAL_SINGLE_CAR //�������------�ɹر�:ʹ���Ƽ�⵽һ�ε�Ҳ���и���

//#define RESEVE_DIR_0 //�����л�ҽԺ���ڵ�����---��Կ��ڵ�����ͨ��

#define DO_BURNS_VEICHLE_TYPE             // �Ƿ���ʹ��ֱ���жϳ���
#define DO_ABS_BG                         // �Ƿ����þ��Ա�����
//#define DEBUG_FORCE_NIGHT_MODE          // ǿ��ҹ��ģʽ
//#define DEBUG_FORCE_DAY_MODE            // ǿ�ư���ģʽ
//#define DO_DONGS_CODE
//#define PREVENT_PLATE_MISS              // ��ֹ�����ڶ�ʱ���ڶ�ξ�������ʱ��©�����򿪴˿����ڳ���ʱ���ܵ��¶౨��
 //#define DEBUG_FTG_OPTIMIZATION //��¼��ģ���ʱ----------------------------
//#define DEBUG_ERROR                     //����
#define SAVE_CODE    //���ص���ʹ��
//�������

#ifdef LINUX
 #define int64 long long
#endif

#ifdef LINUX

	#include <dirent.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#define _chdir(a) chdir(a)
	#define _mkdir(a) mkdir(a, 0777)

	#define DEBUG_SILENT                      //����������(�޴��ڡ��޴�ͼ)���ر�������(�д��ڻ��ͼ)��
	#define DEBUG_ERROR                     //����
    #undef DEBUG_FTG_OPTIMIZATION //close time Recoard
    #undef SAVE_CODE

#else
	#include <direct.h>
	#define SHOW_WINDOW
	#define READ_CALIBRATION_FILE             //Linux�±��� �ص���Windows�±����
//	#define DEBUG_SILENT
    //#define DEBUG_ERROR                     //����


#endif


#ifdef  SPEED_UP  //���٣����ر��˲ɱ궨;�ر����߶μ�⣬��getimg���˴���
#define DEBUG_SILENT 
#endif

#define STORE_FRAMES     60  
#define CHANGE_FOLDER_FRAMES     1000     //ÿ����ô��֡�����ļ��д�ͼ��
//#define DEBUG_VIRTUAL_LOOP_IMAGE          //�Ƿ����������Ȧͼ����ʾ����ͼ��
//#define SAVE_VLP_IMAGE                    //����������Ȧͼ��
//#define DEBUG_BACKGROUND                  //�Ƿ����������Ȧ����
//#define SAVE_BACKGROUND                   //���汳��ͼ��
//#define DEBUG_LONG_TERM_GBM
//#define DEBUG_LONG_TRACK

//#define DEBUG_ABS_BG
#define LSD_LINE





//#define DEBUG_ERODE_DILATE                //�Ƿ���ʾ������Ȧǰ�����Լ������͸�ʴ���
//#define DEBUG_VLP_CONTOUR                 //�Ƿ���ʾ������Ȧͼ�������

//#define DEBUG_VIRTUAL_LOOP_RECTS          //�Ƿ���ʾ������Ȧ��֪����Rects ��BG,FLOW) //*********

//#define SAVE_FLOW_FORE
//#define SAVE_BG_FORE                      //���汳��ģ����ȡ��ǰ��
//#define SAVE_RECTSIMAGE                   //����rectsimg
//#define DEBUG_EDGE_CONTOUR_GROUP          //�Ƿ���ʾ��Ե��ϵõ���Rects

              
//#define DEBUG_CHECK_IMAGE                 //����checkͼ
//#define SAVE_CHECK_IMAGE                  //����checkͼ
//#define DEBUG_CHECK_IMG_GROUP             //����checkimg��group
//#define DEBUG_NON_UPDATE_REGION 

//#define DEBUG_OUTPUT_WAIKEY
//#define DEBUG_CLEAR_ROAD_LINE
//#define DEBUG_OPTICAL_FLOW_SIFT
//#define DEBUG_WRITE_RECORD                //�Ƿ�ÿһ֡��¼����objs��Ϣ
//#define DEBUG_HAVE_MOVED_POINT_IN_REGION
//#define DEBUG_OBJECT_RECT              //�������ģʽ��Ԥ���Ŀ��λ�á�
//#define SAVE_OBJECT_RECT_IMAGE
//#define DEBUG_POS_FRAME_ASSOC          //��¼���ݳ���λ�ù���
//#define DEBUG_CAR_NUM_LEAKING            //��¼©����CarNumRecord.txt
//#define LOG_RUN_FRAMES                  //��¼������ܵ���ÿһ֡��֡�ţ�ʱ���
//#define DEBUG_BEST_ASSIGNMENT           //��ӡ��Ѷ�Ӧ��Ϣ
//#define DEBUG_EXIT_WHEN_REINIT
//#define TIMER								//��ӡ�ͱ������е�ʱ����Ϣ
//#define DEBUG_MANY_ZERO_FLOW_TRACK_SEAL
//#define DEBUG_VEICHLE_TYPE_LINES         //�鿴�г���ʱ��ֱ����ȡ���
//#define DEBUG_VEICHLE_TYPE_BY_LINES        //�����г���Ч��
//#define SAVE_VEICHLE_TYPE_BY_LINES_IMG     //�г��ĳ��ʹ�ͼ��
//#define DEBUG_CAR_NUM_REVISE               //���Ƴ���������ļ�¼�����ļ���
//#define DEBUG_SPLIT_BY_OBJS                //���Է������
//#define DEBUG_CORNER_BACKGROUND
//#define DEBUG_VEICHLE_TYPE_BY_HEAD_LIGHT   //�����ó����жϳ���
//#define SAVE_VEICHLE_TYPE_BY_HEAD_LIGHT_IMG
#define DEBUG_CHANNELS_LINES                  // ���Գ�����ֹͣ�ߵ���Ϣ��

//#define DEBUG_BG_CHANGED_DETECT

//#define DEBUG_WAIT_COLOR_CHANGE_SEAL
//#define SAVE_WAIT_COLOR_CHANGE_SEAL
// #define DEBUG_RIGHT_CAR
// #define DEBUG_BIG_CAR
// #define SAVE_SIDE_BIG_CAR_IMAGE0
// #define SAVE_BIG_CAR
// #define DEBUG_HISTOGRAM
// #define DEBUG_THRESHOLD
// #define DEBUG_HISTOGRAM_PROJECT
 //#define DEBUG_GROUPS
// #define SAVE_BIG_CAR_NIGHT
//#define DEBUG_WAITKEY


//#define DEBUG_FTG_CORNERS
#define DEBUG_FTG_TRACKS
#define DEBUG_FTG_TACK_SET

//#define DEBUG_FIX_BY_HISTORY
//#define SAVE_FIX_BY_HISTORY


//#define DEBUG_ROAD_STATISTIC
//#define DEBUG_BG_LINE
//#define DEBUG_REVISE_BY_CARNUM
//#define DEBUG_PHYSIC_LOOP1
//#define DEBUG_MOTION_DIFF_CUT`
//#define DEBUG_PHYSIC_LOOP2
//#define DEBUG_ERROR_CORRECT_TIME

//#define DEBUG_SAVE_StarVlpBigVeh_Removal   //��������*****��Ŀ��౨���ܣ�




//police
#define FORCE_STRAIGHT_RED_LIGHT
//#define SAVE_CORNERS_IMAGE
#define SAVE_TRACKS_AND_GROUPS


#define DEBUG_GROUPS_UPDATE 

//#define DEBUG_TRACKS_UPDATE

//#define DEBUG_CORNERS

#define DEBUG_TRACKS_AND_GROUPS 



//#define DEBUG_LOOP_SELECT_PIC

//#define PRINTF_INFO
//#define TIMER_INFO

//#define DEBUG_MERGE_GROUPS
//#define DEBUG_ROAD_TYPE_DETECTOR            // ���Ե�·�����жϹ��ܡ��ж�ͼ��������ǻ����������Ƿǻ���������

//#define LGW_GOAL_IMG
//#define LGW_TIME_PRINTF


//#define   FUNCTION_TIME_TEST
//#define   TEST_SWITCH
//#define LGW_TEST_SHOW














#ifdef DEBUG_SILENT

#ifndef SHOW_WINDOW
#undef SAVE_CODE
#endif

#undef TEST_SWITCH
#undef FUNCTION_TIME_TEST
#undef LGW_TIME_PRINTF
#undef LGW_GOAL_IMG
#undef LGW_TEST_SHOW
#undef DEBUG_BACKGROUND
#undef SAVE_BACKGROUND
#undef DEBUG_LONG_TERM_GBM
#undef DEBUG_LONG_TRACK
#undef DEBUG_ABS_BG

#undef LSD_LINE
//#undef DEBUG_FTG_OPTIMIZATION //��ӡʱ�� //////-------------��liuxu������ӡʱ��


#undef DEBUG_VIRTUAL_LOOP_RECTS
#undef DEBUG_CHECK_IMAGE


#undef DEBUG_VIRTUAL_LOOP_IMAGE
#undef SAVE_VLP_IMAGE
#undef DEBUG_ERODE_DILATE
#undef DEBUG_VLP_CONTOUR

#undef DEBUG_EDGE_CONTOUR_GROUP
#undef DEBUG_VIDEO
#undef DEBUG_DIFF_IMAGE

#undef DEBUG_CHECK_IMG_GROUP
#undef DEBUG_NON_UPDATE_REGION
#undef DEBUG_SOBEL_IMAGE
#undef DEBUG_OUTPUT_WAIKEY
#undef DEBUG_LINES
#undef DEBUG_CLEAR_ROAD_LINE
#undef DEBUG_OPTICAL_FLOW_SIFT
#undef DEBUG_WRITE_RECORD
#undef DEBUG_HAVE_MOVED_POINT_IN_REGION

#undef DEBUG_OBJECT_RECT

#undef DEBUG_POS_FRAME_ASSOC
#undef DEBUG_CAR_NUM_LEAKING
#undef LOG_RUN_FRAMES
#undef DEBUG_BEST_ASSIGNMENT
#undef DEBUG_EXIT_WHEN_REINIT
#undef SAVE_BIG_CAR_NIGHT
#undef TIMER
#undef DEBUG_RIGHT_CAR
#undef DEBUG_BIG_CAR
#undef DEBUG_HISTOGRAM
#undef DEBUG_THRESHOLD
#undef DEBUG_HISTOGRAM_PROJECT

#undef DEBUG_WAITKEY

#undef DEBUG_MANY_ZERO_FLOW_TRACK_SEAL
#undef DEBUG_VEICHLE_TYPE_LINES
#undef DEBUG_VEICHLE_TYPE_BY_LINES
#undef SAVE_VEICHLE_TYPE_BY_LINES_IMG
#undef DEBUG_CAR_NUM_REVISE
#undef DEBUG_SPLIT_BY_OBJS
#undef DEBUG_CORNER_BACKGROUND
#undef DEBUG_VEICHLE_TYPE_BY_HEAD_LIGHT
#undef DEBUG_BG_CHANGED_DETECT


#undef DEBUG_FTG_CORNERS
#undef DEBUG_FTG_TRACKS
#undef DEBUG_FTG_TACK_SET
#undef DEBUG_FIX_BY_HISTORY

#undef DEBUG_WAIT_COLOR_CHANGE_SEAL

#undef DEBUG_ROAD_STATISTIC
#undef DEBUG_BG_LINE
#undef DEBUG_REVISE_BY_CARNUM
#undef DEBUG_PHYSIC_LOOP1
#undef DEBUG_MOTION_DIFF_CUT
#undef DEBUG_PHYSIC_LOOP2
#undef DEBUG_ERROR_CORRECT_TIME


//police

#undef FORCE_STRAIGHT_RED_LIGHT
#undef SAVE_CORNERS_IMAGE
#undef SAVE_TRACKS_AND_GROUPS


#undef DEBUG_GROUPS_UPDATE 

#undef DEBUG_TRACKS_UPDATE

#undef DEBUG_CORNERS

#undef DEBUG_TRACKS_AND_GROUPS 

#undef DEBUG_MAX_SIZE

#undef PRINTF_INFO
#undef TIMER_INFO

#undef DEBUG_MERGE_GROUPS

#undef DEBUG_ROAD_TYPE_DETECTOR

#undef DEBUG_LOOP_SELECT_PIC

#endif



//#define DEBUG_VIRTUAL_LOOP_RECTS






#ifndef MAX_OF_TWO
#define MAX_OF_TWO(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN_OF_TWO
#define MIN_OF_TWO(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#ifndef MEAN_OF_TWO
#define MEAN_OF_TWO(a, b)          (((a) + (b)) / 2)
#endif



#ifndef MAX_UINT
#define MAX_UINT     ((unsigned int)~((unsigned int)0))
#endif


#ifndef MAX_INT
#define MAX_INT      ((int)(MAX_UINT >> 1))
#endif

#ifndef MIN_INT
#define MIN_INT      ((int)~MAX_INT)
#endif


#ifndef PRJ_NAMESPACE_NAME
#define PRJ_NAMESPACE_NAME FindTargetElePolice
#endif

#ifndef PRJ_NAMESPACE_BEGIN
#define PRJ_NAMESPACE_BEGIN namespace FindTargetElePolice {
#endif

#ifndef PRJ_NAMESPACE_END
#define PRJ_NAMESPACE_END }
#endif




#define DRAW_RECT(img, rect, color) \
	cvDrawRect( \
	(img), \
	cvPoint(((rect).x), ((rect).y)), \
	cvPoint(((rect).x) + ((rect).width -1), ((rect).y) + ((rect).height - 1)), \
	(color), \
	2 \
	)




#define RESIZE_RECT(rect, fx, fy) \
	cvRect((rect.x) * (fx), (rect.y) * (fy), (rect.width) * (fx), (rect.height) * (fy));





#ifdef LINUX
	#define LOCALTIME(ptime, ptm) localtime_r((ptime), (ptm))
#else
	#define LOCALTIME(ptime, ptm) localtime_s((ptm), (ptime))
#endif



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1C7A72A5_FA7D_4E8B_979A_4D0AE3C54735__INCLUDED_)




