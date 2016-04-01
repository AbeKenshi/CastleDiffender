#include "barricade.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Barricade::Barricade() : Entity()
{
	active = true;
	visible = true;
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
	// Boxの衝突判定用
	edge.left = -barricadeNS::WIDTH / 2.0;
	edge.right = barricadeNS::WIDTH / 2.0;
	edge.top = -barricadeNS::HEIGHT / 2.0;
	edge.bottom = barricadeNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
	health = 100;
	death = false;
	isDamaged = false;
	drawFlag = true;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Barricade::reset()
{
	active = true;
	visible = true;
	health = 100;
	// アニメーションの最初のフレーム
	startFrame = barricadeNS::START_FRAME;
	// アニメーションの最後のフレーム
	endFrame = barricadeNS::END_FRAME;
	currentFrame = startFrame;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// バリケードを描画
//==========================================================
void Barricade::draw()
{
	if (drawFlag)
		Image::draw();	// 城を描画
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

	
	if ((currentFrame == barricadeNS::START_FRAME && health < 66) || (currentFrame == barricadeNS::START_FRAME + 1 && health < 33))
	{
		currentFrame++;
		if (currentFrame < startFrame || currentFrame > endFrame)
		{
			if (loop == true)            // if looping animation
				currentFrame = startFrame;
			else                        // not looping animation
			{
				currentFrame = endFrame;
				animComplete = true;    // animation complete
			}
		}
		setRect();                      // set spriteData.rect
	}
	updateWithoutImage(frameTime);
	
}

//==========================================================
// ダメージ処理
//==========================================================
void Barricade::damage()
{
	health -= 5;
	if (health <= 0)
	{
		visible = false;
		active = false;
	}

	isDamaged = true;
}