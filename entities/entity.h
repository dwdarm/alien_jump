#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../libs/sprite.h"

#define UPDATE_ANIMATION_IN_MS 250

namespace dwdarm {

class Entity : public dwdarm::Sprite {
    public:
        virtual void tick() {}
        virtual bool canFly() { return false; }
};

};

#endif