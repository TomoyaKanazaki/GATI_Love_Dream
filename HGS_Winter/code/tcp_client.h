//==========================================================
//
// winsock�ʐM(�N���C�A���g)
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

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
	bool Init(const char *pIPAddress, int nPortNum);
	void BindSock(SOCKET sock);
	void Uninit(void);
	int Send(const char *pSendData, int nSendDataSize);
	int Recv(char *pRecvData, int nRecvDataSize);
	void SetCliePort(int nPort) { m_nClientPort = nPort; }
	char *GetIP(void) { return &m_aClientIP[0]; }
	int GetPort(void) { return m_nClientPort; }
	int GetId(void) { return m_nId; }
	void SetId(int nId) { m_nId = nId; }
	char *GetName(void) { return &m_aName[0]; }
	SOCKET GetSock(void) { return m_sock; }

private:	// ���������A�N�Z�X�\

	// �����o�ϐ�
	SOCKET m_sock;	// �\�P�b�g
	char m_aClientIP[64];
	int m_nClientPort;
	int m_nId;
	char m_aName[MAX_NAME];
};

#endif