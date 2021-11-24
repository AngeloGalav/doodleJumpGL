#ifndef HERMITE_BUILDER_H
#define HERMITE_BUILDER_H
#include "json.hpp"
#include "Lib.h"
#include "Mesh2D.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define  PI   3.14159265358979323846
#define PHI0(t)  (2.0*t*t*t-3.0*t*t+1)
#define PHI1(t)  (t*t*t-2.0*t*t+t)
#define PSI0(t)  (-2.0*t*t*t+3.0*t*t)
#define PSI1(t)  (t*t*t-t*t)

class MeshHermite : public Mesh2D
{
private:
    vec4 color_top;
    vec4 color_bot;
    bool isDefinedByFile;
    float* t; // interval
    vec3 centerPoint; // il punto centrale del triangle fan
public:
    MeshHermite(vec4 cb, vec4 ct);
    MeshHermite();
    float Tens = 0.0, Bias = 0.0, Cont = 0.0;
    int pval; // number of points to draw
    vector<vec3> controlPoints; 
    void setCenterPoint(vec3 cpoint);
    float dx(int i);
    float dy(int i);
    void InterpolazioneHermite(float* t);
    bool loadFromFile(std::string path);
    virtual void buildMesh();
    virtual void drawMesh(int ModelUniform);
    void drawMesh(int ModelUniform, GLenum drawMode, vec2 position, vec2 scaleFactor);
    void drawMesh(int ModelUniform, GLenum drawMode, vec2 position, vec2 scaleFactor, GLuint myVAO);
    vector<vec3> getVerticesVector();
    vector<vec4> getColorsVector();
    vec3 getCenterPoint();
};

#endif