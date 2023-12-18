//=======================================
//
//エフェクト処理[effect.cpp]
//Author : MORIKAWA SHUNYA
//
//=======================================

#include "effect.h"      //作成したeffect.hをインクルードする
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===========================================
//マクロ定義
//===========================================
#define EFFECT_LIFE		(100)		//エフェクトの寿命
#define EFFECT_MOVE		(10.0f)		//エフェクトの移動量

//===========================================
//コンストラクタ
//===========================================
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
	m_fRadius = 0.0f;	//半径(大きさ)
	m_nLife = 0;		//寿命(表示時間)
	m_nType = 0;		//種類
	bool m_balpha = false;			//加算合成

}

//===========================================
//デストラクタ
//===========================================
CEffect::~CEffect()
{
}

//===========================================
//生成
//===========================================
CEffect *CEffect::Create(void)
{
	//CEffect型のポインタ
	CEffect *pEffect = nullptr;

	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	if (pEffect == nullptr)
	{//nullptrの時
		//インスタンス生成
		pEffect = new CEffect;

		//初期化
		pEffect->Init();

		//テクスチャ割り当て
		pEffect->BindTexture(pTexture->Regist("data\\texture\\effect000.png"));
	}

	//ポインタを返す
	return pEffect;
}

//===========================================
//エフェクトの初期化処理
//===========================================
HRESULT CEffect::Init(void)
{
	//初期化
	CBillboard::Init();

	//成功を返す
	return S_OK;
}

//===========================================
//エフェクトの終了処理
//===========================================
void CEffect::Uninit(void)
{
	//終了
	CBillboard::Uninit();
}

//===========================================
//エフェクトの更新処理
//===========================================
void CEffect::Update(void)
{
	//更新
	CBillboard::Update();

	//弾の移動
	D3DXVECTOR3 pos = GetPosition();

	//弾の位置更新
	pos += m_move;

	//半径
	m_fRadius += ((float)(rand() % 100) / 100.0f - 0.3f) * 5.0f;

	//α値(消える速度)
	m_col.a -= 0.01f;

	//体力減算
	m_nLife--;

	if (m_nLife < 0)
	{
		//破棄する
		Uninit();
	}
}

//===========================================
//エフェクトの描画処理
//===========================================
void CEffect::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//描画
	CBillboard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
