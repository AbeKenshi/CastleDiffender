//==========================================================
/// @file
/// @brief    character.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "character.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Character::Character() : Entity()
{
	// �����̕����͉E
	direction = characterNS::RIGHT;
	// Box�̏Փ˔�����g�p
	collisionType = entityNS::BOX;
	// �U������̃R���W�����͍ŏ��͂Ȃ�
	attackCollisionFlag = false;
	// ��Ԃ͉������Ȃ���Ԃ���X�^�[�g
	state = characterNS::STATE::MOVE;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Character::reset()
{
	// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����t���[���ۑ��p
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	// �����̕����͉E
	direction = characterNS::RIGHT;
	// �U������̃R���W�����͂Ȃ��Ń��Z�b�g
	attackCollisionFlag = false;
	// ��Ԃ͉������Ȃ���Ԃ���X�^�[�g
	state = characterNS::STATE::MOVE;
	// �G���e�B�e�B�����Z�b�g
	Entity::reset();
}

//==========================================================
// �ړ����̃A�b�v�f�[�g�֐�
// �A�j���[�V�����ȊO���A�b�v�f�[�g
//==========================================================
void Character::updateMoving(float frameTime)
{
	// �A�j���[�V�����̃A�b�v�f�[�g�͒P�Ƃōs����̂ł���ȊO���A�b�v�f�[�g
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// �U�����̃A�b�v�f�[�g�֐�
// ����ł͒ʏ�̃A�b�v�f�[�g
//==========================================================
void Character::updateAttacking(float frameTime)
{
	Entity::update(frameTime);
}

//==========================================================
// ���S���ɌĂяo�����֐�
//==========================================================
void Character::dead()
{
	// �L�����N�^�[���A�N�e�B�u�ɂ���
	active = false;
	visible = false;
	health = 0;
}

//==========================================================
// �ړ��\���`�F�b�N
// ���s�O�Fx�Ay = �`�F�b�N�������ʒu�̉�ʏ�ł̍��W
//==========================================================
bool Character::checkCanMove(float x, float y)
{
	// 1�}�X32pixel�̂���32�Ŋ���
	// -16�͂߂荞�݂�h�~���邽�߂ɔ��}�X�������Ă�
	// +���͔������c
	int map_x = (int)((x - 16) / 32) + 1;
	int map_y = (int)((y - 16) / 32) + 1;
	if (map_x <= 0)
		map_x = 0;
	if (map_x >= mapNS::MAP_WIDTH)
		map_x = mapNS::MAP_WIDTH - 1;
	if (map_y <= 0)
		map_y = 0;
	if (map_y >= mapNS::MAP_HEIGHT)
		map_y = mapNS::MAP_HEIGHT - 1;

	// �i�����Ƃ���}�b�v�^�C���ɏ�Q�����������ꍇ�A
	if (map->getMapCol(map_y, map_x) == 1 || map->getMapCol(map_y, map_x) == 2)
	{
		// �ړ��s��
		return false;
	}
	else  // �i�����Ƃ���}�b�v�^�C���ɏ�Q�����Ȃ��ꍇ�A
	{
		// �ړ��\
		return true;
	}
}

//==========================================================
// �����Ă���������Z�b�g����
// ���s�O�Fdir = �Z�b�g����L�����N�^�[�̌���
//==========================================================
void Character::setDirection(characterNS::DIRECTION dir)
{
	// �Z�b�g����L�����N�^�[�̌����ɂ���ĕ���
	switch (dir)
	{
	case characterNS::LEFT:
		// �������������Ă��Ȃ���΍������ɃA�j���[�V���������Z�b�g
		if (direction != characterNS::DIRECTION::LEFT)
		{
			direction = characterNS::DIRECTION::LEFT;
			startFrame = moveLeftStartFrame;
			currentFrame = endFrame - currentFrame + moveLeftStartFrame;
			endFrame = moveLeftEndFrame;
			setRect();
		}
		break;
	case characterNS::RIGHT:
		// �E�����������Ă��Ȃ���ΉE�����ɃA�j���[�V���������Z�b�g
		if (direction != characterNS::DIRECTION::RIGHT)
		{
			direction = characterNS::DIRECTION::RIGHT;
			startFrame = moveRightStartFrame;
			currentFrame = endFrame - currentFrame + moveRightStartFrame;
			endFrame = moveRightEndFrame;
			setRect();
		}
		break;
	case characterNS::UP:
		// ������������Ă��Ȃ���Ώ�����ɃA�j���[�V���������Z�b�g
		if (direction != characterNS::DIRECTION::UP)
		{
			direction = characterNS::DIRECTION::UP;
			startFrame = moveUpStartFrame;
			currentFrame = endFrame - currentFrame + moveUpStartFrame;
			endFrame = moveUpEndFrame;
			setRect();
		}
		break;
	case characterNS::DOWN:
		// �������������Ă��Ȃ���Ή������ɃA�j���[�V���������Z�b�g
		if (direction != characterNS::DIRECTION::DOWN)
		{
			direction = characterNS::DIRECTION::DOWN;
			startFrame = moveDownStartFrame;
			currentFrame = endFrame - currentFrame + moveDownStartFrame;
			endFrame = moveDownEndFrame;
			setRect();
		}
		break;
	default:
		break;
	}
}

//==========================================================
// �ړ����ւƏ�Ԃ�J��
//==========================================================
void Character::changeStateToMove()
{
	// ��Ԃ͈ړ����ւƑJ��
	state = characterNS::MOVE;
	// �A�j���[�V�����t���[���̑J�ڂ͐�������
	mode = imageNS::HORIZONTAL;
	// �ړ����̓A�j���[�V�����̓��[�v������
	loop = true;
	// �A�j���[�V�����������Ă�������ɍ��킹�ăZ�b�g
	startFrame = oldStartFrame;
	endFrame = oldEndFrame;
	setCurrentFrame(startFrame);
}