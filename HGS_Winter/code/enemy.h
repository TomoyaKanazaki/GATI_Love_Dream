//==========================================
//
//  攻撃対象クラス(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "objectX.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy : public CObjectX
{
public:

	// メンバ関数
	CEnemy(int nPriority = 0); // コンストラクタ
	~CEnemy(); // デストラクタ

	HRESULT Init(void) override; // 初期化処理
	void Uninit(void) override; // 終了処理
	void Update(void) override; // 更新処理
	void Draw(void) override; // 描画処理
	void Hit(); // 当たったよ
	CEnemy *GetNext(void) { return m_pNext; }

	// 静的メンバ関数
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority = 4);
	static CEnemy* GetTop(void) { return m_pTop; }

private:

	// メンバ関数
	bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) override;

	// メンバ変数
	// メンバ変数c
	static CEnemy *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CEnemy *m_pCur;	// 最後尾のオブジェクトへのポインタ

	CEnemy *m_pPrev;		// 前のオブジェクトへのポインタ
	CEnemy *m_pNext;		// 次のオブジェクトへのポインタ
	float m_Life; // オブジェクトの体力
};

#endif
