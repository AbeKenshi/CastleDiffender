#ifndef _HIT_EFFECT_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _HIT_EFFECT_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"

namespace hitEffectNS
{
	const int WIDTH = 108;				// �摜�̕��i�e�t���[���j
	const int HEIGHT = 108;				// �摜�̍���
	const int TEXTURE_COLS = 3;			// �e�N�X�`����3��
	const int START_FRAME = 0;			// �A�j���[�V�����̓t���[��0����J�n
	const int END_FRAME = 2;			// �A�j���[�V�����t���[����0�A1�A2
	const float ANIMATION_DELAY = 0.1;	// �A�j���[�V�����̃t���[���Ԃ̎���
}

class HitEffect : public Image
{
public:
	// �R���X�g���N�^
	HitEffect();

	// Update
	void update(float frameTime);

	// Hit
	void hit(float x, float y);
};
#endif // !_ATTACK_EFFECT_H
