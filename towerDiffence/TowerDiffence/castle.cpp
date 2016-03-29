#include "castle.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Castle::Castle() : Entity()
{
	active = true;
	visible = true;
	spriteData.width = castleNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = castleNS::HEIGHT;
	spriteData.rect.bottom = castleNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = castleNS::WIDTH;
	spriteData.x = castleNS::X;
	spriteData.y = castleNS::Y;
	cols = castleNS::TEXTURE_COLS;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	// Box�̏Փ˔���p
	edge.left = -castleNS::WIDTH / 1.8;
	edge.right = castleNS::WIDTH / 1.8;
	edge.top = -castleNS::HEIGHT / 1.8;
	edge.bottom = castleNS::HEIGHT / 1.8;
	collisionType = entityNS::BOX;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Castle::reset()
{
	active = true;
	visible = true;
	health = 100;
	spriteData.x = castleNS::X;
	spriteData.y = castleNS::Y;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// ���`��
//==========================================================
void Castle::draw()
{
	if (drawFlag)
		Image::draw();	// ���`��
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Castle::update(float frameTime)
{
	if (visible == false)
		return;

	// �_���[�W���󂯂Ă���Ȃ��莞�Ԃ��ƂɃA�j���[�V������_��
	if (isDamaged)
	{
		timeCounter += frameTime;
		totalTimeCounter += frameTime;
		if (timeCounter > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			timeCounter = 0.0f;
		}
		if (totalTimeCounter > braveNS::DAMAGE_TIME)
		{
			timeCounter = 0.0f;
			totalTimeCounter = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}

	Entity::update(frameTime);
}

//==========================================================
// �_���[�W
//==========================================================
void Castle::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		break;
	case BRAVE_ATTACK:
		break;
	case BRAVE_SECOND_ATTACK:
		break;
	case ENEMY_ATTACK:
		health -= enemyNS::ATTACK_DAMAGE;
		break;
	default:
		break;
	}
	if (health <= 0)
		death = true;
	isDamaged = true;
}