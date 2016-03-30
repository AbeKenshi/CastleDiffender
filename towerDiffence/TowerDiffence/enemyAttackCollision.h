#ifndef _ENEMY_COLLISION_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_COLLISION_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "brave.h"
#include "enemy.h"

namespace enemyCollisionNS
{
	const int ATTACK_WIDTH = 32;				// �摜�̕��i�e�t���[���j
	const int ATTACK_HEIGHT = 1;				// �摜�̍���
	const int WALK_WIDTH = 2;
	const int WALK_HEIGHT = 24;
	const float COLLISION_TIME = 0.3f;	// �U���̓����蔻�肪�o�Ă��鎞��
}

class EnemyCollision : public Entity
{
private:
	float collisionTimer;				// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
public:
	// �R���X�g���N�^
	EnemyCollision();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);

	// �V���������o�[�֐�
	void attack(Enemy *enemy);	// �G���G����̍U��
	void walk(Enemy *enemy);
};

#endif // !_ATTACK_COLLISION_H
