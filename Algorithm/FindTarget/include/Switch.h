#include "tinyxml.h"

// �͵����йصĿ��ء����á�
class Switch
{
public:
	//static bool CreateFolder;
	static bool SaveImages;
	static int  SaveImageWidth;
	static int  SaveImageHeight;
	static bool SaveInputParas;
	static time_t  SaveImageParasTimeStart;
	static time_t  SaveImageParasTimeEnd;

	static bool SaveClassVehicleType; //���泵�ͷ���ͼƬ��
	// ����������ͼƬ���������˸���ܡ�

	
	static bool SaveRedLightRgnImage;

	static bool SavePlateImage;

	static bool ForceStraightRedLight;
	
	static bool SaveBusVanType;


	// ��ֹ�ڲ���ʱ����Ϊ�������ؿ������ξ����������ʱ�����̵ܶ��µĳ���©����
	static bool PreventPlateMiss;

	//������Ƶ�ٶ���أ�
	static bool DEBUG_CORRECT_VIDEO_SPEED;
	
	//�����״��ٶ���أ�
	static bool Debug_Radar_Speed;

	static void LoadSwtichValueFromXml(TiXmlNode *pConfigNode);

	//�ж��Ƿ���
	static bool OnTime;
};
