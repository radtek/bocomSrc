#ifndef _C_USB_KEY_IMP_H
#define _C_USB_KEY_IMP_H

#include <string>

class UsbKeyLockWrite
{
public:
	UsbKeyLockWrite();
	~UsbKeyLockWrite();

	//��usbkey�豸
	bool OpenUsb(int port = 0);
	//�ر�usbkey�豸
	bool CloseUsb();
	//д���ݵ�usbkey�豸
	bool WriteUsb();

private:
	//�޸Ĺ���Ա�û�����ͨ�û�����,retriesΪ�����������ʱ��ೢ�ԵĴ�����-1����ʾ�޳��ԣ���1~15����,Ĭ��3��
	int SetPwd(unsigned char * adminPwd, unsigned char * userPwd, int retries = 6);

private:
#if defined _X64_ || defined __x86_64__
	 int m_inHandle;
#else
	 int m_inHandle;
#endif
};

#endif