#ifndef GROUND_H
#define GROUND_H

#include "Mesh2D.h"
#include "Transform.h"
#include "Collider.h"
#include "Definitions.h"
#include "MeshHermite.h"

class Ground : public Mesh2D, public Collider, public Transform{

protected:
    vec4 color_top;
    vec4 color_bottom;
    vec4 color_rock_top;
    vec4 color_rock_bottom;
    vec4 color_cactus_top;
    vec4 color_cactus_bottom;

    bool hasLoadedFiles;

public:
    // props
    MeshHermite cactus;
    MeshHermite rock[2];

    Ground(int x,int y);

    virtual void drawMesh(int ModelUniform);
    virtual void buildMesh();
    void buildColliders();

    void setupValues(float x, float y);
};

#endif