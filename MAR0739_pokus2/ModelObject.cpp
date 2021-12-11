#include "ModelObject.h"

ModelObject::ModelObject(float* points, int sizeOfPoints, ShaderProgramType shaderProgram, bool modelIsSkybox) {
    this->isSkybox = modelIsSkybox;
    InitVars(shaderProgram);
    InitVBO(points, sizeOfPoints);
    InitVAO();
    SetVertexAttribs(shaderProgram);
}

void ModelObject::DrawObject(glm::mat4 view, glm::mat4 projection) {
    if (this->isSkybox) {
        glDepthMask(GL_FALSE);
    }
    glUseProgram(this->shaderProgram->getShaderProgram());
    glBindVertexArray(this->VAO);


    int modelLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
    int viewLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "view");
    if (this->isSkybox) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(view))));
    }
    else {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    int projectionLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    if (this->isSkybox) {
        GLint uniformID = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "skybox");
        glUniform1i(uniformID, 0);
    }
    else {
        GLint uniformID = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "textureUnitID");
        glUniform1i(uniformID, 1);
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


