//==========================================================
/// @file
/// @brief    inputDialog.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "inputDialog.h"

//=============================================================================
// コンストラクタ
//=============================================================================
InputDialog::InputDialog()
{
    mTextBackColor = inputDialogNS::TEXT_BACK_COLOR;
    mTextFontColor = inputDialogNS::TEXT_COLOR;
    mInTextVerts = NULL;
    mInText = "";
}

//=============================================================================
// デストラクタ
//=============================================================================
InputDialog::~InputDialog()
{
    onLostDevice();            // すべてのグラフィックアイテムについてonLostDevice()を呼び出す
}

//=============================================================================
// ダイアログの背景とボタンを描画するために頂点バッファを準備
//=============================================================================
void InputDialog::prepareVerts()
{
    MessageDialog::prepareVerts();  // 基本クラスのprepareVertsを呼び出す
    SAFE_RELEASE(mInTextVerts);

    // inText top left
    mVtx[0].x = mX + messageDialogNS::BORDER*2;
    mVtx[0].y = mY + mHeight - messageDialogNS::BORDER - messageDialogNS::MARGIN - messageDialogNS::BUTTON_HEIGHT*2.5f;
    mVtx[0].z = 0.0f;
    mVtx[0].rhw = 1.0f;
    mVtx[0].color = mTextBackColor;
    // inText top right
    mVtx[1].x = mX + mWidth - messageDialogNS::BORDER*2;
    mVtx[1].y = mVtx[0].y;
    mVtx[1].z = 0.0f;
    mVtx[1].rhw = 1.0f;
    mVtx[1].color = mTextBackColor;
    // inText bottom right
    mVtx[2].x =  mVtx[1].x;
    mVtx[2].y = mVtx[0].y + messageDialogNS::BUTTON_HEIGHT;
    mVtx[2].z = 0.0f;
    mVtx[2].rhw = 1.0f;
    mVtx[2].color = mTextBackColor;
    // inText bottom left
    mVtx[3].x = mVtx[0].x;
    mVtx[3].y = mVtx[2].y;
    mVtx[3].z = 0.0f;
    mVtx[3].rhw = 1.0f;
    mVtx[3].color = mTextBackColor;
    mGraphics->createVertexBuffer(mVtx, sizeof mVtx, mInTextVerts);

    // set inTextRect
    mInTextRect.left   = (long)mVtx[0].x;
    mInTextRect.right  = (long)mVtx[1].x;
    mInTextRect.top    = (long)mVtx[0].y;
    mInTextRect.bottom = (long)mVtx[2].y;
}

//=============================================================================
// InputDialogを描画
//=============================================================================
const void InputDialog::draw()
{
    if (!mVisible || mGraphics == NULL || !mInitialized)
        return;

    mGraphics->drawQuad(mBorderVerts);        // draw border
    mGraphics->drawQuad(mDialogVerts);        // draw backdrop
    mGraphics->drawQuad(mButtonVerts);        // draw button
    mGraphics->drawQuad(mButton2Verts);       // draw button2
    mGraphics->drawQuad(mInTextVerts);        // draw input text area

    mGraphics->spriteBegin();                // begin drawing sprites

    if(mText.size() == 0)
        return;
    // display text on MessageDialog
    mDxFont.setFontColor(mFontColor);
    mDxFont.print(mText,mTextRect,DT_CENTER|DT_WORDBREAK);

    // display text on buttons
    mDxFont.setFontColor(mButtonFontColor);
    mDxFont.print(messageDialogNS::BUTTON1_TEXT[mButtonType],mButtonRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
    mDxFont.print(messageDialogNS::BUTTON2_TEXT[mButtonType],mButton2Rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);

    // display input text
    mDxFont.setFontColor(mTextFontColor);
    mTempRect = mInTextRect;      // save
    // No text is printed with DT_CALDRECT option. It moves RECT.right
    mDxFont.print(mInText,mTempRect,DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
    if(mTempRect.right > mInTextRect.right)   // if text too long, right justify
        mDxFont.print(mInText,mInTextRect,DT_SINGLELINE|DT_RIGHT|DT_VCENTER);
    else    // else, left justify
        mDxFont.print(mInText,mInTextRect,DT_SINGLELINE|DT_LEFT|DT_VCENTER);

    mGraphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// DIALOG_CLOSE_KEYとボタンのマウスクリックをチェック
//=============================================================================
void InputDialog::update()
{
    MessageDialog::update();        // call update in base class
    if (!mInitialized || !mVisible)
    {
        if(mButtonClicked == 2)      // if Cancel button
            mInText = "";            // clear input text
        return;
    }
    mInText = mInput->getTextIn();    // get input text
}

//=============================================================================
// テキストstrをInputDialogに表示
//=============================================================================
void InputDialog::print(const std::string &str)         
{
    if (!mInitialized || mVisible)    // if not initialized or already in use
        return;
    mText = str + "\n\n\n\n\n";   // leave some room for input text and buttons

    // Set textRect to text area of dialog
    mTextRect.left   = (long)(mX + messageDialogNS::MARGIN);
    mTextRect.right  = (long)(mX + messageDialogNS::WIDTH - messageDialogNS::MARGIN);
    mTextRect.top    = (long)(mY + messageDialogNS::MARGIN);
    mTextRect.bottom = (long)(mY + messageDialogNS::HEIGHT - messageDialogNS::MARGIN);

    // Set textRect.bottom to precise height required for text
    // No text is printed with DT_CALDRECT option.
    mDxFont.print(mText,mTextRect,DT_CENTER|DT_WORDBREAK|DT_CALCRECT);
    mHeight = mTextRect.bottom - (int)mY + messageDialogNS::BORDER + messageDialogNS::MARGIN;

    prepareVerts();                 // prepare the vertex buffers
    mInText = "";                    // clear old input
    mInput->clearTextIn();
    mButtonClicked = 0;              // clear buttonClicked
    mVisible = true;
}

//=============================================================================
// グラフィックスデバイスが消失したときに呼び出す
//=============================================================================
void InputDialog::onLostDevice()
{
    if (!mInitialized)
        return;
    MessageDialog::onLostDevice();
    SAFE_RELEASE(mInTextVerts);
}

