//==========================================================
/// @file
/// @brief    textureManager.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������
#include "textureManager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
TextureManager::TextureManager()
{
	mGraphics = NULL;
	mInitialized = false;            // �������ɐ��������ꍇ�́Atrue
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TextureManager::~TextureManager()
{
	for (UINT i = 0; i<mTexture.size(); i++)
		safeReleaseTexture(mTexture[i]);
}

//=============================================================================
// �e�N�X�`���t�@�C�����f�B�X�N����ǂݍ���
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//=============================================================================
bool TextureManager::initialize(Graphics *g, std::string file)
{
	bool success = true;
	try {
		mGraphics = g;                       // graphics�I�u�W�F�N�g
		for (UINT i = 0; i<file.size(); i++)    // convert to lowercase
			file.at(i) = tolower(file.at(i));
		if (file.rfind(".txt") == file.size() - 4) // if .txt extension
		{
			// open file containing individual texture names
			std::ifstream infile(file.c_str());
			if (!infile)                     // if open failed
				return false;
			std::string name;
			while (getline(infile, name))
			{
				mFileNames.push_back(name);  // add to files
				mWidth.push_back(0);         // make room for width
				mHeight.push_back(0);        // make room for height
				mTexture.push_back(NULL);    // make room for texture
			}
			infile.close();
		}
		else    // not .txt file so file contains name of one texture
		{
			mFileNames.push_back(file);      // put one file name in files
			mWidth.push_back(0);         // make room for width
			mHeight.push_back(0);        // make room for height
			mTexture.push_back(NULL);    // make room for texture
		}

		// load texture files
		for (UINT i = 0; i<mFileNames.size(); i++)
		{
			mHr = mGraphics->loadTexture(mFileNames[i].c_str(),
				graphicsNS::TRANSCOLOR, mWidth[i], mHeight[i], mTexture[i]);
			if (FAILED(mHr))
				success = false;    // at least one texture failed to load
		}
	}
	catch (...) { return false; }
	mInitialized = true;                    // ����ɏ��������ꂽ�ꍇ�Atrue��ݒ�
	return success;
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
//=============================================================================
void TextureManager::onLostDevice()
{
	try
	{
		if (!mInitialized)
			return;
		for (UINT i = 0; i<mTexture.size(); i++)
			safeReleaseTexture(mTexture[i]);
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::WARNING,
			"Warning, TextureManager onLostDevice attempted to access an invalid texture."));
	}
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo�����
//=============================================================================
void TextureManager::onResetDevice()
{
	if (!mInitialized)
		return;
	// load texture files
	for (UINT i = 0; i<mFileNames.size(); i++)
	{
		mHr = mGraphics->loadTexture(mFileNames[i].c_str(),
			graphicsNS::TRANSCOLOR, mWidth[i], mHeight[i], mTexture[i]);
		if (FAILED(mHr))
			safeReleaseTexture(mTexture[i]);
	}
}