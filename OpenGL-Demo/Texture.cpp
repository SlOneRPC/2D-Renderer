#include "Texture.h"
#include "CommonRender.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
		_ASSERT(0);

	stbi_image_free(data);
}

Texture::Texture(const Texture& texture)
{
	*this = texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE_2D + slot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}