#pragma once
#include <string>

class Texture {
public:
	Texture(const std::string& path);
	Texture(const Texture& texture);
	~Texture();

	void Bind(unsigned int slot);
private:
	unsigned int textureId;
};