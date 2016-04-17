//==========================================================
/// @file
/// @brief    graphics.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������


#include "graphics.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	sprite = NULL;
	fullscreen = false;
	width = GAME_WIDTH;    // ���ƍ�����initialize()�Œu����������
	height = GAME_HEIGHT;
	backColor = graphicsNS::BACK_COLOR;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Graphics::~Graphics()
{
	releaseAll();
}

//=============================================================================
// ���ׂĂ����
//=============================================================================
void Graphics::releaseAll()
{
	safeRelease(sprite);
	safeRelease(device3d);
	safeRelease(direct3d);
}

//=============================================================================
// DirextX�O���t�B�b�N�X��������
// �G���[����GameError���X���[
//=============================================================================
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	// Direct3D�f�o�C�X���쐬
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp();        // D3D�v���[���e�[�V�����p�����[�^��������
	if (fullscreen)      // �S��ʕ\�����[�h�̏ꍇ
	{
		if (isAdapterCompatible())   // �A�_�v�^�[���Ή����Ă��邩
			// �Ή����Ă��郊�t���b�V�����[�g��ݒ�
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR,
				"The graphics device does not support the specified resolution and/or format."));
	}

	// �O���t�B�b�N�X�J�[�h���n�[�h�E�F�A�e�N�X�`�������O�ƃ��C�e�B���O�A
	// ���_�V�F�[�_�[���T�|�[�g���Ă��邩�ǂ����𔻒�
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	// �f�o�C�X��HW�e�N�X�`�������O�ƃ��C�e�B���O���T�|�[�g���Ă��Ȃ��ꍇ�A
	// �܂��́A1.1���_�V�F�[�_�[���n�[�h�E�F�A�ŃT�|�[�g���Ă��Ȃ��ꍇ�A
	// �\�t�g�E�F�A���_�����ɐ؂�ւ��܂��B
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		// �\�t�g�E�F�A�݂̂̏������g�p
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		// �n�[�h�E�F�A�݂̂̏����̎g�p
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// Direct3D�f�o�C�X���쐬
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&device3d);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

	result = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite"));

	// Configure for alpha blend of primitives
	device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// D3D�v���[���e�[�V�����p�����[�^��������
//=============================================================================
void Graphics::initD3Dpp()
{
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));              // �\���̂�0��ݒ�
		// �K�v�ȃp�����[�^��ݒ�
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)                                 // �S��ʕ\���̏ꍇ
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24�r�b�g�J���[
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   // �f�X�N�g�b�v�ݒ���g�p
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;    // Depth 24, Stencil 8
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR,
			"Error initializing D3D presentation parameters"));
	}
}

//=============================================================================
// �e�N�X�`�����f�t�H���g��D3D�������ɓǂݍ��ށi�ʏ�̃e�N�X�`���Ŏg�p�j
// �G���W���̎g�p���ɓ����I�ɂ̂ݎg�p���܂��B
// �Q�[���e�N�X�`���̓ǂݍ��݂ɂ́ATextureManager�N���X���g�p���܂��B
// ���s�O�Ffilename�́A�e�N�X�`���t�@�C���̖��O
//		�@ transcolor�́A�����Ƃ��Ĉ����F
// ���s��Fwidth��height = �e�N�X�`���̐��@
//         texture�́A�e�N�X�`�����w��
// HRESULT��߂�
//=============================================================================
HRESULT Graphics::loadTexture(const char *filename, COLOR_ARGB transcolor,
	UINT &width, UINT &height, LP_TEXTURE &texture)
{
	// �t�@�C������ǂݎ�邽�߂̍\����
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try {
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// ���ƍ������t�@�C������擾
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// �t�@�C����ǂݍ���ŁA�V�����e�N�X�`�����쐬
		result = D3DXCreateTextureFromFileEx(
			device3d,           // 3D�f�o�C�X
			filename,           // �摜�t�@�C���̖��O
			info.Width,         // �e�N�X�`���̕�
			info.Height,        // �e�N�X�`���̍���
			1,                  // �~�b�v�}�b�v�̃��x���i�`�F�[���Ȃ��̏ꍇ��1�j
			0,                  // �g�p���@�iusage�j
			D3DFMT_UNKNOWN,     // �T�[�t�F�C�X�t�H�[�}�b�g�i�f�t�H���g�j
			D3DPOOL_DEFAULT,    // �e�N�X�`���p�̃������̎��
			D3DX_DEFAULT,       // �摜�t�B���^
			D3DX_DEFAULT,       // �~�b�v�t�B���^
			transcolor,         // �����p�̐F�L�[
			&info,              // �s�b�g�}�b�v�t�@�C�����i�ǂݍ��񂾃t�@�C������j
			NULL,               // �J���[�p���b�g
			&texture);          // �ړI�̃e�N�X�`��

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
	}
	return result;
}

//=============================================================================
// �e�N�X�`�����V�X�e���������ɓǂݍ��ށi�V�X�e���������̓��b�N�\�j
// �s�N�Z���f�[�^�ւ̒��ڃA�N�Z�X���\�ɂ��܂��B
// TextureManager�N���X���g���āA�\������e�N�X�`����ǂݍ��݂܂��B
// ���s�O�Ffilename�́A�e�N�X�`���t�@�C���̖��O
//		   transcolor�́A�����Ƃ��Ĉ����F
// ���s��Fwidth��height = �e�N�X�`���̐��@
//         texture�́A�e�N�X�`�����w��
// HRESULT��߂��ATextureData�\���̂Ƀf�[�^���i�[����
//=============================================================================
HRESULT Graphics::loadTextureSystemMem(const char *filename, COLOR_ARGB transcolor,
	UINT &width, UINT &height, LP_TEXTURE &texture)
{
	// �r�b�g�}�b�v�t�@�C������ǂݎ�邽�߂̍\����
	D3DXIMAGE_INFO info;
	result = E_FAIL;        // �W����Windows�߂�l

	try {
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// ���ƍ������r�b�g�}�b�v�t�@�C������擾
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// �r�b�g�}�b�v�摜�t�@�C����ǂݍ���ŁA�V�����e�N�X�`�����쐬
		result = D3DXCreateTextureFromFileEx(
			device3d,           // 3D�f�o�C�X
			filename,           // �r�b�g�}�b�v�t�@�C���̖��O
			info.Width,         // �r�b�g�}�b�v�摜�̕�
			info.Height,        // �r�b�g�}�b�v�摜�̍���
			1,                  // �~�b�v�}�b�v�̃��x���i�`�F�[���Ȃ��̏ꍇ��1�j
			0,                  // �g�p���@�iusage�j
			D3DFMT_UNKNOWN,     // �T�[�t�F�C�X�t�H�[�}�b�g�i�f�t�H���g�j
			D3DPOOL_SYSTEMMEM,  // �V�X�e���������̓��b�N�\
			D3DX_DEFAULT,       // �摜�t�B���^
			D3DX_DEFAULT,       // �~�b�v�t�B���^
			transcolor,         // �����p�̐F�L�[
			&info,              // �r�b�g�}�b�v�t�@�C�����i�ǂݍ��񂾃t�@�C������j
			NULL,               // �J���[�p���b�g
			&texture);          // �ړI�̃e�N�X�`��

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
	}
	return result;
}

//=============================================================================
// ���_�o�b�t�@���쐬
// ���s�O�Fverts[]�ɒ��_�f�[�^���i�[����Ă���
//		   size = verts[]�̃T�C�Y
// ���s��F���������ꍇ�A&vertexBuffer���o�b�t�@���w��
//=============================================================================
HRESULT Graphics::createVertexBuffer(VertexC verts[], UINT size, LP_VERTEXBUFFER &vertexBuffer)
{
	// �W����Windows�߂�l
	HRESULT result = E_FAIL;

	// ���_�o�b�t�@���쐬
	result = device3d->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, D3DFVF_VERTEX,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	if (FAILED(result))
		return result;

	void *ptr;
	// �f�[�^���]������Ă���O�ɁA�o�b�t�@�����b�N����K�v������
	result = vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	if (FAILED(result))
		return result;
	memcpy(ptr, verts, size);   // ���_�f�[�^���o�b�t�@�ɃR�s�[
	vertexBuffer->Unlock();     // �o�b�t�@�̃��b�N������

	return result;
}

//=============================================================================
// �O�p�`�t�@�����g���āA�A���t�@���ߐ������l�p�`��\��
// ���s�O�FcreateVertexBuffer���g����vertexBuffer���쐬���A
//		   �l�p�`�����v���̏����Œ�`����4�̒��_���i�[���Ă���
//		   g3ddev->BeginScene���Ăяo��
// ���s��F�l�p�`���`�悳���
//=============================================================================
bool Graphics::drawQuad(LP_VERTEXBUFFER vertexBuffer)
{
	HRESULT result = E_FAIL;    // �W����Windows�߂�l

	if (vertexBuffer == NULL)
		return false;

	// �A���t�@�u�����h��L����
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	device3d->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexC));
	device3d->SetFVF(D3DFVF_VERTEX);
	result = device3d->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

	// �A���t�@�u�����h�𖳌���
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	if (FAILED(result))
		return false;

	return true;
}

//=============================================================================
// �o�b�N�o�b�t�@��\��
//=============================================================================
HRESULT Graphics::showBackbuffer()
{
	// �o�b�N�o�b�t�@����ʂɕ\��
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

//=============================================================================
// �A�_�v�^�[���`�F�b�N���āAd3dpp�Ŏw�肳�ꂽBackBuffer�̍����A���A
// ���t���b�V�����[�g�ɑΉ����Ă��邩�ǂ������m�F���܂��B
// �Ή�������̂����������ꍇ�́ApMode�\���̂ɁA
// �Ή����Ă��郂�[�h�̃t�H�[�}�b�g��ݒ肵�܂��B
// ���s�O�Fd3dpp������������Ă���
// ���s��F�Ή����Ă��郂�[�h��������ApMode�\���̂Ƀf�[�^��
// �ݒ肳�ꂽ�ꍇ�Atrue��߂��܂��B
// �Ή����Ă��郂�[�h��������Ȃ������ꍇ�Afalse��߂��܂��B
//=============================================================================
bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,
		d3dpp.BackBufferFormat);
	for (UINT i = 0; i<modes; i++)
	{
		result = direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,
			d3dpp.BackBufferFormat,
			i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}

//=============================================================================
// SpriteData�\���̂ɋL�q���ꂽ�X�v���C�g��`��
// color�i�I�v�V�����j�́A�t�B���^�̂悤�ɓK�p�����
// �f�t�H���g�͔��i�ω��Ȃ��j
// ���s�O�Fsprite->Begin()���Ăяo��
// ���s��Fsprite->End()���Ăяo��
//		   spriteDate.rect�́A�`�悷��spriteDate.texture�̕������`
//		   spriteData.rect.right�́A�E�[+1�ɂ���K�v������
//		   spriteDate.rect.bottom�́A���[+1�ɂ���K�v������
//=============================================================================
void Graphics::drawSprite(const SpriteData &spriteData, COLOR_ARGB color)
{
	if (spriteData.texture == NULL)      // �e�N�X�`�����Ȃ��ꍇ
		return;

	// �X�v���C�g�̒��S�����
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.width / 2 * spriteData.scale),
		(float)(spriteData.height / 2 * spriteData.scale));
	// �X�v���C�g�̉�ʈʒu
	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x, (float)spriteData.y);
	// X������Y�����̊g��k��
	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);
	if (spriteData.flipHorizontal)  // ���������ɔ��]����ꍇ
	{
		scaling.x *= -1;            // X�X�P�[���𕉂ɂ��Ĕ��]
		// ���]���ꂽ�摜�̒��S���擾
		spriteCenter.x -= (float)(spriteData.width*spriteData.scale);
		// ���[�𒆐S�ɔ��]���N����̂ŁA���]���ꂽ�摜��
		// ���Ɠ����ʒu�ɔz�u���邽�߂ɁA�E�ֈړ����܂��B
		translate.x += (float)(spriteData.width*spriteData.scale);
	}
	if (spriteData.flipVertical)    // ���������ɔ��]����ꍇ
	{
		scaling.y *= -1;            // Y�X�P�[���𕉂ɂ��Ĕ��]
		// ���]���ꂽ�摜�̒��S���擾
		spriteCenter.y -= (float)(spriteData.height*spriteData.scale);
		// ��[�𒆐S�ɔ��]���N����̂ŁA���]���ꂽ�摜��
		// ���Ɠ����ʒu�ɔz�u���邽�߂ɁA���ֈړ����܂��B
		translate.y += (float)(spriteData.height*spriteData.scale);
	}
	// �X�v���C�g�̉�]�A�g��k���A�z�u���s�����߂̍s����쐬
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,                // �s��
		NULL,                   // �g��k�����s���Ƃ��A���_�͍���̂܂�
		0.0f,                   // �g��k�����̉�]�Ȃ�
		&scaling,               // �g��k���̔{��
		&spriteCenter,          // ��]�̒��S
		(float)(spriteData.angle),  // ��]�̊p�x
		&translate);            // X�AY�ʒu

	// �s����X�v���C�g�ɓK�p
	sprite->SetTransform(&matrix);

	// �X�v���C�g��`��
	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);
}

//=============================================================================
// �E�B���h�E���[�h��t���X�N���[�����[�h�ɐݒ�
// ���s�O�F���ׂĂ�D3DPOOL_DEFAULT�T�[�t�F�C�X���������
// ���s��F���ׂẴT�[�t�F�C�X���č쐬
//=============================================================================
void Graphics::changeDisplayMode(graphicsNS::DISPLAY_MODE mode)
{
	try {
		switch (mode)
		{
		case graphicsNS::FULLSCREEN:
			if (fullscreen)      // if already in fullscreen mode
				return;
			fullscreen = true; break;
		case graphicsNS::WINDOW:
			if (fullscreen == false) // if already in window mode
				return;
			fullscreen = false; break;
		default:        // default to toggle window/fullscreen
			fullscreen = !fullscreen;
		}
		reset();
		if (fullscreen)  // fullscreen
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
		}
		else            // windowed
		{
			SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

			// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);   // get size of client area of window
			MoveWindow(hwnd,
				0,                                           // Left
				0,                                           // Top
				GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
				GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
				TRUE);                                       // Repaint the window
		}

	}
	catch (...)
	{
		// An error occured, try windowed mode 
		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, GAME_WIDTH, GAME_HEIGHT,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(hwnd,
			0,                                           // Left
			0,                                           // Top
			GAME_WIDTH + (GAME_WIDTH - clientRect.right),    // Right
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), // Bottom
			TRUE);                                       // Repaint the window
	}
}

//=============================================================================
// �f�o�C�X���������Ă��Ȃ������`�F�b�N
//=============================================================================
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;    // �������f�t�H���g�Ƃ��A�������ɒu������
	if (device3d == NULL)
		return  result;
	result = device3d->TestCooperativeLevel();
	return result;
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g
//=============================================================================
HRESULT Graphics::reset()
{
	initD3Dpp();                        // D3D�v���[���e�[�V�����p�����[�^��������
	sprite->OnLostDevice();             // release sprite
	// �O���t�B�b�N�X�f�o�C�X�̃��Z�b�g�����݂�
	result = device3d->Reset(&d3dpp);

	// �v���~�e�B�u�̃A���t�@�u�����h�p�̍\��
	device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	sprite->OnResetDevice();            // recreate sprite
	return result;
}
