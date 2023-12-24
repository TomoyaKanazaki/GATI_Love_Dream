//==========================================================
//
// winsock�ʐM(�N���C�A���g) [tcp_client.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include <stdio.h>
#include "tcp_client.h"
#include <string.h>

CClient *CClient::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CClient *CClient::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CClient::CClient()
{
	// �l���N���A����
	m_sock = NULL;

	m_nId = -1;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}

	m_bSend = false;
	memset(&m_aSendData[0], '\0', sizeof(m_aSendData));
	m_nSendByte = 0;
	m_bDeath = false;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CClient::~CClient()
{

}

//==========================================================
// �\�P�b�g�̊��蓖��
//==========================================================
void CClient::BindSock(SOCKET sock)
{
	m_sock = sock;
}

//==========================================================
// �I������
//==========================================================
void CClient::Uninit(void)
{
	// �ڑ���ؒf����
	closesocket(m_sock);	// �N���C�A���g�Ƃ̐ڑ������

		// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}
}

//==========================================================
// ���M����
//==========================================================
int CClient::Send(const char *pSendData, int nSendDataSize)
{
	// �f�[�^���M
	int nSendByte = send(m_sock, pSendData, nSendDataSize, 0);	// send�֐�: �f�[�^�𑗐M����

	return nSendByte;
}

//==========================================================
// ��M����
//==========================================================
int CClient::Recv(char *pRecvData, int nRecvDataSize)
{
	int nRecvByte = recv(m_sock, pRecvData, nRecvDataSize, 0);	// recv�֐�: �f�[�^����M����

	return nRecvByte;
}

//==========================================================
// IP�̐ݒ�
//==========================================================
void CClient::SetIP(char *pIp)
{
	memcpy(&m_aClientIP[0], pIp, strlen(pIp));
}

//==========================================================
// ���M�f�[�^�̐ݒ�
//==========================================================
void CClient::SetData(char *pChar, int nByte)
{
	if (m_nSendByte + nByte < MAX_COMMAND_DATA)
	{
		memcpy(&m_aSendData[m_nSendByte], pChar, nByte);
		m_nSendByte += nByte;
	}
}

//==========================================================
// ���M�f�[�^�̃��Z�b�g
//==========================================================
void CClient::ResetData(void)
{
	memset(&m_aSendData[0], '\0', sizeof(m_aSendData));
	m_nSendByte = 0;
}