//==========================================================
/// @file
/// @brief    Castleクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _CASTLE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _CASTLE_H		// 多重に定義されることを防ぎます。

#include "entity.h"
#include "character.h"
#include "constants.h"


// Castleクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace castleNS
{
	const int WIDTH = 120;			// 画像の幅（各フレーム）
	const int HEIGHT = 120;			// 画像の高さ
	const int TEXTURE_COLS = 2;		// テクスチャは2列
	const int X = 549;				// 初期位置
	const int Y = 285;
	const int START_FRAME = 1;		// アニメーションの最初のフレーム
}

class Castle : public Entity		// Entityクラスを継承
{
private:
	bool death;						// 城が死亡時にtrue。activeをfalseにすると描画されなくなるので、代わりにこのフラグを用いる
public:
	// コンストラクタ
	Castle();

	// 継承されたメンバー関数
	// update
	void update(float frameTime);
	// ダメージ処理
	// WEAPONの種類によって受けるダメージが分岐
	void damage(WEAPON);
	// パラメータリセット
	void reset();

	// getter
	// 城が死亡しているかどうかを返す
	bool isDeath() { return death; }

	// setter
	// 城が死亡しているかどうかをセット
	void setDeath(bool d) { death = d; }
};

#endif // !_CASTLE_H
