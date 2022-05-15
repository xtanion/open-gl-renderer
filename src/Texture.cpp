#include "../headers/Texture.h"

Texture::Texture(const char *imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    // Loading the image
    type = texType;
    int widthImg, heightImg, numColorCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgBytes = stbi_load(imagePath, &widthImg, &heightImg, &numColorCh, 0);

    glGenTextures(1, &ID);
    // Activating Texture slot 0
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Modifying the Texture
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Generating the Texture
    if (imgBytes) {
        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, imgBytes);
        glGenerateMipmap(texType);  // Mipmap on
    }
    else
    {
        std::cout << "Failed to load Texture" << std::endl;
    }

    stbi_image_free(imgBytes);
    glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}
void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
