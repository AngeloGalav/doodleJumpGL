#include "../include/Platform.h"

Platform::Platform(int x, int y) : Mesh2D(), Transform(), Collider(){
    this->position.x = x;
    this->position.y = y;
   	color_top = { 106/255, 90/255, 205/255, 1.0 };
	color_bottom = { 1.0, 0.0, 0.0, 1.0 };
	color_bottom_mov = { 0.0, 0.0, 1.0, 1.0 };
	direction = 1;
	velocity = 3.0;
	isMovable = false;
}

Platform::Platform(int x, int y, bool isMovable, bool goesForward) : Mesh2D(), Transform(), Collider(){
    this->position.x = x;
    this->position.y = y;
   	color_top = { 106/255, 90/255, 205/255, 1.0 };
	color_bottom = { 1.0, 0.0, .0, 1.0 };
	color_bottom_mov = { 0.0, 0.0, 1.0, 1.0 };
	direction = 1;
	velocity = 3.0;
	this->isMovable = isMovable;
	goesForward ? direction = -1 : direction = 1; 
}

void Platform::drawMesh(int ModelUniform){ 
    glBindVertexArray(VAO);

	vec2 position_ = vec2(position.x, position.y);
	vec2 scaleFactor = vec2(60.0, 10.0);

    Model = mat4(1.0);
	Model = translate(Model, vec3(position_, 0.0));
	Model = scale(Model, vec3(scaleFactor, 1.0));
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model)); // assegno il valore di model allo uniform nello shader
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// setup della mostra dei colliders uuuh (da mettere in toggle durante la modalità debug)
	Model = mat4(1.0);
	Model = translate(Model, vec3(position_, 0.0f));
	Model = scale(Model, vec3(scaleFactor, 1.0));
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
	glDrawArrays(GL_LINE_LOOP, 4, 4);


	// updating colliders after transformations
	topLeftCorner = vec2(vertices.at(verticesNumber - 1).x * scaleFactor.x + position.x,
		vertices.at(verticesNumber - 1).y * scaleFactor.y + position_.y);
	bottomRightCorner = vec2(vertices.at(verticesNumber - 3).x * scaleFactor.x + position.x, 
		vertices.at(verticesNumber - 3).y * scaleFactor.y + position_.y);
	
	glBindVertexArray(0);
}

void Platform::buildMesh(){
	vertices.clear();
	colors.clear();

	vertices.push_back(vec3(-1.0, -1.0, 0.0));
	isMovable ? colors.push_back(color_bottom_mov) : colors.push_back(color_bottom);
	
    vertices.push_back(vec3(1.0, -1.0, 0.0));
	isMovable ? colors.push_back(color_bottom_mov) : colors.push_back(color_bottom);
    
    vertices.push_back(vec3(-1.0, 1.0, 0.0));
	colors.push_back(vec4(color_top.r, color_top.g, color_top.b, color_top.a));
    
    vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(vec4(color_top.r, color_top.g, color_top.b, color_top.a));

	buildColliders();

	///WARNING: this is just debug code, to be deleted in the final version
	vertices.push_back(vec3(topLeftCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, bottomRightCorner.y, 0.0));
	vertices.push_back(vec3(bottomRightCorner.x, topLeftCorner.y, 0.0));
	vertices.push_back(vec3(topLeftCorner.x, topLeftCorner.y, 0.0));
	for (int i = 0; i < 4; i++) colors.push_back(vec4(COLLIDER_COLORS));

	verticesNumber = vertices.size();
}

void Platform::movePlatform(){
	if (isMovable){
		if (position.x <= 0 || position.x >= SCREEN_WIDTH) direction *= -1; 
		position.x += direction * velocity;
	}
}

void Platform::buildColliders(){
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

void Platform::setMovable(bool mov){
	isMovable = mov;
}