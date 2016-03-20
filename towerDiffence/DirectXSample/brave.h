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
	enum DIRECTION { NONE, LEFT, RIGHT, UP, DOWN};	// 回転の方向
	const int TEXTURE_COLS = 12;					// テクスチャは6 * 4列
	const int MOVE_UP_START_FRAME = 0;				// 上方向移動のアニメーションはフレーム0から開始
	const int MOVE_UP_END_FRAME = 5;				// 上方向移動のアニメーションフレームは0、1、2、3、4、5
	const int MOVE_RIGHT_START_FRAME = 12;			// 右方向移動のアニメーションはフレーム12から開始
	const int MOVE_RIGHT_END_FRAME = 17;			// 右方向移動のアニメーションフレームは12、13、14、15、16、17
	const int MOVE_DOWN_START_FRAME = 24;			// 下方向移動のアニメーションはフレーム24から開始
	const int MOVE_DOWN_END_FRAME = 29;				// 下方向移動のアニメーションフレームは24、25、26、27、28、29
	const int MOVE_LEFT_START_FRAME = 36;			// 左方向移動のアニメーションはフレーム36から開始
	const int MOVE_LEFT_END_FRAME = 41;				// 左方向移動のアニメーションフレームは36、37、38、39、40、41
	const float MOVE_ANIMATION_DELAY = 0.2f;		// 移動アニメーションのフレーム間の時間
	
}

// Braveクラス
class Brave : public Entity
{
private:
	braveNS::DIRECTION direction;	// 向き
public:
	// コンストラクタ
	Brave();

	// 継承されたメンバー関数
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
 };
#endif
