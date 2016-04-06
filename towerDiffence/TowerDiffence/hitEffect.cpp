#include "hitEffect.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
HitEffect::HitEffect() : Image()
{
	visible = false;							// ��\�����f�t�H���g
	spriteData.width = hitEffectNS::WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = hitEffectNS::HEIGHT;
	spriteData.rect.bottom = hitEffectNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = hitEffectNS::WIDTH;
	cols = hitEffectNS::TEXTURE_COLS;
	frameDelay = hitEffectNS::ANIMATION_DELAY;
	// �A�j���[�V�����̍ŏ��̃t���[��
	startFrame = hitEffectNS::START_FRAME;
	// �A�j���[�V�����̍Ō�̃t���[��
	endFrame = hitEffectNS::END_FRAME;
	currentFrame = startFrame;
	setScale(0.5);
	loop = false;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void HitEffect::update(float frameTime)
{
	if (visible == false)
		return;
	Image::update(frameTime);
	if (animComplete)
		visible = false;
}

//==========================================================
// Hit
// ���̊֐����Ă΂��ƍU�����q�b�g�����Ƃ��̃G�t�F�N�g������
//==========================================================
void HitEffect::hit(float x, float y)
{
	spriteData.x = x - spriteData.width * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	spriteData.y = y - spriteData.height * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	visible = true;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
}