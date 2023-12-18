//========================================
//
//シューティングアクション[motion.h]
//Author：森川駿弥
//
//========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "model.h"

//========================================
//マクロ定義
//========================================
#define MAX_MODEL	(10)	//パーツの最大数
#define MAX_MOTION	(2)		//モーションの最大数
#define MAX_KEY		(2)		//キーの総数

//========================================
//モーションクラス
//========================================
class CMotion
{
public:
	typedef struct 
	{//キーの構造体
		float fPosX;	//位置X
		float fPosY;	//位置Y
		float fPosZ;	//位置Z
		float fRotX;	//向きX
		float fRotY;	//向きY
		float fRotZ;	//向きZ
	}KEY;	//位置・向き

	typedef struct
	{//キー情報の構造体
		int nFrame;				//再生フレーム
		KEY aKey[MAX_MODEL];	//各モデルのキー要素
	}KEY_INFO;		//カットシーン

	typedef struct 
	{//モーション情報の構造体
		bool bLoop;		//ループするかどうか
		int nNumKey;	//キーの総数
		KEY_INFO aKeyInfo[MAX_MODEL];	//キー情報
	}INFO;

	CMotion();		//コンストラクタ
	~CMotion();		//デストラクタ

	//メンバ関数
	static CMotion *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Set(int nType);
	void Update(void);
	void Draw(void);
	int GetType(void) { return m_nType; }	//種類取得
	bool IsFinish(void);

	void SetInfo(INFO info);
	void SetModel(CModel *ppModel, int nNumModel);

	CModel **GetModel(void) { return &m_ppModel[0]; }

	void Load(char *pPath);

private:
	//メンバ変数
	INFO m_aInfo[MAX_MOTION];	//モーション情報
	int m_nNumAll;		//モーション総数
	int m_nType;		//モーション種類
	int m_nKey;			//現在のキーナンバー
	int m_nCounter;		//モーションカウンター
	bool m_bFinish;		//終了したかどうか
	CModel *m_ppModel[MAX_PARTS];	//モデルへのダブルポインタ
	int m_nNumModel;	//モデルの総数
	D3DXVECTOR3 m_pos;	//位置

	D3DXVECTOR3 m_rot;	//向き

	CModel *m_pParent;	//親モデルへのポインタ
	D3DXMATRIX m_mtxWorld;			//ワールドマトリックス
	LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	DWORD m_dwNumMat;				//マテリアルの数
	LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャ

};

#endif
