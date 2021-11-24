#ifndef LIB_H
#define LIB_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "ShaderMaker.h"
using namespace glm;
using namespace std;


double lerp(double a, double b, double amount);

/*
void INIT_SHADER(int *programId);
}*/

#endif