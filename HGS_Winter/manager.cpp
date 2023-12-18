//========================================
//
//マネージャー[manager.cp]
//Author：森川駿弥
//
//========================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "game.h"

//========================================
//静的メンバ変数
//========================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputPad *CManager::m_pInputPad = nullptr;
CScene *CManager::m_pScene = nullptr;
CTexture *CManager::m_pTexture = nullptr;
CDebugProc *CManager::m_pDebugProc = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CManager *CManager::m_pManager = nullptr;

//========================================
//コンストラクタ
//========================================
CManager::CManager(void) : 
	m_nCnt(0),	//自動遷移のカウンター
	m_state(0),	//状態変更
	m_NowScene(CScene::MODE_NONE)	//現在のシーン
{//値クリア
}

//========================================
//デストラクタ
//========================================
CManager::~CManager(void)
{
}

//========================================
//初期化
//========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == nullptr)
	{//g_pRendererがnullptrの時
		m_pRenderer = new CRenderer;
	}

	//レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//キーボードの生成
	if (m_pInputKeyboard == nullptr)
	{//m_pInputKeyboardがnullptrの時
		m_pInputKeyboard = new CInputKeyboard;
	}

	//キーボードの初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//コントローラーの生成
	if (m_pInputPad == nullptr)
	{//m_pInputKeyboardがnullptrの時
		m_pInputPad = new CInputPad;
	}

	//コントローラーの初期化処理
	if (FAILED(m_pInputPad->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//カメラ生成
	if (m_pCamera == nullptr)
	{//m_pCameraがnullptrの時
		m_pCamera = new CCamera;
	}

	//カメラの初期化処理
	if (FAILED(m_pCamera->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}

	//debugprocの生成
	if (m_pDebugProc == nullptr)
	{//m_pDebugProcがnullptrの時
		m_pDebugProc = new CDebugProc;

		//初期化
		m_pDebugProc->Init();
	}

	//テクスチャ生成
	m_pTexture = new CTexture;

	//モード設定
	SetMode(CScene::MODE_TITLE);

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CManager::Uninit(void)
{
	//オブジェクトの破棄
	CObject::ReleaseAll();
	
	//レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//キーボードの破棄
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//コントローラーの破棄
	if (m_pInputPad != nullptr)
	{
		m_pInputPad->Uninit();
		delete m_pInputPad;
		m_pInputPad = nullptr;
	}

	//カメラの破棄
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{//debugprocの破棄
		m_pDebugProc->Uninit();
	}

	if (m_pTexture != nullptr)
	{//テクスチャ破棄
		m_pTexture->Unload();

		//nullptrにする
		m_pTexture = nullptr;
	}
}

//========================================
//更新
//========================================
void CManager::Update(void)
{
	if (m_pRenderer != nullptr)
	{//g_pRendererがnullptrの時
		//更新処理
		m_pRenderer->Update();
	}

	//キーボードの更新
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//コントローラーの更新
	if (m_pInputPad != nullptr)
	{
		m_pInputPad->Update();
	}

	//カメラの更新
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	//DebugProの更新
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Update();
	}
	//シーンの更新
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

//========================================
//描画
//========================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{//g_pRendererがnullptrの時
		//描画処理
		m_pRenderer->Draw();
	}
}

//========================================
//モード設定
//========================================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{//モード破棄
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//全て破棄
	CObject::ReleaseAll();

	//モード生成
	m_pScene = CScene::Create(mode);
}

//========================================
//インスタンス取得
//========================================
CManager *CManager::GetInstance()
{
	if (m_pManager == nullptr)
	{//インスタンス生成
		return m_pManager = new CManager;
	}
	else
	{//ポインタを返す
		return m_pManager;
	}
}

//========================================
//コンストラクタ
//========================================
CScene::CScene() : 
	m_pVtxBuff(nullptr),	//頂点情報を格納
	m_nIdxTexture(0),		//テクスチャ番号
	m_mode(MODE_NONE)		//モード
{//値クリア
}

//========================================
//デストラクタ
//========================================
CScene::~CScene()
{
}

//========================================
//生成
//========================================
CScene *CScene::Create(int nMode)
{
	//CSceneのポインタ
	CScene *pScene = nullptr;

	if (pScene == nullptr)
	{
		switch (nMode)
		{
		case MODE_TITLE:
			//タイトルシーン生成
			pScene = CTitle::Create();
			break;

		case MODE_TUTORIAL:
			//タイトルシーン生成
			pScene = CTutorial::Create();
			break;

		case MODE_GAME:
			//タイトルシーン生成
			pScene = CGame::Create();
			break;

		case MODE_RESULT:
			//リザルトシーン
			pScene = CResult::Create();
			break;
		}

		//初期化
		pScene->Init();
	}

	//ポインタを返す
	return pScene;
}
 