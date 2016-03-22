#include "enemy.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Enemy::Enemy() : Entity()
{
	spriteData.width = enemyNS::WIDTH;			// �G���G�̃T�C�Y
	spriteData.height = enemyNS::HEIGHT;
	spriteData.x = enemyNS::X;					// ��ʏ�̈ʒu
	spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	currentFrame = startFrame;
	state = enemyNS::MOVE;
	direction = enemyNS::RIGHT;
	isDamaged = false;
	timeCounter = 0.0f;
	totalTimeCounter = 0.0f;
	drawFlag = true;
}

//==========================================================
// �G���G��������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//==========================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	setRect();
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// �G���G��`��
//==========================================================
void Enemy::draw()
{
	if (drawFlag)
		Image::draw();	// �G���G��`��
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Enemy::update(float frameTime)
{
	// ��ԑJ�ڑO�̏���
	switch (state)
	{
	case enemyNS::MOVE:
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK:
		break;
	case enemyNS::GAURD:
		break;
	default:
		break;
	}
	// ��ԑJ�ڌ�̏���
	switch (state)
	{
	case enemyNS::MOVE:
		updateMoving(frameTime);
		break;
	case enemyNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case enemyNS::GAURD:
		Entity::update(frameTime);
		break;
	default:
		Entity::update(frameTime);
		break;
	}

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
		if (totalTimeCounter > enemyNS::DAMAGE_TIME)
		{
			timeCounter = 0.0f;
			totalTimeCounter = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}

	spriteData.x += frameTime * velocity.x;     // �L������X�����ɓ�����
	spriteData.y += frameTime * velocity.y;     // �L������Y�����ɓ�����
}

//==========================================================
// �ړ����̃A�b�v�f�[�g�֐�
//==========================================================
void Enemy::updateMoving(float frameTime)
{
	// �A�j���[�V�����̃A�b�v�f�[�g�͒P�Ƃōs����̂ł���ȊO���A�b�v�f�[�g
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// �U�����̃A�b�v�f�[�g�֐�
//==========================================================
void Enemy::updateAttacking(float frameTime)
{
	Entity::update(frameTime);
}

//==========================================================
// �_���[�W
//==========================================================
void Enemy::damage(WEAPON weapon)
{
	isDamaged = true;
}