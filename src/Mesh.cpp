#include "../headers/Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vao.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(float)));
    vao.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6*sizeof(float)));
    vao.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    vao.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera)
{
    shader.Activate();
    vao.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (int i = 0; i < textures.size(); i++) {

        std::string num;
        std::string type = textures[i].type;

        if (type=="diffuse"){
            num = std::to_string(numDiffuse++);
        }
        else if (type=="specular"){
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type+num).c_str(), i);
        textures[i].Bind();
    }

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.camPosition.x, camera.camPosition.y, camera.camPosition.z);
    camera.Matrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}