//==========================================================
/// @file
/// @brief    attackEffect.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#include "attackEffect.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
AttackEffect::AttackEffect() : Image()
{
	visible = false;								// 非表示がデフォルト
	spriteData.width = attackEffectNS::WIDTH;		// １つの画像のサイズ
	spriteData.height = attackEffectNS::HEIGHT;
	spriteData.rect.bottom = attackEffectNS::HEIGHT;// 画像内の選択する部分
	spriteData.rect.right = attackEffectNS::WIDTH;
	cols = attackEffectNS::TEXTURE_COLS;			// テクスチャの列数
	frameDelay = attackEffectNS::ANIMATION_DELAY;	// アニメーションの各フレームの間隔
	startFrame = attackEffectNS::START_FRAME;		// アニメーションの最初のフレーム
	endFrame = attackEffectNS::END_FRAME;			// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
	spriteData.scale = attackEffectNS::SCALE;		// スプライトのスケール
	loop = false;									// アニメーションはループさせない
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void AttackEffect::update(float frameTime)
{
	// スプライトが非表示なら何もしない
	if (getVisible() == false)
		return;
	// 画像を更新
	Image::update(frameTime);
	// アニメーションが終了した場合、スプライトを非表示にする
	if (getAnimationComplete())
		setVisible(false);
}

//==========================================================
// Attack
// この関数が呼ばれると攻撃の衝撃波のアニメーションが発動
//==========================================================
void AttackEffect::attack(Brave &brave)
{
	// brave（プレイヤー）の向きによって表示させる位置を分岐
	// プレイヤーの元々の画像が偏っているので、±10程度の補正をかけている
	switch (brave.getDirection())
	{
	case characterNS::RIGHT:	// 右
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10);
		setDegrees(0);
		flipHorizontal(false);
		break;
	case characterNS::LEFT:		// 左
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10);
		setDegrees(0);
		flipHorizontal(true);
		break;
	case characterNS::UP:		// 上
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10 - 10);
		setDegrees(40.0f);
		flipHorizontal(true);
		break;
	case characterNS::DOWN:		// 下
		setX(brave.getCenterX() - getWidth() * getScale() / 2.0f - 10);
		setY(brave.getCenterY() - getHeight() * getScale() / 2.0f - 10 + 10);
		setDegrees(230.0f);
		flipHorizontal(true);
		break;
	}
	// スプライトを表示
	visible = true;
	// 現在のフレームをアニメーションの最初のフレームにセット
	setCurrentFrame(startFrame);
}