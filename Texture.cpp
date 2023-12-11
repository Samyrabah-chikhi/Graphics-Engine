#include "Texture.h"



////Parameters
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
//
////Already in use
//stbi_image_free(bytes);
//glBindTexture(GL_TEXTURE_2D, 0);
//
////Time for bitmaps
//glGenerateMipmap(GL_TEXTURE_2D);
//
//GLuint tex0Uni = glGetUniformLocation(shader, "tex0");
//glUniform1i(tex0Uni, 0);

Texture::Texture(int widthImg, int heightImg, int colorChannel)
{

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(
        "C:\\Users\\Administrator\\Pictures\\wall.jpg",
        &widthImg, &heightImg, &colorChannel, 0
    );

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

}



