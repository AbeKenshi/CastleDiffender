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
	// �_���[�W���Ɏg�p����^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
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
	oldStartFrame = startFrame;
	oldEndFrame = endFrame;
	// �����̕����͉E
	direction = characterNS::RIGHT;
	// �_���[�W���Ɏg�p����^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
	// �U������̃R���W�����͂Ȃ��Ń��Z�b�g
	attackCollisionFlag = false;
	// ��Ԃ͉������Ȃ���Ԃ���X�^�[�g
	state = characterNS::STATE::MOVE;
	Entity::reset();
}

//==========================================================
// �L�����N�^�[��`��
// �`��t���O���I���̂Ƃ��̂ݕ`��
//==========================================================
void Character::draw(COLOR_ARGB color)
{
	// �`��t���O���I���̂Ƃ��̂ݕ`��
	if (drawFlag)
		Image::draw(color);	// �G���G��`��
}

//==========================================================
// �ړ����̃A�b�v�f�[�g�֐�
//==========================================================
void Character::updateMoving(float frameTime)
{
	// �A�j���[�V�����̃A�b�v�f�[�g�͒P�Ƃōs����̂ł���ȊO���A�b�v�f�[�g
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// �U�����̃A�b�v�f�[�g�֐�
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

	if (map->getMapCol(map_y, map_x) == 1 || map->getMapCol(map_y, map_x) == 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}