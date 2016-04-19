//==========================================================
/// @file
/// @brief    CastleIcon�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _CASTLE_ICON_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CASTLE_ICON_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"

// CastleIcon�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace castleIconNS
{
	const int WIDTH = 48;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 48;			// �摜�̍���
	const int X = 780;				// �����ʒu
	const int Y = 0;
	const int TEXTURE_COLS = 1;		// �e�N�X�`����1��
	const int START_FRAME = 1;		// �A�j���[�V�����̓t���[��1����J�n
}

class CastleIcon : public Image
{
public:
	// �R���X�g���N�^
	CastleIcon();
};
#endif // !_BRAVE_ICON_H