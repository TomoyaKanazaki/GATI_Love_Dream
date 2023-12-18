//========================================
//
//�v���C���[����[player.h]
//Author�F�X��x��
//
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "input.h"
#include "manager.h"
#include "model.h"
#include "motion.h"

//========================================
//�v���C���[�N���X
//========================================
class CPlayer : public CObject
{
public:
	enum MOTIONTYPE
	{//���[�V�����̎��
		MOTIONTYPE_NEUTRAL = 0,	//�ҋ@���
		MOTIONTYPE_WALK,			//�������
		MOTIONTYPE_MAX
	};

	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	//�����o�֐�
	static CPlayer *Create(void);	//�v���C���[����

	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��

	void Move(float fSpeed);	//�v���C���[�̑���

	float RotNormalize(float RotN, float Rot);		//rot�̐��K��

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//�����ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }			//�����擾

	void ManagementMotion(void);

private:
	//�����o�ϐ�

	//�ꊇ�Ǘ�
	LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	int m_nIdxTexture;				//�e�N�X�`���̔ԍ�
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�

	//�I�u�W�F�N�g
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����

	CModel *m_apModel[MAX_PARTS];	//���f���ւ̃|�C���^
	CMotion *m_pMotion;		//���[�V�����̃|�C���^
	int m_apNumModel;		//���f��(�p�[�c)�̑���
	D3DXVECTOR3 m_RotDest;	//�ړI�̌���
	bool m_bJump;			//�W�����v
	bool m_bMove;			//�ړ�
	bool m_bWait;			//�ҋ@
};

#endif