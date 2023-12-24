//==========================================================
//
// �G�f�B�b�g�����S�� [editor.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "editor.h"
#include "manager.h"
#include "objectX.h"
#include "Xfile.h"
#include "fileload.h"
#include "debugproc.h"
#include "renderer.h"
#include "texture.h"
#include "meshfield.h"
#include "game.h"
#include "player.h"

//==========================================================
//�}�N����`
//==========================================================
#define EDITMODEL_MOVE	(5.0f)	//���f���ړ���
#define MAX_EDITSPEED	(100.0f)	//�ő�ړ���
#define MIN_EDITSPEED	(1.0f)	//�Œ�ړ���
#define EDIT_DATATXT	"data/TXT/edit.txt"	//�G�f�B�b�g�f�[�^�ۑ��p�e�L�X�g�t�@�C��
#define MAX_MESHLENGTH	(500.0f)	// ���b�V���t�B�[���h����ő�
#define MIN_MESHLENGTH	(20.0f)		// ���b�V���t�B�[���h����ŏ�
#define MAX_MESHMOVE	(100.0f)	// ���b�V���t�B�[���h�ړ��ʍő�
#define MIN_MESHMOVE	(0.5f)		// ���b�V���t�B�[���h�ړ��ʍŏ�

//==========================================================
// �R���X�g���N�^
//==========================================================
CEditor::CEditor()
{
	// �l���N���A
	m_fSpeed = EDITMODEL_MOVE;
	m_nIdx = 0;
	m_Object.nIdxModel = -1;
	m_Object.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_bMesh = false;
	m_nMoveCnt = 0;
	m_nNumMove = 0;
	m_nType = TYPE_NONE;
	m_fLength = 0.0f;
	m_fMeshMove = 0.0f;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEditor::~CEditor()
{

}


//==========================================================
// ���f���̏���������
//==========================================================
void CEditor::Init(void)
{
	if (CManager::GetInstance()->GetScene()->GetFileLoad() == NULL)
	{
		return;
	}

	m_Object.nIdxModel = CManager::GetInstance()->GetModelFile()->Regist(CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelFileName(m_nIdx));
}

//==========================================================
// �I������
//==========================================================
void CEditor::Uninit(void)
{
	
}

//==========================================================
// �X�V����
//==========================================================
void CEditor::Update(void)
{
	if (CManager::GetInstance()->GetScene()->GetFileLoad() == NULL)
	{
		return;
	}

	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CPlayer *pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	D3DXVECTOR3 pos = m_Object.pos;
	D3DXVECTOR3 rot = m_Object.rot;
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CMeshField *pMesh = NULL;	// �擪���擾

	// �z�u�ꏊ���w�肳�ꂽ�G���A�ɐݒ�
	if (pPlayer != NULL)
	{
		pMesh = CMeshField::GetArea(pPlayer->GetPosition());
	}

	// ���b�V���t�B�[���h����
	if (pMesh != NULL && m_bMesh == true)
	{
		pMesh->Edit(&m_fLength, &m_fMeshMove);

		if (m_fLength > MAX_MESHLENGTH)
		{
			m_fLength = MAX_MESHLENGTH;
		}
		if (m_fLength < MIN_MESHLENGTH)
		{
			m_fLength = MIN_MESHLENGTH;
		}

		if (m_fMeshMove > MAX_MESHMOVE)
		{
			m_fMeshMove = MAX_MESHMOVE;
		}
		if (m_fMeshMove < MIN_MESHMOVE)
		{
			m_fMeshMove = MIN_MESHMOVE;
		}
	}
	
	if (pInputKey->GetTrigger(DIK_F3) == true)
	{
		m_bUse = m_bUse ? false : true;
	}
	if (pInputKey->GetTrigger(DIK_F4) == true)
	{
		m_bMesh = m_bMesh ? false : true;
	}

	CManager::GetInstance()->GetDebugProc()->Print("�G�f�B�^�[[ F3 ] : ���b�V������[ F4 ]\n");

	if (m_bUse == false)
	{// �g�p���ł͂Ȃ��ꍇ
		return;
	}

	if (pInputKey->GetPress(DIK_LEFT) == true)
	{
		if (pInputKey->GetPress(DIK_UP) == true)
		{
			pos.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * m_fSpeed;
		}
		else if (pInputKey->GetPress(DIK_DOWN) == true)
		{
			pos.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * m_fSpeed;
		}
		else
		{
			pos.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * m_fSpeed;
		}

		m_nMoveCnt++;
	}
	else if (pInputKey->GetPress(DIK_RIGHT) == true)
	{
		if (pInputKey->GetPress(DIK_UP) == true)
		{
			pos.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * m_fSpeed;
		}
		else if (pInputKey->GetPress(DIK_DOWN) == true)
		{
			pos.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * m_fSpeed;
		}
		else
		{
			pos.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * m_fSpeed;
			pos.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * m_fSpeed;
		}

		m_nMoveCnt++;
	}
	else if (pInputKey->GetPress(DIK_UP) == true)
	{
		pos.x += -cosf(CamRot.y) * m_fSpeed;
		pos.z += -sinf(CamRot.y) * m_fSpeed;

		m_nMoveCnt++;
	}
	else if (pInputKey->GetPress(DIK_DOWN) == true)
	{
		pos.x += cosf(CamRot.y) * m_fSpeed;
		pos.z += sinf(CamRot.y) * m_fSpeed;

		m_nMoveCnt++;
	}
	//�㉺�ړ�
	else if (pInputKey->GetPress(DIK_RSHIFT) == true)
	{
		pos.y += m_fSpeed;

		m_nMoveCnt++;
	}
	else if (pInputKey->GetPress(DIK_RCONTROL) == true)
	{
		pos.y -= m_fSpeed;

		m_nMoveCnt++;
	}
	else
	{
		m_nMoveCnt = m_nNumMove - 1;
	}

	if (m_nMoveCnt > m_nNumMove)
	{
		m_nMoveCnt = 0;
	}
	else
	{
		pos = m_Object.pos;
	}

	//�ݒu
	if (pInputKey->GetTrigger(DIK_RETURN) == true)
	{
		CObjectX::Create(pos, rot, CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelFileName(m_nIdx));
	}

	//�ݒu���ύX
	if (pInputKey->GetTrigger(DIK_LSHIFT) == true)
	{
		m_nIdx = (m_nIdx + 1) % CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelNumAll();
		m_Object.nIdxModel = CManager::GetInstance()->GetModelFile()->Regist(CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelFileName(m_nIdx));
	}
	else if (pInputKey->GetTrigger(DIK_LCONTROL) == true)
	{
		m_nIdx = (m_nIdx - 1 + CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelNumAll()) % CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelNumAll();
		m_Object.nIdxModel = CManager::GetInstance()->GetModelFile()->Regist(CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelFileName(m_nIdx));
	}

	//��]
	if (pInputKey->GetTrigger(DIK_P) == true)
	{
		rot.y += D3DX_PI * 0.5f;
	}
	else if (pInputKey->GetTrigger(DIK_L) == true)
	{
		rot.y -= -D3DX_PI * 0.5f;
	}

	if (rot.y < -D3DX_PI)
	{// x���W�p�x���E
		rot.y += D3DX_PI * 2;
	}
	else if (rot.y > D3DX_PI)
	{// x���W�p�x���E
		rot.y += -D3DX_PI * 2;
	}

	//�ۑ�
	if (pInputKey->GetTrigger(DIK_F9) == true)
	{//F9�L�[�����ꂽ�Ƃ�
		Save();
	}

	//�ړ��ʕύX
	if (pInputKey->GetPress(DIK_0) == true)
	{
		m_fSpeed += 1.0f;
		if (m_fSpeed > MAX_EDITSPEED)
		{
			m_fSpeed = MAX_EDITSPEED;
		}
	}
	else if (pInputKey->GetPress(DIK_9) == true)
	{
		m_fSpeed -= 1.0f;
		if (m_fSpeed < MIN_EDITSPEED)
		{
			m_fSpeed = MIN_EDITSPEED;
		}
	}

	// ������@�ύX
	if (pInputKey->GetTrigger(DIK_F4) == true)
	{
		m_nType ^= 1;

		switch (m_nType)
		{
		case TYPE_NONE:
			m_nNumMove = 1;

			break;

		case TYPE_REPEAT:

			m_nNumMove = 10;
			break;
		}
	}

	// ���W�m�F
	float fHeight = CMeshField::GetHeight(m_Object.pos);

	if (fHeight > m_Object.pos.y)
	{
		m_Object.pos.y = fHeight;
	}

	m_Object.pos = pos;
	m_Object.rot = rot;

	CManager::GetInstance()->GetDebugProc()->Print("\n-------------------------------------------------------\n");
	CManager::GetInstance()->GetDebugProc()->Print("�G�f�B�b�g������@ ---------------\n");
	CManager::GetInstance()->GetDebugProc()->Print("�z�u�yENTER�z: �ړ� �y��,��,��,���z: ��]�yP, I�z: �ړ����@�ύX�yF4�z\n");
	CManager::GetInstance()->GetDebugProc()->Print("�ۑ��yF9�z\n");
	CManager::GetInstance()->GetDebugProc()->Print("�z�u���ύX�yLSHIFT, LCTRL�z: �����ړ��yRSHIFT, RCTRL\n�ړ��ʕύX�y9, 0�z: �폜�͈͕ύX�y7, 8�z\n");
	CManager::GetInstance()->GetDebugProc()->Print("���W�y%f, %f, %f�z: �����y%f�z : �ړ��ʁy%f�z\n", pos.x, pos.y, pos.z, rot.y, m_fSpeed);

}

//==========================================================
// ���f���̕`�揈��
//==========================================================
void CEditor::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	CXFile *pModelFile = CManager::GetInstance()->GetModelFile();	// X�t�@�C�����̃|�C���^
	CXFile::FileData *pFileData = pModelFile->SetAddress(m_Object.nIdxModel);
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	if (m_bUse == false)
	{// �g�p���ł͂Ȃ��ꍇ
		return;
	}

	if (pFileData != NULL)
	{// ���f�����g�p����Ă���ꍇ
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Object.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Object.rot.y, m_Object.rot.x, m_Object.rot.z);
		D3DXMatrixMultiply(&m_Object.mtxWorld, &m_Object.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_Object.pos.x, m_Object.pos.y, m_Object.pos.z);
		D3DXMatrixMultiply(&m_Object.mtxWorld, &m_Object.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_Object.mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
		{
			D3DXMATERIAL Mat = pMat[nCntMat];

			//�F�𔼓����ɕύX
			Mat.MatD3D.Diffuse.a = 0.5f;
			Mat.MatD3D.Ambient.a = 0.5f;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&Mat.MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->SetAddress(pFileData->pIdexTexture[nCntMat]));

			//���f��(�p�[�c)�̕`��
			pFileData->pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//==========================================================
// �G�f�B�b�g���t�@�C���ۑ�
//==========================================================
void CEditor::Save(void)
{
	FILE *pFile = fopen(EDIT_DATATXT, "w");
	D3DXVECTOR3 ROT;

	if (pFile == NULL)
	{//�t�@�C�����J���Ȃ������ꍇ
		return;
	}

	fprintf(pFile, "#==============================================================================\n"
		"# �G�f�B�b�g�f�[�^�t�@�C��[edit.txt]\n"
		"# Author : IBUKI OKUSADA\n"
		"#==============================================================================\n\n");
	fprintf(pFile, "#----------------------------------------------\n"
		"#���f�����\n"
		"#----------------------------------------------\n\n");

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY - 2; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			if (pObj == NULL)
			{//�g�p����Ă���ꍇ
				pObj = pObjNext;
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_MODEL)
			{// ���f���ȊO
				pObj = pObjNext;
				continue;
			}

			int nType = pObj->GetModelType();

			if (nType == -1)
			{
				pObj = pObjNext;
				continue;
			}

			// �t�@�C���ǂݍ��݃��f���̔ԍ��擾
			char *pChar = CManager::GetInstance()->GetModelFile()->GetFileName(nType);
			nType = CManager::GetInstance()->GetScene()->GetFileLoad()->GetModelNum(pChar);

			if (nType == -1)
			{
				pObj = pObjNext;
				continue;
			}

			ROT = D3DXVECTOR3(pObj->GetRotation().x / D3DX_PI * 180, pObj->GetRotation().y / D3DX_PI * 180, pObj->GetRotation().z / D3DX_PI * 180);

			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "	TYPE = %d\n", nType);
			fprintf(pFile, "	POS = %.1f %.1f %.1f\n", pObj->GetPosition().x, pObj->GetPosition().y, pObj->GetPosition().z);
			fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", ROT.x, ROT.y, ROT.z);
			fprintf(pFile, "	SHADOW = 1		#�g�p���Ȃ��ꍇ��0\n");
			fprintf(pFile, "END_MODELSET\n\n");

			pObj = pObjNext;
		}
	}

	//�t�@�C�������
	fclose(pFile);
}