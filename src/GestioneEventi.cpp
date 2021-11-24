#include "../include/GestioneEventi.h"
#include "../include/Platform.h"
#include <iostream>
#include "../include/Ground.h"
#include "../include/Player.h"

extern double speedX;
extern int heightValue;
extern double speedY; //velocita verticale (pixel per frame)
extern double delta;
extern double accelerazione ; // forza di accelerazione data dalla tastiera
extern double decelerazione; //decelerazione in assenza di input
extern Ground terra;
extern Player playerBall;
extern vector<Platform*> platforms;
extern bool gameOver;
extern bool hasRestarted;

bool stalledInAir = false;
bool pressing_left, pressing_right;

void keyboardPressedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		pressing_left = true;
		break;

	case 'd':
		pressing_right = true;
		break;
	case 'r':
		if (gameOver) hasRestarted = true;
		break;
	
	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void keyboardReleasedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		pressing_left = false;
		break;

	case 'd':
		pressing_right = false;
		break;

	default:
		break;
	}
}

void update(int a)
{
	bool moving = false;
	//Movimento della palla in orizzontale

	if (pressing_left) speedX -= accelerazione;
	if (pressing_right) speedX += accelerazione;

	moving = pressing_left || pressing_right;

	if (!moving) {   //Se non mi sto muovendo con i tasti a e d decremento od incremento la velocita' iniziale fino a portarla
					 // a zero e la palla continua a rimbalzare sul posto
		if (speedX > 0)
		{
			speedX -= 1;
			if (speedX < 0)
				speedX = 0;
		}

		if (speedX < 0)
		{
			speedX += 1;
			if (speedX > 0)
				speedX = 0;
		}
	}

	//Aggioramento della posizione in x della pallina, che regola il movimento orizzontale

	playerBall.position.x += speedX;

	//Se la pallina assume una posizione in x minore di 0 o maggiore di SCREEN_WIDTH dello schermo
	//facciamo rimbalzare la pallina ai bordi dello schermo

	if (playerBall.position.x < 0) {
		playerBall.position.x = 0;
		speedX = -speedX * 0.8;
	}

	if (playerBall.position.x > SCREEN_WIDTH) {
		playerBall.position.x = SCREEN_WIDTH;
		speedX = -speedX * 0.8;
	}

	// Gestione del rimbalzo e quindi dell'altezza da terra

	//Rimbalzo
	speedY -= delta;	

	// se doodle raggiunge la massima altezza su schermo, per permettere lo spostamento fermo doodle
	// altrimenti, può andare avanti come sempre
	if (!stalledInAir) playerBall.distacco_da_terra -= speedY;
			
	processCollisions();
	
	if (playerBall.topLeftCorner.y >= (SCREEN_HEIGHT*5/6) && speedY > 0){
		stalledInAir = true;
		for (Platform* plat : platforms){	
			plat->position.y += -speedY;
		}
		terra.position.y += -speedY;

		heightValue += speedY;

	} else stalledInAir = false;

	Platform* plat = platforms.front();
	if (plat->position.y <= -10){
		plat->position.y = (platforms.back())->position.y + 100;
		int randWidth = rand() % 7;
		plat->position.x = float(SCREEN_WIDTH) * (0.15 + (float) randWidth/10);
		platforms.erase(platforms.begin());
		platforms.push_back(plat);
	}

	// se cade troppo giù, allora è gameover
	gameOver = (playerBall.topLeftCorner.y < -20);

	glutPostRedisplay();
	glutTimerFunc(24, update, 0);
}


void processCollisions(){
	// qui devo fare in modo che non ci siano collisioni con piattaforme quando la velocità.y di doodle è > 0
	// le collisioni con oggetti ed eventuali nemici invece ci devono essere SEMPRE

	for (Platform* plat : platforms){	
		if(checkCollision((Collider) playerBall, (Collider) *plat)){
			if (speedY < 0) speedY = 30;   // doodle qui salta yee
		}
		plat->movePlatform();
	}

	// controllo se la terra non sia troppo in basso, per evitari calcoli inutili in caso sia troppo lontana...
	if (terra.position.y >= -40 && checkCollision((Collider) playerBall, (Collider) terra)){
		if (speedY < 0) speedY = 30;
	}
}


bool checkCollision(Collider obj1, Collider obj2){
	// guardo collisioni su asse x
	bool collisionX = obj1.bottomRightCorner.x >= obj2.topLeftCorner.x &&
		obj1.topLeftCorner.x <= obj2.bottomRightCorner.x;

	// guardo collisioni su asse y
	bool collisionY = obj1.bottomRightCorner.y <= obj2.topLeftCorner.y &&
		obj1.topLeftCorner.y >= obj2.bottomRightCorner.y;

	return collisionX && collisionY;
}