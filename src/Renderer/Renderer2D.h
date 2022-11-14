#pragma once

struct Vector2 { float x, y, z; };
struct Colour { float r, g, b, a; };

#define APP_RESOURCE(path) "../resources/" path

class Renderer2D {
public:
	void Begin();
	void End();

	void DrawQuad(const Vector2& position, const Vector2& dimensions, const Colour& colour);
	void DrawTexturedQuad(const Vector2& position, const Vector2& dimensions, const char* texturePath);
	void DrawTriangle(const Vector2& position, const Vector2& dimensions, const Colour& colour);
	void DrawRotatedQuad(const Vector2& position, const Vector2& dimensions, const float& rotation);
private:
	void DrawQuad(const Vector2& position, const Vector2& dimensions);
};