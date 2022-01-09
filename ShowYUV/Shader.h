#pragma once

/**
* CShader
* �V�F�[�_�[�v���O������ǂݍ���Őݒ�
*/
class CShader
{
public:
    static const GLuint POSITION_ID = 0;
    static const GLuint TEXTURE_ID  = 1;

private:
    static const std::string VERTEX_FILE;
    static const std::string FRAGMENT_FILE;

private:
    GLuint m_programID;
    GLuint m_vertexID;      // �o�[�e�b�N�X�V�F�[�_�̔ԍ�
    GLuint m_fragmentID;    // �t���O�����g�V�F�[�_�̔ԍ�

public:
    CShader();
    virtual ~CShader();
    void SetTransformationMatrix(double left, double right, double bottom, double top);

protected:
    void DeleteAllObjects();
    void ReadProgram(GLuint shaderID, const std::string& file_name);
    void SetTextureSampler();
};

