#ifndef _ENEMY_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ENEMY_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH = 24;							// 画像の幅（各フレーム）
	const int HEIGHT = 32;							// 画像の高さ
	const int X = 200;								// 画面上の位置
	const int Y = 200;
	const int MOVE_SPEED = 100;						// 移動速度（ピクセル）
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };	// 向いている方向
	const int TEXTURE_COLS = 12;					// テクスチャは12列
	const int MOVE_UP_START_FRAME = 54;				// 上方向移動のアニメーションはフレーム54から開始
	const int MOVE_UP_END_FRAME = 56;				// 上方向移動のアニメーションフレームは54、55、56
	const int MOVE_RIGHT_START_FRAME = 66;			// 右方向移動のアニメーションはフレーム66から開始
	const int MOVE_RIGHT_END_FRAME = 68;			// 右方向移動のアニメーションフレームは66、67、68
	const int MOVE_DOWN_START_FRAME = 78;			// 下方向移動のアニメーションはフレーム78から開始
	const int MOVE_DOWN_END_FRAME = 80;				// 下方向移動のアニメーションフレームは78、79、80
	const int MOVE_LEFT_START_FRAME = 90;			// 左方向移動のアニメーションはフレーム90から開始
	const int MOVE_LEFT_END_FRAME = 92;				// 左方向移動のアニメーションフレームは90、91、92
	const float MOVE_ANIMATION_DELAY = 0.2;			// 移動アニメーションのフレーム間の時間
	const int ATTACK_UP_START_FRAME = 151;			// 上方向攻撃のアニメーションはフレーム151から開始
	const int ATTACK_UP_END_FRAME = 151 + 36;		// 上方向攻撃にアニメーションフレームは151、163、175、184
	const int ATTACK_RIGHT_START_FRAME = 148;		// 右方向攻撃のアニメーションはフレーム148から開始
	const int ATTACK_RIGHT_END_FRAME = 148 + 36;	// 右方向攻撃のアニメーションフレームは148、161、173、182
	const int ATTACK_DOWN_START_FRAME = 103;		// 下方向攻撃のアニメーションはフレーム103から開始
	const int ATTACK_DOWN_END_FRAME = 103 + 36;		// 下方向攻撃のアニメーションフレームは103、115、127、139
	const int ATTACK_LEFT_START_FRAME = 100;		// 左方向攻撃のアニメーションはフレーム100から開始
	const int ATTACK_LEFT_END_FRAME = 100 + 36;		// 左方向攻撃のアニメーションフレームは100、112、124、136
	const float ATTACK_TIME = 0.3f;					// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	const float CONTINUE_ATTACK_TIME = 0.8f;		// 連続で攻撃する場合の溜め時間
	const float DAMAGE_TIME = 1.0f;					// ダメージを受けている場合、DAMAGE_TIMEごとに画像が点滅
	enum STATE {MOVE, ATTACK, PRE_ATTACK, GAURD };	// 雑魚敵の状態
}

// Enemyクラス
class Enemy : public Entity
{
private:
	enemyNS::DIRECTION direction;		// 向き
	enemyNS::DIRECTION oldDirection;	// 攻撃直前に向いていた方向を格納
	enemyNS::DIRECTION goalDirection;	// 次に進むべき方向
	enemyNS::STATE state;				// 状態
	int oldStartFrame;					// 攻撃アニメーション終了後に戻るべきアニメーションフレーム保存用
	int oldEndFrame;					// 攻撃アニメーション終了後に戻るべきアニメーションフレーム保存用
	float distanceCounter;				// 距離計測用カウンター、同じ方向に一定距離進まないと方向転換できないようにする
	float damageTimer;					// ダメージ時のアニメーション用のタイマー
	float totalDamageTime;				// ダメージ時のアニメーション用のタイマー
	float attackTimer;					// 攻撃アニメーション用のタイマー
	bool isDamaged;						// ダメージを受けている状態かどうか
	bool drawFlag;						// 描画フラグ、ダメージを受けている状態時に使用
	bool nearPlayer;					// プレイヤーと隣接しているかどうか
	bool isAttacked;					// 攻撃した直後かどうか
public:
	// コンストラクタ
	Enemy();

	// 継承されたメンバー関数
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	virtual void ai(float frameTime, Entity &ent);
	void update(float frameTime);
	void damage(WEAPON);	


	// 新しく追加するメンバー関数
	// 移動時のアップデート関数
	void updateMoving(float frameTime);
	// 攻撃時のアップデート関数
	void updateAttacking(float frameTime);
	// 向いている方向を返す
	enemyNS::DIRECTION getDirection(){ return direction; }
	// プレイヤーと隣接しているかどうかをセット
	void setNearPlayer(bool np)
	{
		nearPlayer = np;
	}
	// 向きをgoalDirectionへとアップデートする関数
	void changeDirection(int strF, int endF);
};
#endif
