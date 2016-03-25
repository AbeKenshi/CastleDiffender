#include "castle.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Castle::Castle() : Entity()
{
	active = true;
	visible = true;
	spriteData.width = castleNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = castleNS::HEIGHT;
	spriteData.rect.bottom = castleNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = castleNS::WIDTH;
	spriteData.x = castleNS::X;
	spriteData.y = castleNS::Y;
	cols = 0;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	radius = castleNS::COLLISION_RADIUS;		// 円の衝突判定用
	collisionType = entityNS::CIRCLE;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションを制御するために使用
//==========================================================
void Castle::update(float frameTime)
{
	if (visible == false)
		return;

	Image::update(frameTime);
}