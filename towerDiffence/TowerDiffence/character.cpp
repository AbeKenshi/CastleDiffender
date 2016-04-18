//==========================================================
/// @file
/// @brief    character.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "character.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Character::Character() : Entity()
{
	// 初期の方向は右
	direction = characterNS::RIGHT;
	// Boxの衝突判定を使用
	collisionType = entityNS::BOX;
	// 攻撃判定のコリジョンは最初はなし
	attackCollisionFlag = false;
	// 状態は何もしない状態からスタート
	state = characterNS::STATE::MOVE;
}

//==========================================================
// パラメータ初期化
//==========================================================
void Character::reset()
{
	// 攻撃アニメーション終了後に戻るべきアニメーションフレーム保存用
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	// 初期の方向は右
	direction = characterNS::RIGHT;
	// 攻撃判定のコリジョンはなしでリセット
	attackCollisionFlag = false;
	// 状態は何もしない状態からスタート
	state = characterNS::STATE::MOVE;
	// エンティティをリセット
	Entity::reset();
}

//==========================================================
// 移動時のアップデート関数
// アニメーション以外をアップデート
//==========================================================
void Character::updateMoving(float frameTime)
{
	// アニメーションのアップデートは単独で行われるのでそれ以外をアップデート
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// 攻撃時のアップデート関数
// 現状では通常のアップデート
//==========================================================
void Character::updateAttacking(float frameTime)
{
	Entity::update(frameTime);
}

//==========================================================
// 死亡時に呼び出される関数
//==========================================================
void Character::dead()
{
	// キャラクターを非アクティブにする
	active = false;
	visible = false;
	health = 0;
}

//==========================================================
// 移動可能かチェック
// 実行前：x、y = チェックしたい位置の画面上での座標
//==========================================================
bool Character::checkCanMove(float x, float y)
{
	// 1マス32pixelのため32で割る
	// -16はめり込みを防止するために半マス分引いてる
	// +αは微調整…
	int map_x = (int)((x - 16) / 32) + 1;
	int map_y = (int)((y - 16) / 32) + 1;
	if (map_x <= 0)
		map_x = 0;
	if (map_x >= mapNS::MAP_WIDTH)
		map_x = mapNS::MAP_WIDTH - 1;
	if (map_y <= 0)
		map_y = 0;
	if (map_y >= mapNS::MAP_HEIGHT)
		map_y = mapNS::MAP_HEIGHT - 1;

	// 進もうとするマップタイルに障害物があった場合、
	if (map->getMapCol(map_y, map_x) == 1 || map->getMapCol(map_y, map_x) == 2)
	{
		// 移動不可
		return false;
	}
	else  // 進もうとするマップタイルに障害物がない場合、
	{
		// 移動可能
		return true;
	}
}

//==========================================================
// 向いている方向をセットする
// 実行前：dir = セットするキャラクターの向き
//==========================================================
void Character::setDirection(characterNS::DIRECTION dir)
{
	// セットするキャラクターの向きによって分岐
	switch (dir)
	{
	case characterNS::LEFT:
		// 左方向を向いていなければ左方向にアニメーションをリセット
		if (direction != characterNS::DIRECTION::LEFT)
		{
			direction = characterNS::DIRECTION::LEFT;
			startFrame = moveLeftStartFrame;
			currentFrame = endFrame - currentFrame + moveLeftStartFrame;
			endFrame = moveLeftEndFrame;
			setRect();
		}
		break;
	case characterNS::RIGHT:
		// 右方向を向いていなければ右方向にアニメーションをリセット
		if (direction != characterNS::DIRECTION::RIGHT)
		{
			direction = characterNS::DIRECTION::RIGHT;
			startFrame = moveRightStartFrame;
			currentFrame = endFrame - currentFrame + moveRightStartFrame;
			endFrame = moveRightEndFrame;
			setRect();
		}
		break;
	case characterNS::UP:
		// 上方向を向いていなければ上方向にアニメーションをリセット
		if (direction != characterNS::DIRECTION::UP)
		{
			direction = characterNS::DIRECTION::UP;
			startFrame = moveUpStartFrame;
			currentFrame = endFrame - currentFrame + moveUpStartFrame;
			endFrame = moveUpEndFrame;
			setRect();
		}
		break;
	case characterNS::DOWN:
		// 下方向を向いていなければ下方向にアニメーションをリセット
		if (direction != characterNS::DIRECTION::DOWN)
		{
			direction = characterNS::DIRECTION::DOWN;
			startFrame = moveDownStartFrame;
			currentFrame = endFrame - currentFrame + moveDownStartFrame;
			endFrame = moveDownEndFrame;
			setRect();
		}
		break;
	default:
		break;
	}
}

//==========================================================
// 移動中へと状態を遷移
//==========================================================
void Character::changeStateToMove()
{
	// 状態は移動中へと遷移
	state = characterNS::MOVE;
	// アニメーションフレームの遷移は水平方向
	mode = imageNS::HORIZONTAL;
	// 移動中はアニメーションはループさせる
	loop = true;
	// アニメーションを向いている方向に合わせてセット
	startFrame = oldStartFrame;
	endFrame = oldEndFrame;
	setCurrentFrame(startFrame);
}