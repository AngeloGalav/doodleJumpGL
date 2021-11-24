#include "../include/Player.h"
#include <iostream>

Player::Player(int nTriangles, float x, float y) : Mesh2D(), Transform(), Collider()
{
    this->nTriangles = nTriangles;
    this->position.x = x;
    this->position.y = y;
    distacco_da_terra = 30;
    color_top = vec4(0.0, 0.4, 0.0, 1.0);
	color_bot = vec4(0.3, 0.6, 0.0, 1.0);
	color_eyes = vec4(0.0, 0.0, 0.0, 1.0);

	hermiteMeshLoaded = false;
	specialMesh = MeshHermite(color_bot, color_top);
}

// funzione provvisoria per la costruzione del mesh dedicato al protagonista
void Player::buildMesh()
{
	vertices.clear();
	colors.clear();

	specialMesh.setCenterPoint(vec3(0.35,0.43, 0.0));
	hermiteMeshLoaded = specialMesh.loadFromFile("assets/doodle.json");
	if (hermiteMeshLoaded) {
		specialMesh.initMesh();
		vertices = specialMesh.getVerticesVector();
		colors = specialMesh.getColorsVector();
		if (DEBUG_MODE) std::cout << "vertices: " << vertices.size() << std::endl;
	}
	else {
		float stepA = (2 * PI) / nTriangles;

		vertices.push_back(vec3(0.0, 0.0, 0.0));
		colors.push_back(color_bot);

		for (int i = 0; i <= nTriangles; i++)
		{
			float t = (float)i * stepA;

			vertices.push_back(vec3(cos(t), sin(t), 0.0));
			colors.push_back(color_top);
		}
	}
	buildColliders();

	// costruzione degli occhi
	float stepA = (2 * PI) / nTriangles;

	vertices.push_back(vec3(0.0, 0.0, 0.0));
	colors.push_back(color_eyes);

	for (int i = 0; i <= nTriangles; i++)
	{
		float t = (float) i * stepA;

		vertices.push_back(vec3(cos(t), sin(t), 0.0));
		colors.push_back(vec4(color_eyes.r, color_eyes.g, color_eyes.b, color_eyes.a));
	}


	// adding collider geometry
	vertices.push_back(vec3(topLeftCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, topLeftCorner.y, 0.0));
	vertices.push_back(vec3(topLeftCorner.x, topLeftCorner.y, 0.0));
	for (int i = 0; i < 4; i++) colors.push_back(vec4(COLLIDER_COLORS));

	verticesNumber = vertices.size();
	if (DEBUG_MODE) std::cout << "final vertices number: " << verticesNumber << std::endl;
}

// ModelUniform è il uniform nel vertexShader, per interfacciarlo appunto con lo shader.
void Player::drawMesh(int ModelUniform){
    
    float distacco_da_terra_n = -distacco_da_terra;

	glBindVertexArray(0);
	vec2 position_ = vec2(position.x, position.y + distacco_da_terra_n );
	vec2 scaleFactor;

	vec2 eyesScaleFactor = vec2(2, 6);
	vec2 eyesOffset = vec2(-5, 5);
	float eyesDistance = 10;

	if (!hermiteMeshLoaded){
		scaleFactor = vec2(30, 30);
		glBindVertexArray(VAO);	
		//matrice di Trasformazione della Palla
		Model = mat4(1.0);
		Model = translate(Model, vec3(position_ , 0.0f));
		Model = scale(Model, vec3(scaleFactor, 1.0));
		glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model)); // assegno il valore di model allo uniform nello shader
		
		//Disegna Corpo della palla  
		glDrawArrays(GL_TRIANGLE_FAN, 0, (nTriangles) + 2);
	} else {
		scaleFactor = vec2(200, 200);
		specialMesh.drawMesh(ModelUniform, GL_TRIANGLE_FAN, position_, scaleFactor, VAO);
	}

	// disegna occhi
	for (float i = 0; i <= eyesDistance; i += eyesDistance){
		Model = mat4(1.0);
		if (hermiteMeshLoaded) eyesOffset = vec2(12, 12);
		Model = translate(Model, vec3(position_.x + i + eyesOffset.x, position_.y + eyesOffset.y, 0.0f));
		Model = scale(Model, vec3(eyesScaleFactor, 1.0));
		glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model)); // assegno il valore di model allo uniform nello shader
		
		if (!hermiteMeshLoaded) glDrawArrays(GL_TRIANGLE_FAN, (nTriangles + 2), (nTriangles) + 2);
		else glDrawArrays(GL_TRIANGLE_FAN, specialMesh.getVerticesVector().size(), (nTriangles) + 2);
	}

	if (DEBUG_MODE){
		Model = mat4(1.0);
		Model = translate(Model, vec3(position_, 0.0f));
		Model = scale(Model, vec3(scaleFactor, 1.0));
		glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
		glDrawArrays(GL_LINE_LOOP, hermiteMeshLoaded ? (verticesNumber - 4) : (nTriangles + 2)*2, 4);
	}

	// updating colliders after transformations
	topLeftCorner = vec2(vertices.at(verticesNumber - 1).x * scaleFactor.x + position.x,
		vertices.at(verticesNumber - 1).y * scaleFactor.y + position_.y);
	bottomRightCorner = vec2(vertices.at(verticesNumber - 3).x * scaleFactor.x + position.x, 
		vertices.at(verticesNumber - 3).y * scaleFactor.y + position_.y);
	
	glBindVertexArray(0);
}

void Player::buildColliders(){
	vec2 min = vertices.at(0); 
	vec2 max = vertices.at(0); // minimun and maximum coordinates
	for (vec3 vert : vertices){
		if (min.x > vert.x) min.x = vert.x;
		if (min.y > vert.y) min.y = vert.y;
		if (max.x < vert.x) max.x = vert.x;
		if (max.y < vert.y) max.y = vert.y;
	}
	topLeftCorner.x = min.x;
	topLeftCorner.y = max.y;
	bottomRightCorner.x = max.x;
	bottomRightCorner.y = min.y;
}

void Player::setupValues(float x, float y){
    this->position.x = x;
    this->position.y = y;
    distacco_da_terra = 30;
}