#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "stb_image.h"
#include <glad/glad.h>

class Texture
{
public:
	int widthImg, heightImg, colorChannel;
	GLuint texture;


	Texture(int widthImg, int heightImg, int colorChannel);

};
#endif

