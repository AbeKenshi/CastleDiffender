#include "midBoss.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
MidBoss::MidBoss() : Enemy()
{
	// 初期の方向は右
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
}

//==========================================================
// パラメータ初期化
//==========================================================
void MidBoss::reset()
{
	// 初期の方向は右
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	Enemy::reset();
}

//==========================================================
// 攻撃モードにチェンジするときに呼び出す関数
//==========================================================
void MidBoss::changeAttack(VECTOR2 &collisionVector)
{
	// 攻撃直前モードにチェンジ
	loop = false;
	distanceCounter = 0.0f;
	float yPerx = (float)collisionVector.y / collisionVector.x;
	float hPerw = (float)spriteData.height / spriteData.width;
	if (collisionVector.x > 0)
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::RIGHT;
			changeDirection(midBossNS::MOVE_RIGHT_START_FRAME, midBossNS::MOVE_RIGHT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::UP;
			changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::DOWN;
			changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
		}
	}
	else
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::LEFT;
			changeDirection(midBossNS::MOVE_LEFT_START_FRAME, midBossNS::MOVE_LEFT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::DOWN;
			changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::UP;
			changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
		}
	}
	goalDirection = characterNS::NONE;
	state = enemyNS::PRE_ATTACK;
	// アニメーション終了時にフレームを戻すために保存
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// 方向に応じてアニメーションを切り替え
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = midBossNS::ATTACK_LEFT_START_FRAME;
		endFrame = midBossNS::ATTACK_LEFT_END_FRAME;
		break;
	case characterNS::RIGHT:
		startFrame = midBossNS::ATTACK_RIGHT_START_FRAME;
		endFrame = midBossNS::ATTACK_RIGHT_END_FRAME;
		break;
	case characterNS::UP:
		startFrame = midBossNS::ATTACK_UP_START_FRAME;
		endFrame = midBossNS::ATTACK_UP_END_FRAME;
		break;
	case characterNS::DOWN:
		startFrame = midBossNS::ATTACK_DOWN_START_FRAME;
		endFrame = midBossNS::ATTACK_DOWN_END_FRAME;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================
void MidBoss::update(float frameTime)
{
	// 非アクティブなら何もしない
	if (!active)
		return;
	// 攻撃中のフラグをオフ
	attackCollisionFlag = false;
	// 状態ごとに処理を分岐
	switch (state)
	{
	case enemyNS::MOVE_CASTLE:		// 城への移動
	case enemyNS::MOVE_BARRICADE:	// バリケードへの移動
									// 目標への向きに応じて自分の向きを修正
									// 向きを変更する場合はアニメーションをリセット
		switch (goalDirection)
		{
		case characterNS::LEFT:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_LEFT_START_FRAME, midBossNS::MOVE_LEFT_END_FRAME);
			}
			// 移動可能だったら
			if (checkCanMove(spriteData.x - enemyNS::MOVE_SPEED * frameTime, spriteData.y)) {
				// 左に移動
				spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::RIGHT:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_RIGHT_START_FRAME, midBossNS::MOVE_RIGHT_END_FRAME);
			}
			// 移動可能だったら
			if (checkCanMove(spriteData.x + enemyNS::MOVE_SPEED * frameTime, spriteData.y)) {
				// 右に移動
				spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::UP:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
			}
			// 移動可能だったら
			if (checkCanMove(spriteData.x, spriteData.y - enemyNS::MOVE_SPEED * frameTime)) {
				// 上に移動
				spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::DOWN:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
			}
			// 移動可能だったら
			if (checkCanMove(spriteData.x, spriteData.y + enemyNS::MOVE_SPEED * frameTime)) {
				// 下に移動
				spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::NONE:
			break;
		}
		// 攻撃直後ではないはずなのでフラグをオフ
		isAttacked = false;
		// 画像のみアップデート
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK_BRAVE:
	case enemyNS::ATTACK_CASTLE:
	case enemyNS::ATTACK_BARRICADE:
		// アニメーションが終了していたら攻撃終了
		// 状態を移動時に戻す
		if (animComplete)
		{
			isAttacked = true;
			mode = imageNS::HORIZONTAL;
			direction = oldDirection;
			state = enemyNS::MOVE_CASTLE;
			loop = true;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case enemyNS::PRE_ATTACK:
		// タイマーを加算、一定時間を超えたら攻撃に移る
		attackTimer += frameTime;
		if (isAttacked && attackTimer > enemyNS::CONTINUE_ATTACK_TIME)
		{
			attackTimer = 0.0f;
			state = attackState;
			attackCollisionFlag = true;
		}
		else if (!isAttacked && attackTimer > enemyNS::ATTACK_TIME)
		{
			attackTimer = 0.0f;
			state = attackState;
			attackCollisionFlag = true;
		}
		break;
	case enemyNS::GAURD:
		break;
	default:
		break;
	}

	/*
	// 状態遷移前の処理
	switch (state)
	{
	case enemyNS::MOVE:		// 移動時
	// 目標への向きに応じて自分の向きを修正
	// 向きを変更する場合はアニメーションをリセット
	switch (goalDirection)
	{
	case enemyNS::LEFT:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_LEFT_START_FRAME, enemyNS::MOVE_LEFT_END_FRAME);
	}
	// 移動可能だったら
	if (checkCanMove(spriteData.x - enemyNS::MOVE_SPEED * frameTime, spriteData.y, map)) {
	// 左に移動
	spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::RIGHT:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_RIGHT_START_FRAME, enemyNS::MOVE_RIGHT_END_FRAME);
	}
	// 移動可能だったら
	if (checkCanMove(spriteData.x + enemyNS::MOVE_SPEED * frameTime, spriteData.y, map)) {
	// 右に移動
	spriteData.x += enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::UP:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_UP_START_FRAME, enemyNS::MOVE_UP_END_FRAME);
	}
	// 移動可能だったら
	if (checkCanMove(spriteData.x, spriteData.y - enemyNS::MOVE_SPEED * frameTime, map)) {
	// 上に移動
	spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::DOWN:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_DOWN_START_FRAME, enemyNS::MOVE_DOWN_END_FRAME);
	}
	// 移動可能だったら
	if (checkCanMove(spriteData.x, spriteData.y + enemyNS::MOVE_SPEED * frameTime, map)) {
	// 下に移動
	spriteData.y += enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::NONE:
	break;
	}
	// 攻撃直後ではないはずなのでフラグをオフ
	isAttacked = false;
	// 画像のみアップデート
	Entity::updateOnlyImage(frameTime);
	break;
	case enemyNS::ATTACK:	// 攻撃時
	// アニメーションが終了していたら攻撃終了
	// 状態を移動時に戻す
	if (animComplete)
	{
	isAttacked = true;
	mode = imageNS::HORIZONTAL;
	direction = oldDirection;
	state = enemyNS::ATTACK;
	loop = true;
	startFrame = oldStartFrame;
	endFrame = oldEndFrame;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
	Entity::updateOnlyImage(frameTime);
	}
	break;
	case enemyNS::PRE_ATTACK:
	// タイマーを加算、一定時間を超えたら攻撃に移る
	attackTimer += frameTime;
	if (isAttacked && attackTimer > enemyNS::CONTINUE_ATTACK_TIME)
	{
	attackTimer = 0.0f;
	state = enemyNS::ATTACK;
	attackCollisionFlag = true;
	}
	else if (!isAttacked && attackTimer > enemyNS::ATTACK_TIME)
	{
	attackTimer = 0.0f;
	state = enemyNS::ATTACK;
	attackCollisionFlag = true;
	}
	break;
	case enemyNS::GAURD:
	break;
	default:
	break;
	}
	*/

	// 状態遷移後の処理
	switch (state)
	{
	case enemyNS::MOVE_CASTLE:
	case enemyNS::MOVE_BARRICADE:
		updateMoving(frameTime);
		break;
	case enemyNS::ATTACK_BRAVE:
	case enemyNS::ATTACK_CASTLE:
	case enemyNS::ATTACK_BARRICADE:
		updateAttacking(frameTime);
		break;
	case enemyNS::PRE_ATTACK:
		Entity::updateWithoutImage(frameTime);
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
		damageTimer += frameTime;
		totalDamageTime += frameTime;
		if (damageTimer > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			damageTimer = 0.0f;
		}
		if (totalDamageTime > enemyNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// 移動可能だったら
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y))
	{
		spriteData.x += frameTime * velocity.x;     // キャラをX方向に動かす
		spriteData.y += frameTime * velocity.y;     // キャラをY方向に動かす
	}
	// 画面の端まで来たら進めない
	if (spriteData.x > GAME_WIDTH - enemyNS::WIDTH * getScale())	// 画面右端を超えたら
		spriteData.x = GAME_WIDTH - enemyNS::WIDTH * getScale();	// 画面右端に移動
	if (spriteData.x < 0)											// 画面左端を超えたら
		spriteData.x = 0;											// 画面左端に移動
	if (spriteData.y < rectNS::HEIGHT - 10)								// 画面上端を超えたら
		spriteData.y = rectNS::HEIGHT - 10;								// 画面上端に移動
	if (spriteData.y > GAME_HEIGHT - enemyNS::HEIGHT * getScale())  // 画面下端を超えたら
		spriteData.y = GAME_HEIGHT - enemyNS::HEIGHT * getScale();	// 画面下端に移動

}

//==========================================================
// ダメージ
//==========================================================
void MidBoss::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		health -= braveNS::FIRE_DAMAGE / 3;
		break;
	case BRAVE_ATTACK:
		health -= braveNS::ATTACK_DAMAGE / 3;
		break;
	case BRAVE_SECOND_ATTACK:
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	if (health <= 0)
		dead();
	isDamaged = true;
}