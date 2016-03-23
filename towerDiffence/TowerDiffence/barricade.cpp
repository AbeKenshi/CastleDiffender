#include "barricade.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Barricade::Barricade() : Entity()
{
	active = true;
	spriteData.width = barricadeNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = barricadeNS::HEIGHT;
	spriteData.rect.bottom = barricadeNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = barricadeNS::WIDTH;
	cols = barricadeNS::TEXTURE_COLS;
	// アニメーションの最初のフレーム
	startFrame = barricadeNS::START_FRAME;
	// アニメーションの最後のフレーム
	endFrame = barricadeNS::END_FRAME;
	currentFrame = startFrame;
	radius = barricadeNS::COLLISION_RADIUS;			// 円の衝突判定用
	visible = true;
	collisionType = entityNS::CIRCLE;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void Barricade::update(float frameTime)
{
	if (visible == false)
		return;

//	updateWithoutImage(frameTime);
	Image::update(frameTime);
}