//==========================================================
/// @file
/// @brief    barricade.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#include "barricade.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Barricade::Barricade() : Entity()
{
	spriteData.width = barricadeNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = barricadeNS::HEIGHT;
	spriteData.rect.bottom = barricadeNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = barricadeNS::WIDTH;
	cols = barricadeNS::TEXTURE_COLS;				// �e�N�X�`���̗�
	startFrame = barricadeNS::START_FRAME;			// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = barricadeNS::END_FRAME;				// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	// Box�̏Փ˔���p
	edge.left = (LONG)(-barricadeNS::WIDTH / 2.0);
	edge.right = (LONG)(barricadeNS::WIDTH / 2.0);
	edge.top = (LONG)(-barricadeNS::HEIGHT / 2.0);
	edge.bottom = (LONG)(barricadeNS::HEIGHT / 2.0);
	collisionType = entityNS::BOX;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Barricade::update(float frameTime)
{
	// ��A�N�e�B�u�ȏꍇ�A�������Ȃ�
	if (active == false)
		return;

	// �c��̗͂��ƂɁA�A�j���[�V�����𕪊�
	// ���E���c��̗͂��㉺�����ꍇ�A�A�j���[�V������J�ڂ�����
	if ((currentFrame == barricadeNS::START_FRAME && health < 66) || (currentFrame == barricadeNS::START_FRAME + 1 && health < 33))
	{
		// �̗͂����E����������ꍇ�A�A�j���[�V������i�߂�
		setCurrentFrame(currentFrame + 1);
	}
	if ((currentFrame == barricadeNS::END_FRAME && health >= 33) || (currentFrame == barricadeNS::START_FRAME + 1 && health >= 66))
	{
		// �̗͂����E���������ꍇ�A�A�j���[�V������߂�
		setCurrentFrame(currentFrame - 1);
	}
	// �U�����q�b�g�����Ƃ��̃A�j���[�V�������X�V
	hitEffect.update(frameTime);
	// �A�j���[�V�����ȊO���X�V
	updateWithoutImage(frameTime);
	
}

//==========================================================
// �_���[�W����
// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
//==========================================================
void Barricade::damage(WEAPON weapon)
{
	// ��A�N�e�B�u�ȏꍇ�A�_���[�W�͎󂯂Ȃ�
	if (!active)
		return;
	
	// WEAPON�ɂ���ă_���[�W�𕪊�
	switch (weapon)
	{
	case FIRE:					// ���i�v���C���[�̕K�E�Z�j
		// �ω��Ȃ�
		break;
	case BRAVE_ATTACK:			// �v���C���[�̍U��
	case BRAVE_SECOND_ATTACK:	// �v���C���[�̍U��
		// �o���P�[�h����
		health += 20;
		// MAX100�𒴂����ꍇ��100�ɂ���
		if (health > 100)
		{
			health = 100;
		}
		// �U�����q�b�g�����Ƃ��̃A�j���[�V�����𔭓�
		hitEffect.hit(getCenterX(), getCenterY());
		break;
	case ENEMY_ATTACK:
		// �o���P�[�h�Ƀ_���[�W
		health -= 10 * damagePer;
		// �U�����q�b�g�����Ƃ��̃A�j���[�V�����𔭓�
		hitEffect.hit(getCenterX(), getCenterY());
		// �c��̗͂��Ȃ��Ȃ����ꍇ�A
		if (health <= 0)
		{
			// ���g�ƍU�����q�b�g�����Ƃ��̃A�j���[�V�������A�N�e�B�u�ɂ���
			visible = false;
			active = false;
			hitEffect.setVisible(false);
		}
		break;
	case MIDBOSS_ATTACK:
		// �o���P�[�h�Ƀ_���[�W
		health -= 20 * damagePer;
		// �U�����q�b�g�����Ƃ��̃A�j���[�V�����𔭓�
		hitEffect.hit(getCenterX(), getCenterY());
		// �c��̗͂��Ȃ��Ȃ����ꍇ�A
		if (health <= 0)
		{
			// ���g�ƍU�����q�b�g�����Ƃ��̃A�j���[�V�������A�N�e�B�u�ɂ���
			visible = false;
			active = false;
			hitEffect.setVisible(false);
		}
		break;
	default:
		break;
	}
}