#ifndef _BRAVE_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _BRAVE_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace braveNS
{
	const int WIDTH = 24;							// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;							// �摜�̍���
	const int X = GAME_WIDTH / 2 - WIDTH / 2;		// ��ʏ�̈ʒu
	const int Y = GAME_HEIGHT / 6 - HEIGHT;
	const int MOVE_SPEED = 100;						// �ړ����x�i�s�N�Z���j
	enum DIRECTION { NONE, LEFT, RIGHT, UP, DOWN};	// ��]�̕���
	const int TEXTURE_COLS = 12;					// �e�N�X�`����6 * 4��
	const int MOVE_UP_START_FRAME = 0;				// ������ړ��̃A�j���[�V�����̓t���[��0����J�n
	const int MOVE_UP_END_FRAME = 5;				// ������ړ��̃A�j���[�V�����t���[����0�A1�A2�A3�A4�A5
	const int MOVE_RIGHT_START_FRAME = 12;			// �E�����ړ��̃A�j���[�V�����̓t���[��12����J�n
	const int MOVE_RIGHT_END_FRAME = 17;			// �E�����ړ��̃A�j���[�V�����t���[����12�A13�A14�A15�A16�A17
	const int MOVE_DOWN_START_FRAME = 24;			// �������ړ��̃A�j���[�V�����̓t���[��24����J�n
	const int MOVE_DOWN_END_FRAME = 29;				// �������ړ��̃A�j���[�V�����t���[����24�A25�A26�A27�A28�A29
	const int MOVE_LEFT_START_FRAME = 36;			// �������ړ��̃A�j���[�V�����̓t���[��36����J�n
	const int MOVE_LEFT_END_FRAME = 41;				// �������ړ��̃A�j���[�V�����t���[����36�A37�A38�A39�A40�A41
	const float MOVE_ANIMATION_DELAY = 0.2f;		// �ړ��A�j���[�V�����̃t���[���Ԃ̎���
	
}

// Brave�N���X
class Brave : public Entity
{
private:
	braveNS::DIRECTION direction;	// ����
public:
	// �R���X�g���N�^
	Brave();

	// �p�����ꂽ�����o�[�֐�
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
 };
#endif
