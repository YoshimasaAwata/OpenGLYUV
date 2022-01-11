#include "pch.h"
#include "Window.h"

const std::string CWindow::DEF_TITLE = "Show YUV";
std::mutex CWindow::init;
int CWindow::init_count = 0;

CWindow::CWindow(UINT width, UINT height, const char* pFileName, const char* pTitle)
    : m_pWindow(NULL)
    , m_pRenderer(nullptr)
{
    InitOpenGL();

    m_pWindow = glfwCreateWindow(width, height, pTitle, NULL, NULL);
    if (NULL == m_pWindow)
    {
        throw std::runtime_error("Failed to create opengl window using GLFW.");
    }
    // ���݂̃E�B���h�E�������Ώۂɂ���
    glfwMakeContextCurrent(m_pWindow);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // GLEW������������
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        TerminateOpenGL();
        throw std::runtime_error("Failed to initialize GLEW.");
    }

    // ���������̃^�C�~���O��҂�
    glfwSwapInterval(1);

    // ���̃C���X�^���X�� this �|�C���^���L�^���Ă���
    glfwSetWindowUserPointer(m_pWindow, this);

    // �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
    glfwSetWindowSizeCallback(m_pWindow, Resize);

    m_pRenderer = new CRenderer(pFileName);

    // �J�����E�B���h�E�̏����ݒ�
    Resize(m_pWindow, width, height);

}

CWindow::~CWindow()
{
    if (nullptr != m_pRenderer)
    {
        delete m_pRenderer;
    }
    glfwDestroyWindow(m_pWindow);
    TerminateOpenGL();
}

HRESULT CWindow::Render()
{
    HRESULT hr = S_FALSE;
    if (nullptr != m_pRenderer)
    {
        hr = m_pRenderer->SetNextTexture();
        if (S_OK == hr)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            m_pRenderer->Render();
            glfwSwapBuffers(m_pWindow);
        }
    }
    return hr;
}

void CWindow::InitOpenGL()
{
    init.lock();

    if (init_count == 0)
    {
        // GLFW������������
        if (GL_FALSE == glfwInit())
        {
            init.unlock();
            throw std::runtime_error("Failed to initialize opengl using GLFW.");
        }

        // OpenGL Version 3.3 Core Profile ��I������
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    init_count++;

    init.unlock();
}

void CWindow::TerminateOpenGL()
{
    init.lock();
    if (--init_count <= 0)
    {
        glfwTerminate();
    }
    init.unlock();
}

void CWindow::SetSize(GLuint width, GLuint height)
{
    if (nullptr != m_pRenderer)
    {
        m_pRenderer->SetSize(width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        m_pRenderer->Render();
        glfwSwapBuffers(m_pWindow);
    }
}

void CWindow::Resize(GLFWwindow* const window, int width, int height)
{
    // �t���[���o�b�t�@�̃T�C�Y�𒲂ׂăt���[���o�b�t�@�S�̂��r���[�|�[�g�ɐݒ肷��
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // window�Ɋ֘A�t�����Ă���C���X�^���X���擾���A�T�C�Y���Z�b�g
    CWindow* const pinstance = static_cast<CWindow*>(glfwGetWindowUserPointer(window));
    if (NULL != pinstance)
    {
        pinstance->SetSize(fbWidth, fbHeight);
    }
}
