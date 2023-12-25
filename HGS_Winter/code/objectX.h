//==========================================================
//
// Xファイルモデルの処理全般 [objectX.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

// マクロ定義
#define NUM_TEXTURE	(64)	// テクスチャ最大数

//**********************************************************
// Xファイルモデルクラスの定義
//**********************************************************
class CObjectX : public CObject
{
public:	// 誰でもアクセス可能

	CObjectX(int nPriority = 0);	// コンストラクタ
	virtual ~CObjectX();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindFile(int nIdx);

	static CObjectX *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char *pFileName, const int nPriority = 4);
	static bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
	void SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot);

	// メンバ関数(設定)
	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(const D3DXVECTOR3& rot);
	void SetMaterial(const D3DMATERIAL9& Material) { m_ChangeMat = Material; }
	void ChangeCol(bool bValue = false) { m_bChangeCol = bValue; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DMATERIAL9 GetMaterial(void) const { return m_ChangeMat; }
	CObject2D *GetObject2D(void) { return NULL; }
	virtual D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
	int GetIdx(void) { return m_nIdxModel; }
	void ListOut(void);
	int GetModelType(void) { return m_nIdxModel; }

protected:

	// メンバ関数
	virtual bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
	void ResetMaterial(const char* pFileName); // 変更後マテリアルの初期化

private:	// 自分だけがアクセス可能
	
	// メンバ関数
	

	// メンバ変数c
	static CObjectX *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CObjectX *m_pCur;	// 最後尾のオブジェクトへのポインタ

	bool m_bChangeCol;		// 色変更をするかどうか
	D3DMATERIAL9 m_ChangeMat;	// 変更後の色
	CObjectX *m_pPrev;		// 前のオブジェクトへのポインタ
	CObjectX *m_pNext;		// 次のオブジェクトへのポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	int m_nIdxModel;			// モデル番号
};

#endif
