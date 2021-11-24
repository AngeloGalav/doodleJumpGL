#ifndef SKY_H
#define SKY_H

#include "Mesh2D.h"
#include "Definitions.h"
#include "Transform.h"

class Sky : public Mesh2D, public Transform{
        vec4 color_top;
        vec4 color_bot;
    
    public:
        Sky(float x,float y);

        virtual void drawMesh(int ModelUniform);
        virtual void buildMesh();
};

#endif