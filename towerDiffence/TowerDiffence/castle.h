#ifndef _CASTLE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _CASTLE_H		// 多重に定義されることを防ぎます。

#include "entity.h"
#include "constants.h"
#include "enemy.h"
#include "midBoss.h"

namespace castleNS
{
	const int WIDTH = 120;			// 画像の幅（各フレーム）
	const int HEIGHT = 120;			// 画像の高さ
	const int TEXTURE_COLS = 2;
	const int X = 18.3 * 30;	// 初期位置
	const int Y = 9.5 * 30;
	const int START_FRAME = 1;
}

class Castle : public Entity		// Entityクラスを継承
{
private:
	float timeCounter;				// ダメージアニメーション用のタイマー
	float totalTimeCounter;
	bool death;						// 城が死亡時にtrue
	bool isDamaged;					// ダメージを受けている状態かどうか
	bool drawFlag;					// 描画フラグ、true時に描画
	float damagePer;                // ダメージを受ける時に掛ける割合
public:
	// コンストラクタ
	Castle();

	// 継承されたメンバー関数
	virtual void draw();
	void update(float frameTime);
	void damage(WEAPON);
	void reset();

	// getter
	bool isDeath() { return death; }

	// setter
	void setDeath(bool d) { death = d; }
	void setDamagePer(float per) { damagePer = per; }
};

#endif // !_CASTLE_H
