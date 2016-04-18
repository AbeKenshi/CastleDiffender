//==========================================================
/// @file
/// @brief    midBoss.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "midBoss.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
MidBoss::MidBoss() : Enemy()
{
	// 初期の方向は右
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;				// アニメーションの最初のフレーム
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;					// アニメーションの最後のフレーム
	oldStartFrame = startFrame;									// 攻撃アニメーション終了後に戻るべきアニメーションの最初のフレーム
	oldEndFrame = endFrame;										// 攻撃アニメーション終了後に戻るべきアニメーションの最後のフレーム
	currentFrame = startFrame;									// 現在のフレームをアニメーションの最初のフレームにセット
	attackAnimationMode = imageNS::HORIZONTAL;					// 攻撃時のアニメーションの遷移モード（水平、垂直）
	moveUpStartFrame = midBossNS::MOVE_UP_START_FRAME;			// 上方向移動のアニメーションの最初のフレーム
	moveUpEndFrame = midBossNS::MOVE_UP_END_FRAME;				// 上方向移動のアニメーションの最後のフレーム
	moveRightStartFrame = midBossNS::MOVE_RIGHT_START_FRAME;	// 右方向移動のアニメーションの最初のフレーム
	moveRightEndFrame = midBossNS::MOVE_RIGHT_END_FRAME;		// 右方向移動のアニメーションの最後のフレーム
	moveDownStartFrame = midBossNS::MOVE_DOWN_START_FRAME;		// 下方向移動のアニメーションの最初のフレーム
	moveDownEndFrame = midBossNS::MOVE_DOWN_END_FRAME;			// 下方向移動のアニメーションの最後のフレーム
	moveLeftStartFrame = midBossNS::MOVE_LEFT_START_FRAME;		// 左方向移動のアニメーションの最初のフレーム
	moveLeftEndFrame = midBossNS::MOVE_LEFT_END_FRAME;			// 左方向移動のアニメーションの最後のフレーム
	attackUpStartFrame = midBossNS::ATTACK_UP_START_FRAME;		// 上方向攻撃のアニメーションの最初のフレーム
	attackUpEndFrame = midBossNS::ATTACK_UP_END_FRAME;			// 上方向攻撃のアニメーションの最後のフレーム
	attackRightStartFrame = midBossNS::ATTACK_RIGHT_START_FRAME;// 右方向攻撃のアニメーションの最初のフレーム
	attackRightEndFrame = midBossNS::ATTACK_RIGHT_END_FRAME;	// 右方向攻撃のアニメーションの最後のフレーム
	attackDownStartFrame = midBossNS::ATTACK_DOWN_START_FRAME;	// 下方向攻撃のアニメーションの最初のフレーム
	attackDownEndFrame = midBossNS::ATTACK_DOWN_END_FRAME;		// 下方向攻撃のアニメーションの最後のフレーム
	attackLeftStartFrame = midBossNS::ATTACK_LEFT_START_FRAME;	// 左方向攻撃のアニメーションの最初のフレーム
	attackLeftEndFrame = midBossNS::ATTACK_LEFT_END_FRAME;		// 左方向攻撃のアニメーションの最後のフレーム
	attackTime = midBossNS::ATTACK_TIME;						// プレイヤーに隣接してから攻撃に移るまでの溜め時間
	continueAttackTime = midBossNS::CONTINUE_ATTACK_TIME;		// 連続で攻撃する場合の溜め時間
}

//==========================================================
// ダメージ処理
// WEAPONの種類によって受けるダメージが分岐
//==========================================================
void MidBoss::damage(WEAPON weapon)
{
	// 敵のタイプによって、受けるダメージの割合を変化
	if (type == enemyNS::NORMAL)
		setDamagePer(1.0f);
	else if (type == enemyNS::RED)
		setDamagePer(0.8f);
	else if (type == enemyNS::BLUE)
		setDamagePer(0.9f);

	// WEAPONによってダメージを分岐
	switch (weapon)
	{
	case FIRE:					// 炎
		// 一定ダメージを受ける
		health -= braveFireDamage  * damagePer / 3;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case BRAVE_ATTACK:			// 勇者の攻撃
		// 一定ダメージを受ける
		health -= braveAttackDamage * damagePer / 3;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case BRAVE_SECOND_ATTACK:	// 勇者の第二撃
		// 一定ダメージを受ける
		health -= braveAttackDamage * damagePer / 3;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	// 体力が0以下になったら、
	if (health <= 0)
	{
		isDamaged = false;
		// 状態を死亡時に遷移
		state = characterNS::DEATH;
		// 適当な方向へジャンプしながら画面外へと落ちていく
		if (rand() % 2 == 0)
			velocity.x = 32.0f * 2.0;
		else
			velocity.x = -32.0f * 2.0;
		velocity.y = -sqrt(2 * 2000.0f * 96 * 2);
		map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
	}
}