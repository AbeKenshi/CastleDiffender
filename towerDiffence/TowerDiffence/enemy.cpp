//==========================================================
/// @file
/// @brief    enemy.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "enemy.h"
#include <iostream>
//==========================================================
// デフォルトコンストラクタ
//==========================================================
Enemy::Enemy() : Character()
{
	spriteData.width = enemyNS::WIDTH;								// 雑魚敵のサイズ
	spriteData.height = enemyNS::HEIGHT;
	spriteData.rect.bottom = enemyNS::HEIGHT;						// 画面の一部を選択
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;						// アニメーションの各フレームの間隔
																	// 初期の方向は右
	goalDirection = characterNS::RIGHT;								// 次に進むべき方向
	oldDirection = direction;										// 攻撃直前に向いていた方向
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;					// アニメーションの最初のフレーム
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;						// アニメーションの最後のフレーム
	oldStartFrame = startFrame;										// 攻撃アニメーション終了後に戻るべきアニメーションの最初のフレーム
	oldEndFrame = endFrame;											// 攻撃アニメーション終了後に戻るべきアニメーションの最後のフレーム
	currentFrame = startFrame;										// 現在のフレームをアニメーションの最初のフレームにセット
																	// Boxの衝突判定用
	edge.left = (LONG)(-enemyNS::WIDTH * spriteData.scale / 2.0);
	edge.right = (LONG)(enemyNS::WIDTH * spriteData.scale / 2.0);
	edge.top = (LONG)(-enemyNS::HEIGHT * spriteData.scale / 2.0);
	edge.bottom = (LONG)(enemyNS::HEIGHT * spriteData.scale / 2.0);

	canMakeDecesionMove = false;									// 移動に関しての意思決定を行えるかどうか
	attackAnimationMode = imageNS::VERTICAL;						// 攻撃時のアニメーションの遷移モード（水平、垂直）
	moveUpStartFrame = enemyNS::MOVE_UP_START_FRAME;				// 上方向移動のアニメーションの最初のフレーム
	moveUpEndFrame = enemyNS::MOVE_UP_END_FRAME;					// 上方向移動のアニメーションの最後のフレーム
	moveRightStartFrame = enemyNS::MOVE_RIGHT_START_FRAME;			// 右方向移動のアニメーションの最初のフレーム
	moveRightEndFrame = enemyNS::MOVE_RIGHT_END_FRAME;				// 右方向移動のアニメーションの最後のフレーム
	moveDownStartFrame = enemyNS::MOVE_DOWN_START_FRAME;			// 下方向移動のアニメーションの最初のフレーム
	moveDownEndFrame = enemyNS::MOVE_DOWN_END_FRAME;				// 下方向移動のアニメーションの最後のフレーム
	moveLeftStartFrame = enemyNS::MOVE_LEFT_START_FRAME;			// 左方向移動のアニメーションの最初のフレーム
	moveLeftEndFrame = enemyNS::MOVE_LEFT_END_FRAME;				// 左方向移動のアニメーションの最後のフレーム
	attackUpStartFrame = enemyNS::ATTACK_UP_START_FRAME;			// 上方向攻撃のアニメーションの最初のフレーム
	attackUpEndFrame = enemyNS::ATTACK_UP_END_FRAME;				// 上方向攻撃のアニメーションの最後のフレーム
	attackRightStartFrame = enemyNS::ATTACK_RIGHT_START_FRAME;		// 右方向攻撃のアニメーションの最初のフレーム
	attackRightEndFrame = enemyNS::ATTACK_RIGHT_END_FRAME;			// 右方向攻撃のアニメーションの最後のフレーム
	attackDownStartFrame = enemyNS::ATTACK_DOWN_START_FRAME;		// 下方向攻撃のアニメーションの最初のフレーム
	attackDownEndFrame = enemyNS::ATTACK_DOWN_END_FRAME;			// 下方向攻撃のアニメーションの最後のフレーム
	attackLeftStartFrame = enemyNS::ATTACK_LEFT_START_FRAME;		// 左方向攻撃のアニメーションの最初のフレーム
	attackLeftEndFrame = enemyNS::ATTACK_LEFT_END_FRAME;			// 左方向攻撃のアニメーションの最後のフレーム
	attackTime = enemyNS::ATTACK_TIME;								// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	continueAttackTime = enemyNS::CONTINUE_ATTACK_TIME;				// 連続で攻撃する場合の溜め時間
	damagePer = 1.0f;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Enemy::reset()
{
	Character::reset();
	// 初期の方向は右
	oldDirection = direction;
	goalDirection = characterNS::RIGHT;
	// 移動に関しての意思決定は行えない
	canMakeDecesionMove = false;
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
	
	// 攻撃判定がでている場合はコリジョンを生成して当たり判定をとる
	if (attackCollisionFlag) {
		attackCollision.attack(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), direction);
	}
	// 攻撃中のエンティティを出すフラグをオフ
	attackCollisionFlag = false;
	// 移動に関しての意思決定はデフォルトでは行えない
	canMakeDecesionMove = false;

	// ここで状態遷移、座標の移動、アニメーションのリセットを行う
	// それぞれの状態ごとに処理を分岐
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
			map->updateMapCol((float)(tileY * mapNS::TEXTURE_SIZE), (float)(tileX * mapNS::TEXTURE_SIZE), map->getMapCol(tileY, tileX) + 3);
			// 移動に関しての意思決定が可能
			canMakeDecesionMove = true;
		}
		break;
	case characterNS::ATTACK:	// 攻撃中
		// アニメーションが終了していたら攻撃終了
		// 状態を移動時に戻す
		if (animComplete)
		{
			// 移動に関しての意思決定が可能
			canMakeDecesionMove = true;
			// 攻撃直後なのでフラグをオン
			isAttacked = true;
			// 状態を移動中へと遷移
			changeStateToMove();
			// 向いている方向を戻す
			direction = oldDirection;
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case characterNS::PRE_ATTACK:	// 攻撃直前
		// タイマーを加算、一定時間を超えたら攻撃に移る
		attackTimer += frameTime;
		// 攻撃直後ならcuntinueAttackTime後に攻撃
		if (isAttacked && attackTimer > continueAttackTime)
		{
			attackTimer = 0.0f;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		// 攻撃直後でないならattackTime後に攻撃
		else if (!isAttacked && attackTimer > attackTime)
		{
			attackTimer = 0.0f;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		break;
	case characterNS::WAIT:		// 待機中
		// 移動に関しての意思決定が可能
		canMakeDecesionMove = true;
		break;
	case characterNS::DEATH:	// 死亡中
		// 描画は可能
		drawFlag = true;
		// ダメージは無効
		isDamaged = false;
		// ジャンプ中なので、重力に従って減速をする
		velocity.y += frameTime * 2000.0f;
		// xy方向にジャンプ
		spriteData.x += frameTime * velocity.x;
		spriteData.y += frameTime * velocity.y;
		// ゲーム画面より下に出たら、エンティティを非アクティブ化
		if (spriteData.y > GAME_HEIGHT)
			dead();
	default:
		break;
	}

	// 状態遷移後の処理
	// 移動中はキーが押されている間のみアニメーションが進むようにしたいので、
	// エンティティとアニメーションの更新を独立に行っている
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
		// ダメージ時にアニメーション用のタイマーを加算
		damageTimer += frameTime;
		totalDamageTime += frameTime;
		// 0.15秒ごとに描画フラグを切り替え
		if (damageTimer > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			damageTimer = 0.0f;
		}
		// DAMAGE_TIME分だけ点滅したら、点滅を終了
		if (totalDamageTime > enemyNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// 攻撃用エンティティを更新
	attackCollision.update(frameTime);
}

//==========================================================
// ダメージ処理
// WEAPONの種類によって受けるダメージが分岐
//==========================================================
void Enemy::damage(WEAPON weapon)
{
	// 敵のタイプによって、受けるダメージの割合を変化
	if (type == enemyNS::NORMAL)
		setDamagePer(1.0f);
	else if (type == enemyNS::RED)
		setDamagePer(0.8f);
	else if (type == enemyNS::BLUE)
		setDamagePer(0.9f);

	// WEAPONによってダメージを分岐
	switch (weapon)
	{
	case FIRE:					// 炎
		// 一定ダメージを受ける
		health -= braveFireDamage * damagePer;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case BRAVE_ATTACK:			// 勇者の攻撃
		// 一定ダメージを受ける
		health -= braveAttackDamage * damagePer;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case BRAVE_SECOND_ATTACK:	// 勇者の第二撃
		// 一定ダメージを受ける
		health -= braveAttackDamage * damagePer;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	// 体力が0以下になったら、
	if (health <= 0)
	{
		isDamaged = false;
		// 状態を死亡時に遷移
		state = characterNS::DEATH;
		// 適当な方向へジャンプしながら画面外へと落ちていく
		if (rand() % 2 == 0)
			velocity.x = 32.0f * 2.0;
		else
			velocity.x = -32.0f * 2.0;
		velocity.y = -sqrt(2 * 2000.0f * 96 * 2);
		map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
	}
}

//==========================================================
// 人工知能
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
}

//==========================================================
// 向いている方向を変更するメソッド
//==========================================================
void Enemy::changeDirection(int strF, int endF)
{
	direction = goalDirection;
	startFrame = strF;
	endFrame = endF;
	setCurrentFrame(startFrame);
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
		// もしバリケードがアクティブなら
		if (barricades[i].getActive())
		{
			// 探索1つ目の場合
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getTileX() - getTileX());
				minY = (int)abs(barricades[i].getTileY() - getTileY());
				minIndex = i;
			}
			else // 2つ目以降
			{
				if ((barricades[i].getTileX() - getTileX())*(barricades[i].getTileX() - getTileX()) +
					(barricades[i].getTileY() - getTileY())*(barricades[i].getTileY() - getTileY()) <
					minX * minX + minY * minY)
				{
					// 新たに代入
					minX = (int)abs(barricades[i].getTileX() - getTileX());
					minY = (int)abs(barricades[i].getTileY() - getTileY());
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
	// 雑魚敵の上下左右それぞれに対して、雑魚敵から近い順に城がないかをチェック
	// それぞれの方向について、城以外のオブジェクトが先に見つかった場合はtrueを返す
	// いずれかの方向について、城までの直線状になんのオブジェクトもない場合はfalseを返す
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
	// 衝突ベクトルを利用して、衝突対象がある方向を向くように設定
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
	// 次に進むべき方向はリセット
	goalDirection = characterNS::NONE;
	// 攻撃直前に状態を遷移
	state = characterNS::PRE_ATTACK;
	// アニメーションのモードを設定
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
	setCurrentFrame(startFrame);
	return;
}

//==========================================================
// 攻撃モードにチェンジするときに呼び出す関数
//==========================================================
void Enemy::changeAttack(characterNS::DIRECTION dir)
{
	// 攻撃直前モードにチェンジ
	loop = false;
	// 方向を変更
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
	// 次に進むべき方向はリセット
	goalDirection = characterNS::NONE;
	// 攻撃直前に状態を遷移
	state = characterNS::PRE_ATTACK;
	// アニメーションのモードを設定
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
	setCurrentFrame(startFrame);
	return;
}

//==========================================================
// タイルの中央にキャラクターがいるかどうか
//==========================================================
bool Enemy::isCenterOfTile()
{
	bool isCenter = false;
	// 上下左右どこに移動しているかによって中央にいるかの判定を分岐
	// 基本的には、今いるタイルを跨いだらタイルを移動して中央に来たと判定
	switch (goalDirection)
	{
	case characterNS::RIGHT:
		if (spriteData.x / 32 >= tileX + 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileX += 1;
			isCenter = true;
		}
		break;
	case characterNS::LEFT:
		if (spriteData.x / 32 <= tileX - 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileX -= 1;
			isCenter = true;
		}
		break;
	case characterNS::UP:
		if (spriteData.y / 32 <= tileY - 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileY -= 1;
			isCenter = true;
		}
		break;
	case characterNS::DOWN:
		if (spriteData.y / 32 >= tileY + 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileY += 1;
			isCenter = true;
		}
		break;
	}
	return isCenter;
}

//==========================================================
// 指定した方向に進み始められるかどうか
//==========================================================
bool Enemy::canMoveTo(characterNS::DIRECTION dir)
{
	// 指定した方向のタイルに障害物があれば移動できない
	// なければ移動可能
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