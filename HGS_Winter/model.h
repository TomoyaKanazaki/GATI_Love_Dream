//========================================
//
//�V���[�e�B���O�A�N�V����[model.h]
//Author�F�X��x��
//
//========================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "object.h"

//=======================================
//���f���N���X
//=======================================
class CModel
{
public:
	CModel();		//�R���X�g���N�^
	~CModel();		//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const char *pFilename);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��

	static CModel *Create(const char *pFilename);	//�I�u�W�F�N�g����
	void SetParent(CModel *pModel);	//�e
	D3DXMATRIX GetMtxWorld(void);	//���[���h�}�g���b�N�X�̎擾

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

	//����
	void SetRot(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetRot(void);

	//�ԍ�
	void SetIndex(CModel *pModel);

	//�ʒu
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);

	//����
	void SetRotate(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotate(void);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	CModel *m_pParent;	//�e���f���ւ̃|�C���^

	D3DXVECTOR3 m_setPos;
	D3DXVECTOR3 m_setRot;

};

#endif