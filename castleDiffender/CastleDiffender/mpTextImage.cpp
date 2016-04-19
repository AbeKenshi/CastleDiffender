//==========================================================
/// @file
/// @brief    mpTextImage.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "MpTextImage.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
MpTextImage::MpTextImage() : Image()
{
	mSpriteData.width = mpTextImageNS::WIDTH;		// �e�L�X�g�摜�̃T�C�Y
	mSpriteData.height = mpTextImageNS::HEIGHT;
	mSpriteData.x = mpTextImageNS::X;				// ��ʏ�̏����ʒu
	mSpriteData.y = mpTextImageNS::Y;
	mSpriteData.rect.bottom = mpTextImageNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	mSpriteData.rect.right = mpTextImageNS::WIDTH;
	mStartFrame = mpTextImageNS::START_FRAME;		// �A�j���[�V�����̍ŏ��̃t���[��	
	mEndFrame = mStartFrame;							// �A�j���[�V�����̍Ō�̃t���[��
	mCurrentFrame = mStartFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
}