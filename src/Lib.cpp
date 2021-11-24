#include "../include/Lib.h"

double lerp(double a, double b, double amount) {

	//Interpolazione lineare tra a e b secondo amount
	return (1 - amount) * a + amount * b;
}

/*
void INIT_SHADER(int *programId)
{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"shaders/vertexShader_M.glsl";
	char* fragmentShader = (char*)"shaders/fragmentShader_M.glsl";

	*programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(*programId);
}*/
