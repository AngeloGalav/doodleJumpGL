#ifndef COLLIDER_H
#define COLLIDER_H

#include "Lib.h"

// realizzazione di un collider di tipo AABB (Axis Aligned Bounding Box)
class Collider
{
  public:
    Collider();
    Collider(vec4 bounds);
    vec2 topLeftCorner;
    vec2 bottomRightCorner;
    //void displayColliders();
};

#endif