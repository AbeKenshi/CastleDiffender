//==========================================================
/// @file
/// @brief    textureManager.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#include "textureManager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
TextureManager::TextureManager()
{
	mGraphics = NULL;
	mInitialized = false;            // 初期化に成功した場合は、true
}

//=============================================================================
// デストラクタ
//=============================================================================
TextureManager::~TextureManager()
{
	for (UINT i = 0; i<mTexture.size(); i++)
		safeReleaseTexture(mTexture[i]);
}

//=============================================================================
// テクスチャファイルをディスクから読み込む
// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
//=============================================================================
bool TextureManager::initialize(Graphics *g, std::string file)
{
	bool success = true;
	try {
		mGraphics = g;                       // graphicsオブジェクト
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
	mInitialized = true;                    // 正常に初期化された場合、trueを設定
	return success;
}

//=============================================================================
// グラフィックスデバイスが消失したときに呼び出される
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
// グラフィックスデバイスがリセットされたときに呼び出される
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