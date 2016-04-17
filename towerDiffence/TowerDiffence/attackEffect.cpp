#include "attackEffect.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
AttackEffect::AttackEffect() : Image()
{
	visible = false;							// 非表示がデフォルト
	spriteData.width = attackEffectNS::WIDTH;	// １つの画像のサイズ
	spriteData.height = attackEffectNS::HEIGHT;
	spriteData.rect.bottom = attackEffectNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = attackEffectNS::WIDTH;
	cols = attackEffectNS::TEXTURE_COLS;
	frameDelay = attackEffectNS::ANIMATION_DELAY;
	// アニメーションの最初のフレーム
	startFrame = attackEffectNS::START_FRAME;
	// アニメーションの最後のフレーム
	endFrame = attackEffectNS::END_FRAME;
	currentFrame = startFrame;
	spriteData.scale = 0.8f;
	loop = false;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void AttackEffect::update(float frameTime)
{
	if (visible == false)
		return;
	Image::update(frameTime);
	if (animComplete)
		visible = false;
}

//==========================================================
// Attack
// この関数が呼ばれると攻撃の衝撃波のアニメーションが発動
//==========================================================
void AttackEffect::attack(Brave &brave)
{
	switch (brave.getDirection())
	{
	case characterNS::RIGHT:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10;
		setDegrees(0);
		flipHorizontal(false);
		break;
	case characterNS::LEFT:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10;
		setDegrees(0);
		flipHorizontal(true);
		break;
	case characterNS::UP:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10 - 10;
		setDegrees(40.0f);
		flipHorizontal(true);
		break;
	case characterNS::DOWN:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10 + 10;
		setDegrees(230.0f);
		flipHorizontal(true);
		break;
	}
	visible = true;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
}