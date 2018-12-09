#ifndef CAMERACRTSTRUCT_H
#define CAMERACRTSTRUCT_H

#define CLIGHT_KINDS (6) /*�������ڼ���˳�⡢���������ֱ��ͼ*/
const float CEPSILONN = 0.0000001f;

#ifndef	_LIGHT_CARROAD
#define _LIGHT_CARROAD
enum LIGHT_CARROAD
{
	TOWARDS_LIGHT = 1,
	INV_LIGHT,
	LEFT_SIDE_LIGHT, 
	RIGHT_SIDE_LIGHT,
	NORMAL_LIGHT
}; // �Ű����������� 1 Ϊ˳�� 2 Ϊ���  3 Ϊ�����Һ� 4 Ϊ�������
#endif

enum _COLORCHNNL
{
	CB_G_R = 0,
	CR_G_B
};

enum _C_MODE_DN
{
	C_NIGHT = 0,
	C_DAY
};

#ifdef LINUX
	#define RGB_CHNNL_CAMERA
#endif

#ifdef LINUX
	//#define BG_SAVE_LIGHT
	//#define TEST_CAMERA_CONTROL_SAVE
#else

	//#define BG_TIME_PRINTF
	//#define DEBUG_CARD_BG_LIGHT
	//#define DEBUG_LINUX_CARDCAR
	//#define BG_LIGHT_PRINTF
	#define BG_SAVE_LIGHT
	#define TEST_CAMERA_CONTROL_SAVE

#endif










#endif