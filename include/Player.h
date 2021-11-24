#ifndef PLAYER_H
#define PLAYER_H

#include "Lib.h"
#include "Transform.h"
#include "Mesh2D.h"
#include "Definitions.h"
#include "MeshHermite.h"
#include "Collider.h"

class Player : public Mesh2D, public Transform, public Collider
{
protected:
  vec4 color_top;
  vec4 color_bot;
  vec4 color_eyes;
  bool hermiteMeshLoaded;

public:
  virtual void drawMesh(int ModelUniform);
  virtual void buildMesh();
  void buildColliders();
  Player(int nTriangles, float x, float y);
  MeshHermite specialMesh; // il mesh fatto con hermite

  void setupValues(float x, float y);

  float distacco_da_terra; // distacco da terra è negativo,
  // siccome lo misuro nel sistema di riferimento locale della palla
};

#endif