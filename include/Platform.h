#ifndef PLATFORM_H
#define PLATFORM_H

#include "Transform.h"
#include "Mesh2D.h"
#include "Collider.h"
#include "Lib.h"
#include "Definitions.h"

class Platform : public Collider, public Transform, public Mesh2D
{
    bool hasCollectable;
    bool isMovable;
    vec4 color_top;
    vec4 color_bottom;
    vec4 color_bottom_mov;

public:
    Platform(int x,int y); // TODO: creare un creatore dei collider per ogni entità
    Platform(int x, int y, bool isMovable, bool goesForward);
    Platform();

    virtual void drawMesh(int ModelUniform);
    virtual void buildMesh();
    void buildColliders();
    void movePlatform();

    int direction;
    float velocity;
    void setMovable(bool mov);

};

#endif