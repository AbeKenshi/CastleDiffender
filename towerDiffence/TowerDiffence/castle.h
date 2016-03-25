#ifndef _CASTLE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CASTLE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "entity.h"
#include "constants.h"

namespace castleNS
{
	const int WIDTH = 96;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 96;			// �摜�̍���
	const int X = 18.3 * 30;	// �����ʒu
	const int Y = 9.5 * 30;
	const int COLLISION_RADIUS = 10;// �~�̏Փ˔���	
	const int START_FRAME = 0;
}

class Castle : public Entity		// Entity�N���X���p��
{
public:
	// �R���X�g���N�^
	Castle();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);
};

#endif // !_CASTLE_H
