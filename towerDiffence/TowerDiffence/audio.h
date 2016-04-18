//==========================================================
/// @file
/// @brief    Audioクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _AUDIO_H                // このファイルが複数の箇所でインクルードされる場合に、
#define _AUDIO_H                // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <xact3.h>
#include "constants.h"

class Audio
{
    // Audioプロパティ
  private:
    IXACT3Engine* mXactEngine;   // XACTエンジンへのポインタ
    IXACT3WaveBank* mWaveBank;   // XACTウェイブバンクへのポインタ
    IXACT3SoundBank* mSoundBank; // XACTサウンドバンクへのポインタ
    XACTINDEX mCueI;             // XACTサウンドインデックス
    void* mMapWaveBank;          // UnmapViewOfFile()を呼び出してファイルを解放
    void* mSoundBankData;
    bool mCoInitialized;         // CoInitializeExが成功した場合、trueを設定

  public:
	// コンストラクタ
    Audio();

    // デストラクタ
    virtual ~Audio();

    // メンバー関数
    // Audioを初期化
    HRESULT initialize();

    // サウンドエンジンの周期的タスクを実行
    void run();

	// キューで指定されたサウンドをサウンドバンクから再生
	// キューが存在しない場合は、サウンドが再生されないだけで、エラーは発生しない
    void playCue(const char cue[]);

	// キューで指定されたサウンドをサウンドバンクで停止
	// キューが存在しない場合、エラーは発生しない
    void stopCue(const char cue[]);
};

#endif
