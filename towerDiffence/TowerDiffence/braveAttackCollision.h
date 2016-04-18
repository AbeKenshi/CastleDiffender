//==========================================================
/// @file
/// @brief    BraveAttackCollision�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _ATTACK_COLLISION_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ATTACK_COLLISION_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "attackEffect.h"

// BraveAttackCollision�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace braveAttackCollisionNS
{
	const int WIDTH = 24;				// �摜�̕��i�e�t���[���j
	const int HEIGHT = 96;				// �摜�̍���
	const float COLLISION_TIME = 0.3f;	// �U���̓����蔻�肪�o�Ă��鎞��
}

class BraveAttackCollision : public Entity
{
private:
	float collisionTimer;			// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
	AttackEffect attackEffect;		// �U���̏Ռ��h
public:
	// �R���X�g���N�^
	BraveAttackCollision();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);

	// �V���������o�[�֐�
	// Attack
	// �E�҂���U���𔭓�
	// �w�肵���ʒu�ɂ��̃G���e�B�e�B���A�N�e�B�u�ɂ��ďo��������
	void attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction);

	//==========================================================
	// getter
	//==========================================================
	// �U���̏Ռ��h�̉摜��߂�
	AttackEffect& getAttackEffect() { return attackEffect; }
};

#endif // !_ATTACK_COLLISION_H
