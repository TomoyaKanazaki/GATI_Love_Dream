//========================================
//
//�V���[�e�B���O�A�N�V����[polygon.h]
//Author�F�X��x��
//
//========================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "main.h"
#include "object3D.h"

//========================================
//�|���S���N���X
//========================================
class CPolygon : public CObject3D
{
public:
	CPolygon();		//�R���X�g���N�^
	~CPolygon();	//�f�X�g���N�^

	//�����o�֐�
	static CPolygon *Create(void);	//�|���S������

	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��

private:
	//�����o�ϐ�
	static 	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	CObject3D *m_pObj3D;
};

#endif