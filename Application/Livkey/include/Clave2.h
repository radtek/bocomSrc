/**************************************************************************
* Copyright (c) 1995-2012, Beijing Senselock Software Technology Co.,Ltd.
* All rights reserved.
*
* filename: Clave2.h
*
* briefs:  API library interface declaration and the error code
*
* history:
* 07/31/2008   yingy   R&D   create
* 08/05/2008   zhaock  R&D   modify
**************************************************************************/

#ifndef _CLAVE2_H_
#define _CLAVE2_H_

#ifdef  _MSC_VER
#pragma comment(linker, "/defaultlib:setupapi.lib")
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIVAPI
#if defined WIN32 || defined _WIN32
#define LIVAPI __stdcall
#else
#define LIVAPI
#endif
#endif

// ������
#define LIV_SUCCESS                            0  // �ɹ�
#define LIV_OPEN_DEVICE_FAILED                 1  // ���豸ʧ��
#define LIV_FIND_DEVICE_FAILED                 2  // δ�ҵ������������豸
#define LIV_INVALID_PARAMETER                  3  // ��������
#define LIV_INVALID_BLOCK_NUMBER               4  // ��Ŵ���
#define LIV_HARDWARE_COMMUNICATE_ERROR         5  // ��Ӳ��ͨ�Ŵ���
#define LIV_INVALID_PASSWORD                   6  // �������
#define LIV_ACCESS_DENIED                      7  // û��Ȩ��
#define LIV_ALREADY_OPENED                     8  // �豸�Ѿ���
#define LIV_ALLOCATE_MEMORY_FAILED             9  // �ڴ����ʧ��
#define LIV_INVALID_UPDATE_PACKAGE             10 // ���Ϸ���������
#define LIV_SYN_ERROR                          11 // �߳�ͬ������
#define LIV_OTHER_ERROR                        12 // ����δ֪�쳣������
#define LIV_OPERATION_NOT_SUPPORTED            13 // ��֧�ֵĲ���
#define LIV_DEVICE_BLOCKED                     14 // �豸����
#define LIV_WRITE_FAILED                       15 // FLASHдʧ��

// Ӳ����Ϣ�ṹ
typedef struct {
    int    developerNumber; // �����̱��
    char   serialNumber[8]; // �豸Ψһ���к�
    int    manufactureDate; // ��������
    int    setDate;         // ��������
	int    reservation;     // ����
}LIV_hardware_info;

// �����Ϣ�ṹ
typedef struct {
    int    version;        // ����汾
	int    reservation;    // ����
} LIV_software_info;

// Ӳ���汾��Ϣ
typedef struct {
	char   capacity[4];    // �����ֽ�Ϊ������Ϣ
	char   version[3];     // ��λ�̼��汾��Ϣ
}LIV_version_info;

// @{
/**
    @LIV API function interface
*/

/**
    ���ݿ����̱�ź��������򿪷����������豸

    @parameter vendor           [in]  �����̱��(0= ����)
    @parameter index            [in]  �豸����(0= ��һ������������)
    @parameter handle           [out] ���ص��豸���

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_open(int vendor, int index, int *handle);

/**
    �ر��Ѿ��򿪵��豸

    @parameter handle           [in]  �򿪵��豸���

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_close(int handle);

/**
    У���豸����

    @parameter handle           [in]  �򿪵��豸���
    @parameter type             [in]  �������ͣ�����Ա0����ͨ1����֤2��
    @parameter passwd           [in]  ����(8�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_passwd(int handle, int type, unsigned char *passwd);

/**
    ��ָ�����������

    @parameter handle           [in]  �򿪵��豸���
    @parameter block            [in]  Ҫ��ȡ�������
    @parameter buffer           [out] ��ȡ���ݻ�������������ڵ���512�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_read(int handle, int block, unsigned char *buffer);

/**
    дָ�����������

    @parameter handle           [in]  �򿪵��豸���
    @parameter block            [in]  Ҫд��������
    @parameter buffer           [in]  д�����ݻ�������������ڵ���512�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_write(int handle, int block, unsigned char *buffer);

/**
    ʹ��AES�㷨��������

    @parameter handle           [in]  �򿪵��豸���
    @parameter plaintext        [in]  Ҫ���ܵ���������(16�ֽ�)
    @parameter ciphertext       [out] ���ܺ����������(16�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_encrypt(int handle, unsigned char *plaintext,  unsigned char *ciphertext);

/**
    ʹ��AES�㷨��������

    @parameter handle           [in]  �򿪵��豸���
    @parameter ciphertext       [in]  Ҫ���ܵ���������(16�ֽ�)
    @parameter plaintext        [out] ���ܺ����������(16�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_decrypt(int handle, unsigned char *ciphertext, unsigned char *plaintext);

/**
    �����µĿ����Ҫ������Ȩ��

    @parameter handle           [in]  �򿪵��豸���
    @parameter type             [in]  �������ͣ�����Ա0����ͨ1����֤2��
    @parameter newpasswd        [in]  ����(8�ֽ�)
    @parameter retries          [in]  �������(1-15) -1��ʾ��ʹ�ô������

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_set_passwd(int handle, int type, unsigned char *newpasswd, int retries);

/**
    �޸Ŀ���

    @parameter handle           [in]  �򿪵��豸���
    @parameter type             [in]  �������ͣ�����Ա0����ͨ1����֤2��
    @parameter oldpasswd        [in]  �ɿ���(8�ֽ�)
    @parameter newpasswd        [in]  �¿���(8�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_change_passwd(int handle, int type, unsigned char *oldpasswd, unsigned char *newpasswd);

/**
    ����������
	@parameter serial           [in]  �����������к�
	@parameter block            [in]  Ҫ�����������
	@parameter buffer           [in]  �������ݣ�����3Ϊ384�ֽڣ�����512�ֽڣ�
	@parameter key              [in]  Զ��������Կ��20�ֽڣ�
	@parameter uptPkg           [out] ��������549�ֽڣ�

	@return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_gen_update_pkg(unsigned char * serial, int block, unsigned char *buffer, unsigned char *key, unsigned char *uptPkg);


/**
    Զ�̸���ָ��������

    @parameter handle           [in]  �򿪵��豸���
    @parameter buffer           [in]  �������ݰ�������


    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_update(int handle, unsigned char *buffer);

/**
    ȡӲ����Ϣ

    @parameter handle           [in]  �򿪵��豸���
    @parameter info             [out] Ӳ����Ϣ

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_get_hardware_info(int handle, LIV_hardware_info *info);

/**
ȡӲ����ذ汾��Ϣ

    @parameter handle           [in]  �򿪵��豸���
    @parameter buffer           [out] Ӳ���汾�����Ϣ

    @return value
�ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_get_version_info(int handle,LIV_version_info *versioninfo);

/**
    ȡ�����Ϣ

    @parameter info             [out] �����Ϣ

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_get_software_info(LIV_software_info *info);

/**
    Ӳ������hmac

    @parameter handle           [in]  �򿪵��豸���
    @parameter text             [in]  Ҫ����hmacֵ������
    @parameter textlen          [in]  ���ݳ���( >= 0)
    @parameter digest           [out] hmacֵ(20�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_hmac(int handle, unsigned char *text, int textlen, unsigned char *digest);

/**
    �������hmacֵ

    @parameter text            [in]  Ҫ����hmacֵ������
    @parameter textlen         [in]  ���ݳ���(0-(δȷ��) �ֽ�)
    @parameter key             [in]  hmac�㷨��key(20�ֽ�)
    @parameter digest          [out] hmacֵ(20�ֽ�)

    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_hmac_software(unsigned char *text, int textlen, unsigned char * key, unsigned char *digest);

/**
    ������Կ

    @parameter handle           [in]  �򿪵��豸���
    @parameter type             [in]  ��Կ���ͣ�0--Զ��������Կ��1--��֤��Կ ��
	@parameter key              [in]  ��Կ(20�ֽ�)


    @return value
    �ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_set_key(int handle, int type, unsigned char *key);

/**
LED����

    @parameter handle        [in]  ���豸���
    @parameter types         [in]  ��˸���� ��0�� 0xff�� 1-3��ͬƵ�ʣ�

    @return value
�ɹ�������0��ʧ�ܣ�����Ԥ����Ĵ�����
*/
int LIVAPI LIV_flash_led(int handle, unsigned char types);

#ifdef __cplusplus
}
#endif

#endif /* end of "#ifndef _LIVING1_H_" */
