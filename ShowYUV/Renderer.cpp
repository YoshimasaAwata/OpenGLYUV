#include "pch.h"
#include "Renderer.h"

const GLfloat CRenderer::TEXTURE[] =
{
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

const GLfloat CRenderer::VERTEX[] =
{
    -(CTexture::CIF_WIDTH / 2.0f), -(CTexture::CIF_HEIGHT / 2.0f), 0.0f,
    -(CTexture::CIF_WIDTH / 2.0f),   CTexture::CIF_HEIGHT / 2.0f,  0.0f,
      CTexture::CIF_WIDTH / 2.0f,    CTexture::CIF_HEIGHT / 2.0f,  0.0f,
      CTexture::CIF_WIDTH / 2.0f,  -(CTexture::CIF_HEIGHT / 2.0f), 0.0f,
};

CRenderer::CRenderer(const char* pFileName)
    : m_vertexArrayObjID(0)
    , m_vbuffer(0)
    , m_tbuffer(0)
    , m_pShader(nullptr)
    , m_pTexture(nullptr)
{
    glGenVertexArrays(1, &m_vertexArrayObjID);
    glBindVertexArray(m_vertexArrayObjID);
    glGenBuffers(1, &m_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX), VERTEX, GL_STATIC_DRAW);
    glGenBuffers(1, &m_tbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_tbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TEXTURE), TEXTURE, GL_STATIC_DRAW);
    m_pShader = new CShader();
    m_pTexture = new CTexture(pFileName);
}

CRenderer::~CRenderer()
{
    if (nullptr != m_pTexture)
    {
        delete m_pTexture;
    }
    if (nullptr != m_pShader)
    {
        delete m_pShader;
    }
    glDeleteBuffers(1, &m_tbuffer);
    glDeleteBuffers(1, &m_vbuffer);
    glDeleteVertexArrays(1, &m_vertexArrayObjID);
}

void CRenderer::Render()
{
    glEnableVertexAttribArray(CShader::POSITION_ID);
    glEnableVertexAttribArray(CShader::TEXTURE_ID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbuffer);
    glVertexAttribPointer(
        CShader::POSITION_ID,   // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
        3,                      // サイズ
        GL_FLOAT,               // タイプ
        GL_FALSE,               // 正規化？
        0,                      // ストライド
        (void*)0                // 配列バッファオフセット
    );

    glBindBuffer(GL_ARRAY_BUFFER, m_tbuffer);
    glVertexAttribPointer(
        CShader::TEXTURE_ID,      // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
        2,                      // サイズ
        GL_FLOAT,               // タイプ
        GL_FALSE,               // 正規化？
        0,                      // ストライド
        (void*)0                // 配列バッファオフセット
    );

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。

    glDisableVertexAttribArray(CShader::TEXTURE_ID);
    glDisableVertexAttribArray(CShader::POSITION_ID);
}

void CRenderer::SetSize(GLuint width, GLuint height)
{
    if (nullptr != m_pShader)
    {
        double tempH = static_cast<double>(CTexture::CIF_WIDTH) * height / width;
        double tempW;
        if (tempH > CTexture::CIF_HEIGHT)
        {
            tempW = static_cast<double>(CTexture::CIF_WIDTH);
        }
        else
        {
            tempH = static_cast<double>(CTexture::CIF_HEIGHT);
            tempW = static_cast<double>(CTexture::CIF_HEIGHT) * width / height;
        }
        m_pShader->SetTransformationMatrix(-tempW / 2, tempW / 2, -tempH / 2, tempH / 2);
    }
}

HRESULT CRenderer::SetNextTexture()
{
    HRESULT hr = S_FALSE;
    if (nullptr != m_pTexture)
    {
        hr = m_pTexture->SetNextFrame();
    }
    return hr;
}
