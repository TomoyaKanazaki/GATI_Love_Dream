//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "objectX.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "result.h"
#include "sound.h"
#include "fileload.h"
#include "debugproc.h"
#include "player.h"
#include "editor.h"
#include "gimmick_move.h"
#include "gimmick_rotate.h"
#include "gimmick_fish.h"
#include "time.h"
#include "meshdome.h"
#include "gimmick_button.h"
#include "gimmick_air.h"
#include "gimmick_door.h"
#include "countdown.h"
#include "tcp_client.h"
#include <thread>
#include "protocol_online.h"
#include "object2D.h"

// �O���[�o��

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(60 * 4)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A
#define MAP_SIZE	(100.0f)	// �}�b�v�T�C�Y
#define STARTSET_NUMENEMY	(3)	// �J�n���ɔz�u����G�̐�
#define MORNING_TIME	(60 * 6)	// �����I������
#define AM_COMRUSH	(60 * 9)	// �ʋ΃��b�V��
#define RELAX_TIME	(60 * 11)	// �����b�N�X�^�C��
#define NOON_TIME	(60 * 12.5)	// ���x��
#define EVENT_RUSH	(60 * 15.5)	// �C�x���g
#define PM_RELAX_TIME	(60 * 16)	// �A��J�n����
#define PM_GOHOME_RUSH	(60 * 19)	// �A��b�V��
#define MAX_TIME	(60 * 20 + 10)	// �ő厞��
#define SPEED_UP	(30.0f)
#define DEF_PORT	(22333)	// �|�[�g�ԍ�
#define MAX_STRING	(2048)
#define ADDRESSFILE	"data\\TXT\\address.txt"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CGame::STATE CGame::m_state = CGame::STATE_MULTI;	// ���

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame()
{
	// �l�̃N���A
	m_pMapCamera = NULL;
	m_pTime = NULL;
	m_pPlayer = NULL;
	m_pFileLoad = NULL;
	m_pEditor = NULL;
	m_pMeshDome = NULL;
	m_pStart = NULL;
	m_pPause = NULL;
	m_pScore = NULL;
	m_pClient = NULL;
	m_pCountDown = NULL;
	m_nSledCnt = 0;
	m_bEnd = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{

}

//===============================================
// ����������
//===============================================
HRESULT CGame::Init(void)
{
	memset(&m_aAddress[0], '\0', sizeof(m_aAddress));
	int nErr = WSAStartup(WINSOCK_VERSION, &m_wsaData);	// winsock�̏������֐�

	if (nErr != 0)
	{// �������Ɏ��s�����ꍇ
		
	}

	// �O���t�@�C���ǂݍ��݂̐���
	if (nullptr == m_pFileLoad)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}

	// �G�f�B�^�[�̐���
	if (nullptr == m_pEditor)
	{
		m_pEditor = new CEditor;
		m_pEditor->Init();
	}

	// �}�b�v�̐���
	CObject2D *pObj = CObject2D::Create();
	pObj->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\map.png"));
	pObj->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.95f, 0.0f));
	pObj->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.05f);

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pPlayer->SetUp(true);
	m_pPlayer->SetType(CPlayer::TYPE_SEND);
	m_pCountDown = CCountDown::Create();

	m_pMeshDome = CMeshDome::Create(D3DXVECTOR3(-8000.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f, 10.0f, 10, 10);

	if (m_state == STATE_MULTI)
	{// �}���`�̏ꍇ

		m_pClient = new CClient;
		AddressLoad(&m_aAddress[0]);

		if (m_pClient->Init(&m_aAddress[0], DEF_PORT))
		{// �����ڑ�����
			// �}���`�X���b�h
			std::thread th(&CGame::Online, this);
			th.detach();

			m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.075f, 0.0f));
			m_pTime->Set(0);
			m_pTime->SetMode(CTime::MODE_PLUS);
		}
		else
		{// �ڑ����s

			// �^�C���A�^�b�N�ɕύX
			m_state = STATE_TIMEATTACK;
			m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.075f, 0.0f));
			m_pTime->Set(180 * 100);
		}
	}
	else
	{
		m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.075f, 0.0f));
		m_pTime->Set(180 * 100);
	}
	
	// �M�~�b�N�ݒu
	GimmickSet();

	//�J����������
	{
		CManager::GetInstance()->GetCamera()->Init();
		D3DVIEWPORT9 viewport;
		//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
	}

	// �|�[�Y�̐���
	if (nullptr == m_pPause)
	{
		m_pPause = CPause::Create();
	}

	// �X�|�b�g���C�g���I��
	CManager::GetInstance()->GetLight()->EnablePointLight(true);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
	m_pPlayer = nullptr;
	m_bEnd = true;

	while (1)
	{
		OnlineEnd();
		if (m_nSledCnt <= 0)
		{
			break;
		}
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = NULL;
	}

	if (m_pClient != NULL)
	{
		m_pClient->Uninit();
		delete m_pClient;
		m_pClient = NULL;
	}

	if (m_pCountDown != nullptr)
	{
		m_pCountDown->Uninit();
		delete m_pCountDown;
		m_pCountDown = nullptr;
	}

	//Winsock�I������
	WSACleanup();	// WSACleanup�֐� : winsock�̏I������

}

//===============================================
// �X�V����
//===============================================
void CGame::Update(void)
{
	if (m_pCountDown != nullptr)
	{
		CScene::Update();

		int nSetUp = 0;

		CPlayer *pPlayer = NULL;		// �擪���擾
		CPlayer *pPlayerNext = NULL;	// ����ێ�
		pPlayer = CPlayer::GetTop();	// �擪���擾

		while (pPlayer != NULL)
		{// �g�p����Ă���ԌJ��Ԃ�
			pPlayerNext = pPlayer->GetNext();	// ����ێ�

			if (pPlayer->GetSetUp() == true)
			{
				nSetUp++;
			}

			pPlayer = pPlayerNext;	// ���Ɉړ�
		}

		SendSetUp();

		if ((m_state == STATE_TIMEATTACK && m_pPlayer->GetSetUp() == true) || (m_state == STATE_MULTI && nSetUp >= 2 && CPlayer::GetNum() >= 2))
		{
			if (!m_pCountDown->GetEnd())
			{
				m_pCountDown->Update();
				return;
			}
			else
			{
				m_pPlayer->SetType(CPlayer::TYPE_ACTIVE);
				if (m_pTime != nullptr)
				{
					m_pTime->SetActive(true);
				}
				if (m_pCountDown != nullptr)
				{
					m_pCountDown->Uninit();
					delete m_pCountDown;
					m_pCountDown = nullptr;
				}
			}
		}
		else
		{
			return;
		}
	}

	// �|�[�Y
	if (m_pPause != NULL)
	{
		m_pPause->Update();

		if (m_pPause->GetEnable() == true)
		{
			if (m_pPause->GetSelect() == true)
			{
				CManager::GetInstance()->GetFade()->Update();
			}
			return;
		}
	}

#if _DEBUG

	if (m_pEditor != NULL)
	{
		m_pEditor->Update();

		if (m_pEditor->GetActive())
		{
			return;
		}
	}

#endif

	if (m_pTime != NULL)
	{
		m_pTime->Update();

		if (m_pTime->GetNum() <= 0 && m_state == STATE_TIMEATTACK)
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
			CResult::SetScore(m_pTime->GetNum());
		}
	}

	// �S�[������
	if (m_pPlayer != NULL)
	{
		if (m_pPlayer->GetPosition().x < -15000.0f)
		{
			// �}���`�v���C
			if (m_state == STATE_MULTI && CResult::GetType() == CResult::TYPE_MAX)
			{
				int nSetUp = 0;

				CPlayer *pPlayer = NULL;		// �擪���擾
				CPlayer *pPlayerNext = NULL;	// ����ێ�
				pPlayer = CPlayer::GetTop();	// �擪���擾

				while (pPlayer != NULL)
				{// �g�p����Ă���ԌJ��Ԃ�
					pPlayerNext = pPlayer->GetNext();	// ����ێ�

					if (pPlayer->GetGoal())
					{
						nSetUp++;
					}

					pPlayer = pPlayerNext;	// ���Ɉړ�
				}

				if (nSetUp == 0)
				{
					CResult::SetType(CResult::TYPE_MULTI_WIN);
				}
				else
				{
					CResult::SetType(CResult::TYPE_MULTI_LOSE);
				}
			}

			m_pPlayer->SetGoal(true);
			if (m_pTime != nullptr)
			{
				CResult::SetScore(m_pTime->GetNum());
				m_pTime->SetActive(false);
			}
			SendGoal();
		}
	}
	{
		int nSetUp = 0;

		CPlayer *pPlayer = NULL;		// �擪���擾
		CPlayer *pPlayerNext = NULL;	// ����ێ�
		pPlayer = CPlayer::GetTop();	// �擪���擾

		while (pPlayer != NULL)
		{// �g�p����Ă���ԌJ��Ԃ�
			pPlayerNext = pPlayer->GetNext();	// ����ێ�

			if (pPlayer->GetGoal())
			{
				nSetUp++;
			}

			pPlayer = pPlayerNext;	// ���Ɉړ�
		}

		SendSetUp();

		if ((m_state == STATE_TIMEATTACK && m_pPlayer->GetGoal() == true) || (m_state == STATE_MULTI && nSetUp >= 2 && CPlayer::GetNum() >= 2))
		{
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
			m_bEnd = true;
		}
	}

	if (!m_bEnd)
	{
		// �X�V����
		CScene::Update();
	}
	else
	{
		CManager::GetInstance()->GetFade()->Update();
	}
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
	CScene::Draw();

	// �|�[�Y
	if (m_pPause != NULL)
	{
		m_pPause->Draw();
	}
}

//===================================================
// �X�R�A�̎擾
//===================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �|�[�Y�̎擾
//===================================================
CPause *CGame::GetPause(void)
{
	return m_pPause;
}

//===================================================
// �G�f�B�^�[���̎擾
//===================================================
CEditor *CGame::GetEditor(void)
{
	return m_pEditor;
}

//===================================================
// �M�~�b�N�̐ݒu
//===================================================
void CGame::GimmickSet(void)
{
	// �ړ�
	CGimmickMove *pMove = CGimmickMove::Create(D3DXVECTOR3(-7300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 2.0f), 300.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-7800.0f, 0.0f, -1600.0f), D3DXVECTOR3(0.0f, 0.0f, -3.0f), 120.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-8000.0f, 0.0f, -1980.0f), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 60.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-8400.0f, 0.0f, -1500.0f), D3DXVECTOR3(4.0f, 0.0f, 0.0f), 100.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-9400.0f, 0.0f, -2100.0f), D3DXVECTOR3(-4.0f, 0.0f, 4.0f), 150.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-9400.0f, 0.0f, -1400.0f), D3DXVECTOR3(-6.0f, 0.0f, -6.0f), 100.0f);
	pMove = CGimmickMove::Create(D3DXVECTOR3(-14100.0f, 0.0f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, -3.0f), 100.0f);

	// ��]
	CGimmickRotate *p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-5625.0f, 0.0f, -350.0f));
	p->SetRotate(p->GetRotate() * 1.0f);

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-6900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * 0.8f);
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.1f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-7900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * -1.0f);

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-8900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * 1.2f);
	p->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-8900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * 1.2f);
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-9900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * -1.5f);
	p->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-9900.0f, 0.0f, -850.0f));
	p->SetRotate(p->GetRotate() * -1.5f);
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-12850.0f, 0.0f, -2125.0f));
	p->SetRotate(p->GetRotate() * 1.0f);
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	p = CGimmickRotate::Create();
	p->SetPosition(D3DXVECTOR3(-13550.0f, 0.0f, 960.0f));
	p->SetRotate(p->GetRotate() * 1.0f);
	p->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// ��
	CGimmickFish *pFish = CGimmickFish::Create();
	pFish->SetPosition(D3DXVECTOR3(-850.0f, -750.0f, 150.0f));
	pFish->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	pFish = CGimmickFish::Create();
	pFish->SetPosition(D3DXVECTOR3(-3950.0f, -750.0f, -650.0f));

	pFish = CGimmickFish::Create();
	pFish->SetPosition(D3DXVECTOR3(-8800.0f, -750.0f, -1750.0f));

	pFish = CGimmickFish::Create();
	pFish->SetPosition(D3DXVECTOR3(-14400.0f, -750.0f, 650.0f));
	pFish->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	pFish = CGimmickFish::Create();
	pFish->SetPosition(D3DXVECTOR3(-12700.0f, -750.0f, 275.0f));
	pFish->SetRotation(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �{�^���z�u
	CGimmickButton *pButton = CGimmickButton::Create();
	pButton->SetPosition(D3DXVECTOR3(-14640.0f, 0.0f, -2050.0f));
	pButton->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	pButton->SetGoalPos(D3DXVECTOR3(-14680.0f, 0.0f, -2050.0f));
	pButton->SetType(CGimmickButton::TYPE_REVERSE);

	pButton = CGimmickButton::Create();
	pButton->SetPosition(D3DXVECTOR3(-14400.0f, 0.0f, 110.0f));
	pButton->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	pButton->SetGoalPos(D3DXVECTOR3(-14400.0f, 0.0f, 70.0f));
	pButton->SetType(CGimmickButton::TYPE_DOOR);

	// �h�A�z�u
	CGimmickDoor *pDoor = CGimmickDoor::Create();
	pDoor->SetPosition(D3DXVECTOR3(-13810.0f, 0.0f, -750.0f));
	pDoor->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// ���z�u
	CGimmickAir *pAir = CGimmickAir::Create();
	pAir->SetPosition(D3DXVECTOR3(-13525.0f, 80.0f, -800.0f));
	pAir->SetMove(D3DXVECTOR3(0.0f, 0.0f, -0.5f));
	pAir->SetHeight(750.0f);
	pAir->SetWidth(250.0f);

	pAir = CGimmickAir::Create();
	pAir->SetPosition(D3DXVECTOR3(-12800.0f, 80.0f, -1325.0f));
	pAir->SetMove(D3DXVECTOR3(0.5f, 0.0f, 0.0f));
	pAir->SetHeight(225.0f);
	pAir->SetWidth(950.0f);

	pAir = CGimmickAir::Create();
	pAir->SetPosition(D3DXVECTOR3(-12800.0f, 80.0f, -275.0f));
	pAir->SetMove(D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	pAir->SetHeight(225.0f);
	pAir->SetWidth(950.0f);

	pAir = CGimmickAir::Create();
	pAir->SetPosition(D3DXVECTOR3(-14000.0f, 80.0f, -1875.0f));
	pAir->SetMove(D3DXVECTOR3(0.75f, 0.0f, 0.0f));
	pAir->SetHeight(225.0f);
	pAir->SetWidth(250.0f);
	pAir->SetRevease(true);

	pAir = CGimmickAir::Create();
	pAir->SetPosition(D3DXVECTOR3(-13935.0f, 80.0f, 265.0f));
	pAir->SetMove(D3DXVECTOR3(0.85f, 0.0f, 0.0f));
	pAir->SetHeight(205.0f);
	pAir->SetWidth(185.0f);
	pAir->SetRevease(true);
}

//===================================================
// �I�����C���ʐM
//===================================================
void CGame::Online(void)
{
	m_nSledCnt = 1;
	while (1)
	{
		if (m_pPlayer == NULL || m_bEnd == true)
		{
			break;
		}

		char aRecvData[MAX_STRING] = {};	// ��M�p

		// ��M
		int nRecvByte = m_pClient->Recv(&aRecvData[0], MAX_STRING);

		// �}���`�X���b�h
		std::thread th(&CGame::ByteCheck, this, &aRecvData[0], nRecvByte);
		th.detach();
	}

	m_nSledCnt--;
}

//===================================================
// ��M�m�F
//===================================================
void CGame::ByteCheck(char *pRecvData, int nRecvByte)
{
	m_mutex.lock();
	m_nSledCnt++;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	int nType = COMMAND_TYPE_NONE;	// �R�}���h�ԍ�
	int nId = -1;		// ID
	int nByte = 0;	// �o�C�g��
	int nDamage = 0;	// �_���[�W��
	CPlayer *pPlayer = NULL;		// �擪���擾
	CPlayer *pPlayerNext = NULL;	// ����ێ�

	if (nRecvByte <= 0)
	{
		m_nSledCnt--;
		m_mutex.unlock();
		return;
	}

	int nSetUp = 0;
	pPlayer = CPlayer::GetTop();	// �擪���擾

	while (pPlayer != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		pPlayerNext = pPlayer->GetNext();	// ����ێ�

		if (pPlayer->GetGoal())
		{
			nSetUp++;
		}

		pPlayer = pPlayerNext;	// ���Ɉړ�
	}

	if (nSetUp >= 2)
	{
		m_nSledCnt--;
		m_mutex.unlock();
		return;
	}

	// �I�[�����܂Ŋm�F����
	while (nByte < nRecvByte)
	{
		bool bIn = false;	// ���ɂ��邩�ǂ���
		memcpy(&nId, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		// �R�}���h�擾
		memcpy(&nType, &pRecvData[nByte], sizeof(int));
		nByte += sizeof(int);

		if (nId != -1)
		{
			// �R�}���h���Ƃɕ�����
			switch (nType)
			{

			case COMMAND_TYPE_SETPOSITION:

				memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
				nByte += sizeof(D3DXVECTOR3);
				break;

			case COMMAND_TYPE_SETROTATION:

				memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
				nByte += sizeof(D3DXVECTOR3);
				break;

			case COMMAND_TYPE_SETLIFE:

				memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
				nByte += sizeof(int);
				break;

			case COMMAND_TYPE_START_OK:

				break;

			case COMMAND_TYPE_CREATE:
				break;

			case COMMAND_TYPE_DAMAGE:

				memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
				nByte += sizeof(int);
				break;

			case COMMAND_TYPE_DELETE:
				break;

			case COMMAND_TYPE_GETID:
				break;
			}
		}

		if (m_pPlayer == NULL)
		{
			m_nSledCnt--;
			m_mutex.unlock();
			return;
		}

		if (nId != -1 && m_pPlayer->GetId() != -1)
		{// ID����M�ł���

			pPlayer = CPlayer::GetTop();	// �擪���擾

			while (pPlayer != NULL)
			{// �g�p����Ă���ԌJ��Ԃ�
				pPlayerNext = pPlayer->GetNext();	// ����ێ�

				if (nId == pPlayer->GetId() && m_pPlayer->GetId() != nId)
				{// �����ȊO�����삵�Ă��Ȃ�

				 // �R�}���h���Ƃɕ�����
					switch (nType)
					{
					case COMMAND_TYPE_SETPOSITION:

						pPlayer->SetDiffPosition(pos);
						break;

					case COMMAND_TYPE_SETROTATION:

						pPlayer->SetRotation(pos);
						break;

					case COMMAND_TYPE_SETLIFE:

						pPlayer->SetLife(nDamage);
						break;

					case COMMAND_TYPE_START_OK:

						pPlayer->SetUp(true);
						break;

					case COMMAND_TYPE_CREATE:

						break;

					case COMMAND_TYPE_DAMAGE:

						pPlayer->Damage(nDamage);
						break;

					case COMMAND_TYPE_GOAL:

						if (m_pPlayer != NULL)
						{
							if (!m_pPlayer->GetGoal())
							{
								pPlayer->SetGoal(true);
							}
							else
							{
								pPlayer->SetGoalValue(true);
							}
						}

						break;

					case COMMAND_TYPE_DELETE:

						pPlayer->Uninit();
						break;

					case COMMAND_TYPE_GETID:

						break;
					}

					bIn = true;	// �����Ԃɂ���
					break;
				}
				else if (nId == pPlayer->GetId() && m_pPlayer->GetId() == nId)
				{// �����ȊO������L����

					bIn = true;	// �����Ԃɂ���
					break;
				}

				pPlayer = pPlayerNext;	// ���Ɉړ�
			}

			if (bIn == false && m_pPlayer->GetId() != -1 && nType > COMMAND_TYPE_NONE && nType < COMMAND_TYPE_MAX)
			{// �܂����݂��Ă��Ȃ��ꍇ
				pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pPlayer->BindId(nId);
				pPlayer->SetType(CPlayer::TYPE_NONE);
			}
		}
		else if (nId == -1 && m_pPlayer->GetId() == -1)
		{// ID����M�ł��Ă��Ȃ����������g��ID�����݂��Ă��Ȃ�
			nId = nType;

			// ������ID��ݒ�
			m_pPlayer->BindId(nId);

			break;
		}
	}

	m_nSledCnt--;
	m_mutex.unlock();
}

//===================================================
// ���W���M
//===================================================
void CGame::SendPosition(const D3DXVECTOR3& pos)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETPOSITION;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���W��}��
		memcpy(&aSendData[sizeof(int)], &pos, sizeof(D3DXVECTOR3));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// �������M
//===================================================
void CGame::SendRotation(const D3DXVECTOR3& rot)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETROTATION;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���W��}��
		memcpy(&aSendData[sizeof(int)], &rot, sizeof(D3DXVECTOR3));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
	}
}

//===================================================
// �_���[�W���M
//===================================================
void CGame::SendDamage(const int nDamage)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_DAMAGE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// �_���[�W��}��
		memcpy(&aSendData[sizeof(int)], &nDamage, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// �̗͑��M
//===================================================
void CGame::SendLife(const int nLife)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_SETLIFE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// �_���[�W��}��
		memcpy(&aSendData[sizeof(int)], &nLife, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
	}
}

//===================================================
// �I�����M
//===================================================
void CGame::OnlineEnd(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_DELETE;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CGame::SendSetUp(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_START_OK;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===============================================
// �S�[�����M
//===============================================
void CGame::SendGoal(void)
{
	if (m_pClient != nullptr)
	{
		char aSendData[MAX_STRING] = {};	// ���M�p
		int nProt = COMMAND_TYPE_GOAL;

		// protocol��}��
		memcpy(&aSendData[0], &nProt, sizeof(int));

		// ���M
		m_pClient->Send(&aSendData[0], sizeof(int));
	}
}

//===================================================
// �A�h���X�ǂݍ���
//===================================================
void CGame::AddressLoad(char *pAddrss)
{
	FILE *pFile;	// �t�@�C���ւ̃|�C���^

	pFile = fopen(ADDRESSFILE, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		
		//�e�L�X�g�ǂݍ���
		fscanf(pFile, "%s", pAddrss);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		return;
	}
}
