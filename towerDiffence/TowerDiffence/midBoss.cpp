#include "midBoss.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
MidBoss::MidBoss() : Enemy()
{
	// 初期の方向は右
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	attackAnimationMode = imageNS::HORIZONTAL;
	moveUpStartFrame = midBossNS::MOVE_UP_START_FRAME;
	moveUpEndFrame = midBossNS::MOVE_UP_END_FRAME;
	moveRightStartFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	moveRightEndFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	moveDownStartFrame = midBossNS::MOVE_DOWN_START_FRAME;
	moveDownEndFrame = midBossNS::MOVE_DOWN_END_FRAME;
	moveLeftStartFrame = midBossNS::MOVE_LEFT_START_FRAME;
	moveLeftEndFrame = midBossNS::MOVE_LEFT_END_FRAME;
	attackUpStartFrame = midBossNS::ATTACK_UP_START_FRAME;
	attackUpEndFrame = midBossNS::ATTACK_UP_END_FRAME;
	attackRightStartFrame = midBossNS::ATTACK_RIGHT_START_FRAME;
	attackRightEndFrame = midBossNS::ATTACK_RIGHT_END_FRAME;
	attackDownStartFrame = midBossNS::ATTACK_DOWN_START_FRAME;
	attackDownEndFrame = midBossNS::ATTACK_DOWN_END_FRAME;
	attackLeftStartFrame = midBossNS::ATTACK_LEFT_START_FRAME;
	attackLeftEndFrame = midBossNS::ATTACK_LEFT_END_FRAME;
	attackTime = midBossNS::ATTACK_TIME;
	continueAttackTime = midBossNS::CONTINUE_ATTACK_TIME;
}

//==========================================================
// ダメージ
//==========================================================
void MidBoss::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		health -= braveFireDamage / 3;
		break;
	case BRAVE_ATTACK:
		health -= braveAttackDamage / 3;
		break;
	case BRAVE_SECOND_ATTACK:
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	if (health <= 0)
		dead();
	isDamaged = true;
}