#include "brave.h"

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
	direction = braveNS::DIRECTION::RIGHT;
	state = braveNS::STATE::MOVE;
}

//==========================================================
// �E�҂�������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//==========================================================
bool Brave::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// �E�҂�`��
//==========================================================
void Brave::draw()
{
	Image::draw();		// �E�҂�`��
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
		if (input->isKeyDown(BRAVE_LEFT_KEY) || input->isKeyDown(BRAVE_RIGHT_KEY) || input->isKeyDown(BRAVE_UP_KEY) || input->isKeyDown(BRAVE_DOWN_KEY))
		{
			if (input->isKeyDown(BRAVE_LEFT_KEY))
			{
				if (direction != braveNS::DIRECTION::LEFT)
				{
					direction = braveNS::DIRECTION::LEFT;
					startFrame = braveNS::MOVE_LEFT_START_FRAME;
					endFrame = braveNS::MOVE_LEFT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.x -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_RIGHT_KEY))
			{
				if (direction != braveNS::DIRECTION::RIGHT)
				{
					direction = braveNS::DIRECTION::RIGHT;
					startFrame = braveNS::MOVE_RIGHT_START_FRAME;
					endFrame = braveNS::MOVE_RIGHT_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.x += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_UP_KEY))
			{
				if (direction != braveNS::DIRECTION::UP)
				{
					direction = braveNS::DIRECTION::UP;
					startFrame = braveNS::MOVE_UP_START_FRAME;
					endFrame = braveNS::MOVE_UP_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.y -= braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
			if (input->isKeyDown(BRAVE_DOWN_KEY))
			{
				if (direction != braveNS::DIRECTION::DOWN)
				{
					direction = braveNS::DIRECTION::DOWN;
					startFrame = braveNS::MOVE_DOWN_START_FRAME;
					endFrame = braveNS::MOVE_DOWN_END_FRAME;
					currentFrame = startFrame;
					animTimer = 0.0f;
					setRect();
				}
				spriteData.y += braveNS::MOVE_SPEED * frameTime;
				Entity::updateOnlyImage(frameTime);
			}
		}
		else if (input->isKeyDown(BRAVE_ATTACK_KEY))
		{
			loop = false;
			state = braveNS::ATTACK;
			mode = imageNS::VERTICAL;
			oldStartFrame = startFrame;
			oldEndFrame = endFrame;
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
		break;
	case braveNS::ATTACK:
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
	default:
		Entity::update(frameTime);
		break;
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

}