#ifndef _BARRICADE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BARRICADE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace barricadeNS
{
	const int WIDTH = 32;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;			// �摜�̍���
	const int COLLISION_RADIUS = 4;	// �~�̏Փ˔���
	const int TEXTURE_COLS = 8;		// �e�N�X�`����8��
	const int START_FRAME = 0;		// �A�j���[�V�����̓t���[��0����J�n
	const int END_FRAME = 2;		// �A�j���[�V�����t���[����0�A1�A2
}

class Barricade : public Entity		// Entity�N���X���p��
{
public:
	// �R���X�g���N�^
	Barricade();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);
};
#endif // !_BARRICADE_H
