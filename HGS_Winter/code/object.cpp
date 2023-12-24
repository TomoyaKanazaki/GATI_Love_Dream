//===============================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"

// �}�N����`
#define DEFAULT_PRIORITY	(3)	// ��{�̗D�揇��

//===============================================
// �ÓI�����o�ϐ��錾
//===============================================
CObject *CObject::m_apTop[NUM_PRIORITY] = {};	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CObject *CObject::m_apCur[NUM_PRIORITY] = {};	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CObject::m_nNumAll = 0;
int CObject::m_nItemNumAll = 0;
int CObject::m_nNumEnemyAll = 0;
int CObject::m_aPriNumAll[NUM_PRIORITY] = {};

//===============================================
// �R���X�g���N�^
//===============================================
//CObject::CObject()
//{
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObject[DEFAULT_PRIORITY][nCntObject] == NULL)
//		{// �g�p����Ă��Ȃ��ꍇ
//			m_apObject[DEFAULT_PRIORITY][nCntObject] = this;	// �������g����
//			m_nID = nCntObject;	// �������g��ID���
//			m_nNumAll++;			// �������J�E���g�A�b�v
//			m_nPriority = DEFAULT_PRIORITY;
//			m_type = TYPE_NONE;	// ��ނ����Z�b�g
//			break;
//		}
//	}
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CObject::CObject(int nPriority)
{
	// �l�̃N���A
	m_pNext = NULL;
	m_pPrev = NULL;
	m_bDeath = false;
	m_bDraw = true;

	// �D�揇�ʂ̊m�F
	if (nPriority < 0)
	{
		nPriority = 0;
	}
	else if (nPriority >= NUM_PRIORITY)
	{
		nPriority = NUM_PRIORITY - 1;
	}

	m_nPriority = nPriority;	// �ݒ�

	// �������g�����X�g�ɒǉ�
	if (m_apTop[nPriority] != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_apCur[nPriority]->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_apCur[nPriority];
		m_apCur[nPriority] = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_apTop[nPriority] = this;	// �������g���擪�ɂȂ�
		m_apCur[nPriority] = this;	// �������g���Ō���ɂȂ�
	}

	m_aPriNumAll[nPriority]++;
	m_nNumAll++;
}

//===============================================
// �f�X�g���N�^
//===============================================
CObject::~CObject()
{
	
}

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// ����������
//===============================================
HRESULT CObject::Init(void)
{

}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �I������
//===============================================
void CObject::Uninit(void)
{
	
}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �X�V����
//===============================================
void CObject::Update(void)
{

}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �`�揈��
//===============================================
void CObject::Draw(void)
{

}
#endif

//===============================================
// �S�ẴI�u�W�F�N�g�̔p��
//===============================================
void CObject::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObject = m_apTop[nCntPri];	// �擪���擾
		
		while(pObject != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CObject *pObjectNext = pObject->m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			// �I������
			pObject->Uninit();

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	// ���S�t���O���`�F�b�N
	DeathCheck();
}

//===============================================
// �S�ẴI�u�W�F�N�g�̍X�V
//===============================================
void CObject::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObject = m_apTop[nCntPri];	// �擪���擾

		while (pObject != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�
			CObject *pObjectNext = pObject->m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObject->m_bDeath == false)
			{// ���S���Ă��Ȃ��ꍇ
				// �X�V����
				pObject->Update();
			}

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	// ���S�t���O���`�F�b�N
	DeathCheck();
}

//===============================================
// �S�ẴI�u�W�F�N�g�̕`��
//===============================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CCamera *pMapCamera = CManager::GetInstance()->GetScene()->GetMapCamera();

	if (pMapCamera != NULL)
	{
		pMapCamera->SetCamera();
	}

	if (pCamera != NULL)
	{// �g�p����Ă���ꍇ
		pCamera->SetCamera();
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObject = m_apTop[nCntPri];	// �擪���擾

		while (pObject != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�
			CObject *pObjectNext = pObject->m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObject->m_type != TYPE_PAUSE && pObject->m_type != TYPE_MAP && pObject->m_bDraw == true && pObject->m_bDeath == false)
			{// �|�[�Y��ʈȊO
				// �`�揈��
				pObject->Draw();
			}
			pObject = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}
}

//===============================================
// �I�u�W�F�N�g�̔p��
//===============================================
void CObject::Release(void)
{
	// ���S��Ԃɂ���
	m_bDeath = true;
}

//===============================================
// �^�C�v�̐ݒ�
//===============================================
void CObject::SetType(const TYPE type)
{
	if (m_type != type)
	{
		if (type == TYPE_MODEL && m_type != TYPE_MODEL)
		{
			m_nItemNumAll++;
		}
		else if (type == TYPE_ENEMY && m_type != TYPE_ENEMY)
		{
			m_nNumEnemyAll++;
		}

		if (type != TYPE_MODEL && m_type == TYPE_MODEL)
		{
			m_nItemNumAll--;
		}
		else if (type != TYPE_ENEMY && m_type == TYPE_ENEMY)
		{
			m_nNumEnemyAll--;
		}
	}

	m_type = type;	// ��ނ�ݒ�
}

//===============================================
// ���S�t���O���`�F�b�N
//===============================================
void CObject::DeathCheck(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObject = m_apTop[nCntPri];	// �擪���擾

		while (pObject != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�
			CObject *pObjectNext = pObject->m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObject->m_bDeath == true)
			{
				TYPE type = pObject->m_type;

				// ���X�g���玩�����g���폜����
				if (m_apTop[nCntPri] == pObject)
				{// ���g���擪
					if (pObject->m_pNext != NULL)
					{// �������݂��Ă���
						m_apTop[nCntPri] = pObject->m_pNext;	// ����擪�ɂ���
						pObject->m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
					}
					else
					{// ���݂��Ă��Ȃ�
						m_apTop[nCntPri] = NULL;	// �擪���Ȃ���Ԃɂ���
						m_apCur[nCntPri] = NULL;	// �Ō�����Ȃ���Ԃɂ���
					}
				}
				else if (m_apCur[nCntPri] == pObject)
				{// ���g���Ō��
					if (pObject->m_pPrev != NULL)
					{// �������݂��Ă���
						m_apCur[nCntPri] = pObject->m_pPrev;	// �O���Ō���ɂ���
						pObject->m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
					}
					else
					{// ���݂��Ă��Ȃ�
						m_apTop[nCntPri] = NULL;	// �擪���Ȃ���Ԃɂ���
						m_apCur[nCntPri] = NULL;	// �Ō�����Ȃ���Ԃɂ���
					}
				}
				else
				{
					if (pObject->m_pPrev != NULL)
					{
						pObject->m_pPrev->m_pNext = pObject->m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
					}

					if (pObject->m_pNext != NULL)
					{
						pObject->m_pNext->m_pPrev = pObject->m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
					}
				}

				delete pObject;	// �������̊J��
				pObject = NULL;

				m_aPriNumAll[nCntPri]--;
				m_nNumAll--;

				if (type == TYPE_MODEL)
				{
					m_nItemNumAll--;
				}
				else if (type == TYPE_ENEMY)
				{
					m_nNumEnemyAll--;
				}
			}

			pObject = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}
}