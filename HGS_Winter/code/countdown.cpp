//==========================================================
//
// �J�E���g�_�E������ [countdown.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "countdown.h"
#include "number.h"
#include "manager.h"
#include "slow.h"
#include "texture.h"
#include "object2D.h"

// �}�N����`
#define NUM_COUNT	(60)	// �^�C�}�[�J�E���g

//==========================================================
// �R���X�g���N�^
//==========================================================
CCountDown::CCountDown()
{
	m_nNum = 0;
	m_fDownCounter = 0.0f;
	m_bEnd = false;
	m_pObject = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CCountDown::~CCountDown()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CCountDown::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	m_nNum = COUNT_DOWN_NUM;
	m_fDownCounter = NUM_COUNT;

	m_pObject = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.2f);
	m_pObject->SetIdx(m_nNum);

	if (pTexture != nullptr)
	{
		m_pObject->GetObject2D()->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_TIMER)));
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CCountDown::Uninit(void)
{
	if (m_pObject != nullptr)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = nullptr;
	}
}

//==========================================================
// �X�V����
//==========================================================
void CCountDown::Update(void)
{
	if (m_bEnd)
	{
		return;
	}

	m_fDownCounter -= CManager::GetInstance()->GetSlow()->Get();

	if (m_fDownCounter <= 0)
	{
		m_fDownCounter = NUM_COUNT;
		m_nNum--;

		if (m_pObject != nullptr && m_nNum >= 0)
		{
			m_pObject->SetIdx(m_nNum);
		}
	}

	if (m_nNum < 0)
	{
		m_pObject->PolygonDelete();
		m_bEnd = true;
	}
}

//==========================================================
// ����
//==========================================================
CCountDown *CCountDown::Create(void)
{
	CCountDown *pCountDown = new CCountDown;

	if (pCountDown != NULL)
	{
		// ����������
		pCountDown->Init();
	}

	return pCountDown;
}