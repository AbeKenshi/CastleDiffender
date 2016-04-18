//==========================================================
/// @file
/// @brief    enemy.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "enemy.h"
#include <iostream>
//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Enemy::Enemy() : Character()
{
	spriteData.width = enemyNS::WIDTH;								// �G���G�̃T�C�Y
	spriteData.height = enemyNS::HEIGHT;
	spriteData.rect.bottom = enemyNS::HEIGHT;						// ��ʂ̈ꕔ��I��
	spriteData.rect.right = enemyNS::WIDTH;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;						// �A�j���[�V�����̊e�t���[���̊Ԋu
																	// �����̕����͉E
	goalDirection = characterNS::RIGHT;								// ���ɐi�ނׂ�����
	oldDirection = direction;										// �U�����O�Ɍ����Ă�������
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;					// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;						// �A�j���[�V�����̍Ō�̃t���[��
	oldStartFrame = startFrame;										// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����̍ŏ��̃t���[��
	oldEndFrame = endFrame;											// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;										// ���݂̃t���[�����A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
																	// Box�̏Փ˔���p
	edge.left = (LONG)(-enemyNS::WIDTH * spriteData.scale / 2.0);
	edge.right = (LONG)(enemyNS::WIDTH * spriteData.scale / 2.0);
	edge.top = (LONG)(-enemyNS::HEIGHT * spriteData.scale / 2.0);
	edge.bottom = (LONG)(enemyNS::HEIGHT * spriteData.scale / 2.0);

	canMakeDecesionMove = false;									// �ړ��Ɋւ��Ă̈ӎv������s���邩�ǂ���
	attackAnimationMode = imageNS::VERTICAL;						// �U�����̃A�j���[�V�����̑J�ڃ��[�h�i�����A�����j
	moveUpStartFrame = enemyNS::MOVE_UP_START_FRAME;				// ������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveUpEndFrame = enemyNS::MOVE_UP_END_FRAME;					// ������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveRightStartFrame = enemyNS::MOVE_RIGHT_START_FRAME;			// �E�����ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveRightEndFrame = enemyNS::MOVE_RIGHT_END_FRAME;				// �E�����ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveDownStartFrame = enemyNS::MOVE_DOWN_START_FRAME;			// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveDownEndFrame = enemyNS::MOVE_DOWN_END_FRAME;				// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveLeftStartFrame = enemyNS::MOVE_LEFT_START_FRAME;			// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveLeftEndFrame = enemyNS::MOVE_LEFT_END_FRAME;				// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	attackUpStartFrame = enemyNS::ATTACK_UP_START_FRAME;			// ������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackUpEndFrame = enemyNS::ATTACK_UP_END_FRAME;				// ������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackRightStartFrame = enemyNS::ATTACK_RIGHT_START_FRAME;		// �E�����U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackRightEndFrame = enemyNS::ATTACK_RIGHT_END_FRAME;			// �E�����U���̃A�j���[�V�����̍Ō�̃t���[��
	attackDownStartFrame = enemyNS::ATTACK_DOWN_START_FRAME;		// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackDownEndFrame = enemyNS::ATTACK_DOWN_END_FRAME;			// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackLeftStartFrame = enemyNS::ATTACK_LEFT_START_FRAME;		// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackLeftEndFrame = enemyNS::ATTACK_LEFT_END_FRAME;			// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackTime = enemyNS::ATTACK_TIME;								// �v���C���[�ɗאڂ��Ă���U���Ɉڂ�܂ł̗��ߎ���
	continueAttackTime = enemyNS::CONTINUE_ATTACK_TIME;				// �A���ōU������ꍇ�̗��ߎ���
	damagePer = 1.0f;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Enemy::reset()
{
	Character::reset();
	// �����̕����͉E
	oldDirection = direction;
	goalDirection = characterNS::RIGHT;
	// �ړ��Ɋւ��Ă̈ӎv����͍s���Ȃ�
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
	
	// �U�����肪�łĂ���ꍇ�̓R���W�����𐶐����ē����蔻����Ƃ�
	if (attackCollisionFlag) {
		attackCollision.attack(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), direction);
	}
	// �U�����̃G���e�B�e�B���o���t���O���I�t
	attackCollisionFlag = false;
	// �ړ��Ɋւ��Ă̈ӎv����̓f�t�H���g�ł͍s���Ȃ�
	canMakeDecesionMove = false;

	// �����ŏ�ԑJ�ځA���W�̈ړ��A�A�j���[�V�����̃��Z�b�g���s��
	// ���ꂼ��̏�Ԃ��Ƃɏ����𕪊�
	switch (state)
	{
	case characterNS::MOVE:	// �ړ����Ȃ�ڕW�̕����ɂ܂������i��
		// �ڕW�̕����Ɍ������Đi��
		switch (goalDirection)
		{
		case characterNS::LEFT:
			if (direction != goalDirection)
				changeDirection(moveLeftStartFrame, moveLeftEndFrame);
			// ���Ɉړ�
			spriteData.x -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::RIGHT:
			if (direction != goalDirection)
				changeDirection(moveRightStartFrame, moveRightEndFrame);
			// �E�Ɉړ�
			spriteData.x += enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::UP:
			if (direction != goalDirection)
				changeDirection(moveUpStartFrame, moveUpEndFrame);
			// ��Ɉړ�
			spriteData.y -= enemyNS::MOVE_SPEED * frameTime;
			break;
		case characterNS::DOWN:
			if (direction != goalDirection)
				changeDirection(moveDownStartFrame, moveDownEndFrame);
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
			map->updateMapCol((float)(tileY * mapNS::TEXTURE_SIZE), (float)(tileX * mapNS::TEXTURE_SIZE), map->getMapCol(tileY, tileX) + 3);
			// �ړ��Ɋւ��Ă̈ӎv���肪�\
			canMakeDecesionMove = true;
		}
		break;
	case characterNS::ATTACK:	// �U����
		// �A�j���[�V�������I�����Ă�����U���I��
		// ��Ԃ��ړ����ɖ߂�
		if (animComplete)
		{
			// �ړ��Ɋւ��Ă̈ӎv���肪�\
			canMakeDecesionMove = true;
			// �U������Ȃ̂Ńt���O���I��
			isAttacked = true;
			// ��Ԃ��ړ����ւƑJ��
			changeStateToMove();
			// �����Ă��������߂�
			direction = oldDirection;
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case characterNS::PRE_ATTACK:	// �U�����O
		// �^�C�}�[�����Z�A��莞�Ԃ𒴂�����U���Ɉڂ�
		attackTimer += frameTime;
		// �U������Ȃ�cuntinueAttackTime��ɍU��
		if (isAttacked && attackTimer > continueAttackTime)
		{
			attackTimer = 0.0f;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		// �U������łȂ��Ȃ�attackTime��ɍU��
		else if (!isAttacked && attackTimer > attackTime)
		{
			attackTimer = 0.0f;
			state = characterNS::ATTACK;
			attackCollisionFlag = true;
		}
		break;
	case characterNS::WAIT:		// �ҋ@��
		// �ړ��Ɋւ��Ă̈ӎv���肪�\
		canMakeDecesionMove = true;
		break;
	case characterNS::DEATH:	// ���S��
		// �`��͉\
		drawFlag = true;
		// �_���[�W�͖���
		isDamaged = false;
		// �W�����v���Ȃ̂ŁA�d�͂ɏ]���Č���������
		velocity.y += frameTime * 2000.0f;
		// xy�����ɃW�����v
		spriteData.x += frameTime * velocity.x;
		spriteData.y += frameTime * velocity.y;
		// �Q�[����ʂ�艺�ɏo����A�G���e�B�e�B���A�N�e�B�u��
		if (spriteData.y > GAME_HEIGHT)
			dead();
	default:
		break;
	}

	// ��ԑJ�ڌ�̏���
	// �ړ����̓L�[��������Ă���Ԃ̂݃A�j���[�V�������i�ނ悤�ɂ������̂ŁA
	// �G���e�B�e�B�ƃA�j���[�V�����̍X�V��Ɨ��ɍs���Ă���
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
		if (totalDamageTime > enemyNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// �U���p�G���e�B�e�B���X�V
	attackCollision.update(frameTime);
}

//==========================================================
// �_���[�W����
// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
//==========================================================
void Enemy::damage(WEAPON weapon)
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
		health -= braveFireDamage * damagePer;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case BRAVE_ATTACK:			// �E�҂̍U��
		// ���_���[�W���󂯂�
		health -= braveAttackDamage * damagePer;
		// �_���[�W��Ԃ̃t���O���I��
		isDamaged = true;
		break;
	case BRAVE_SECOND_ATTACK:	// �E�҂̑��
		// ���_���[�W���󂯂�
		health -= braveAttackDamage * damagePer;
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

//==========================================================
// �l�H�m�\
//==========================================================
void Enemy::ai(float frameTime, Entity &ent)
{
}

//==========================================================
// �����Ă��������ύX���郁�\�b�h
//==========================================================
void Enemy::changeDirection(int strF, int endF)
{
	direction = goalDirection;
	startFrame = strF;
	endFrame = endF;
	setCurrentFrame(startFrame);
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
		// �����o���P�[�h���A�N�e�B�u�Ȃ�
		if (barricades[i].getActive())
		{
			// �T��1�ڂ̏ꍇ
			if (count == 0)
			{
				minX = (int)abs(barricades[i].getTileX() - getTileX());
				minY = (int)abs(barricades[i].getTileY() - getTileY());
				minIndex = i;
			}
			else // 2�ڈȍ~
			{
				if ((barricades[i].getTileX() - getTileX())*(barricades[i].getTileX() - getTileX()) +
					(barricades[i].getTileY() - getTileY())*(barricades[i].getTileY() - getTileY()) <
					minX * minX + minY * minY)
				{
					// �V���ɑ��
					minX = (int)abs(barricades[i].getTileX() - getTileX());
					minY = (int)abs(barricades[i].getTileY() - getTileY());
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
	// �G���G�̏㉺���E���ꂼ��ɑ΂��āA�G���G����߂����ɏ邪�Ȃ������`�F�b�N
	// ���ꂼ��̕����ɂ��āA��ȊO�̃I�u�W�F�N�g����Ɍ��������ꍇ��true��Ԃ�
	// �����ꂩ�̕����ɂ��āA��܂ł̒�����ɂȂ�̃I�u�W�F�N�g���Ȃ��ꍇ��false��Ԃ�
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
	// �Փ˃x�N�g���𗘗p���āA�ՓˑΏۂ���������������悤�ɐݒ�
	float yPerx = (float)collisionVector.y / collisionVector.x;
	float hPerw = (float)spriteData.height / spriteData.width;
	if (collisionVector.x > 0)
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::RIGHT;
			changeDirection(moveRightStartFrame, moveRightEndFrame);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::UP;
			changeDirection(moveUpStartFrame, moveUpEndFrame);
		}
		else
		{
			goalDirection = characterNS::DOWN;
			changeDirection(moveDownStartFrame, moveDownEndFrame);
		}
	}
	else
	{
		if (yPerx > -hPerw && yPerx < hPerw)
		{
			goalDirection = characterNS::LEFT;
			changeDirection(moveLeftStartFrame, moveLeftEndFrame);
		}
		else if (yPerx < -hPerw)
		{
			goalDirection = characterNS::DOWN;
			changeDirection(moveDownStartFrame, moveDownEndFrame);
		}
		else
		{
			goalDirection = characterNS::UP;
			changeDirection(moveUpStartFrame, moveUpEndFrame);
		}
	}
	// ���ɐi�ނׂ������̓��Z�b�g
	goalDirection = characterNS::NONE;
	// �U�����O�ɏ�Ԃ�J��
	state = characterNS::PRE_ATTACK;
	// �A�j���[�V�����̃��[�h��ݒ�
	mode = attackAnimationMode;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;

	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = attackLeftStartFrame;
		endFrame = attackLeftEndFrame;
		break;
	case characterNS::RIGHT:
		startFrame = attackRightStartFrame;
		endFrame = attackRightEndFrame;
		break;
	case characterNS::UP:
		startFrame = attackUpStartFrame;
		endFrame = attackUpEndFrame;
		break;
	case characterNS::DOWN:
		startFrame = attackDownStartFrame;
		endFrame = attackDownEndFrame;
		break;
	default:
		break;
	}
	setCurrentFrame(startFrame);
	return;
}

//==========================================================
// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
//==========================================================
void Enemy::changeAttack(characterNS::DIRECTION dir)
{
	// �U�����O���[�h�Ƀ`�F���W
	loop = false;
	// ������ύX
	goalDirection = dir;
	switch (dir)
	{
	case characterNS::LEFT:
		changeDirection(moveLeftStartFrame, moveLeftEndFrame);
		break;
	case characterNS::RIGHT:
		changeDirection(moveRightStartFrame, moveRightEndFrame);
		break;
	case characterNS::UP:
		changeDirection(moveUpStartFrame, moveUpEndFrame);
		break;
	case characterNS::DOWN:
		changeDirection(moveDownStartFrame, moveDownEndFrame);
		break;
	case characterNS::NONE:
		break;
	default:
		break;
	}
	// ���ɐi�ނׂ������̓��Z�b�g
	goalDirection = characterNS::NONE;
	// �U�����O�ɏ�Ԃ�J��
	state = characterNS::PRE_ATTACK;
	// �A�j���[�V�����̃��[�h��ݒ�
	mode = attackAnimationMode;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case characterNS::LEFT:
		startFrame = attackLeftStartFrame;
		endFrame = attackLeftEndFrame;
		break;
	case characterNS::RIGHT:
		startFrame = attackRightStartFrame;
		endFrame = attackRightEndFrame;
		break;
	case characterNS::UP:
		startFrame = attackUpStartFrame;
		endFrame = attackUpEndFrame;
		break;
	case characterNS::DOWN:
		startFrame = attackDownStartFrame;
		endFrame = attackDownEndFrame;
		break;
	default:
		break;
	}
	setCurrentFrame(startFrame);
	return;
}

//==========================================================
// �^�C���̒����ɃL�����N�^�[�����邩�ǂ���
//==========================================================
bool Enemy::isCenterOfTile()
{
	bool isCenter = false;
	// �㉺���E�ǂ��Ɉړ����Ă��邩�ɂ���Ē����ɂ��邩�̔���𕪊�
	// ��{�I�ɂ́A������^�C�����ׂ�����^�C�����ړ����Ē����ɗ����Ɣ���
	switch (goalDirection)
	{
	case characterNS::RIGHT:
		if (spriteData.x / 32 >= tileX + 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileX += 1;
			isCenter = true;
		}
		break;
	case characterNS::LEFT:
		if (spriteData.x / 32 <= tileX - 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileX -= 1;
			isCenter = true;
		}
		break;
	case characterNS::UP:
		if (spriteData.y / 32 <= tileY - 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileY -= 1;
			isCenter = true;
		}
		break;
	case characterNS::DOWN:
		if (spriteData.y / 32 >= tileY + 1)
		{
			map->updateMapCol((float)tileY * 32, (float)tileX * 32, map->getMapCol(tileY, tileX) - 3);
			tileY += 1;
			isCenter = true;
		}
		break;
	}
	return isCenter;
}

//==========================================================
// �w�肵�������ɐi�ݎn�߂��邩�ǂ���
//==========================================================
bool Enemy::canMoveTo(characterNS::DIRECTION dir)
{
	// �w�肵�������̃^�C���ɏ�Q��������Έړ��ł��Ȃ�
	// �Ȃ���Έړ��\
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