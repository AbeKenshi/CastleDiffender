#include "brave.h"
#include "math.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Brave::Brave() : Character()
{
	spriteData.width = braveNS::WIDTH;			// 勇者のサイズ
	spriteData.height = braveNS::HEIGHT;
	spriteData.x = braveNS::X;					// 画面上の位置
	spriteData.y = braveNS::Y;
	spriteData.rect.bottom = braveNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = braveNS::WIDTH;
	frameDelay = braveNS::MOVE_ANIMATION_DELAY;
	startFrame = braveNS::MOVE_UP_START_FRAME;
	endFrame = braveNS::MOVE_UP_END_FRAME;
	currentFrame = startFrame;
	// Boxの衝突判定用
	edge.left = -braveNS::WIDTH / 4.0;
	edge.right = braveNS::WIDTH / 2.0;
	edge.top = -braveNS::HEIGHT / 26.0;
	edge.bottom = braveNS::HEIGHT / 2.0;
	// 状態は何もしない状態からスタート
	state = braveNS::STATE::MOVE;
	secondAttackFlag = false;
	mpTimer = 0.0;
	magicPoint = 100;							// MPはMAX100でスタート
}

//==========================================================
// パラメータ初期化
//==========================================================
void Brave::reset()
{
	magicPoint = 100;							// MPはMAX100でスタート
	spriteData.x = braveNS::X;					// 画面上の位置
	spriteData.y = braveNS::Y;
	frameDelay = braveNS::MOVE_ANIMATION_DELAY;
	startFrame = braveNS::MOVE_UP_START_FRAME;
	endFrame = braveNS::MOVE_UP_END_FRAME;
	currentFrame = startFrame;
	state = braveNS::STATE::MOVE;
	secondAttackFlag = false;
	mpTimer = 0.0;
	Character::reset();
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================	
void Brave::update(float frameTime)
{
	if (!active)
		return;
	attackCollisionFlag = false;
	// 状態遷移前の処理
	switch (state)
	{
	case braveNS::MOVE:		// 移動時はすべてのキーの入力を受け付ける
							// 上下左右キーが入力された場合、
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// 左キーが入力された場合、
			if (input->isKeyDown(BRAVE_LEFT_KEY))
			{
				// 左方向を向いていなければ左方向にアニメーションをリセット
				if (direction != characterNS::DIRECTION::LEFT)
				{
					direction = characterNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 移動可能だったら
				if (checkCanMove(spriteData.x - braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// 左に移動
					spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// 右キーが入力された場合、
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				// 右方向を向いていなければ右方向にアニメーションをリセット
				if (direction != characterNS::DIRECTION::RIGHT)
				{
					direction = characterNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 移動可能だったら
				if (checkCanMove(spriteData.x + braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// 右に移動
					spriteData.x += braveNS::MOVE_SPEED * frameTime;
				}
			}
			// 上キーが入力された場合、
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				// 上方向を向いていなければ上方向にアニメーションをリセット
				if (direction != characterNS::DIRECTION::UP)
				{
					direction = characterNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 移動可能だったら
				if (checkCanMove(spriteData.x, spriteData.y - braveNS::MOVE_SPEED * frameTime)) {
					// 上に移動
					spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// 下キーが入力された場合、
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				// 下方向を向いていなければ下方向にアニメーションをリセット
				if (direction != characterNS::DIRECTION::DOWN)
				{
					direction = characterNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 移動可能だったら
				if (checkCanMove(spriteData.x, spriteData.y + braveNS::MOVE_SPEED * frameTime)) {
					// 下に移動
					spriteData.y += braveNS::MOVE_SPEED * frameTime;
				}
			}
			Entity::updateOnlyImage(frameTime);
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))	// 攻撃キーが押された場合、
		{
			audio->playCue("kill");
			// アニメーションをリセット
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			// アニメーション終了時にフレームを戻すために保存
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			attackCollisionFlag = true;
			// 向いている方向でアニメーションを分岐
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = braveNS::DOWN_ATTACK_START_FRAME;
				endFrame = braveNS::DOWN_ATTACK_END_FRAME;
				break;
			case characterNS::RIGHT:
				startFrame = braveNS::RIGHT_ATTACK_START_FRAME;
				endFrame = braveNS::RIGHT_ATTACK_END_FRAME;
				break;
			case characterNS::LEFT:
				startFrame = braveNS::LEFT_ATTACK_START_FRAME;
				endFrame = braveNS::LEFT_ATTACK_END_FRAME;
				break;
			case characterNS::UP:
				startFrame = braveNS::UP_ATTACK_START_FRAME;
				endFrame = braveNS::UP_ATTACK_END_FRAME;
				break;
			}
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (input->isKeyDown(BRAVE_GAURD_KEY))	// ガードキーが押された場合、
		{
			// アニメーションをリセット
			state = braveNS::GAURD;
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
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		break;
	case braveNS::ATTACK:	// 攻撃時はアニメーションが終了するまで第二段攻撃の入力しか受け付けない
		if (input->isKeyDown(BRAVE_ATTACK_KEY) && currentFrame > startFrame + 2)
		{
			secondAttackFlag = true;
		}
		if (animComplete)
		{
			if (secondAttackFlag)
			{
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
				state = braveNS::SECOND_ATTACK;
				loop = false;
				currentFrame = startFrame;
				animTimer = 0.0f;
				animComplete = false;
				setRect();
				Entity::updateOnlyImage(frameTime);
				secondAttackFlag = false;
				velocity.y = -sqrt(2 * 2000.0f * braveNS::HEIGHT);
				attackCollisionFlag = true;
			}
			else
			{
				state = braveNS::MOVE;
				mode = imageNS::HORIZONTAL;
				loop = true;
				startFrame = oldStartFrame;
				endFrame = oldEndFrame;
				currentFrame = startFrame;
				animTimer = 0.0f;
				animComplete = false;
				setRect();
				Entity::updateOnlyImage(frameTime);
			}
		}
		break;
	case braveNS::SECOND_ATTACK:	// 第二段攻撃時はアニメーションが終了するまで入力を受け付けない
		velocity.y += frameTime * 2000.0f;
		if (animComplete)
		{
			state = braveNS::MOVE;
			mode = imageNS::HORIZONTAL;
			loop = true;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
			Entity::updateOnlyImage(frameTime);
			velocity.y = 0.0f;
		}
		break;
	case braveNS::GAURD:	// ボタンが離されたらガード終了
		if (!input->isKeyDown(BRAVE_GAURD_KEY))
		{
			state = braveNS::MOVE;
			mode = imageNS::HORIZONTAL;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
		}
		break;
	}
	// 状態遷移後の処理
	switch (state)
	{
	case braveNS::MOVE:
		updateMoving(frameTime);
		break;
	case braveNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case braveNS::GAURD:
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
	if (mpTimer > braveNS::MP_RECOVERY_TIME)
	{
		mpTimer = 0.0f;
		magicPoint += braveNS::MP_RECOVERY;
		if (magicPoint > 100)
			magicPoint = 100;
	}

	// 移動可能だったら
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y))
	{
		spriteData.x += frameTime * velocity.x;     // キャラをX方向に動かす
		spriteData.y += frameTime * velocity.y;     // キャラをY方向に動かす
	}
	// 画面の端まで来たら進めない
	if (spriteData.x > GAME_WIDTH - braveNS::WIDTH * getScale())	// 画面右端を超えたら
		spriteData.x = GAME_WIDTH - braveNS::WIDTH * getScale();	// 画面右端に移動
	if (spriteData.x < 0)											// 画面左端を超えたら
		spriteData.x = 0;											// 画面左端に移動
	if (spriteData.y < rectNS::HEIGHT - 10)								// 画面上端を超えたら
		spriteData.y = rectNS::HEIGHT - 10;								// 画面上端に移動
	if (spriteData.y > GAME_HEIGHT - braveNS::HEIGHT * getScale())  // 画面下端を超えたら
		spriteData.y = GAME_HEIGHT -braveNS::HEIGHT * getScale();	// 画面下端に移動
}

//==========================================================
// ダメージ
//==========================================================
void Brave::damage(WEAPON weapon)
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
		if (state == braveNS::GAURD)
			magicPoint -= 25;
		else
		{
			health -= enemyNS::ATTACK_DAMAGE;
			isDamaged = true;
		}
		break;
	default:
		break;
	}
	if (health <= 0)
		dead();
}