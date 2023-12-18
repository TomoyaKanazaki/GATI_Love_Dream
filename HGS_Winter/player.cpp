//========================================
//
//プレイヤー処理[player.cpp]
//Author：森川駿弥
//
//========================================
#include "player.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "debugproc.h"
#include "motion.h"
#include "model.h"
#include "game.h"
#include "effect.h"

//========================================
//マクロ定義
//========================================
#define PLAYER_SPEED	(1.0f)		//プレイヤーの移動速度
#define PLAYER_INERTIA	(0.3f)		//プレイヤーの慣性
#define PLAYER_DASH		(120)		//プレイヤーがダッシュ出来る時間
#define PLAYER_DASH_INTERVAL		(600)		//ダッシュ出来るまでの間隔
#define PLAYER_DASH_SPEED			(2.0f)		//ダッシュ時の速さ
#define PLAYER_JUMP		(95.0f)		//ジャンプ力の大きさ
#define PLAYER_GRAVITY	(5.5f)		//重力

#define MOTION_PATH	"data\\FILE\\player.txt"	//読み込むファイルのパス

//========================================
//コンストラクタ
//========================================
CPlayer::CPlayer() : 
	m_pTexture(nullptr),
	m_pos(0.0f, 0.0f, 0.0f),		//位置
	m_move(0.0f, 0.0f, 0.0f),		//移動量
	m_rot(0.0f, 0.0f, 0.0f),		//向き
	m_nIdxTexture(0),				//テクスチャの番号
	m_pMesh(nullptr),				//メッシュ(頂点情報)へのポインタ
	m_pBuffMat(nullptr),			//マテリアルへのポインタ
	m_dwNumMat(0),					//マテリアルの数
	m_apNumModel(0), 				//モデル(パーツ)の総数
	m_RotDest(0.0f, 0.0f, 0.0f),	//目的の向き
	m_bJump(false),
	m_bMove(false),
	m_bWait(false)
{//値をクリア
}

//========================================
//デストラクタ
//========================================
CPlayer::~CPlayer()
{
}

//========================================
//プレイヤーの生成
//========================================
CPlayer *CPlayer::Create(void)
{
	//CPlayer型のポインタ
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		//プレイヤー生成
		pPlayer = new CPlayer;

		//初期化
		pPlayer->Init();

		//プレイヤーの初期位置
		pPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//プレイヤーの初期向き
		pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//ポインタを返す
	return pPlayer;
}

//========================================
//初期化
//========================================
HRESULT CPlayer::Init(void)
{
	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0, 0.0f);

	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);

	//モーションのポインタ
	m_pMotion = nullptr;

	//目的の向き
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ジャンプしてるかどうか
	//m_bJump = false;

	if (m_pMotion == nullptr)
	{
		//モーション生成
		m_pMotion = CMotion::Create();

		//モーション読み込み
		m_pMotion->Load(MOTION_PATH);

		//待機モーション
		m_pMotion->Set(MOTIONTYPE_NEUTRAL);

		//待機状態
		m_bWait = true;
	}

	//成功を返す
	return S_OK;
}

//========================================
//終了
//========================================
void CPlayer::Uninit(void)
{
	if (m_pTexture != nullptr)
	{//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	if (m_pMotion != nullptr)
	{//モーション破棄
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//オブジェクト(自分自身)の破棄
	Release();
}

//========================================
//更新
//========================================
void CPlayer::Update(void)
{
	//CInputKeyboard型のポインタ
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//位置取得
	D3DXVECTOR3 pos = GetPosition();

	//向き取得
	D3DXVECTOR3 rot = GetRot();

	//プレイヤー移動
	Move(PLAYER_SPEED);

	//位置更新
	//SetPosition(D3DXVECTOR3(pos.x += m_move.x, pos.y += m_move.y, 0.0f));

	if (m_pMotion != nullptr)
	{//モーション更新
		m_pMotion->Update();
	}

	//ポインタ
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();

	//デバッグ表示
	pDebugProc->Print("\nプレイヤーの位置：%f、%f、%f\n", pos.x, pos.y, pos.z);
	pDebugProc->Print("プレイヤーの向き：%f、%f、%f\n", rot.x, rot.y, rot.z);
}

//========================================
//描画
//========================================
void CPlayer::Draw(void)
{
	//描画
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//CRenderer型のポインタ
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//位置取得
	D3DXVECTOR3 pos = GetPosition();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モーション描画
	m_pMotion->Draw();
}

//========================================
//プレイヤーの操作
//========================================
void CPlayer::Move(float fSpeed)
{
	//CInputKeyboard型のポインタ
	CInputKeyboard *pInputKeyboard = nullptr;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボードの情報取得

	//CInputPad型のポインタ
	CInputPad *pInputPad = nullptr;
	pInputPad = CManager::GetInstance()->GetInputPad();	//コントローラーの情報取得

	//CCamera型のポインタ
	CCamera *pCamera = nullptr;
	pCamera = CManager::GetInstance()->GetCamera();

	//rotの取得
	D3DXVECTOR3 rot = pCamera->GetRot();

	//視点の取得
	D3DXVECTOR3 PosV = pCamera->GetPosV();

	//注視点の取得
	D3DXVECTOR3 PosR = pCamera->GetPosR();

	//目的の向き
	D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputPad->GetLStickXPress(CInputPad::BUTTON_XSTICK, 0) < 0)
	{//Aが押された
		m_move.x += cosf(rot.y + (-D3DX_PI * 0.5f)) * fSpeed;

		//移動方向にモデルを向ける
		m_RotDest.y = -rot.y;

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true || pInputPad->GetPress(CInputPad::BUTTON_B, 0) == true)
		{
			m_move.x += cosf(rot.y + (-D3DX_PI * 0.5f)) * (fSpeed *  PLAYER_DASH_SPEED);
		}

		//注視点をずらす
		PosR - m_move;

		//移動状態にする
		m_bMove = true;
	}
	
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputPad->GetLStickXPress(CInputPad::BUTTON_XSTICK, 0) > 0)
	{//Dが押された
		m_move.x += cosf(rot.y + (D3DX_PI * 0.5f)) * fSpeed;

		if (pInputKeyboard->GetPress(DIK_LSHIFT) == true || pInputPad->GetPress(CInputPad::BUTTON_B, 0) == true)
		{
			m_move.x += cosf(rot.y + (D3DX_PI * 0.5f)) * (fSpeed *  PLAYER_DASH_SPEED);
		}

		//移動方向にモデルを向ける
		m_RotDest.y = -rot.y + D3DX_PI;

		//注視点をずらす
		PosR + m_move;

		//移動状態にする
		m_bMove = true;
	}

	if ((pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) == true) && m_bJump == false)
	{//SPACEが押下された時
		//状態をtrueにする
		m_bJump = true;

		//ジャンプの値
		m_move.y = PLAYER_JUMP;
	}

	//重力処理
	//m_move.y -= PLAYER_GRAVITY;

	//位置を更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * PLAYER_INERTIA;
	m_move.y += (0.0f - m_move.y) * PLAYER_INERTIA;

	//目的の向き
	DiffRot.y = m_RotDest.y - m_rot.y;

	//角度の正規化
	if (DiffRot.y > D3DX_PI)
	{//3.14を超えたときに反対にする
		DiffRot.y -= D3DX_PI * 2;
	}

	//-3.14を超えたときに反対にする
	if (DiffRot.y < -D3DX_PI)
	{
		DiffRot.y += D3DX_PI * 2;
	}

	//Diffに補正係数をかける
	m_rot.y += DiffRot.y * 0.1f;

	//角度の正規化
	if (m_rot.y > D3DX_PI)
	{//3.14を超えたときに反対にする
		m_rot.y -= D3DX_PI * 2;
	}

	//-3.14を超えたときに反対にする
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//========================================
//モーション管理
//========================================
void CPlayer::ManagementMotion(void)
{
	if (m_bWait == true)
	{//待機モーション
		m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		m_bMove = false;
	}

	if (m_bMove == true)
	{//歩きモーション
		m_pMotion->Set(MOTIONTYPE_WALK);
		m_bWait = false;
	}
}

//=======================================
//rotの正規化
//=======================================
float CPlayer::RotNormalize(float RotN, float Rot)
{
	//角度の正規化
	if (RotN > D3DX_PI)
	{//3.14を超えたときに反対にする
		RotN -= D3DX_PI * 2;
	}

	//-3.14を超えたときに反対にする
	if (RotN < -D3DX_PI)
	{
		RotN += D3DX_PI * 2;
	}

	//Diffに補正係数をかける
	Rot += RotN * 0.1f;

	//角度の正規化
	if (Rot > D3DX_PI)
	{//3.14を超えたときに反対にする
		Rot -= D3DX_PI * 2;
	}

	//-3.14を超えたときに反対にする
	if (Rot < -D3DX_PI)
	{
		Rot += D3DX_PI * 2;
	}

	return RotN, Rot;
}

//========================================
//3Dオブジェクトの生成
//========================================
void CPlayer::SetVertex(void)
{
}

//========================================
//3Dオブジェクトの生成
//========================================
void CPlayer::SetSize(float fWidht, float fHeight)
{
}
