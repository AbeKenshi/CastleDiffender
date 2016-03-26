#include "MpTextImage.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
MpTextImage::MpTextImage() : Image()
{
	spriteData.width = mpTextImageNS::WIDTH;	// �e�L�X�g�摜�̃T�C�Y
	spriteData.height = mpTextImageNS::HEIGHT;
	spriteData.x = mpTextImageNS::X;			// ��ʏ�̏����ʒu
	spriteData.y = mpTextImageNS::Y;
	spriteData.rect.bottom = mpTextImageNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = mpTextImageNS::WIDTH;
	startFrame = mpTextImageNS::START_FRAME;
	endFrame = startFrame;
	currentFrame = startFrame;
}