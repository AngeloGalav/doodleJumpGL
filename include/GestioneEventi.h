#ifndef GESTIONE_EVENTI_H
#define GESTIONE_EVENTI_H

#include "Lib.h"
#include "Definitions.h"
#include "Collider.h"

void keyboardPressedEvent(unsigned char key, int x, int y);
void keyboardReleasedEvent(unsigned char key, int x, int y);
void update(int a);
void update_pala(int a);
void processCollisions();
bool checkCollision(Collider obj1, Collider obj2);

#endif