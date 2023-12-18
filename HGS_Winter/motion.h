//========================================
//
//�V���[�e�B���O�A�N�V����[motion.h]
//Author�F�X��x��
//
//========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"

//========================================
//�}�N����`
//========================================
#define MAX_MODEL	(10)	//�p�[�c�̍ő吔
#define MAX_MOTION	(2)		//���[�V�����̍ő吔
#define MAX_KEY		(2)		//�L�[�̑���

//========================================
//���[�V�����N���X
//========================================
class CMotion
{
public:
	typedef struct 
	{//�L�[�̍\����
		float fPosX;	//�ʒuX
		float fPosY;	//�ʒuY
		float fPosZ;	//�ʒuZ
		float fRotX;	//����X
		float fRotY;	//����Y
		float fRotZ;	//����Z
	}KEY;	//�ʒu�E����

	typedef struct
	{//�L�[���̍\����
		int nFrame;				//�Đ��t���[��
		KEY aKey[MAX_MODEL];	//�e���f���̃L�[�v�f
	}KEY_INFO;		//�J�b�g�V�[��

	typedef struct 
	{//���[�V�������̍\����
		bool bLoop;		//���[�v���邩�ǂ���
		int nNumKey;	//�L�[�̑���
		KEY_INFO aKeyInfo[MAX_MODEL];	//�L�[���
	}INFO;

	CMotion();		//�R���X�g���N�^
	~CMotion();		//�f�X�g���N�^

	//�����o�֐�
	static CMotion *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Set(int nType);
	void Update(void);
	void Draw(void);
	int GetType(void) { return m_nType; }	//��ގ擾
	bool IsFinish(void);

	void SetInfo(INFO info);
	void SetModel(CModel *ppModel, int nNumModel);

	CModel **GetModel(void) { return &m_ppModel[0]; }

	void Load(char *pPath);

private:
	//�����o�ϐ�
	INFO m_aInfo[MAX_MOTION];	//���[�V�������
	int m_nNumAll;		//���[�V��������
	int m_nType;		//���[�V�������
	int m_nKey;			//���݂̃L�[�i���o�[
	int m_nCounter;		//���[�V�����J�E���^�[
	bool m_bFinish;		//�I���������ǂ���
	CModel *m_ppModel[MAX_PARTS];	//���f���ւ̃_�u���|�C���^
	int m_nNumModel;	//���f���̑���
	D3DXVECTOR3 m_pos;	//�ʒu

	D3DXVECTOR3 m_rot;	//����

	CModel *m_pParent;	//�e���f���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��

};

#endif
