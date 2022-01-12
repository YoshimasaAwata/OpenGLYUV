#include "pch.h"
#include "Texture.h"

const std::string CTexture::YUV_FILE_NAME = "akiyo_cif.yuv";

CTexture::CTexture(const char* pFileName, GLuint width, GLuint height)
    : m_pFile(nullptr)
    , m_textureIDY(0)
    , m_textureIDU(0)
    , m_textureIDV(0)
    , m_pY(nullptr)
    , m_pU(nullptr)
    , m_pV(nullptr)
    , m_width(width)
    , m_height(height)
    , m_size(width * height)
{
    m_pFile = new std::ifstream(pFileName, std::ifstream::in | std::ifstream::binary);
    if ((nullptr == m_pFile) || !m_pFile->good())
    {
        delete m_pFile;
        throw std::runtime_error("Failed to open YUV file " + YUV_FILE_NAME);
    }

    m_pY = new GLubyte[m_size];
    m_pU = new GLubyte[m_size / 4];
    m_pV = new GLubyte[m_size / 4];

    SetTextureAttribute();

    SetNextFrame();
}

CTexture::~CTexture()
{
    if (nullptr != m_pFile)
    {
        m_pFile->close();
        delete m_pFile;
    }
    if (nullptr != m_pY)
    {
        delete[] m_pY;
    }
    if (nullptr != m_pU)
    {
        delete[] m_pU;
    }
    if (nullptr != m_pV)
    {
        delete[] m_pV;
    }
    if (0 != m_textureIDY)
    {
        glDeleteTextures(1, &m_textureIDY);
    }
    if (0 != m_textureIDU)
    {
        glDeleteTextures(1, &m_textureIDU);
    }
    if (0 != m_textureIDV)
    {
        glDeleteTextures(1, &m_textureIDV);
    }
}

HRESULT CTexture::SetNextFrame()
{
    HRESULT hr = ReadYUV();
    if (S_OK == hr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureIDY);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, m_pY);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_textureIDU);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width / 2, m_height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, m_pU);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_textureIDV);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width / 2, m_height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, m_pV);
    }
    return hr;
}

void CTexture::SetTextureAttribute()
{
    glGenTextures(1, &m_textureIDY);
    glBindTexture(GL_TEXTURE_2D, m_textureIDY);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenTextures(1, &m_textureIDU);
    glBindTexture(GL_TEXTURE_2D, m_textureIDU);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenTextures(1, &m_textureIDV);
    glBindTexture(GL_TEXTURE_2D, m_textureIDV);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

HRESULT CTexture::ReadYUV()
{
    HRESULT hr = S_FALSE;

    if ((nullptr != m_pFile) && (m_pFile->good()))
    {
        if (!m_pFile->eof())
        {
            m_pFile->read(reinterpret_cast<char*>(m_pY), m_size);
            m_pFile->read(reinterpret_cast<char*>(m_pU), m_size / 4);
            m_pFile->read(reinterpret_cast<char*>(m_pV), m_size / 4);
            hr = S_OK;
        }
    }

    return hr;
}
