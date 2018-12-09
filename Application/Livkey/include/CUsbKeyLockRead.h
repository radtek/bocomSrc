#ifndef _C_USB_KEY_LOCK_H
#define _C_USB_KEY_LOCK_H

class CUsbKeyLockRead
{
public:
	CUsbKeyLockRead();
	~CUsbKeyLockRead();

	//�����⴮��
	bool OpenUsb(int port = 0);
	//�ر����⴮��
	bool CloseUsb();
	//�Ƚ���֤���
	bool CompareLocalInfo();

private:
#if defined _X64_ || defined __x86_64__
	int m_inHandle;
#else
	int m_inHandle;
#endif

	int m_nKeyType;
};

#endif