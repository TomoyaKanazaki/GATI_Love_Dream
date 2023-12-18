//========================================
//
//�V���[�e�B���O�A�N�V����[motion.cpp]
//Author�F�X��x��
//
//========================================
#include "motion.h"

//========================================
//�R���X�g���N�^
//========================================
CMotion::CMotion() : 
	m_nNumAll(0),		//���[�V�����̑���
	m_nType(0),			//���
	m_nKey(0),			//���݂̃L�[��
	m_nCounter(0),		//�t���[���J�E���^�[
	m_bFinish(false),	//�I���������ǂ���
	m_nNumModel(0)		//���f���̑���
{//�l�N���A
	memset(&m_aInfo[0], 0, sizeof(m_aInfo));	//���[�V�������
}

//========================================
//�f�X�g���N�^
//========================================
CMotion::~CMotion()
{
	
}

//========================================
//����
//========================================
CMotion *CMotion::Create(void)
{
	//CMotion�^�̃|�C���^
	CMotion *pMotion = nullptr;

	if (pMotion == nullptr)
	{//nullptr�̎�
		//�C���X�^���X����
		pMotion = new CMotion;

		//������
		pMotion->Init();
	}

	//�|�C���^��Ԃ�
	return pMotion;
}

//========================================
//������
//========================================
HRESULT CMotion::Init(void)
{
	//�e�l�̏����l�ݒ�
	memset(&m_aInfo[0], 0, sizeof(m_aInfo));		//���[�V�������
	m_nNumAll = 0;				//���[�V��������
	m_nType = 0;				//���[�V�������
	m_nKey = 0;					//���݂̃L�[�i���o�[
	m_nCounter = 0;				//���[�V�����J�E���^�[
	m_bFinish = false;			//�I���������ǂ���

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{//�_�u���|�C���^�̏�����
		m_ppModel[nCntModel] = nullptr;
	}

	m_nNumModel = 0;	//���f���̑���

	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CMotion::Uninit(void)
{
}

//========================================
//�ݒ�
//========================================
void CMotion::Set(int nType)
{
	m_nType = nType;

	//�L�[���Z�b�g
	m_nKey = 0;

	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{//MAX_MOTION����
		m_aInfo[nCntMotion].aKeyInfo[nCntMotion].nFrame;
	}
}

//========================================
//�X�V
//========================================
void CMotion::Update(void)
{
	//�ʒu
	float fDiffPosX = 0;	//����
	float fDiffPosY = 0;	//����
	float fDiffPosZ = 0;	//����

	//����
	float fDiffRotX = 0;	//����
	float fDiffRotY = 0;	//����
	float fDiffRotZ = 0;	//����

	//���̒l
	int nNextKey = m_nKey + 1;	

	if (nNextKey >= m_aInfo[m_nType].nNumKey)
	{//���̃L�[��
		nNextKey = 0;
	}

	for (int nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{//�p�[�c�̍ő啪��
		//���f���̃|�C���^
		CModel *pModel = m_ppModel[nCntParts];

		//�ʒu�擾
		D3DXVECTOR3 pos = pModel->GetPosition();

		//�ʒu�擾
		D3DXVECTOR3 rot = pModel->GetRot();

		//�ʒu���Z�o
		fDiffPosX = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosX;
		fDiffPosY = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosY;
		fDiffPosZ = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosZ;

		//�������Z�o
		fDiffRotX = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotX;
		fDiffRotY = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotY;
		fDiffRotZ = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotZ;

		//�ʒu
		pos.x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosX
				+ fDiffPosX
				* ((float)m_nCounter
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		pos.y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosY
				+ fDiffPosY
				* ((float)m_nCounter
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		pos.z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosZ
				+ fDiffPosZ 
				* ((float)m_nCounter 
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		//����
		rot.x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotX
				+ fDiffRotX 
				* ((float)m_nCounter 
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		rot.y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotY
				+ fDiffRotY 
				* ((float)m_nCounter 
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		rot.z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotZ
				+ fDiffRotZ 
				* ((float)m_nCounter 
				/ (float)m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame);

		//�ʒu���f
		pModel->SetPosition(pos + pModel->GetPos());

		//�������f
		pModel->SetRot(rot + pModel->GetRotate());
	}

	//���݂̃L�[��1�i�߂�
	m_nCounter++;

	if (m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame < m_nCounter)
	{
		//���݂̃L�[���Z
		m_nKey++;

		//���[�V�����J�E���^�[���Z�b�g
		m_nCounter = 0;

		if (m_aInfo[m_nType].nNumKey <= m_nKey)
		{//�L�[���������݂̃L�[��菬����
			//���݂̃L�[���Z�b�g
			m_nKey = 0;
		}
	}
}

//========================================
//�`��
//========================================
void CMotion::Draw(void)
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{//���f���̕`��(�S�p�[�c)
 		if (m_ppModel[nCntParts] != nullptr)
		{//m_apModel��nullptr�̎�
			m_ppModel[nCntParts]->Draw();
		}
	}
}

//========================================
//�I���������ǂ���
//========================================
bool CMotion::IsFinish(void)
{
	//�I���������ǂ�����Ԃ�
	return m_bFinish;
}

//========================================
//���[�V�������̐ݒ�
//========================================
void CMotion::SetInfo(INFO info)
{
}

//========================================
//���f���ݒ�
//========================================
void CMotion::SetModel(CModel *ppModel, int nNumModel)
{
	//�|�C���^
	m_ppModel[nNumModel] = ppModel;

	//�p�[�c�ԍ�
	m_nNumModel++;
}

//========================================
//�ǂݍ���
//========================================
void CMotion::Load(char *pPath)
{
	//�ϐ��錾
	char garbage[640];		//�S�~�i�[�p
	char FileName[32];		//�e���f���̃t�@�C����
	int nNumParts = 0;		//�p�[�c��
	int nIdx = 0;			//���Ԗڂ̃p�[�c��
	int nParent = 0;		//�e�q�֌W
	int nPartsIndex = 0;	//�p�[�c�̔ԍ�
	int nNum = 0;			//�ǂݍ��ޔԍ�
	int nMotion = 0;		//���Ԗڂ̃��[�V������
	int nCntKey = 0;		//���ڂ̃L�[��
	int nLoop = 0;			//���[�v���邩���Ȃ���
	int nNumKey = 0;		//�L�[��
	int nFlame = 0;			//�t���[����
	float move = 0.0f;		//�ړ���
	int KeyCount = 0;
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);		//�ʒu
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);		//����

	//�L�[��
	int keysetCount = 0;

	//FILE�̃|�C���^
	FILE *pFile = nullptr;

	//�t�@�C�����J��
	pFile = fopen(pPath, "r");

	while (1)
	{//END_SCRIPT������܂ŌJ��Ԃ�
		//�s�v�ȕ������̂Ă�
		fscanf(pFile, "%s", &garbage[0]);

		if (strcmp(&garbage[0], "END_SCRIPT") == 0)
		{//������END_SCRIPT�̂Ƃ�
			//�����o��
			break;
		}

		//========================================
		//���f���t�@�C���̓ǂݍ���
		//========================================
		if (strcmp(&garbage[0], "MODEL_FILENAME") == 0)
		{//������MODEL_FILENAME�̂Ƃ�
			//=�̂Ă�
			fscanf(pFile, "%s", &garbage[0]);

			//�t�@�C���̖��O�擾
			fscanf(pFile, "%s", &FileName[0]);

			//���f���̐���
			m_ppModel[nNum] = CModel::Create(&FileName[0]);

			//���f���ݒ�
			SetModel(m_ppModel[nNum], nNum);

			//���f���̔ԍ������Z����
			nNum++;
		}

		//========================================
		//���f���ݒ�
		//========================================
		if (strcmp(&garbage[0], "CHARACTERSET") == 0)
		{//������CHARACTERSET�̂Ƃ�
			while (1)
			{//������END_CHARACTERSET�ɂȂ�܂ŌJ��Ԃ�
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_CHARACTERSET") == 0)
				{//������END_CHARACTERSET�̎�
					//�����o��
					break;
				}

				if (strcmp(&garbage[0], "MOVE") == 0)
				{//������MOVE�̎�
					//=�̂Ă�
					fscanf(pFile, "%s", &garbage[0]);

					//�ړ��ʂ�����
					fscanf(pFile, "%f", &move);
				}

				if (strcmp(&garbage[0], "NUM_PARTS") == 0)
				{//������NUM_PARTS�̎�
					//=�̂Ă�
					fscanf(pFile, "%s", &garbage[0]);

					//�p�[�c��������
					fscanf(pFile, "%d", &nNumParts);
				}

				if (strcmp(&garbage[0], "PARTSSET") == 0)
				{//������PARTSSET�̎�
					while (1)
					{//END_PARTSSET������܂ŉ�
						fscanf(pFile, "%s", &garbage[0]);

						if (strcmp(&garbage[0], "END_PARTSSET") == 0)
						{//������END_PARTSSET�̎�
							//�p�[�c�������Z
							nPartsIndex++;

							//�����o��
							break;
						}

						if (strcmp(&garbage[0], "INDEX") == 0)
						{//������INDEX�̎�
							//=�̂Ă�
							fscanf(pFile, "%s", &garbage[0]);

							//���Ԗڂ̃p�[�c���̐ݒ�
							fscanf(pFile, "%d", &nIdx);

							//���f���̔ԍ��ݒ�
							m_ppModel[nPartsIndex]->SetIndex(m_ppModel[nIdx]);
						}

						if (strcmp(&garbage[0], "PARENT") == 0)
						{//������PARENT�̎�
							//=�̂Ă�
							fscanf(pFile, "%s", &garbage[0]);

							//�e�q�֌W�ݒ�
							fscanf(pFile, "%d", &nParent);

							if (nParent == -1)
							{//�e�p�[�c�������ꍇ
								m_ppModel[nPartsIndex]->SetParent(nullptr);
							}
							else
							{//�e�p�[�c������ꍇ
								m_ppModel[nPartsIndex]->SetParent(m_ppModel[nParent]);
							}
						}

						if (strcmp(&garbage[0], "POS") == 0)
						{//������PARENT�̎�
							//=�̂Ă�
							fscanf(pFile, "%s", &garbage[0]);

							fscanf(pFile, "%f", &pos.x);
							fscanf(pFile, "%f", &pos.y);
							fscanf(pFile, "%f", &pos.z);

							//�ʒu��ݒ�
							m_ppModel[nPartsIndex]->SetPos(pos);
						}

						if (strcmp(&garbage[0], "ROT") == 0)
						{//������PARENT�̎�
							//=�̂Ă�
							fscanf(pFile, "%s", &garbage[0]);

							fscanf(pFile, "%f", &rot.x);
							fscanf(pFile, "%f", &rot.y);
							fscanf(pFile, "%f", &rot.z);

							//������ݒ�
							m_ppModel[nPartsIndex]->SetRotate(rot);
						}
					}
				}
			}
		}

		//�o�[�c�ԍ����Z�b�g
		nPartsIndex = 0;

		//========================================
		//���[�V�����ݒ�
		//========================================
		if (strcmp(&garbage[0], "MOTIONSET") == 0)
		{//������MOTIONSET�̎�
			//�p�[�c�����Z�b�g

			while (1)
			{//END_PARTSSET������܂ŉ�
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_MOTIONSET") == 0)
				{//������END_PARTSSET�̎�
					//�p�[�c�������Z
					nPartsIndex++;

					//�����o��
					break;
				}

				if (strcmp(&garbage[0], "LOOP") == 0)
				{//������INDEX�̎�
					//=�̂Ă�
					fscanf(pFile, "%s", &garbage[0]);

					//�e�q�֌W�ݒ�
					fscanf(pFile, "%d", &nLoop);

					if (nLoop == 0)
					{//nLoop��0�̎�
						m_aInfo[nPartsIndex].bLoop = false;
					}
					if (nLoop == 1)
					{//nLoop��1�̎�
						m_aInfo[nPartsIndex].bLoop = true;
					}
				}

				if (strcmp(&garbage[0], "NUM_KEY") == 0)
				{//������NUM_KEY�̎�
					//=�̂Ă�
					fscanf(pFile, "%s", &garbage[0]);

					//�e�q�֌W�ݒ�
					fscanf(pFile, "%d", &m_aInfo[nPartsIndex].nNumKey);
				}

				if (strcmp(&garbage[0], "KEYSET") == 0)
				{//������PARENT�̎�
					while (1)
					{//END_KEYSET������܂ŌJ��Ԃ�
						//=�̂Ă�
						fscanf(pFile, "%s", &garbage[0]);

						if (strcmp(&garbage[0], "END_KEYSET") == 0)
						{//������END_PARTSSET�̎�

							//���Z����
							keysetCount++;
							KeyCount = 0;
							//�����o��
							break;
						}

						if (strcmp(&garbage[0], "FRAME") == 0)
						{//������FRAME�̎�
							//=�̂Ă�
							fscanf(pFile, "%s", &garbage[0]);

							//�t���[����
							fscanf(pFile, "%d", &m_aInfo[nPartsIndex].aKeyInfo[keysetCount].nFrame);
						}

						if (strcmp(&garbage[0], "KEY") == 0)
						{//������KEY�̎�
							while (1)
							{//END_KEY������܂ŌJ��Ԃ�
								//=�̂Ă�
								fscanf(pFile, "%s", &garbage[0]);

								if (strcmp(&garbage[0], "END_KEY") == 0)
								{//������END_KEY�̎�

									//���Z����
									KeyCount++;

									//�����o��
									break;
								}

								if (strcmp(&garbage[0], "POS") == 0)
								{//������POS�̎�
									//=�̂Ă�
									fscanf(pFile, "%s", &garbage[0]);

									fscanf(pFile, "%f", &pos.x);
									fscanf(pFile, "%f", &pos.y);
									fscanf(pFile, "%f", &pos.z);

									//�ʒu��ݒ�
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosX = pos.x;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosY = pos.y;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosZ = pos.z;
								}

								if (strcmp(&garbage[0], "ROT") == 0)
								{//������ROT�̎�
									//=�̂Ă�
									fscanf(pFile, "%s", &garbage[0]);

									fscanf(pFile, "%f", &rot.x);
									fscanf(pFile, "%f", &rot.y);
									fscanf(pFile, "%f", &rot.z);

									//�ʒu��ݒ�
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fRotX = rot.x;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fRotY = rot.y;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fRotZ = rot.z;
								}
							}
						}
					}
				}
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);
}
