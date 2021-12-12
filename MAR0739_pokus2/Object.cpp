#include "Object.h"
void Object::MoveRight(int size){
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(0, 0, size));
}
void Object::Scale(int size) {
    this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(size, 0, size));
}
void Object::SetVertexAttribs(ShaderProgramType shaderProgram) {
    switch (shaderProgram) {
    case ShaderProgramType::SkyBox:
    case ShaderProgramType::TwoD:
        glEnableVertexAttribArray(0); //enable vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1); //enable vertex attributes
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        break;
    case ShaderProgramType::ThreeD:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
        break;
    }
}

void Object::InitVars(ShaderProgramType shaderProgram, glm::mat4 defaultMat) {
    this->shaderProgram = ShaderProgramFactory::createShaderProgram(shaderProgram);
    this->modelMatrix = defaultMat;
}
void Object::InitVAO() {
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(VAO);
}
void Object::InitVBO(float* points, int sizeOfPoints) {
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfPoints, points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    this->VBO = VBO;
    this->sizeOfPoints = sizeOfPoints;
}
void Object::InitVBO(Vertex* points, int sizeOfPoints) {
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * sizeOfPoints, points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    this->VBO = VBO;
    this->sizeOfPoints = sizeOfPoints;
}