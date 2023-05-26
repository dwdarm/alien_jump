// how to compile: g++ main.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -Wall

#include <string>
#include <vector>
#include <memory>

#include "libs/all.h"
#include "entities/player.h"
#include "entities/enemies/enemies.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "jump alien"

#define FRAMELIMIT 60

#define CHAR_TEXTURE_PATH "assets/characters_packed.png"
#define CHAR_TILE_SIZE 24
#define SPRITE_SIZE 32

#define BG_TEXTURE_PATH "assets/background.png"
#define GR_TEXTURE_PATH "assets/ground.png"

#define FONT_PATH "assets/fonts/kenvector_future.fnt"

#define GROUND_LEVEL WINDOW_HEIGHT - 144
#define GRAVITY 1

namespace dwdarm {

class Game {
    public:
        Game() : mPlayer(32, 24, GROUND_LEVEL, 1) {
            initTextures();
            initBg();
            initGr();
            initPlayer();
            reset();
        }

        void reset() {
            mBgSprite.setPosition(0, 0);
            mGrSprite.setPosition(0, GROUND_LEVEL + SPRITE_SIZE);
            mPlayer.setPosition(100, GROUND_LEVEL);
            mEnemies.clear();

            mPause = false;
            mOver = false;
            mScore = 0;
        }

        void update() {
            handleEvent();

            if (!mPause && !mOver) {
                mPlayer.tick();
                mScore++;

                updateEnemies();

                mBgSprite.setTextureRect(mBgX, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                mBgX+=1;

                mGrSprite.setTextureRect(mGrX, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
                mGrX+=1;

                handleCollision();
            }
        }

        void draw() {
            mBgSprite.draw();
            mGrSprite.draw();

            for (auto enemy : mEnemies) {
                enemy->draw();
            }

            mPlayer.draw();

            drawScore();

            if (mOver) {
                drawGameOver();
            }
        }

    private:

        void drawScore() {
            int fontSize = 18, padding = 4;
            int posX = 10, posY = 10;
            std::string score = "Score: " + std::to_string(mScore);
            int textWidth = MeasureText(score.c_str(), fontSize);
            
            DrawRectangle(WINDOW_WIDTH - (textWidth + (padding*2) + posX), posY, textWidth + (padding*2), fontSize + (padding*2), BLACK);
            DrawText(score.c_str(), WINDOW_WIDTH - (textWidth + (padding*2) + (posX - padding)), posY + padding , fontSize, WHITE);
        }

        void drawGameOver() {
            int fontSize = 32;
            std::string text = "Game Over";
            int textWidth = MeasureText(text.c_str(), fontSize);
            int posX = (WINDOW_WIDTH/2) - (textWidth/2);
            int posY = (WINDOW_HEIGHT/2) - (fontSize/2);
            DrawText(text.c_str(), posX, posY, fontSize, RED);

            fontSize = 18;
            text = "Press enter to restart";
            posY = posY + 64;
            DrawText(text.c_str(), posX, posY, fontSize, BLACK);
        }

        void initTextures() {
            charTextureMap.loadFromFile(CHAR_TEXTURE_PATH);
            mBgTexture.loadFromFile(BG_TEXTURE_PATH);
            mGrTexture.loadFromFile(GR_TEXTURE_PATH);
        }

        void initPlayer() {
            mPlayer.setTexture(&charTextureMap);
            mPlayer.updateTexture();
        }

        void initBg() {
            mBgSprite.setTexture(&mBgTexture);
        }

        void initGr() {
            mGrSprite.setTexture(&mGrTexture);
        }

        void updateEnemies() {
            if (mEnemies.size() < 4) {
                int index = GetRandomValue(0, 2);
                Entity *enemy = nullptr;

                if (index == 0) {
                    enemy = new Spike(SPRITE_SIZE, CHAR_TILE_SIZE, GROUND_LEVEL);
                    enemy->setTexture(&charTextureMap);
                    ((Spike*)enemy)->updateTexture();
                } else if (index == 1) {
                    enemy = new Bug(SPRITE_SIZE, CHAR_TILE_SIZE, GROUND_LEVEL);
                    enemy->setTexture(&charTextureMap);
                    ((Bug*)enemy)->updateTexture();
                } else if (index == 2) {
                    enemy = new Bat(SPRITE_SIZE, CHAR_TILE_SIZE, GROUND_LEVEL);
                    enemy->setTexture(&charTextureMap);
                    ((Bug*)enemy)->updateTexture();
                }

                if (enemy) {
                    float posY = enemy->canFly() ? GROUND_LEVEL - (SPRITE_SIZE + 8) : GROUND_LEVEL;

                    if (mEnemies.size() == 0) {
                        enemy->setPosition(WINDOW_WIDTH + SPRITE_SIZE, posY);
                    } else {
                        std::shared_ptr<Entity>& last = mEnemies.back();
                        enemy->setPosition(last->getPosition().x + (SPRITE_SIZE * GetRandomValue(7, 10)), posY);
                    }

                    mEnemies.push_back(std::shared_ptr<Entity>(enemy));
                }
            } else {
                for (int i = 0; i < mEnemies.size(); i++) {
                    mEnemies[i]->move(-mSpeed, 0);
                    mEnemies[i]->tick();
                    if ((mEnemies[i]->getPosition().x + SPRITE_SIZE) <= 0) {
                        mEnemies.erase(mEnemies.begin() + i);
                    } 
                }
            }
        }

        void handleCollision() {
            for (auto enemy : mEnemies) {
                if (CheckCollisionRecs(
                    { mPlayer.getPosition().x, mPlayer.getPosition().y, SPRITE_SIZE, SPRITE_SIZE },
                    { enemy->getPosition().x, enemy->getPosition().y, SPRITE_SIZE, SPRITE_SIZE }
                )) {
                    mOver = true;
                    break;
                }
            }
        }

        void handleEvent() {
            if (IsKeyPressed(KEY_SPACE)) {
                if (!mPause && !mOver) {
                    mPlayer.jump();
                }
            } else if(IsKeyPressed(KEY_ENTER)) {
                if (mOver) {
                    reset();
                } else {
                    mPause = !mPause;
                }
            } 
        }

        dwdarm::Player mPlayer;
        dwdarm::Texture charTextureMap;
        int mSpeed = 6;

        dwdarm::Texture mBgTexture;
        dwdarm::Sprite mBgSprite;
        int mBgX = 0;

        dwdarm::Texture mGrTexture;
        dwdarm::Sprite mGrSprite;
        int mGrX = 0;

        std::vector<std::shared_ptr<dwdarm::Entity>> mEnemies;

        bool mPause = false;
        bool mOver = false;
        int mScore = 0;
};

};

void drawLoop(void* arg) {
    dwdarm::Game* game = (dwdarm::Game*)arg;

    game->update();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        game->draw();
    EndDrawing();
}


int main() {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    dwdarm::Game game;

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop_arg(drawLoop, (void*)&game,0, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            drawLoop((void*)&game);
        }
    #endif

    CloseWindow();  

    return 0;
}