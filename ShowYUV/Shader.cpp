#include "pch.h"
#include "Shader.h"

const std::string CShader::VERTEX_FILE = "Shader.vert";
const std::string CShader::FRAGMENT_FILE = "Shader.frag";

CShader::CShader()
    : m_programID(0)
    , m_vertexID(0)
    , m_fragmentID(0)
{
    m_programID = glCreateProgram();
    if (0 == m_programID)
    {
        throw std::runtime_error("Failed to create new program.");
    }

    m_vertexID = glCreateShader(GL_VERTEX_SHADER);
    if (0 == m_vertexID)
    {
        DeleteAllObjects();
        throw std::runtime_error("Failed to create new vertex shader.");
    }
    try
    {
        ReadProgram(m_vertexID, VERTEX_FILE);
    }
    catch (std::runtime_error e)
    {
        DeleteAllObjects();
        throw;
    }

    m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == m_fragmentID)
    {
        DeleteAllObjects();
        throw std::runtime_error("Failed to create new fragment shader.");
    }
    try
    {
        ReadProgram(m_fragmentID, FRAGMENT_FILE);
    }
    catch (std::runtime_error e)
    {
        DeleteAllObjects();
        throw;
    }

    glBindAttribLocation(m_programID, POSITION_ID, "position");
    glBindAttribLocation(m_programID, TEXTURE_ID, "vertexUV");

    glLinkProgram(m_programID);

    glUseProgram(m_programID);

    SetTextureSampler();
}

CShader::~CShader()
{
    DeleteAllObjects();
}

void CShader::SetTransformationMatrix(double left, double right, double bottom, double top)
{
    glm::mat4 Projection = glm::ortho(left, right, bottom, top);
    glm::mat4 View = glm::lookAt(
        glm::vec3(0, 0, 1), // ワールド空間でカメラは(4,3,3)にあります。
        glm::vec3(0, 0, 0), // 原点を見ています。
        glm::vec3(0, 1, 0)  // 頭が上方向(0,-1,0にセットすると上下逆転します。)
    );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 MVP = Projection * View * Model;

    GLuint MatrixID = glGetUniformLocation(m_programID, "modelViewProj");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

void CShader::DeleteAllObjects()
{
    glDetachShader(m_programID, m_fragmentID);
    glDetachShader(m_programID, m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteShader(m_vertexID);
    glDeleteProgram(m_programID);
}

void CShader::ReadProgram(GLuint shaderID, const std::string& file_name)
{
    // ファイルからソースコードを読み込み
    std::ifstream sourceFile;
    sourceFile.open(file_name, std::ios::in | std::ios::binary | std::ios::ate);
    if (!sourceFile.is_open())
    {
        throw std::runtime_error("Failed to open shader file " + file_name);
    }

    size_t size = sourceFile.tellg();
    sourceFile.seekg(0, sourceFile.beg);
    if (size <= 0)
    {
        sourceFile.close();
        throw std::runtime_error("Failed to read shader file " + file_name);
    }

    std::vector<char> source(size + 1);
    char* psource = source.data();
    sourceFile.read(psource, size);
    sourceFile.close();
    *(psource + size) = '\0';

    // ソースコードをコンパイルしてプログラムにアタッチ
    glShaderSource(shaderID, 1, &psource, NULL);
    glCompileShader(shaderID);
    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        // コンパイル失敗ならエラーログ出力
        std::vector<char> info(256);
        GLsizei len;
        glGetShaderInfoLog(shaderID, 256, &len, info.data());
        _RPT0(_CRT_ERROR, info.data());
        throw std::runtime_error("Failed to compile shader file" + file_name);
    }

    glAttachShader(m_programID, shaderID);
}

void CShader::SetTextureSampler()
{
    // GLSL内のTextureSamplerにIDを割り振り
    GLint samplerIDY = glGetUniformLocation(m_programID, "textureSamplerY");
    glUniform1i(samplerIDY, 0); // GL_TEXTURE0
    GLint samplerIDU = glGetUniformLocation(m_programID, "textureSamplerU");
    glUniform1i(samplerIDU, 1); // GL_TEXTURE1
    GLint samplerIDV = glGetUniformLocation(m_programID, "textureSamplerV");
    glUniform1i(samplerIDV, 2); // GL_TEXTURE2
}
