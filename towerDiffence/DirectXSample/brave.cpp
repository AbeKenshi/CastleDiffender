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
	// 左キーが押されてて、かつxcountが0以上なら0にしてからframeTimeを引く。
	// それ以外はframeTimeを引く。
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
		Entity::update(frameTime);
	}
	// 右キーが押されてて、かつxcountが0以下なら0にしてからframeTimeを足す。
	// それ以外はframeTimeを足す。
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
	// 上キーが押されてて、かつycountが0以上なら0にしてからframeTimeを引く。
	// それ以外はframeTimeを引く。
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
	// 下キーが押されてて、かつycountが0以下なら0にしてからframeTimeを足す。
	// それ以外はframeTimeを足す。
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
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// ダメージ
//==========================================================
void Brave::damage(WEAPON weapon)
{

}