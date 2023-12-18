//========================================
//
//シューティングアクション[polygon.cpp]
//Author：森川駿弥
//
//========================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//========================================
//マクロ定義
//========================================
#define POLYGON_TEX		"data\\texture\\block001.jpg"

//========================================
//静的メンバ変数
//========================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = nullptr;

//========================================
//コンストラクタ
//========================================
CPolygon::CPolygon()
{
}

//========================================
//デストラクタ
//========================================
CPolygon::~CPolygon()
{
}

//========================================
//ポリゴン生成
//========================================
CPolygon *CPolygon::Create(void)
{
	//CPlayer型のポインタ
	CPolygon *pPolygon = nullptr;

	if (pPolygon == nullptr)
	{
		//プレイヤー生成
		pPolygon = new CPolygon;

		//初期化
		pPolygon->Init();
	}

	//ポインタを返す
	return pPolygon;
}

//========================================
//初期化
//========================================
HRESULT CPolygon::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (m_pObj3D == nullptr)
	{
		//CObject2Dのポインタ
		m_pObj3D = CObject3D::Create();

		//テクスチャ割り当て
		m_pObj3D->BindTexture(pTexture->Regist(POLYGON_TEX));
	}

	return S_OK;
}

//========================================
//終了
//========================================
void CPolygon::Uninit(void)
{
	//終了
	CObject3D::Uninit();
}

//========================================
//更新
//========================================
void CPolygon::Update(void)
{

}

//========================================
//描画
//========================================
void CPolygon::Draw(void)
{
	//描画
	CObject3D::Draw();
}