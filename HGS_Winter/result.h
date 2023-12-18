//========================================
//
//�V���[�e�B���O�A�N�V����[result.h]
//Author�F�X��x��
//
//========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//========================================
//�Q�[���N���X
//========================================
class CResult : public CScene
{
public:
	CResult();	//�R���X�g���N�^
	~CResult();	//�f�X�g���N�^

				//�����o�֐�
	static CResult *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCnt;
	int m_Counter;
	CObject2D *m_pObj2D;
};

#endif
