#ifndef _HP_TEXT_IMAGE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _HP_TEXT_IMAGE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"

namespace hpTextImageNS
{
	const int WIDTH = 40;		// �摜�̕��i�e�t���[���j
	const int HEIGHT = 20;		// �摜�̍���
	const int X = 60;			// �����ʒu
	const int Y = 5;
	const int TEXTURE_COLS = 5;	// �e�N�X�`����5��
	const int START_FRAME = 15;	// �A�j���[�V�����̓t���[��15����J�n
}

class HpTextImage : public Image
{
public:
	// �R���X�g���N�^
	HpTextImage();
};
#endif // !_HP_TEXT_IMAGE_H
