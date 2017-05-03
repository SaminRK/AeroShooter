#include "iGraphics.h"
#include <iostream>
#include <cstdio>
using namespace std;

#define MAGAZINE 10
#define ENEMY 4

void showBullet(void);

void showEnemy(void);

void kill(void);


int screenX = 500;
int screenY = 500;

int b;

struct fighter{

    int initialX = screenX / 2;
    int initialY = 0;
    float x = initialX;
    float y = initialY;
    int width = 30;
    int length = 60;
    float velocity = 5;
    int life;

};

fighter fighter1;

struct enemyFighter{

    int initialX;
    int initialY = 200;
    float x = initialX;
    float y = initialY;
    int width = 30;
    int length = 60;
    float velocity = 0.00 ;
    int existance = 1;
};

enemyFighter enemyFighter[ENEMY];



struct bullet{

    float x;
    float y;
    float velocity = 0.5;
    int killingPower = 0;


};

bullet bullet[MAGAZINE];
/*
function iDraw() is called again and again by the system.
*/
void iDraw(){
    //place your drawing codes here
    iClear();
    iSetColor(255, 255, 255);
    iFilledRectangle(fighter1.x - fighter1.width/2, fighter1.y, fighter1.width, fighter1.length);

    showBullet();
    showEnemy();
    kill();
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
        bullet[b].y = fighter1.y;
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
            if (bullet[i].x >= enemyFighter[j].x - enemyFighter[j].width / 2 && bullet[i].x <= enemyFighter[j].x + enemyFighter[j]. width / 2 && bullet[i].y >= enemyFighter[j].y && bullet[i].y <= enemyFighter[j].y){
                enemyFighter[j].existance = 0;
                bullet[i].killingPower = 0;
                enemyFighter[j].x = -200;
            }
        }
    }

}

int main(){
    //place your own initialization codes here.
    enemyFighter[0].x = 200;
    enemyFighter[1].x = 100;
    enemyFighter[2].x = 20;
    enemyFighter[3].x = 150;
    b = 0;
    fighter1.life = 3;
    iInitialize(screenX, screenY, "demooo");



    return 0;
}
