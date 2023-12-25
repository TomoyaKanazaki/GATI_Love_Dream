//==========================================
//
//  �X�R�A�N���X(score.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "score.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "number.h"
#include "object2D.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const int MAX_SCORE = 99999999; // �X�R�A�̍ő�l
	const D3DXVECTOR2 NUM_SIZE = D3DXVECTOR2(80.0f, 120.0f); // �����̃T�C�Y
	const D3DXVECTOR3 NUM_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - NUM_SIZE.x * (NUM_NUM * 0.5f - 0.5f), SCREEN_HEIGHT * 0.5f, 0.0f); // �����̈ʒu
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CScore::m_ScorePoint = 0; // �������g�̃|�C���^

//==========================================
//  �R���X�g���N�^
//==========================================
CScore::CScore()
{
	for (int i = 0; i < NUM_NUM; ++i)
	{
		m_apNumber[i] = nullptr;
	}
}

//==========================================
//  �f�X�g���N�^
//==========================================
CScore::~CScore()
{

}

//==========================================
//  ����������
//==========================================
void CScore::Init()
{
	// ���U���g�̎������������o��
	if (CManager::GetInstance()->GetMode() == CScene::MODE_RESULT)
	{
		// �e�N�X�`�����W���Z�o
		int nCalc = m_ScorePoint;
		int nNum[NUM_NUM];
		for (int i = NUM_NUM - 1; i >= 0; --i)
		{
			nNum[i] = nCalc % 10;
			nCalc /= 10;
		}

		for (int i = 0; i < NUM_NUM; ++i)
		{
			if (m_apNumber[i] == nullptr)
			{
				D3DXVECTOR3 pos = NUM_POS;
				pos.x += NUM_SIZE.x * i + NUM_SIZE.x * 0.5f;
				m_apNumber[i] = CNumber::Create(pos, NUM_SIZE.x, NUM_SIZE.y);
				m_apNumber[i]->GetObject2D()->BindTexture(CTexture::TYPE_SCORE);
				m_apNumber[i]->SetIdx(nNum[i]);
			}
		}
	}

	// �X�R�A��������
	m_ScorePoint = 0;
}

//==========================================
//  �I������
//==========================================
void CScore::Uninit()
{
	// ������j��
	for (int i = 0; i < NUM_NUM; ++i)
	{
		if (m_apNumber[i] != nullptr)
		{
			delete m_apNumber[i];
			m_apNumber[i] = nullptr;
		}
	}

	// �������g�̔j��
	delete this;
}

//==========================================
//  �X�V����
//==========================================
void CScore::Update()
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"�X�R�A : %d", m_ScorePoint
	);

	// �f�o�b�O�L�[
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_UP))
	{
		m_ScorePoint += 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_DOWN))
	{
		m_ScorePoint -= 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_ScorePoint += 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_ScorePoint -= 100;
	}
#endif

	// �X�R�A����
	LimitScore();
}

//==========================================
//  �`�揈��
//==========================================
void CScore::Draw()
{

}

//==========================================
//  �X�R�A�̉��Z
//==========================================
void CScore::AddScorePoint(const int AddPoint)
{
	// �X�R�A�����Z����
	m_ScorePoint += AddPoint;

	// �X�R�A����
	LimitScore();
}

//==========================================
//  ��������
//==========================================
CScore* CScore::Create()
{
	CScore* pScore = new CScore;

	pScore->Init();

	return pScore;
}

//==========================================
//  �X�R�A����
//==========================================
void CScore::LimitScore()
{
	// �X�R�A��␳����
	if (m_ScorePoint < 0) // �X�R�A�����̐��ɂȂ����ꍇ
	{
		// �X�R�A��0�ɕ␳����
		m_ScorePoint = 0;
	}
	else if (m_ScorePoint > MAX_SCORE)
	{
		// �X�R�A���ő�l�ɕ␳����
		m_ScorePoint = MAX_SCORE;
	}
}
