//========================================
//
//objectX����[objectX.h]
//Author�F�X��x��
//
//========================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_
#include "main.h"
#include "object.h"
#include <functional>

//========================================
//�}�N����`
//========================================
#define LOAD_OBJECT		"data\\FILE\\Object.txt"		//�I�u�W�F�N�g�̊O���t�@�C��

#define MAX_OBJX		(160)		//�I�u�W�F�N�g�̍ő吔
#define MAX_GARBAGE		(900)		//�S�~�����锠�̍ő吔
#define OBJ_DETA		(83)		//�I�u�W�F�N�g�̓ǂݍ��ސ�

//=======================================
//objectX�N���X
//=======================================
class CObjectX	: public CObject
{
public:
	CObjectX();		//�R���X�g���N�^
	~CObjectX();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos);
	void Load(void);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�擾
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }	//���f���̍ŏ��l�擾
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }	//���f���̍ő�l�擾

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;				//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXVECTOR3 m_vtxMin, m_vtxMax;	//���f���̍ő�A�ŏ��l

	std::function<float(float,float)> m_funcTest;
};

#endif