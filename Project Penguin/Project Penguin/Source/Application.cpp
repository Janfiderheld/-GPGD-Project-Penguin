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
    ThemeChangingManager levelBarrier(-4.0f);
    UserInterface::ThemeChangingManager = &levelBarrier;

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
    BackgroundManager backgrounds;

    // Camera
    glm::vec3 camPos = glm::vec3(5.6f, 5.5f, 3.0f);
    Camera cam = Camera(camPos, glm::vec3(0.0f, 1.0f, 0.0f), &character);
	
	// Shader
    Shader textureShader("SimpleTexture.vert", "SimpleTexture.frag");
    Shader levelTextureShader("SimpleTexture.vert", "LevelTexture.frag");
    Shader projectileLightShader("ProjectileLighting.frag");
    Shader themeChangingShader("ThemeChanging.frag");
    Shader parallaxShader("ParallaxScrolling.frag");

	// Level Textures
    Texture ice("Ice.png", GL_RGBA);
    Texture iceBorder("IceBorder.png", GL_RGBA);
    Texture desert("Desert.png", GL_RGBA);
    Texture desertBorder("DesertBorder.png", GL_RGBA);

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

    // fullscreen quad positions
    GLfloat quadPos[] = {
         1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
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

        textureShader.setMat4Uniform("view", view);
        textureShader.setMat4Uniform("projection", projection);  
    	
        Shader::DeactivateCurrentShader();
        parallaxShader.activateThisShader();
        parallaxShader.setMat4Uniform("VP", projection * view);
        parallaxShader.setIntUniform("width", UserInterfaceParameters::Width);
        parallaxShader.setIntUniform("height", UserInterfaceParameters::Height);
        parallaxShader.setIntUniform("maxWidth", level.getWidth());
        parallaxShader.setIntUniform("maxHeight", level.getHeight());
        parallaxShader.setVec3Uniform("camPos", cam.getPosition());
        parallaxShader.setVec3Uniform("barrierPos", levelBarrier.getPosition());

        for(int i = backgrounds.getLayerAmount() - 1; i >= 0; i--) {
            glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

            parallaxShader.setIntUniform("layerNo", i);
            parallaxShader.setIntUniform("ice", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, backgrounds.getIceTextureForLayer(i)->TextureId);

            parallaxShader.setIntUniform("desert", 1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, backgrounds.getDesertTextureForLayer(i)->TextureId);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadPos), quadPos, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glDisable(GL_BLEND);
        }

        glActiveTexture(GL_TEXTURE0);
        Shader::DeactivateCurrentShader();
        textureShader.activateThisShader();

        ui.processInput(&cam);
        float delta = ui.calculateDeltaTime();
        if (ui.hasGameStarted()) {
            character.calculateSpeed(delta);
            enemies.updateEnemies(delta, levelBarrier.getCurrentX(), view, projection);
            cam.updatePosition(delta);
            levelBarrier.updatePosition(delta);

            // draw Lighting from projectiles
            Shader::DeactivateCurrentShader();
            projectileLightShader.activateThisShader();
            projectileLightShader.setIntUniform("height", UserInterfaceParameters::Height);
            projectileLightShader.setIntUniform("width", UserInterfaceParameters::Width);
            projectileLightShader.setMat4Uniform("VP", projection* view);

            glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
            glBindTexture(GL_TEXTURE_2D, 0);

            for (int i = 0; i < enemies.getShooterAndProjectileAmount(); i++) {
                Projectile* tempProj = enemies.getProjectileAtVectorPos(i);
                if (tempProj->getStatus()) {
                    projectileLightShader.setIntUniform("lightRadius", tempProj->getRadius());
                    projectileLightShader.setVec3Uniform("lightLocation", tempProj->getPosition());
                    projectileLightShader.setVec4Uniform("lightColor", tempProj->getColorAndBrightness());

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_ONE, GL_ONE);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(quadPos), quadPos, GL_DYNAMIC_DRAW);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    glDisable(GL_BLEND);
                }
            }

            Shader::DeactivateCurrentShader();
            textureShader.activateThisShader();

            glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // draw Level
            Shader::DeactivateCurrentShader();
            levelTextureShader.activateThisShader();
            levelTextureShader.setMat4Uniform("view", view);
            levelTextureShader.setMat4Uniform("projection", projection);
            levelTextureShader.setFloatUniform("barrierPos", levelBarrier.getCurrentX());

            levelTextureShader.setIntUniform("ice", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ice.TextureId);

            levelTextureShader.setIntUniform("desert", 1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, desert.TextureId);

            levelTextureShader.setIntUniform("iceBorder", 2);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, iceBorder.TextureId);

            levelTextureShader.setIntUniform("desertBorder", 3);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, desertBorder.TextureId);

            for (int x = 0; x < level.getWidth(); x++) {
                for (int y = 0; y < level.getHeight(); y++) {
                    LevelGridTile currTile = level.getTileFromGrid(x, y);
                    if(currTile.isFilled()) {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, currTile.getPosition());
                        levelTextureShader.setMat4Uniform("model", model);

                        levelTextureShader.setBoolUniform("isStart", currTile.getLocation() == START_AREA);
                        levelTextureShader.setBoolUniform("isEnd", currTile.getLocation() == END_AREA);
                        levelTextureShader.setBoolUniform("borderUp", currTile.getTopBorder());

                        glBufferSubData(textBuffer, 0, sizeof(currTile.getVertices()), currTile.getVertices());
                        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    }
                }
            }

            Shader::DeactivateCurrentShader();
            textureShader.activateThisShader();
            glActiveTexture(GL_TEXTURE0);

            // draw character
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, character.getTexturePosition());
            model = glm::scale(model, Character::getScale());
            if (character.checkLastDirectionLeft()) {
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
                ShootingEnemy* tempShoot = enemies.getShootingEnemyAtVectorPos(i);
                if (!tempShoot->getCullingStatus()) {
                    continue;
                }

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

                model = glm::mat4(1.0f);
                model = glm::translate(model, tempShoot->getTexturePosition());
                model = glm::scale(model, ShootingEnemy::getScale());
                if (tempShoot->checkLastDirectionLeft()) {
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
                if (!tempWalker->getCullingStatus()) {
                    continue;
                }

                model = glm::mat4(1.0f);
                model = glm::translate(model, tempWalker->getTexturePosition());
                model = glm::scale(model, WalkingEnemy::getScale());
                if (tempWalker->checkLastDirectionLeft()) {
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
            collectables.checkForCollision(character.getHitbox(), levelBarrier.getCurrentX());
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
            Shader::DeactivateCurrentShader();
            themeChangingShader.activateThisShader();

            glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

            themeChangingShader.setIntUniform("height", UserInterfaceParameters::Height);
            themeChangingShader.setIntUniform("width", UserInterfaceParameters::Width);
            themeChangingShader.setMat4Uniform("VP", projection * view);
            themeChangingShader.setFloatUniform("barrierSize", 8.0f);
            themeChangingShader.setVec3Uniform("barrierPos", levelBarrier.getPosition());
            themeChangingShader.setIntUniform("lightRadius", levelBarrier.getRadius());
            themeChangingShader.setVec4Uniform("lightColor", levelBarrier.getColorAndBrightness());

            themeChangingShader.setBoolUniform("drawLight", false);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadPos), quadPos, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glDisable(GL_BLEND);

            themeChangingShader.setBoolUniform("drawLight", true);
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadPos), quadPos, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glDisable(GL_BLEND);

            Shader::DeactivateCurrentShader();
            textureShader.activateThisShader();

            glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        ui.drawUI();
        glfwSwapBuffers(ui.getWindowPointer());
        glfwPollEvents();
    }

    glDeleteBuffers(1, &textBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &quadBuffer);

    textureShader.deleteThisShader();
    levelTextureShader.deleteThisShader();
    projectileLightShader.deleteThisShader();
    themeChangingShader.deleteThisShader();
    parallaxShader.deleteThisShader();

    ui.cleanUp();
    return 0;
}