//========================================
//
//シューティングアクション[motion.cpp]
//Author：森川駿弥
//
//========================================
#include "motion.h"

//========================================
//コンストラクタ
//========================================
CMotion::CMotion() : 
	m_nNumAll(0),		//モーションの総数
	m_nType(0),			//種類
	m_nKey(0),			//現在のキー数
	m_nCounter(0),		//フレームカウンター
	m_bFinish(false),	//終了したかどうか
	m_nNumModel(0)		//モデルの総数
{//値クリア
	memset(&m_aInfo[0], 0, sizeof(m_aInfo));	//モーション情報
}

//========================================
//デストラクタ
//========================================
CMotion::~CMotion()
{
	
}

//========================================
//生成
//========================================
CMotion *CMotion::Create(void)
{
	//CMotion型のポインタ
	CMotion *pMotion = nullptr;

	if (pMotion == nullptr)
	{//nullptrの時
		//インスタンス生成
		pMotion = new CMotion;

		//初期化
		pMotion->Init();
	}

	//ポインタを返す
	return pMotion;
}

//========================================
//初期化
//========================================
HRESULT CMotion::Init(void)
{
	//各値の初期値設定
	memset(&m_aInfo[0], 0, sizeof(m_aInfo));		//モーション情報
	m_nNumAll = 0;				//モーション総数
	m_nType = 0;				//モーション種類
	m_nKey = 0;					//現在のキーナンバー
	m_nCounter = 0;				//モーションカウンター
	m_bFinish = false;			//終了したかどうか

	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{//ダブルポインタの初期化
		m_ppModel[nCntModel] = nullptr;
	}

	m_nNumModel = 0;	//モデルの総数

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CMotion::Uninit(void)
{
}

//========================================
//設定
//========================================
void CMotion::Set(int nType)
{
	m_nType = nType;

	//キーリセット
	m_nKey = 0;

	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{//MAX_MOTION分回す
		m_aInfo[nCntMotion].aKeyInfo[nCntMotion].nFrame;
	}
}

//========================================
//更新
//========================================
void CMotion::Update(void)
{
	//位置
	float fDiffPosX = 0;	//差分
	float fDiffPosY = 0;	//差分
	float fDiffPosZ = 0;	//差分

	//向き
	float fDiffRotX = 0;	//差分
	float fDiffRotY = 0;	//差分
	float fDiffRotZ = 0;	//差分

	//次の値
	int nNextKey = m_nKey + 1;	

	if (nNextKey >= m_aInfo[m_nType].nNumKey)
	{//次のキーが
		nNextKey = 0;
	}

	for (int nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{//パーツの最大分回す
		//モデルのポインタ
		CModel *pModel = m_ppModel[nCntParts];

		//位置取得
		D3DXVECTOR3 pos = pModel->GetPosition();

		//位置取得
		D3DXVECTOR3 rot = pModel->GetRot();

		//位置を算出
		fDiffPosX = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosX;
		fDiffPosY = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosY;
		fDiffPosZ = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fPosZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fPosZ;

		//向きを算出
		fDiffRotX = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotX;
		fDiffRotY = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotY;
		fDiffRotZ = m_aInfo[m_nType].aKeyInfo[nNextKey].aKey[nCntParts].fRotZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntParts].fRotZ;

		//位置
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

		//向き
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

		//位置反映
		pModel->SetPosition(pos + pModel->GetPos());

		//向き反映
		pModel->SetRot(rot + pModel->GetRotate());
	}

	//現在のキーを1つ進める
	m_nCounter++;

	if (m_aInfo[m_nType].aKeyInfo[nNextKey].nFrame < m_nCounter)
	{
		//現在のキー加算
		m_nKey++;

		//モーションカウンターリセット
		m_nCounter = 0;

		if (m_aInfo[m_nType].nNumKey <= m_nKey)
		{//キー総数が現在のキーより小さい
			//現在のキーリセット
			m_nKey = 0;
		}
	}
}

//========================================
//描画
//========================================
void CMotion::Draw(void)
{
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{//モデルの描画(全パーツ)
 		if (m_ppModel[nCntParts] != nullptr)
		{//m_apModelがnullptrの時
			m_ppModel[nCntParts]->Draw();
		}
	}
}

//========================================
//終了したかどうか
//========================================
bool CMotion::IsFinish(void)
{
	//終了したかどうかを返す
	return m_bFinish;
}

//========================================
//モーション情報の設定
//========================================
void CMotion::SetInfo(INFO info)
{
}

//========================================
//モデル設定
//========================================
void CMotion::SetModel(CModel *ppModel, int nNumModel)
{
	//ポインタ
	m_ppModel[nNumModel] = ppModel;

	//パーツ番号
	m_nNumModel++;
}

//========================================
//読み込み
//========================================
void CMotion::Load(char *pPath)
{
	//変数宣言
	char garbage[640];		//ゴミ格納用
	char FileName[32];		//各モデルのファイル名
	int nNumParts = 0;		//パーツ数
	int nIdx = 0;			//何番目のパーツか
	int nParent = 0;		//親子関係
	int nPartsIndex = 0;	//パーツの番号
	int nNum = 0;			//読み込む番号
	int nMotion = 0;		//何番目のモーションか
	int nCntKey = 0;		//何個目のキーか
	int nLoop = 0;			//ループするかしないか
	int nNumKey = 0;		//キー数
	int nFlame = 0;			//フレーム数
	float move = 0.0f;		//移動量
	int KeyCount = 0;
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);		//位置
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);		//向き

	//キー数
	int keysetCount = 0;

	//FILEのポインタ
	FILE *pFile = nullptr;

	//ファイルを開く
	pFile = fopen(pPath, "r");

	while (1)
	{//END_SCRIPTが来るまで繰り返す
		//不要な文字を捨てる
		fscanf(pFile, "%s", &garbage[0]);

		if (strcmp(&garbage[0], "END_SCRIPT") == 0)
		{//文字列がEND_SCRIPTのとき
			//抜け出す
			break;
		}

		//========================================
		//モデルファイルの読み込み
		//========================================
		if (strcmp(&garbage[0], "MODEL_FILENAME") == 0)
		{//文字列がMODEL_FILENAMEのとき
			//=捨てる
			fscanf(pFile, "%s", &garbage[0]);

			//ファイルの名前取得
			fscanf(pFile, "%s", &FileName[0]);

			//モデルの生成
			m_ppModel[nNum] = CModel::Create(&FileName[0]);

			//モデル設定
			SetModel(m_ppModel[nNum], nNum);

			//モデルの番号を加算する
			nNum++;
		}

		//========================================
		//モデル設定
		//========================================
		if (strcmp(&garbage[0], "CHARACTERSET") == 0)
		{//文字列がCHARACTERSETのとき
			while (1)
			{//文字列がEND_CHARACTERSETになるまで繰り返す
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_CHARACTERSET") == 0)
				{//文字列がEND_CHARACTERSETの時
					//抜け出す
					break;
				}

				if (strcmp(&garbage[0], "MOVE") == 0)
				{//文字列がMOVEの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//移動量を入れる
					fscanf(pFile, "%f", &move);
				}

				if (strcmp(&garbage[0], "NUM_PARTS") == 0)
				{//文字列がNUM_PARTSの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//パーツ数を入れる
					fscanf(pFile, "%d", &nNumParts);
				}

				if (strcmp(&garbage[0], "PARTSSET") == 0)
				{//文字列がPARTSSETの時
					while (1)
					{//END_PARTSSETが来るまで回す
						fscanf(pFile, "%s", &garbage[0]);

						if (strcmp(&garbage[0], "END_PARTSSET") == 0)
						{//文字列がEND_PARTSSETの時
							//パーツ数を加算
							nPartsIndex++;

							//抜け出す
							break;
						}

						if (strcmp(&garbage[0], "INDEX") == 0)
						{//文字列がINDEXの時
							//=捨てる
							fscanf(pFile, "%s", &garbage[0]);

							//何番目のパーツかの設定
							fscanf(pFile, "%d", &nIdx);

							//モデルの番号設定
							m_ppModel[nPartsIndex]->SetIndex(m_ppModel[nIdx]);
						}

						if (strcmp(&garbage[0], "PARENT") == 0)
						{//文字列がPARENTの時
							//=捨てる
							fscanf(pFile, "%s", &garbage[0]);

							//親子関係設定
							fscanf(pFile, "%d", &nParent);

							if (nParent == -1)
							{//親パーツが無い場合
								m_ppModel[nPartsIndex]->SetParent(nullptr);
							}
							else
							{//親パーツがある場合
								m_ppModel[nPartsIndex]->SetParent(m_ppModel[nParent]);
							}
						}

						if (strcmp(&garbage[0], "POS") == 0)
						{//文字列がPARENTの時
							//=捨てる
							fscanf(pFile, "%s", &garbage[0]);

							fscanf(pFile, "%f", &pos.x);
							fscanf(pFile, "%f", &pos.y);
							fscanf(pFile, "%f", &pos.z);

							//位置を設定
							m_ppModel[nPartsIndex]->SetPos(pos);
						}

						if (strcmp(&garbage[0], "ROT") == 0)
						{//文字列がPARENTの時
							//=捨てる
							fscanf(pFile, "%s", &garbage[0]);

							fscanf(pFile, "%f", &rot.x);
							fscanf(pFile, "%f", &rot.y);
							fscanf(pFile, "%f", &rot.z);

							//向きを設定
							m_ppModel[nPartsIndex]->SetRotate(rot);
						}
					}
				}
			}
		}

		//バーツ番号リセット
		nPartsIndex = 0;

		//========================================
		//モーション設定
		//========================================
		if (strcmp(&garbage[0], "MOTIONSET") == 0)
		{//文字列がMOTIONSETの時
			//パーツ数リセット

			while (1)
			{//END_PARTSSETが来るまで回す
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_MOTIONSET") == 0)
				{//文字列がEND_PARTSSETの時
					//パーツ数を加算
					nPartsIndex++;

					//抜け出す
					break;
				}

				if (strcmp(&garbage[0], "LOOP") == 0)
				{//文字列がINDEXの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//親子関係設定
					fscanf(pFile, "%d", &nLoop);

					if (nLoop == 0)
					{//nLoopが0の時
						m_aInfo[nPartsIndex].bLoop = false;
					}
					if (nLoop == 1)
					{//nLoopが1の時
						m_aInfo[nPartsIndex].bLoop = true;
					}
				}

				if (strcmp(&garbage[0], "NUM_KEY") == 0)
				{//文字列がNUM_KEYの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//親子関係設定
					fscanf(pFile, "%d", &m_aInfo[nPartsIndex].nNumKey);
				}

				if (strcmp(&garbage[0], "KEYSET") == 0)
				{//文字列がPARENTの時
					while (1)
					{//END_KEYSETが来るまで繰り返す
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						if (strcmp(&garbage[0], "END_KEYSET") == 0)
						{//文字列がEND_PARTSSETの時

							//加算する
							keysetCount++;
							KeyCount = 0;
							//抜け出す
							break;
						}

						if (strcmp(&garbage[0], "FRAME") == 0)
						{//文字列がFRAMEの時
							//=捨てる
							fscanf(pFile, "%s", &garbage[0]);

							//フレーム数
							fscanf(pFile, "%d", &m_aInfo[nPartsIndex].aKeyInfo[keysetCount].nFrame);
						}

						if (strcmp(&garbage[0], "KEY") == 0)
						{//文字列がKEYの時
							while (1)
							{//END_KEYが来るまで繰り返す
								//=捨てる
								fscanf(pFile, "%s", &garbage[0]);

								if (strcmp(&garbage[0], "END_KEY") == 0)
								{//文字列がEND_KEYの時

									//加算する
									KeyCount++;

									//抜け出す
									break;
								}

								if (strcmp(&garbage[0], "POS") == 0)
								{//文字列がPOSの時
									//=捨てる
									fscanf(pFile, "%s", &garbage[0]);

									fscanf(pFile, "%f", &pos.x);
									fscanf(pFile, "%f", &pos.y);
									fscanf(pFile, "%f", &pos.z);

									//位置を設定
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosX = pos.x;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosY = pos.y;
									m_aInfo[nPartsIndex].aKeyInfo[keysetCount].aKey[KeyCount].fPosZ = pos.z;
								}

								if (strcmp(&garbage[0], "ROT") == 0)
								{//文字列がROTの時
									//=捨てる
									fscanf(pFile, "%s", &garbage[0]);

									fscanf(pFile, "%f", &rot.x);
									fscanf(pFile, "%f", &rot.y);
									fscanf(pFile, "%f", &rot.z);

									//位置を設定
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
	//ファイルを閉じる
	fclose(pFile);
}
