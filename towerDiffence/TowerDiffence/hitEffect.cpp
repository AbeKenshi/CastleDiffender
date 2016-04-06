#include "hitEffect.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
HitEffect::HitEffect() : Image()
{
	visible = false;							// 非表示がデフォルト
	spriteData.width = hitEffectNS::WIDTH;	// １つの画像のサイズ
	spriteData.height = hitEffectNS::HEIGHT;
	spriteData.rect.bottom = hitEffectNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = hitEffectNS::WIDTH;
	cols = hitEffectNS::TEXTURE_COLS;
	frameDelay = hitEffectNS::ANIMATION_DELAY;
	// アニメーションの最初のフレーム
	startFrame = hitEffectNS::START_FRAME;
	// アニメーションの最後のフレーム
	endFrame = hitEffectNS::END_FRAME;
	currentFrame = startFrame;
	setScale(0.5);
	loop = false;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void HitEffect::update(float frameTime)
{
	if (visible == false)
		return;
	Image::update(frameTime);
	if (animComplete)
		visible = false;
}

//==========================================================
// Hit
// この関数が呼ばれると攻撃がヒットしたときのエフェクトが発動
//==========================================================
void HitEffect::hit(float x, float y)
{
	spriteData.x = x - spriteData.width * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	spriteData.y = y - spriteData.height * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	visible = true;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
}