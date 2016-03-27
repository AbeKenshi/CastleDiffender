#ifndef _BARRICADE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _BARRICADE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace barricadeNS
{
	const int WIDTH = 32;			// 画像の幅（各フレーム）
	const int HEIGHT = 32;			// 画像の高さ
	const int TEXTURE_COLS = 8;		// テクスチャは8列
	const int START_FRAME = 0;		// アニメーションはフレーム0から開始
	const int END_FRAME = 2;		// アニメーションフレームは0、1、2
}

class Barricade : public Entity		// Entityクラスを継承
{
private:
	float timeCounter;				// ダメージアニメーション用のタイマー
	float totalTimeCounter;
	bool death;						// 城が死亡時にtrue
	bool isDamaged;					// ダメージを受けている状態かどうか
	bool drawFlag;					// 描画フラグ、true時に描画
public:
	// コンストラクタ
	Barricade();

	// 継承されたメンバー関数
	virtual void draw();
	void reset();

	void update(float frameTime);
	void damage();
};
#endif // !_BARRICADE_H
