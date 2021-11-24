#include <iostream>
#include <string>
#include "../include/ShaderMaker.h"
#include "../include/Lib.h"
#include "../include/GestioneEventi.h"
#include "../include/Player.h"
#include "../include/Definitions.h"
#include "../include/Sky.h"
#include "../include/Ground.h"
#include "../include/Platform.h"

#define GLT_IMPLEMENTATION
#include "../include/gltext.h"

static unsigned int programId;

mat4 Projection;
GLuint MatProj, MatModelUniform;
int nv_P;

// Physics paramters
double delta = 1.5; // forza di gravita
double speedY = 20; // velocita verticale (pixel per frame)
double speedX = 0;  // velocita orizzontale (pixel per frame)

double accelerazione = 1; // forza di accelerazione data dalla tastiera
double decelerazione = 1; // decelerazione in assenza di input

GLTtext *textScore;
GLTtext *points_display;
GLTtext *restartText;
char points_string[50];
int heightValue = 0;

bool gameOver = false;
bool hasRestarted = false;

// elementi di gioco
Player playerBall(30, float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) * 0.30);
Sky cielo(0, 0);
Ground terra(0, 0);
vector<Platform*> platforms;

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"shaders/vertexShader_M.glsl";
	char* fragmentShader = (char*)"shaders/fragmentShader_M.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);

	glUseProgram(programId);
}

void setupGame(){
	int randWidth;
	int coinFlip;

	platforms.clear();

	// dichiarazione/riepimento dell'array di piattaforme
	for (int i = 0; i < PLATFORM_NUMBER; i++){
		randWidth = rand() % 7;
		coinFlip  = rand() % 2;

		platforms.push_back(new Platform(float(SCREEN_WIDTH) * (0.15 + (float) randWidth/10), 
			float(SCREEN_HEIGHT) * (0.35 + 0.20 * i), coinFlip, coinFlip));
	}

	gltSetText(textScore, "Height: ");
	speedY = 20; // velocita verticale (pixel per frame)
	speedX = 0;  // velocita orizzontale (pixel per frame)

	heightValue = 0;
	gameOver = false;
	hasRestarted = false;

	terra.setupValues(0, 0);
	playerBall.setupValues(float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) * 0.30);

	for (Platform* plat : platforms){
		plat->initMesh();
	}

}

void INIT_VAO(void)
{
	vec4 col_bottom;
	vec4 col_top;

	setupGame();

	terra.initMesh();
	cielo.initMesh();
	playerBall.initMesh();

	//Costruzione della matrice di Proiezione
	Projection = ortho(0.0f, float(SCREEN_WIDTH), 0.0f, float(SCREEN_HEIGHT));
	MatProj = glGetUniformLocation(programId, "Projection");
	MatModelUniform = glGetUniformLocation(programId, "Model");
}

void drawScene(void)
{
	if (gameOver && hasRestarted) setupGame(); // caso in cui devo riavviare il gioco

	glUseProgram(programId);
	glClearColor(0.0,0.0,0.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
 
	cielo.drawMesh(MatModelUniform);	
	terra.drawMesh(MatModelUniform);

	playerBall.drawMesh(MatModelUniform);

	for (Platform* plat : platforms){
		plat->drawMesh(MatModelUniform);
	}

	// testo dei punti
	if (!gameOver)
	{
		sprintf(points_string, "%d m", heightValue);
		gltSetText(points_display, points_string);
		gltBeginDraw();
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(textScore, 10, 10, 1.0);
		gltColor(1.0f, 1.0f, 0.0f, 1.0f);
		gltDrawText2D(points_display, 10, 25, 1.0);
		gltEndDraw();
	} else {
		gltSetText(textScore, "Game Over!");
		sprintf(points_string, "You have reached %d m!", heightValue);
		gltSetText(points_display, points_string);
		gltBeginDraw();
		gltColor(1.0f, 0.0f, 0.0f, 1.0f);
		gltDrawText2DAligned(textScore, float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) / 2 - 70, 5.0, GLT_CENTER, GLT_CENTER);
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2DAligned(points_display, float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) / 2, 4.0, GLT_CENTER, GLT_CENTER);
		gltColor(0.0f, 1.0f, 0.0f, 1.0f);
		gltDrawText2DAligned(restartText, float(SCREEN_WIDTH) - 10, 10, 1.0, GLT_RIGHT, GLT_TOP);
		gltEndDraw();
	}

	// swap dei due framebuffer
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	srand (time(NULL));
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DoodleJumpGL");
	glutDisplayFunc(drawScene);

	// keyboard events
	glutKeyboardFunc(keyboardPressedEvent);
	glutKeyboardUpFunc(keyboardReleasedEvent);

	//gestione animazione
	glutTimerFunc(66, update, 0);

	glewExperimental = GL_TRUE;
	glewInit();
	
	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		exit(0);
		return EXIT_FAILURE;
	}
	
	textScore = gltCreateText();
	points_display = gltCreateText();
	restartText = gltCreateText();
	gltSetText(restartText, "Press r to restart");

	INIT_SHADER();
	INIT_VAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
	gltDeleteText(textScore);
	gltDeleteText(restartText);
	gltDeleteText(points_display);
	gltTerminate();
}


