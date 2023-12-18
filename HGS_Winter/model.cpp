//========================================
//
//シューティングアクション[model.cpp]
//Author：森川駿弥
//
//========================================
#include "model.h"
#include "renderer.h"
#include "manager.h"

//========================================
//コンストラクタ
//========================================
CModel::CModel() : 
	m_pTexture(nullptr),		//共有テクスチャ
	m_pMesh(nullptr),			//メッシュ(頂点情報)へのポインタ
	m_pBuffMat(nullptr),		//マテリアルへのポインタ
	m_dwNumMat(NULL),			//マテリアルの数
	m_pos(0.0f, 0.0f, 0.0f),	//位置
	m_rot(0.0f, 0.0f, 0.0f),	//向き
	m_pParent(nullptr)			//親モデルへのポインタ
{

}

//========================================
//デストラクタ
//========================================
CModel::~CModel()
{

}

//========================================
//モデル生成
//========================================
CModel *CModel::Create(const char *pFilename)
{
	//CModel型のポインタ
	CModel *pModel = nullptr;

	if (pModel == nullptr)
	{
		//プレイヤー生成
		pModel = new CModel;

		//初期化
		pModel->Init(pFilename);
	}

	//ポインタを返す
	return pModel;
}

//========================================
//初期化
//========================================
HRESULT CModel::Init(const char *pFilename)
{
	//ローカル変数宣言
	D3DXMATERIAL *pMat;

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_dwNumMat,
		&m_pMesh);

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)m_dwNumMat; nCntTex++)
	{
		if (pMat[nCntTex].pTextureFilename != nullptr)
		{//テクスチャファイル名が存在する
		 //テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntTex].pTextureFilename, &m_pTexture);
		}
	}
	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CModel::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//========================================
//更新
//========================================
void CModel::Update(void)
{

}

//========================================
//描画
//========================================
void CModel::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	D3DXMATRIX mtxParent;			//親モデルのマトリックス

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{//親が存在する
		//親モデルのマトリックスを取得する
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//親が存在しない
		//現在(最新)のマトリックスを取得する{ = プレイヤーのマトリックス}
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{//マテリアルの数分回す
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture); //テクスチャを使用してないときはnullptr

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================================
//親モデル
//========================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//========================================
//ワールドマトリックスの取得
//========================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//========================================
//頂点情報
//========================================
void CModel::SetVertex(void)
{

}

//========================================
//サイズ調整
//========================================
void CModel::SetSize(float fWidht, float fHeight)
{

}

//========================================
//位置設定
//========================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================
//位置取得
//========================================
D3DXVECTOR3 CModel::GetPosition(void)
{
	return m_pos;
}

//========================================
//向き設定
//========================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================
//向き取得
//========================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//========================================
//モデルの番号設定
//========================================
void CModel::SetIndex(CModel *pModel)
{
	m_pParent = pModel;
}

//========================================
//モデルの番号設定
//========================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_setPos = pos;
}

//========================================
//モデルの位置取得
//========================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_setPos;
}

//========================================
//モデルの向き
//========================================
void CModel::SetRotate(D3DXVECTOR3 rot)
{
	m_setRot = rot;
}

//========================================
//モデルの位置取得
//========================================
D3DXVECTOR3 CModel::GetRotate(void)
{
	return m_setRot;
}
