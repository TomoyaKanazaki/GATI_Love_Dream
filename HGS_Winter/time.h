//========================================
//
//シューティングアクション[time.h]
//Author：森川駿弥
//
//========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "number.h"

//========================================
//マクロ定義
//========================================
#define TIME_DIGIT	(3)		//タイムの桁数

//========================================
//タイムクラス
//========================================
class CTime : public CObject
{
public:
	CTime();	//コンストラクタ
	~CTime();	//デストラクタ

				//メンバ関数
	static CTime *Create(void);	//敵生成

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime);
	void SubTime(int nTime) {SetTime(m_Time - nTime);}	//タイム減算
	int GetTime(void) { return m_Time; }

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	//メンバ変数
	D3DXVECTOR3 m_pos;
	int m_nIdxTexture;		//テクスチャの番号
	int m_Time;				//タイムの値
	int m_nCounterTimer;	//タイムカウンター
	CNumber *m_apNumber[TIME_DIGIT];		//CNumberの配列
};

#endif