//========================================
//
//�V���[�e�B���O�A�N�V����[bg.h]
//Author�F�X��x��
//
//========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//========================================
//�}�N����`
//========================================
#define MAX_BG	(3)		//�w�i�̍ő吔

//========================================
//�w�i�N���X
//========================================
class CBg : public CObject2D
{
public:
	CBg();		//�R���X�g���N�^
	~CBg();		//�f�X�g���N�^
	
	//�����o�֐�
	static CBg *Create(void);		//�w�i�̐���

	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��

	void SetPosition(D3DXVECTOR3 pos);		//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void);			//�ʒu�擾

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��
	D3DXVECTOR3 m_pos;
	float m_aTexV;		//�e�N�X�`�����W�̊J�n�ʒu(V�l)
};

#endif