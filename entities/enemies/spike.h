#ifndef _ENTITY_H_
#include "../entity.h"
#endif

namespace dwdarm {

class Spike : public dwdarm::Entity {
    public:

        Spike(int spriteSize, int tileSize, float groundLevel) {
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
            setTextureRect((6 + animState) * mTileSize, 1 * mTileSize, mTileSize, mTileSize);
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