//========================================
//
//�V���[�e�B���O�A�N�V����[number.h]
//Author�F�X��x��
//
//========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//========================================
//�i���o�[�N���X
//========================================
class CNumber : public CObject2D
{
public:
	CNumber();		//�R���X�g���N�^
	~CNumber();		//�f�X�g���N�^

	//�����o�֐�
	static CNumber *Create(void);	//�v���C���[����
};

#endif