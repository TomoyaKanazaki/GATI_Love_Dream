//========================================
//
//シューティングアクション[title.h]
//Author：森川駿弥
//
//========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "manager.h"
#include "object2D.h"

//========================================
//チュートリアルクラス
//========================================
class CTutorial : public CScene
{
public:
	CTutorial();	//コンストラクタ
	~CTutorial();	//デストラクタ

	//メンバ関数
	static CTutorial *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_Counter;
	CObject2D *m_pObj2D;
};

#endif
