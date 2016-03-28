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
	// �_���[�W�͎󂯂Ă��Ȃ���Ԃ���X�^�[�g
	isDamaged = false;
	// �_���[�W���Ɏg�p����^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
	// �`��t���O�̓I��
	drawFlag = true;
	// �U������̃R���W�����͍ŏ��͂Ȃ�
	attackCollisionFlag = false;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Character::reset()
{
	// �L�����N�^�[���A�N�e�B�u�ɂ���
	active = true;
	visible = true;
	// �̗͂�MAX100
	health = 100;
	// �����̕����͉E
	direction = characterNS::RIGHT;
	// �_���[�W�͎󂯂Ă��Ȃ���ԂɃ��Z�b�g
	isDamaged = false;
	// �_���[�W���Ɏg�p����^�C�}�[�����Z�b�g
	damageTimer = 0.0f;
	totalDamageTime = 0.0f;
	// �`��t���O���I���Ƀ��Z�b�g
	drawFlag = true;
	// �U������̃R���W�����͂Ȃ��Ń��Z�b�g
	attackCollisionFlag = false;
}

//==========================================================
// �L�����N�^�[��`��
// �`��t���O���I���̂Ƃ��̂ݕ`��
//==========================================================
void Character::draw()
{
	// �`��t���O���I���̂Ƃ��̂ݕ`��
	if (drawFlag)
		Image::draw();	// �G���G��`��
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