#include "Renderer2D.h"

#include <OpenGL/CommonRender.h>
#include <OpenGL/Shader.h>
#include <OpenGL/Texture.h>
#include <OpenGL/VertexArray.h>

#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static bool initialSetup = true;

struct VertexData 
{
    glm::vec2 position;
    glm::vec2 textureCoords;
};

struct RenderData {
};

static std::unique_ptr<Shader> flatColourShader;
static std::unique_ptr<Shader> textureShader;

static std::unique_ptr<VertexArray> quadVertexArray;
static std::unique_ptr<VertexArray> triangleVertexArray;

Renderer2D* g_Renderer;

Renderer2D::Renderer2D()
{
    if (initialSetup) 
    {
        // Create shaders
        flatColourShader = std::make_unique<Shader>(APP_RESOURCE("shaders/vertex.shader"), APP_RESOURCE("shaders/fragment.shader"));
        textureShader = std::make_unique<Shader>(APP_RESOURCE("shaders/vertex.shader"), APP_RESOURCE("shaders/textureFragment.shader"));

        unsigned int quadIndices[] = {
                       0, 1, 2,
                       2, 3, 0
        };

        std::shared_ptr<IndexBuffer> quadIndex = std::make_shared<IndexBuffer>(quadIndices, _countof(quadIndices));

        // Create Basic quad
        glm::vec2 quadBase[4];
        quadBase[0] = { -0.5f , -0.5f };
        quadBase[1] = { 0.5f, -0.5f };
        quadBase[2] = { 0.5f, 0.5f };
        quadBase[3] = { -0.5f, 0.5f };

        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
       
        VertexData quadVertexBuffer[4];
        for (int i = 0; i < 4; i++)
        {
            quadVertexBuffer[i].position = quadBase[i];
            quadVertexBuffer[i].textureCoords = textureCoords[i];
        }

        VertexData triangleVertexBuffer[3];
        for (int i = 0; i < 3; i++)
        {
            quadVertexBuffer[i].position = quadBase[i];
            quadVertexBuffer[i].textureCoords = textureCoords[i];
        }

        std::shared_ptr<VertexBuffer> vertex =
            std::make_shared<VertexBuffer>(quadVertexBuffer, sizeof(quadVertexBuffer));

        VertexLayout layoutQuad;
        layoutQuad.AddAttrib(std::make_shared<VertexLayoutAtrrib>(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr));
        layoutQuad.AddAttrib(std::make_shared<VertexLayoutAtrrib>(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2)));

        vertex->SetLayout(layoutQuad);

        std::shared_ptr<VertexBuffer> vertexTriangle =
            std::make_shared<VertexBuffer>(triangleVertexBuffer, sizeof(triangleVertexBuffer));

        vertexTriangle->SetLayout(layoutQuad);

        quadVertexArray = std::make_unique<VertexArray>(vertex, quadIndex);
        triangleVertexArray = std::make_unique<VertexArray>(vertexTriangle, quadIndex);

        initialSetup = true;
        g_Renderer = this;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void Renderer2D::Begin(OrthographicCamera& camera)
{
    /* Poll for and process events */
    glfwPollEvents();
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    viewProjection = camera.GetViewProjection();
}

void Renderer2D::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer2D::DrawQuad(const glm::vec2& transform, const glm::vec2& dimensions, const Colour& colour)
{
    flatColourShader->Bind();
    flatColourShader->SetUniformVec4("uColour", colour.r, colour.g, colour.b, colour.a);

    DrawQuad(transform, dimensions, flatColourShader);
}

void Renderer2D::DrawOutlineQuad(const glm::vec2& transform, const glm::vec2& dimensions, const Colour& colour, const float& outlineThickness)
{
    flatColourShader->Bind();
    flatColourShader->SetUniformVec4("uColour", colour.r, colour.g, colour.b, colour.a);

    const glm::vec2 half = dimensions / 2.f;

    DrawQuad(transform - glm::vec2{ 0.f, half.y}, { dimensions.x, outlineThickness }, flatColourShader);
    DrawQuad(transform - glm::vec2{ half.x, 0.0f }, { outlineThickness, dimensions.y }, flatColourShader);
    DrawQuad(transform + glm::vec2{ 0.f, half.y }, { dimensions.x, outlineThickness }, flatColourShader);
    DrawQuad(transform + glm::vec2{ half.x, 0.0f }, { outlineThickness, dimensions.y }, flatColourShader);
}


void Renderer2D::DrawRotatedQuad(const glm::vec2& transform, const glm::vec2& dimensions, const float& rotation)
{
   // DrawQuad(transform, dimensions);
}

void Renderer2D::DrawQuad(const glm::vec2& transform, const glm::vec2& dimensions, std::unique_ptr<Shader>& shader)
{
    quadVertexArray->Bind();

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 1.f));
    glm::mat4 transformed = glm::translate(glm::mat4(1.0f), { transform.x, transform.y, 0.f }) * scale;

    shader->SetUniformMat4("uTransform", transformed);
    shader->SetUniformMat4("uViewProjection", viewProjection);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawTexturedQuad(const glm::vec2& transform, const glm::vec2& dimensions, Texture* texture)
{
    textureShader->Bind();
    texture->Bind(0);
    DrawQuad(transform, dimensions, textureShader);
}

void Renderer2D::DrawTriangle(const glm::vec2& transform, const glm::vec2& dimensions, const Colour& colour)
{
    triangleVertexArray->Bind();

    flatColourShader->Bind();
    flatColourShader->SetUniformVec4("uColour", colour.r, colour.g, colour.b, colour.a);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 1.f));
    glm::mat4 transformed = glm::translate(glm::mat4(1.0f), { transform.x, transform.y, 0.f }) * scale;

    flatColourShader->SetUniformMat4("uTransform", transformed);
    flatColourShader->SetUniformMat4("uViewProjection", viewProjection);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
