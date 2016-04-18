//==========================================================
/// @file
/// @brief    MpTextImage�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _MP_TEXT_IMAGE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _MP_TEXT_IMAGE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"

// MpTextImage�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace mpTextImageNS
{
	const int WIDTH = 40;		// �摜�̕��i�e�t���[���j
	const int HEIGHT = 20;		// �摜�̍���
	const int X = 60;			// �����ʒu
	const int Y = 30;
	const int TEXTURE_COLS = 5;	// �e�N�X�`����5��
	const int START_FRAME = 20;	// �A�j���[�V�����̓t���[��15����J�n
}

class MpTextImage : public Image
{
public:
	// �R���X�g���N�^
	MpTextImage();
};
#endif // !_MP_TEXT_IMAGE_H
