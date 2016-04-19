//==========================================================
/// @file
/// @brief    Castle�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _CASTLE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CASTLE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B

#include "entity.h"
#include "character.h"
#include "constants.h"


// Castle�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace castleNS
{
	const int WIDTH = 120;			// �摜�̕��i�e�t���[���j
	const int HEIGHT = 120;			// �摜�̍���
	const int TEXTURE_COLS = 2;		// �e�N�X�`����2��
	const int X = 549;				// �����ʒu
	const int Y = 285;
	const int START_FRAME = 1;		// �A�j���[�V�����̍ŏ��̃t���[��
}

class Castle : public Entity		// Entity�N���X���p��
{
private:
	bool death;						// �邪���S����true�Bactive��false�ɂ���ƕ`�悳��Ȃ��Ȃ�̂ŁA����ɂ��̃t���O��p����
public:
	// �R���X�g���N�^
	Castle();

	// �p�����ꂽ�����o�[�֐�
	// update
	void update(float frameTime);
	// �_���[�W����
	// WEAPON�̎�ނɂ���Ď󂯂�_���[�W������
	void damage(WEAPON);
	// �p�����[�^���Z�b�g
	void reset();

	// getter
	// �邪���S���Ă��邩�ǂ�����Ԃ�
	bool isDeath() { return death; }

	// setter
	// �邪���S���Ă��邩�ǂ������Z�b�g
	void setDeath(bool d) { death = d; }
};

#endif // !_CASTLE_H
