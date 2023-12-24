//==========================================================
//
// オブジェクト3Dの処理全般 [object3D.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECT3D_H_	 // このマクロが定義されていない場合
#define _OBJECT3D_H_	 // 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"

//**********************************************************
// オブジェクト3Dクラスの定義
//**********************************************************
class CObject3D : public CObject
{
public:	// 誰でもアクセス可能

	CObject3D(int nPriority = 5);	// コンストラクタ
	~CObject3D();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject3D *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
	void SetpVtx(float fWidth, float fHeight);
	void SetTextureVtx(float fWidth, float fHeight);
	void BindTexture(int nIdx);

	// メンバ関数(設定)
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetSize(float fWidth, float fHeight);
	float GetHeight(void) { return m_fHeight; }
	void SetCol(D3DXCOLOR col);
	float GetWidth(void) { return m_fWidth; }
	void SetMtx(void);
	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	CObject2D *GetObject2D(void) { return NULL; }
	float GetHeight(const D3DXVECTOR3& pos, D3DXVECTOR3 &normal);

private:	// 自分だけがアクセス可能

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	int m_nIdxTexture;		// テクスチャ番号
	float m_fWidth;		// 幅
	float m_fHeight;	// 高さ
};

#endif
