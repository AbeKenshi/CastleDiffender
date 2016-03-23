#include "brave.h"
#include "math.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Brave::Brave() : Entity()
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
	state = braveNS::STATE::MOVE;
	direction = braveNS::UP;
	secondAttackFlag = false;
	isDamaged = false;
	timeCounter = 0.0f;
	totalTimeCounter = 0.0f;
	drawFlag = true;
}

//==========================================================
// �E�҂�������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//==========================================================
bool Brave::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	setRect();
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// �E�҂�`��
//==========================================================
void Brave::draw()
{
	if (drawFlag)
		Image::draw();	// �E�҂�`��
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Brave::update(float frameTime)
{	
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
				if (direction != braveNS::DIRECTION::LEFT)
				{
					direction = braveNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (Brave::checkCanMove(spriteData.x - braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// ���Ɉړ�
					spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// �E�L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				// �E�����������Ă��Ȃ���ΉE�����ɃA�j���[�V���������Z�b�g
				if (direction != braveNS::DIRECTION::RIGHT)
				{
					direction = braveNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (Brave::checkCanMove(spriteData.x + braveNS::MOVE_SPEED * frameTime, spriteData.y)) {
					// �E�Ɉړ�
					spriteData.x += braveNS::MOVE_SPEED * frameTime;
				}
			}
			// ��L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				// ������������Ă��Ȃ���Ώ�����ɃA�j���[�V���������Z�b�g
				if (direction != braveNS::DIRECTION::UP)
				{
					direction = braveNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (Brave::checkCanMove(spriteData.x, spriteData.y - braveNS::MOVE_SPEED * frameTime)) {
					// ��Ɉړ�
					spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				}
			}
			// ���L�[�����͂��ꂽ�ꍇ�A
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				// �������������Ă��Ȃ���Ή������ɃA�j���[�V���������Z�b�g
				if (direction != braveNS::DIRECTION::DOWN)
				{
					direction = braveNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				// �ړ��\��������
				if (Brave::checkCanMove(spriteData.x, spriteData.y + braveNS::MOVE_SPEED * frameTime)) {
					// ���Ɉړ�
					spriteData.y += braveNS::MOVE_SPEED * frameTime;
				}
			}
			Entity::updateOnlyImage(frameTime);
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))	// �U���L�[�������ꂽ�ꍇ�A
		{
			// �A�j���[�V���������Z�b�g
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			// �A�j���[�V�����I�����Ƀt���[����߂����߂ɕۑ�
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
			// �����Ă�������ŃA�j���[�V�����𕪊�
			switch (direction)
			{
			case braveNS::DOWN:
				startFrame = braveNS::DOWN_ATTACK_START_FRAME;
				endFrame = braveNS::DOWN_ATTACK_END_FRAME;
				break;
			case braveNS::RIGHT:
				startFrame = braveNS::RIGHT_ATTACK_START_FRAME;
				endFrame = braveNS::RIGHT_ATTACK_END_FRAME;
				break;
			case braveNS::LEFT:
				startFrame = braveNS::LEFT_ATTACK_START_FRAME;
				endFrame = braveNS::LEFT_ATTACK_END_FRAME;
				break;
			case braveNS::UP:
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
			case braveNS::DOWN:
				startFrame = braveNS::DOWN_GUARD_START_FRAME;
				endFrame = braveNS::DOWN_GUARD_END_FRAME;
				break;
			case braveNS::RIGHT:
				startFrame = braveNS::RIGHT_GUARD_START_FRAME;
				endFrame = braveNS::RIGHT_GUARD_END_FRAME;
				break;
			case braveNS::LEFT:
				startFrame = braveNS::LEFT_GUARD_START_FRAME;
				endFrame = braveNS::LEFT_GUARD_END_FRAME;
				break;
			case braveNS::UP:
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
				case braveNS::DOWN:
					startFrame = braveNS::DOWN_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::DOWN_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::RIGHT:
					startFrame = braveNS::RIGHT_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::RIGHT_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::UP:
					startFrame = braveNS::UP_SECOND_ATTACK_START_FRAME;
					endFrame = braveNS::UP_SECOND_ATTACK_END_FRAME;
					break;
				case braveNS::LEFT:
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

	// �ړ��\��������
	if (Brave::checkCanMove(spriteData.x + frameTime * velocity.x, spriteData.y + frameTime * velocity.y))
	{
		spriteData.x += frameTime * velocity.x;     // �L������X�����ɓ�����
		spriteData.y += frameTime * velocity.y;     // �L������Y�����ɓ�����
	}
}

//==========================================================
// �ړ����̃A�b�v�f�[�g�֐�
//==========================================================
void Brave::updateMoving(float frameTime)
{
	// �A�j���[�V�����̃A�b�v�f�[�g�͒P�Ƃōs����̂ł���ȊO���A�b�v�f�[�g
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// �U�����̃A�b�v�f�[�g�֐�
//==========================================================
void Brave::updateAttacking(float frameTime)
{
	Entity::update(frameTime);
}

//==========================================================
// �_���[�W
//==========================================================
void Brave::damage(WEAPON weapon)
{	
	isDamaged = true;
}

//==========================================================
// �ړ��\���`�F�b�N
//==========================================================
bool Brave::checkCanMove(float x, float y)
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

	if (mapNS::tileCol[map_y][map_x] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}