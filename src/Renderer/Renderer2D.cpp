#include "Renderer2D.h"

#include <OpenGL/CommonRender.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/Shader.h>
#include <OpenGL/Texture.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <memory>

void Renderer2D::Begin()
{
    /* Poll for and process events */
    glfwPollEvents();
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer2D::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer2D::DrawQuad(const Vector2& position, const Vector2& dimensions)
{
    const float xOffset = position.x + dimensions.x;
    const float yOffset = position.y + dimensions.y;

    float vertexBuffer[] = {
        position.x, position.y, // 0
        xOffset, position.y,  // 1
        xOffset, yOffset,   // 2
        position.x, yOffset   // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::unique_ptr<VertexBuffer> vertex = std::make_unique<VertexBuffer>(vertexBuffer, sizeof(vertexBuffer));
    std::unique_ptr<IndexBuffer> index = std::make_unique<IndexBuffer>(indices, _countof(indices));
}

void Renderer2D::DrawQuad(const Vector2& position, const Vector2& dimensions, const Colour& colour)
{
    const float xOffset = position.x + dimensions.x;
    const float yOffset = position.y + dimensions.y;

    float vertexBuffer[] = {
        position.x, position.y, // 0
        xOffset, position.y,  // 1
        xOffset, yOffset,   // 2
        position.x, yOffset   // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::unique_ptr<VertexBuffer> vertex = std::make_unique<VertexBuffer>(vertexBuffer, sizeof(vertexBuffer));
    std::unique_ptr<IndexBuffer> index = std::make_unique<IndexBuffer>(indices, _countof(indices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(APP_RESOURCE("shaders/vertex.shader"), APP_RESOURCE("shaders/fragment.shader"));
    shader->Bind();
    shader->SetUniformVec4("uColour", colour.r, colour.g, colour.b, colour.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawRotatedQuad(const Vector2& position, const Vector2& dimensions, const float& rotation)
{
    DrawQuad(position, dimensions);
}

void Renderer2D::DrawTexturedQuad(const Vector2& position, const Vector2& dimensions, const char* texturePath)
{
    const float xOffset = position.x + dimensions.x;
    const float yOffset = position.y + dimensions.y;

    float vertexBuffer[] = {
        position.x, position.y, 0.0f, 0.0f, // 0
        xOffset, position.y,  1.0f, 0.0f,   // 1
        xOffset, yOffset, 1.0f, 1.0f,       // 2
        position.x, yOffset, 0.0f, 1.0f     // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::unique_ptr<VertexBuffer> vertex = std::make_unique<VertexBuffer>(vertexBuffer, sizeof(vertexBuffer));
    std::unique_ptr<IndexBuffer> index = std::make_unique<IndexBuffer>(indices, _countof(indices));
    std::unique_ptr<Shader> shader = std::make_unique<Shader>(APP_RESOURCE("shaders/vertex.shader"), APP_RESOURCE("shaders/textureFragment.shader"));
    std::unique_ptr<Texture> texture = std::make_unique<Texture>(texturePath);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

    shader->Bind();
    texture->Bind(0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawTriangle(const Vector2& position, const Vector2& dimensions, const Colour& colour)
{
    const float xOffset = position.x + dimensions.x;
    const float yOffset = position.y + dimensions.y;

    float vertexBuffer[] = {
        position.x, position.y, // 0
        xOffset, position.y,  // 1
        xOffset, yOffset   // 2
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    std::unique_ptr<VertexBuffer> vertex = std::make_unique<VertexBuffer>(vertexBuffer, sizeof(vertexBuffer));
    std::unique_ptr<IndexBuffer> index = std::make_unique<IndexBuffer>(indices, _countof(indices));
    std::unique_ptr<Shader> shader = std::make_unique<Shader>(APP_RESOURCE("shaders/vertex.shader"), APP_RESOURCE("shaders/fragment.shader"));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    shader->Bind();
    shader->SetUniformVec4("uColour", colour.r, colour.g, colour.b, colour.a);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
