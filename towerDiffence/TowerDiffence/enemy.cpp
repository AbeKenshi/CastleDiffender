#include "enemy.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Enemy::Enemy() : Entity()
{
	spriteData.width = enemyNS::WIDTH;			// 雑魚敵のサイズ
	spriteData.height = enemyNS::HEIGHT;
	spriteData.x = enemyNS::X;					// 画面上の位置
	spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	currentFrame = startFrame;
	radius = enemyNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	state = enemyNS::MOVE;
	direction = enemyNS::RIGHT;
	isDamaged = false;
	timeCounter = 0.0f;
	totalTimeCounter = 0.0f;
	drawFlag = true;
	distanceCounter = 0.0f;
}

//==========================================================
// 雑魚敵を初期化
// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
//==========================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	setRect();
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// 雑魚敵を描画
//==========================================================
void Enemy::draw()
{
	if (drawFlag)
		Image::draw();	// 雑魚敵を描画
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================
void Enemy::update(float frameTime)
{
	// 状態遷移前の処理
	switch (state)
	{
	case enemyNS::MOVE:
		switch (goalDirection)
		{
		case enemyNS::LEFT:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_LEFT_START_FRAME;
				endFrame = enemyNS::MOVE_LEFT_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::RIGHT:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
				endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::UP:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_UP_START_FRAME;
				endFrame = enemyNS::MOVE_UP_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::DOWN:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_DOWN_START_FRAME;
				endFrame = enemyNS::MOVE_DOWN_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::NONE:
			break;
		}
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK:
		if (collisionVector.x > 0 && collisionVector.y < 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
			endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x > 0 && collisionVector.y > 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
			endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x < 0 && collisionVector.y < 0)
		{
			direction = enemyNS::LEFT;
			startFrame = enemyNS::MOVE_LEFT_START_FRAME;
			endFrame = enemyNS::MOVE_LEFT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x < 0 && collisionVector.y > 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_LEFT_START_FRAME;
			endFrame = enemyNS::MOVE_LEFT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		break;
	case enemyNS::GAURD:
		break;
	default:
		break;
	}
	// 状態遷移後の処理
	switch (state)
	{
	case enemyNS::MOVE:
		updateMoving(frameTime);
		break;
	case enemyNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case enemyNS::GAURD:
		Entity::update(frameTime);
		break;
	default:
		Entity::update(frameTime);
		break;
	}

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
		if (totalTimeCounter > enemyNS::DAMAGE_TIME)
		{
			timeCounter = 0.0f;
			totalTimeCounter = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}

	spriteData.x += frameTime * velocity.x;     // キャラをX方向に動かす
	spriteData.y += frameTime * velocity.y;     // キャラをY方向に動かす
}

//==========================================================
// 移動時のアップデート関数
//==========================================================
void Enemy::updateMoving(float frameTime)
{
	// アニメーションのアップデートは単独で行われるのでそれ以外をアップデート
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// 攻撃時のアップデート関数
//==========================================================
void Enemy::updateAttacking(float frameTime)
{

	Entity::update(frameTime);
}

//==========================================================
// ダメージ
//==========================================================
void Enemy::damage(WEAPON weapon)
{
	isDamaged = true;
}

//==========================================================
// 人工知能
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
	if (nearPlayer)
	{
		distanceCounter = 0.0f;
		goalDirection = enemyNS::NONE;
		state = enemyNS::ATTACK;
		return;
	}
	// プレイヤの現在位置を取得
	int playerX = ent.getX();
	int playerY = ent.getY();
	int subX = playerX - getX();
	int subY = playerY - getY();
	
	// 同じ方向に32ピクセル移動するごとに方向を決めなおす
	if (distanceCounter <=  0)
	{
		distanceCounter = 32.0f;
		state = enemyNS::MOVE;
		if (abs(subX) > abs(subY))
		{
			if (subX > 0)
				goalDirection = enemyNS::RIGHT;
			else
				goalDirection = enemyNS::LEFT;
			return;
		}
		else
		{
			if (subY > 0)
				goalDirection = enemyNS::DOWN;
			else
				goalDirection = enemyNS::UP;
			return;
		}
	}
}