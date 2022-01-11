#pragma once

#include "Renderer.h"

/**
* CWindow
* OpenGLのGLFWでウィンドウを表示
*/
class CWindow
{
private:
    static const std::string DEF_TITLE;
    static std::mutex init;
    static int init_count;

private:
    // ウィンドウのハンドル
    GLFWwindow* m_pWindow;
    CRenderer* m_pRenderer;

public:
    /**
    * コンストラクタ
    */
    CWindow(
        UINT width = CTexture::CIF_WIDTH, 
        UINT height = CTexture::CIF_HEIGHT,
        const char* pFileName = nullptr,
        const char* pTitle = DEF_TITLE.c_str());

    /**
    * デストラクタ
    */
    virtual ~CWindow();

    /**
    * 描画
    */
    virtual HRESULT Render();

protected:
    /**
    * OpenGLを初期化
    */
    virtual void InitOpenGL();

    /**
    * OpenGLを初期化
    */
    virtual void TerminateOpenGL();

    /**
    * ウィンドウサイズをセット
    */
    void SetSize(GLuint width, GLuint height);

    /**
    * ウィンドウのサイズ変更時のコールバック関数
    */
    static void Resize(GLFWwindow* const window, int width, int height);

};

