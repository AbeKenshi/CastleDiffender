#ifndef _CHARACTER_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _CHARACTER_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "map.h"

namespace characterNS
{
	enum DIRECTION { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NONE = 4};	// キャラクターの向き（上下左右）
	enum STATE { MOVE, ATTACK, SECOND_ATTACK, GAURD , PRE_ATTACK , WAIT , DEATH };			// 状態
}

// Characterクラス
// プレイヤーや敵クラスの基本となるクラス。
// 継承することで使用可能。継承なしではオブジェクトの生成はできない。
class Character : public Entity
{
protected:
	characterNS::DIRECTION direction;	// キャラクターの向き（上下左右）
	int oldStartFrame;					// 攻撃アニメーション終了後に戻るべきアニメーションフレーム保存用
	int oldEndFrame;					// 攻撃アニメーション終了後に戻るべきアニメーションフレーム保存用
	float damageTimer;					// ダメージ時のアニメーション用のタイマー
	float totalDamageTime;				// ダメージ時のアニメーション用のタイマー
	bool drawFlag;						// 描画フラグ、オンのときだけ画像を描画する。ダメージを受けている状態時に使用。ダメージ時は一定時間おきに反転。ダメージ時以外は常にオン
	bool isDamaged;						// ダメージを受けている状態ならtrue、それ以外ならfalse
	bool attackCollisionFlag;			// 攻撃用の衝突判定を出現させるフラグ。攻撃を開始してから一定時間後にtrueとなる。時間を調整することによってアニメーションと同期させるのが目的。
	Map *map;							// ステージマップへのポインタ
	characterNS::STATE state;			// 状態
	int moveUpStartFrame;
	int moveUpEndFrame;
	int moveRightStartFrame;
	int moveRightEndFrame;
	int moveDownStartFrame;
	int moveDownEndFrame;
	int moveLeftStartFrame;
	int moveLeftEndFrame;
	int moveAnimationDelay; 
	int attackUpStartFrame;
	int attackUpEndFrame;
	int attackRightStartFrame;
	int attackRightEndFrame;
	int attackDownStartFrame;
	int attackDownEndFrame;
	int attackLeftStartFrame;
	int attackLeftEndFrame;
public:
	// コンストラクタ
	Character();

	//==========================================================
	// 継承されたメンバー関数
	//==========================================================
	// 描画関数、描画フラグがオンのときのみ描画をする
	virtual void draw(COLOR_ARGB color);
	// Update
	// 通常、フレームごとに1回呼び出す
	// frameTimeは、移動とアニメーションの速さを制御するために使用
	virtual void update(float frameTime) = 0;
	// 人工知能。NPCの行動を決定するのに使用
	virtual void ai(float frameTime, Entity &ent) = 0;
	// キャラクターにダメージを与える関数
	virtual void damage(WEAPON) = 0;

	//==========================================================
	// 新しく追加するメンバー関数
	//==========================================================
	// パラメータリセット
	virtual void reset();
	// 移動可能かチェック
	virtual bool checkCanMove(float x, float y);	
	// 死亡時に呼び出す関数
	void dead();
	// 移動時のアップデート関数
	void updateMoving(float frameTime);
	// 攻撃時のアップデート関数
	void updateAttacking(float frameTime);

	//==========================================================
	// setter
	//==========================================================
	// マップへのポインタをセットする関数
	void setMapPointer(Map *m) { map = m; }
	// 状態をセットする関数
	void setState(characterNS::STATE st) { state = st; }

	//==========================================================
	// getter
	//==========================================================
	// 攻撃用の衝突判定を出現させるフラグを返す関数。攻撃状態に遷移した直後にtrueとなって、それ以外はfalse
	bool getAttackCollisionFlag() { return attackCollisionFlag; }
	// 向いている方向を返す関数
	characterNS::DIRECTION getDirection() { return direction; }
	// 状態を返す関数
	characterNS::STATE getState() { return state; }

};

#endif // !_CHARACTER_H
