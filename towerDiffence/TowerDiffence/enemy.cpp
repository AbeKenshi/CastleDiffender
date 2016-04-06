#include "enemy.h"
#include <iostream>
//==========================================================
// デフォルトコンストラクタ
//==========================================================
Enemy::Enemy() : Character()
{
	spriteData.width = enemyNS::WIDTH;			// 雑魚敵のサイズ
	spriteData.height = enemyNS::HEIGHT;
	spriteData.rect.bottom = enemyNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	// 初期の方向は右
	goalDirection = characterNS::RIGHT;
	oldDirection = direction;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	// Boxの衝突判定用
	edge.left = -enemyNS::WIDTH * spriteData.scale / 2.0;
	edge.right = enemyNS::WIDTH * spriteData.scale / 2.0;
	edge.top = -enemyNS::HEIGHT * spriteData.scale / 2.0;
	edge.bottom = enemyNS::HEIGHT * spriteData.scale / 2.0;
	// 初期の状態は城に向かって移動
	stateDeteil = enemyNS::MOVE_CASTLE;
	// 範囲内にはいない状態からスタート
	inCertainRange = false;
	canMakeDecesionMove = false;
	attackAnimationMode = imageNS::VERTICAL;
	moveUpStartFrame = enemyNS::MOVE_UP_START_FRAME;
	moveUpEndFrame = enemyNS::MOVE_UP_END_FRAME;
	moveRightStartFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	moveRightEndFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	moveDownStartFrame = enemyNS::MOVE_DOWN_START_FRAME;
	moveDownEndFrame = enemyNS::MOVE_DOWN_END_FRAME;
	moveLeftStartFrame = enemyNS::MOVE_LEFT_START_FRAME;
	moveLeftEndFrame = enemyNS::MOVE_LEFT_END_FRAME;
	moveAnimationDelay = enemyNS::MOVE_ANIMATION_DELAY;
	attackUpStartFrame = enemyNS::ATTACK_UP_START_FRAME;
	attackUpEndFrame = enemyNS::ATTACK_UP_END_FRAME;
	attackRightStartFrame = enemyNS::ATTACK_RIGHT_START_FRAME;
	attackRightEndFrame = enemyNS::ATTACK_RIGHT_END_FRAME;
	attackDownStartFrame = enemyNS::ATTACK_DOWN_START_FRAME;
	attackDownEndFrame = enemyNS::ATTACK_DOWN_END_FRAME;
	attackLeftStartFrame = enemyNS::ATTACK_LEFT_START_FRAME;
	attackLeftEndFrame = enemyNS::ATTACK_LEFT_END_FRAME;
	attackTime = enemyNS::ATTACK_TIME;
	continueAttackTime = enemyNS::CONTINUE_ATTACK_TIME;
	attackDamage = enemyNS::ATTACK_DAMAGE;
	// ダメージを受ける時に掛ける割合は1.0
	damagePer = 1.0f;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Enemy::reset()
{
	Character::reset();
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	// 初期の方向は右
	oldDirection = direction;
	goalDirection = characterNS::RIGHT;
	startFrame = moveRightStartFrame;
	endFrame = moveRightEndFrame;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	// 初期の状態は移動
	stateDeteil = enemyNS::MOVE_CASTLE;
	// 範囲内にはいない状態からスタート
	inCertainRange = false;
	canMakeDecesionMove = false;
	// ダメージを受ける時に掛ける割合は1.0
	damagePer = 1.0f;
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================
void Enemy::update(float frameTime)
{
	// 非アクティブなら何もしない
	if (!active)
		return;
	
	if (attackCollisionFlag) {
		attackCollision.attack(getCenterX(), getCenterY(), getWidth(), getHeight(), direction);
	}
	// 攻撃中の当たり判定を出すフラグをオフ
	attackCollisionFlag = false;
	canMakeDecesionMove = false;

	// 各状態に応じて処理を分岐
	switch (state)
	{
	case characterNS::MOVE:	// 移動中なら目標の方向にまっすぐ進む
		// 目標の方向に向かって進む
		switch (goalDirection)
		{
		case characterNS::LEFT:
			if (direction != goalDirection)
				changeDirection(moveLeftStartFrame, moveLeftEndFrame);
			// 左に移動
			spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::RIGHT:
			if (direction != goalDirection)
				changeDirection(moveRightStartFrame, moveRightEndFrame);
			// 右に移動
			spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::UP:
			if (direction != goalDirection)
				changeDirection(moveUpStartFrame, moveUpEndFrame);
			// 上に移動
			spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::DOWN:
			if (direction != goalDirection)
				changeDirection(moveDownStartFrame, moveDownEndFrame);
			// 左に移動
			spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			break;
		}
		// 攻撃直後ではないはずなのでフラグをオフ
		isAttacked = false;
		// 画像のみアップデート
		Entity::updateOnlyImage(frameTime);
		if (isCenterOfTile())	// タイルの中央に来たらマップを更新
		{
			// マップに自分の位置を追加
			map->updateMapCol(tileY * mapNS::TEXTURE_SIZE, tileX * mapNS::TEXTURE_SIZE, map->getMapCol(tileY, tileX) + 3);
			canMakeDecesionMove = true;
		}
		break;
	case characterNS::ATTACK:
		// アニメーションが終了していたら攻撃終了
		// 状態を移動時に戻す
		if (animComplete)
		{
			canMakeDecesionMove = true;
			isAttacked = true;
			mode = imageNS::HORIZONTAL;
			direction = oldDirection;
			stateDeteil = enemyNS::MOVE_CASTLE;
			state = characterNS::MOVE;
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
	case characterNS::PRE_ATTACK:
		// タイマーを加算、一定時間を超えたら攻撃に移る
		attackTimer += frameTime;
		if (isAttacked && attackTimer > continueAttackTime)
		{
			attackTimer = 0.0f;
			stateDeteil = attackState;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		else if (!isAttacked && attackTimer > attackTime)
		{
			attackTimer = 0.0f;
			stateDeteil = attackState;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		break;
	case characterNS::WAIT:
		canMakeDecesionMove = true;
		break;
	case characterNS::DEATH:
		drawFlag = true;
		isDamaged = false;
		velocity.y += frameTime * 2000.0f;
	default:
		break;
	}

	// Entityのアップデートに関する処理
	switch (state)
	{
	case characterNS::MOVE:
		updateMoving(frameTime);
		break;
	case characterNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case characterNS::PRE_ATTACK:
		Entity::updateWithoutImage(frameTime);
		break;
	case characterNS::WAIT:
		Entity::updateWithoutImage(frameTime);
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
	if (state != characterNS::DEATH)
	{/*
		// 画面の端まで来たら進めない
		if (spriteData.x > GAME_WIDTH - enemyNS::WIDTH * getScale())	// 画面右端を超えたら
			spriteData.x = GAME_WIDTH - enemyNS::WIDTH * getScale();	// 画面右端に移動
		if (spriteData.x < 0)											// 画面左端を超えたら
			spriteData.x = 0;											// 画面左端に移動
		if (spriteData.y < rectNS::HEIGHT - 10)								// 画面上端を超えたら
			spriteData.y = rectNS::HEIGHT - 10;								// 画面上端に移動
		if (spriteData.y > GAME_HEIGHT - enemyNS::HEIGHT * getScale())  // 画面下端を超えたら
			spriteData.y = GAME_HEIGHT - enemyNS::HEIGHT * getScale();	// 画面下端に移動
			*/
	}
	else
	{
		spriteData.x += frameTime * velocity.x;
		spriteData.y += frameTime * velocity.y;
		if (spriteData.y > GAME_HEIGHT)
			dead();
	}
	attackCollision.update(frameTime);
}

//==========================================================
// ダメージ
//==========================================================
void Enemy::damage(WEAPON weapon)
{
	if (type == enemyNS::NORMAL)
		setDamagerPer(1.0f);
	else if (type == enemyNS::RED)
		setDamagerPer(0.8f);
	else if (type == enemyNS::BLUE)
		setDamagerPer(0.9f);

	switch (weapon)
	{
	case FIRE:
		health -= braveNS::FIRE_DAMAGE * damagePer;
		break;
	case BRAVE_ATTACK:
		health -= braveNS::ATTACK_DAMAGE * damagePer;
		break;
	case BRAVE_SECOND_ATTACK:
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	if (health <= 0)
	{
		state = characterNS::DEATH;
		if (rand() % 2 == 0)
			velocity.x = 32.0f * 2.0;
		else
			velocity.x = -32.0f * 2.0;
		velocity.y = -sqrt(2 * 2000.0f * 96 * 2);
		map->updateMapCol(tileY * 32, tileX * 32, map->getMapCol(tileY, tileX) - 3);
	}
	isDamaged = true;
}

//==========================================================
// 人工知能
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
	// 攻撃中ならば行動選択は行わない
	if (state == characterNS::ATTACK)
	{
		return;
	}
}

//==========================================================
// 
//==========================================================
void Enemy::changeDirection(int strF, int endF)
{
	direction = goalDirection;
	startFrame = strF;
	endFrame = endF;
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
}

//==========================================================
// プレイヤーとの距離が一定範囲内ならtrue、それ以外はfalseを返す
//==========================================================
bool Enemy::checkDistancePlayer(int px, int py)
{
	int subX = px - getX();
	int subY = py - getY();

	int dist = (int)sqrt(subX * subX + subY * subY);

	if (dist < 100) return true;
	else return false;
}

//==========================================================
// 一番近くのバリケードの位置を返す関数
// バリケードが存在しない場合はプレイヤーの位置を返す
//==========================================================
VECTOR2 Enemy::searchNearBarricade(Entity &ent)
{

	// 最小の距離差
	int minX = 0, minY = 0;
	// 最小のバリケードの座標
	int minBariPosiX = 0, minBariPosiY = 0;
	// アクティブなバリケードの数を数える用
	int count = 0;

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		// もしバリケードnがアクティブなら
		if (barricades[i].getActive())
		{
			// 探索1つ目の場合
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getX() - getX());
				minY = (int)abs(barricades[i].getY() - getY());
				minBariPosiX = (int)barricades[i].getX();
				minBariPosiY = (int)barricades[i].getY();
			}
			else // 2つ目以降
			{
				// もし最小値を更新したら
				if ((barricades[i].getX() - getX())*(barricades[i].getX() - getX()) +
					(barricades[i].getY() - getY())*(barricades[i].getY() - getY()) <
					minX * minX + minY * minY)
				{
					// 新たに代入
					minX = (int)abs(barricades[i].getX() - getX());
					minY = (int)abs(barricades[i].getY() - getY());
					minBariPosiX = (int)barricades[i].getX();
					minBariPosiY = (int)barricades[i].getY();
				}
			}
			// カウントを増やす
			count++;
		}
	}

	// ベクター2クラス生成
	VECTOR2 vec;

	// もしバリケードが1つ以上存在したら
	if (count > 0) {
		// 最小値を代入
		vec.x = minBariPosiX;
		vec.y = minBariPosiY;
	}
	else {
		// プレイヤーの位置を代入
		vec.x = ent.getX();
		vec.y = ent.getY();
	}

	// ベクトル返す
	return vec;
}

//==========================================================
// 一番近くのバリケードのインデックスを返す関数
//==========================================================
int Enemy::searchNearBarricadeIndex()
{
	// 最小の距離差
	int minX = 0, minY = 0;
	// 最小の距離のインデックス
	int minIndex = 0;
	// アクティブなバリケードの数を数える用
	int count = 0;

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		// もしバリケードnがアクティブなら
		if (barricades[i].getActive())
		{
			// 探索1つ目の場合
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getX() - getX());
				minY = (int)abs(barricades[i].getY() - getY());
				minIndex = i;
			}
			else // 2つ目以降
			{
				if ((barricades[i].getX() - getX())*(barricades[i].getX() - getX()) +
					(barricades[i].getY() - getY())*(barricades[i].getY() - getY()) <
					minX * minX + minY * minY)
				{
					// 新たに代入
					minX = (int)abs(barricades[i].getX() - getX());
					minY = (int)abs(barricades[i].getY() - getY());
					minIndex = i;
				}
			}
			// カウントを増やす
			count++;
		}
	}
	nearBarricadeIndex =  minIndex;
	return minIndex;
}

//==========================================================
// 雑魚敵から城までの直線上にバリケードが存在したらtrue、存在しない場合はfalseを返す。
//==========================================================
bool Enemy::checkBarricadeOnLine() {
	for (int x = tileX; x <= mapNS::MAP_WIDTH; ++x)
	{
		if (map->getMapObj(tileY, x) == 0 || map->getMapCol(tileY, x) == 1)
			break;
		if (map->getMapCol(tileY, x) == 2)
		{
			goalDirection = characterNS::RIGHT;
			return false;
		}
	}
	for (int x = tileX; x >= 0; --x)
	{
		if (map->getMapObj(tileY, x) == 0 || map->getMapCol(tileY, x) == 1)
			break;
		if (map->getMapCol(tileY, x) == 2)
		{
			goalDirection = characterNS::LEFT;
			return false;
		}
	}
	for (int y = tileY; y <= mapNS::MAP_HEIGHT; ++y)
	{
		if (map->getMapObj(y, tileX) == 0 || map->getMapCol(y, tileX) == 1)
			break;
		if (map->getMapCol(y, tileX) == 2)
		{
			goalDirection = characterNS::DOWN;
			return false;
		}
	}
	for (int y = tileY; y >= 0; --y)
	{
		if (map->getMapObj(y, tileX) == 0 || map->getMapCol(y, tileX) == 1)
			break;
		if (map->getMapCol(y, tileX) == 2)
		{
			goalDirection = characterNS::UP;
			return false;
		}
	}
	return true;
}

//==========================================================
// 攻撃モードにチェンジするときに呼び出す関数
//==========================================================
void Enemy::changeAttack(VECTOR2 &collisionVector)
{
	// 攻撃直前モードにチェンジ
	loop = false;
	float yPerx = (float)collisionVector.y / collisionVector.x;
	float hPerw = (float)spriteData.height / spriteData.width;
	if (collisionVector.x > 0)
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::RIGHT;
			changeDirection(moveRightStartFrame, moveRightEndFrame);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::UP;
			changeDirection(moveUpStartFrame, moveUpEndFrame);
		}
		else
		{
			goalDirection = characterNS::DOWN;
			changeDirection(moveDownStartFrame, moveDownEndFrame);
		}
	}
	else
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::LEFT;
			changeDirection(moveLeftStartFrame, moveLeftEndFrame);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::DOWN;
			changeDirection(moveDownStartFrame, moveDownEndFrame);
		}
		else
		{
			goalDirection = characterNS::UP;
			changeDirection(moveUpStartFrame, moveUpEndFrame);
		}
	}
	goalDirection = characterNS::NONE;
	stateDeteil = enemyNS::PRE_ATTACK;
	state = characterNS::PRE_ATTACK;
	mode = attackAnimationMode;
	// アニメーション終了時にフレームを戻すために保存
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;

	// 方向に応じてアニメーションを切り替え
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = attackLeftStartFrame;
		endFrame = attackLeftEndFrame;
		break;
	case characterNS::RIGHT:
		startFrame = attackRightStartFrame;
		endFrame = attackRightEndFrame;
		break;
	case characterNS::UP:
		startFrame = attackUpStartFrame;
		endFrame = attackUpEndFrame;
		break;
	case characterNS::DOWN:
		startFrame = attackDownStartFrame;
		endFrame = attackDownEndFrame;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//==========================================================
// 攻撃モードにチェンジするときに呼び出す関数
//==========================================================
void Enemy::changeAttack(characterNS::DIRECTION dir)
{
	// 攻撃直前モードにチェンジ
	loop = false;
	goalDirection = dir;
	switch (dir)
	{
	case characterNS::LEFT:
		changeDirection(moveLeftStartFrame, moveLeftEndFrame);
		break;
	case characterNS::RIGHT:
		changeDirection(moveRightStartFrame, moveRightEndFrame);
		break;
	case characterNS::UP:
		changeDirection(moveUpStartFrame, moveUpEndFrame);
		break;
	case characterNS::DOWN:
		changeDirection(moveDownStartFrame, moveDownEndFrame);
		break;
	case characterNS::NONE:
		break;
	default:
		break;
	}
	goalDirection = characterNS::NONE;
	stateDeteil = enemyNS::PRE_ATTACK;
	state = characterNS::PRE_ATTACK;
	mode = imageNS::VERTICAL;
	// アニメーション終了時にフレームを戻すために保存
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// 方向に応じてアニメーションを切り替え
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = attackLeftStartFrame;
		endFrame = attackLeftEndFrame;
		break;
	case characterNS::RIGHT:
		startFrame = attackRightStartFrame;
		endFrame = attackRightEndFrame;
		break;
	case characterNS::UP:
		startFrame = attackUpStartFrame;
		endFrame = attackUpEndFrame;
		break;
	case characterNS::DOWN:
		startFrame = attackDownStartFrame;
		endFrame = attackDownEndFrame;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//==========================================================
// 移動可能かチェック
//==========================================================
bool Enemy::checkCanMove(float x, float y)
{
	// 1マス32pixelのため32で割る
	// -16はめり込みを防止するために半マス分引いてる
	// +αは微調整…
	int map_x = (int)((x - 8) / 32) + 1;
	int map_y = (int)((y - 8) / 32) + 2;

	if (map_x <= 0)
		map_x = 0;
	if (map_x >= mapNS::MAP_WIDTH)
		map_x = mapNS::MAP_WIDTH - 1;
	if (map_y <= 0)
		map_y = 0;
	if (map_y >= mapNS::MAP_HEIGHT)
		map_y = mapNS::MAP_HEIGHT - 1;

	if (map->getMapCol(map_y, map_x) >= 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//==========================================================
// タイルの中央にキャラクターがいるかどうか
//==========================================================
bool Enemy::isCenterOfTile()
{
	map->resetMapCol(tileY, tileX);
	switch (goalDirection)
	{
	case characterNS::RIGHT:
		if (spriteData.x / 32 > tileX + 1)
		{
			tileX += 1;
			return true;
		}
		break;
	case characterNS::LEFT:
		if (spriteData.x / 32 < tileX - 1)
		{
			tileX -= 1;
			return true;
		}
		break;
	case characterNS::UP:
		if (spriteData.y / 32 < tileY - 1)
		{
			tileY -= 1;
			return true;
		}
		break;
	case characterNS::DOWN:
		if (spriteData.y / 32 > tileY + 1)
		{
			tileY += 1;
			return true;
		}
		break;
	}
	return false;
}

//==========================================================
// 指定した方向に進み始められるかどうか
//==========================================================
bool Enemy::canMoveTo(characterNS::DIRECTION dir)
{
	switch (dir)
	{
	case characterNS::LEFT:
		if (map->getMapCol(tileY, tileX - 1) >= 1)
		{
			return false;
		}
		break;
	case characterNS::RIGHT:
		if (map->getMapCol(tileY, tileX + 1) >= 1)
		{
			return false;
		}
		break;
	case characterNS::UP:
		if (map->getMapCol(tileY - 1, tileX) >= 1)
		{
			return false;
		}
		break;
	case characterNS::DOWN:
		if (map->getMapCol(tileY + 1, tileX) >= 1)
		{
			return false;
		}
		break;
	}
	return true;
}

//==========================================================
// 敵の種類をセットする関数
//==========================================================
void Enemy::setEnemyType(enemyNS::TYPE t)
{
	type = t;
}

//==========================================================
// 敵の種類を取得する関数
//==========================================================
enemyNS::TYPE Enemy::getEnemyType()
{
	return type;
}

//==========================================================
// ダメージを受ける時に掛ける割合の更新
//==========================================================
void Enemy::setDamagerPer(float per)
{
	damagePer = per;
}