//==========================================
//
//  �U���ΏۃN���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "game.h"

// �ÓI�����o�ϐ��錾
CEnemy *CEnemy::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CEnemy *CEnemy::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float DAMAGE = 0.015f; // ���̃q�b�g�Ŏ󂯂�_���[�W��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_Life(0.0f)
{
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
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	return CObjectX::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();

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

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	CObjectX::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority)
{
	CEnemy* pEnemy = nullptr;
	CXFile* pModelFile = CManager::GetInstance()->GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// �����ł����ꍇ
		// ����������
		pEnemy->Init();

		// ���W
		pEnemy->SetPosition(pos);

		// ����
		pEnemy->SetRotation(rot);

		// ��ސݒ�
		pEnemy->SetType(TYPE_MODEL);

		// �ǂݍ��݊m�F
		pEnemy->BindFile(pModelFile->Regist(pFileName));

		// �ύX��}�e���A���J���[�̏�����
		pEnemy->ResetMaterial(pFileName);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy;
}

//==========================================
//  �ʔ���`�F�b�N(override)
//==========================================
bool CEnemy::CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const int nDamage)
{
	// �q�b�g������擾
	if (!CObjectX::CollisionCheck(pos, posOld, move, vtxMin, vtxMax, nDamage))
	{
		return false;
	}

	// �_���[�W���󂯂�
	if (m_Life < 1.0f)
	{
		if (nDamage == 1) {
			m_Life += DAMAGE * 0.85f;

			if (m_Life > 1.0f) {
				m_Life = 1.0f;
			}
			else
			{
				CGame::GetScore()->AddScorePoint(10);
			}
		}
		else if (nDamage == 2) {
			m_Life += DAMAGE * 0.5f;

			if (m_Life > 1.0f) {
				m_Life = 1.0f;
			}
		}

		SetLife(m_Life);

		// �}�e���A���ύX�t���O���I���ɂ���
		ChangeCol(true);
	}

	// �q�b�g�ŕԂ�
	return true;
}
