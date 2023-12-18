//========================================
//
//�V���[�e�B���O�A�N�V����[object.h]
//Author�F�X��x��
//
//========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

//========================================
//�}�N����`
//========================================
#define MAX_DATA (100)	//�ő吔

//========================================
//�I�u�W�F�N�g�N���X
//========================================
class CObject
{
public: 
	enum TYPE
	{//���
		TYPE_NONE = 0,	//��ޖ���
		TYPE_PLAYER,	//�v���C���[
		TYPE_ENEMY,		//�G
		TYPE_BULLET,	//�e
		TYPE_EXPLOSION,	//����
		TYPE_EFFECT,	//�G�t�F�N�g
		TYPE_ITEM,		//�A�C�e��
		TYPE_MAX
	};

	enum ITEM
	{//�A�C�e��
		ITEM_NONE = 0,
		ITEM_HEAL,		//��
		ITEM_BULLET,	//�e
		ITEM_MAX
	};

	CObject();				//�R���X�g���N�^
	virtual ~CObject();		//�f�X�g���N�^

	//�������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetVertex(void) = 0;
	virtual void SetSize(float fWidht, float fHeight) = 0;
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	//�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject *GetObject(int nIdx);
	void BindTexture(int pTexture);				//�e�N�X�`�����蓖��

	D3DXVECTOR3 Getpos(void) { return m_pos; }
protected:
	void Release(void);

private:
	static CObject *m_apObject[MAX_DATA];
	static int m_nNumAll;	//�I�u�W�F�N�g����
	int m_nID;				//�������g��ID
	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�
};

#endif
