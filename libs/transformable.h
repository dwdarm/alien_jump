#ifndef _TRANSFORMABLE_H_
#define _TRANSFORMABLE_H_

#include "raylib.h"

namespace dwdarm {

class Transformable {
    public:
        ~Transformable () {};

        void setOrigin(float x, float y) {
            mOrigin = { x, y };
        }
        const Vector2& getOrigin() const {
            return mOrigin;
        }

        void setScale(float x, float y) {
            mScale = { x, y};
        }
        const Vector2& getScale() const {
            return mScale;
        }

        void setPosition(float x, float y) {
            mPosition = { x, y };
        }
        const Vector2& getPosition() const {
            return mPosition;
        }

        void setRotation(float rotation) {
            mRotation = rotation;
        }
        float getRotation() const {
            return mRotation;
        }

        void move(float x, float y) {
            mPosition = { mPosition.x += x, mPosition.y += y };
        }

    protected:
        Vector2 mOrigin = {0};
        Vector2 mScale = { 1.0f, 1.0f };
        Vector2 mPosition = {0};
        float mRotation = 0;
};

};

#endif