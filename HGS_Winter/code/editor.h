//==========================================================
//
// �G�f�B�b�g�����S�� [editor.h]
//Author : Ibuki Okusada
//
//==========================================================
#ifndef _EDITOR_H_
#define _EDITOR_H_

// �O���錾
class CObjectX;

//**********************************************************
// ���b�V���t�B�[���h�N���X�̒�`(�h���N���X)
//**********************************************************
class CEditor
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	typedef struct
	{
		D3DXVECTOR3 pos;		//�ʒu
		D3DXVECTOR3 rot;		//����
		D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
		int nIdxModel;		// ���f���ԍ�
	}ObjectX;

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_REPEAT,
		TYPE_MAX
	}TYPE;

public:	// �N�ł��A�N�Z�X�\

	CEditor();	// �R���X�g���N�^
	~CEditor();	// �f�X�g���N�^

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);
	bool GetActive(void) { return m_bUse; }
	bool GetMeshActive(void) { return m_bMesh; }

private:	// �����������A�N�Z�X�\
	
	ObjectX m_Object;	// ���f���|�C���^
	int m_nIdx;		// �C���f�b�N�X
	float m_fSpeed;	// ���x
	int m_nMoveCnt;	// ����J�E���g
	int m_nNumMove;	// �ړ��܂ł̎���
	int m_nType;		// ���
	float m_fLength;	// ���b�V�������p���a
	float m_fMeshMove;	// ���b�V���̈ړ���
	bool m_bUse;		// �g�p�����ǂ�
	bool m_bMesh;		// ���b�V�����삷�邩�ۂ�
};


#endif

