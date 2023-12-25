//==========================================================
//
// NPCの処理 [npc.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _NPC_H_		// このマクロが定義されていない場合
#define _NPC_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// 前方宣言
class CShadow;
class CCharacter;
class CWaist;
class CObject2D;
class CObjectBillboard;
class CModel;
class CLockOn;
class CMeshOrbit;
class CObject3D;
class CEnemy;

//==========================================================
// プレイヤーのクラス定義(派生クラス)
//==========================================================
class CNpc : public CTask
{
private:	// 自分だけがアクセス可能な定義

			// 状態列挙型
	enum STATE
	{
		STATE_NEUTRAL = 0,	// 待機状態
		STATE_MOVE,		// 移動状態
		STATE_STOP,		// 停止状態
		STATE_WAIT,		// 待機
		STATE_DEATH,
		STATE_MAX
	};

	// 情報構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 posOld;	// 設定位置
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		D3DXVECTOR3 posDiff;
		STATE state;			// 状態
		float fStateCounter;	// 状態管理カウンター
	}SInfo;

public:	// 誰でもアクセス可能

	CNpc();	// コンストラクタ
	~CNpc();	// デストラクタ

				// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CNpc *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move);

	// メンバ関数(設定)
	void SetMove(const D3DXVECTOR3& move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3& pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3& pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_Info.rot = rot; }
	void SetType(TYPE type);

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	static CNpc *GetTop(void) { return m_pTop; }
	CNpc *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);
	static int GetNum(void) { return m_nNumCount; }

private:	// 自分だけがアクセス可能

			// メンバ関数
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void KeyBoardRotation(void);
	void LockOn(void);

	// メンバ変数
	static CNpc *m_pTop;	// 先頭のオブジェクトへのポインタ
	static CNpc *m_pCur;	// 最後尾のオブジェクトへのポインタ
	CNpc *m_pPrev;		// 前のオブジェクトへのポインタ
	CNpc *m_pNext;		// 次のオブジェクトへのポインタ
	SInfo m_Info;			// 自分自身の情報
	CEnemy *m_pTarget;	// 目標
	CCharacter *m_pObject;	// 描画オブジェクト
	float m_fRotMove;		// 現在の角度
	float m_fRotDiff;		// 目的の角度
	float m_fRotDest;		// 角度計算
	int m_nLife;	// 体力
	static int m_nNumCount;
};

#endif
