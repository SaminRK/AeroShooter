#include "iGraphics.h"
#include <iostream>
#include <cstdio>
using namespace std;

#define MAGAZINE 10
#define ENEMY 20

void showBullet(void);
void showEnemy(void);
void kill(void);
void createEnemy(void);
void collision(void);
void restart(void);


int screenX = 500;
int screenY = 500;

int scoreX = screenX - 100;
int scoreY = screenY - 50;
char str[100];
char strtemp[50];

int b, enemySerial, score;

struct fighter{

    int initialX = screenX / 2;
    int initialY = 0;
    float x = initialX;
    float y = initialY;
    int width = 79;
    int length = 60;
    float velocity = 5;
    int life;
    int bmpx = initialX - 45;

};

fighter fighter1;

struct enemyFighter{

    int initialX;
    int initialY = screenY - 100;
    float x = initialX;
    float y = initialY;
    int width = 30;
    int length = 60;
    float velocity = 01 ;
    int existance = 0;
};

enemyFighter enemyFighter[ENEMY];



struct bullet{

    float x;
    float y;
    float velocity = 5;
    int killingPower = 0;


};

bullet bullet[MAGAZINE];
/*
function iDraw() is called again and again by the system.
*/
void iDraw(){
    //place your drawing codes here
    iClear();

    fighter1.bmpx = fighter1.x - 39;

    iSetColor(20, 49, 96);
    iFilledRectangle(0, 0, screenX, screenY);
    iSetColor(255, 255, 255);
    iFilledRectangle(fighter1.x - fighter1.width/2, fighter1.y, fighter1.width, fighter1.length);
    iShowBMP2(fighter1.bmpx , fighter1.y, "bmp\\basic player.bmp", 0);
    iText(scoreX, scoreY, itoa(score, str, 10), GLUT_BITMAP_9_BY_15);
    iText(scoreX - 75, scoreY, "Score :", GLUT_BITMAP_9_BY_15);
    iText(scoreX - 75, scoreY - 50 , "Life :", GLUT_BITMAP_9_BY_15);
    iText(scoreX, scoreY - 50, itoa(fighter1.life, strtemp, 10), GLUT_BITMAP_9_BY_15);

    showBullet();
    showEnemy();
    kill();
    collision();
    restart();

}
/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my){
    //place your codes here
}
/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //place your codes here
        bullet[b].killingPower = 1;
        bullet[b].x = fighter1.x;
        bullet[b].y = fighter1.y + fighter1.length;
        b++;
        if(b >= MAGAZINE){
            b = 0;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    //place your codes here
    }
}
/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key){
    if(key == 'q'){
        //do something with 'q'
    }
    if(key == 'x'){
        if (fighter1.x + fighter1.width / 2 <= screenX) (fighter1.x)+= (fighter1.velocity);
    }
    if(key == 'z'){
        if (fighter1.x - fighter1.width / 2>= 0) (fighter1.x)-= (fighter1.velocity);
    }
    if(key == 'f'){
        bullet[b].killingPower = 1;
        bullet[b].x = fighter1.x;
        bullet[b].y = fighter1.y + fighter1.length;
        b++;
        if(b >= MAGAZINE){
            b = 0;
        }
    }
//place your codes for other keys here
}
/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key){
    if(key == GLUT_KEY_END){
        exit(0);
    }
    if(key == GLUT_KEY_RIGHT){
        if (fighter1.x + fighter1.width / 2 <= screenX) (fighter1.x)+= (fighter1.velocity);
    }
    if(key == GLUT_KEY_LEFT){
        if (fighter1.x - fighter1.width / 2>= 0) (fighter1.x)-= (fighter1.velocity);
    }
    if(key == GLUT_KEY_UP){
        if (fighter1.y - fighter1.length / 2<= screenY) (fighter1.y)+= (fighter1.velocity);
    }
    if(key == GLUT_KEY_DOWN){
        if (fighter1.y + fighter1.length / 2>= 0) (fighter1.y)-= (fighter1.velocity);
    }
//place your codes for other keys here
}

void showBullet(void){

    int i;

    for (i = 0; i < MAGAZINE; i++){
        if (bullet[i].killingPower){
            iFilledCircle(bullet[i].x, bullet[i].y, 5, 100);
            bullet[i].y += bullet[i].velocity;
        }
    }
}

void showEnemy(void){

    int i;
    iSetColor(200, 200, 200);
    for (i = 0; i < ENEMY; i++){
        if (enemyFighter[i].existance){
            iFilledRectangle(enemyFighter[i].x - enemyFighter[i].width/2, enemyFighter[i].y, enemyFighter[i].width, enemyFighter[i].length);
            enemyFighter[i].y -= enemyFighter[i].velocity;
        }
    }
    iSetColor(255, 255, 255);
}

void kill(void){

    int i, j;
    for (i = 0 ; i < MAGAZINE; i++){
        for (j = 0; j < ENEMY; j++){
            if (bullet[i].x >= enemyFighter[j].x - enemyFighter[j].width / 2 && bullet[i].x <= enemyFighter[j].x + enemyFighter[j]. width / 2 && bullet[i].y >= enemyFighter[j].y && bullet[i].y <= enemyFighter[j].y + enemyFighter[j].length && bullet[i].killingPower){
                enemyFighter[j].existance = 0;
                bullet[i].killingPower = 0;
                enemyFighter[j].x = -200;
                cout << "score: "<<++score << endl;
            }
        }
    }
}

void createEnemy(void){

    enemyFighter[enemySerial].existance = 1;
    enemyFighter[enemySerial].x = rand() % screenX;
    enemyFighter[enemySerial].y = enemyFighter[enemySerial].initialY + 200;
    enemySerial++;
    if (enemySerial >= ENEMY) enemySerial = 0;
}

void collision(void){

    int i;

    for (i = 0; i < ENEMY; i++){
        if (((fighter1.x - enemyFighter[i].x) <= fighter1.width) && ((enemyFighter[i].x - fighter1.x) <= fighter1.width)  && ((enemyFighter[i].y - fighter1.y) <=fighter1.length) && (( fighter1.y - enemyFighter[i].y) <=fighter1.length) && enemyFighter[i].existance == 1){
            enemyFighter[i].existance = 0;
            fighter1.life--;
            enemyFighter[i].x = -200;
            cout << "life: " << fighter1.life;
        }
    }
}

void restart(void){

    if (fighter1.life <= 0){
        fighter1.x = fighter1.initialX;
        fighter1.y = fighter1.initialY;
        fighter1.life = 3;
        score = 0;
    }

}

int main(){
    //place your own initialization codes here.
    //enemyFighter[0].x = 200;
    //enemyFighter[1].x = 100;
    //enemyFighter[2].x = 20;
    //enemyFighter[3].x = 150;
    score = 0;
    enemySerial = 0;
    b = 0;

    fighter1.life = 3;
    iSetTimer(5000, createEnemy);



    iInitialize(screenX, screenY, "demooo");


    return 0;
}
