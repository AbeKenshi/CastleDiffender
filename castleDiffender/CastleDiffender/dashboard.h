//==========================================================
/// @file
/// @brief    �_�b�V���{�[�h�֘A�̃N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _DASHBOARD_H            // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA 
#define _DASHBOARD_H            // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "image.h"
#include "constants.h"
#include "textureManager.h"
#include "input.h"

// �_�b�V���{�[�h�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace dashboardNS
{
	const int	WIDTH = 48;				// �摜�̕��i�e�t���[���j
	const int	HEGIHT = 48;			// �摜�̍���
    const int   TEXTURE_COLS = 4;       // �e�N�X�`����4��
    const int   BAR_FRAME = 0;          // ���ꂼ��̃e�N�X�`���̃t���[���ԍ�
    const int   DIAL360_FRAME = 1;      // "
    const int   DIAL270_FRAME = 2;      // ...
    const int   DIAL180_FRAME = 3;
    const int   LIGHT_FRAME = 4;
    const int   POINTER_FRAME = 5;
    const int   SEGMENT_FRAME = 6;
    const int   DECIMAL_FRAME = 7;
    const int   SWITCH_OFF_FRAME = 8;
    const int   SWITCH_ON_FRAME = 9;
    const int   BUTTON_UP_FRAME = 10;
    const int   BUTTON_DOWN_FRAME = 11;
    const int   BAR_GRAPH_FRAME = 12;
    const int   SWITCH_WIDTH = 44;      // �g�O���X�C�b�`�̕��i�s�N�Z���P�ʁj
    const int   BAR_GRAPH_WIDTH = 8;    // �_�O���t�̕��{�󂫃X�y�[�X
    enum DialType{DIAL360, DIAL270, DIAL180};
}

class SevenSegment : public Image
{
private:
    Image   mDecimal;	// �Z�u���Z�O�����g�̉摜
    UINT    mDigits;	// ����
    double  mNumber;	// �\�����鐔�l
public:
	// �R���X�g���N�^
    SevenSegment();
	// �Z�u���Z�O�����g�\���̏�����
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   left�Atop = ��ʈʒu
	//         scale = �{���i�Y�[���j
	//		   digits = ����
	//		   color = �����̐F
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT digits, COLOR_ARGB color);
	// �Z�u���Z�O�����g�\���ɕ\�����鐔�l��ݒ�
    void set(double value);
    // update���I�[�o�[���C�h
    virtual void update(float frameTime)    {}
	// �Z�u���Z�O�����g�̐����u0�v�`�u9�v�Ɓu-�v��\��
    void drawDigit(char n, COLOR_ARGB color);
	// �����_��`��
    void drawDecimal(COLOR_ARGB color);
	// �Z�u���Z�O�����g�\����`��
	// number�ϐ��ɂ́A�\�����镂�������_���l���i�[����Ă���
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);
};

class Bar : public Image
{
public:
	// Bar��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   left�Atop = ��ʈʒu
	//         scale = �{���i�Y�[���j
	//		   color = �o�[�̐F
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, COLOR_ARGB color);
	// �o�[�̃T�C�Y��ݒ�
    void set(float percentOn);
	// update���I�[�o�[���C�h
    virtual void update(float frameTime)    {}
};

class DialGauge : public Image
{
private:
    Image   mPointer;					// �摜
    dashboardNS::DialType mDialType;	// �~�Ղ̎��
public:
	// DialGauge��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   left�Atop = ��ʈʒu
	//         scale = �{���i�Y�[���j
	//		   type = �~�Ղ̎��
	//		   zeroAngle = �~�Ղ̃[���̈ʒu
	//		   dialColor = �~�Ղ̐F
	//		   pointColor = �����̐F
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, dashboardNS::DialType type, float zeroAngle,
                    COLOR_ARGB dialColor, COLOR_ARGB pointerColor);
	// DialGauge�̎w�j��ݒ�
    void set(float percentOn);
	// update���I�[�o�[���C�h
    virtual void update(float frameTime)    {}
	// DialGauge�Ǝw�j��`��
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

class Light : public Image
{
private:
    float   mFlashTimer;	// ���C�g�_�ŗp�̃^�C�}�[
    float   mFlashDelay;	// ���C�g���_�ł���Ԋu
    COLOR_ARGB  mOnColor;	// �_�����̃��C�g�̐F
    COLOR_ARGB  mOffColor;	// �������̃��C�g�̐F
public:
	// �R���X�g���N�^
    Light();
	// Light��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   left�Atop = ��ʈʒu
	//         scale = �{���i�Y�[���j
	//		   flashRate = �_��/����/�_�ł̑���
	//		   �i<0�̏ꍇ�͓_���A=0�̏ꍇ�͏����A>0�̏ꍇ��1�b������̓_�ł̎��ԁj
	//		   colorOn = �_�����̃��C�g�̐F
	//		   colorOff = �������̃��C�g�̐F
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                float scale,float flashRate, COLOR_ARGB colorOn, COLOR_ARGB colorOff);
	// flashRate��ݒ�F<0�̏ꍇ�͓_���A =0�̏ꍇ�͏����A>0�̏ꍇ�͓_�ł̎���
	void set(float rate);
	// update���I�[�o�[���C�h
    virtual void update(float frameTime);
};

class ToggleSwitch : public Image
{
private:
    Input   *mInput;			// ���̓V�X�e���ւ̃|�C���^
    HWND    mHwnd;				// �E�B���h�E�n���h��
    RECT    mSwitchRect;        // �}�E�X�N���b�N���󂯕t����͈�
    bool    mSwitchOn;          // �X�C�b�`�̏��
    bool    mMouseClick;        // �}�E�X�N���b�N�̏��
    public:
    // Toggle switch�R���X�g���N�^
    ToggleSwitch();
	// �؂�ւ��X�C�b�`�iToggleSwitch�j��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   *in = Input�I�u�W�F�N�g�ւ̃|�C���^
	//         hwnd = �E�B���h�E�ւ̃n���h��
	//		   left�Atop = ��ʈʒu
	//		   scale = �{���i�Y�[���j
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale);
	// update���I�[�o�[���C�h
    virtual void update(float frameTime);
    // �X�C�b�`�̏�Ԃ��擾
    bool getSwitchOn()   {return mSwitchOn;}
    // �X�C�b�`�̏�Ԃ�ݒ�
    void setSwitch(bool on) {mSwitchOn = on;}
};

class PushButton : public Image
{
private:
	Input   *mInput;			// ���̓V�X�e���ւ̃|�C���^
	HWND    mHwnd;				// �E�B���h�E�n���h��
	RECT    mSwitchRect;        // �}�E�X�N���b�N���󂯕t����͈�
	bool    mSwitchOn;          // �X�C�b�`�̏��
	bool    mMouseClick;        // �}�E�X�N���b�N�̏��
    bool    mMomentary;         // ��莞�Ԃ��Ƃɐ؂�ւ���ꍇ��true�A�g�O���̏ꍇ��false
public:
    // Pushbutton switch�R���X�g���N�^
    PushButton();
	// �v�b�V���{�^���iPushButton�j��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   *in = Input�I�u�W�F�N�g�ւ̃|�C���^
	//         hwnd = �E�B���h�E�ւ̃n���h��
	//		   left�Atop = ��ʈʒu
	//		   scale = �{���i�Y�[���j
	//		   type = true�̏ꍇ�̓��[�����^���[�Afalse�̏ꍇ�̓I���^�l�[�g
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale, bool momentary);
	// update���I�[�o�[���C�h
    virtual void update(float frameTime);
	// �X�C�b�`�̏�Ԃ��擾
    bool getSwitchOn()  {return mSwitchOn;}
	// �X�C�b�`�̏�Ԃ�ݒ�
    void setSwitch(bool on) {mSwitchOn = on;}
};

//
class BarGraph : public Image
{
private:
    int mMaxBars;			// �o�[�̖{���̍ő吔
    int mBarsOn;			// ���݂̃o�[�̖{��
public:
    // BarGraph�R���X�g���N�^
    BarGraph();
	// BarGraph��������
	// ���s�O�F*graphics = Graphics�I�u�W�F�N�g�ւ̃|�C���^
	//		   *textureM = TextureManager�I�u�W�F�N�g�ւ̃|�C���^
	//		   left�Atop = ��ʈʒu
	//		   scale = �{���i�Y�[���j
	//		   bars = ���[�^�[���̃o�[�̖{��
	//		   color = �o�[�̐F
	// ���s��F���������ꍇ��true�A�G���[�̏ꍇ��false��߂�
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT bars, COLOR_ARGB color);
	// barsOn�̒l���A�\������o�[�̖{���ɐݒ�
	// �p�����[�^p�͊����i0�`100�j
    void set(float percentOn);	
	// update���I�[�o�[���C�h
    virtual void update(float frameTime)    {}
	// BarGraph��`��
	// barsOn�́A�\������o�[�̖{�����i�[
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

#endif

