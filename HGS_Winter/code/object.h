//===============================================
//
// �I�u�W�F�N�g�̏��� [object.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _OBJECT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �}�N����`
#define MAX_OBJECT		(1536)	// �ő吔
#define NUM_PRIORITY	(8)		// �D�揇�ʊǗ���

// �O���錾
class CObject2D;
class CMultiBg;
class CEnemy;

//===============================================
// �I�u�W�F�N�g�N���X�̒�`(���ۃN���X)
//===============================================
class CObject
{
public:	// �N�ł��A�N�Z�X�\

	// ��ޗ񋓌^�̒�`
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_BG,			// �w�i
		TYPE_PLAYER,		// �v���C���[
		TYPE_ENEMY,		// �G
		TYPE_BULLET,		// �e
		TYPE_ITEM,		// �A�C�e��
		TYPE_EXPLOSION,	// ����
		TYPE_EFFECT,		// �G�t�F�N�g
		TYPE_BLOCK,		// �u���b�N
		TYPE_MODEL,		// ���f��
		TYPE_CAR,		// �ԁ@
		TYPE_PAUSE,		// �|�[�Y���
		TYPE_MAP,		// �}�b�v�\��
		TYPE_MAX
	}TYPE;

	//CObject();			// �R���X�g���N�^
	CObject(int nPriority = 3);	// �R���X�g���N�^(�I�[�o�[���[�h)�f�t�H���g����
	virtual ~CObject();	// �f�X�g���N�^

	// �������z�֐��֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// �����o�֐�(�ݒ�)
	virtual void SetPosition(const D3DXVECTOR3&) = 0;
	virtual void SetRotation(const D3DXVECTOR3&) = 0;

	// �����o�֐�(�擾)
	virtual D3DXVECTOR3 GetPosition(void) const = 0;
	virtual D3DXVECTOR3 GetRotation(void) const = 0;
	virtual CObject2D *GetObject2D(void) { return NULL; }
	virtual int GetModelType(void) { return -1; }
	virtual D3DXMATRIX *GetMtx(void) { return NULL; }
	virtual CEnemy *GetEnemy(void) { return NULL; }
	virtual bool GetDeath(void) { return m_bDeath; }

	// �����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject *GetTop(const int nPriority) { return m_apTop[nPriority]; }
	CObject *GetNext(void) { return m_pNext; }
	static int GetNumAll(void) { return m_nNumAll; }
	static int GetItemNumAll(void) { return m_nItemNumAll; }
	static int GetPriNumAll(int nPriority) { return m_aPriNumAll[nPriority]; }
	static int GetNumEnemAll(void) { return m_nNumEnemyAll; }
	void SetDraw(bool bUse = true) { m_bDraw = bUse; }
	bool GetDraw(void) { return m_bDraw; }

	// �����o�֐�(�擾
	TYPE GetType(void) { return m_type; }
	int GetPri(void) { return m_nPriority; }

	// �����o�֐�(�ݒ�)
	void SetType(const TYPE type);

protected:	// �h���N���X������A�N�Z�X�\

	// �����o�֐�
	void Release(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static void DeathCheck(void);
	// �����o�ϐ�
	static int m_aPriNumAll[NUM_PRIORITY];	// �e�D�揇�ʂ��Ƃ̑���
	static int m_nNumAll;	// �I�u�W�F�N�g����
	static int m_nNumEnemyAll;	// �G�l�~�[�̑���
	static int m_nItemNumAll;	// �A�C�e���̑���
	static CObject *m_apTop[NUM_PRIORITY];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_apCur[NUM_PRIORITY];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;	// ���S�t���O
	bool m_bDraw;		// �`��t���O
	int m_nPriority;	// �D�揇�ʂ̈ʒu
	TYPE m_type;		// ���
};

#endif
