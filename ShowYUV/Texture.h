#pragma once

class CTexture
{
public:
    static const UINT CIF_WIDTH = 352;
    static const UINT CIF_HEIGHT = 288;
    static const std::string YUV_FILE_NAME;

private:
    std::ifstream* m_pFile;
    GLuint m_textureIDY;
    GLuint m_textureIDU;
    GLuint m_textureIDV;
    GLubyte* m_pY;
    GLubyte* m_pU;
    GLubyte* m_pV;
    GLuint* m_pRGB;
    GLuint m_width;
    GLuint m_height;
    GLuint m_size;

public:
    CTexture(const char* pFileName = YUV_FILE_NAME.c_str(), GLuint width = CIF_WIDTH, GLuint height = CIF_HEIGHT);
    virtual ~CTexture();
    virtual HRESULT SetNextFrame();

protected:
    void SetTextureAttribute();
    HRESULT ReadYUV();
};

