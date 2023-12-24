//==========================================================
//
// winsock�ʐM(�ڑ���t) [tcp_listener.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "tcp_listener.h"
#include "tcp_client.h"
#include <stdio.h>

//==========================================================
// �R���X�g���N�^
//==========================================================
CListener::CListener()
{
	// �l���N���A����
	m_sockServer = NULL;
	m_nClientPort = 0;
	memset(&m_aClientIP[0], '\0', sizeof(m_aClientIP));
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CListener::~CListener()
{

}

//==========================================================
// ����������
//==========================================================
bool CListener::Init(int nPortNum)
{
	// �\�P�b�g�̍쐬
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);	//�ڑ���t�p�̃\�P�b�g�̍쐬����֐�

	if (m_sockServer == INVALID_SOCKET)
	{// �쐬�Ɏ��s�����ꍇ

		return FALSE;	// �I��
	}

	// �ڑ����󂯕t���邽�߂̏���
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);	// �ڑ����󂯕t����|�[�g�A�ԍ����Œ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;	// �\�P�b�g�Ƀ|�[�g�����蓖��
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));	// �ڑ���t�̏����A�ۗ����̐ڑ��ő吔��10�ŌŒ�
	listen(m_sockServer, 10);

	return TRUE;
}

//==========================================================
// �I������
//==========================================================
void CListener::Uninit(void)
{
	// �ڑ���t�p�\�P�b�g�����
	closesocket(m_sockServer);	// closesocket�֐� : �\�P�b�g�����
}

//==========================================================
// �ڑ���t����
//==========================================================
SOCKET CListener::Accept(void)
{
	SOCKET sock;	// �\�P�b�g

	// �ڑ���҂�
	printf("    *** �T�[�o�[�ڑ���t��... ***\n");
	struct sockaddr_in addrClient;
	int nLengthAddr = sizeof(addrClient);
	sock = accept(m_sockServer,	// accept�֐� : �ڑ����󂯓���� SOCKET�^�̕ϐ�->�\�P�b�g�f�B�X�N���v�^
		(struct sockaddr*)&addrClient, &nLengthAddr);	// �N���C�A���g���ڑ�������\�P�b�g�����������

	// �ڑ�����IP�A�h���X�E�|�[�g�ԍ����擾
	const char *pClientIP = inet_ntoa(addrClient.sin_addr);
	strcpy(&m_aClientIP[0], pClientIP);
	m_nClientPort = ntohs(addrClient.sin_port);

	// �ڑ����b�Z�[�W�̕\��
	printf("*** �N���C�A���g�Ɛڑ����܂���!!! ***\n");
	printf("IP�A�h���X: %s\n", &m_aClientIP[0]);
	printf("�|�[�g�ԍ�: %d\n", m_nClientPort);

	CClient *pClient = CClient::GetTop();	// �擪���擾

	int nCnt = 0;

	while (pClient != NULL)
	{// �g�p����Ă��Ȃ���Ԃ܂�

		CClient *pClientNext = pClient->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

		nCnt++;
		pClient = pClientNext;	// ���̃I�u�W�F�N�g�Ɉړ�
	}

	printf("*** ����%d�l�ڑ���***\n", nCnt);

	return sock;
}
