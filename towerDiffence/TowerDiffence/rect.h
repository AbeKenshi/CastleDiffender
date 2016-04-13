// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// console.h v1.0

#ifndef _RECT_H              // Prevent multiple definitions if this 
#define _RECT_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

namespace rectNS
{
	const UINT WIDTH = GAME_WIDTH;     // ��`�̕��i�s�N�Z���P�ʁj
	const UINT HEIGHT = 50;            // ��`�̍����i�s�N�Z���P�ʁj
	const UINT X = 0;                  // ���������̉�ʈʒu
	const UINT Y = 0;
	const COLOR_ARGB BACK_COLOR = graphicsNS::BLACK;
}

// �P���Ȏl�p�`�N���X
class Rect
{
private:
	Graphics    *graphics;              // graphics system
	float       x, y;                   // console location (dynamic)
	int width, height;					// ���A�����i�s�N�Z���P�ʁj
	COLOR_ARGB  backColor;              // background color (a,r,g,b)
	VertexC vtx[4];                     // vertex data for background
	LP_VERTEXBUFFER vertexBuffer;       // buffer to hold vertex data
	bool        initialized;            // true when initialized successfully

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

	// Call when graphics device is lost.
	void onLostDevice();

	// Call when graphics device is reset.
	void onResetDevice();

	void reset();
	// setter
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }

	// getter
	float getX() { return x; }
	float getY() { return y; }
	// �w�i�F���Z�b�g
	void setBackColor(COLOR_ARGB clr) { backColor = clr; }
};

#endif

