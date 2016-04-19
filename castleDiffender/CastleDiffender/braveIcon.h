//==========================================================
/// @file
/// @brief    BraveIcon�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _BRAVE_ICON_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BRAVE_ICON_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"
#include "brave.h"

// BraveIcon�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace braveIconNS
{
	const int WIDTH = 48;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 48;			// �摜�̍���
	const int X = 10;				// �����ʒu
	const int Y = 0;
	const int TEXTURE_COLS = 4;		// �e�N�X�`����4��
	const int START_FRAME = 0;		// �A�j���[�V�����̓t���[��0����J�n
	const int END_FRAME = 3;		// �A�j���[�V�����t���[����0�A1�A2�A3
}

class BraveIcon : public Image
{
private:
	Brave *mBrave;	// �E�҂ւ̃|�C���^�B�I�u�W�F�N�g�͂��̃N���X�O�Ő��������̂Ńf�X�g���N�^�͕K�v�Ȃ��B
public:
	// �R���X�g���N�^
	BraveIcon();

	// �p�����ꂽ�����o�[�֐�
	// update
	void update(float frameTime);
	// �p�����[�^���Z�b�g
	// roundStart()���ŌĂяo�����
	void reset();
	
	// �V���������o�[�֐�
	// Entity�I�u�W�F�N�g�ƃ����N������B
	// initialize�֐��̒���ɌĂяo���B
	void linkEntity(Brave& brv) { mBrave = &(brv); }
};
#endif // !_BRAVE_ICON_H
