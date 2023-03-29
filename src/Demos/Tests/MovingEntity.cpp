#include "MovingEntity.h"

const float entitySpeed = 0.1f;

void MovingEntity::OnUpdate(TimeStep ts)
{
	TransformComponent* transform = GetComponent<TransformComponent>();
	
	if (movingLeft) 
	{
		if (transform->translation.x > -4.f)
			transform->translation.x -= entitySpeed * ts;
		else
			movingLeft = false;
	}
	else 
	{
		if (transform->translation.x < 4.f)
			transform->translation.x += entitySpeed * ts;
		else
			movingLeft = true;
	}
}
