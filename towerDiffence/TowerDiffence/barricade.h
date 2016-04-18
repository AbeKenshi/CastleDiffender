//==========================================================
/// @file
/// @brief    Barricadeクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#ifndef _BARRICADE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _BARRICADE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "hitEffect.h"

// Barricadeクラスの定数
// ゲーム内でのステータス以外をここに記述
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
	float totalTimeCounter;			// ダメージアニメーション用のタイマー
	HitEffect hitEffect;			// 攻撃がヒットしたときのアニメーション画像
public:
	// コンストラクタ
	Barricade();

	//==========================================================
	// 継承されたメンバ関数
	//==========================================================
	// Update
	// 通常、フレームごとに1回呼び出す
	// frameTimeは、移動とアニメーションの速さを制御するために使用
	void update(float frameTime);
	// ダメージ処理
	// WEAPONの種類によって受けるダメージが分岐
	void damage(WEAPON);

	//==========================================================
	// 新しく追加するメンバー関数
	//==========================================================

	//==========================================================
	// setter
	//==========================================================
	// ダメージを受けるときの倍率をセット
	void setDamagerPer(float per) { damagePer = per; }
	
	//==========================================================
	// getter
	//==========================================================
	// 攻撃がヒットしたときのアニメーション画像を戻す
	HitEffect& getHitEffect() { return hitEffect; }

};
#endif // !_BARRICADE_H
