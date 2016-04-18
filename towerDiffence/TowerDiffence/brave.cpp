//==========================================================
/// @file
/// @brief    brave.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "brave.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Brave::Brave() : Character()
{
	spriteData.width = braveNS::WIDTH;							// 勇者のサイズ
	spriteData.height = braveNS::HEIGHT;
	spriteData.x = braveNS::X;									// 画面上の位置
	spriteData.y = braveNS::Y;
	spriteData.rect.bottom = braveNS::HEIGHT;					// 画面の一部を選択
	spriteData.rect.right = braveNS::WIDTH;
	frameDelay = braveNS::ANIMATION_DELAY;						// アニメーションの各フレームの間隔
	startFrame = braveNS::MOVE_UP_START_FRAME;					// アニメーションの最初のフレーム
	endFrame = braveNS::MOVE_UP_END_FRAME;						// アニメーションの最後のフレーム
	currentFrame = startFrame;									// 現在のフレームはアニメーションの最初のフレームに設定
	// Boxの衝突判定用
	edge.left = (LONG)(-braveNS::WIDTH * spriteData.scale / 2.0);
	edge.right = (LONG)(braveNS::WIDTH * spriteData.scale / 2.0);
	edge.top = (LONG)(-braveNS::HEIGHT * spriteData.scale / 2.0);
	edge.bottom = (LONG)(braveNS::HEIGHT * spriteData.scale / 2.0);

	secondAttackFlag = false;									// 二連撃目の攻撃フラグはオフ
	mpTimer = 0.0;												// MP回復用のタイマー
	magicPoint = 100;											// MPはMAX100でスタート
	moveUpStartFrame = braveNS::MOVE_UP_START_FRAME;			// 上方向移動のアニメーションの最初のフレーム
	moveUpEndFrame = braveNS::MOVE_UP_END_FRAME;				// 上方向移動のアニメーションの最後のフレーム
	moveRightStartFrame = braveNS::MOVE_RIGHT_START_FRAME;		// 右方向移動のアニメーションの最初のフレーム
	moveRightEndFrame = braveNS::MOVE_RIGHT_END_FRAME;			// 右方向移動のアニメーションの最後のフレーム
	moveDownStartFrame = braveNS::MOVE_DOWN_START_FRAME;		// 下方向移動のアニメーションの最初のフレーム
	moveDownEndFrame = braveNS::MOVE_DOWN_END_FRAME;			// 下方向移動のアニメーションの最後のフレーム
	moveLeftStartFrame = braveNS::MOVE_LEFT_START_FRAME;		// 左方向移動のアニメーションの最初のフレーム
	moveLeftEndFrame = braveNS::MOVE_LEFT_END_FRAME;			// 左方向移動のアニメーションの最後のフレーム
	frameDelay = braveNS::ANIMATION_DELAY;						// アニメーションのフレーム間の間隔（秒）
	attackUpStartFrame = braveNS::UP_ATTACK_START_FRAME;		// 上方向攻撃のアニメーションの最初のフレーム
	attackUpEndFrame = braveNS::UP_ATTACK_END_FRAME;			// 上方向攻撃のアニメーションの最後のフレーム
	attackRightStartFrame = braveNS::RIGHT_ATTACK_START_FRAME;	// 右方向攻撃のアニメーションの最初のフレーム
	attackRightEndFrame = braveNS::RIGHT_ATTACK_END_FRAME;		// 右方向攻撃のアニメーションの最後のフレーム
	attackDownStartFrame = braveNS::DOWN_ATTACK_START_FRAME;	// 下方向攻撃のアニメーションの最初のフレーム
	attackDownEndFrame = braveNS::DOWN_ATTACK_END_FRAME;		// 下方向攻撃のアニメーションの最後のフレーム
	attackLeftStartFrame = braveNS::LEFT_ATTACK_START_FRAME;	// 左方向攻撃のアニメーションの最初のフレーム
	attackLeftEndFrame = braveNS::LEFT_ATTACK_END_FRAME;		// 左方向攻撃のアニメーションの最後のフレーム
}

//==========================================================
// パラメータ初期化
//==========================================================
void Brave::reset()
{
	mpTimer = 0.0;												// MP回復用のタイマー
	magicPoint = 100;											// MPはMAX100でスタート
	spriteData.x = braveNS::X;									// 画面上の位置
	spriteData.y = braveNS::Y;
	frameDelay = braveNS::ANIMATION_DELAY;						// アニメーションのフレーム間の間隔（秒）
	startFrame = braveNS::MOVE_UP_START_FRAME;					// アニメーションの最初のフレーム
	endFrame = braveNS::MOVE_UP_END_FRAME;						// アニメーションの最後のフレーム
	currentFrame = startFrame;									// 現在のフレームはアニメーションの最初のフレームに設定
	secondAttackFlag = false;									// 二連撃目の攻撃フラグはオフ
	fire.reset();												// 炎を初期化
	Character::reset();
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================	
void Brave::update(float frameTime)
{
	// エンティティが非アクティブなら、何もしない
	if (!active)
		return;


	// 勇者の攻撃判定がでている場合はコリジョンを生成して当たり判定をとる
	if (attackCollisionFlag)
		braveAttackCollision.attack(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), direction);

	// FIRE_KEYに対応するキーが押されたら勇者から炎を発射
	if (input->isKeyDown(BRAVE_FIRE_KEY))
		fire.fire(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), getScale(), magicPoint, direction);

	// 攻撃用のエンティティを出現させるフラグをオフ
	attackCollisionFlag = false;

	// ここで状態遷移、座標の移動、アニメーションのリセットを行う
	// それぞれの状態ごとに処理を分岐
	switch (state)
	{
	case characterNS::MOVE:		// 移動時はすべてのキーの入力を受け付ける
		// 上下左右キーが入力された場合、
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// 入力に応じて勇者の向きを変更、移動
			changeWithMove(frameTime);
		}
		if (input->isKeyDown(BRAVE_ATTACK_KEY))	// 攻撃キーが押された場合、
		{
			// 攻撃用オーディオを再生
			audio->playCue("kill");
			// 状態を攻撃中に遷移
			state = characterNS::ATTACK;
			// アニメーションフレームの遷移は垂直方向
			mode = imageNS::VERTICAL;
			// アニメーション終了時にフレームを戻すために保存
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// 攻撃用のエンティティの出現フラグをオン
			attackCollisionFlag = true;
			// 向いている方向でアニメーションを分岐
			loop = false;
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = attackDownStartFrame;
				endFrame = attackDownEndFrame;
				break;
			case characterNS::RIGHT:
				startFrame = attackRightStartFrame;
				endFrame = attackRightEndFrame;
				break;
			case characterNS::LEFT:
				startFrame = attackLeftStartFrame;
				endFrame = attackLeftEndFrame;
				break;
			case characterNS::UP:
				startFrame = attackUpStartFrame;
				endFrame = attackUpEndFrame;
				break;
			}
			setCurrentFrame(startFrame);
		}
		else if (input->isKeyDown(BRAVE_GAURD_KEY))	// ガードキーが押された場合、
		{
			// 状態をガード中に遷移
			state = characterNS::GAURD;
			// アニメーション終了時にフレームを戻すために保存
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// 向いている方向でアニメーションを分岐
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = braveNS::DOWN_GUARD_START_FRAME;
				endFrame = braveNS::DOWN_GUARD_END_FRAME;
				break;
			case characterNS::RIGHT:
				startFrame = braveNS::RIGHT_GUARD_START_FRAME;
				endFrame = braveNS::RIGHT_GUARD_END_FRAME;
				break;
			case characterNS::LEFT:
				startFrame = braveNS::LEFT_GUARD_START_FRAME;
				endFrame = braveNS::LEFT_GUARD_END_FRAME;
				break;
			case characterNS::UP:
				startFrame = braveNS::UP_GUARD_START_FRAME;
				endFrame = braveNS::UP_GUARD_END_FRAME;
				break;
			}
			setCurrentFrame(startFrame);
		}
		break;
	case characterNS::ATTACK:	// 攻撃時はアニメーションが終了するまで第二段攻撃か移動の入力しか受け付けない
		// 上下左右キーが入力された場合、
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// 入力に応じて勇者の向きを変更、移動
			changeWithMove(frameTime);
		}
		// 攻撃中にさらに攻撃ボタンが押された場合、
		if (input->isKeyDown(BRAVE_ATTACK_KEY) && currentFrame > startFrame + 2)
		{
			// 第二撃攻撃のフラグをオン
			secondAttackFlag = true;
		}
		// 攻撃アニメーションが終了した場合、
		if (animComplete)
		{
			// 第二撃攻撃のフラグがオンなら
			if (secondAttackFlag)
			{
				// 状態は第二撃攻撃中へと遷移
				state = characterNS::SECOND_ATTACK;
				// 現在の向きに合わせてアニメーションを再度リセット
				loop = false;
				switch (direction)
				{
				case characterNS::DOWN:
					startFrame = braveNS::DOWN_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::DOWN_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::RIGHT:
					startFrame = braveNS::RIGHT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::RIGHT_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::UP:
					startFrame = braveNS::UP_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::UP_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::LEFT:
					startFrame = braveNS::LEFT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::LEFT_SECOND_ATTACK_END_FRAME;
					break;
				}
				setCurrentFrame(startFrame);
				// 第二撃攻撃のフラグをオフ
				secondAttackFlag = false;
				// 第二撃攻撃中は軽くジャンプしながら攻撃する
				velocity.y = -sqrt(2 * 2000.0f * braveNS::HEIGHT);
				// ジャンプを開始した直後のY座標を保存
				tmpY = getY();
				// 攻撃のエンティティの出現フラグをオン
				attackCollisionFlag = true;
			}
			else
			// 第二撃攻撃のフラグがオフなら
			{
				// 状態を移動中へと遷移
				changeStateToMove();
			}
			// アニメーションのみ更新（エンティティは更新しない）
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case characterNS::SECOND_ATTACK:	// 第二段攻撃時はアニメーションが終了するまで入力を受け付けない
		// ジャンプ中なので、重力に従って減速をする
		velocity.y += frameTime * 2000.0f;
		// y方向の速度 = -ジャンプを開始したときの初速度の場合（ジャンプ前のy座標まで戻っていることが期待される）、
		if (velocity.y > sqrt(2 * 2000.0f * braveNS::HEIGHT))
		{
			// 若干のずれを補正するために、強制的にy座標をジャンプ前の座標へと戻す
			setY(tmpY);
			// 状態を移動中へと遷移
			changeStateToMove();
			// アニメーションのみ更新（エンティティは更新しない）
			Entity::updateOnlyImage(frameTime);
			// y方向への速度を0にしてジャンプ終了
			velocity.y = 0.0f;
		}
		break;
	case characterNS::GAURD:	// ボタンが離されたらガード終了
		if (!input->isKeyDown(BRAVE_GAURD_KEY))
		{
			// 状態を移動中へと遷移
			changeStateToMove();
		}
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
	case characterNS::GAURD:
		Entity::update(frameTime);
		break;
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
		if (totalDamageTime > braveNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}

	// MPを一定時間ごとに回復
	mpTimer += frameTime;
	if (mpTimer > braveMpRecoveryTime)
	{
		mpTimer = 0.0f;
		magicPoint += braveMpRecovery;
		// MAX100を超えたら、100にする
		if (magicPoint > 100)
			magicPoint = 100;
	}

	// 移動可能だったら（第二撃攻撃中はジャンプ中なので移動を強制的に許可）
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y) || state == characterNS::SECOND_ATTACK)
	{
		spriteData.x += frameTime * velocity.x;     // キャラをX方向に動かす
		spriteData.y += frameTime * velocity.y;     // キャラをY方向に動かす
	}

	// 画面の端まで来たら進めない
	if (spriteData.x > GAME_WIDTH - braveNS::WIDTH * getScale())	// 画面右端を超えたら
		spriteData.x = GAME_WIDTH - braveNS::WIDTH * getScale();	// 画面右端に移動
	if (spriteData.x < 0)											// 画面左端を超えたら
		spriteData.x = 0;											// 画面左端に移動
	if (spriteData.y < rectNS::HEIGHT - 10)							// 画面上端を超えたら
		spriteData.y = rectNS::HEIGHT - 10;							// 画面上端に移動
	if (spriteData.y > GAME_HEIGHT - braveNS::HEIGHT * getScale())  // 画面下端を超えたら
		spriteData.y = GAME_HEIGHT -braveNS::HEIGHT * getScale();	// 画面下端に移動


	// 勇者の攻撃コリジョンを更新
	braveAttackCollision.update(frameTime);
	// 炎を更新
	fire.update(frameTime);
}

//==========================================================
// ダメージ処理
// WEAPONの種類によって受けるダメージが分岐
//==========================================================
void Brave::damage(WEAPON weapon)
{
	// 非アクティブな場合、ダメージは受けない
	if (!active)
		return;

	// WEAPONによってダメージを分岐
	switch (weapon)
	{
	case FIRE:					// 炎
		break;
	case BRAVE_ATTACK:			// 勇者の攻撃
		break;
	case BRAVE_SECOND_ATTACK:	// 勇者の第二撃
		break;
	case ENEMY_ATTACK:			// 雑魚敵
		// ガード中なら、ダメージの代わりにMPを消費
		if (state == characterNS::GAURD)
			magicPoint -= 25;
		else  // ガード中でないなら、
		{
			// 一定ダメージを受ける
			health -= enemyAttackDamage * damagePer;
			// ダメージ状態のフラグをオン
			isDamaged = true;
		}
		break;
	case MIDBOSS_ATTACK:		// 中ボス
		// ガード中なら、ダメージの代わりにMPを消費
		if (state == characterNS::GAURD)
			magicPoint -= 35;
		else  // ガード中でないなら、
		{
			// 一定ダメージを受ける
			health -= midBossAttackDamage * damagePer;
			// ダメージ状態のフラグをオン
			isDamaged = true;
		}
		break;
	default:
		break;
	}
	// 体力が0以下になったなら、死亡
	if (health <= 0)
		dead();
}

//==========================================================
// 向いている方向とアニメーションを切り替える
// 内部的にのみ使用
//==========================================================
void Brave::changeWithMove(float frameTime)
{
	float r = 1.0f;
	if (state == BRAVE_ATTACK)
		r = 2.0f;
	// 左キーが入力された場合、
	if (input->isKeyDown(BRAVE_LEFT_KEY))
	{
		// 向いている方向を左に
		setDirection(characterNS::LEFT);
		// 移動可能だったら
		if (checkCanMove(spriteData.x - braveMoveSpeed * frameTime, spriteData.y)) {
			// 左に移動
			spriteData.x -= braveMoveSpeed / r * frameTime;
		}
	}
	// 右キーが入力された場合、
	if (input->isKeyDown(BRAVE_RIGHT_KEY))
	{
		// 向いている方向を右に
		setDirection(characterNS::RIGHT);
		// 移動可能だったら
		if (checkCanMove(spriteData.x + braveMoveSpeed * frameTime, spriteData.y)) {
			// 右に移動
			spriteData.x += braveMoveSpeed / r * frameTime;
		}
	}
	// 上キーが入力された場合、
	if (input->isKeyDown(BRAVE_UP_KEY))
	{
		// 向いている方向を上に
		setDirection(characterNS::UP);
		// 移動可能だったら
		if (checkCanMove(spriteData.x, spriteData.y - braveMoveSpeed * frameTime)) {
			// 上に移動
			spriteData.y -= braveMoveSpeed / r * frameTime;
		}
	}
	// 下キーが入力された場合、
	if (input->isKeyDown(BRAVE_DOWN_KEY))
	{
		// 向いている方向を下に
		setDirection(characterNS::DOWN);
		// 移動可能だったら
		if (checkCanMove(spriteData.x, spriteData.y + braveMoveSpeed * frameTime)) {
			// 下に移動
			spriteData.y += braveMoveSpeed / r * frameTime;
		}
	}
	// アニメーションのみ更新（エンティティは更新しない）
	Entity::updateOnlyImage(frameTime);
}