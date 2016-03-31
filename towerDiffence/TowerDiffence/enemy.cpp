#include "enemy.h"
#include <iostream>
//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Enemy::Enemy() : Character()
{
	spriteData.width = enemyNS::WIDTH;			// �G���G�̃T�C�Y
	spriteData.height = enemyNS::HEIGHT;
	// spriteData.x = enemyNS::X;					// ��ʏ�̈ʒu
	// spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	// �����̕����͉E
	goalDirection = characterNS::RIGHT;
	oldDirection = direction;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	// Box�̏Փ˔���p
	edge.left = -enemyNS::WIDTH / 2.0;
	edge.right = enemyNS::WIDTH / 2.0;
	edge.top = -enemyNS::HEIGHT / 8.0;
	edge.bottom = enemyNS::HEIGHT / 2.0;
	// �����̏�Ԃ͏�Ɍ������Ĉړ�
	stateDeteil = enemyNS::MOVE_CASTLE;
	goalPos.x = castleNS::X + castleNS::WIDTH / 2;
	goalPos.y = castleNS::Y + castleNS::HEIGHT / 2;
	// �͈͓��ɂ͂��Ȃ���Ԃ���X�^�[�g
	inCertainRange = false;
	canMakeDecesionMove = false;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Enemy::reset()
{
	Character::reset();
	// spriteData.x = enemyNS::X;					// ��ʏ�̈ʒu
	// spriteData.y = enemyNS::Y;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	// �����̕����͉E
	oldDirection = direction;
	goalDirection = characterNS::RIGHT;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	// �����̏�Ԃ͈ړ�
	stateDeteil = enemyNS::MOVE_CASTLE;
	goalPos.x = castleNS::X + castleNS::WIDTH / 2;
	goalPos.y = castleNS::Y + castleNS::HEIGHT / 2;
	// �͈͓��ɂ͂��Ȃ���Ԃ���X�^�[�g
	inCertainRange = false;
	canMakeDecesionMove = false;
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Enemy::update(float frameTime)
{
	// ��A�N�e�B�u�Ȃ牽�����Ȃ�
	if (!active)
		return;
	// �U�����̓����蔻����o���t���O���I�t
	attackCollisionFlag = false;
	canMakeDecesionMove = false;

	// �e��Ԃɉ����ď����𕪊�
	switch (state)
	{
	case characterNS::MOVE:	// �ړ����Ȃ�ڕW�̕����ɂ܂������i��
		// �ڕW�̕����Ɍ������Đi��
		switch (goalDirection)
		{
		case characterNS::LEFT:
			// ���Ɉړ�
			spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::RIGHT:
			// �E�Ɉړ�
			spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::UP:
			// ��Ɉړ�
			spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::DOWN:
			// ���Ɉړ�
			spriteData.y += enemyNS::MOVE_SPEED * frameTime;
			break;
		}
		// �U������ł͂Ȃ��͂��Ȃ̂Ńt���O���I�t
		isAttacked = false;
		// �摜�̂݃A�b�v�f�[�g
		Entity::updateOnlyImage(frameTime);
		if (isCenterOfTile())	// �^�C���̒����ɗ�����}�b�v���X�V
		{
			// �}�b�v�Ɏ����̈ʒu��ǉ�
			map->updateMapCol(tileY * mapNS::TEXTURE_SIZE, tileX * mapNS::TEXTURE_SIZE, 3);
			canMakeDecesionMove = true;
		}
		break;
	case characterNS::ATTACK:
		// �A�j���[�V�������I�����Ă�����U���I��
		// ��Ԃ��ړ����ɖ߂�
		if (animComplete)
		{
			canMakeDecesionMove = true;
			isAttacked = true;
			mode = imageNS::HORIZONTAL;
			direction = oldDirection;
			stateDeteil = enemyNS::MOVE_CASTLE;
			state = characterNS::MOVE;
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
	case characterNS::PRE_ATTACK:
		// �^�C�}�[�����Z�A��莞�Ԃ𒴂�����U���Ɉڂ�
		attackTimer += frameTime;
		if (isAttacked && attackTimer > enemyNS::CONTINUE_ATTACK_TIME)
		{
			attackTimer = 0.0f;
			stateDeteil = attackState;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		else if (!isAttacked && attackTimer > enemyNS::ATTACK_TIME)
		{
			attackTimer = 0.0f;
			stateDeteil = attackState;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		break;
	case characterNS::WAIT:
		canMakeDecesionMove = true;
		break;
	default:
		break;
	}

	// Entity�̃A�b�v�f�[�g�Ɋւ��鏈��
	switch (state)
	{
	case characterNS::MOVE:
		updateMoving(frameTime);
		break;
	case characterNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case characterNS::PRE_ATTACK:
		Entity::updateWithoutImage(frameTime);
		break;
	case characterNS::WAIT:
		Entity::updateWithoutImage(frameTime);
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
void Enemy::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case FIRE:
		health -= braveNS::FIRE_DAMAGE;
		break;
	case BRAVE_ATTACK:
		health -= braveNS::ATTACK_DAMAGE;
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

//==========================================================
// �l�H�m�\
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
	// �U�����Ȃ�΍s���I���͍s��Ȃ�
	if (state == characterNS::ATTACK)
	{
		return;
	}
}

//==========================================================
// 
//==========================================================
void Enemy::changeDirection(int strF, int endF)
{
	direction = goalDirection;
	startFrame = strF;
	endFrame = endF;
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
}

//==========================================================
// �v���C���[�Ƃ̋��������͈͓��Ȃ�true�A����ȊO��false��Ԃ�
//==========================================================
bool Enemy::checkDistancePlayer(int px, int py)
{
	int subX = px - getX();
	int subY = py - getY();

	int dist = (int)sqrt(subX * subX + subY * subY);

	if (dist < 100) return true;
	else return false;
}

//==========================================================
// ��ԋ߂��̃o���P�[�h�̈ʒu��Ԃ��֐�
// �o���P�[�h�����݂��Ȃ��ꍇ�̓v���C���[�̈ʒu��Ԃ�
//==========================================================
VECTOR2 Enemy::searchNearBarricade(Entity &ent)
{

	// �ŏ��̋�����
	int minX = 0, minY = 0;
	// �ŏ��̃o���P�[�h�̍��W
	int minBariPosiX = 0, minBariPosiY = 0;
	// �A�N�e�B�u�ȃo���P�[�h�̐��𐔂���p
	int count = 0;

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		// �����o���P�[�hn���A�N�e�B�u�Ȃ�
		if (barricades[i].getActive())
		{
			// �T��1�ڂ̏ꍇ
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getX() - getX());
				minY = (int)abs(barricades[i].getY() - getY());
				minBariPosiX = (int)barricades[i].getX();
				minBariPosiY = (int)barricades[i].getY();
			}
			else // 2�ڈȍ~
			{
				// �����ŏ��l���X�V������
				if ((barricades[i].getX() - getX())*(barricades[i].getX() - getX()) +
					(barricades[i].getY() - getY())*(barricades[i].getY() - getY()) <
					minX * minX + minY * minY)
				{
					// �V���ɑ��
					minX = (int)abs(barricades[i].getX() - getX());
					minY = (int)abs(barricades[i].getY() - getY());
					minBariPosiX = (int)barricades[i].getX();
					minBariPosiY = (int)barricades[i].getY();
				}
			}
			// �J�E���g�𑝂₷
			count++;
		}
	}

	// �x�N�^�[2�N���X����
	VECTOR2 vec;

	// �����o���P�[�h��1�ȏ㑶�݂�����
	if (count > 0) {
		// �ŏ��l����
		vec.x = minBariPosiX;
		vec.y = minBariPosiY;
	}
	else {
		// �v���C���[�̈ʒu����
		vec.x = ent.getX();
		vec.y = ent.getY();
	}

	// �x�N�g���Ԃ�
	return vec;
}

//==========================================================
// ��ԋ߂��̃o���P�[�h�̃C���f�b�N�X��Ԃ��֐�
//==========================================================
int Enemy::searchNearBarricadeIndex()
{
	// �ŏ��̋�����
	int minX = 0, minY = 0;
	// �ŏ��̋����̃C���f�b�N�X
	int minIndex = 0;
	// �A�N�e�B�u�ȃo���P�[�h�̐��𐔂���p
	int count = 0;

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		// �����o���P�[�hn���A�N�e�B�u�Ȃ�
		if (barricades[i].getActive())
		{
			// �T��1�ڂ̏ꍇ
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getX() - getX());
				minY = (int)abs(barricades[i].getY() - getY());
				minIndex = i;
			}
			else // 2�ڈȍ~
			{
				if ((barricades[i].getX() - getX())*(barricades[i].getX() - getX()) +
					(barricades[i].getY() - getY())*(barricades[i].getY() - getY()) <
					minX * minX + minY * minY)
				{
					// �V���ɑ��
					minX = (int)abs(barricades[i].getX() - getX());
					minY = (int)abs(barricades[i].getY() - getY());
					minIndex = i;
				}
			}
			// �J�E���g�𑝂₷
			count++;
		}
	}
	nearBarricadeIndex =  minIndex;
	return minIndex;
}

//==========================================================
// �G���G�����܂ł̒�����Ƀo���P�[�h�����݂�����true�A���݂��Ȃ��ꍇ��false��Ԃ��B
//==========================================================
bool Enemy::checkBarricadeOnLine() {
	for (int x = tileX; x <= mapNS::MAP_WIDTH; ++x)
	{
		if (map->getMapObj(tileY, x) == 0 || map->getMapCol(tileY, x) == 1)
			break;
		if (map->getMapCol(tileY, x) == 2)
		{
			goalDirection = characterNS::RIGHT;
			return false;
		}
	}
	for (int x = tileX; x >= 0; --x)
	{
		if (map->getMapObj(tileY, x) == 0 || map->getMapCol(tileY, x) == 1)
			break;
		if (map->getMapCol(tileY, x) == 2)
		{
			goalDirection = characterNS::LEFT;
			return false;
		}
	}
	for (int y = tileY; y <= mapNS::MAP_HEIGHT; ++y)
	{
		if (map->getMapObj(y, tileX) == 0 || map->getMapCol(y, tileX) == 1)
			break;
		if (map->getMapCol(y, tileX) == 2)
		{
			goalDirection = characterNS::DOWN;
			return false;
		}
	}
	for (int y = tileY; y >= 0; --y)
	{
		if (map->getMapObj(y, tileX) == 0 || map->getMapCol(y, tileX) == 1)
			break;
		if (map->getMapCol(y, tileX) == 2)
		{
			goalDirection = characterNS::UP;
			return false;
		}
	}
	return true;
}

//==========================================================
// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
//==========================================================
void Enemy::changeAttack(VECTOR2 &collisionVector)
{
	// �U�����O���[�h�Ƀ`�F���W
	loop = false;
	float yPerx = (float)collisionVector.y / collisionVector.x;
	float hPerw = (float)spriteData.height / spriteData.width;
	if (collisionVector.x > 0)
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::RIGHT;
			changeDirection(enemyNS::MOVE_RIGHT_START_FRAME, enemyNS::MOVE_RIGHT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::UP;
			changeDirection(enemyNS::MOVE_UP_START_FRAME, enemyNS::MOVE_UP_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::DOWN;
			changeDirection(enemyNS::MOVE_DOWN_START_FRAME, enemyNS::MOVE_DOWN_END_FRAME);
		}
	}
	else
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::LEFT;
			changeDirection(enemyNS::MOVE_LEFT_START_FRAME, enemyNS::MOVE_LEFT_END_FRAME);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::DOWN;
			changeDirection(enemyNS::MOVE_DOWN_START_FRAME, enemyNS::MOVE_DOWN_END_FRAME);
		}
		else
		{
			goalDirection = characterNS::UP;
			changeDirection(enemyNS::MOVE_UP_START_FRAME, enemyNS::MOVE_UP_END_FRAME);
		}
	}
	goalDirection = characterNS::NONE;
	stateDeteil = enemyNS::PRE_ATTACK;
	state = characterNS::PRE_ATTACK;
	mode = imageNS::VERTICAL;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = enemyNS::ATTACK_LEFT_START_FRAME;
		endFrame = enemyNS::ATTACK_LEFT_END_FRAME;
		break;
	case characterNS::RIGHT:
		startFrame = enemyNS::ATTACK_RIGHT_START_FRAME;
		endFrame = enemyNS::ATTACK_RIGHT_END_FRAME;
		break;
	case characterNS::UP:
		startFrame = enemyNS::ATTACK_UP_START_FRAME;
		endFrame = enemyNS::ATTACK_UP_END_FRAME;
		break;
	case characterNS::DOWN:
		startFrame = enemyNS::ATTACK_DOWN_START_FRAME;
		endFrame = enemyNS::ATTACK_DOWN_END_FRAME;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//==========================================================
// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
//==========================================================
void Enemy::changeAttack(characterNS::DIRECTION dir)
{
	// �U�����O���[�h�Ƀ`�F���W
	loop = false;
	goalDirection = dir;
	switch (dir)
	{
	case characterNS::LEFT:
		changeDirection(enemyNS::MOVE_LEFT_START_FRAME, enemyNS::MOVE_LEFT_END_FRAME);
		break;
	case characterNS::RIGHT:
		changeDirection(enemyNS::MOVE_RIGHT_START_FRAME, enemyNS::MOVE_RIGHT_END_FRAME);
		break;
	case characterNS::UP:
		changeDirection(enemyNS::MOVE_UP_START_FRAME, enemyNS::MOVE_UP_END_FRAME);
		break;
	case characterNS::DOWN:
		changeDirection(enemyNS::MOVE_DOWN_START_FRAME, enemyNS::MOVE_DOWN_END_FRAME);
		break;
	case characterNS::NONE:
		break;
	default:
		break;
	}
	goalDirection = characterNS::NONE;
	stateDeteil = enemyNS::PRE_ATTACK;
	state = characterNS::PRE_ATTACK;
	mode = imageNS::VERTICAL;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = enemyNS::ATTACK_LEFT_START_FRAME;
		endFrame = enemyNS::ATTACK_LEFT_END_FRAME;
		break;
	case characterNS::RIGHT:
		startFrame = enemyNS::ATTACK_RIGHT_START_FRAME;
		endFrame = enemyNS::ATTACK_RIGHT_END_FRAME;
		break;
	case characterNS::UP:
		startFrame = enemyNS::ATTACK_UP_START_FRAME;
		endFrame = enemyNS::ATTACK_UP_END_FRAME;
		break;
	case characterNS::DOWN:
		startFrame = enemyNS::ATTACK_DOWN_START_FRAME;
		endFrame = enemyNS::ATTACK_DOWN_END_FRAME;
		break;
	default:
		break;
	}
	currentFrame = startFrame;
	animTimer = 0.0f;
	setRect();
	return;
}

//==========================================================
// �ړ��\���`�F�b�N
//==========================================================
bool Enemy::checkCanMove(float x, float y)
{
	if (!canMove)
	{
		return false;
	}
	return Character::checkCanMove(x, y);
}

//==========================================================
// �^�C���̒����ɃL�����N�^�[�����邩�ǂ���
//==========================================================
bool Enemy::isCenterOfTile()
{
	map->resetMapCol(tileY, tileX);
	switch (goalDirection)
	{
	case characterNS::RIGHT:
		if (spriteData.x / 32 > tileX + 1)
		{
			tileX += 1;
			return true;
		}
		break;
	case characterNS::LEFT:
		if (spriteData.x / 32 < tileX - 1)
		{
			tileX -= 1;
			return true;
		}
		break;
	case characterNS::UP:
		if (spriteData.y / 32 < tileY - 1)
		{
			tileY -= 1;
			return true;
		}
		break;
	case characterNS::DOWN:
		if (spriteData.y / 32 > tileY + 1)
		{
			tileY += 1;
			return true;
		}
		break;
	}
	return false;
}

//==========================================================
// �w�肵�������ɐi�ݎn�߂��邩�ǂ���
//==========================================================
bool Enemy::canMoveTo(characterNS::DIRECTION dir)
{
	switch (dir)
	{
	case characterNS::LEFT:
		if (map->getMapCol(tileY, tileX - 1) >= 1)
		{
			return false;
		}
		break;
	case characterNS::RIGHT:
		if (map->getMapCol(tileY, tileX + 1) >= 1)
		{
			return false;
		}
		break;
	case characterNS::UP:
		if (map->getMapCol(tileY - 1, tileX) >= 1)
		{
			return false;
		}
		break;
	case characterNS::DOWN:
		if (map->getMapCol(tileY + 1, tileX) >= 1)
		{
			return false;
		}
		break;
	}
	return true;
}