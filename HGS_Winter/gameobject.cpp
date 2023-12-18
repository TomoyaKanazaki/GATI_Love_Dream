//========================================
//
//ゲーム内オブジェクト[gameobject.h]
//Author：森川駿弥
//
//========================================
#include "gameobject.h"
#include "renderer.h"

//========================================
//コンストラクタ
//========================================
CGameObject::CGameObject() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_nNumModel(0)
{
	m_ppModel[GAME_OBJ] = {};
}

//========================================
//デストラクタ
//========================================
CGameObject::~CGameObject()
{
}

//========================================
//初期化
//========================================
HRESULT CGameObject::Init(void)
{
	//オブジェクト生成
	m_ppModel[0] = CModel::Create("data\\MODEL\\object\\woodbox.x");

	//パーツの位置(全パーツ分)
	m_ppModel[0]->SetPosition(D3DXVECTOR3(0.0f, 12.5f, 0.0f));

	//ファイル読み込み
	//LoadObj("data\\FILE\\object.txt");

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CGameObject::Uninit()
{
	//オブジェクト(自分自身)の破棄
	Release();
}

//========================================
//更新
//========================================
void CGameObject::Update()
{
}

//========================================
//描画
//========================================
void CGameObject::Draw()
{
	//描画
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置取得
	D3DXVECTOR3 pos = GetPosition();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//========================================
//生成
//========================================
CGameObject *CGameObject::Create(void)
{
	//CGameObject型のポインタ
	CGameObject *pGameObject = nullptr;

	if (pGameObject == nullptr)
	{
		//インスタンス生成
		pGameObject = new CGameObject;

		//初期化
		pGameObject->Init();
	}

	//ポインタを返す
	return pGameObject;
}

//========================================
//オブジェクト設定
//========================================
void CGameObject::SetObject(CModel * ppModel, int nNumModel)
{
	//ポインタ
	m_ppModel[nNumModel] = ppModel;

	//パーツ番号
	m_nNumModel++;
}

//========================================
//ファイル読み込み
//========================================
void CGameObject::LoadObj(char * pFilePath)
{
	//変数宣言
	char garbage[640];		//ゴミ格納用
	char FileName[32];		//各モデルのファイル名
	int nIdx = 0;			//何番目のパーツか
	int nNumParts = 0;		//パーツ数
	int nNum = 0;			//読み込む番号
	int nModelIndex = 0;	//パーツの番号

	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);		//位置
	D3DXVECTOR3 rot(0.0f, 0.0f, 0.0f);		//向き

	//FILEのポインタ
	FILE *pFile = nullptr;

	//ファイルを開く
	pFile = fopen(pFilePath, "r");

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
		//オブジェクトファイルの読み込み
		//========================================
		if (strcmp(&garbage[0], "OBJECT_FILENAME") == 0)
		{//文字列がOBJECT_FILENAMEのとき
			//=捨てる
			fscanf(pFile, "%s", &garbage[0]);

			//ファイルの名前取得
			fscanf(pFile, "%s", &FileName[0]);

			//モデルの生成
			m_ppModel[nNum] = CModel::Create(&FileName[0]);

			//モデル設定
			SetObject(m_ppModel[nNum], nNum);

			//モデルの番号を加算する
			nNum++;
		}

		//========================================
		//オブジェクト設定
		//========================================
		if (strcmp(&garbage[0], "MODELSET") == 0)
		{//文字列がOBJECTSETの場合
			while (1)
			{//文字列がEND_OBJECTSETになるまで繰り返す
				fscanf(pFile, "%s", &garbage[0]);

				if (strcmp(&garbage[0], "END_MODELSET") == 0)
				{//文字列がEND_CHARACTERSETの時
					//抜け出す
					break;
				}

				if (strcmp(&garbage[0], "NUM_OBJECT") == 0)
				{//文字列がNUM_PARTSの時
					//=捨てる
					fscanf(pFile, "%s", &garbage[0]);

					//パーツ数を入れる
					fscanf(pFile, "%d", &nNumParts);
				}
			}

			if (strcmp(&garbage[0], "OBJECTSET") == 0)
			{//文字列がPARTSSETの時
				while (1)
				{//END_PARTSSETが来るまで回す
					fscanf(pFile, "%s", &garbage[0]);

					if (strcmp(&garbage[0], "END_OBJECTSET") == 0)
					{//文字列がEND_PARTSSETの時
						//パーツ数を加算
						nModelIndex++;

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
						m_ppModel[nModelIndex]->SetIndex(m_ppModel[nIdx]);
					}

					if (strcmp(&garbage[0], "POS") == 0)
					{//文字列がPARENTの時
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);

						//位置を設定
						m_ppModel[nModelIndex]->SetPos(pos);
					}

					if (strcmp(&garbage[0], "ROT") == 0)
					{//文字列がPARENTの時
						//=捨てる
						fscanf(pFile, "%s", &garbage[0]);

						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);

						//向きを設定
						m_ppModel[nModelIndex]->SetRotate(rot);
					}
				}
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}

//========================================
//3Dオブジェクトの生成
//========================================
void CGameObject::SetVertex(void)
{
}

//========================================
//3Dオブジェクトの生成
//========================================
void CGameObject::SetSize(float fWidht, float fHeight)
{
}
