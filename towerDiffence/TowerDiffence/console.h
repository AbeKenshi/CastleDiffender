//==========================================================
/// @file
/// @brief    Console�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _CONSOLE_H              // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CONSOLE_H              // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

namespace consoleNS
{
    const UINT WIDTH = 1000;										// �R���\�[���̋�`�̕��i�s�N�Z���P�ʁj
    const UINT HEIGHT = 400;										// �R���\�[���̋�`�̍����i�s�N�Z���P�ʁj
    const UINT X = 5;												// �R���\�[���̍��������̉�ʈʒu
    const UINT Y = 5;
    const UINT MARGIN = 4;											// �R���\�[���̒[����e�L�X�g�܂ł̗]��
    const char FONT[] = "Courier New";								// �R���\�[���̃e�L�X�g�Ɏg�p����t�H���g
    const int FONT_HEIGHT = 14;										// �R���\�[���̃t�H���g�̍���
    const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;				// �R���\�[���̃t�H���g�̐F
    const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192,128,128,128);   // �R���\�[���̔w�i�̐F
    const int MAX_LINES = 256;										// �e�L�X�g�o�b�t�@���̕\���\�ȃe�L�X�g�̍ő�s��
}

// 
class Console
{
private:
    Graphics    *graphics;              // �O���t�B�b�N�V�X�e���ւ̃|�C���^
    Input       *input;                 // ���̓V�X�e���ւ̃|�C���^
    TextDX      dxFont;                 // DirectX�t�H���g
    float       x,y;                    // �R���\�[���̈ʒu
    int         rows;                   // �R���\�[���Ɏ��܂�e�L�X�g�̍s��
    std::string commandStr;             // �R���\�[���R�}���h
    std::string inputStr;               // �R���\�[���ւ̓��̓e�L�X�g
    std::deque<std::string> text;       // �f�b�Ntext
    RECT        textRect;               // �e�L�X�g�\��rect
    COLOR_ARGB  fontColor;              // �t�H���g�J���[(a,r,g,b)
    COLOR_ARGB  backColor;              // �w�i�F(a,r,g,b)
    VertexC vtx[4];                     // �w�i�p��vertex�f�[�^
    LP_VERTEXBUFFER vertexBuffer;       // vertex�f�[�^�ۑ��p�̃o�b�t�@
    int         scrollAmount;           // �X�N���[������Ă���s��
    bool        initialized;            // �������ɐ��������ꍇ�Atrue
    bool        visible;                // �R���\�[����\��������ꍇ�Atrue

public:
	// �R���X�g���N�^
    Console();

	// �f�X�g���N�^
    virtual ~Console();

	// �R���\�[����������
    bool initialize(Graphics *g, Input *in);

	// �R���\�[����`��
	// ���s�O�FBeginScene��EndScene�̓����ɂ���
    const void draw();

	// �R���\�[���̕\��/��\���𐧌䂷��v���p�e�B�𔽓]�����܂��B
	// �\������Ă���R���\�[���͔�\���ɂȂ�A
	// ��\���̃R���\�[���͕\�������悤�ɂȂ�܂��B
    void showHide();

	// �\��/��\���𐧌䂷��v���p�e�B�̌��݂̏�Ԃ�߂��܂��B
    bool getVisible() {return visible;}

	// �R���\�[����\�����܂��B
    void show() {visible = true;}

	// �R���\�[�����\���ɂ��܂��B
    void hide() {visible = false;}

	// �R���\�[���f�B�X�v���C�Ƀe�L�X�g�������ǉ����܂��B
    void print(const std::string &str);

	// �V���O���L�[�̃R���\�[���R�}���h���������܂��B
	// ���[�U�[�����͂����R�}���h�������߂��܂��B
    std::string getCommand();

	// �R���\�[���̓��̓e�L�X�g��߂��܂�
    std::string getInput() {return inputStr;}

	// �R���\�[���̓��̓e�L�X�g���N���A���܂�
    void clearInput()   {inputStr = "";}

	// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
    void onLostDevice();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo�����
    void onResetDevice();
};

#endif

