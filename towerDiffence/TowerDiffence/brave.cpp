#include "brave.h"

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
	direction = braveNS::DIRECTION::RIGHT;
	state = braveNS::STATE::MOVE;
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
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			if (input->isKeyDown(BRAVE_LEFT_KEY))
			{
				if (direction != braveNS::DIRECTION::LEFT)
				{
					direction = braveNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				if (direction != braveNS::DIRECTION::RIGHT)
				{
					direction = braveNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.x += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				if (direction != braveNS::DIRECTION::UP)
				{
					direction = braveNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				if (direction != braveNS::DIRECTION::DOWN)
				{
					direction = braveNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.y += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))
		{
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
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
		break;
	case braveNS::ATTACK:
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
	default:
		Entity::update(frameTime);
		break;
	}
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