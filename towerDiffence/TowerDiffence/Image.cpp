//==========================================================
/// @file
/// @brief    image.h�̎���
/// @author   �������V
///
/// @attention  
#include "image.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
Image::Image()
{
	initialized = false;            // set true when successfully initialized
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       // used to select one frame from multi-frame image
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;      // the sprite texture (picture)
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	textureManager = NULL;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0;               // default to 1 second per frame of animation
	animTimer = 0.0;
	visible = true;                 // the image is visible
	loop = true;                    // loop frames
	animComplete = false;
	graphics = NULL;                // link to graphics system
	colorFilter = graphicsNS::WHITE; // WHITE for no change
	mode = imageNS::MODE::HORIZONTAL;		// �ʏ�͐����ŃA�j���[�V�������i��
}

//==========================================================
// �p�����[�^������
//==========================================================
void Image::reset()
{
	visible = true;
	setCurrentFrame(startFrame);
	mode = imageNS::HORIZONTAL;
	// �A�j���[�V�����̓��[�v��Ԃ���X�^�[�g
	loop = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Image::~Image()
{}

//=============================================================================
// Image��������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
// Graphics�ւ̃|�C���^
// Image�̕��i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̕����g�p�j
// Image�̍����i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̍������g�p�j
// �e�N�X�`�����̗񐔁i1����n�܂Łj�i0��1�Ɠ����j
// TextureManager�ւ̃|�C���^
//=============================================================================
bool Image::initialize(Graphics *g, int width, int height, int ncols,
	TextureManager *textureM)
{
	try {
		graphics = g;				// graphics�I�u�W�F�N�g
		textureManager = textureM;	// �e�N�X�`���I�u�W�F�N�g�ւ̃|�C���^
		spriteData.texture = textureManager->getTexture();
		if (width == 0)
			width = textureManager->getWidth();		// �S�̂̕����g�p
		spriteData.width = width;
		if (height == 0)
			height = textureManager->getHeight();	// �S�̂̍������g�p
		spriteData.height = height;
		cols = ncols;
		if (cols == 0)
			cols = 1;								// cols��0�̏ꍇ�́A1���g�p
													// currentFrame��`�悷��spriteData.rect���\��
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		// �E�[+1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		// ���[+1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...)
	{
		return false;
	}
	initialized = true;	// ����ɏ��������ꂽ�ꍇ
	return true;
}

//=============================================================================
// color���t�B���^�Ƃ��Ďg���ĉ摜��`��
// color�p�����[�^�̓I�v�V����
// �iimage.h�ŁA�f�t�H���g�Ƃ��Ĕ������蓖�Ă��Ă���j
// ���s�O�FspriteBegin()���Ăяo��
// ���s��FspriteEnd()���Ăяo��
//=============================================================================
void Image::draw(COLOR_ARGB color)
{
	if (!visible || graphics == NULL)
		return;
	// onReset()���Ăяo���ꂽ�Ƃ��ɐV�����e�N�X�`�����擾
	spriteData.texture = textureManager->getTexture();
	if (color == graphicsNS::FILTER)	// �t�B���^���g���ĕ`�悷��ꍇ
										// colorFilter���g�p
		graphics->drawSprite(spriteData, colorFilter);
	else
		// �t�B���^�Ƃ���color���g�p
		graphics->drawSprite(spriteData, color);
}

//=============================================================================
// �w�肳�ꂽSpriteData���g���Ă��̉摜��`��
// ���݂�SpriteData.rect���g���āA�e�N�X�`����I��
// ���s�O�FspriteBegin()���Ăяo��
// ���s��FspriteEnd()���Ăяo��
//=============================================================================
void Image::draw(SpriteData sd, COLOR_ARGB color, UINT textureN)
{
	if (!visible || graphics == NULL)
		return;
	// ���̉摜�̋�`���g���ăe�N�X�`����I��
	sd.rect = spriteData.rect;
	// onReset()���Ăяo���ꂽ�Ƃ��ɐV�����e�N�X�`�����擾
	sd.texture = textureManager->getTexture(textureN);
	if (color == graphicsNS::FILTER)			// �t�B���^���g���ĕ`�悷��ꍇ
		graphics->drawSprite(sd, colorFilter);	// colorFilter���g�p
	else
		graphics->drawSprite(sd, color);
}

//=============================================================================
// update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Image::update(float frameTime)
{
	switch (mode)
	{
	case imageNS::HORIZONTAL:					// �ǂݍ��񂾉摜�t�@�C���ɑ΂��Đ��������ɃA�j���[�V�������i�ޏꍇ�A
		if (endFrame - startFrame > 0)          // �A�j���[�V����������X�v���C�g�̏ꍇ
		{
			animTimer += frameTime;             // ���v�̌o�ߎ���
			if (animTimer > frameDelay)
			{
				animTimer -= frameDelay;
				currentFrame++;
				if (currentFrame < startFrame || currentFrame > endFrame)
				{
					if (loop == true)           // ���[�v����A�j���[�V�����̏ꍇ
						currentFrame = startFrame;
					else                        // ���[�v���Ȃ��A�j���[�V�����̏ꍇ
					{
						currentFrame = endFrame;
						animComplete = true;    // �A�j���[�V�����̊���
					}
				}
				setRect();                      // spriteData.rect��ݒ�
			}
		}
		break;
	case imageNS::VERTICAL:						// �ǂݍ��񂾉摜�t�@�C���ɑ΂��Đ��������ɃA�j���[�V�������i�ޏꍇ�A
		if (endFrame - startFrame > 0)          // �A�j���[�V����������X�v���C�g�̏ꍇ
		{
			animTimer += frameTime;             // ���v�̌o�ߎ���
			if (animTimer > frameDelay)
			{
				animTimer -= frameDelay;
				currentFrame += cols;
				if (currentFrame < startFrame || currentFrame > endFrame)
				{
					if (loop == true)           // ���[�v����A�j���[�V�����̏ꍇ
						currentFrame = startFrame;
					else                        // ���[�v���Ȃ��A�j���[�V�����̏ꍇ
					{
						currentFrame = endFrame;
						animComplete = true;    // �A�j���[�V�����̊���
					}
				}
				setRect();                      // spriteData.rect��ݒ�
			}
		}
		break;
	}
}

//=============================================================================
// �摜�̌��݂̃t���[����ݒ�
//=============================================================================
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		animTimer = 0.0f;
		currentFrame = c;
		animComplete = false;
		setRect();                          // spriteData.rect��ݒ�
	}
}

//=============================================================================
//  Set spriteData.rect to draw currentFrame
//=============================================================================
inline void Image::setRect()
{
	// configure spriteData.rect to draw currentFrame
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// right edge + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// bottom edge + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}