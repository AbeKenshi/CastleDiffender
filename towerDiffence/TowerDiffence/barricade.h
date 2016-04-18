//==========================================================
/// @file
/// @brief    Barricade�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#ifndef _BARRICADE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BARRICADE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "hitEffect.h"

// Barricade�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace barricadeNS
{
	const int WIDTH = 32;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;			// �摜�̍���
	const int TEXTURE_COLS = 8;		// �e�N�X�`����8��
	const int START_FRAME = 0;		// �A�j���[�V�����̓t���[��0����J�n
	const int END_FRAME = 2;		// �A�j���[�V�����t���[����0�A1�A2
}

class Barricade : public Entity		// Entity�N���X���p��
{
private:
	float timeCounter;				// �_���[�W�A�j���[�V�����p�̃^�C�}�[
	float totalTimeCounter;			// �_���[�W�A�j���[�V�����p�̃^�C�}�[
	HitEffect hitEffect;			// �U�����q�b�g�����Ƃ��̃A�j���[�V�����摜
public:
	// �R���X�g���N�^
	Barricade();

	//==========================================================
	// �p�����ꂽ�����o�֐�
	//==========================================================
	// Update
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
	void update(float frameTime);
	// �_���[�W����
	// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
	void damage(WEAPON);

	//==========================================================
	// �V�����ǉ����郁���o�[�֐�
	//==========================================================

	//==========================================================
	// setter
	//==========================================================
	// �_���[�W���󂯂�Ƃ��̔{�����Z�b�g
	void setDamagerPer(float per) { damagePer = per; }
	
	//==========================================================
	// getter
	//==========================================================
	// �U�����q�b�g�����Ƃ��̃A�j���[�V�����摜��߂�
	HitEffect& getHitEffect() { return hitEffect; }

};
#endif // !_BARRICADE_H
