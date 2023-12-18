//========================================
//
//�V���[�e�B���O�A�N�V����[object3D.h]
//Author�F�X��x��
//
//========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//========================================
//�I�u�W�F�N�g3D�N���X
//========================================
class CObject3D : public CObject
{
public:
	CObject3D();	//�R���X�g���N�^
	~CObject3D();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��
	static CObject3D *Create();		//�I�u�W�F�N�g�̐���
	void BindTexture(int pTexture);	//�e�N�X�`�����蓖��

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetVertex3D(void);
	void SetVerTexBillboard(void);
	void Collision(void);
	void MeshVertex(void);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		 //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����

	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�
};

#endif