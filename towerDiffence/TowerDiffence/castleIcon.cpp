//==========================================================
/// @file
/// @brief    castleIcon.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "castleIcon.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
CastleIcon::CastleIcon() : Image()
{
	spriteData.width = castleIconNS::WIDTH;			// ��̃A�C�R���̃T�C�Y
	spriteData.height = castleIconNS::HEIGHT;
	spriteData.x = castleIconNS::X;					// ��ʏ�̈ʒu
	spriteData.y = castleIconNS::Y;
	spriteData.rect.bottom = castleIconNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = castleIconNS::WIDTH;
	startFrame = castleIconNS::START_FRAME;			// �A�j���[�V�����̍ŏ��̃t���[��
	currentFrame = startFrame;						// ���݂̃t���[�����A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
}

