//===============================================
//
// �`���[�g���A����ʂ̊Ǘ����� [tutorial.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "timer.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "fileload.h"
#include "slow.h"
#include "player.h"
#include "objectX.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "result.h"
#include "editor.h"
#include "sound.h"
#include "game.h"
#include "debugproc.h"

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(60 * 3)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A
#define MAP_SIZE	(100.0f)	// �}�b�v�T�C�Y
#define STARTSET_NUMENEMY	(30)	// �J�n���ɔz�u����G�̐�
#define MAX_TIME	(60 * 20)	// �ő厞��

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CTutorial::m_pScore = NULL;		// �X�R�A�̃|�C���^
CSlow *CTutorial::m_pSlow = NULL;		// �X���[��Ԃւ̃|�C���^
CMeshField *CTutorial::m_pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CTutorial::CTutorial()
{
	// �l�̃N���A
	m_pTime = NULL;
	m_pEnemyManager = NULL;
	m_pPlayer = NULL;
	m_pFileLoad = NULL;
	m_pCarManager = NULL;
	m_pMeshDome = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTutorial::~CTutorial()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTutorial::Init(void)
{
	CObject2D *p = CObject2D::Create(6);
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	p->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\tutorial.png"));
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	m_pScore = NULL;		// �X�R�A�̃|�C���^
	m_pTime = NULL;		// �^�C���̃|�C���^
	m_pPlayer = NULL;	// �v���C���[�̃|�C���^
	m_pMeshField = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
}

//===============================================
// �X�V����
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
		CGame::SetState(CGame::STATE_TIMEATTACK);
	}

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	CScene::Draw();
}

//===================================================
// �X�R�A�̎擾
//===================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CTime *CTutorial::GetTime(void)
{
	return m_pTime;
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// �X���[���̎擾
//===================================================
CSlow *CTutorial::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// ���b�V���t�B�[���h�̎擾
//===================================================
CMeshField *CTutorial::GetMeshField(void)
{
	return m_pMeshField;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �ǂݍ��݃f�[�^���Z�b�g
//===================================================
void CTutorial::DataReset(void)
{
	// �I��
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	// �O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}
}
