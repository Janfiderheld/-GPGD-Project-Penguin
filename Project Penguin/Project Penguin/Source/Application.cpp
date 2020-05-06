#include <Game.h>
#include <Shader.h>
#include <Texture.h>

int main(void)
{
    Game game;

    if (!game.Initialize()) {
        return -1;
    }

    Shader shader("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
    // TODO: Make path relative
    Texture texture("C:/Users/Janfi/Documents/gpgd-project-penguin/Project Penguin/Assets/Textures/GenericExampleTexture.png", GL_RGBA);
    texture.changeWrapping(GL_REPEAT, GL_REPEAT);
    texture.changeFiltering(GL_LINEAR, GL_LINEAR);

    glm::vec3 examplePos = glm::vec3(0.0f);

    // Camera
    Camera cam = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // 3x Positions 2x Texture
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f      
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // fill Vertex Buffer 
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(game.getWindowPointer()))
    {
        game.calculateDeltaTime();
        game.processInput(&cam);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // model transform
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, examplePos);

        // view transform
        glm::mat4 view = cam.getViewMatrix();

        // projection transform
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)game.getWidth() / (float)game.getHeight(), 0.1f, 100.0f);

        shader.changeStatus(true);
        shader.setMat4Uniform("model", model);
        shader.setMat4Uniform("view", view);
        shader.setMat4Uniform("projection", projection);
        glBindTexture(GL_TEXTURE_2D, texture.TextureId);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(game.getWindowPointer());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.changeStatus(false);

    glfwTerminate();
    return 0;
}