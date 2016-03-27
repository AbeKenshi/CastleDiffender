#ifndef _BARRICADE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BARRICADE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

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
	float totalTimeCounter;
	bool death;						// �邪���S����true
	bool isDamaged;					// �_���[�W���󂯂Ă����Ԃ��ǂ���
	bool drawFlag;					// �`��t���O�Atrue���ɕ`��
public:
	// �R���X�g���N�^
	Barricade();

	// �p�����ꂽ�����o�[�֐�
	virtual void draw();
	void reset();

	void update(float frameTime);
	void damage();
};
#endif // !_BARRICADE_H
