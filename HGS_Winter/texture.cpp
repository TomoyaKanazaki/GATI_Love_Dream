//========================================
//
//シューティングアクション[texture.cpp]
//Author：森川駿弥
//
//========================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//一括管理
const char *str[] = {"data\\texture\\Player.png"};

//========================================
//静的メンバ変数
//========================================
int CTexture::m_nNumAll = 0;

//========================================
//コンストラクタ
//========================================
CTexture::CTexture()
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_apTexture[nCntTex] = {};	//テクスチャのポインタ
		m_apPath[nCntTex] = "\0";
	}
}

//========================================
//デストラクタ
//========================================
CTexture::~CTexture()
{

}

//========================================
//テクスチャ一括読み込み
//========================================
HRESULT CTexture::Load(void)
{
	////CRenderer型のポインタ
	//CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	//{//全てのテクスチャの読み込み
	//	if (FAILED(D3DXCreateTextureFromFile(pDevice,
	//		str[nCntTex],
	//		&m_apTexture[nCntTex])))
	//	{// 失敗を返す
	//		return E_FAIL;
	//	}
	//}

	return S_OK;
}

//========================================
//テクスチャ破棄
//========================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{//テクスチャの終了処理
		if (m_apTexture[nCntTex] != nullptr)
		{//m_apTexture[nCntTex]がnullptrじゃないとき
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = nullptr;
		}
	}
}

//========================================
//テクスチャ個別割り当て
//========================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (strcmp(m_apPath[nCntTex], pFilename) == 0)
		{//ファイル名が一致したとき
			//nCntTex番目を返す
			return nCntTex;
		}

		if (m_apTexture[nCntTex] == nullptr)
		{//nullptrの時
			//CRenderer型のポインタ
			CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

			//指定のテクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[nCntTex]);

			//ファイル名を入れる
			m_apPath[nCntTex] = pFilename;

			//総数をカウントアップ
			m_nNumAll++;

			//nCntTex番目を返す
			return nCntTex;
		}
	}

	//NULLを返す
	return NULL;
}

//========================================
//テクスチャのアドレス取得
//========================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx >= 0 && nIdx <= m_nNumAll)
	{
		return m_apTexture[nIdx];
	}

	//nullptrを返す
	return nullptr;
}