#pragma once

#include "Shader.h"
#include "Texture.h"

/**
* CRenderer
* 実際にレンダリングを行う
*/
class CRenderer
{
private:
    static const GLfloat VERTEX[];
    static const GLfloat TEXTURE[];

private:
    GLuint m_vertexArrayObjID;
    GLuint m_vbuffer;
    GLuint m_tbuffer;
    CShader* m_pShader;
    CTexture* m_pTexture;

public:
    /**
    * コンストラクタ
    */
    CRenderer(const char* pFileName = nullptr);

    /**
    * デストラクタ
    */
    virtual ~CRenderer();

    /**
    * 描画
    */
    virtual void Render();

    /**
    * サイズセット
    */
    virtual void SetSize(GLuint width, GLuint height);

    /**
    * 次のテクスチャセット
    */
    virtual HRESULT SetNextTexture();
};

