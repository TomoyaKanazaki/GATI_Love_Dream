//==========================================================
//
// �|�[�Y�̏��� [pause.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "texture.h"
#include "manager.h"
#include "camera.h"
#include "timer.h"

//�}�N����`
#define BUTTONWIDTH		(140.0f)		//�|�[�Y��ʃ{�^����
#define BUTTONHEIGHT		(50.0f)			//�|�[�Y��ʃ{�^������
#define BUTTONX			(640.0f)		//�|�[�Y���X���W
#define BUTTONY			(280.0f)		//�|�[�Y���Y���W
#define BUTTONSPACE		(110.0f)		//�|�[�Y��ʏc�X�y�[�X
#define MOVECOLA		(-0.02f)			//���t���[���ς��{�^���̓����x
#define BGSIZE			(270.0f)		//�T�C�Y
#define BGHEIGHT		(270.0f)			//�c��

//===============================================
// �e�N�X�`���t�@�C����
//===============================================
const char* CPause::m_apTexPass[TYPE_MAX]
{
	"data\\TEXTURE\\pause000.png",
	"data\\TEXTURE\\pause001.png",
	"data\\TEXTURE\\pause002.png",
	"data\\TEXTURE\\pause_bg000.png",
};

//===============================================
// �R���X�g���N�^
//===============================================
CPause::CPause()
{
	// �l�̃N���A
	m_SelectMenu = MENU_CONTINUE;
	m_bState = false;
	m_bSelect = false;
	m_fMoveCol_a = 0.0f;
	m_pBg = NULL;

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_aMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aMenu[nCnt].pObject2D = NULL;
	}
	
	m_nStartDeltaTime = 0;
	m_nPauseTimer = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CPause::~CPause()
{

}

//===============================================
// ����������
//===============================================
HRESULT CPause::Init(void)
{
	// �w�i�̐���
	m_pBg = CObject2D::Create(NUM_PRIORITY - 1);

	if (m_pBg != NULL)
	{
		m_pBg->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTexPass[TYPE_BG]));
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.49f, 0.0f));
		m_pBg->SetSize(BGSIZE, BGHEIGHT);
		m_pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pBg->SetType(CObject::TYPE_PAUSE);
	}

	// �I����
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_aMenu[nCnt].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		// 2D�I�u�W�F�N�g�̐���
		m_aMenu[nCnt].pObject2D = CObject2D::Create(NUM_PRIORITY - 1);

		if (m_aMenu[nCnt].pObject2D != NULL)
		{// �������ꂽ
			// �e�N�X�`���̐ݒ�
			m_aMenu[nCnt].pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->Regist(m_apTexPass[nCnt]));
			m_aMenu[nCnt].pObject2D->SetPosition(D3DXVECTOR3(BUTTONX, BUTTONY + nCnt * BUTTONSPACE, 0.0f));
			m_aMenu[nCnt].pObject2D->SetSize(BUTTONWIDTH, BUTTONHEIGHT);
			m_aMenu[nCnt].pObject2D->SetType(CObject::TYPE_PAUSE);
		}
	}

	ColorSet();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_aMenu[nCnt].pObject2D = NULL;
	}

	m_pBg = NULL;
}

//===============================================
// �X�V����
//===============================================
void CPause::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CFade *pFade = CManager::GetInstance()->GetFade();

	if (m_bSelect == true || CManager::GetInstance()->GetFade()->GetState() != CFade::STATE_NONE)
	{// �����ꂽ��Ԃ̏ꍇ
		return;
	}

	if (pInputKey->GetTrigger(DIK_P)|| pInputPad->GetTrigger(CInputPad::BUTTON_START, 0) == true)
	{// ��ړ��L�[�����͂��ꂽ
		m_bState = m_bState ? false : true;

		CObject::TYPE type = CObject::TYPE_NONE;

		if (m_bState == false)
		{
			type = CObject::TYPE_PAUSE;

			if (CManager::GetInstance()->GetScene()->GetTime() != NULL)
			{
				CManager::GetInstance()->GetScene()->GetTime()->SetPauseTimer((int)((timeGetTime() - m_nStartDeltaTime) * 0.1f) + CManager::GetInstance()->GetScene()->GetTime()->GetPauseTimer());
			}
		}

		if (m_pBg != NULL)
		{
			m_pBg->SetType(type);
		}

		// �I����
		for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
		{
			if (m_aMenu[nCnt].pObject2D != NULL)
			{// �������ꂽ
				m_aMenu[nCnt].pObject2D->SetType(type);
			}
		}
	}

	if (m_bState == false)
	{
		m_nStartDeltaTime = timeGetTime();
		return;
	}

	m_aMenu[m_SelectMenu].col.a += m_fMoveCol_a;

	if (m_aMenu[m_SelectMenu].col.a >= 1.0f || m_aMenu[m_SelectMenu].col.a <= 0.3f)
	{// ���S�ɕs�����A�܂��͓���
		m_fMoveCol_a *= -1.0f;	// ���]
	}

	if (pInputKey->GetTrigger(DIK_W) || pInputKey->GetRepeat(DIK_W) || pInputPad->GetTrigger(CInputPad::BUTTON_UP, 0) == true)
	{// ��ړ��L�[�����͂��ꂽ
		m_SelectMenu = (MENU)((m_SelectMenu - 1 + MENU_MAX) % MENU_MAX);
		ColorSet();
	}
	else if (pInputKey->GetTrigger(DIK_S) || pInputKey->GetRepeat(DIK_S) || pInputPad->GetTrigger(CInputPad::BUTTON_DOWN, 0) == true)
	{// ���ړ��L�[�����͂��ꂽ
		
		m_SelectMenu = (MENU)((m_SelectMenu + 1) % MENU_MAX);
		ColorSet();
	}
	else if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) == true)
	{// ����L�[�������ꂽ

		if (pFade == NULL)
		{
			return;
		}
		switch (m_SelectMenu)
		{
		case MENU_CONTINUE:
			m_bState = false;

			if (CManager::GetInstance()->GetScene()->GetTime() != NULL)
			{
				CManager::GetInstance()->GetScene()->GetTime()->SetPauseTimer((int)((timeGetTime() - m_nStartDeltaTime) * 0.1f) + CManager::GetInstance()->GetScene()->GetTime()->GetPauseTimer());
			}
			break;
		case MENU_RETRY:
			//SetFadeMode(FADEMODE_NORMAL);
			pFade->Set(CScene::MODE_GAME);
			break;
		case MENU_QUIT:
			//SetFadeMode(FADEMODE_NORMAL);
			pFade->Set(CScene::MODE_TITLE);
			break;
		}

		if (m_SelectMenu != MENU_CONTINUE)
		{// ���������߂�Ƃ��ȊO
			m_bSelect = true;		//�����ꂽ��ԂɕύX
		}
		else
		{
			CObject::TYPE type = CObject::TYPE_PAUSE;

			if (m_pBg != NULL)
			{
				m_pBg->SetType(type);
			}

			// �I����
			for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
			{
				if (m_aMenu[nCnt].pObject2D != NULL)
				{// �������ꂽ
					m_aMenu[nCnt].pObject2D->SetType(type);
				}
			}
		}
	}

	// �I�����̐F�ύX
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_aMenu[nCnt].pObject2D != NULL)
		{// �g�p����Ă���
			// �F�ݒ�
			m_aMenu[nCnt].pObject2D->SetCol(m_aMenu[nCnt].col);
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CPause::Draw(void)
{
	
}

//===============================================
// �F�ݒ�
//===============================================
void CPause::ColorSet(void)
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_SelectMenu == nCnt)
		{// �I������Ă���
			m_aMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// �I���O
			m_aMenu[nCnt].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}

		if (m_aMenu[nCnt].pObject2D != NULL)
		{// �g�p����Ă���
			// �F�ݒ�
			m_aMenu[nCnt].pObject2D->SetCol(m_aMenu[nCnt].col);
		}
	}

	// �����x�ړ��ʐݒ�
	m_fMoveCol_a = MOVECOLA;
}

//===============================================
// ����
//===============================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	pPause = new CPause;

	if (pPause != NULL)
	{
		pPause->Init();
	}
	else
	{
		return NULL;
	}

	return pPause;
}