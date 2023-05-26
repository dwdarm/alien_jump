#ifndef _ENTITY_H_
#include "entity.h"
#endif

namespace dwdarm {

class Player : public dwdarm::Entity {
    public:

        Player(int spriteSize, int tileSize, float groundLevel, float gravity) {
            mSpriteSize = spriteSize;
            mTileSize = tileSize;
            mGroundLevel = groundLevel;
            mGravity = gravity;
            updateTexture();
            setScale((float)mSpriteSize / mTileSize, (float)mSpriteSize / mTileSize);
        }

        void tick() {
            static int update = 0;

            update++;
            if (update >= 20) {
                updateAnimation();
                update = 0;
            }

            updateMovement();
        }

        void jump() {
            if (mY >= mGroundLevel) {
                mVY = -14;
            }
        }

        void updateTexture() {
            setTextureRect((animState * mTileSize), 0, -mTileSize, mTileSize);
        }

    private:

        void updateAnimation() {
            updateTexture();

            animState++;
            if (animState >= 2) {
                animState = 0;
            }
        }

        void updateMovement() {
            if (mY < mGroundLevel) {
                mVY += mGravity;
            }

            mVY += mAY;
            mY += mVY;

            if (mY > mGroundLevel) {
                mY = mGroundLevel;
            }

            setPosition(getPosition().x, mY);
        }

        int animState = 0;
        int mSpriteSize, mTileSize;
        float mGroundLevel, mGravity;
        float mX = 0, mY = 0, mVX = 0, mVY = 0, mAX = 0, mAY = 0;
};

};