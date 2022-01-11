#pragma once

#include "Renderer.h"

/**
* CWindow
* OpenGL��GLFW�ŃE�B���h�E��\��
*/
class CWindow
{
private:
    static const std::string DEF_TITLE;
    static std::mutex init;
    static int init_count;

private:
    // �E�B���h�E�̃n���h��
    GLFWwindow* m_pWindow;
    CRenderer* m_pRenderer;

public:
    /**
    * �R���X�g���N�^
    */
    CWindow(
        UINT width = CTexture::CIF_WIDTH, 
        UINT height = CTexture::CIF_HEIGHT,
        const char* pFileName = nullptr,
        const char* pTitle = DEF_TITLE.c_str());

    /**
    * �f�X�g���N�^
    */
    virtual ~CWindow();

    /**
    * �`��
    */
    virtual HRESULT Render();

protected:
    /**
    * OpenGL��������
    */
    virtual void InitOpenGL();

    /**
    * OpenGL��������
    */
    virtual void TerminateOpenGL();

    /**
    * �E�B���h�E�T�C�Y���Z�b�g
    */
    void SetSize(GLuint width, GLuint height);

    /**
    * �E�B���h�E�̃T�C�Y�ύX���̃R�[���o�b�N�֐�
    */
    static void Resize(GLFWwindow* const window, int width, int height);

};

