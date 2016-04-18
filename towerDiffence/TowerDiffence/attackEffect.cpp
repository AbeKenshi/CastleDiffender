//==========================================================
/// @file
/// @brief    attackEffect.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#include "attackEffect.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
AttackEffect::AttackEffect() : Image()
{
	visible = false;								// ��\�����f�t�H���g
	spriteData.width = attackEffectNS::WIDTH;		// �P�̉摜�̃T�C�Y
	spriteData.height = attackEffectNS::HEIGHT;
	spriteData.rect.bottom = attackEffectNS::HEIGHT;// �摜���̑I�����镔��
	spriteData.rect.right = attackEffectNS::WIDTH;
	cols = attackEffectNS::TEXTURE_COLS;			// �e�N�X�`���̗�
	frameDelay = attackEffectNS::ANIMATION_DELAY;	// �A�j���[�V�����̊e�t���[���̊Ԋu
	startFrame = attackEffectNS::START_FRAME;		// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = attackEffectNS::END_FRAME;			// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	spriteData.scale = attackEffectNS::SCALE;		// �X�v���C�g�̃X�P�[��
	loop = false;									// �A�j���[�V�����̓��[�v�����Ȃ�
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void AttackEffect::update(float frameTime)
{
	// �X�v���C�g����\���Ȃ牽�����Ȃ�
	if (getVisible() == false)
		return;
	// �摜���X�V
	Image::update(frameTime);
	// �A�j���[�V�������I�������ꍇ�A�X�v���C�g���\���ɂ���
	if (getAnimationComplete())
		setVisible(false);
}

//==========================================================
// Attack
// ���̊֐����Ă΂��ƍU���̏Ռ��g�̃A�j���[�V����������
//==========================================================
void AttackEffect::attack(Brave &brave)
{
	// brave�i�v���C���[�j�̌����ɂ���ĕ\��������ʒu�𕪊�
	// �v���C���[�̌��X�̉摜���΂��Ă���̂ŁA�}10���x�̕␳�������Ă���
	switch (brave.getDirection())
	{
	case characterNS::RIGHT:	// �E
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10);
		setDegrees(0);
		flipHorizontal(false);
		break;
	case characterNS::LEFT:		// ��
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10);
		setDegrees(0);
		flipHorizontal(true);
		break;
	case characterNS::UP:		// ��
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10 - 10);
		setDegrees(40.0f);
		flipHorizontal(true);
		break;
	case characterNS::DOWN:		// ��
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10 + 10);
		setDegrees(230.0f);
		flipHorizontal(true);
		break;
	}
	// �X�v���C�g��\��
	visible = true;
	// ���݂̃t���[�����A�j���[�V�����̍ŏ��̃t���[���ɃZ�b�g
	setCurrentFrame(startFrame);
}