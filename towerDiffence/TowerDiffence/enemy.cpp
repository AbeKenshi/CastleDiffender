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
	// �����̕����͉E
	direction = enemyNS::RIGHT;
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
	collisionType = entityNS::BOX;
	// �����̏�Ԃ͏�Ɍ������Ĉړ�
	state = enemyNS::MOVE_CASTLE;
	goalPos.x = castleNS::X + castleNS::WIDTH / 2;
	goalPos.y = castleNS::Y + castleNS::HEIGHT / 2;
	// �_���[�W�͎󂯂Ă��Ȃ���Ԃ���X�^�[�g
	isDamaged = false;
	// �^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
	// �����v���p�J�E���^�[�����Z�b�g
	distanceCounter = 0.0f;
	// �`��t���O�̓I��
	drawFlag = true;
	// �U������̃R���W�����͖�����Ԃ���X�^�[�g
	attackCollisionFlag = false;
	// �͈͓��ɂ͂��Ȃ���Ԃ���X�^�[�g
	inCertainRange = false;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Enemy::reset()
{
	active = true;
	visible = true;
	health = 100;

	spriteData.x = enemyNS::X;					// ��ʏ�̈ʒu
	spriteData.y = enemyNS::Y;
	frameDelay = enemyNS::MOVE_ANIMATION_DELAY;
	// �����̕����͉E
	direction = enemyNS::RIGHT;
	oldDirection = direction;
	startFrame = enemyNS::MOVE_RIGHT_START_FRAME;
	endFrame = enemyNS::MOVE_RIGHT_END_FRAME;
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	currentFrame = startFrame;
	// �����̏�Ԃ͈ړ�
	state = enemyNS::MOVE_CASTLE;
	goalPos.x = castleNS::X + castleNS::WIDTH / 2;
	goalPos.y = castleNS::Y + castleNS::HEIGHT / 2;
	// �_���[�W�͎󂯂Ă��Ȃ���Ԃ���X�^�[�g
	isDamaged = false;
	// �^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
	// �����v���p�J�E���^�[�����Z�b�g
	distanceCounter = 0.0f;
	// �`��t���O�̓I��
	drawFlag = true;
	// �U������̃R���W�����͖�����Ԃ���X�^�[�g
	attackCollisionFlag = false;
	// �͈͓��ɂ͂��Ȃ���Ԃ���X�^�[�g
	inCertainRange = false;
}

//==========================================================
// �G���G��������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//==========================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// �G���G��`��
//==========================================================
void Enemy::draw()
{
	// �`��t���O���I���̂Ƃ��̂ݕ`��
	if (drawFlag)
		Image::draw();	// �G���G��`��
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Enemy::update(float frameTime, Map *map)
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
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y, map))
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
// ���S���ɌĂяo�����֐�
//==========================================================
void Enemy::dead()
{
	active = false;
	visible = false;
	health = 0;
}

//==========================================================
// �l�H�m�\
//==========================================================
void Enemy::ai(float frameTime, Entity &ent, Barricade *barricades)
{
	// �U�����Ȃ�΍s���I���͍s��Ȃ�
	if (state == enemyNS::ATTACK_BARRICADE || state == enemyNS::ATTACK_BRAVE || state == enemyNS::ATTACK_CASTLE || state == enemyNS::PRE_ATTACK)
	{
		return;
	}

	/*
	// �߂��Ƀv���C���[������ꍇ�A
	if (nearPlayer || nearBarricade)
	{
		changeAttack();
	}
	*/

	/*
	// ����ȊO�͈ړ����[�h�ɐ؂�ւ�
	state = enemyNS::MOVE;
	*/
	int subX, subY;
	/*
	// �v���C���[�Ƃ̈ʒu�����͈͓��Ȃ��true�A����ȊO��false
	inCertainRange = checkDistancePlayer(ent.getX(), ent.getY());

	if (inCertainRange) // �͈͓��ɂ�����v���C���[��ڎw��
	{
		subX = ent.getX() - getX();
		subY = ent.getY() - getY();
	}
	else  // �͈͓��łȂ���Έ�ԋ߂��̃o���P�[�h�̈ʒu��ڎw��
	{
		VECTOR2 nearBarricade = searchNearBarricade(ent, barricades);
		subX = nearBarricade.x - getX();
		subY = nearBarricade.y - getY();
	}*/
	if (state == enemyNS::MOVE_CASTLE || state == enemyNS::MOVE_BARRICADE)
	{
		subX = goalPos.x - getX();
		subY = goalPos.y - getY();
	}

	// ����������32�s�N�Z���ړ����邲�Ƃɕ��������߂Ȃ���
	if (distanceCounter <= 0.0f)
	{
		distanceCounter = 32.0f;
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
// �ړ��\���`�F�b�N
//==========================================================
bool Enemy::checkCanMove(float x, float y, Map *map)
{
	// 1�}�X32pixel�̂���32�Ŋ���
	// -16�͂߂荞�݂�h�~���邽�߂ɔ��}�X�������Ă�
	// +���͔������c
	int map_x = (int)((x - 8) / 32) + 1;
	int map_y = (int)((y - 8) / 32) + 2;

	if (map_x <= 0)
		map_x = 0;
	if (map_x >= mapNS::MAP_WIDTH)
		map_x = mapNS::MAP_WIDTH - 1;
	if (map_y <= 0)
		map_y = 0;
	if (map_y >= mapNS::MAP_HEIGHT)
		map_y = mapNS::MAP_HEIGHT - 1;

	if (map->getMapCol(map_y, map_x) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
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
VECTOR2 Enemy::searchNearBarricade(Entity &ent, Barricade *barricade)
{

	// �ŏ��̋�����
	int minX = 0, minY = 0;
	// �A�N�e�B�u�ȃo���P�[�h�̐��𐔂���p
	int count = 0;

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		// �����o���P�[�hn���A�N�e�B�u�Ȃ�
		if (barricade[i].getActive())
		{
			// �T��1�ڂ̏ꍇ
			if (count == 0)
			{
				minX = barricade[i].getX();
				minY = barricade[i].getY();
			}
			else // 2�ڈȍ~
			{
				// �����ŏ��l���X�V������
				if (barricade[i].getX() * barricade[i].getX() + barricade[i].getY() * barricade[i].getY() <
					minX * minX + minY * minY)
				{
					// �V���ɑ��
					minX = barricade[i].getX();
					minY = barricade[i].getY();
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
		vec.x = minX;
		vec.y = minY;
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
int Enemy::searchNearBarricadeIndex(Barricade *barricade) 
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
		if (barricade[i].getActive())
		{
			// �T��1�ڂ̏ꍇ
			if (count == 0)
			{
				minX = barricade[i].getX();
				minY = barricade[i].getY();
				minIndex = i;
			}
			else // 2�ڈȍ~
			{
				// �����ŏ��l���X�V������
				if (barricade[i].getX() * barricade[i].getX() + barricade[i].getY() * barricade[i].getY() <
					minX * minX + minY * minY)
				{
					// �V���ɑ��
					minX = barricade[i].getX();
					minY = barricade[i].getY();
					minIndex = i;
				}
			}
			// �J�E���g�𑝂₷
			count++;
		}
	}
	return minIndex;
}

//==========================================================
// �G���G���炠��_�܂ł̒�����Ƀo���P�[�h�����݂�����true�A���݂��Ȃ��ꍇ��false��Ԃ��B
//==========================================================
bool Enemy::checkBarricadeOnLine(float x, float y, Map *map) {
	float a = (spriteData.y - y) / (spriteData.x - x);
	float b = (spriteData.x * y - x * spriteData.y) / (spriteData.x - x);
	if (spriteData.x <= x)
	{
		for (int i = spriteData.x; i <= x; ++i)
		{
			if (map->getMapObj(i, a * i + b) == 0)
				return true;
			if (i == x)
				return false;
		}
	}
}

//==========================================================
// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
//==========================================================
void Enemy::changeAttack()
{
	// �U�����O���[�h�Ƀ`�F���W
	loop = false;
	distanceCounter = 0.0f;
	goalDirection = enemyNS::NONE;
	state = enemyNS::PRE_ATTACK;
	mode = imageNS::VERTICAL;
	// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	oldDirection = direction;
	// �����ɉ����ăA�j���[�V������؂�ւ�
	switch (direction)
	{
	case enemyNS::LEFT:
		startFrame = enemyNS::ATTACK_LEFT_START_FRAME;
		endFrame = enemyNS::ATTACK_LEFT_END_FRAME;
		break;
	case enemyNS::RIGHT:
		startFrame = enemyNS::ATTACK_RIGHT_START_FRAME;
		endFrame = enemyNS::ATTACK_RIGHT_END_FRAME;
		break;
	case enemyNS::UP:
		startFrame = enemyNS::ATTACK_UP_START_FRAME;
		endFrame = enemyNS::ATTACK_UP_END_FRAME;
		break;
	case enemyNS::DOWN:
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