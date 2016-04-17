#ifndef _ATTACK_EFFECT_H	// このファイルが複数の箇所でインクルードされる場合、
#define _ATTACK_EFFECT_H	// 多重に定義されることを防ぎます。

#include "brave.h"

namespace attackEffectNS
{
	const int WIDTH = 96;	// 画像の幅（各フレーム）
	const int HEIGHT = 96;	// 画像の高さ
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 0;
	const int END_FRAME = 3;
	const float ANIMATION_DELAY = 0.05f;	// アニメーションのフレーム間の時間
}

class AttackEffect : public Image
{
public:
	// コンストラクタ
	AttackEffect();

	// Update
	void update(float frameTime);

	// Attack
	void attack(Brave &brave);
};
#endif // !_ATTACK_EFFECT_H
