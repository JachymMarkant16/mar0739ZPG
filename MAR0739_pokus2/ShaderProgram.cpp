#include "ShaderProgram.h"
ShaderProgram::ShaderProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexShaderFileName);
        fShaderFile.open(fragmentShaderFileName);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    this->createAndCompileShaders(vertexCode.c_str(), fragmentCode.c_str());
}

ShaderProgram::ShaderProgram() {
    const char* vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);"
        "}";



    const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
        "}";
    this->createAndCompileShaders(vertex_shader, fragment_shader);
}

GLuint ShaderProgram::getShaderProgram() {
    return this->shaderProgram;
}

void ShaderProgram::createAndCompileShaders(const char* vertexShader, const char* fragmentShader) {
    //create and compile shaders
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &vertexShader, NULL);
    glCompileShader(this->vertexShader);
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &fragmentShader, NULL);
    glCompileShader(this->fragmentShader);
    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, this->fragmentShader);
    glAttachShader(shaderProgram, this->vertexShader);
    glLinkProgram(shaderProgram);

    //Error checks
    int  success;
    char infoLog[512];
    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
}