#ifndef _ENEMY_COLLISION_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_COLLISION_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "brave.h"
#include "enemy.h"

namespace enemyAttackCollisionNS
{
	const int WIDTH = 24;				// �摜�̕��i�e�t���[���j
	const int HEIGHT = 48;				// �摜�̍���
	const int COLLISION_RADIUS = 4;		// �~�̏Փ˔���
	const float COLLISION_TIME = 0.3f;	// �U���̓����蔻�肪�o�Ă��鎞��
}

class EnemyAttackCollision : public Entity
{
private:
	float collisionTimer;				// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
public:
	// �R���X�g���N�^
	EnemyAttackCollision();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);

	// �V���������o�[�֐�
	void attack(Enemy *enemy);	// �G���G����̍U��
};

#endif // !_ATTACK_COLLISION_H
