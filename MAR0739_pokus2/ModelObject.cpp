#include "ModelObject.h"

ModelObject::ModelObject(float* points, int sizeOfPoints, ShaderProgram shaderProgram) {
    initObject(points, sizeOfPoints, shaderProgram);
}

void ModelObject::DrawObject(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    glUseProgram(this->shaderProgram.getShaderProgram());
    glBindVertexArray(this->VAO);

    int modelLoc = glGetUniformLocation(this->shaderProgram.getShaderProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(this->shaderProgram.getShaderProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(this->shaderProgram.getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint uniformID = glGetUniformLocation(this->shaderProgram.getShaderProgram(), "textureUnitID");
    glUniform1i(uniformID, 0);

    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, this->sizeOfPoints); //mode,first,count
}

ModelObject::ModelObject() {
    float points[] = {
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
    };
    ShaderProgram program;
    initObject(points, sizeof(points), program);
}

void ModelObject::initObject(float* points, int sizeOfPoints, ShaderProgram shaderProgram) {
    this->sizeOfPoints = sizeOfPoints;
    this->points = points;
    this->shaderProgram = shaderProgram;
    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfPoints, points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); //enable vertex attributes
}

