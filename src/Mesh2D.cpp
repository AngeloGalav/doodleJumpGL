#include "../include/Mesh2D.h"
#include <iostream>

Mesh2D::Mesh2D(){}

void Mesh2D::initMesh(){
	buildMesh();
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero, rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

// setta la Model Matrix, che contiene tutte le modellazione che l'oggetto dovrà subire prima di essere 
// mostrato su schermo. 
void Mesh2D::setModelMatrix(mat4 Model){
    this->Model = Model;
}   

// ritorna l'id del VAO
GLuint Mesh2D::getVAO(){
    return VAO;
}

// ritorna il numero di vertici nell'oggetto
int Mesh2D::getNumberOfVertices(){
    return verticesNumber;
}

void Mesh2D::drawMesh(int ModelUniform){} // ogni oggetto renderizzabile deve incorporare questa funzione
void Mesh2D::buildMesh(){ std::cout << "ops.. qualcuno si e' sbagliato... \n";}