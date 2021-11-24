#include "../include/MeshHermite.h"

using json = nlohmann::json;

MeshHermite::MeshHermite(vec4 cb, vec4 ct) : Mesh2D() {
    Tens = 0.0;
    Bias = 0.0;
    Cont = 0.0;
    color_bot = cb;
    color_top = ct;
	isDefinedByFile = false;
	pval = 300;
}

MeshHermite::MeshHermite() : Mesh2D() {

}

float MeshHermite::dx(int i)
{
	if (i == 0)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (controlPoints[i + 1].x - controlPoints[i].x) / (t[i + 1] - t[i]);
	if (i == controlPoints.size() - 1)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (controlPoints[i].x - controlPoints[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 + Cont) * (controlPoints.at(i).x - controlPoints.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (controlPoints.at(i + 1).x - controlPoints.at(i).x) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 - Cont) * (controlPoints.at(i).x - controlPoints.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (controlPoints.at(i + 1).x - controlPoints.at(i).x) / (t[i + 1] - t[i]);
}

float MeshHermite::dy(int i)
{
	if (i == 0)
		return 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1 - Cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
	if (i == controlPoints.size() - 1)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (controlPoints.at(i).y - controlPoints.at(i - 1).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 + Cont) * (controlPoints.at(i).y - controlPoints.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 - Cont) * (controlPoints.at(i).y - controlPoints.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (controlPoints.at(i + 1).y - controlPoints.at(i).y) / (t[i + 1] - t[i]);
}

void MeshHermite::InterpolazioneHermite(float* t)
{
	float p_t = 0, p_b = 0, p_c = 0, x, y;
	float passotg = 1.0 / (float)(pval - 1);
	 
	float tg = 0, tgmapp, ampiezza;
	int i = 0;
	int is = 0; //indice dell'estremo sinistro dell'intervallo [t(i),t(i+1)] a cui il punto tg
				//appartiene

	vertices.clear();
	colors.clear();

    if (!isDefinedByFile){
		vertices.push_back(vec3(0.0, 0.0, 0.0)); // default mesh
		colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	} else {
		vertices.push_back(centerPoint);
		colors.push_back(color_top);
	}


	for (tg = 0; tg <= 1; tg += passotg)
	{
		if (tg > t[is + 1]) is++;

		ampiezza = (t[is + 1] - t[is]);
		tgmapp = (tg - t[is]) / ampiezza;

		x = controlPoints[is].x * PHI0(tgmapp) + dx(is) * PHI1(tgmapp) * ampiezza + controlPoints[is + 1].x * PSI0(tgmapp) + dx(is + 1) * PSI1(tgmapp) * ampiezza;
		y = controlPoints[is].y * PHI0(tgmapp) + dy(is) * PHI1(tgmapp) * ampiezza + controlPoints[is + 1].y * PSI0(tgmapp) + dy(is + 1) * PSI1(tgmapp) * ampiezza;
		vertices.push_back(vec3(x, y, 0.0));
		colors.push_back(color_bot);
	}

    verticesNumber = vertices.size();
}

void MeshHermite::buildMesh()
{
	if (!isDefinedByFile)	// se non l'ho definito con un file, allora metto un mesh di Default 
	{
		controlPoints.push_back(vec3(0.0,0.0,0.0));
		controlPoints.push_back(vec3(-2.0, 0.0, 0.0));
		controlPoints.push_back(vec3(-2.0, 3.0, 0.0));
		controlPoints.push_back(vec3(-2.0, 5.0, 0.0));
		controlPoints.push_back(vec3(-6.0, 6.0, 0.0));
		controlPoints.push_back(vec3(-5.0, 8.0, 0.0));
		controlPoints.push_back(vec3(0.0, 14.0, 0.0));
		controlPoints.push_back(vec3(5.0, 8.0, 0.0));
		controlPoints.push_back(vec3(6.0, 6.0, 0.0));
		controlPoints.push_back(vec3(2.0, 5.0, 0.0));
		controlPoints.push_back(vec3(2.0, 3.0, 0.0));
		controlPoints.push_back(vec3(2.0, 0.0, 0.0));
		controlPoints.push_back(vec3(0.0, 0.0, 0.0));
	}

    t = new float[controlPoints.size()];
    int i;
    float step = 1.0 / (float)(controlPoints.size() - 1);

    for (i = 0; i < controlPoints.size(); i++)
        t[i] = (float)i * step;

    InterpolazioneHermite(t);

	// normalizzazione dei punti
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x -= centerPoint.x;
		vertices[i].y -= centerPoint.y;
	}
    verticesNumber = vertices.size();
}

bool MeshHermite::loadFromFile(std::string path)
{
    ifstream inputFile(path);
    if (inputFile)
    {
        json jsonParser;
        inputFile >> jsonParser;
        controlPoints.clear();
		isDefinedByFile = true;

        for (int i = 0; i < jsonParser["vertices"].size(); i++)
            controlPoints.push_back(vec3((float) jsonParser["vertices"].at(i)[0], (float) jsonParser["vertices"].at(i)[1], 0.0));

		return true;

    } else std::cout << "Erroraccio nella lettura del file" << std::endl;

	return false;
}

void MeshHermite::drawMesh(int ModelUniform){
    Model = mat4(1.0);
    if (controlPoints.size() > 1)
    {	glBindVertexArray(VAO);
        glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
        glBindVertexArray(0);
    }
}

void MeshHermite::drawMesh(int ModelUniform, GLenum drawMode, vec2 position, vec2 scaleFactor){
    Model = mat4(1.0);
    if (controlPoints.size() > 1)
    {	
		glBindVertexArray(VAO);
        Model = translate(Model, vec3(position, 0.0));
	    Model = scale(Model, vec3(scaleFactor, 1.0));
        glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
        glDrawArrays(drawMode, 0, vertices.size());
    }
}

void MeshHermite::drawMesh(int ModelUniform, GLenum drawMode, vec2 position, vec2 scaleFactor, GLuint myVAO){
    Model = mat4(1.0);
    if (controlPoints.size() > 1)
    {	
		glBindVertexArray(myVAO);
        Model = translate(Model, vec3(position, 0.0));
	    Model = scale(Model, vec3(scaleFactor, 1.0));
        glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
        glDrawArrays(drawMode, 0, vertices.size());
    }
}

void MeshHermite::setCenterPoint(vec3 cp){
	centerPoint = cp;
}

vec3 MeshHermite::getCenterPoint(){
	return centerPoint;
}

vector<vec3> MeshHermite::getVerticesVector(){
	return vertices;
}

vector<vec4> MeshHermite::getColorsVector(){
	return colors;
}