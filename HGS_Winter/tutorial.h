//========================================
//
//�V���[�e�B���O�A�N�V����[title.h]
//Author�F�X��x��
//
//========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//========================================
//�`���[�g���A���N���X
//========================================
class CTutorial : public CScene
{
public:
	CTutorial();	//�R���X�g���N�^
	~CTutorial();	//�f�X�g���N�^

	//�����o�֐�
	static CTutorial *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_Counter;
	CObject2D *m_pObj2D;
};

#endif
