//==========================================================
/// @file
/// @brief    midBoss.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "midBoss.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
MidBoss::MidBoss() : Enemy()
{
	// �����̕����͉E
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;				// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;					// �A�j���[�V�����̍Ō�̃t���[��
	oldStartFrame = startFrame;									// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����̍ŏ��̃t���[��
	oldEndFrame = endFrame;										// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;									// ���݂̃t���[�����A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
	attackAnimationMode = imageNS::HORIZONTAL;					// �U�����̃A�j���[�V�����̑J�ڃ��[�h�i�����A�����j
	moveUpStartFrame = midBossNS::MOVE_UP_START_FRAME;			// ������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveUpEndFrame = midBossNS::MOVE_UP_END_FRAME;				// ������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveRightStartFrame = midBossNS::MOVE_RIGHT_START_FRAME;	// �E�����ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveRightEndFrame = midBossNS::MOVE_RIGHT_END_FRAME;		// �E�����ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveDownStartFrame = midBossNS::MOVE_DOWN_START_FRAME;		// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveDownEndFrame = midBossNS::MOVE_DOWN_END_FRAME;			// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveLeftStartFrame = midBossNS::MOVE_LEFT_START_FRAME;		// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveLeftEndFrame = midBossNS::MOVE_LEFT_END_FRAME;			// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	attackUpStartFrame = midBossNS::ATTACK_UP_START_FRAME;		// ������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackUpEndFrame = midBossNS::ATTACK_UP_END_FRAME;			// ������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackRightStartFrame = midBossNS::ATTACK_RIGHT_START_FRAME;// �E�����U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackRightEndFrame = midBossNS::ATTACK_RIGHT_END_FRAME;	// �E�����U���̃A�j���[�V�����̍Ō�̃t���[��
	attackDownStartFrame = midBossNS::ATTACK_DOWN_START_FRAME;	// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackDownEndFrame = midBossNS::ATTACK_DOWN_END_FRAME;		// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackLeftStartFrame = midBossNS::ATTACK_LEFT_START_FRAME;	// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackLeftEndFrame = midBossNS::ATTACK_LEFT_END_FRAME;		// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackTime = midBossNS::ATTACK_TIME;						// �v���C���[�ɗאڂ��Ă���U���Ɉڂ�܂ł̗��ߎ���
	continueAttackTime = midBossNS::CONTINUE_ATTACK_TIME;		// �A���ōU������ꍇ�̗��ߎ���
}

//==========================================================
// �_���[�W����
// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
//==========================================================
void MidBoss::damage(WEAPON weapon)
{
	// �G�̃^�C�v�ɂ���āA�󂯂�_���[�W�̊�����ω�
	if (type == enemyNS::NORMAL)
		setDamagePer(1.0f);
	else if (type == enemyNS::RED)
		setDamagePer(0.8f);
	else if (type == enemyNS::BLUE)
		setDamagePer(0.9f);

	// WEAPON�ɂ���ă_���[�W�𕪊�
	switch (weapon)
	{
	case FIRE:					// ��
		// ���_���[�W���󂯂�
		health -= braveFireDamage  * damagePer / 3;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case BRAVE_ATTACK:			// �E�҂̍U��
		// ���_���[�W���󂯂�
		health -= braveAttackDamage * damagePer / 3;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case BRAVE_SECOND_ATTACK:	// �E�҂̑��
		// ���_���[�W���󂯂�
		health -= braveAttackDamage * damagePer / 3;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case ENEMY_ATTACK:
		break;
	default:
		break;
	}
	// �̗͂�0�ȉ��ɂȂ�����A
	if (health <= 0)
	{
		isDamaged = false;
		// ��Ԃ����S���ɑJ��
		state = characterNS::DEATH;
		// �K���ȕ����փW�����v���Ȃ����ʊO�ւƗ����Ă���
		if (rand() % 2 == 0)
			velocity.x = 32.0f * 2.0;
		else
			velocity.x = -32.0f * 2.0;
		velocity.y = -sqrt(2 * 2000.0f * 96 * 2);
		map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
	}
}