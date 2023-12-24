//==========================================================
//
// winsock�ʐM(�N���C�A���g) [tcp_client.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <winsock2.h>
#include "protocol_online.h"

#define MAX_NAME	(1024)

//==========================================================
// �N���C�A���g�N���X�̒�`
//==========================================================
class CClient
{
public:	// �N�ł��A�N�Z�X�\

	CClient();	// �R���X�g���N�^
	~CClient();	// �f�X�g���N�^

	// �����o�֐�
	void BindSock(SOCKET sock);
	void Uninit(void);
	int Send(const char *pSendData, int nSendDataSize);
	int Recv(char *pRecvData, int nRecvDataSize);
	static CClient *GetTop(void) { return m_pTop; }
	CClient *GetNext(void) { return m_pNext; }
	void SetIP(char *pIp);
	void SetCliePort(int nPort) { m_nClientPort = nPort; }
	char *GetIP(void) { return &m_aClientIP[0]; }
	int GetPort(void) { return m_nClientPort; }
	int GetId(void) { return m_nId; }
	void SetId(int nId) { m_nId = nId;}
	bool GetSend(void) { return m_bSend; }
	void SetSend(bool bSend) { m_bSend = bSend; }
	void SetData(char *pChar, int nByte);
	void ResetData(void);
	int GetSendByte(void) { return m_nSendByte; }
	char *GetSendData(void) { return &m_aSendData[0]; }
	bool GetDeath(void) { return m_bDeath; }
	void SetDeath(bool bDeath) { m_bDeath = bDeath; }

private:	// ���������A�N�Z�X�\

	// �����o�ϐ�
	SOCKET m_sock;	// �\�P�b�g
	static CClient *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CClient *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CClient *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CClient *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	char m_aClientIP[64];
	int m_nClientPort;
	int m_nId;
	bool m_bSend;		// �f�[�^���M��
	char m_aSendData[MAX_COMMAND_DATA];
	int m_nSendByte;		// �f�[�^��
	bool m_bDeath;		// �ؒf���Ă��邩�ۂ�
};

#endif