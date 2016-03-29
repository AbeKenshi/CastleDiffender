#include "brave.h"
#include "math.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Brave::Brave() : Character()
{
	spriteData.width = braveNS::WIDTH;			// �E�҂̃T�C�Y
	spriteData.height = braveNS::HEIGHT;
	spriteData.x = braveNS::X;					// ��ʏ�̈ʒu
	spriteData.y = braveNS::Y;
	spriteData.rect.bottom = braveNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveNS::WIDTH;
	frameDelay = braveNS::MOVE_ANIMATION_DELAY;
	startFrame = braveNS::MOVE_UP_START_FRAME;
	endFrame = braveNS::MOVE_UP_END_FRAME;
	currentFrame = startFrame;
	// Box�̏Փ˔���p
	edge.left = -braveNS::WIDTH / 4.0;
	edge.right = braveNS::WIDTH / 2.0;
	edge.top = -braveNS::HEIGHT / 26.0;
	edge.bottom = braveNS::HEIGHT / 2.0;
	// ��Ԃ͉������Ȃ���Ԃ���X�^�[�g
	state = braveNS::STATE::MOVE;
	secondAttackFlag = false;
	mpTimer = 0.0;
	magicPoint = 100;							// MP��MAX100�ŃX�^�[�g
}

//==========================================================
// �p�����[�^������
//==========================================================
void Brave::reset()
{
	magicPoint = 100;							// MP��MAX100�ŃX�^�[�g
	spriteData.x = braveNS::X;					// ��ʏ�̈ʒu
	spriteData.y = braveNS::Y;
	frameDelay = braveNS::MOVE_ANIMATION_DELAY;
	startFrame = braveNS::MOVE_UP_START_FRAME;
	endFrame = braveNS::MOVE_UP_END_FRAME;
	currentFrame = startFrame;
	state = braveNS::STATE::MOVE;
	secondAttackFlag = false;
	mpTimer = 0.0;
	Character::reset();
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================	
void Brave::update(float frameTime)
{
	if (!active)
		return;
	attackCollisionFlag = false;
	// ��ԑJ�ڑO�̏���
	switch (state)
	{
	case braveNS::MOVE:		// �ړ����͂��ׂẴL�[�̓��͂��󂯕t����
							// �㉺���E�L�[�����͂��ꂽ�ꍇ�A
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// ���L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_LEFT_KEY))
			{
				// �������������Ă��Ȃ���΍������ɃA�j���[�V���������Z�b�g
				if (direction != characterNS::DIRECTION::LEFT)
				{
					direction = characterNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (checkCanMove(spriteData.x - braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// ���Ɉړ�
					spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// �E�L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				// �E�����������Ă��Ȃ���ΉE�����ɃA�j���[�V���������Z�b�g
				if (direction != characterNS::DIRECTION::RIGHT)
				{
					direction = characterNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (checkCanMove(spriteData.x + braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// �E�Ɉړ�
					spriteData.x += braveNS::MOVE_SPEED * frameTime;
				}
			}
			// ��L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				// ������������Ă��Ȃ���Ώ�����ɃA�j���[�V���������Z�b�g
				if (direction != characterNS::DIRECTION::UP)
				{
					direction = characterNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (checkCanMove(spriteData.x, spriteData.y - braveNS::MOVE_SPEED * frameTime)) {
					// ��Ɉړ�
					spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// ���L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				// �������������Ă��Ȃ���Ή������ɃA�j���[�V���������Z�b�g
				if (direction != characterNS::DIRECTION::DOWN)
				{
					direction = characterNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (checkCanMove(spriteData.x, spriteData.y + braveNS::MOVE_SPEED * frameTime)) {
					// ���Ɉړ�
					spriteData.y += braveNS::MOVE_SPEED * frameTime;
				}
			}
			Entity::updateOnlyImage(frameTime);
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))	// �U���L�[�������ꂽ�ꍇ�A
		{
			audio->playCue("kill");
			// �A�j���[�V���������Z�b�g
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			attackCollisionFlag = true;
			// �����Ă�������ŃA�j���[�V�����𕪊�
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = braveNS::DOWN_ATTACK_START_FRAME;
				endFrame = braveNS::DOWN_ATTACK_END_FRAME;
				break;
			case characterNS::RIGHT:
				startFrame = braveNS::RIGHT_ATTACK_START_FRAME;
				endFrame = braveNS::RIGHT_ATTACK_END_FRAME;
				break;
			case characterNS::LEFT:
				startFrame = braveNS::LEFT_ATTACK_START_FRAME;
				endFrame = braveNS::LEFT_ATTACK_END_FRAME;
				break;
			case characterNS::UP:
				startFrame = braveNS::UP_ATTACK_START_FRAME;
				endFrame = braveNS::UP_ATTACK_END_FRAME;
				break;
			}
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		else if (input->isKeyDown(BRAVE_GAURD_KEY))	// �K�[�h�L�[�������ꂽ�ꍇ�A
		{
			// �A�j���[�V���������Z�b�g
			state = braveNS::GAURD;
			// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// �����Ă�������ŃA�j���[�V�����𕪊�
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = braveNS::DOWN_GUARD_START_FRAME;
				endFrame = braveNS::DOWN_GUARD_END_FRAME;
				break;
			case characterNS::RIGHT:
				startFrame = braveNS::RIGHT_GUARD_START_FRAME;
				endFrame = braveNS::RIGHT_GUARD_END_FRAME;
				break;
			case characterNS::LEFT:
				startFrame = braveNS::LEFT_GUARD_START_FRAME;
				endFrame = braveNS::LEFT_GUARD_END_FRAME;
				break;
			case characterNS::UP:
				startFrame = braveNS::UP_GUARD_START_FRAME;
				endFrame = braveNS::UP_GUARD_END_FRAME;
				break;
			}
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		break;
	case braveNS::ATTACK:	// �U�����̓A�j���[�V�������I������܂ő��i�U���̓��͂����󂯕t���Ȃ�
		if (input->isKeyDown(BRAVE_ATTACK_KEY) && currentFrame > startFrame + 2)
		{
			secondAttackFlag = true;
		}
		if (animComplete)
		{
			if (secondAttackFlag)
			{
				switch (direction)
				{
				case characterNS::DOWN:
					startFrame = braveNS::DOWN_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::DOWN_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::RIGHT:
					startFrame = braveNS::RIGHT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::RIGHT_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::UP:
					startFrame = braveNS::UP_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::UP_SECOND_ATTACK_END_FRAME;
					break;
				case characterNS::LEFT:
					startFrame = braveNS::LEFT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::LEFT_SECOND_ATTACK_END_FRAME;
					break;
				}
				state = braveNS::SECOND_ATTACK;
				loop = false;
				currentFrame = startFrame;
				animTimer = 0.0f;
				animComplete = false;
				setRect();
				Entity::updateOnlyImage(frameTime);
				secondAttackFlag = false;
				velocity.y = -sqrt(2 * 2000.0f * braveNS::HEIGHT);
				attackCollisionFlag = true;
			}
			else
			{
				state = braveNS::MOVE;
				mode = imageNS::HORIZONTAL;
				loop = true;
				startFrame = oldStartFrame;
				endFrame = oldEndFrame;
				currentFrame = startFrame;
				animTimer = 0.0f;
				animComplete = false;
				setRect();
				Entity::updateOnlyImage(frameTime);
			}
		}
		break;
	case braveNS::SECOND_ATTACK:	// ���i�U�����̓A�j���[�V�������I������܂œ��͂��󂯕t���Ȃ�
		velocity.y += frameTime * 2000.0f;
		if (animComplete)
		{
			state = braveNS::MOVE;
			mode = imageNS::HORIZONTAL;
			loop = true;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
			Entity::updateOnlyImage(frameTime);
			velocity.y = 0.0f;
		}
		break;
	case braveNS::GAURD:	// �{�^���������ꂽ��K�[�h�I��
		if (!input->isKeyDown(BRAVE_GAURD_KEY))
		{
			state = braveNS::MOVE;
			mode = imageNS::HORIZONTAL;
			startFrame = oldStartFrame;
			endFrame = oldEndFrame;
			currentFrame = startFrame;
			animTimer = 0.0f;
			animComplete = false;
			setRect();
		}
		break;
	}
	// ��ԑJ�ڌ�̏���
	switch (state)
	{
	case braveNS::MOVE:
		updateMoving(frameTime);
		break;
	case braveNS::ATTACK:
		updateAttacking(frameTime);
		break;
	case braveNS::GAURD:
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
		if (totalDamageTime > braveNS::DAMAGE_TIME)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// MP����莞�Ԃ��Ƃɉ�
	mpTimer += frameTime;
	if (mpTimer > braveNS::MP_RECOVERY_TIME)
	{
		mpTimer = 0.0f;
		magicPoint += braveNS::MP_RECOVERY;
		if (magicPoint > 100)
			magicPoint = 100;
	}

	// �ړ��\��������
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y))
	{
		spriteData.x += frameTime * velocity.x;     // �L������X�����ɓ�����
		spriteData.y += frameTime * velocity.y;     // �L������Y�����ɓ�����
	}
	// ��ʂ̒[�܂ŗ�����i�߂Ȃ�
	if (spriteData.x > GAME_WIDTH - braveNS::WIDTH * getScale())	// ��ʉE�[�𒴂�����
		spriteData.x = GAME_WIDTH - braveNS::WIDTH * getScale();	// ��ʉE�[�Ɉړ�
	if (spriteData.x < 0)											// ��ʍ��[�𒴂�����
		spriteData.x = 0;											// ��ʍ��[�Ɉړ�
	if (spriteData.y < rectNS::HEIGHT - 10)								// ��ʏ�[�𒴂�����
		spriteData.y = rectNS::HEIGHT - 10;								// ��ʏ�[�Ɉړ�
	if (spriteData.y > GAME_HEIGHT - braveNS::HEIGHT * getScale())  // ��ʉ��[�𒴂�����
		spriteData.y = GAME_HEIGHT -braveNS::HEIGHT * getScale();	// ��ʉ��[�Ɉړ�
}

//==========================================================
// �_���[�W
//==========================================================
void Brave::damage(WEAPON weapon)
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
		if (state == braveNS::GAURD)
			magicPoint -= 25;
		else
		{
			health -= enemyNS::ATTACK_DAMAGE;
			isDamaged = true;
		}
		break;
	default:
		break;
	}
	if (health <= 0)
		dead();
}