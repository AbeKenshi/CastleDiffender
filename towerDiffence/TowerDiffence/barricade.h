#ifndef _BARRICADE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _BARRICADE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "hitEffect.h"

namespace barricadeNS
{
	const int WIDTH = 32;			// 画像の幅（各フレーム）
	const int HEIGHT = 32;			// 画像の高さ
	const int TEXTURE_COLS = 8;		// テクスチャは8列
	const int START_FRAME = 0;		// アニメーションはフレーム0から開始
	const int END_FRAME = 2;		// アニメーションフレームは0、1、2
}

class Barricade : public Entity		// Entityクラスを継承
{
private:
	float timeCounter;				// ダメージアニメーション用のタイマー
	float totalTimeCounter;
	HitEffect hitEffect;			// 攻撃がヒットしたときのアニメーション画像
public:
	// コンストラクタ
	Barricade();

	// 継承されたメンバー関数
	virtual void draw();
	void update(float frameTime);
	void damage();

	//==========================================================
	// setter
	//==========================================================
	void setDamagerPer(float per) { damagePer = per; }
	
	//==========================================================
	// getter
	//==========================================================
	HitEffect& getHitEffect() { return hitEffect; }

};
#endif // !_BARRICADE_H
