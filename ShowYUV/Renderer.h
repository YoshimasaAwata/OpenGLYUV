#pragma once

#include "Shader.h"
#include "Texture.h"

/**
* CRenderer
* ���ۂɃ����_�����O���s��
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
    * �R���X�g���N�^
    */
    CRenderer(const char* pFileName = nullptr);

    /**
    * �f�X�g���N�^
    */
    virtual ~CRenderer();

    /**
    * �`��
    */
    virtual void Render();

    /**
    * �T�C�Y�Z�b�g
    */
    virtual void SetSize(GLuint width, GLuint height);

    /**
    * ���̃e�N�X�`���Z�b�g
    */
    virtual HRESULT SetNextTexture();
};

