//========================================
//
//シューティングアクション[title.cpp]
//Author：森川駿弥
//
//========================================
#include "title.h"

//=======================================
//マクロ定義
//=======================================
#define TITLE_TEX	"data\\TEXTURE\\Title.png"

//=======================================
//コンストラクタ
//=======================================
CTitle::CTitle() :
	m_pObj2D(nullptr)
{
}

//=======================================
//デストラクタ
//=======================================
CTitle::~CTitle()
{
}

//=======================================
//生成
//=======================================
CTitle *CTitle::Create(void)
{
	//タイトルのポインタ
	CTitle *pTitle = nullptr;

	if (pTitle == nullptr)
	{
		//インスタンス生成
		pTitle = new CTitle;

		//初期化
		pTitle->Init();
	}

	//ポインタを返す
	return pTitle;
}

//=======================================
//初期化
//=======================================
HRESULT CTitle::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (m_pObj2D == nullptr)
	{
		//CObject2Dのポインタ
		m_pObj2D = CObject2D::Create();

		//位置取得
		D3DXVECTOR3 pos = m_pObj2D->GetPosition();

		//頂点情報
		m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

		//ポリゴンの位置
		pos = (D3DXVECTOR3(640.0f, 360.0f, 0.0f));

		//位置設定
		m_pObj2D->SetPosition(pos);

		//テクスチャ割り当て
		m_pObj2D->BindTexture(pTexture->Regist(TITLE_TEX));
	}

	//成功を返す
	return S_OK;
}

//=======================================
//終了
//=======================================
void CTitle::Uninit(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Uninit();
		m_pObj2D = nullptr;
	}
}

//=======================================
//更新
//=======================================
void CTitle::Update(void)
{
	//CInputKeyboard型のポインタ
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//CInputPad型のポインタ
	CInputPad *pInputPad = nullptr;
	pInputPad = CManager::GetInstance()->GetInputPad();			//コントローラーの情報取得

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || 
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0) == true ||
		pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) == true)
	{
		//モード設定
		CManager::SetMode(CScene::MODE_TUTORIAL);
	}
}

//=======================================
//描画
//=======================================
void CTitle::Draw(void)
{
}
