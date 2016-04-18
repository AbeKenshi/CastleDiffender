//==========================================================
/// @file
/// @brief    AttackEffectクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#ifndef _ATTACK_EFFECT_H	// このファイルが複数の箇所でインクルードされる場合、
#define _ATTACK_EFFECT_H	// 多重に定義されることを防ぎます。

#include "brave.h"

namespace attackEffectNS
{
	const int WIDTH = 96;					// 画像の幅（各フレーム）
	const int HEIGHT = 96;					// 画像の高さ
	const int TEXTURE_COLS = 5;				// テクスチャは5列
	const int START_FRAME = 0;				// アニメーションはフレーム0から開始
	const int END_FRAME = 3;				// アニメーションフレームは0、1、2、3
	const float ANIMATION_DELAY = 0.05f;	// アニメーションのフレーム間の時間
	const float SCALE = 0.8f;				// スプライトのスケール
}

class AttackEffect : public Image
{
public:
	// コンストラクタ
	AttackEffect();


	//==========================================================
	// 継承されたメンバ関数
	//==========================================================
	// Update
	// 通常、フレームごとに1回呼び出す
	// frameTimeは、移動とアニメーションの速さを制御するために使用
	void update(float frameTime);

	//==========================================================
	// 新しく追加するメンバー関数
	//==========================================================
	// Attack
	// この関数が呼ばれると攻撃の衝撃波のアニメーションが発動
	void attack(Brave &brave);
};
#endif // !_ATTACK_EFFECT_H
