//==========================================================
//
// X�t�@�C���Ǘ� [modelfile.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MODELFILE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MODELFILE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

//==========================================================
// X�t�@�C�����̃N���X��`
//==========================================================
class CXFile
{
private:	// �����������A�N�Z�X�\�Ȓ萔��`

	const static int MAX_FILE = 256;	// ���f���t�@�C���̍ő吔
	const static int MAX_NAME = 256;	// �t�@�C����������

public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	// X�t�@�C�����
	typedef struct
	{
		LPD3DXMESH pMesh;		//���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;	//�}�e���A���ւ̃|�C���^
		int *pIdexTexture;	// �e�N�X�`���ԍ�
		DWORD dwNumMat;		//�}�e���A���̐�
		D3DXVECTOR3 vtxMin;	// �ŏ�
		D3DXVECTOR3 vtxMax;	// �ő�
	}FileData;

private:	// �����������A�N�Z�X�\�Ȓ�`

	// �t�@�C���ǂݍ��ݏ��
	typedef struct
	{
		FileData filedata;			// �t�@�C�����
		char aFileName[MAX_NAME];	// �t�@�C����
	}FileInfo;

public:	// �N�ł��A�N�Z�X�\

	CXFile();	// �R���X�g���N�^
	~CXFile();	// �f�X�g���N�^

	// �����o�֐�
	 int Regist(const char *pFileName);
	 void Unload(void);
	 void SetSizeVtxMax(int nIdx, const D3DXVECTOR3& vtxMax) { m_apModelFileData[nIdx]->filedata.vtxMax = vtxMax; }
	 void SetSizeVtxMin(int nIdx, const D3DXVECTOR3& vtxMin) { m_apModelFileData[nIdx]->filedata.vtxMin = vtxMin; }

	 // �����o�֐�(�擾)
	 FileData *SetAddress(int nIdx);
	 static int GetNumAll(void) { return m_nNumAll; }
	 D3DXVECTOR3 GetMax(int nIdx) const { return m_apModelFileData[nIdx]->filedata.vtxMax; }
	 D3DXVECTOR3 GetMin(int nIdx) const { return m_apModelFileData[nIdx]->filedata.vtxMin; }
	 char *GetFileName(int nIdx) { return &m_apModelFileData[nIdx]->aFileName[0]; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	 HRESULT FileLoad(int nIdx);

	// �����o�ϐ�
	FileInfo *m_apModelFileData[MAX_FILE];	// ���f���̃t�@�C�����̃|�C���^
	static int m_nNumAll;	// �ǂݍ��ݑ���
};

#endif
