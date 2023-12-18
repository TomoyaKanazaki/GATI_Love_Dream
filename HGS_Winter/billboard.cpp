//=======================================
//
//シューティングアクション[polygon.cpp]
//Author : MORIKAWA SHUNYA
//
//=======================================

#include "main.h"		//作成したmain.hをインクルードする
#include "billboard.h"  //作成したfade.hをインクルードする
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=======================================
//マクロ定義
//=======================================
#define BILLBOARD_TEX	"data\\TEXTURE\\LIFE.png"

#define BILL_WIDTH		(40)	//ビルボードの幅
#define BILL_HEIGHT		(40)	//ビルボードの高さ

#define BULLET_SIZE     (25)    //弾のサイズ

//========================================
//静的メンバ変数
//========================================
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = nullptr;	//テクスチャのポインタ

//=======================================
//コンストラクタ
//=======================================
CBillboard::CBillboard() : 
	m_nIdxTexture(0),		//テクスチャ番号
	m_pVtxBuff(nullptr),	//頂点情報
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//位置
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//移動量
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//向き
	m_col(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)),	//色
	m_fLength(0.0f),	//対角線の長さ
	m_fAngle(0.0f)		//対角線の長さ
{
}

//=======================================
//デストラクタ
//=======================================
CBillboard::~CBillboard()
{
}

//=======================================
//テクスチャ読み込み
//=======================================
HRESULT CBillboard::Load(void)
{
	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEX,
		&m_pTexture)))
	{// 失敗を返す
		return E_FAIL;
	}

	//成功を返す
	return S_OK;
}

//=======================================
//テクスチャ破棄
//=======================================
void CBillboard::Unload(void)
{
	//テクスチャの終了処理
	if (m_pTexture != nullptr)
	{//m_pTextureがnullptrじゃないとき
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//=======================================
//ビルボード生成
//=======================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, float fwidth, float fheight)
{
	//pBillboard型のポインタ
	CBillboard *pBillboard = nullptr;

	if (pBillboard == nullptr)
	{//pBillboardがnullptrの時
		//ビルボード生成
		pBillboard = new CBillboard;

		//サイズ設定
		pBillboard->SetSize(fwidth, fheight);

		//位置設定
		pBillboard->SetPosition(pos);

		//初期化
		pBillboard->Init();
	}

	//ポインタを返す
	return pBillboard;
}

//=======================================
//ビルボードの初期化処理
//=======================================
HRESULT CBillboard::Init(void)
{
	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=======================================
//ビルボードの終了処理
//=======================================
void CBillboard::Uninit(void)
{
	//頂点バッファの終了処理
	if (m_pVtxBuff != nullptr)
	{//m_pTextureがnullptrじゃないとき
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//オブジェクト(自分自身)の破棄
	Release();
}

//=======================================
//ビルボードの更新処理
//=======================================
void CBillboard::Update(void)
{
}

//=======================================
//ビルボードの描画処理
//=======================================
void CBillboard::Draw(void)
{
	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリクス取得用

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//CTexture型のポインタ
	CTexture *pTexture = CManager::GetTexture();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);	//逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture)); //テクスチャを使用してないときはnullptr

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=======================================
//テクスチャ割り当て
//=======================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//========================================
//テクスチャの割り当て
//========================================
void CBillboard::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}

//========================================
//弾の頂点座標
//========================================
void CBillboard::SetPosVertex(void)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//========================================
//アニメーションビルボードの頂点座標
//========================================
void CBillboard::SetVertexAnim(int Num, int Cnt)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の再設定
	pVtx[0].tex = D3DXVECTOR2(1.0f / Num * Cnt, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / Num * (Cnt + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / Num * Cnt, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / Num * (Cnt + 1), 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//========================================
//頂点情報のサイズ設定
//========================================
void CBillboard::SetSizeVertex(float fwidth, float fheight)
{
	m_fWidth = fwidth;
	m_fHeight = fheight;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-fwidth, fheight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fwidth, fheight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fwidth, -fheight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fwidth, -fheight, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//========================================
//ビルボードエフェクトの頂点座標
//========================================
void CBillboard::SetEffectVertex(float fEffectsize)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の再設定
	pVtx[0].pos = D3DXVECTOR3(-fEffectsize, fEffectsize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fEffectsize, fEffectsize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fEffectsize, -fEffectsize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fEffectsize, -fEffectsize, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//========================================
//ビルボードの移動量
//========================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================
//ビルボードの移動量取得
//========================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}

//========================================
//ビルボードの頂点座標
//========================================
void CBillboard::SetVertex(void)
{

}

//========================================
//弾ビルボードの頂点座標
//========================================
void CBillboard::SetSize(float fWidht, float fHeight)
{
	//対角線の長さ(横、縦)
	m_fLength = sqrtf(fWidht * fWidht + fHeight * fHeight) * 1.0f;

	//対角線の向き(横、縦)
	m_fAngle = atan2f(fWidht, fHeight);
}

//========================================
//位置設定
//========================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================
//位置取得
//========================================
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}