#include "attackEffect.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
AttackEffect::AttackEffect() : Image()
{
	visible = false;							// ��\�����f�t�H���g
	spriteData.width = attackEffectNS::WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = attackEffectNS::HEIGHT;
	spriteData.rect.bottom = attackEffectNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = attackEffectNS::WIDTH;
	cols = attackEffectNS::TEXTURE_COLS;
	frameDelay = attackEffectNS::ANIMATION_DELAY;
	// �A�j���[�V�����̍ŏ��̃t���[��
	startFrame = attackEffectNS::START_FRAME;
	// �A�j���[�V�����̍Ō�̃t���[��
	endFrame = attackEffectNS::END_FRAME;
	currentFrame = startFrame;
	spriteData.scale = 0.8f;
	loop = false;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void AttackEffect::update(float frameTime)
{
	if (visible == false)
		return;
	Image::update(frameTime);
	if (animComplete)
		visible = false;
}

//==========================================================
// Attack
// ���̊֐����Ă΂��ƍU���̏Ռ��g�̃A�j���[�V����������
//==========================================================
void AttackEffect::attack(Brave &brave)
{
	switch (brave.getDirection())
	{
	case characterNS::RIGHT:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10;
		setDegrees(0);
		flipHorizontal(false);
		break;
	case characterNS::LEFT:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10;
		setDegrees(0);
		flipHorizontal(true);
		break;
	case characterNS::UP:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10 - 10;
		setDegrees(40.0f);
		flipHorizontal(true);
		break;
	case characterNS::DOWN:
		spriteData.x = brave.getCenterX() - spriteData.width * spriteData.scale / 2.0f - 10;
		spriteData.y = brave.getCenterY() - spriteData.height * spriteData.scale / 2.0f - 10 + 10;
		setDegrees(230.0f);
		flipHorizontal(true);
		break;
	}
	visible = true;
	currentFrame = startFrame;
	animTimer = 0.0f;
	animComplete = false;
	setRect();
}