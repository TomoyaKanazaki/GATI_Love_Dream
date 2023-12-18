//========================================
//
//シューティングアクション[time.cpp]
//Author：森川駿弥
//
//========================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//========================================
//マクロ定義
//========================================
#define TIME_TEX		"data\\texture\\time.png"		//テクスチャへのパス
#define TIME_SPACE		(40.0f)		//タイムの桁数毎の間隔
#define TIME_POSX		(900.0f)	//タイムのX座標
#define TIME_POSY		(35.0f)		//タイムのY座標
#define TIME_VALUE		(120)		//タイムの値

//========================================
//コンストラクタ
//========================================
CTime::CTime()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Time = 0;			//タイムの値
	m_nCounterTimer = 0;	//タイムカウンター

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;		//CNumberの配列
	}
}

//========================================
//デストラクタ
//========================================
CTime::~CTime()
{
}

//========================================
//タイム生成
//========================================
CTime *CTime::Create(void)
{
	//CTime型のポインタ
	CTime *pTime = nullptr;

	if (pTime == nullptr)
	{//pTimeがnullptrの時
		//タイムの生成
		pTime = new CTime;

		//位置の初期化
		pTime->m_pos = D3DXVECTOR3(TIME_POSX, TIME_POSY, 0.0f);

		//初期化
		pTime->Init();

		//タイムの初期値
		pTime->SetTime(TIME_VALUE);
	}

	//ポインタを返す
	return pTime;
}

//========================================
//初期化
//========================================
HRESULT CTime::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{//nullptrの時
			//タイムの生成
			m_apNumber[nCnt] = CNumber::Create();

			if (m_apNumber[nCnt] != nullptr)
			{
				m_apNumber[nCnt]->BindTexture(pTexture->Regist(TIME_TEX));

				//タイムのサイズ
				m_apNumber[nCnt]->SetSize(70.0f, 70.0f);

				D3DXVECTOR3 posNum = m_pos;

				//桁数の間隔
				posNum.x += nCnt * 70.0f;

				//位置の設定
				m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(posNum.x - 350.0f, 40.0f, 0.0f));
			}
		}
	}

	//タイムの値
	m_Time = TIME_VALUE;

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	//自分自身の破棄
	CObject::Release();
}

//========================================
//更新
//========================================
void CTime::Update(void)
{
	//カウンター加算
	m_nCounterTimer++;

	if (m_nCounterTimer >= 60)
	{//カウンターが60を超えたら
		//タイム減算
		SubTime(1);

		m_nCounterTimer = 0;
	}

	if (m_Time == 0)
	{//0になったらタイマーを止める
		m_Time = 0;
	}
}

//========================================
//描画
//========================================
void CTime::Draw(void)
{
}

//========================================
//タイム設定
//========================================
void CTime::SetTime(int nTime)
{
	m_Time = nTime;

	int aTexU[TIME_DIGIT];  //各桁の数字を格納

	aTexU[0] = m_Time % 1000 / 100;
	aTexU[1] = m_Time % 100 / 10;
	aTexU[2] = m_Time % 10 / 1;

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{//桁数分回す
		//アニメーション頂点座標(パターンの最大数、現在のパターン)
		m_apNumber[nCnt]->SetVertexAnim(10, aTexU[nCnt]);
	}
}

//========================================
//頂点情報
//========================================
void CTime::SetVertex(void)
{
}

//========================================
//サイズ調整
//========================================
void CTime::SetSize(float fWidht, float fHeight)
{
}
