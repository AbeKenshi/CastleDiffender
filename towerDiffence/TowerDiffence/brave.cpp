#include "brave.h"
#include "math.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Brave::Brave() : Entity()
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
	state = braveNS::STATE::MOVE;
	secondAttackFlag = false;
}

//==========================================================
// 勇者を初期化
// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
//==========================================================
bool Brave::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// 勇者を描画
//==========================================================
void Brave::draw()
{
	Image::draw();		// 勇者を描画
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================
void Brave::update(float frameTime)
{	
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
				if (direction != braveNS::DIRECTION::LEFT)
				{
					direction = braveNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 左に移動
				spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			// 右キーが入力された場合、
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				// 右方向を向いていなければ右方向にアニメーションをリセット
				if (direction != braveNS::DIRECTION::RIGHT)
				{
					direction = braveNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 右に移動
				spriteData.x += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			// 上キーが入力された場合、
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				// 上方向を向いていなければ上方向にアニメーションをリセット
				if (direction != braveNS::DIRECTION::UP)
				{
					direction = braveNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 上に移動
				spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			// 下キーが入力された場合、
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				// 下方向を向いていなければ下方向にアニメーションをリセット
				if (direction != braveNS::DIRECTION::DOWN)
				{
					direction = braveNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// 下に移動
				spriteData.y += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))	// 攻撃キーが押された場合、
		{
			// アニメーションをリセット
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			// アニメーション終了時にフレームを戻すために保存
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// 向いている方向でアニメーションを分岐
			switch (direction)
			{
			case braveNS::DOWN:
				startFrame = braveNS::DOWN_ATTACK_START_FRAME;
				endFrame = braveNS::DOWN_ATTACK_END_FRAME;
				break;
			case braveNS::RIGHT:
				startFrame = braveNS::RIGHT_ATTACK_START_FRAME;
				endFrame = braveNS::RIGHT_ATTACK_END_FRAME;
				break;
			case braveNS::LEFT:
				startFrame = braveNS::LEFT_ATTACK_START_FRAME;
				endFrame = braveNS::LEFT_ATTACK_END_FRAME;
				break;
			case braveNS::UP:
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
			case braveNS::DOWN:
				startFrame = braveNS::DOWN_GUARD_START_FRAME;
				endFrame = braveNS::DOWN_GUARD_END_FRAME;
				break;
			case braveNS::RIGHT:
				startFrame = braveNS::RIGHT_GUARD_START_FRAME;
				endFrame = braveNS::RIGHT_GUARD_END_FRAME;
				break;
			case braveNS::LEFT:
				startFrame = braveNS::LEFT_GUARD_START_FRAME;
				endFrame = braveNS::LEFT_GUARD_END_FRAME;
				break;
			case braveNS::UP:
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
				case braveNS::DOWN:
					startFrame = braveNS::DOWN_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::DOWN_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::RIGHT:
					startFrame = braveNS::RIGHT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::RIGHT_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::UP:
					startFrame = braveNS::UP_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::UP_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::LEFT:
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

	spriteData.x += frameTime * velocity.x;     // 宇宙船をX方向に動かす
	spriteData.y += frameTime * velocity.y;     // 宇宙船をY方向に動かす
}

//==========================================================
// 移動時のアップデート関数
//==========================================================
void Brave::updateMoving(float frameTime)
{
	// アニメーションのアップデートは単独で行われるのでそれ以外をアップデート
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// 攻撃時のアップデート関数
//==========================================================
void Brave::updateAttacking(float frameTime)
{
	Entity::update(frameTime);
}

//==========================================================
// ダメージ
//==========================================================
void Brave::damage(WEAPON weapon)
{

}