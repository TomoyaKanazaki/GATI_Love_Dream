//========================================
//
//�V���[�e�B���O�A�N�V����[Number.cpp]
//Author�F�X��x��
//
//========================================
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"

//========================================
//�R���X�g���N�^
//========================================
CNumber::CNumber()
{

}

//========================================
//�f�X�g���N�^
//========================================
CNumber::~CNumber()
{

}

//========================================
//�i���o�[����
//========================================
CNumber *CNumber::Create(void)
{
	//CBullet�^�̃|�C���^
	CNumber *pNumber = nullptr;

	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetTexture();

	if (pNumber == nullptr)
	{
		//�v���C���[����
		pNumber = new CNumber;

		//������
		pNumber->Init();
	}

	//�|�C���^��Ԃ�
	return pNumber;
}
