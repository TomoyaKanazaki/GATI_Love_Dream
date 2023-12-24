//==========================================================
//
// �J�E���g�_�E������ [countdown.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _COUNTDOWN_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _COUNTDOWN_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

// �}�N����`
#define COUNT_DOWN_NUM	 (3)	// �J�E���g�_�E���̐��l

// �O���錾
class CNumber;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CCountDown
{

public:	// �N�ł��A�N�Z�X�\

	CCountDown();	// �R���X�g���N�^
	~CCountDown();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CCountDown *Create(void);

	// �����o�֐�(�擾)
	bool GetEnd(void) { return m_bEnd; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	CNumber *m_pObject;
	D3DXVECTOR3 m_pos;	// ���W
	float m_fDownCounter;	// �J�ڃJ�E���g
	int m_nNum;	// ���݂̒l
	bool m_bEnd;	// �J�E���g�_�E���I��
};

#endif

