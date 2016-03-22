#ifndef _FILE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _FILE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "brave.h"
#include "constants.h"

namespace fireNS
{
	const int WIDTH = 24;							// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;							// �摜�̍���
	const int COLLISION_RADIUS = 4;					// �~�̏Փ˔���
	const float SPEED = 200;						// 1�b������̃s�N�Z����
	const float FIRE_DELAY = 1.0f;					// �������̊Ԋu��4�b
	const int TEXTURE_COLS = 12;					// �e�N�X�`����8��
	const int START_FRAME = 52;						// �A�j���[�V�����̓t���[��52����J�n
	const int END_FRAME = 52 + 36;					// �A�j���[�V�����t���[����52�A64�A76�A88
	const float ANIMATION_DELAY = 0.1f;				// �t���[���Ԃ̎���
}

class Fire : public Entity							// Entity�N���X���p��
{
private:
	float fireTimer;								// ���˂��\�ɂȂ�܂ł̎c�莞��
public:
	// �R���X�g���N�^
	Fire();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);

	// �V���������o�[�֐�
	void fire(Brave *brave);		// �E�҂���~�T�C���𔭎�
};
#endif // !_FILE_H
