//==========================================================
/// @file
/// @brief    hpTextImage.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "hpTextImage.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
HpTextImage::HpTextImage() : Image()
{
	mSpriteData.width = hpTextImageNS::WIDTH;		// �e�L�X�g�摜�̃T�C�Y
	mSpriteData.height = hpTextImageNS::HEIGHT;
	mSpriteData.x = hpTextImageNS::X;				// ��ʏ�̏����ʒu
	mSpriteData.y = hpTextImageNS::Y;
	mSpriteData.rect.bottom = hpTextImageNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	mSpriteData.rect.right = hpTextImageNS::WIDTH;
	mStartFrame = hpTextImageNS::START_FRAME;		// �A�j���[�V�����̍ŏ��̃t���[��
	mEndFrame = mStartFrame;							// �A�j���[�V�����̍Ō�̃t���[��
	mCurrentFrame = mStartFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
}