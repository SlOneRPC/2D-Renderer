#pragma once

#include <glm/glm.hpp>

class OrthographicCamera {
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	void SetPosition(const glm::vec3& pos);
	void SetProjection(float left, float right, float bottom, float top);
	const glm::vec3& GetPosition() { return postion; }
	const glm::mat4& GetViewProjection() { return viewProjectionMatrix; }
	const glm::mat4& GetProjectionMatrix() { return projectionMatrix; }
private:
	void RecalculateMatrix();

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 viewProjectionMatrix;
	glm::vec3 postion;
};