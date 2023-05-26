#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "raylib.h"

namespace dwdarm {

class Texture {

    public:

        ~Texture() {
            UnloadTexture(mtextureHandle);
        }

        void loadFromFile(const std::string &filename) {
            mtextureHandle = LoadTexture(filename.c_str());
        }

        Vector2 getSize() const {
            return Vector2{ (float)mtextureHandle.width, (float)mtextureHandle.height };
        }

        const Texture2D& getHandle() const {
            return mtextureHandle;
        }

    private:
        Texture2D mtextureHandle;
};

};

#endif