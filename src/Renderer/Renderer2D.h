#pragma once

#include "OpenGL/Texture.h"
#include "OpenGL/Shader.h"
#include <OpenGL/OrthographicCamera.h>
#include "glm/vec2.hpp"
#include "Core/Colour.h"

#include <memory>

#define BASE_APP_PATH "../resources/"
#define APP_RESOURCE(path) BASE_APP_PATH path

class Renderer2D {
public:
	Renderer2D();

	void Begin(OrthographicCamera& camera);
	void End();

	void DrawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Colour& colour);
	void DrawOutlineQuad(const glm::vec2& position, const glm::vec2& dimensions, const Colour& colour, const float& outlineThickness = 0.1f);
	void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& dimensions, Texture* texture);
	void DrawTriangle(const glm::vec2& position, const glm::vec2& dimensions, const Colour& colour);
	void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float& rotation);
private:
	void DrawQuad(const glm::vec2& position, const glm::vec2& dimensions, std::unique_ptr<Shader>& shader);

	glm::mat4 viewProjection;
};

extern Renderer2D* g_Renderer;