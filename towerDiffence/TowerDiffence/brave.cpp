//==========================================================
/// @file
/// @brief    brave.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "brave.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Brave::Brave() : Character()
{
	spriteData.width = braveNS::WIDTH;							// �E�҂̃T�C�Y
	spriteData.height = braveNS::HEIGHT;
	spriteData.x = braveNS::X;									// ��ʏ�̈ʒu
	spriteData.y = braveNS::Y;
	spriteData.rect.bottom = braveNS::HEIGHT;					// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveNS::WIDTH;
	frameDelay = braveNS::ANIMATION_DELAY;						// �A�j���[�V�����̊e�t���[���̊Ԋu
	startFrame = braveNS::MOVE_UP_START_FRAME;					// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = braveNS::MOVE_UP_END_FRAME;						// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;									// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	// Box�̏Փ˔���p
	edge.left = (LONG)(-braveNS::WIDTH * spriteData.scale / 2.0);
	edge.right = (LONG)(braveNS::WIDTH * spriteData.scale / 2.0);
	edge.top = (LONG)(-braveNS::HEIGHT * spriteData.scale / 2.0);
	edge.bottom = (LONG)(braveNS::HEIGHT * spriteData.scale / 2.0);

	secondAttackFlag = false;									// ��A���ڂ̍U���t���O�̓I�t
	mpTimer = 0.0;												// MP�񕜗p�̃^�C�}�[
	magicPoint = 100;											// MP��MAX100�ŃX�^�[�g
	moveUpStartFrame = braveNS::MOVE_UP_START_FRAME;			// ������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveUpEndFrame = braveNS::MOVE_UP_END_FRAME;				// ������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveRightStartFrame = braveNS::MOVE_RIGHT_START_FRAME;		// �E�����ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveRightEndFrame = braveNS::MOVE_RIGHT_END_FRAME;			// �E�����ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveDownStartFrame = braveNS::MOVE_DOWN_START_FRAME;		// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveDownEndFrame = braveNS::MOVE_DOWN_END_FRAME;			// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	moveLeftStartFrame = braveNS::MOVE_LEFT_START_FRAME;		// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	moveLeftEndFrame = braveNS::MOVE_LEFT_END_FRAME;			// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	frameDelay = braveNS::ANIMATION_DELAY;						// �A�j���[�V�����̃t���[���Ԃ̊Ԋu�i�b�j
	attackUpStartFrame = braveNS::UP_ATTACK_START_FRAME;		// ������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackUpEndFrame = braveNS::UP_ATTACK_END_FRAME;			// ������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackRightStartFrame = braveNS::RIGHT_ATTACK_START_FRAME;	// �E�����U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackRightEndFrame = braveNS::RIGHT_ATTACK_END_FRAME;		// �E�����U���̃A�j���[�V�����̍Ō�̃t���[��
	attackDownStartFrame = braveNS::DOWN_ATTACK_START_FRAME;	// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackDownEndFrame = braveNS::DOWN_ATTACK_END_FRAME;		// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	attackLeftStartFrame = braveNS::LEFT_ATTACK_START_FRAME;	// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	attackLeftEndFrame = braveNS::LEFT_ATTACK_END_FRAME;		// �������U���̃A�j���[�V�����̍Ō�̃t���[��
}

//==========================================================
// �p�����[�^������
//==========================================================
void Brave::reset()
{
	mpTimer = 0.0;												// MP�񕜗p�̃^�C�}�[
	magicPoint = 100;											// MP��MAX100�ŃX�^�[�g
	spriteData.x = braveNS::X;									// ��ʏ�̈ʒu
	spriteData.y = braveNS::Y;
	frameDelay = braveNS::ANIMATION_DELAY;						// �A�j���[�V�����̃t���[���Ԃ̊Ԋu�i�b�j
	startFrame = braveNS::MOVE_UP_START_FRAME;					// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = braveNS::MOVE_UP_END_FRAME;						// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;									// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	secondAttackFlag = false;									// ��A���ڂ̍U���t���O�̓I�t
	fire.reset();												// ����������
	Character::reset();
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================	
void Brave::update(float frameTime)
{
	// �G���e�B�e�B����A�N�e�B�u�Ȃ�A�������Ȃ�
	if (!active)
		return;


	// �E�҂̍U�����肪�łĂ���ꍇ�̓R���W�����𐶐����ē����蔻����Ƃ�
	if (attackCollisionFlag)
		braveAttackCollision.attack(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), direction);

	// FIRE_KEY�ɑΉ�����L�[�������ꂽ��E�҂��牊�𔭎�
	if (input->isKeyDown(BRAVE_FIRE_KEY))
		fire.fire(getCenterX(), getCenterY(), (float)getWidth(), (float)getHeight(), getScale(), magicPoint, direction);

	// �U���p�̃G���e�B�e�B���o��������t���O���I�t
	attackCollisionFlag = false;

	// �����ŏ�ԑJ�ځA���W�̈ړ��A�A�j���[�V�����̃��Z�b�g���s��
	// ���ꂼ��̏�Ԃ��Ƃɏ����𕪊�
	switch (state)
	{
	case characterNS::MOVE:		// �ړ����͂��ׂẴL�[�̓��͂��󂯕t����
		// �㉺���E�L�[�����͂��ꂽ�ꍇ�A
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// ���͂ɉ����ėE�҂̌�����ύX�A�ړ�
			changeWithMove(frameTime);
		}
		if (input->isKeyDown(BRAVE_ATTACK_KEY))	// �U���L�[�������ꂽ�ꍇ�A
		{
			// �U���p�I�[�f�B�I���Đ�
			audio->playCue("kill");
			// ��Ԃ��U�����ɑJ��
			state = characterNS::ATTACK;
			// �A�j���[�V�����t���[���̑J�ڂ͐�������
			mode = imageNS::VERTICAL;
			// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// �U���p�̃G���e�B�e�B�̏o���t���O���I��
			attackCollisionFlag = true;
			// �����Ă�������ŃA�j���[�V�����𕪊�
			loop = false;
			switch (direction)
			{
			case characterNS::DOWN:
				startFrame = attackDownStartFrame;
				endFrame = attackDownEndFrame;
				break;
			case characterNS::RIGHT:
				startFrame = attackRightStartFrame;
				endFrame = attackRightEndFrame;
				break;
			case characterNS::LEFT:
				startFrame = attackLeftStartFrame;
				endFrame = attackLeftEndFrame;
				break;
			case characterNS::UP:
				startFrame = attackUpStartFrame;
				endFrame = attackUpEndFrame;
				break;
			}
			setCurrentFrame(startFrame);
		}
		else if (input->isKeyDown(BRAVE_GAURD_KEY))	// �K�[�h�L�[�������ꂽ�ꍇ�A
		{
			// ��Ԃ��K�[�h���ɑJ��
			state = characterNS::GAURD;
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
			setCurrentFrame(startFrame);
		}
		break;
	case characterNS::ATTACK:	// �U�����̓A�j���[�V�������I������܂ő��i�U�����ړ��̓��͂����󂯕t���Ȃ�
		// �㉺���E�L�[�����͂��ꂽ�ꍇ�A
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			// ���͂ɉ����ėE�҂̌�����ύX�A�ړ�
			changeWithMove(frameTime);
		}
		// �U�����ɂ���ɍU���{�^���������ꂽ�ꍇ�A
		if (input->isKeyDown(BRAVE_ATTACK_KEY) && currentFrame > startFrame + 2)
		{
			// ��񌂍U���̃t���O���I��
			secondAttackFlag = true;
		}
		// �U���A�j���[�V�������I�������ꍇ�A
		if (animComplete)
		{
			// ��񌂍U���̃t���O���I���Ȃ�
			if (secondAttackFlag)
			{
				// ��Ԃ͑�񌂍U�����ւƑJ��
				state = characterNS::SECOND_ATTACK;
				// ���݂̌����ɍ��킹�ăA�j���[�V�������ēx���Z�b�g
				loop = false;
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
				setCurrentFrame(startFrame);
				// ��񌂍U���̃t���O���I�t
				secondAttackFlag = false;
				// ��񌂍U�����͌y���W�����v���Ȃ���U������
				velocity.y = -sqrt(2 * 2000.0f * braveNS::HEIGHT);
				// �W�����v���J�n���������Y���W��ۑ�
				tmpY = getY();
				// �U���̃G���e�B�e�B�̏o���t���O���I��
				attackCollisionFlag = true;
			}
			else
			// ��񌂍U���̃t���O���I�t�Ȃ�
			{
				// ��Ԃ��ړ����ւƑJ��
				changeStateToMove();
			}
			// �A�j���[�V�����̂ݍX�V�i�G���e�B�e�B�͍X�V���Ȃ��j
			Entity::updateOnlyImage(frameTime);
		}
		break;
	case characterNS::SECOND_ATTACK:	// ���i�U�����̓A�j���[�V�������I������܂œ��͂��󂯕t���Ȃ�
		// �W�����v���Ȃ̂ŁA�d�͂ɏ]���Č���������
		velocity.y += frameTime * 2000.0f;
		// y�����̑��x = -�W�����v���J�n�����Ƃ��̏����x�̏ꍇ�i�W�����v�O��y���W�܂Ŗ߂��Ă��邱�Ƃ����҂����j�A
		if (velocity.y > sqrt(2 * 2000.0f * braveNS::HEIGHT))
		{
			// �኱�̂����␳���邽�߂ɁA�����I��y���W���W�����v�O�̍��W�ւƖ߂�
			setY(tmpY);
			// ��Ԃ��ړ����ւƑJ��
			changeStateToMove();
			// �A�j���[�V�����̂ݍX�V�i�G���e�B�e�B�͍X�V���Ȃ��j
			Entity::updateOnlyImage(frameTime);
			// y�����ւ̑��x��0�ɂ��ăW�����v�I��
			velocity.y = 0.0f;
		}
		break;
	case characterNS::GAURD:	// �{�^���������ꂽ��K�[�h�I��
		if (!input->isKeyDown(BRAVE_GAURD_KEY))
		{
			// ��Ԃ��ړ����ւƑJ��
			changeStateToMove();
		}
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
	case characterNS::GAURD:
		Entity::update(frameTime);
		break;
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
	if (mpTimer > braveMpRecoveryTime)
	{
		mpTimer = 0.0f;
		magicPoint += braveMpRecovery;
		// MAX100�𒴂�����A100�ɂ���
		if (magicPoint > 100)
			magicPoint = 100;
	}

	// �ړ��\��������i��񌂍U�����̓W�����v���Ȃ̂ňړ��������I�ɋ��j
	if (checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y) || state == characterNS::SECOND_ATTACK)
	{
		spriteData.x += frameTime * velocity.x;     // �L������X�����ɓ�����
		spriteData.y += frameTime * velocity.y;     // �L������Y�����ɓ�����
	}

	// ��ʂ̒[�܂ŗ�����i�߂Ȃ�
	if (spriteData.x > GAME_WIDTH - braveNS::WIDTH * getScale())	// ��ʉE�[�𒴂�����
		spriteData.x = GAME_WIDTH - braveNS::WIDTH * getScale();	// ��ʉE�[�Ɉړ�
	if (spriteData.x < 0)											// ��ʍ��[�𒴂�����
		spriteData.x = 0;											// ��ʍ��[�Ɉړ�
	if (spriteData.y < rectNS::HEIGHT - 10)							// ��ʏ�[�𒴂�����
		spriteData.y = rectNS::HEIGHT - 10;							// ��ʏ�[�Ɉړ�
	if (spriteData.y > GAME_HEIGHT - braveNS::HEIGHT * getScale())  // ��ʉ��[�𒴂�����
		spriteData.y = GAME_HEIGHT -braveNS::HEIGHT * getScale();	// ��ʉ��[�Ɉړ�


	// �E�҂̍U���R���W�������X�V
	braveAttackCollision.update(frameTime);
	// �����X�V
	fire.update(frameTime);
}

//==========================================================
// �_���[�W����
// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
//==========================================================
void Brave::damage(WEAPON weapon)
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
	case ENEMY_ATTACK:			// �G���G
		// �K�[�h���Ȃ�A�_���[�W�̑����MP������
		if (state == characterNS::GAURD)
			magicPoint -= 25;
		else  // �K�[�h���łȂ��Ȃ�A
		{
			// ���_���[�W���󂯂�
			health -= enemyAttackDamage * damagePer;
			// �_���[�W��Ԃ̃t���O���I��
			isDamaged = true;
		}
		break;
	case MIDBOSS_ATTACK:		// ���{�X
		// �K�[�h���Ȃ�A�_���[�W�̑����MP������
		if (state == characterNS::GAURD)
			magicPoint -= 35;
		else  // �K�[�h���łȂ��Ȃ�A
		{
			// ���_���[�W���󂯂�
			health -= midBossAttackDamage * damagePer;
			// �_���[�W��Ԃ̃t���O���I��
			isDamaged = true;
		}
		break;
	default:
		break;
	}
	// �̗͂�0�ȉ��ɂȂ����Ȃ�A���S
	if (health <= 0)
		dead();
}

//==========================================================
// �����Ă�������ƃA�j���[�V������؂�ւ���
// �����I�ɂ̂ݎg�p
//==========================================================
void Brave::changeWithMove(float frameTime)
{
	float r = 1.0f;
	if (state == BRAVE_ATTACK)
		r = 2.0f;
	// ���L�[�����͂��ꂽ�ꍇ�A
	if (input->isKeyDown(BRAVE_LEFT_KEY))
	{
		// �����Ă������������
		setDirection(characterNS::LEFT);
		// �ړ��\��������
		if (checkCanMove(spriteData.x - braveMoveSpeed * frameTime, spriteData.y)) {
			// ���Ɉړ�
			spriteData.x -= braveMoveSpeed / r * frameTime;
		}
	}
	// �E�L�[�����͂��ꂽ�ꍇ�A
	if (input->isKeyDown(BRAVE_RIGHT_KEY))
	{
		// �����Ă���������E��
		setDirection(characterNS::RIGHT);
		// �ړ��\��������
		if (checkCanMove(spriteData.x + braveMoveSpeed * frameTime, spriteData.y)) {
			// �E�Ɉړ�
			spriteData.x += braveMoveSpeed / r * frameTime;
		}
	}
	// ��L�[�����͂��ꂽ�ꍇ�A
	if (input->isKeyDown(BRAVE_UP_KEY))
	{
		// �����Ă�����������
		setDirection(characterNS::UP);
		// �ړ��\��������
		if (checkCanMove(spriteData.x, spriteData.y - braveMoveSpeed * frameTime)) {
			// ��Ɉړ�
			spriteData.y -= braveMoveSpeed / r * frameTime;
		}
	}
	// ���L�[�����͂��ꂽ�ꍇ�A
	if (input->isKeyDown(BRAVE_DOWN_KEY))
	{
		// �����Ă������������
		setDirection(characterNS::DOWN);
		// �ړ��\��������
		if (checkCanMove(spriteData.x, spriteData.y + braveMoveSpeed * frameTime)) {
			// ���Ɉړ�
			spriteData.y += braveMoveSpeed / r * frameTime;
		}
	}
	// �A�j���[�V�����̂ݍX�V�i�G���e�B�e�B�͍X�V���Ȃ��j
	Entity::updateOnlyImage(frameTime);
}