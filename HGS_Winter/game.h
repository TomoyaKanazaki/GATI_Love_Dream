//========================================
//
//ゲーム内処理[game.h]
//Author：森川駿弥
//
//========================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"

//========================================
//前方宣言
//========================================
class CObjectX;
class CObject3D;
class CLight;
class CPlayer;
class CPolygon;
class CGameObject;
class CBg;
class CTime;

//========================================
//マクロ
//========================================
#define MAX_ITEM	(256)	//アイテムの最大数
#define MAX_BULLET	(80)	//弾の最大数

//========================================
//ゲームクラス
//========================================
class CGame : public CScene
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	//メンバ関数
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PauseState(bool bPauseState) { m_bPause = bPauseState; }	//ポーズ状態かどうか

	static CGame *GetGame(void) { return m_pGame; }		//ゲームマネージャーの情報
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	static CObject *m_pObject[MAX_DATA];		//オブジェクトのポインタ
	static CObjectX *m_pObjectX;		//Xファイルオブジェクトのポインタ
	static CObject3D *m_pObject3D;		//オブジェクト3Dのポインタ
	static CGame *m_pGame;				//ゲームマネージャーのポインタ
	static CLight *m_pLight;			//ライトのポインタ
	static CPlayer *m_pPlayer;			//プレイヤーのポインタ
	static CPolygon *m_pPolygon;		//ポリゴンのポインタ
	static CGameObject *m_pGameObject;	//ゲーム内オブジェクト
	static CBg *m_pBg;					//背景のポインタ
	static CTime *m_pTime;				//タイムのポインタ
	bool m_bPause;						//ポーズ状態のON/OFF
};

#endif
