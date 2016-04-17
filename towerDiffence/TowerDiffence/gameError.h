//==========================================================
/// @file
/// @brief    GameErrorクラス
/// @author   阿部拳之
///
/// @attention  ゲームエンジンによってスローされるErrorクラス

#ifndef _GAMEERROR_H            // このファイルが複数の箇所でインクルードされる場合に、
#define _GAMEERROR_H            // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <exception>

namespace gameErrorNS
{
	// エラーコード
	// 負の数は、ゲームをシャットダウンする必要のある致命的なエラーを表します。
	// 正の数は、ゲームをシャットダウンする必要のない警告を表します。
    const int FATAL_ERROR = -1;
    const int WARNING = 1;
}

// GameErrorクラス。ゲームエンジンによってエラーが検知されたときにスローされます。
// std::exceptionを継承
class GameError : public std::exception
{
private:
    int     errorCode;
    std::string message;
public:
	// デフォルトコンストラクタ
    GameError() throw() :errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game.") {}
    // コピーコンストラクタ
    GameError(const GameError& e) throw(): std::exception(e), errorCode(e.errorCode), message(e.message) {}
    // 引数ありのコンストラクタ
    GameError(int code, const std::string &s) throw() :errorCode(code), message(s) {}
    // 代入演算子
    GameError& operator= (const GameError& rhs) throw() 
    {
        std::exception::operator=(rhs);
        this->errorCode = rhs.errorCode;
        this->message = rhs.message;
    }
	// デストラクタ
    virtual ~GameError() throw() {};

	// 基本クラスに対するオーバーライド
    virtual const char* what() const throw() { return this->getMessage(); }

    const char* getMessage() const throw() { return message.c_str(); }
    int getErrorCode() const throw() { return errorCode; }
};

#endif
