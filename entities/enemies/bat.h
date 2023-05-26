#ifndef _ENTITY_H_
#include "../entity.h"
#endif

namespace dwdarm {

class Bat : public dwdarm::Entity {
    public:

        Bat(int spriteSize, int tileSize, float groundLevel) {
            mSpriteSize = spriteSize;
            mTileSize = tileSize;
            mGroundLevel = groundLevel;
            setScale((float)mSpriteSize / mTileSize, (float)mSpriteSize / mTileSize);
        }

        void tick() {
            mAnimate++;
            if (mAnimate >= 20) {
                updateAnimation();
                mAnimate = 0;
            }
        }

        void updateTexture() {
            setTextureRect((6 + animState) * mTileSize, 2 * mTileSize, mTileSize, mTileSize);
        }

        bool canFly() {
            return true;
        }

    private:

        void updateAnimation() {
            updateTexture();

            animState++;
            if (animState >= 3) {
                animState = 0;
            }
        }

        int animState = 0;
        int mSpriteSize, mTileSize;
        float mGroundLevel;
        int mAnimate = 0;
};

};