#include "../include/Sky.h"

Sky::Sky(float x, float y) : Mesh2D(), Transform() {
    this->position.x = x;
    this->position.y = y;
   	color_top = vec4( 0.0, 0.0, 0.6, 1.0 );
	color_bot = vec4( 0.0, 0.5, 1.0, 1.0 );
}

void Sky::drawMesh(int ModelUniform){ 
    glBindVertexArray(VAO);

	vec2 position_ = vec2(position.x, position.y);
	vec2 scaleFactor = vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT));

    Model = mat4(1.0);
	Model = translate(Model, vec3(position_, 0.0));
	Model = scale(Model, vec3(scaleFactor, 1.0));
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model)); // assegno il valore di model allo uniform nello shader
	glDrawArrays(GL_TRIANGLE_STRIP, 0, verticesNumber);
	
	glBindVertexArray(0);
}

void Sky::buildMesh(){
	vertices.push_back(vec3(0.0, 0.0,0.0));
	colors.push_back(color_bot);
	vertices.push_back(vec3(1.0, 0.0, 0.0));
	colors.push_back(color_bot);
	vertices.push_back(vec3(0.0, 1.0, 0.0));
	colors.push_back(color_top);
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(color_top);

	verticesNumber = vertices.size();
}