#include "DemoScene.h"
#include "Core/Logging.h"
#include "BasicQuadEntity.h"

void BasicDemoScene::Init()
{
	const float rows = 12;
	const float columns = 12;
	const float Count = 8.0f;

	// create entities
	for (int x = 1; x <= rows; x++)
	{
		for (int y = 1; y <= columns; y++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			const float offset = Count / columns;

			float posx = (offset * x) - Count / 2;
			float posy = (offset * y) - Count / 2;

			auto quad = BasicQuadEntity::CreateNonTextured(glm::vec2(posx, posy), glm::vec2(1.0f, 1.0f), 45.f, { 1.0, 0.0, 0.0f, 1.0 });
			AddCustomEntity(quad);
		}
	}

	LOG_INFO("Added entities");
}
