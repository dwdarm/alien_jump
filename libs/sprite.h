#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "drawable.h"
#include "transformable.h"
#include "texture.h"

#include <cmath>

namespace dwdarm {

class Sprite : public Drawable, public Transformable {
    public:
        void setTexture(dwdarm::Texture *texture) {
            mTexture = texture;
            mTextureRect.x = 0;
            mTextureRect.y = 0;

            Vector2 textureSize = mTexture->getSize();
            mTextureRect.width = textureSize.x;
            mTextureRect.height = textureSize.y;
        }

        void setTextureRect(float x, float y, float w, float h) {
            mTextureRect.x = x;
            mTextureRect.y = y;
            mTextureRect.width = w;
            mTextureRect.height = h;
        }

        void draw() {
            DrawTexturePro(
                mTexture->getHandle(), 
                mTextureRect, 
                { mPosition.x, mPosition.y, abs(mTextureRect.width) * mScale.x, abs(mTextureRect.height) * mScale.y }, 
                mOrigin, 
                mRotation, 
                mColor
            );
        }

    private:
        dwdarm::Texture *mTexture = nullptr;
        Color mColor = RAYWHITE;
        Rectangle mTextureRect = {0};
};

};

#endif