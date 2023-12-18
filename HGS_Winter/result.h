//========================================
//
//シューティングアクション[result.h]
//Author：森川駿弥
//
//========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//========================================
//ゲームクラス
//========================================
class CResult : public CScene
{
public:
	CResult();	//コンストラクタ
	~CResult();	//デストラクタ

				//メンバ関数
	static CResult *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCnt;
	int m_Counter;
	CObject2D *m_pObj2D;
};

#endif
