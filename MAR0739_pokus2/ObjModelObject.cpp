#include "ObjModelObject.h"
ObjModelObject::ObjModelObject(const char* filename, ShaderProgramType shaderProgram, std::string textureName, bool loop, glm::mat4 defaultMat) {
    this->loop = loop;
    int indicesCount = 0;
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // slouèení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

        //aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    const aiScene* scene = importer.ReadFile(filename, importOptions);
    getMeshFromObj(scene);
    InitVars(shaderProgram, defaultMat);
    InitVBO(this->points, this->sizeOfPoints);
    InitVAO();
    InitIBO();
    SetVertexAttribs(shaderProgram);
    TextureController* texController = texController->getInstance();
    textureSpace = texController->getTextureByName(textureName);
}

void ObjModelObject::getMaterialFromObj(aiScene* scene) {
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
    {
        const aiMaterial* mat = scene->mMaterials[i];

        aiString name;
        mat->Get(AI_MATKEY_NAME, name);
        printf("Material [%d] name %s\n", i, name.C_Str());

        aiColor4D d;

        glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
            diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        printf("Color: %f %f %f %f\n", d.r, d.g, d.b, d.a);
    }
}
void ObjModelObject::getMeshFromObj(const aiScene* scene) {


    for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
    {
        aiMesh* mesh = scene->mMeshes[i];

        Vertex* pVertices = new Vertex[mesh->mNumVertices];
        std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            if (mesh->HasPositions())
            {
                pVertices[i].Position[0] = mesh->mVertices[i].x;
                pVertices[i].Position[1] = mesh->mVertices[i].y;
                pVertices[i].Position[2] = mesh->mVertices[i].z;
            }
            if (mesh->HasNormals())
            {
                pVertices[i].Normal[0] = mesh->mNormals[i].x;
                pVertices[i].Normal[1] = mesh->mNormals[i].y;
                pVertices[i].Normal[2] = mesh->mNormals[i].z;
            }
            if (mesh->HasTextureCoords(0))
            {
                pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
            }
            if (mesh->HasTangentsAndBitangents())
            {
                pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                pVertices[i].Tangent[2] = mesh->mTangents[i].z;
            }

        }

        unsigned int* pIndices = nullptr;

        if (mesh->HasFaces())
        {

            pIndices = new unsigned int[mesh->mNumFaces * 3];
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
            }
        }
        this->indices_count = mesh->mNumFaces * 3;
        this->points = pVertices;
        this->sizeOfPoints = mesh->mNumVertices;
        this->num_of_faces = mesh->mNumFaces;
        this->indices = pIndices;
    }
}

void ObjModelObject::DrawObject(glm::mat4 view, glm::mat4 projection) {
    if (loop) {
        loopModel();
    }
    glUseProgram(this->shaderProgram->getShaderProgram());
    glBindVertexArray(this->VAO);


    int modelLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->modelMatrix));
    int viewLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLint uniformID = glGetUniformLocation(this->shaderProgram->getShaderProgram(), "textureUnitID");
    glUniform1i(uniformID, this->textureSpace);

    // draw triangles
    glDrawElements(GL_TRIANGLES, this->indices_count, GL_UNSIGNED_INT, NULL); //mode,first,count

    glBindVertexArray(0);
}

void ObjModelObject::InitIBO() {
    glGenBuffers(1, &IBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->num_of_faces * 3, this->indices, GL_STATIC_DRAW);
}

void ObjModelObject::loopModel() {
    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * A * glm::transpose(B);
    this->modelMatrix = glm::translate(glm::mat4(1.0f), p);
    this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(0.015));
    if (t >= 1.0f || t <= 0.0f) delta *= -1;
    t += delta;
}