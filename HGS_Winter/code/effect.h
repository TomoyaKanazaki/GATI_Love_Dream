//===============================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object2D.h"
#include "billboard.h"

//===============================================
//�N���X�̒�`
//===============================================
class CEffect : public CObjectBillboard
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	// ��ނ̗񋓌^��`
	typedef enum
	{
		TYPE_NONE = 0,	// �ʏ�
		TYPE_BULLET,	// �e
		TYPE_EXPLOSION,	// ����
		TYPE_DUST,		// �y��
		TYPE_SHWBULLET,	// �V�����[�e
		TYPE_SHWREF,	// �n�ʔ��˃V�����[
		TYPE_SWEAT,		// ��
		TYPE_HEAT,		// �M���Ǐ��
		TYPE_JUMP,		// �W�����v
		TYPE_SWAP,		// �O�Ղ��ۂ���
		TYPE_BALEXPLOSION,	// ���D����
		TYPE_SMAKE,		// ��
		TYPE_HEATHAZE,	// �z��
		TYPE_BUBBLE,		// �V���{����
		TYPE_MAX
	}TYPE;

	// �������@�񋓌^
	enum FUSION
	{
		FUSION_ADD = 0,	// ���Z����
		FUSION_MINUS,		// ���Z����
		FUSION_NORMAL,	// �������Ȃ�
		FUSION_MAX
	};

private:	// ���������A�N�Z�X�\�Ȓ�`

	// ���\���̂̒�`
	typedef struct
	{
		float fLife;	// ����
		TYPE Type;	// ���
		D3DXCOLOR col;	//�F
		D3DXVECTOR3 move;	// �ړ���
		float fRadius;	//���a
	}INFO;

public:	// �N�ł��A�N�Z�X�\

	//CEffect();	// �R���X�g���N�^
	CEffect(int nPriority = 5);	// �f�t�H���g�����R���X�g���N�^
	~CEffect();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, TYPE type);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fLife, TYPE type);
	void SetMove(D3DXVECTOR3 move);
	void SetFusion(FUSION fusion) { m_fusion = fusion; }
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void RadiusSet(void);
	void ColorSet(void);

	// �����o�ϐ�
	int nIdxTexture;	// �e�N�X�`���ԍ�
	static const D3DXCOLOR m_aColInfo[TYPE_MAX];	// �F�̏��
	static const float m_aRadiusInfo[TYPE_MAX];		// ���a�̏��
	FUSION m_fusion;
	INFO m_Info;	// ���̍\����
};

#endif 
