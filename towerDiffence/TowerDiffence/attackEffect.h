#ifndef _ATTACK_EFFECT_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�A
#define _ATTACK_EFFECT_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "brave.h"

namespace attackEffectNS
{
	const int WIDTH = 96;	// �摜�̕��i�e�t���[���j
	const int HEIGHT = 96;	// �摜�̍���
	const int TEXTURE_COLS = 5;
	const int START_FRAME = 0;
	const int END_FRAME = 3;
	const float ANIMATION_DELAY = 0.05f;	// �A�j���[�V�����̃t���[���Ԃ̎���
}

class AttackEffect : public Image
{
public:
	// �R���X�g���N�^
	AttackEffect();

	// Update
	void update(float frameTime);

	// Attack
	void attack(Brave &brave);
};
#endif // !_ATTACK_EFFECT_H
