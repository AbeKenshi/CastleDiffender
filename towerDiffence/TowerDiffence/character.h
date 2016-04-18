//==========================================================
/// @file
/// @brief    Characterクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _CHARACTER_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _CHARACTER_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "map.h"

// Characterクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace characterNS
{
	enum DIRECTION { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NONE = 4};				// キャラクターの向き（上下左右）
	enum STATE { MOVE, ATTACK, SECOND_ATTACK, GAURD , PRE_ATTACK , WAIT , DEATH };	// 状態（移動中、攻撃中、第二撃中、ガード中、攻撃直前、待機、死亡）
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
	bool attackCollisionFlag;			// 攻撃用の衝突判定を出現させるフラグ。攻撃を開始してから一定時間後にtrueとなる。時間を調整することによってアニメーションと同期させるのが目的。
	Map *map;							// ステージマップへのポインタ
	characterNS::STATE state;			// 状態（移動中、攻撃中、第二撃中、ガード中、攻撃直前、待機、死亡）
	int moveUpStartFrame;				// 上方向移動のアニメーションの最初のフレーム
	int moveUpEndFrame;					// 上方向移動のアニメーションの最後のフレーム
	int moveRightStartFrame;			// 右方向移動のアニメーションの最初のフレーム
	int moveRightEndFrame;				// 右方向移動のアニメーションの最後のフレーム
	int moveDownStartFrame;				// 下方向移動のアニメーションの最初のフレーム
	int moveDownEndFrame;				// 下方向移動のアニメーションの最後のフレーム
	int moveLeftStartFrame;				// 左方向移動のアニメーションの最初のフレーム
	int moveLeftEndFrame;				// 左方向移動のアニメーションの最後のフレーム
	int attackUpStartFrame;				// 上方向攻撃のアニメーションの最初のフレーム
	int attackUpEndFrame;				// 上方向攻撃のアニメーションの最後のフレーム
	int attackRightStartFrame;			// 右方向攻撃のアニメーションの最初のフレーム
	int attackRightEndFrame;			// 右方向攻撃のアニメーションの最後のフレーム
	int attackDownStartFrame;			// 下方向攻撃のアニメーションの最初のフレーム
	int attackDownEndFrame;				// 下方向攻撃のアニメーションの最後のフレーム
	int attackLeftStartFrame;			// 左方向攻撃のアニメーションの最初のフレーム
	int attackLeftEndFrame;				// 左方向攻撃のアニメーションの最後のフレーム
public:
	// コンストラクタ
	Character();

	//==========================================================
	// 継承されたメンバー関数
	//==========================================================
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
	// 実行前：x、y = チェックしたい位置の画面上での座標
	virtual bool checkCanMove(float x, float y);	
	// 死亡時に呼び出す関数
	void dead();
	// 移動時のアップデート関数
	// アニメーション以外をアップデート
	void updateMoving(float frameTime);
	// 攻撃時のアップデート関数
	// 現状では通常のアップデート
	void updateAttacking(float frameTime);

	//==========================================================
	// setter
	//==========================================================
	// マップへのポインタをセットする関数
	void setMapPointer(Map& m) { map = &(m); }
	// 状態をセットする関数
	void setState(characterNS::STATE st) { state = st; }
	// 向いている方向をセットする
	// 実行前：dir = セットするキャラクターの向き
	void setDirection(characterNS::DIRECTION dir);

	//==========================================================
	// getter
	//==========================================================
	// 攻撃用の衝突判定を出現させるフラグを返す関数。攻撃状態に遷移した直後にtrueとなって、それ以外はfalse
	bool getAttackCollisionFlag() { return attackCollisionFlag; }
	// 向いている方向を返す関数
	characterNS::DIRECTION getDirection() { return direction; }
	// 状態を返す関数
	characterNS::STATE getState() { return state; }

	// 移動中へと状態を遷移
	void changeStateToMove();

};

#endif // !_CHARACTER_H
