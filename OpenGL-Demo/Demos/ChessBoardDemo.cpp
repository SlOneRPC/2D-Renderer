#include "ChessBoardDemo.h"
#include "../CommonRender.h"

#include <unordered_map>

struct Vector2 { 
	int x, y;

	bool operator==(const Vector2& other) const
	{
		return (x == other.x
			&& y == other.y);
	}
};

class MyHashFunction {
public:
	size_t operator()(const Vector2& p) const
	{
		return p.x + p.y;
	}
};

std::unordered_map<Vector2, std::string, MyHashFunction> pieces {
	{ {1, 1}, "rook"},
	{ {2, 1}, "knight"}, 
	{ {3, 1}, "bishop"},
	{ {4, 1}, "king"},
	{ {5, 1}, "queen"},
	{ {6, 1}, "bishop"},
	{ {7, 1}, "knight"},
	{ {8, 1}, "rook"},

	{ {1, 2}, "pawn"},
	{ {2, 2}, "pawn"},
	{ {3, 2}, "pawn"},
	{ {4, 2}, "pawn"},
	{ {5, 2}, "pawn"},
	{ {6, 2}, "pawn"},
	{ {7, 2}, "pawn"},
	{ {8, 2}, "pawn"},

	{ {1, 7}, "pawn"},
	{ {2, 7}, "pawn"},
	{ {3, 7}, "pawn"},
	{ {4, 7}, "pawn"},
	{ {5, 7}, "pawn"},
	{ {6, 7}, "pawn"},
	{ {7, 7}, "pawn"},
	{ {8, 7}, "pawn"},

	{ {1, 8}, "rook"},
	{ {2, 8}, "knight"},
	{ {3, 8}, "bishop"},
	{ {4, 8}, "king"},
	{ {5, 8}, "queen"},
	{ {6, 8}, "bishop"},
	{ {7, 8}, "knight"},
	{ {8, 8}, "rook"}
};

std::unordered_map<std::string, Texture*> textureMap;

ChessBoardDemo::ChessBoardDemo()
{
}

ChessBoardDemo::~ChessBoardDemo()
{
	Shutdown();
}

void ChessBoardDemo::Init()
{
	unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
	};

	index = new IndexBuffer(indices, _countof(indices));
	shader = new Shader("shaders/vertex.shader", "shaders/fragment.shader");
	textureShader = new Shader("shaders/vertex.shader", "shaders/textureFragment.shader");

	index->Bind();
	shader->Bind();

	for (auto const& x : pieces)
	{
		std::string type = x.first.y <= 2 ? "black-pieces" : "white-pieces";

		if (textureMap.find(type + "/" + x.second) != textureMap.end())
			continue;

		Texture* t = new Texture("images/" + type + "/" + x.second + ".png");
		textureMap.emplace(type + "/" + x.second, t);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ChessBoardDemo::OnRender()
{
	float size = 8;

	for (size_t iteration = 1; iteration <= 2; iteration++)
	{
		for (size_t x = 0; x < size; x++)
		{
			for (size_t y = 0; y < size; y++)
			{
				const float baseOffset = 1.f / (size / 2);

				float offset1x = (baseOffset * x) - 1;
				float offset2x = offset1x + (baseOffset);

				float offset1y = (baseOffset * y) - 1;
				float offset2y = offset1y + (baseOffset);

				float vertexBuffer[] = {
					offset1x, offset1y, 0.0f, 0.0f, // 0
					offset2x, offset1y, 1.0f, 0.0f,  // 1
					offset2x, offset2y, 1.0f, 1.0f,  // 2
					offset1x, offset2y, 0.0f, 1.0f // 3
				};

				vertex = new VertexBuffer(vertexBuffer, sizeof(vertexBuffer));

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

				vertex->Bind();
				index->Bind();

				bool lightSquare = (x + y) % 2 == 0;

				if (iteration == 2)
				{
					Vector2 position = { x + 1, y + 1 };
					if (pieces.find(position) != pieces.end()) {
						textureShader->Bind();

						std::string type = position.y <= 2 ? "black-pieces" : "white-pieces";
						textureMap[type + "/" + pieces.at(position)]->Bind(0);
					}
					else 
					{
						delete vertex;
						continue;
					}
				}
				else
				{
					shader->Bind();
					shader->SetUniformVec4("uColour", lightSquare ? 0.90 : 0.49f, lightSquare ? 0.92f : 0.529f, lightSquare ? 0.937f : 0.588f, 1.0f);
				}

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				delete vertex;
			}
		}
	}
}

void ChessBoardDemo::OnImguiRender()
{

}

void ChessBoardDemo::Shutdown()
{
	delete index;
	delete shader;

	for (auto const& x : textureMap) 
	{
		delete x.second;
	}
}
