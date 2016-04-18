//==========================================================
/// @file
/// @brief    Fireクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _FIRE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _FIRE_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "character.h"
#include "constants.h"


// Fireクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace fireNS
{
	const int WIDTH = 24;							// 画像の幅（各フレーム）
	const int HEIGHT = 32;							// 画像の高さ
	const int COLLISION_RADIUS = 4;					// 円の衝突判定
	const float SPEED = 300;						// 1秒あたりのピクセル数
	const float FIRE_DELAY = 0.5f;					// 炎発動の間隔は4秒
	const int TEXTURE_COLS = 12;					// テクスチャは8列
	const int START_FRAME = 52;						// アニメーションはフレーム52から開始
	const int END_FRAME = 52 + 36;					// アニメーションフレームは52、64、76、88
	const float ANIMATION_DELAY = 0.1f;				// フレーム間の時間
	const int FIRE_MP = 20;							// 必殺技に使用するMP
}

class Fire : public Entity							// Entityクラスを継承
{
private:
	float fireTimer;								// 発射が可能になるまでの残り時間
public:
	// コンストラクタ
	Fire();

	// 継承されたメンバー関数
	void update(float frameTime);
	void reset();

	// 新しいメンバー関数
	// 勇者から炎を発射
	// 指定した位置にこのエンティティをアクティブにして出現させる
	void fire(float centerX, float centerY, float width, float height, float scale, int& mp, characterNS::DIRECTION direction);
};
#endif
