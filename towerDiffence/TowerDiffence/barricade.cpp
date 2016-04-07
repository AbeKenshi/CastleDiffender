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
}

//==========================================================
// バリケードを描画
//==========================================================
void Barricade::draw()
{
	Image::draw();	// 城を描画
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void Barricade::update(float frameTime)
{
	if (active == false)
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
	hitEffect.update(frameTime);
	updateWithoutImage(frameTime);
	
}

//==========================================================
// ダメージ処理
//==========================================================
void Barricade::damage()
{
	if (!active)
		return;
	hitEffect.hit(getCenterX(), getCenterY());
	health -= 10 * damagePer;

	if (health <= 0)
	{
		visible = false;
		active = false;
		hitEffect.setVisible(false);
	}

	isDamaged = true;
}