//=======================================
//
//�V���[�e�B���O�A�N�V����[billboard.h]
//Author�@:�@MORIKAWA SHUNYA
//
//=======================================

#ifndef _BILLBOARD_H_     //���̃}�N����`����`����Ă��Ȃ�������
#define _BILLBOARD_H_    //2�A�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object3d.h"

//=======================================
//�r���{�[�h�N���X
//=======================================
class CBillboard : public CObject
{
public:
	CBillboard();	//�R���X�g���N�^
	~CBillboard();	//�f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��

	static CBillboard *Create(D3DXVECTOR3 pos, float fwidth, float fheight);	//�r���{�[�h����

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`�����蓖��
	void BindTexture(int pTexture);				//�e�N�X�`�����蓖��
	void SetPosVertex(void);
	void SetVertexAnim(int Num, int Cnt);		//�e�N�X�`���A�j���[�V����
	void SetSizeVertex(float size, float fheight);
	void SetEffectVertex(float fEffectsize);		//�G�t�F�N�g�̒��_���
	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetMove(void);
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);	//�T�C�Y�ݒ�
	void SetPosition(D3DXVECTOR3 pos);			//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void);				//�ʒu�擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//���_�����i�[
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;        //�F
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fLength;		//�Ίp���̒���
	float m_fAngle;			//�Ίp���̊p�x
};

#endif