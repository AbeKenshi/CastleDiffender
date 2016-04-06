#ifndef _HIT_EFFECT_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _HIT_EFFECT_H	// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"

namespace hitEffectNS
{
	const int WIDTH = 108;				// 画像の幅（各フレーム）
	const int HEIGHT = 108;				// 画像の高さ
	const int TEXTURE_COLS = 3;			// テクスチャは3列
	const int START_FRAME = 0;			// アニメーションはフレーム0から開始
	const int END_FRAME = 2;			// アニメーションフレームは0、1、2
	const float ANIMATION_DELAY = 0.1;	// アニメーションのフレーム間の時間
}

class HitEffect : public Image
{
public:
	// コンストラクタ
	HitEffect();

	// Update
	void update(float frameTime);

	// Hit
	void hit(float x, float y);
};
#endif // !_ATTACK_EFFECT_H
