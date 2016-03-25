#include "braveIcon.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
BraveIcon::BraveIcon() : Image()
{
	spriteData.width = braveIconNS::WIDTH;			// 勇者のアイコンのサイズ
	spriteData.height = braveIconNS::HEIGHT;
	spriteData.x = braveIconNS::X;					// 画面上の位置
	spriteData.y = braveIconNS::Y;
	spriteData.rect.bottom = braveIconNS::HEIGHT;		// 画面の一部を選択
	spriteData.rect.right = braveIconNS::WIDTH;
	startFrame = braveIconNS::START_FRAME;
	endFrame = braveIconNS::END_FRAME;
	currentFrame = startFrame;
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================	
void BraveIcon::update(float frameTime)
{
	if (currentFrame == 0 && brave->getHealth() < 75)
		Image::update(frameTime);
	if (currentFrame == 1 && brave->getHealth() < 50)
		Image::update(frameTime);
	if (currentFrame == 2 && brave->getHealth() < 25)
		Image::update(frameTime);
}

