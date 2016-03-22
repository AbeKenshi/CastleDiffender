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
	state = enemyNS::MOVE;
	direction = enemyNS::RIGHT;
	isDamaged = false;
	timeCounter = 0.0f;
	totalTimeCounter = 0.0f;
	drawFlag = true;
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
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK:
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