//==========================================================
/// @file
/// @brief    braveIcon.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#include "braveIcon.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
BraveIcon::BraveIcon() : Image()
{
	spriteData.width = braveIconNS::WIDTH;			// �E�҂̃A�C�R���̃T�C�Y
	spriteData.height = braveIconNS::HEIGHT;
	spriteData.x = braveIconNS::X;					// ��ʏ�̈ʒu
	spriteData.y = braveIconNS::Y;
	spriteData.rect.bottom = braveIconNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveIconNS::WIDTH;
	startFrame = braveIconNS::START_FRAME;			// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = braveIconNS::END_FRAME;				// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
// �v���C���[�̗̑͂ɉ����āA�A�j���[�V�����𕪊�
//=============================================================================	
void BraveIcon::update(float frameTime)
{
	// �v���C���[�̗̑͂ɉ����āA�A�j���[�V�����𕪊�
	if (currentFrame == startFrame && brave->getHealth() < 75)
		setCurrentFrame(startFrame + 1);
	if (currentFrame == startFrame + 1 && brave->getHealth() < 50)
		setCurrentFrame(startFrame + 2);
	if (currentFrame == startFrame + 2 && brave->getHealth() < 25)
		setCurrentFrame(startFrame + 3);
}

//==========================================================
// �p�����[�^���Z�b�g
//==========================================================
void BraveIcon::reset()
{
	// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	setCurrentFrame(startFrame);
}
