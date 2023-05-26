#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

namespace dwdarm {

class Drawable {
    public:
        ~Drawable() {};

    protected:
        virtual void draw() = 0;
};

};

#endif