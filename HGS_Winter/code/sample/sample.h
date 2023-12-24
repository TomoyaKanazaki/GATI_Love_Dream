//==========================================================
//
// �T���v�� [sample.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SAMPLE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "../object.h"

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CSample : public CObject
{

public:	// �N�ł��A�N�Z�X�\

	//CSample();	// �R���X�g���N�^
	CSample(int nPriOrity = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CSample();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSample *Create(void);

	// �����o�֐�(�擾)
	

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
};

#endif

