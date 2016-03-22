#ifndef _ENEMY_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ENEMY_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH = 24;				// 画像の幅（各フレーム）
	const int HEIGHT = 32;				// 画像の高さ
	const int X = 200;					// 画面上の位置
	const int Y = 200;
	const int MOVE_SPEED = 100;			// 移動速度（ピクセル）
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };	// 向いている方向
	const int TEXTURE_COLS = 12;		// テクスチャは12列
	const int MOVE_UP_START_FRAME = 3;	// 上方向移動のアニメーションはフレーム3から開始
	const int MOVE_UP_END_FRAME = 5;	// 上方向移動のアニメーションフレームは3、4、5
	const int MOVE_RIGHT_START_FRAME = 15;	// 右方向移動のアニメーションはフレーム15から開始
	const int MOVE_RIGHT_END_FRAME = 17;	// 右方向移動のアニメーションフレームは15、16、17
	const int MOVE_DOWN_START_FRAME = 27;	// 下方向移動のアニメーションはフレーム27から開始
	const int MOVE_DOWN_END_FRAME = 29;	// 下方向移動のアニメーションフレームは27、28、29
	const int MOVE_LEFT_START_FRAME = 39;	// 左方向移動のアニメーションはフレーム39から開始
	const int MOVE_LEFT_END_FRAME = 41;	// 左方向移動のアニメーションフレームは39、40、41
	const float MOVE_ANIMATION_DELAY = 0.2;	// 移動アニメーションのフレーム間の時間
	const float DAMAGE_TIME = 1.0f;
	enum STATE {MOVE, ATTACK, GAURD };
}

// Enemyクラス
class Enemy : public Entity
{
private:
	enemyNS::DIRECTION direction;		// 向き
	enemyNS::STATE state;				// 状態
	int oldStartFrame;
	int oldEndFrame;
	float timeCounter;					// アニメーション用のタイマー
	float totalTimeCounter;
	bool isDamaged;						// ダメージを受けている状態かどうか
	bool drawFlag;
public:
	// コンストラクタ
	Enemy();

	// 継承されたメンバー関数
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);

	// 新しく追加するメンバー関数
	// 移動時のアップデート関数
	void updateMoving(float frameTime);
	// 攻撃時のアップデート関数
	void updateAttacking(float frameTime);
	// 向いている方向を返す
	enemyNS::DIRECTION getDirection(){ return direction; }

};
#endif
