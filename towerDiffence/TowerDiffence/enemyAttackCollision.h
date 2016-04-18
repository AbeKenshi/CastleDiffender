//==========================================================
/// @file
/// @brief    EnemyAttackCollision�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _ENEMY_COLLISION_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_COLLISION_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "character.h"

// EnemyAttackCollision�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace enemyCollisionNS
{
	const int ATTACK_WIDTH = 10;		// �摜�̕��i�e�t���[���j
	const int ATTACK_HEIGHT = 32;		// �摜�̍���
	const float COLLISION_TIME = 0.3f;	// �U���̓����蔻�肪�o�Ă��鎞��
}

class EnemyCollision : public Entity
{
private:
	float mCollisionTimer;				// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
public:
	// �R���X�g���N�^
	EnemyCollision();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);

	// �V���������o�[�֐�
	// Attack
	// �G����̍U��
	// �w�肵���ʒu�ɂ��̃G���e�B�e�B���A�N�e�B�u�ɂ��ďo��������
	void attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction);
};

#endif // !_ATTACK_COLLISION_H
