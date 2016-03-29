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
	cols = castleNS::TEXTURE_COLS;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	// Boxの衝突判定用
	edge.left = -castleNS::WIDTH / 1.8;
	edge.right = castleNS::WIDTH / 1.8;
	edge.top = -castleNS::HEIGHT / 1.8;
	edge.bottom = castleNS::HEIGHT / 1.8;
	collisionType = entityNS::BOX;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Castle::reset()
{
	active = true;
	visible = true;
	health = 100;
	spriteData.x = castleNS::X;
	spriteData.y = castleNS::Y;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// 城を描画
//==========================================================
void Castle::draw()
{
	if (drawFlag)
		Image::draw();	// 城を描画
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

	// ダメージを受けているなら一定時間ごとにアニメーションを点滅
	if (isDamaged)
	{
		timeCounter += frameTime;
		totalTimeCounter += frameTime;
		if (timeCounter > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			timeCounter = 0.0f;
		}
		if (totalTimeCounter > braveNS::DAMAGE_TIME)
		{
			timeCounter = 0.0f;
			totalTimeCounter = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}

	Entity::update(frameTime);
}

//==========================================================
// ダメージ
//==========================================================
void Castle::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		break;
	case BRAVE_ATTACK:
		break;
	case BRAVE_SECOND_ATTACK:
		break;
	case ENEMY_ATTACK:
		health -= enemyNS::ATTACK_DAMAGE;
		break;
	default:
		break;
	}
	if (health <= 0)
		death = true;
	isDamaged = true;
}