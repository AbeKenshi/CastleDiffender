//==========================================================
/// @file
/// @brief    Rect�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _RECT_H              // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _RECT_H              // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

// Rect�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace rectNS
{
	const UINT WIDTH = GAME_WIDTH;						// ��`�̕��i�s�N�Z���P�ʁj
	const UINT HEIGHT = 50;								// ��`�̍����i�s�N�Z���P�ʁj
	const UINT X = 0;									// ���������̉�ʈʒu
	const UINT Y = 0;
	const COLOR_ARGB BACK_COLOR = graphicsNS::BLACK;	// �w�i�̐F
}

// �P���Ȏl�p�`�N���X
class Rect
{
private:
	Graphics    *graphics;              // grapics�ւ̃|�C���^
	float       x, y;                   // rect�̈ʒu
	int width, height;					// ���A�����i�s�N�Z���P�ʁj
	COLOR_ARGB  backColor;              // �w�i�F(a,r,g,b)
	VertexC vtx[4];                     // �w�i�p��vertex�f�[�^
	LP_VERTEXBUFFER vertexBuffer;       // vertex�f�[�^�ۑ��p�̃o�b�t�@
    bool        initialized;            // �������ɐ��������ꍇ�Atrue

public:
	// �R���X�g���N�^
	Rect();

	// �f�X�g���N�^
	virtual ~Rect();

	// Rect�̏�����
	bool initialize(Graphics *g);

	// �l�p�`��`��
	// ���s�O�FBeginScene��EndScene�̓����ɂ���
	const void draw();

	// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
	void onLostDevice();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo�����
	void onResetDevice();

	// �p�����[�^���Z�b�g
	void reset();
	// setter
	// X�ʒu���Z�b�g
	void setX(float nx) { x = nx; }
	// Y�ʒu���Z�b�g
	void setY(float ny) { y = ny; }
	// �����Z�b�g
	void setWidth(int w) { width = w; }
	// �������Z�b�g
	void setHeight(int h) { height = h; }
	// �w�i�F���Z�b�g
	void setBackColor(COLOR_ARGB clr) { backColor = clr; }
	
	// getter
	// X�ʒu��߂�
	float getX() { return x; }
	// Y�ʒu��߂�
	float getY() { return y; }
};

#endif

