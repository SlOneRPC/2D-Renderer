#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f), 
		postion(0.0f)
{
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::SetPosition(const glm::vec3& pos)
{
	postion = pos;
	RecalculateMatrix();
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void OrthographicCamera::RecalculateMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), postion)
		* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));

	viewMatrix = glm::inverse(transform);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}