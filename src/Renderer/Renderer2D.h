#pragma once

#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
#include "glm/vec2.hpp"

#include <memory>

struct Colour { float r, g, b, a; };

#define APP_RESOURCE(path) "../resources/" path

class Renderer2D {
public:
	Renderer2D();

	void Begin();
	void End();

	void DrawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Colour& colour);
	void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& dimensions, Texture* texture);
	void DrawTriangle(const glm::vec2& position, const glm::vec2& dimensions, const Colour& colour);
	void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float& rotation);
private:
	void DrawQuad(const glm::vec2& position, const glm::vec2& dimensions, std::unique_ptr<Shader>& shader);
};