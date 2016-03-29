#include "midBoss.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
MidBoss::MidBoss() : Enemy()
{
	// �����̕����͉E
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
}

//==========================================================
// �p�����[�^������
//==========================================================
void MidBoss::reset()
{
	// �����̕����͉E
	startFrame = midBossNS::MOVE_RIGHT_START_FRAME;
	endFrame = midBossNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	Enemy::reset();
}

//==========================================================
// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
//==========================================================
void MidBoss::changeAttack(VECTOR2 &collisionVector)
{
	// �U�����O���[�h�Ƀ`�F���W
	loop = false;
	distanceCounter = 0.0f;
	float yPerx = (float)collisionVector.y / collisionVector.x;
	float hPerw = (float)spriteData.height / spriteData.width;
	if (collisionVector.x > 0)
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::RIGHT;
			changeDirection(midBossNS::MOVE_RIGHT_START_FRAME, midBossNS::MOVE_RIGHT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::UP;
			changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::DOWN;
			changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
		}
	}
	else
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::LEFT;
			changeDirection(midBossNS::MOVE_LEFT_START_FRAME, midBossNS::MOVE_LEFT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::DOWN;
			changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::UP;
			changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
		}
	}
	goalDirection = characterNS::NONE;
	state = enemyNS::PRE_ATTACK;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = midBossNS::ATTACK_LEFT_START_FRAME;
		endFrame = midBossNS::ATTACK_LEFT_END_FRAME;
		break;
	case characterNS::RIGHT:
		startFrame = midBossNS::ATTACK_RIGHT_START_FRAME;
		endFrame = midBossNS::ATTACK_RIGHT_END_FRAME;
		break;
	case characterNS::UP:
		startFrame = midBossNS::ATTACK_UP_START_FRAME;
		endFrame = midBossNS::ATTACK_UP_END_FRAME;
		break;
	case characterNS::DOWN:
		startFrame = midBossNS::ATTACK_DOWN_START_FRAME;
		endFrame = midBossNS::ATTACK_DOWN_END_FRAME;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void MidBoss::update(float frameTime)
{
	// ��A�N�e�B�u�Ȃ牽�����Ȃ�
	if (!active)
		return;
	// �U�����̃t���O���I�t
	attackCollisionFlag = false;
	// ��Ԃ��Ƃɏ����𕪊�
	switch (state)
	{
	case enemyNS::MOVE_CASTLE:		// ��ւ̈ړ�
	case enemyNS::MOVE_BARRICADE:	// �o���P�[�h�ւ̈ړ�
									// �ڕW�ւ̌����ɉ����Ď����̌������C��
									// ������ύX����ꍇ�̓A�j���[�V���������Z�b�g
		switch (goalDirection)
		{
		case characterNS::LEFT:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_LEFT_START_FRAME, midBossNS::MOVE_LEFT_END_FRAME);
			}
			// �ړ��\��������
			if (checkCanMove(spriteData.x - enemyNS::MOVE_SPEED * frameTime, spriteData.y)) {
				// ���Ɉړ�
				spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::RIGHT:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_RIGHT_START_FRAME, midBossNS::MOVE_RIGHT_END_FRAME);
			}
			// �ړ��\��������
			if (checkCanMove(spriteData.x + enemyNS::MOVE_SPEED * frameTime, spriteData.y)) {
				// �E�Ɉړ�
				spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::UP:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_UP_START_FRAME, midBossNS::MOVE_UP_END_FRAME);
			}
			// �ړ��\��������
			if (checkCanMove(spriteData.x, spriteData.y - enemyNS::MOVE_SPEED * frameTime)) {
				// ��Ɉړ�
				spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::DOWN:
			if (direction != goalDirection)
			{
				changeDirection(midBossNS::MOVE_DOWN_START_FRAME, midBossNS::MOVE_DOWN_END_FRAME);
			}
			// �ړ��\��������
			if (checkCanMove(spriteData.x, spriteData.y + enemyNS::MOVE_SPEED * frameTime)) {
				// ���Ɉړ�
				spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			}
			distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::NONE:
			break;
		}
		// �U������ł͂Ȃ��͂��Ȃ̂Ńt���O���I�t
		isAttacked = false;
		// �摜�̂݃A�b�v�f�[�g
		Entity::updateOnlyImage(frameTime);
		break;
	case enemyNS::ATTACK_BRAVE:
	case enemyNS::ATTACK_CASTLE:
	case enemyNS::ATTACK_BARRICADE:
		// �A�j���[�V�������I�����Ă�����U���I��
		// ��Ԃ��ړ����ɖ߂�
		if (animComplete)
		{
			isAttacked = true;
			mode = imageNS::HORIZONTAL;
			direction = oldDirection;
			state = enemyNS::MOVE_CASTLE;
			loop = true;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case enemyNS::PRE_ATTACK:
		// �^�C�}�[�����Z�A��莞�Ԃ𒴂�����U���Ɉڂ�
		attackTimer += frameTime;
		if (isAttacked && attackTimer > enemyNS::CONTINUE_ATTACK_TIME)
		{
			attackTimer = 0.0f;
			state = attackState;
			attackCollisionFlag = true;
		}
		else if (!isAttacked && attackTimer > enemyNS::ATTACK_TIME)
		{
			attackTimer = 0.0f;
			state = attackState;
			attackCollisionFlag = true;
		}
		break;
	case enemyNS::GAURD:
		break;
	default:
		break;
	}

	/*
	// ��ԑJ�ڑO�̏���
	switch (state)
	{
	case enemyNS::MOVE:		// �ړ���
	// �ڕW�ւ̌����ɉ����Ď����̌������C��
	// ������ύX����ꍇ�̓A�j���[�V���������Z�b�g
	switch (goalDirection)
	{
	case enemyNS::LEFT:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_LEFT_START_FRAME, enemyNS::MOVE_LEFT_END_FRAME);
	}
	// �ړ��\��������
	if (checkCanMove(spriteData.x - enemyNS::MOVE_SPEED * frameTime, spriteData.y, map)) {
	// ���Ɉړ�
	spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::RIGHT:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_RIGHT_START_FRAME, enemyNS::MOVE_RIGHT_END_FRAME);
	}
	// �ړ��\��������
	if (checkCanMove(spriteData.x + enemyNS::MOVE_SPEED * frameTime, spriteData.y, map)) {
	// �E�Ɉړ�
	spriteData.x += enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::UP:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_UP_START_FRAME, enemyNS::MOVE_UP_END_FRAME);
	}
	// �ړ��\��������
	if (checkCanMove(spriteData.x, spriteData.y - enemyNS::MOVE_SPEED * frameTime, map)) {
	// ��Ɉړ�
	spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::DOWN:
	if (direction != goalDirection)
	{
	changeDirection(enemyNS::MOVE_DOWN_START_FRAME, enemyNS::MOVE_DOWN_END_FRAME);
	}
	// �ړ��\��������
	if (checkCanMove(spriteData.x, spriteData.y + enemyNS::MOVE_SPEED * frameTime, map)) {
	// ���Ɉړ�
	spriteData.y += enemyNS::MOVE_SPEED * frameTime;
	}
	distanceCounter -= enemyNS::MOVE_SPEED * frameTime;
	break;
	case enemyNS::NONE:
	break;
	}
	// �U������ł͂Ȃ��͂��Ȃ̂Ńt���O���I�t
	isAttacked = false;
	// �摜�̂݃A�b�v�f�[�g
	Entity::updateOnlyImage(frameTime);
	break;
	case enemyNS::ATTACK:	// �U����
	// �A�j���[�V�������I�����Ă�����U���I��
	// ��Ԃ��ړ����ɖ߂�
	if (animComplete)
	{
	isAttacked = true;
	mode = imageNS::HORIZONTAL;
	direction = oldDirection;
	state = enemyNS::ATTACK;
	loop = true;
	startFrame = oldStartFrame;
	endFrame = oldEndFrame;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
	Entity::updateOnlyImage(frameTime);
	}
	break;
	case enemyNS::PRE_ATTACK:
	// �^�C�}�[�����Z�A��莞�Ԃ𒴂�����U���Ɉڂ�
	attackTimer += frameTime;
	if (isAttacked && attackTimer > enemyNS::CONTINUE_ATTACK_TIME)
	{
	attackTimer = 0.0f;
	state = enemyNS::ATTACK;
	attackCollisionFlag = true;
	}
	else if (!isAttacked && attackTimer > enemyNS::ATTACK_TIME)
	{
	attackTimer = 0.0f;
	state = enemyNS::ATTACK;
	attackCollisionFlag = true;
	}
	break;
	case enemyNS::GAURD:
	break;
	default:
	break;
	}
	*/

	// ��ԑJ�ڌ�̏���
	switch (state)
	{
	case enemyNS::MOVE_CASTLE:
	case enemyNS::MOVE_BARRICADE:
		updateMoving(frameTime);
		break;
	case enemyNS::ATTACK_BRAVE:
	case enemyNS::ATTACK_CASTLE:
	case enemyNS::ATTACK_BARRICADE:
		updateAttacking(frameTime);
		break;
	case enemyNS::PRE_ATTACK:
		Entity::updateWithoutImage(frameTime);
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
		damageTimer += frameTime;
		totalDamageTime += frameTime;
		if (damageTimer > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			damageTimer = 0.0f;
		}
		if (totalDamageTime > enemyNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// �ړ��\��������
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y))
	{
		spriteData.x += frameTime * velocity.x;     // �L������X�����ɓ�����
		spriteData.y += frameTime * velocity.y;     // �L������Y�����ɓ�����
	}
	// ��ʂ̒[�܂ŗ�����i�߂Ȃ�
	if (spriteData.x > GAME_WIDTH - enemyNS::WIDTH * getScale())	// ��ʉE�[�𒴂�����
		spriteData.x = GAME_WIDTH - enemyNS::WIDTH * getScale();	// ��ʉE�[�Ɉړ�
	if (spriteData.x < 0)											// ��ʍ��[�𒴂�����
		spriteData.x = 0;											// ��ʍ��[�Ɉړ�
	if (spriteData.y < rectNS::HEIGHT - 10)								// ��ʏ�[�𒴂�����
		spriteData.y = rectNS::HEIGHT - 10;								// ��ʏ�[�Ɉړ�
	if (spriteData.y > GAME_HEIGHT - enemyNS::HEIGHT * getScale())  // ��ʉ��[�𒴂�����
		spriteData.y = GAME_HEIGHT - enemyNS::HEIGHT * getScale();	// ��ʉ��[�Ɉړ�

}

//==========================================================
// �_���[�W
//==========================================================
void MidBoss::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		health -= braveNS::FIRE_DAMAGE / 3;
		break;
	case BRAVE_ATTACK:
		health -= braveNS::ATTACK_DAMAGE / 3;
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