#include <Technicals/UserInterface.h>
#include <Technicals/Shader.h>
#include <Gameplay/Camera.h>
#include <Gameplay/Character.h>
#include <Technicals/Texture.h>
#include <Technicals/AABB.h>
#include <Level/LevelGrid.h>
#include <Managers/GridFacade.h>
#include <Managers/CollectableManager.h>
#include <Managers/EnemyManager.h>
#include <Gameplay/Collectable.h>
#include <Gameplay/ShootingEnemy.h>

int main(void) {
    UserInterface ui;

    if (!ui.getInitStatus()) {
        return -1;
    }

    Shader shader("BasicVertexShader.vert", "BasicFragmentShader.frag");
    Texture iceTileStart("IceTileStart.png", GL_RGBA);
    Texture testProj("Projectile.png", GL_RGBA);
    Texture iceTileStartBorder("IceTileStartLeftBorder.png", GL_RGBA);

    Texture iceTileEnd("IceTileEnd.png", GL_RGBA);
    Texture iceTileEndBorder("IceTileEndBorderRight.png", GL_RGBA);

    // TODO: Instead of using 16 different textures use a shader
    Texture iceTileNormal0("IceTileNormalBorder0.png", GL_RGBA);
    Texture iceTileNormal1("IceTileNormalBorder1.png", GL_RGBA);
    Texture iceTileNormal2("IceTileNormalBorder2.png", GL_RGBA);
    Texture iceTileNormal3("IceTileNormalBorder3.png", GL_RGBA);
    Texture iceTileNormal4("IceTileNormalBorder4.png", GL_RGBA);
    Texture iceTileNormal5("IceTileNormalBorder5.png", GL_RGBA);
    Texture iceTileNormal6("IceTileNormalBorder6.png", GL_RGBA);
    Texture iceTileNormal7("IceTileNormalBorder7.png", GL_RGBA);
    Texture iceTileNormal8("IceTileNormalBorder8.png", GL_RGBA);
    Texture iceTileNormal9("IceTileNormalBorder9.png", GL_RGBA);
    Texture iceTileNormal10("IceTileNormalBorder10.png", GL_RGBA);
    Texture iceTileNormal11("IceTileNormalBorder11.png", GL_RGBA);
    Texture iceTileNormal12("IceTileNormalBorder12.png", GL_RGBA);
    Texture iceTileNormal13("IceTileNormalBorder13.png", GL_RGBA);
    Texture iceTileNormal14("IceTileNormalBorder14.png", GL_RGBA);
    Texture iceTileNormal15("IceTileNormalBorder15.png", GL_RGBA);

    Texture charText("Penguin.png", GL_RGBA);

    // Level
    LevelGrid level;
    GridFacade levelFacade(&level); 
    InputManager inpMan;
    UserInterface::InputManager = &inpMan;
    UserInterface::LevelGrid = &levelFacade;

    // Character
    glm::vec3 charPos(1.0f, 3.0f, -10.0f);
    glm::vec3 charScale(0.66f, 1.0f, 1.0f);
    AABB charHitbox(charPos, charScale.y, charScale.x);
    Character character(charPos, &charText, charHitbox);
    MovingObject::LevelFacade = &levelFacade;
    Character::InputManager = &inpMan;
    UserInterface::PlayerCharacter = &character;

    // Enemies
    Texture shooterTex("HeartFilled.png", GL_RGBA);
    ShootingEnemy::ShooterTex = &shooterTex;
    EnemyManager::LevelFacade = &levelFacade;
    EnemyManager::PlayerChar = &character;
    Projectile::ProjectileTex = &testProj;
    EnemyManager enemyMan;
    UserInterface::EnemyManager = &enemyMan;

    // Collectables
    HighscoreManager highMan;
    Texture collectTex("Collectable.png", GL_RGBA); 
    Collectable::CollectTex = &collectTex;
    CollectableManager::LevelFacade = &levelFacade;
    CollectableManager::HighscoreMan = &highMan;
    CollectableManager collectMan;
    UserInterface::HighscoreManager = &highMan;
    UserInterface::CollectableManager = &collectMan;

    // Camera
    // TODO: Calculate camera direction so that the origin is the bottom left corner of the screen
    Camera cam = Camera(glm::vec3(5.6f, 4.9f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), &character);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(ui.getWindowPointer())) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ui.processInput(&cam);
    	if(ui.hasGameStarted()) {
            float delta = ui.calculateDeltaTime();
            character.calculateSpeed(delta);
            cam.updatePosition(delta);
            enemyMan.updateEnemies(delta);
    		
            // view transform
            glm::mat4 view = cam.getViewMatrix();

            // projection transform
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), (float)UserInterface::Width / (float)UserInterface::Height, 0.1f, 100.0f);

            shader.changeStatus(true);
            shader.setMat4Uniform("view", view);
            shader.setMat4Uniform("projection", projection);

            //// Wireframe for Debugging
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // draw Level
            for (int x = 0; x < level.getWidth(); x++) {
                for (int y = 0; y < level.getHeight(); y++) {
                    LevelGridTile currTile = level.getTileFromGrid(x, y);
                    if (currTile.isFilled()) {
                        switch (currTile.getLocation())
                        {
                        case NORMAL:
                        default:
                            switch (currTile.getBorderForTexture())
                            {
                            case 0x01:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal1.TextureId);
                                break;
                            case 0x02:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal2.TextureId);
                                break;
                            case 0x03:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal3.TextureId);
                                break;
                            case 0x04:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal4.TextureId);
                                break;
                            case 0x05:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal5.TextureId);
                                break;
                            case 0x06:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal6.TextureId);
                                break;
                            case 0x07:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal7.TextureId);
                                break;
                            case 0x08:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal8.TextureId);
                                break;
                            case 0x09:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal9.TextureId);
                                break;
                            case 0x0A:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal10.TextureId);
                                break;
                            case 0x0B:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal11.TextureId);
                                break;
                            case 0x0C:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal12.TextureId);
                                break;
                            case 0x0D:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal13.TextureId);
                                break;
                            case 0x0E:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal14.TextureId);
                                break;
                            case 0x0F:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal15.TextureId);
                                break;
                            case 0x00:
                                glBindTexture(GL_TEXTURE_2D, iceTileNormal0.TextureId);
                                break;
                            }
                            break;

                        case START_AREA:
                            if (currTile.getBorderForTexture() == 0x0A) {
                                glBindTexture(GL_TEXTURE_2D, iceTileStartBorder.TextureId);
                            }
                            else {
                                glBindTexture(GL_TEXTURE_2D, iceTileStart.TextureId);
                            }
                            break;

                        case END_AREA:
                            if (currTile.getBorderForTexture() == 0x06) {
                                glBindTexture(GL_TEXTURE_2D, iceTileEndBorder.TextureId);
                            }
                            else {
                                glBindTexture(GL_TEXTURE_2D, iceTileEnd.TextureId);
                            }
                            break;
                        }

                        // model transform
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, currTile.getPosition());
                        shader.setMat4Uniform("model", model);

                        glBufferSubData(VBO, 0, sizeof(currTile.getVertices()), currTile.getVertices());
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    }
                }
            }

            // draw character
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, character.getPosition());
            model = glm::scale(model, charScale);
            if (character.getCurrentSpeed().x < 0.0f) {
                model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
            }
            shader.setMat4Uniform("model", model);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, character.getTexture()->TextureId);
            glBufferSubData(VBO, 0, sizeof(character.getVertices()), character.getVertices());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDisable(GL_BLEND);

            // draw enemies
            for (int i = 0; i < enemyMan.getShooterAndProjectileAmount(); i++) {
                ShootingEnemy* tempShoot = enemyMan.getShootingEnemyAtVectorPos(i);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, tempShoot->getPosition());
                shader.setMat4Uniform("model", model);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, ShootingEnemy::ShooterTex->TextureId);
                glBufferSubData(VBO, 0, sizeof(tempShoot->getVertices()), tempShoot->getVertices());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glDisable(GL_BLEND);

                Projectile* tempProj = enemyMan.getProjectileAtVectorPos(i);
                if (tempProj != NULL && tempProj->getStatus()) {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, tempProj->getPosition());
                    shader.setMat4Uniform("model", model);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, Projectile::ProjectileTex->TextureId);
                    glBufferSubData(VBO, 0, sizeof(tempProj->getVertices()), tempProj->getVertices());
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    glDisable(GL_BLEND);
                }
            }

    		// draw Collectables
            collectMan.checkForCollection(character.getHitbox());
            for (int i = 0; i < collectMan.getAmountOfCollectables(); i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, collectMan.getCollectableAtPosition(i)->getPosition());
                model = glm::scale(model, glm::vec3(collectMan.getCollectableAtPosition(i)->getScale(), 1.0f));
                shader.setMat4Uniform("model", model);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, Collectable::CollectTex->TextureId);
                glBufferSubData(VBO, 0, sizeof(collectMan.getCollectableAtPosition(i)->getVertices()), collectMan.getCollectableAtPosition(i)->getVertices());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glDisable(GL_BLEND);
            }
    	}
    	
        ui.drawUI();
        glfwSwapBuffers(ui.getWindowPointer());
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.changeStatus(false);
    ui.cleanUp();
    return 0;
}