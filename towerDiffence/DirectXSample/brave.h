#ifndef _BRAVE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _BRAVE_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace braveNS
{
	const int WIDTH = 24;							// 画像の幅（各フレーム）
	const int HEIGHT = 32;							// 画像の高さ
	const int X = GAME_WIDTH / 2 - WIDTH / 2;		// 画面上の位置
	const int Y = GAME_HEIGHT / 6 - HEIGHT;
	const int MOVE_SPEED = 100;						// 移動速度（ピクセル）
	enum DIRECTION { LEFT, RIGHT, UP, DOWN};	// 回転の方向
	const int TEXTURE_COLS = 12;					// テクスチャは6 * 4列
	const int MOVE_UP_START_FRAME = 48;				// 上方向移動のアニメーションはフレーム0から開始
	const int MOVE_UP_END_FRAME = 50;				// 上方向移動のアニメーションフレームは0、1、2、3、4、5
	const int MOVE_RIGHT_START_FRAME = 60;			// 右方向移動のアニメーションはフレーム12から開始
	const int MOVE_RIGHT_END_FRAME = 62;			// 右方向移動のアニメーションフレームは12、13、14、15、16、17
	const int MOVE_DOWN_START_FRAME = 72;			// 下方向移動のアニメーションはフレーム24から開始
	const int MOVE_DOWN_END_FRAME = 74;				// 下方向移動のアニメーションフレームは24、25、26、27、28、29
	const int MOVE_LEFT_START_FRAME = 84;			// 左方向移動のアニメーションはフレーム36から開始
	const int MOVE_LEFT_END_FRAME = 86;				// 左方向移動のアニメーションフレームは36、37、38、39、40、41
	const float MOVE_ANIMATION_DELAY = 0.2f;		// 移動アニメーションのフレーム間の時間
	const int DOWN_ATTACK_START_FRAME = 145 + 24;		// 下方向への攻撃アニメーションはフレーム145から開始
	const int DOWN_ATTACK_END_FRAME = 145 + 36;		// 下方向への攻撃アニメーションフレームは145、157、169、181
	const int LEFT_ATTACK_START_FRAME = 148 + 24;		// 左方向への攻撃アニメーションはフレーム148から開始
	const int LEFT_ATTACK_END_FRAME = 148 + 36;		// 左方向への攻撃アニメーションフレームは148、160、172、184
	const int UP_ATTACK_START_FRAME = 151 + 24;			// 上方向への攻撃アニメーションはフレーム151から開始
	const int UP_ATTACK_END_FRAME = 151 + 36;		// 上方向への攻撃アニメーションフレームは151、163、175、187
	const int RIGHT_ATTACK_START_FRAME = 154 + 24;		// 右方向への攻撃アニメーションはフレーム154から開始
	const int RIGHT_ATTACK_END_FRAME = 154 + 36;	// 右方向への攻撃アニメーションフレームは154、166、178、190
	enum STATE { MOVE, ATTACK };					// 状態
}

// Braveクラス
class Brave : public Entity
{
private:
	braveNS::DIRECTION direction;	// 向き
	braveNS::STATE state;			// 状態
	int oldStartFrame;
	int oldEndFrame;
public:
	// コンストラクタ
	Brave();

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
 };
#endif
