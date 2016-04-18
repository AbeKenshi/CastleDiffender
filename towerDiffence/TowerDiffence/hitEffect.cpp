//==========================================================
/// @file
/// @brief    hitEffect.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "hitEffect.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
HitEffect::HitEffect() : Image()
{
	visible = false;								// ��\�����f�t�H���g
	spriteData.width = hitEffectNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = hitEffectNS::HEIGHT;
	spriteData.rect.bottom = hitEffectNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = hitEffectNS::WIDTH;
	cols = hitEffectNS::TEXTURE_COLS;				// �e�N�X�`���̗�
	frameDelay = hitEffectNS::ANIMATION_DELAY;		// �A�j���[�V�����̊e�t���[���̊Ԋu
	startFrame = hitEffectNS::START_FRAME;			// �A�j���[�V�����̍ŏ��̃t���[��
	endFrame = hitEffectNS::END_FRAME;				// �A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;						// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	setScale(0.5);									// �X�P�[��
	loop = false;									// �A�j���[�V�����̓��[�v�����Ȃ�
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void HitEffect::update(float frameTime)
{
	// ��\�����ɂ͉������Ȃ�
	if (visible == false)
		return;
	// �摜���X�V
	Image::update(frameTime);
	// �A�j���[�V�������I�������ꍇ�A��\���ɂ���
	if (animComplete)
		visible = false;
}

//==========================================================
// Hit
// ���̊֐����Ă΂��ƍU�����q�b�g�����Ƃ��̃G�t�F�N�g������
//==========================================================
void HitEffect::hit(float x, float y)
{
	// �w�肳�ꂽ���W�̎l���Ƀ����_���ɕ\��
	spriteData.x = x - spriteData.width * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	spriteData.y = y - spriteData.height * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	visible = true;
	setCurrentFrame(startFrame);
}