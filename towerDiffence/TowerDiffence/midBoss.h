#ifndef _MID_BOSS_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _MID_BOSS_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"

namespace midBossNS
{
	const int MOVE_UP_START_FRAME = 0;				// 上方向移動のアニメーションはフレーム0から開始
	const int MOVE_UP_END_FRAME = 2;				// 上方向移動のアニメーションフレームは0、1、2
	const int MOVE_RIGHT_START_FRAME = 12;			// 右方向移動のアニメーションはフレーム12から開始
	const int MOVE_RIGHT_END_FRAME = 14;			// 右方向移動のアニメーションフレームは12、13、14
	const int MOVE_DOWN_START_FRAME = 24;			// 下方向移動のアニメーションはフレーム24から開始
	const int MOVE_DOWN_END_FRAME = 26;				// 下方向移動のアニメーションフレームは24、25、26
	const int MOVE_LEFT_START_FRAME = 36;			// 左方向移動のアニメーションはフレーム36から開始
	const int MOVE_LEFT_END_FRAME = 38;				// 左方向移動のアニメーションフレームは36、37、38
	const int ATTACK_DOWN_START_FRAME = 96;			// 上方向攻撃のアニメーションはフレーム96から開始
	const int ATTACK_DOWN_END_FRAME = 98;		// 上方向攻撃にアニメーションフレームは28、29、175、184
	const int ATTACK_LEFT_START_FRAME = 99;		// 右方向攻撃のアニメーションはフレーム148から開始
	const int ATTACK_LEFT_END_FRAME = 101;	// 右方向攻撃のアニメーションフレームは148、161、173、182
	const int ATTACK_UP_START_FRAME = 102;		// 下方向攻撃のアニメーションはフレーム103から開始
	const int ATTACK_UP_END_FRAME = 104;		// 下方向攻撃のアニメーションフレームは103、115、127、139
	const int ATTACK_RIGHT_START_FRAME = 105;		// 左方向攻撃のアニメーションはフレーム100から開始
	const int ATTACK_RIGHT_END_FRAME = 107;		// 左方向攻撃のアニメーションフレームは100、112、124、136
	const float ATTACK_TIME = 1.5f;					// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	const float CONTINUE_ATTACK_TIME = 2.0f;		// 連続で攻撃する場合の溜め時間	
	const float ATTACK_DAMAGE = 15.0f;
}

// MidBossクラス
class MidBoss : public Enemy
{
private:
	float distanceCounter;
public:
	// コンストラクタ
	MidBoss();

	//==========================================================
	// 継承されたメンバー関数
	//==========================================================
	// Update
	// 通常、フレームごとに1回呼び出す
	// キャラクターにダメージを与える関数
	void damage(WEAPON);
};

#endif // !_MID_BOSS_H
