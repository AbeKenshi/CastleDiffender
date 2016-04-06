#ifndef _ATTACK_COLLISION_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ATTACK_COLLISION_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "brave.h"
#include "enemy.h"
#include "attackEffect.h"

namespace braveAttackCollisionNS
{
	const int WIDTH = 24;				// �摜�̕��i�e�t���[���j
	const int HEIGHT = 96;				// �摜�̍���
	const int COLLISION_RADIUS = 4;		// �~�̏Փ˔���
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
	void attack(Brave &brave);	// �E�҂���̍U��

	//==========================================================
	// getter
	//==========================================================
	AttackEffect& getAttackEffect() { return attackEffect; }
};

#endif // !_ATTACK_COLLISION_H
