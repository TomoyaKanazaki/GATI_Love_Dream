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

//==========================================
//  �萔��`
//==========================================
namespace
{
	const int MAX_SCORE = 99999; // �X�R�A�̍ő�l
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CScore* CScore::m_pScore = nullptr; // �������g�̃|�C���^

//==========================================
//  �R���X�g���N�^
//==========================================
CScore::CScore(): m_ScorePoint(0)
{

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
	// �X�R�A��������
	m_ScorePoint = 0;
}

//==========================================
//  �I������
//==========================================
void CScore::Uninit()
{
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
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;
		m_pScore->Init();
	}

	return m_pScore;
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
