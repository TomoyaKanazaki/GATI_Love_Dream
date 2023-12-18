//========================================
//
//シューティングアクション[object.cp]
//Author：森川駿弥
//
//========================================
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "texture.h"

//========================================
//静的メンバ変数宣言
//========================================
CObject *CObject::m_apObject[MAX_DATA] = {};
int CObject::m_nNumAll = 0;

//========================================
//コンストラクタ
//========================================
CObject::CObject(void)
{//値クリア
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] == nullptr)
		{
			m_apObject[nCntObject] = this;	//自分自身を代入
			m_nID = nCntObject;				//自分自身のID
			m_nNumAll++;					//総数をカウントアップ
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
			break;
		}
	}
}

//========================================
//デストラクタ
//========================================
CObject::~CObject(void)
{
}

//========================================
//すべてのオブジェクトの破棄
//========================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//========================================
//すべてのオブジェクトの更新
//========================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Update();
		}
	}
}

//========================================
//すべてのオブジェクトの描画
//========================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//カメラ設定
	pCamera->SetCamera();

	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//========================================
//オブジェクトの破棄
//========================================
void CObject::Release(void)
{
	int nNum = m_nID;

	if (m_apObject[nNum] != nullptr)
	{
		//オブジェクト(自分自身の破棄)
		delete m_apObject[nNum];
		m_apObject[nNum] = nullptr;

		//総数をカウントダウン
		m_nNumAll--;
	}
}

//========================================
//TYPEの取得
//========================================
CObject *CObject::GetObject(int nIdx)
{
	return m_apObject[nIdx];
}

//========================================
//テクスチャの割り当て
//========================================
void CObject::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}