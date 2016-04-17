//==========================================================
/// @file
/// @brief    Graphics�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _GRAPHICS_H             // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _GRAPHICS_H             // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

class Graphics;

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

// DirectX�|�C���^�^
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_SPRITE   LPD3DXSPRITE
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define VECTOR2     D3DXVECTOR2
#define LP_VERTEXBUFFER LPDIRECT3DVERTEXBUFFER9
#define LP_DXFONT   LPD3DXFONT
#define LP_VERTEXBUFFER LPDIRECT3DVERTEXBUFFER9

// �F�̒�`
// ���ʂŎg�p����F
// ARGB�̐��l�͈̔͂�0����255�܂�
// A = �A���t�@�`���l���i�����x�A255�͕s�����j
// R = �ԁAG = �΁AB = ��
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// ���ʂŎg�p����F
	// ARGB�̐��l�͈̔͂�0����255�܂�
	// A = �A���t�@�`���l���i�����x�A255�͕s�����j
	// R = �ԁAG = �΁AB = ��
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	// colorFilter�ŕ`�悷�邱�Ƃ��w�肷�邽�߂Ɏg�p
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);
	// �F��AND�����s���āA25%�A���t�@���擾
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);
	// �F��AND�����s���āA50%�A���t�@���擾
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);
	const COLOR_ARGB BACK_COLOR = NAVY;                         // background color of game
	const COLOR_ARGB TRANSCOLOR = MAGENTA;                      // transparent color

	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}

struct VertexC              // ���_�f�[�^�i���W�ƐF�j
{
	float x, y, z;          // ���W�l
	float rhw;              // �������W W (1�ɐݒ�)
	unsigned long color;    // ���_�̐F
};

// �_��Ȓ��_�t�H�[�}�b�g
// D3DFVF_XYZRHW = �ϊ��ςݒ��_���W
// D3DFVF_DIFFUSE = �J���[�f�[�^���݂̒��_���W
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// SpriteData�F�X�v���C�g��`�悷��Graphics::drawSprite���K�v�Ƃ���v���p�e�B
struct SpriteData
{
	int         width;      // �X�v���C�g�̕��i�s�N�Z���P�ʁj
	int         height;     // �X�v���C�g�̍����i�s�N�Z���P�ʁj
	float       x;          // ��ʈʒu�i�X�v���C�g�̍�����j
	float       y;
	float       scale;      // <1�͏k���A>1�͊g��
	float       angle;      // ��]�p�x�i���W�A���P�ʁj
	RECT        rect;       // �傫�ȃe�N�X�`������1�̉摜��I������Ƃ��Ɏg�p
	LP_TEXTURE  texture;    // �e�N�X�`���ւ̃|�C���^
	bool        flipHorizontal; // �X�v���C�g�𐅕������ɔ��]����ꍇ�Atrue
	bool        flipVertical;   // �X�v���C�g�𐂒������ɔ��]����ꍇ�Atrue
};

class Graphics
{
private:
	// DirectX�|�C���^�Ȃ�
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE   sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// ���̑��̕ϐ�
	HRESULT     result;         // �W����Windows���^�[���R�[�h
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // �w�i�F

	// (�G���W���̎g�p���ɓ����I�ɂ̂ݎg�p���܂��B
	// �����ɂ̓��[�U�[���g�p������̂͂���܂���B�j
	// D3D�v���[���e�[�V�����p�����[�^��������
	void    initD3Dpp();

public:
	// �R���X�g���N�^
	Graphics();

	// �f�X�g���N�^
	virtual ~Graphics();

	// direct3d��device3d�����
	void    releaseAll();

	// DirectX�O���t�B�b�N�X��������
	// hw = �E�B���h�E�ւ̃n���h��
	// width = ���i�s�N�Z���P�ʁj
	// height = �����i�s�N�Z���P�ʁj
	// fullscreen = �S��ʕ\���̏ꍇ��true�A�E�B���h�E�̏ꍇ��false
	// �G���[����GameError���X���[
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// ���_�o�b�t�@���쐬
	// ���s�O�Fverts[]�ɒ��_�f�[�^���i�[����Ă���
	//		   size = verts[]�̃T�C�Y
	// ���s��F���������ꍇ�A&vertexBuffer���o�b�t�@���w��
	HRESULT createVertexBuffer(VertexC verts[], UINT size, LP_VERTEXBUFFER &vertexBuffer);

	// �O�p�`�t�@�����g���āA�A���t�@���ߐ������l�p�`��\��
	// ���s�O�FcreateVertexBuffer���g����vertexBuffer���쐬���A
	//		   �l�p�`�����v���̏����Œ�`����4�̒��_���i�[���Ă���
	//		   g3ddev->BeginScene���Ăяo��
	// ���s��F�l�p�`���`�悳���
	bool    drawQuad(LP_VERTEXBUFFER vertexBuffer);

	// �e�N�X�`�����f�t�H���g��D3D�������ɓǂݍ��ށi�ʏ�̃e�N�X�`���Ŏg�p�j
	// �G���W���̎g�p���ɓ����I�ɂ̂ݎg�p���܂��B
	// �Q�[���e�N�X�`���̓ǂݍ��݂ɂ́ATextureManager�N���X���g�p���܂��B
	// ���s�O�Ffilename�́A�e�N�X�`���t�@�C���̖��O
	//		�@ transcolor�́A�����Ƃ��Ĉ����F
	// ���s��Fwidth��height = �e�N�X�`���̐��@
	//         texture�́A�e�N�X�`�����w��
	HRESULT loadTexture(const char * filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);

	// �e�N�X�`�����V�X�e���������ɓǂݍ��ށi�V�X�e���������̓��b�N�\�j
	// �s�N�Z���f�[�^�ւ̒��ڃA�N�Z�X���\�ɂ��܂��B
	// TextureManager�N���X���g���āA�\������e�N�X�`����ǂݍ��݂܂��B
	// ���s�O�Ffilename�́A�e�N�X�`���t�@�C���̖��O
	//		   transcolor�́A�����Ƃ��Ĉ����F
	// ���s��Fwidth��height = �e�N�X�`���̐��@
	//         texture�́A�e�N�X�`�����w��
	HRESULT loadTextureSystemMem(const char *filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);

	// �I�t�X�N���[���o�b�N�o�b�t�@����ʂɕ\��
	HRESULT showBackbuffer();

	// �A�_�v�^�[���`�F�b�N���āAd3dpp�Ŏw�肳�ꂽBackBuffer�̍����A���A
	// ���t���b�V�����[�g�ɑΉ����Ă��邩�ǂ������m�F���܂��B
	// �Ή�������̂����������ꍇ�́ApMode�\���̂ɁA
	// �Ή����Ă��郂�[�h�̃t�H�[�}�b�g��ݒ肵�܂��B
	// ���s�O�Fd3dpp������������Ă���
	// ���s��F�Ή����Ă��郂�[�h��������ApMode�\���̂Ƀf�[�^��
	// �ݒ肳�ꂽ�ꍇ�Atrue��߂��܂��B
	// �Ή����Ă��郂�[�h��������Ȃ������ꍇ�Afalse��߂��܂��B
	bool    isAdapterCompatible();

	// SpriteData�\���̂ɋL�q���ꂽ�X�v���C�g��`��
	// color�i�I�v�V�����j�́A�t�B���^�̂悤�ɓK�p�����
	// �f�t�H���g�͔��i�ω��Ȃ��j
	// ���s�O�Fsprite->Begin()���Ăяo��
	// ���s��Fsprite->End()���Ăяo��
	//		   spriteDate.rect�́A�`�悷��spriteDate.texture�̕������`
	//		   spriteData.rect.right�́A�E�[+1�ɂ���K�v������
	//		   spriteDate.rect.bottom�́A���[+1�ɂ���K�v������
	void    drawSprite(const SpriteData &spriteData,	// �`�悷��X�v���C�g
		COLOR_ARGB color = graphicsNS::WHITE);			// �f�t�H���g�͔�

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g
	HRESULT reset();

	// �E�B���h�E���[�h��t���X�N���[�����[�h�ɐݒ�
	// ���s�O�F���ׂĂ�D3DPOOL_DEFAULT�T�[�t�F�C�X���������
	// ���s��F���ׂẴT�[�t�F�C�X���č쐬
	void    changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

	// �x�N�g���̒�����߂�
	static float    Vector2Length(const VECTOR2 *v) { return D3DXVec2Length(v); }

	// �x�N�g�����m�̓��ς�߂�
	static float    Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2) { return D3DXVec2Dot(v1, v2); }

	// �x�N�g���𐳋K������
	static void     Vector2Normalize(VECTOR2 *v) { D3DXVec2Normalize(v, v); }

	// �x�N�g��v���s��m�ɂ���ĕϊ�����
	static VECTOR2* Vector2Transform(VECTOR2 *v, D3DXMATRIX *m) { return D3DXVec2TransformCoord(v, v, m); }


	////////////////////////////////////////
	//           getter                   //
	////////////////////////////////////////

	// direct3d��߂�
	LP_3D get3D() { return direct3d; }

	// device3d��߂�
	LP_3DDEVICE get3Ddevice() { return device3d; }

	// �X�v���C�g��߂�
	LP_SPRITE getSprite() { return sprite; }

	// �f�o�C�X�R���e�L�X�g�ւ̃n���h����߂�
	HDC getDC() { return GetDC(hwnd); }

	// �f�o�C�X���������Ă��Ȃ������`�F�b�N
	HRESULT getDeviceState();

	// �t���X�N���[�����[�h���ǂ�����߂�
	bool getFullscreen() { return fullscreen; }

	// Set color used to clear screen
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	//=============================================================================
	// �o�b�N�o�b�t�@���N���A���āADirectX��BeginScene()���Ăяo��
	//=============================================================================
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		// �o�b�N�o�b�t�@��backColor�ŃN���A����
		device3d->Clear(0, 0,
			D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
			backColor, 1.0f, 0);

		result = device3d->BeginScene();          // �`��̂��߂̃V�[�����J�n����
		return result;
	}

	//=============================================================================
	// DirectX��EndScene()���Ăяo��
	//=============================================================================
	HRESULT endScene()
	{
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}

	//=============================================================================
	// Sprite Begin
	//=============================================================================
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	//=============================================================================
	// Sprite End
	//=============================================================================
	void spriteEnd()
	{
		sprite->End();
	}
};

#endif

