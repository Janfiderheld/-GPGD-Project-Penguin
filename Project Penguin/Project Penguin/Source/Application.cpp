#include <Gameplay/Camera.h>
#include <Gameplay/Character.h>
#include <Gameplay/Collectable.h>
#include <Gameplay/ShootingEnemy.h>

#include <Level/LevelGrid.h>

#include <Managers/BackgroundManager.h>
#include <Managers/GridFacade.h>
#include <Managers/CollectableManager.h>
#include <Managers/EnemyManager.h>
#include <Managers/ThemeChangingManager.h>

#include <Technicals/UserInterface.h>
#include <Technicals/Shader.h>
#include <Technicals/Texture.h>
#include <Technicals/AABB.h>

int main(void) {
	// Settings
    SettingsManager settings;
    UserInterface::SettingsManager = &settings;
    UserInterfaceParameters::SettingsManager = &settings;

    // User Interface
    UserInterface ui;	
    if (!ui.getInitStatus()) {
        return -1;
    }

    // Input Manager
    InputManager inputs;
    UserInterface::InputManager = &inputs;
    Character::InputManager = &inputs;
	
	// Level
    LevelGrid level;
    GridFacade levelFacade(&level);
    UserInterface::LevelFacade = &levelFacade;
    MovingObject::LevelFacade = &levelFacade;
    CollectableManager::LevelFacade = &levelFacade;
    EnemyManager::LevelFacade = &levelFacade;

    // Character
    Texture charText("Penguin.png", GL_RGBA);
    glm::vec3 charPos(1.0f, 3.0f, -10.0f);
    AABB charHitbox(charPos, Character::getScale().y, Character::getScale().x);
    Character character(charPos, &charText, charHitbox);
    UserInterface::PlayerChar = &character;
    ThemeChangingManager::PlayerChar = &character;
    EnemyManager::PlayerChar = &character;

    // Theme Changing Manager
    ThemeChangingManager levelBarrier(glm::vec3(-5.0f, 0.0f, -10.0f));
    UserInterface::ThemeChangingManager = &levelBarrier;
    EnemyManager::ThemeChangingManager = &levelBarrier;

	// Enemies
    Texture shooterTex("Snowman.png", GL_RGBA);
    Texture walkerTex("WalkingEnemy.png", GL_RGBA);
    Texture projectileTex("Projectile.png", GL_RGBA);
    ShootingEnemy::ShooterTex = &shooterTex;
    WalkingEnemy::WalkerTex = &walkerTex;
    Projectile::ProjectileTex = &projectileTex;
    EnemyManager enemies;
    UserInterface::EnemyManager = &enemies;

    // Highscores
    HighscoreManager highscores;
    EnemyManager::HighscoreManager = &highscores;
    CollectableManager::HighscoreManager = &highscores;
    UserInterface::HighscoreManager = &highscores;

	// Collectables
    Texture collectTex("Collectable.png", GL_RGBA);
    Collectable::CollectTex = &collectTex;
    CollectableManager collectables;
    UserInterface::CollectableManager = &collectables;

    // Backgrounds
    glm::vec3 camPos = glm::vec3(5.6f, 4.9f, 3.0f);
    BackgroundManager backgrounds(camPos);

    // Camera
    // TODO: Calculate camera direction so that the origin is the bottom left corner of the screen
    Camera cam = Camera(camPos, glm::vec3(0.0f, 1.0f, 0.0f), &character);
	
	// Shader
    Shader textureShader("SimpleTexture.vert", "SimpleTexture.frag");
    Shader lightShader("SimpleLighting.frag");

	// Level Texture
	// TODO: Instead of using 16 different textures use a shader
    Texture iceTileStart("IceTileStart.png", GL_RGBA);   
    Texture iceTileStartBorder("IceTileStartLeftBorder.png", GL_RGBA);
    Texture iceTileEnd("IceTileEnd.png", GL_RGBA);
    Texture iceTileEndBorder("IceTileEndBorderRight.png", GL_RGBA);
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
    Texture desert("Desert.png", GL_RGBA);

    // default vertices
    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f      
    };

    // Indices for vertices
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Vertex Buffer Objects
    unsigned int textBuffer, indexBuffer, quadBuffer;
    glGenBuffers(1, &textBuffer);
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &quadBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(ui.getWindowPointer())) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Wireframe for Debugging
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    	
        // view transform
        glm::mat4 view = cam.getViewMatrix();

        // projection transform
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)UserInterfaceParameters::Width / (float)UserInterfaceParameters::Height, 5.0f, 15.0f);

        textureShader.changeStatus(true);
        textureShader.setMat4Uniform("view", view);
        textureShader.setMat4Uniform("projection", projection);
        textureShader.setBoolUniform("drawTexture", true);        
    	
        backgrounds.updateLayers(cam.getPosition().x);
        for(int i = backgrounds.getLayerAmount() - 1; i >= 0; i--) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, backgrounds.getPositionForLayer(i));
            model = glm::scale(model, backgrounds.getScaleForLayer(i));
            textureShader.setMat4Uniform("model", model);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, backgrounds.getTextureForLayer(i)->TextureId);
            glBufferSubData(textBuffer, 0, sizeof(backgrounds.getVerticesForLayer(i)), backgrounds.getVerticesForLayer(i));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDisable(GL_BLEND);
        }
    	        
        ui.processInput(&cam);
        if (ui.hasGameStarted()) {
            float delta = ui.calculateDeltaTime();
            character.calculateSpeed(delta);
            enemies.updateEnemies(delta, view, projection);
            cam.updatePosition(delta);
            levelBarrier.updatePosition(delta);
            textureShader.setFloatUniform("barrierPos", levelBarrier.getCurrentX());

            // draw Lighting from projectiles
            textureShader.changeStatus(false);
            lightShader.changeStatus(true);
            lightShader.setIntUniform("height", UserInterfaceParameters::Height);
            lightShader.setIntUniform("width", UserInterfaceParameters::Width);
            lightShader.setMat4Uniform("VP", projection * view);

            GLfloat lightQuadPositions[] = {
                -1.0f, -1.0f, 0.0f, 1.0f,
                -1.0f,  1.0f, 0.0f, 1.0f,
                 1.0f,  1.0f, 0.0f, 1.0f,
                 1.0f, -1.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 1.0f,
            };

            glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

            for (int i = 0; i < enemies.getShooterAndProjectileAmount(); i++) {
                Projectile* tempProj = enemies.getProjectileAtVectorPos(i);
                if (tempProj->getStatus()) {
                    lightShader.setIntUniform("lightRadius", tempProj->getRadius());
                    lightShader.setVec3Uniform("lightLocation", tempProj->getPosition());
                    lightShader.setVec4Uniform("lightColor", tempProj->getColorAndBrightness());

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_ONE, GL_ONE);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(lightQuadPositions), lightQuadPositions, GL_DYNAMIC_DRAW);
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
                    glDisable(GL_BLEND);
                }
            }

            lightShader.changeStatus(false);
            textureShader.changeStatus(true);

            glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // draw Level
            for (int x = 0; x < level.getWidth(); x++) {
                for (int y = 0; y < level.getHeight(); y++) {
                    textureShader.setIntUniform("normal", 0);
                    glActiveTexture(GL_TEXTURE0);
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
                            } else {
                                glBindTexture(GL_TEXTURE_2D, iceTileStart.TextureId);
                            }
                            break;

                        case END_AREA:
                            if (currTile.getBorderForTexture() == 0x06) {
                                glBindTexture(GL_TEXTURE_2D, iceTileEndBorder.TextureId);
                            } else {
                                glBindTexture(GL_TEXTURE_2D, iceTileEnd.TextureId);
                            }
                            break;
                        }

                        // model transform
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, currTile.getPosition());
                        textureShader.setMat4Uniform("model", model);
                        textureShader.setIntUniform("changed", 1);
                        textureShader.setBoolUniform("changeTexture", true);

                        glActiveTexture(GL_TEXTURE1);
                        glBindTexture(GL_TEXTURE_2D, desert.TextureId);

                        glBufferSubData(textBuffer, 0, sizeof(currTile.getVertices()), currTile.getVertices());
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    }
                }
            }

            textureShader.setBoolUniform("changeTexture", false);
            glActiveTexture(GL_TEXTURE0);

            // draw character
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, character.getTexturePosition());
            model = glm::scale(model, Character::getScale());
            if (character.getCurrentSpeed().x < 0.0f) {
                model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
            }
            textureShader.setMat4Uniform("model", model);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, character.getTexture()->TextureId);
            glBufferSubData(textBuffer, 0, sizeof(character.getVertices()), character.getVertices());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDisable(GL_BLEND);

            // draw enemies
            for (int i = 0; i < enemies.getShooterAndProjectileAmount(); i++) {
                Projectile* tempProj = enemies.getProjectileAtVectorPos(i);
                if (tempProj != NULL && tempProj->getStatus()) {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, tempProj->getPosition());
                    model = glm::scale(model, tempProj->Scale);
                    textureShader.setMat4Uniform("model", model);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, Projectile::ProjectileTex->TextureId);
                    glBufferSubData(textBuffer, 0, sizeof(tempProj->getVertices()), tempProj->getVertices());
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    glDisable(GL_BLEND);
                }

                ShootingEnemy* tempShoot = enemies.getShootingEnemyAtVectorPos(i);
                model = glm::mat4(1.0f);
                model = glm::translate(model, tempShoot->getPosition());
                model = glm::scale(model, ShootingEnemy::getScale());
                if (tempShoot->getCurrentSpeed().x < 0.0f) {
                    model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
                }
                textureShader.setMat4Uniform("model", model);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, ShootingEnemy::ShooterTex->TextureId);
                glBufferSubData(textBuffer, 0, sizeof(tempShoot->getVertices()), tempShoot->getVertices());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glDisable(GL_BLEND);
            }

            for (int i = 0; i < enemies.getWalkerAmount(); i++) {
                WalkingEnemy* tempWalker = enemies.getWalkingEnemyAtVectorPos(i);
                model = glm::mat4(1.0f);
                model = glm::translate(model, tempWalker->getTexturePosition());
                model = glm::scale(model, WalkingEnemy::getScale());
                if (tempWalker->getCurrentSpeed().x < 0.0f) {
                    model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
                }
                textureShader.setMat4Uniform("model", model);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, WalkingEnemy::WalkerTex->TextureId);
                glBufferSubData(textBuffer, 0, sizeof(tempWalker->getVertices()), tempWalker->getVertices());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glDisable(GL_BLEND);
            }

            // draw Collectables
            collectables.checkForCollection(character.getHitbox());
            for (int i = 0; i < collectables.getAmountOfCollectables(); i++) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, collectables.getCollectableAtPosition(i)->getPosition());
                model = glm::scale(model, collectables.getCollectableAtPosition(i)->getScale());
                textureShader.setMat4Uniform("model", model);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBindTexture(GL_TEXTURE_2D, Collectable::CollectTex->TextureId);
                glBufferSubData(textBuffer, 0, sizeof(collectables.getCollectableAtPosition(i)->getVertices()), collectables.getCollectableAtPosition(i)->getVertices());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glDisable(GL_BLEND);
            }

            // draw Theme Changing
            GLfloat lineVertices[] = {
                levelBarrier.getCurrentX(), 0, -10,
                levelBarrier.getCurrentX(), 0, -10
            };

            model = glm::mat4(1.0f);
            model = glm::translate(model, levelBarrier.getPosition());
            model = glm::scale(model, glm::vec3(-1.0f, 45.0f, 1.0f));
            textureShader.setMat4Uniform("model", model);
            textureShader.setBoolUniform("drawTexture", false);

            glLineWidth(8.0f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBufferSubData(textBuffer, 0, sizeof(lineVertices), lineVertices);
            glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
            glDisable(GL_BLEND);
        }

        ui.drawUI();
        glfwSwapBuffers(ui.getWindowPointer());
        glfwPollEvents();
    }

    glDeleteBuffers(1, &textBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &quadBuffer);
    textureShader.deleteThisShader();
    lightShader.deleteThisShader();
    ui.cleanUp();
    return 0;
}