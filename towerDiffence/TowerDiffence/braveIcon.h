#ifndef _BRAVE_ICON_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BRAVE_ICON_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "image.h"
#include "constants.h"
#include "brave.h"

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
	Brave *brave;	// �E�҂ւ̃|�C���^�B�I�u�W�F�N�g�͂��̃N���X�O�Ő��������̂Ńf�X�g���N�^�͕K�v�Ȃ��B
public:
	// �R���X�g���N�^
	BraveIcon();

	// �p�����ꂽ�����o�[�֐�
	void update(float frameTime);
	
	// �V���������o�[�֐�
	// Entity�I�u�W�F�N�g�ƃ����N������B
	// initialize�֐��̒���ɌĂяo���B
	void linkEntity(Brave* brv) { brave = brv; }
};
#endif // !_BRAVE_ICON_H
