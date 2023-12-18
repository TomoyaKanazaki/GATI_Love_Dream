//========================================
//
//�}�l�[�W���[[manager.cp]
//Author�F�X��x��
//
//========================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "game.h"

//========================================
//�ÓI�����o�ϐ�
//========================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputPad *CManager::m_pInputPad = nullptr;
CScene *CManager::m_pScene = nullptr;
CTexture *CManager::m_pTexture = nullptr;
CDebugProc *CManager::m_pDebugProc = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CManager *CManager::m_pManager = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CManager::CManager(void) : 
	m_nCnt(0),	//�����J�ڂ̃J�E���^�[
	m_state(0),	//��ԕύX
	m_NowScene(CScene::MODE_NONE)	//���݂̃V�[��
{//�l�N���A
}

//========================================
//�f�X�g���N�^
//========================================
CManager::~CManager(void)
{
}

//========================================
//������
//========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == nullptr)
	{//g_pRenderer��nullptr�̎�
		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�L�[�{�[�h�̐���
	if (m_pInputKeyboard == nullptr)
	{//m_pInputKeyboard��nullptr�̎�
		m_pInputKeyboard = new CInputKeyboard;
	}

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�R���g���[���[�̐���
	if (m_pInputPad == nullptr)
	{//m_pInputKeyboard��nullptr�̎�
		m_pInputPad = new CInputPad;
	}

	//�R���g���[���[�̏���������
	if (FAILED(m_pInputPad->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return -1;
	}

	//�J��������
	if (m_pCamera == nullptr)
	{//m_pCamera��nullptr�̎�
		m_pCamera = new CCamera;
	}

	//�J�����̏���������
	if (FAILED(m_pCamera->Init()))
	{//���������������s�����ꍇ
		return -1;
	}

	//debugproc�̐���
	if (m_pDebugProc == nullptr)
	{//m_pDebugProc��nullptr�̎�
		m_pDebugProc = new CDebugProc;

		//������
		m_pDebugProc->Init();
	}

	//�e�N�X�`������
	m_pTexture = new CTexture;

	//���[�h�ݒ�
	SetMode(CScene::MODE_TITLE);

	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
	
	//�����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�R���g���[���[�̔j��
	if (m_pInputPad != nullptr)
	{
		m_pInputPad->Uninit();
		delete m_pInputPad;
		m_pInputPad = nullptr;
	}

	//�J�����̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{//debugproc�̔j��
		m_pDebugProc->Uninit();
	}

	if (m_pTexture != nullptr)
	{//�e�N�X�`���j��
		m_pTexture->Unload();

		//nullptr�ɂ���
		m_pTexture = nullptr;
	}
}

//========================================
//�X�V
//========================================
void CManager::Update(void)
{
	if (m_pRenderer != nullptr)
	{//g_pRenderer��nullptr�̎�
		//�X�V����
		m_pRenderer->Update();
	}

	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//�R���g���[���[�̍X�V
	if (m_pInputPad != nullptr)
	{
		m_pInputPad->Update();
	}

	//�J�����̍X�V
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//DebugPro�̍X�V
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Update();
	}
	//�V�[���̍X�V
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

//========================================
//�`��
//========================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{//g_pRenderer��nullptr�̎�
		//�`�揈��
		m_pRenderer->Draw();
	}
}

//========================================
//���[�h�ݒ�
//========================================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{//���[�h�j��
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�S�Ĕj��
	CObject::ReleaseAll();

	//���[�h����
	m_pScene = CScene::Create(mode);
}

//========================================
//�C���X�^���X�擾
//========================================
CManager *CManager::GetInstance()
{
	if (m_pManager == nullptr)
	{//�C���X�^���X����
		return m_pManager = new CManager;
	}
	else
	{//�|�C���^��Ԃ�
		return m_pManager;
	}
}

//========================================
//�R���X�g���N�^
//========================================
CScene::CScene() : 
	m_pVtxBuff(nullptr),	//���_�����i�[
	m_nIdxTexture(0),		//�e�N�X�`���ԍ�
	m_mode(MODE_NONE)		//���[�h
{//�l�N���A
}

//========================================
//�f�X�g���N�^
//========================================
CScene::~CScene()
{
}

//========================================
//����
//========================================
CScene *CScene::Create(int nMode)
{
	//CScene�̃|�C���^
	CScene *pScene = nullptr;

	if (pScene == nullptr)
	{
		switch (nMode)
		{
		case MODE_TITLE:
			//�^�C�g���V�[������
			pScene = CTitle::Create();
			break;

		case MODE_TUTORIAL:
			//�^�C�g���V�[������
			pScene = CTutorial::Create();
			break;

		case MODE_GAME:
			//�^�C�g���V�[������
			pScene = CGame::Create();
			break;

		case MODE_RESULT:
			//���U���g�V�[��
			pScene = CResult::Create();
			break;
		}

		//������
		pScene->Init();
	}

	//�|�C���^��Ԃ�
	return pScene;
}
 