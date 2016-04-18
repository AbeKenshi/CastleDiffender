//==========================================================
/// @file
/// @brief    AttackEffect�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#ifndef _ATTACK_EFFECT_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�A
#define _ATTACK_EFFECT_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "brave.h"

namespace attackEffectNS
{
	const int WIDTH = 96;					// �摜�̕��i�e�t���[���j
	const int HEIGHT = 96;					// �摜�̍���
	const int TEXTURE_COLS = 5;				// �e�N�X�`����5��
	const int START_FRAME = 0;				// �A�j���[�V�����̓t���[��0����J�n
	const int END_FRAME = 3;				// �A�j���[�V�����t���[����0�A1�A2�A3
	const float ANIMATION_DELAY = 0.05f;	// �A�j���[�V�����̃t���[���Ԃ̎���
	const float SCALE = 0.8f;				// �X�v���C�g�̃X�P�[��
}

class AttackEffect : public Image
{
public:
	// �R���X�g���N�^
	AttackEffect();


	//==========================================================
	// �p�����ꂽ�����o�֐�
	//==========================================================
	// Update
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
	void update(float frameTime);

	//==========================================================
	// �V�����ǉ����郁���o�[�֐�
	//==========================================================
	// Attack
	// ���̊֐����Ă΂��ƍU���̏Ռ��g�̃A�j���[�V����������
	void attack(Brave &brave);
};
#endif // !_ATTACK_EFFECT_H
