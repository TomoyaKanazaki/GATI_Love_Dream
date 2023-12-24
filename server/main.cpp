//==========================================================
//
// winsock�ʐM(�T�[�o�[)
// Author : Ibuki Okusada
//
//==========================================================
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#include "tcp_server.h"
#include "tcp_client.h"
#include <thread>
#include <stdlib.h>
#include "protocol_online.h"
#include "d3dx9.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")		// �V�X�e�������擾�ɕK�v

// �}�N����`
#define MAX_STRING	(2048)	// �ő啶����
#define DEF_PORT	(22333)	// �|�[�g�ԍ�

// IP���N���X��`
void Access(CClient *pClient);
void Join(int nId, CClient *pClient);
void SetPosition(int nId, D3DXVECTOR3 pos, CClient *pClient);
void SetRotation(int nId, D3DXVECTOR3 pos, CClient *pClient);
void SetDamage(int nId, int nDamage, CClient *pClient);
void SetLife(int nId, int nLife, CClient *pClient);
void SetUp(int nId, CClient *pClient);
void Leave(int nId, CClient *pClient);
void Goal(int nId, CClient *pClient);
void Accept(CServer *pServer);
void Send(CServer **ppServer);

// �O���[�o���ϐ��錾
char g_aSendData[MAX_STRING] = {};	// ���M�f�[�^
int g_nSendByte = 0;	// ���M�f�[�^��

//==========================================================
// ���C���֐�
//==========================================================
int main(void)
{
	// �f�[�^�̓ǂݍ���	
	CServer *pServer = NULL;	// �T�[�o�[�̃|�C���^
	CClient *pClient = NULL;	// ����M�p�̃|�C���^
	CClient *pOperation = NULL;	// �^�c�̃|�C���^

	// Winsock�̏���������
	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	// winsock�̏������֐�

	if (nErr != 0)
	{// �������Ɏ��s�����ꍇ
		printf("*** Winsock�̏������Ɏ��s���܂��� ***\n");

		// �L�[���͑҂�
		rewind(stdin);
		getchar();

		return E_FAIL;	// �I��
	}

	// �T�[�o�[�̐���
	pServer = new CServer;

	// �����`�F�b�N
	if (pServer == NULL)
	{
		return E_FAIL;
	}

	// ����������
	if (pServer->Init(DEF_PORT) == false)
	{
		return E_FAIL;
	}

	// �ʃX���b�h�ő��M����
	{
		std::thread th(Send, &pServer);
		th.detach();
	}

	// �ʃX���b�h�Ŏ󂯓���҂�
	{
		std::thread th(Accept, pServer);
		th.detach();
	}

	// �^�c���b�Z�[�W���M
	while (1)
	{
		char aMessage[MAX_STRING] = {};
	}

	if (pServer != NULL)
	{// �g�p����Ă���ꍇ
		pServer->Uninit();

		delete pServer;
		pServer = NULL;
	}

	//Winsock�I������
	WSACleanup();	// WSACleanup�֐� : winsock�̏I������

	printf("*** Enter�L�[�������ďI�����Ă������� ***\n");

	// �L�[���͑҂�
	rewind(stdin);
	getchar();

	return S_OK;
}

//==========================================================
// �}���`�X���b�h��M
//==========================================================
void Access(CClient *pClient)
{
	int nProt = -1;
	int nId = pClient->GetId();

	char aSendData[sizeof(int) * 2] = {};	// ���M�p

	Join(pClient->GetId(), pClient);

	while (1)
	{
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		char aRecvData[MAX_STRING] = {};	// ��M�p
		int nType = COMMAND_TYPE_NONE;
		int nDamage = 0;

		// ��M
		int nRecvbite = pClient->Recv(&aRecvData[0], MAX_STRING);

		memcpy(&nType, &aRecvData[0], sizeof(int));

		if (nRecvbite <= 0)
		{
			Leave(pClient->GetId(), pClient);
			break;
		}
		else
		{
			if (pClient->GetSend() == true)
			{
				continue;
			}

			switch (nType)
			{
			case COMMAND_TYPE_NONE:

				break;
			case COMMAND_TYPE_SETROTATION:

				memcpy(&pos, &aRecvData[sizeof(int)], sizeof(D3DXVECTOR3));
				SetRotation(pClient->GetId(), pos, pClient);
				break;

			case COMMAND_TYPE_SETPOSITION:

				memcpy(&pos, &aRecvData[sizeof(int)], sizeof(D3DXVECTOR3));
				SetPosition(pClient->GetId(), pos, pClient);
				break;

			case COMMAND_TYPE_SETLIFE:

				memcpy(&nDamage, &aRecvData[sizeof(int)], sizeof(nDamage));
				SetLife(pClient->GetId(), nDamage, pClient);
				break;

			case COMMAND_TYPE_GOAL:

				Goal(pClient->GetId(), pClient);
				break;

			case COMMAND_TYPE_START_OK:

				SetUp(pClient->GetId(), pClient);

				break;

			case COMMAND_TYPE_CREATE:

				Join(pClient->GetId(), pClient);

				break;

			case COMMAND_TYPE_DAMAGE:

				memcpy(&nDamage, &aRecvData[sizeof(int)], sizeof(nDamage));
				SetDamage(pClient->GetId(), nDamage, pClient);

				break;

			case COMMAND_TYPE_DELETE:

				Leave(pClient->GetId(), pClient);

				break;

			case COMMAND_TYPE_GETID:

				// protocol��}��
				memcpy(&aSendData[0], &nProt, sizeof(int));
				memcpy(&aSendData[sizeof(int)], &nId, sizeof(int));

				// �v���g�R����}��
				memcpy(&g_aSendData[g_nSendByte], &aSendData[0], sizeof(aSendData));
				g_nSendByte += sizeof(int) * 2;

				break;
			}
		}
	}
}

//==========================================================
// ����
//==========================================================
void Join(int nId, CClient *pClient)
{
	int nProt = -1;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2 + sizeof(int) * 2] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nProt, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nId, sizeof(int));

	nProt = COMMAND_TYPE_CREATE;

	// ID��}��
	memcpy(&aSendData[sizeof(int) * 2], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int) * 3], &nProt, sizeof(int));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2 + sizeof(int) * 2);
}

//==========================================================
// �ގ�
//==========================================================
void Leave(int nId, CClient *pClient)
{
	int nProt = COMMAND_TYPE_DELETE;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));

	// �v���g�R����}��
	pClient->ResetData();
	pClient->SetData(&aSendData[0], sizeof(int) * 2);
	pClient->SetDeath(true);
}

//==========================================================
// �󂯓���҂�
//==========================================================
void Accept(CServer *pServer)
{
	int nId = -1;

	while (1)
	{
		// ����M�p����
		CClient *pClient = new CClient;
		pClient->BindSock(pServer->Accept());
		pClient->SetCliePort(pServer->GetPort());
		pClient->SetIP(pServer->GetIP());

		// ID�ݒ�
		nId++;
		pClient->SetId(nId);

		// �}���`�X���b�h
		std::thread th(Access, pClient);
		th.detach();
	}
}

//==========================================================
// ���W�ݒ�
//==========================================================
void SetPosition(int nId, D3DXVECTOR3 pos, CClient *pClient)
{
	int nProt = COMMAND_TYPE_SETPOSITION;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2 + sizeof(D3DXVECTOR3)] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));
	memcpy(&aSendData[sizeof(int) * 2], &pos, sizeof(D3DXVECTOR3));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2 + sizeof(D3DXVECTOR3));
}

//==========================================================
// �����ݒ�
//==========================================================
void SetRotation(int nId, D3DXVECTOR3 pos, CClient *pClient)
{
	int nProt = COMMAND_TYPE_SETROTATION;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2 + sizeof(D3DXVECTOR3)] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));
	memcpy(&aSendData[sizeof(int) * 2], &pos, sizeof(D3DXVECTOR3));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2 + sizeof(D3DXVECTOR3));
}

//==========================================================
// �_���[�W�ݒ�
//==========================================================
void SetDamage(int nId, int nDamage, CClient *pClient)
{
	int nProt = COMMAND_TYPE_DAMAGE;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2 + sizeof(int)] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));
	memcpy(&aSendData[sizeof(int) * 2], &nDamage, sizeof(int));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2 + sizeof(int));
}

//==========================================================
// �����������M
//==========================================================
void SetUp(int nId, CClient *pClient)
{
	int nProt = COMMAND_TYPE_START_OK;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2);
}

//==========================================================
// �̗͐ݒ�
//==========================================================
void SetLife(int nId, int nLife, CClient *pClient)
{
	int nProt = COMMAND_TYPE_SETLIFE;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2 + sizeof(int)] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));
	memcpy(&aSendData[sizeof(int) * 2], &nLife, sizeof(int));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2 + sizeof(int));
}

//==========================================================
// ���𑗐M
//==========================================================
void Send(CServer **ppServer)
{
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwFPSLastTime;	//�Ō��FPS���v����������
	DWORD dwSecondCount;	// 1�b�J�E���g

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;	//������
	dwExecLastTime = timeGetTime();	//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;	//������
	dwFPSLastTime = timeGetTime();	//���ݎ������擾(�ۑ�)
	dwSecondCount = 0;

	// �T�[�o�[��������܂ŌJ��Ԃ�
	while (*ppServer != NULL)
	{
		dwCurrentTime = timeGetTime();	//���ݎ������擾
		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5�b�o��
			//FPS���v��
			dwFPSLastTime = dwCurrentTime;	//FPS�𑪒肵��������ۑ�
			dwFrameCount = 0;	//�t���[���J�E���g���N���A
		}

		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 120))
		{//60����1�b�o��

			// �f�[�^�̍���
			CClient *pClient = CClient::GetTop();	// �擪���擾

			while (pClient != NULL)
			{// �g�p����Ă��Ȃ���Ԃ܂�

				CClient *pClientNext = pClient->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

				pClient->SetSend(true);	// ���������s�\�ȏ�Ԃɂ���

				memcpy(&g_aSendData[g_nSendByte], pClient->GetSendData(), pClient->GetSendByte());
				g_nSendByte += pClient->GetSendByte();

				if (pClient->GetDeath() == false)
				{
					pClient->ResetData();	// �f�[�^�̃��Z�b�g
					pClient->SetSend(false);	// ���������\�ȏ�Ԃɂ���
				}
				else
				{
					if (pClient != NULL)
					{
						pClient->Uninit();
						delete pClient;
						pClient = NULL;
					}
				}

				pClient = pClientNext;	// ���̃I�u�W�F�N�g�Ɉړ�
			}

			//printf("%d,", g_nSendByte);

			pClient = CClient::GetTop();	// �擪���擾

			while (pClient != NULL)
			{// �g�p����Ă��Ȃ���Ԃ܂�

				CClient *pClientNext = pClient->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

				// ���M
				pClient->Send(&g_aSendData[0], g_nSendByte);

				pClient = pClientNext;	// ���̃I�u�W�F�N�g�Ɉړ�
			}

			// ���M�f�[�^���N���A
			memset(&g_aSendData[0], '\0', sizeof(g_aSendData));
			g_nSendByte = 0;

			dwExecLastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�
			dwFrameCount++;	//�t���[���J�E���g�����Z
			dwSecondCount++;
		}
	}
}

//==========================================================
// �S�[�����M
//==========================================================
void Goal(int nId, CClient *pClient)
{
	int nProt = COMMAND_TYPE_GOAL;	// �v���g�R���ԍ�
	char aSendData[sizeof(int) * 2] = {};	// ���M�p�܂Ƃ߃f�[�^

	// ID��}��
	memcpy(&aSendData[0], &nId, sizeof(int));
	memcpy(&aSendData[sizeof(int)], &nProt, sizeof(int));

	// �v���g�R����}��
	pClient->SetData(&aSendData[0], sizeof(int) * 2);
}