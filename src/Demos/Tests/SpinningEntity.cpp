#include "SpinningEntity.h"

void SpinningEntity::OnUpdate(TimeStep ts)
{
	auto transform = this->GetComponent<TransformComponent>();

	float newRotation = transform->rotation + 90.f;

	transform->rotation = newRotation >= 360 ? 0.f : newRotation;
}
