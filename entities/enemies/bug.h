#ifndef _ENTITY_H_
#include "../entity.h"
#endif

namespace dwdarm {

class Bug : public dwdarm::Entity {
    public:

        Bug(int spriteSize, int tileSize, float groundLevel) {
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
            setTextureRect((3 + animState) * mTileSize, 2 * mTileSize, mTileSize, mTileSize);
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