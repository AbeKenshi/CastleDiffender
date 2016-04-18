//==========================================================
/// @file
/// @brief    Enemyクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _ENEMY_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ENEMY_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "character.h"
#include "constants.h"
#include "map.h"
#include "barricade.h"
#include "enemyAttackCollision.h"

namespace enemyNS
{
	const int WIDTH = 32;							// 画像の幅（各フレーム）
	const int HEIGHT = 32;							// 画像の高さ
	const int MOVE_SPEED = 80;						// 移動速度（ピクセル）
	const int TEXTURE_COLS = 12;					// テクスチャは12列
	const int MOVE_UP_START_FRAME = 54;				// 上方向移動のアニメーションはフレーム54から開始
	const int MOVE_UP_END_FRAME = 56;				// 上方向移動のアニメーションフレームは54、55、56
	const int MOVE_RIGHT_START_FRAME = 66;			// 右方向移動のアニメーションはフレーム66から開始
	const int MOVE_RIGHT_END_FRAME = 68;			// 右方向移動のアニメーションフレームは66、67、68
	const int MOVE_DOWN_START_FRAME = 78;			// 下方向移動のアニメーションはフレーム78から開始
	const int MOVE_DOWN_END_FRAME = 80;				// 下方向移動のアニメーションフレームは78、79、80
	const int MOVE_LEFT_START_FRAME = 90;			// 左方向移動のアニメーションはフレーム90から開始
	const int MOVE_LEFT_END_FRAME = 92;				// 左方向移動のアニメーションフレームは90、91、92
	const float MOVE_ANIMATION_DELAY = 0.1f;		// 移動アニメーションのフレーム間の時間
	const int ATTACK_UP_START_FRAME = 151;			// 上方向攻撃のアニメーションはフレーム151から開始
	const int ATTACK_UP_END_FRAME = 151 + 36;		// 上方向攻撃にアニメーションフレームは151、163、175、184
	const int ATTACK_RIGHT_START_FRAME = 148;		// 右方向攻撃のアニメーションはフレーム148から開始
	const int ATTACK_RIGHT_END_FRAME = 148 + 36;	// 右方向攻撃のアニメーションフレームは148、161、173、182
	const int ATTACK_DOWN_START_FRAME = 103;		// 下方向攻撃のアニメーションはフレーム103から開始
	const int ATTACK_DOWN_END_FRAME = 103 + 36;		// 下方向攻撃のアニメーションフレームは103、115、127、139
	const int ATTACK_LEFT_START_FRAME = 100;		// 左方向攻撃のアニメーションはフレーム100から開始
	const int ATTACK_LEFT_END_FRAME = 100 + 36;		// 左方向攻撃のアニメーションフレームは100、112、124、136
	const float ATTACK_TIME = 0.8f;					// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	const float CONTINUE_ATTACK_TIME = 0.8f;		// 連続で攻撃する場合の溜め時間
	const float DAMAGE_TIME = 1.0f;					// ダメージを受けている場合、DAMAGE_TIMEごとに画像が点滅
	enum TYPE { NORMAL, RED, BLUE };                // 敵の種類
}

// Enemyクラス
class Enemy : public Character
{
protected:
	characterNS::DIRECTION mOldDirection;	// 攻撃直前に向いていた方向を格納
	characterNS::DIRECTION mGoalDirection;	// 次に進むべき方向
	float mAttackTimer;						// 攻撃アニメーション用のタイマー
	bool mNearBarricade;					// バリケードと隣接しているかどうか
	bool mIsAttacked;						// 攻撃した直後かどうか
	bool mCanMakeDecesionMove;				// 移動に関しての意思決定を行えるかどうか
	Barricade* mBarricades;					// バリケードの配列へのポインタ
	int mNearBarricadeIndex;				// 最近接のバリケードのインデックス
	float mContinueAttackTime;				// 連続で攻撃する場合の溜め時間
	float mAttackTime;						// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	imageNS::MODE mAttackAnimationMode;		// 攻撃時のアニメーションの遷移モード（水平か垂直方向）
	enemyNS::TYPE mType;                    // 敵の種類
	EnemyCollision mAttackCollision;		// 攻撃判定用のコリジョン
public:
	// コンストラクタ
	Enemy();

	//==========================================================
	// 継承されたメンバー関数
	//==========================================================
	// Update
	// 通常、フレームごとに1回呼び出す
	// frameTimeは、移動とアニメーションの速さを制御するために使用
	virtual void update(float frameTime);
	// 人工知能。NPCの行動を決定するのに使用
	virtual void ai(float frameTime, Entity &ent);
	// ダメージ処理
	// WEAPONの種類によって受けるダメージが分岐
	virtual void damage(WEAPON);
	// パラメータリセット
	virtual void reset();

	//==========================================================
	// setter
	//==========================================================
	// バリケードと隣接しているかどうかをセット
	void setNearBarricade(bool nb) { mNearBarricade = nb; }
	// バリケードの配列へのポインタをセットする関数
	void setBarricadesPointer(Barricade *b) { mBarricades = b; }
	// 次に進むべき方向をセットする関数
	void setGoalDirection(characterNS::DIRECTION gd) { mGoalDirection = gd; }
	// 敵の種類をセットする関数
	void setEnemyType(enemyNS::TYPE t)
	{
		mType = t;
	}

	//==========================================================
	// getter
	//==========================================================
	// 次に進むべき方向を返す関数
	characterNS::DIRECTION getGoalDirection() { return mGoalDirection; }
	// 移動に関しての意思決定を行えるかどうか
	bool canMakeDecesionMoving() { return mCanMakeDecesionMove; }
	// 最近接のバリケードのインデックスを返す
	int getNearBarricadeIndex() { return mNearBarricadeIndex; }
	// 攻撃判定用のコリジョンを返す
	EnemyCollision& getAttackCollision() { return mAttackCollision; }
	// 敵の種類を取得する関数
	enemyNS::TYPE getEnemyType() { return mType; }
	
	// 向きをgoalDirectionへとアップデートする関数
	void changeDirection(int strF, int endF);
	// 一番近くのバリケードのインデックスを返す関数
	int searchNearBarricadeIndex();
	// 雑魚敵から城までの直線上にバリケードが存在したらtrue、存在しない場合はfalseを返す。
	bool checkBarricadeOnLine();
	// 攻撃モードにチェンジするときに呼び出す関数
	virtual void changeAttack(VECTOR2 &collisionVector);
	// 攻撃モードにチェンジするときに呼び出す関数
	virtual void changeAttack(characterNS::DIRECTION dir);
	// タイルの中央にキャラクターがいるかどうか
	virtual bool isCenterOfTile();
	// 指定した方向に進めるかどうか
	bool canMoveTo(characterNS::DIRECTION dir);
};
#endif
