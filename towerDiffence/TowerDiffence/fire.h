#ifndef _FILE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _FILE_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "brave.h"
#include "constants.h"

namespace fireNS
{
	const int WIDTH = 24;							// 画像の幅（各フレーム）
	const int HEIGHT = 32;							// 画像の高さ
	const int COLLISION_RADIUS = 4;					// 円の衝突判定
	const float SPEED = 200;						// 1秒あたりのピクセル数
	const float FIRE_DELAY = 1.0f;					// 炎発動の間隔は4秒
	const int TEXTURE_COLS = 12;					// テクスチャは8列
	const int START_FRAME = 52;						// アニメーションはフレーム52から開始
	const int END_FRAME = 52 + 36;					// アニメーションフレームは52、64、76、88
	const float ANIMATION_DELAY = 0.1f;				// フレーム間の時間
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

	// 新しいメンバー関数
	void fire(Brave *brave);		// 勇者からミサイルを発射
};
#endif // !_FILE_H
