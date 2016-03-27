#include "fire.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Fire::Fire() : Entity()
{
	active = false;								// 炎はアクティブでない状態から開始
	spriteData.width = fireNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = fireNS::HEIGHT;
	spriteData.rect.bottom = fireNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = fireNS::WIDTH;
	cols = fireNS::TEXTURE_COLS;
	frameDelay = fireNS::ANIMATION_DELAY;
	// ファイアーアニメーションの最初のフレーム
	startFrame = fireNS::START_FRAME;
	// ファイアーアニメーションの最後のフレーム
	endFrame = fireNS::END_FRAME;
	currentFrame = startFrame;
	radius = fireNS::COLLISION_RADIUS;			// 円の衝突判定用
	visible = false;
	fireTimer = 0.0f;
	collisionType = entityNS::CIRCLE;
	mode = imageNS::VERTICAL;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Fire::reset()
{
	active = false;								// 炎はアクティブでない状態から開始
	frameDelay = fireNS::ANIMATION_DELAY;
	// ファイアーアニメーションの最初のフレーム
	startFrame = fireNS::START_FRAME;
	// ファイアーアニメーションの最後のフレーム
	endFrame = fireNS::END_FRAME;
	currentFrame = startFrame;
	radius = fireNS::COLLISION_RADIUS;			// 円の衝突判定用
	visible = false;
	fireTimer = 0.0f;
	collisionType = entityNS::CIRCLE;
	mode = imageNS::VERTICAL;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void Fire::update(float frameTime)
{
	fireTimer -= frameTime;						// 発射が可能になるまでの残り時間
	
	if (visible == false)
		return;

	if (fireTimer < 0)							// 発射可能な場合
	{
		visible = false;						// 古い炎を無効化
		active = false;
	}

	Image::update(frameTime);

	spriteData.x += frameTime * velocity.x;		// X方向に移動
	spriteData.y += frameTime * velocity.y;		// Y方向に移動
	// 画面の端まで来たら消去
	if (spriteData.x > GAME_WIDTH || spriteData.x < 0 || spriteData.y < 0 || spriteData.y > GAME_HEIGHT)
	{
		visible = false;
		active = false;
	}
}

//==========================================================
// Fire
// Braveからミサイルを発射
//==========================================================
void Fire::fire(Brave *brave)
{
	if (fireTimer <= 0.0f && brave->getMP() > fireNS::FIRE_MP)	// 発射可能な場合
	{
		switch (brave->getDirection())
		{
		case braveNS::UP:
			velocity.x = 0.0f;
			velocity.y = -fireNS::SPEED;
			spriteData.angle = PI / 2;
			break;
		case braveNS::RIGHT:
			velocity.x = fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = -PI;
			break;
		case braveNS::DOWN:
			velocity.x = 0.0f;
			velocity.y = fireNS::SPEED;
			spriteData.angle = -PI / 2;
			break;
		case braveNS::LEFT:
			velocity.x = -fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = 0.0f;
			break;
		}
		spriteData.x = brave->getCenterX() - spriteData.width / 2;
		spriteData.y = brave->getCenterY() - spriteData.height / 2;
		visible = true;									// 炎を表示
		active = true;									// 衝突可能にする
		fireTimer = fireNS::FIRE_DELAY;					// 発射の間隔
		brave->setMP(brave->getMP() - fireNS::FIRE_MP);	// MPを減少
	}
}