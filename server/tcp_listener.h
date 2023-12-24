//==========================================================
//
// winsock�ʐM(�ڑ���t) [tcp_listener.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include <winsock2.h>

//==========================================================
// �N���C�A���g�N���X�̒�`
//==========================================================
class CListener
{
public:	// �N�ł��A�N�Z�X�\

	CListener();	// �R���X�g���N�^
	~CListener();	// �f�X�g���N�^

	// �����o�֐�
	bool Init(int nPortNum);
	SOCKET Accept(void);
	void Uninit(void);
	char *GetIP(void) { return &m_aClientIP[0]; }
	int GetPort(void) { return m_nClientPort; }

private:	// ���������A�N�Z�X�\

	// �����o�ϐ�
	SOCKET m_sockServer; // �T�[�o�[�p�\�P�b�g
	char m_aClientIP[64];	// IP�A�h���X
	int m_nClientPort;		// �|�[�g�ԍ�
};

#endif