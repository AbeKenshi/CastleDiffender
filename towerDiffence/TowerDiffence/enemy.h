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
	const float MOVE_ANIMATION_DELAY = 0.1f;			// 移動アニメーションのフレーム間の時間
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
	const float ATTACK_DAMAGE = 5.0f;
	enum STATE_DETAIL { MOVE_CASTLE, MOVE_BARRICADE, ATTACK_BRAVE, ATTACK_CASTLE, ATTACK_BARRICADE, PRE_ATTACK, GAURD , WAIT };	// 雑魚敵の状態
	enum TYPE {NORMAL, RED, BLUE};                  // 敵の種類
}

// Enemyクラス
class Enemy : public Character
{
protected:
	characterNS::DIRECTION oldDirection;	// 攻撃直前に向いていた方向を格納
	characterNS::DIRECTION goalDirection;	// 次に進むべき方向
	enemyNS::STATE_DETAIL stateDeteil;		// 状態
	enemyNS::STATE_DETAIL attackState;		// 攻撃用の状態
	float attackTimer;						// 攻撃アニメーション用のタイマー
	bool nearBarricade;						// バリケードと隣接しているかどうか
	bool isAttacked;						// 攻撃した直後かどうか
	bool inCertainRange;					// プレイヤーが一定範囲内にいるか
	bool canMakeDecesionMove;				// 移動に関しての意思決定を行えるかどうか
	Barricade* barricades;					// バリケードの配列へのポインタ
	int nearBarricadeIndex;					// 最近接のバリケードのインデックス
	float continueAttackTime;
	float attackTime;
	float attackDamage;
	imageNS::MODE attackAnimationMode;
	enemyNS::TYPE type;                     // 敵の種類
	EnemyCollision attackCollision;			// 攻撃判定用のコリジョン
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
	// キャラクターにダメージを与える関数
	virtual void damage(WEAPON);
	// パラメータリセット
	virtual void reset();

	//==========================================================
	// setter
	//==========================================================
	// バリケードと隣接しているかどうかをセット
	void setNearBarricade(bool nb) { nearBarricade = nb; }
	// 状態をセットする関数
	void setStateDetail(enemyNS::STATE_DETAIL st) { stateDeteil = st; }
	// 攻撃の状態をセットする関数
	void setAttackState(enemyNS::STATE_DETAIL st) { attackState = st; }
	// バリケードの配列へのポインタをセットする関数
	void setBarricadesPointer(Barricade *b) { barricades = b; }
	// 次に進むべき方向をセットする関数
	void setGoalDirection(characterNS::DIRECTION gd) { goalDirection = gd; }
	// 敵の種類をセットする関数
	void setEnemyType(enemyNS::TYPE t);
	// ダメージを受ける時に掛ける割合の更新
	void setDamagerPer(float per);

	//==========================================================
	// getter
	//==========================================================
	// 状態を返す関数
	enemyNS::STATE_DETAIL getStateDetail() { return stateDeteil; }
	// 次に進むべき方向を返す関数
	characterNS::DIRECTION getGoalDirection() { return goalDirection; }
	// 移動に関しての意思決定を行えるかどうか
	bool canMakeDecesionMoving() { return canMakeDecesionMove; }
	// 最近接のバリケードのインデックスを返す
	int getNearBarricadeIndex() { return nearBarricadeIndex; }
	// 攻撃判定用のコリジョンを返す
	EnemyCollision& getAttackCollision() { return attackCollision; }
	
	// 向きをgoalDirectionへとアップデートする関数
	void changeDirection(int strF, int endF);
	// プレイヤーとの距離が一定範囲内ならtrue、それ以外はfalseを返す
	bool checkDistancePlayer(int px, int py);
	// 一番近くのバリケードの位置を返す関数
	VECTOR2 searchNearBarricade(Entity &entity);
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
	// 敵の種類を取得する関数
    enemyNS::TYPE getEnemyType();
};
#endif
