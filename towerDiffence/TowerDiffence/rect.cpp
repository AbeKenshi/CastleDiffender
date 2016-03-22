// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// console.cpp v1.0

#include "rect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Rect::Rect()
{
	initialized = false;                // ����ɏ��������ꂽ�ꍇ�Atrue��ݒ�
	graphics = NULL;
	backColor = rectNS::BACK_COLOR;

	x = rectNS::X;                   // �ŏ��̎l�p�`�̈ʒu
	y = rectNS::Y;

	vertexBuffer = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Rect::~Rect()
{
	onLostDevice();
}

//=============================================================================
// Rect��������
//=============================================================================
bool Rect::initialize(Graphics *g)
{
	try {
		graphics = g;                    // �O���t�B�b�N�V�X�e��

		// ����
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// �E��
		vtx[1].x = x + rectNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// �E��
		vtx[2].x = x + rectNS::WIDTH;
		vtx[2].y = y + rectNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// ����
		vtx[3].x = x;
		vtx[3].y = y + rectNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

	}
	catch (...) {
		return false;
	}

	initialized = true;
	return true;
}

//=============================================================================
// �l�p�`��`��
// ���s�O�FBeginScene��EndScene�̓����ɂ���
//=============================================================================
const void Rect::draw()
{
	graphics->drawQuad(vertexBuffer);       // �w�i��`��

	graphics->spriteBegin();                // �X�v���C�g�̕`����J�n

	graphics->spriteEnd();                      // �X�v���C�g�̕`����I��
}

//=============================================================================
// called when graphics device is lost
//=============================================================================
void Rect::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(vertexBuffer);
}

//=============================================================================
// called when graphics device is reset
//=============================================================================
void Rect::onResetDevice()
{
	if (!initialized)
		return;
	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
}

