//==========================================================
/// @file
/// @brief    castle.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "castle.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Castle::Castle() : Entity()
{
	spriteData.width = castleNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = castleNS::HEIGHT;
	spriteData.rect.bottom = castleNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = castleNS::WIDTH;
	spriteData.x = castleNS::X;					// ��ʏ�̈ʒu
	spriteData.y = castleNS::Y;
	cols = castleNS::TEXTURE_COLS;				// �e�N�X�`���̗�
	startFrame = castleNS::START_FRAME;			// �A�j���[�V�����̍ŏ��̃t���[��
	currentFrame = startFrame;					// ���݂̃t���[�����A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
	// Box�̏Փ˔���p
	edge.left = (LONG)(-castleNS::WIDTH / 1.8);
	edge.right = (LONG)(castleNS::WIDTH / 1.8);
	edge.top = (LONG)(-castleNS::HEIGHT / 1.8);
	edge.bottom = (LONG)(castleNS::HEIGHT / 1.8);
	collisionType = entityNS::BOX;

	death = false;								// ���S���Ă��Ȃ���Ԃ���X�^�[�g
}

//==========================================================
// �p�����[�^������
//==========================================================
void Castle::reset()
{
	death = false;								// ���S���Ă��Ȃ���ԂɃ��Z�b�g
	// �G���e�B�e�B�����Z�b�g
	Entity::reset();
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Castle::update(float frameTime)
{
	// ��A�N�e�B�u�Ȃ�A�������Ȃ�
	if (visible == false)
		return;


	// �_���[�W���󂯂Ă���Ȃ��莞�Ԃ��ƂɃA�j���[�V������_��
	if (isDamaged)
	{
		// �_���[�W���ɃA�j���[�V�����p�̃^�C�}�[�����Z
		damageTimer += frameTime;
		totalDamageTime += frameTime;
		// 0.15�b���Ƃɕ`��t���O��؂�ւ�
		if (damageTimer > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			damageTimer = 0.0f;
		}
		// DAMAGE_TIME�������_�ł�����A�_�ł��I��
		if (totalDamageTime > 1.0f)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// �G���e�B�e�B���X�V
	Entity::update(frameTime);
}

//==========================================================
// �_���[�W����
// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
//==========================================================
void Castle::damage(WEAPON weapon)
{
	// ��A�N�e�B�u�ȏꍇ�A�_���[�W�͎󂯂Ȃ�
	if (!active)
		return;

	// WEAPON�ɂ���ă_���[�W�𕪊�
	switch (weapon)
	{
	case FIRE:					// ��
		break;
	case BRAVE_ATTACK:			// �E�҂̍U��
		break;
	case BRAVE_SECOND_ATTACK:	// �E�҂̑��
		break;
	case ENEMY_ATTACK:			// �G���G�̍U��
		// ���_���[�W���󂯂�
		health -= enemyAttackDamage * damagePer;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case MIDBOSS_ATTACK:		// ���{�X�̍U��
		// ���_���[�W���󂯂�
		health -= midBossAttackDamage * damagePer;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	default:
		break;
	}
	// �̗͂�0�ȉ��ɂȂ����Ȃ�A���S
	if (health <= 0)
		death = true;
}