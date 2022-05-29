#pragma once

#include "RenderComponent.hpp"

class TriRenderComponent : public RenderComponent {
public:
    TriRenderComponent(GameObject& gameObject, Shader& shader)
        : RenderComponent(gameObject, shader)
    {
        // VAO = 0;
        init();
    }

    virtual ~TriRenderComponent()
    {
        glDeleteVertexArrays(1, &this->VAO);
    }

    virtual void render() const override
    {
        const GameObject& gameObject = getGameObject();
        mShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glBindVertexArray(0);
    }

private:
    unsigned int VAO;

    void init()
    {
        unsigned int VBO;

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f, 0.5f, 0.0f // top
        };

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->VAO);
        glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
};
