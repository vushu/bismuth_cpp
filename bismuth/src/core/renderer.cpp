
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bismuth/renderer.hpp>
#include <glm/vec4.hpp>
#include <stdexcept>
using namespace bi;

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
//float vertices[] = {
//0.5f,  0.5f, 0.0f,  // top right
//0.5f, -0.5f, 0.0f,  // bottom right
//-0.5f, -0.5f, 0.0f,  // bottom left
//-0.5f,  0.5f, 0.0f   // top left
//};
//unsigned int indices[] = {  // note that we start from 0!
//0, 1, 3,  // first Triangle
//1, 2, 3   // second Triangle
//};
unsigned int VBO, VAO, EBO;

Renderer::~Renderer() {
    log("Renderer destroyed ");
}

void Renderer::init() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    // alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    this->shader->compile();
    std::unique_ptr<RenderBatch> firstBatch = std::make_unique<RenderBatch>(this->camera,this->MAX_BATCH_SIZE, this->shader);
    firstBatch->init();
    this->batches.push_back(std::move(firstBatch));
    //for (auto& batch : batches) {
    //batch->init();
    //}
    bi::log("done initializing batches");
    //testTexture();

}

void Renderer::clear(glm::vec4 color) {
    clear(color.x, color.y, color.z, color.w);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

//make unique_ptr for spriterenderer
RenId Renderer::addSprite(std::shared_ptr<SpriteRenderer> sprite) {

    //temp
    int spriteId = -1;
    //taking current batch
    auto& batch = batches.at(batches.size() - 1);

    if (batch->hasRoom) {
        //if has room, then add sprite
        //batch->init();
        spriteId = batch->addSprite(sprite);
    }
    else {
        // if current batch has no more room create a new one
        std::unique_ptr<RenderBatch> nextBatch = std::make_unique<RenderBatch>(this->camera,this->MAX_BATCH_SIZE, this->shader);
        nextBatch->init();
        this->batches.push_back(std::move(nextBatch));
        spriteId = batches.at(batches.size() - 1)->addSprite(sprite);
    }

    return RenId {static_cast<int>(batches.size() - 1), spriteId};
}

void Renderer::render(float dt) {
    //renderTestTriangle();
    //renderTestTexture();
    //bi::log("FPS: " + std::to_string(1.0f/dt));
    for (auto& batch : batches) {
        //Rendering every batch
        batch->render();
    }
    //

}

void Renderer::testTriangle() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void Renderer::renderTestTriangle() {

    shader->use();
    //glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    //glfwSwapBuffers(window);
    //glfwPollEvents();
}

void Renderer::testTexture() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    this->textureTest->init();
    shader->use();
    shader->uploadUniformInt("texture1", 0);
    //glUniform1i(glGetUniformLocation(shader->shaderProgramId, "texture1"), 0);
    //shader->uploadUniformMat4(, glm::mat4 mat4)
}

void Renderer::renderTestTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureTest->textureId);
    this->shader->use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

SpriteRenderer& Renderer::getSprite(int batchId, int spriteId) {
    return *this->batches.at(batchId)->sprites.at(spriteId);
}




