//========================================
//
//�^�C�g������[title.h]
//Author�F�X��x��
//
//========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

//========================================
//�^�C�g���N���X
//========================================
class CTitle : public CScene
{
public:
	CTitle();	//�R���X�g���N�^
	~CTitle();	//�f�X�g���N�^

	//�����o�֐�
	static CTitle *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D *m_pObj2D;
};

#endif
