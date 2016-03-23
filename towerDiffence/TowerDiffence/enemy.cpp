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
	radius = enemyNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	state = enemyNS::MOVE;
	direction = enemyNS::RIGHT;
	isDamaged = false;
	timeCounter = 0.0f;
	totalTimeCounter = 0.0f;
	drawFlag = true;
	distanceCounter = 0.0f;
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
		switch (goalDirection)
		{
		case enemyNS::LEFT:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_LEFT_START_FRAME;
				endFrame = enemyNS::MOVE_LEFT_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::RIGHT:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
				endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::UP:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_UP_START_FRAME;
				endFrame = enemyNS::MOVE_UP_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::DOWN:
			if (direction != goalDirection)
			{
				direction = goalDirection;
				startFrame = enemyNS::MOVE_DOWN_START_FRAME;
				endFrame = enemyNS::MOVE_DOWN_END_FRAME;
				currentFrame = startFrame;
				animTimer = 0.0f;
				setRect();
			}
			spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case enemyNS::NONE:
			break;
		}
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK:
		if (collisionVector.x > 0 && collisionVector.y < 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
			endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x > 0 && collisionVector.y > 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
			endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x < 0 && collisionVector.y < 0)
		{
			direction = enemyNS::LEFT;
			startFrame = enemyNS::MOVE_LEFT_START_FRAME;
			endFrame = enemyNS::MOVE_LEFT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (collisionVector.x < 0 && collisionVector.y > 0)
		{
			direction = enemyNS::RIGHT;
			startFrame = enemyNS::MOVE_LEFT_START_FRAME;
			endFrame = enemyNS::MOVE_LEFT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
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

//==========================================================
// �l�H�m�\
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
	if (nearPlayer)
	{
		distanceCounter = 0.0f;
		goalDirection = enemyNS::NONE;
		state = enemyNS::ATTACK;
		return;
	}
	// �v���C���̌��݈ʒu���擾
	int playerX = ent.getX();
	int playerY = ent.getY();
	int subX = playerX - getX();
	int subY = playerY - getY();
	
	// ����������32�s�N�Z���ړ����邲�Ƃɕ��������߂Ȃ���
	if (distanceCounter <=  0)
	{
		distanceCounter = 32.0f;
		state = enemyNS::MOVE;
		if (abs(subX) > abs(subY))
		{
			if (subX > 0)
				goalDirection = enemyNS::RIGHT;
			else
				goalDirection = enemyNS::LEFT;
			return;
		}
		else
		{
			if (subY > 0)
				goalDirection = enemyNS::DOWN;
			else
				goalDirection = enemyNS::UP;
			return;
		}
	}
}