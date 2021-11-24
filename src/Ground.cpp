#include "../include/Ground.h"

Ground::Ground(int x, int y) : Mesh2D(), Transform(), Collider(){
    this->position.x = x;
    this->position.y = y;
   	color_top = vec4( 0.73, 0.56, 0.16, 1.0 );
	color_bottom = vec4( 0.96, 0.80, 0.3, 1.0 );

	color_cactus_top = vec4(0.0, 0.7, 0.0, 1.0);
	color_cactus_bottom = vec4(0.0, 0.5, 0.0, 1.0);
	cactus = MeshHermite(color_cactus_bottom, color_cactus_top);

	color_rock_top = vec4(0.71, 0.71, 0.71, 1.0);
	color_rock_bottom = vec4(0.47, 0.47, 0.47, 1.0);
	for (int i = 0; i < 2; i++)
	rock[i] = MeshHermite(color_rock_bottom, color_rock_top);	

	hasLoadedFiles = false;
}

void Ground::drawMesh(int ModelUniform){ 
    glBindVertexArray(VAO);

	vec2 position_ = vec2(position.x, position.y);
	vec2 scaleFactor = vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)*0.3);

    Model = mat4(1.0);
	Model = translate(Model, vec3(position_, 0.0));
	Model = scale(Model, vec3(scaleFactor, 1.0));
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model)); // assegno il valore di model allo uniform nello shader
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glBindVertexArray(0);

	//glBindVertexArray(VAO);	
	if (hasLoadedFiles){
		cactus.drawMesh(ModelUniform, GL_TRIANGLE_FAN, vec2(1200, position.y + 250), vec2(300, 300));
		rock[1].drawMesh(ModelUniform, GL_TRIANGLE_FAN, vec2(100, position.y + 160), vec2(250, 250));
		rock[0].drawMesh(ModelUniform, GL_TRIANGLE_FAN, vec2(200, position.y + 160), vec2(300, 300));
	}


	// updating colliders after transformations
	topLeftCorner = vec2(vertices.at(verticesNumber - 1).x * scaleFactor.x + position.x,
		vertices.at(verticesNumber - 1).y * scaleFactor.y + position_.y - 60);
	bottomRightCorner = vec2(vertices.at(verticesNumber - 3).x * scaleFactor.x + position.x, 
		vertices.at(verticesNumber - 3).y * scaleFactor.y + position_.y - 60);
	
	glBindVertexArray(0);
}

void Ground::buildMesh(){
	vertices.clear();
	colors.clear();

	bool loadedCactus, loadedRock;
	cactus.setCenterPoint(vec3(0.5,0.43, 0.0));
	loadedCactus = cactus.loadFromFile("assets/cactus.json");
	if (loadedCactus) cactus.initMesh();
	
	for (int i = 0; i < 2; i++){
		rock[i].setCenterPoint(vec3(0.5,0.43, 0.0));
		loadedRock = rock[i].loadFromFile("assets/rock.json");
		if (loadedRock) rock[i].initMesh();
	}

	hasLoadedFiles = loadedCactus && loadedRock;

	vertices.push_back(vec3(0.0, 0.0,0.0));
	colors.push_back(color_bottom);
	vertices.push_back(vec3(1.0, 0.0, 0.0));
	colors.push_back(color_bottom);
	vertices.push_back(vec3(0.0, 1.0, 0.0));
	colors.push_back(color_top);
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(color_top);

	buildColliders();

	// adding collider geometry for debugging
	vertices.push_back(vec3(topLeftCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, topLeftCorner.y, 0.0));
	vertices.push_back(vec3(topLeftCorner.x, topLeftCorner.y, 0.0));
	for (int i = 0; i < 4; i++) colors.push_back(vec4(COLLIDER_COLORS));

	verticesNumber = vertices.size();
}

void Ground::buildColliders(){
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

void Ground::setupValues(float x, float y){
	this->position.x = x;
    this->position.y = y;
}