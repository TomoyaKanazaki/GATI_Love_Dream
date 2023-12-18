//========================================
//
//レンダラー[renderer.cp]
//Author：森川駿弥
//
//========================================
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"

//========================================
//コンストラクタ
//========================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;			//Direct3Dオブジェクトへのポインタ
	m_pD3DDevice = nullptr;		//Direct3Dデバイスへのポインタ
}

//========================================
//デストラクタ
//========================================
CRenderer::~CRenderer()
{

}

//========================================
//初期化処理
//========================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));  // パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;                          //ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			               //ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;                         //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                     //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                      //ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;                           //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;                   //24ビットZバッファ8ビットステンシルバッファ
	d3dpp.Windowed = bWindow;                                      //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//========================================
//終了処理
//========================================
void CRenderer::Uninit(void)
{
	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//========================================
//更新処理
//========================================
void CRenderer::Update(void)
{
	//すべてのオブジェクト更新
	CObject::UpdateAll();
}

//========================================
//描画処理
//========================================
void CRenderer::Draw(void)
{
	//画面クリア(バックバッファとZバッファ、ステンシルバッファのクリア)
	m_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//ステンシルバッファ有効
	m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//ステンシルバッファと比較する参照値の設定 => ref
	m_pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//ステンシルバッファの値に対してのマスク設定 => 0xff(全て真)
	m_pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//ステンシルバッファの比較方法 => (参照値 => ステンシルバッファの参照値)なら合格
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//ステンシルテスト結果に対しての反映設定
	m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		//ポリゴンの描画
		CObject::DrawAll();

		//ポインタ
		CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();

		//デバッグ表示
		pDebugProc->Draw();

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//========================================
//デバイスの取得
//========================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
