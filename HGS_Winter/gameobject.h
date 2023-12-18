//========================================
//
//ゲーム内オブジェクト[gameobject.h]
//Author：森川駿弥
//
//========================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "main.h"
#include "objectX.h"
#include "model.h"
#include "player.h"

//========================================
//マクロ定義
//========================================
#define GAME_OBJ	(2)		//ゲーム内オブジェクトの最大数

//========================================
//ゲーム内オブジェクトクラス
//========================================
class CGameObject : public CObject
{
public:
	CGameObject();		//コンストラクタ
	~CGameObject();		//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit();
	void Update();
	void Draw();
	void SetObject(CModel *ppModel, int nNumModel);

	static CGameObject *Create(void);	//プレイヤー生成
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//位置取得

	void LoadObj(char *pFilePath);

	CModel **GetModel(void) { return &m_ppModel[0]; }	//モデル取得

private:
	//メンバ変数
	CModel *m_ppModel[GAME_OBJ];	//モデルへのポインタ
	CObjectX *m_pObjX;		//オブジェクトXのポインタ
	CPlayer *m_pPlayer;		//プレイヤーのポインタ

	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;		//向き

	int m_nNumModel;	//モデルの総数
};

#endif
