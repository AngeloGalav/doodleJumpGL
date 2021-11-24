#ifndef MESH2D_H
#define MESH2D_H

#include "Lib.h"

class Mesh2D
{
    private:
        GLuint VBO_G; // VBO dei vertici
        GLuint VBO_C; // VBO dei colori
    
    protected:
        GLuint VAO;
        int verticesNumber; // numero vertici
        mat4 Model; // matrice di modellazione
        vector<vec3> vertices;
        vector<vec4> colors;

    public:
        Mesh2D();
        Mesh2D(int x,int y);
        void initMesh();
        void setModelMatrix(mat4 modelMatrix);
        GLuint getVAO();
        int getNumberOfVertices();
        int nTriangles;

        // these functions are required for each child!!!
        virtual void drawMesh(int ModelUniform); // ogni oggetto renderizzabile deve incorporare questa funzione
        virtual void buildMesh();
};

#endif