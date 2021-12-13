#include "ModelObject.h"

ModelObject::ModelObject(float* points, int sizeOfPoints, ShaderProgramType shaderProgram, std::string textureName, bool modelIsSkybox, glm::mat4 initPos) {
    this->isSkybox = modelIsSkybox;
    InitVars(shaderProgram, initPos);
    InitVBO(points, sizeOfPoints);
    InitVAO();
    SetVertexAttribs(shaderProgram);
    TextureController* texController = texController->getInstance();
    textureSpace = texController->getTextureByName(textureName);
}

void ModelObject::DrawObject(Camera* camera, glm::mat4 projection) {
    if (this->isSkybox) {
        glDepthMask(GL_FALSE);
    }
    glUseProgram(this->shaderProgram->getShaderProgram());
    glBindVertexArray(this->VAO);


    int modelLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
    int viewLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "view");
    if (this->isSkybox) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(camera->getView()))));
    }
    else {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
    }
    int projectionLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    if (this->isSkybox) {
        GLint uniformID = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "skybox");
        glUniform1i(uniformID, this->textureSpace);
    }
    else {
        GLint uniformID = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "textureUnitID");
        glUniform1i(uniformID, this->textureSpace);
    }

    // draw triangles
    glDrawArrays(GL_TRIANGLES, 0, this->sizeOfPoints); //mode,first,count

    if(this->isSkybox)
        glDepthMask(GL_TRUE);
    glBindVertexArray(0);
}

ModelObject::ModelObject() {
    float points[] = {
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
    };
    ShaderProgram program;
}


