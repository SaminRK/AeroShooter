#include "iGraphics.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAGAZINE 10
#define ENEMYBULLET 50
#define ENEMY 20
#define CLOUD 10


////////gameplay functions/////////
void showBullet(void);
void showEnemy(void);
void kill(void);
void createEnemy(void);
void collision(void);
void restart(void);
void myplaneshape(int x, int y, int w, int l);
void enemyplaneshape(int x, int y, int w, int l);
void fdelay(void);
void enemyshoot(void);
void enemybulletaction(void);
void cloudcreate(void);
void showCloud(void);
void indexPage(void);

//common variables//
int screenX = 500;
int screenY = 500;

////index page variables////

int titleX = screenX / 2;
int titleY = screenY / 2;
int enterX = titleX;
int enterY = titleY - 100;
int enterLength = 100;
int enterBreadth = 50;

int mouselocation = 0;

////gameplay variables/////
int delay, page;

int magazine = MAGAZINE;

int scoreX = screenX - 100;
int scoreY = screenY - 50;
char str[100];
char strtemp[50];

int b, eb, enemySerial, enemyfireserial, score, cloudserial;

struct fighter{

    int initialX = screenX / 2;
    int initialY = 0;
    float x = initialX;
    float y = initialY;
    int width = 80;
    int length = 60;
    float velocity = 5;
    int life;
    //int bmpx = initialX - 45;

};

fighter fighter1;

struct enemyFighter{

    int initialX;
    int initialY = screenY - 100;
    float x = initialX;
    float y = initialY;
    int width = 80;
    int length = 60;
    float velocity = .02 ;
    int existance = 0;
    int shootingpower = 0;
};

enemyFighter enemyFighter[ENEMY];



struct bullet{

    float x;
    float y;
    float velocity = 0.2;
    int killingPower = 0;


};

struct bullet bullet[MAGAZINE];
struct bullet enemybullet[ENEMYBULLET];

struct cloud{

    float x;
    float y;
    int radius;
    int existance;
    float velocity = 0.01;
};

struct cloud cloud[CLOUD];
/*
function iDraw() is called again and again by the system.
*/
void iDraw(){
    //place your drawing codes here
    iClear();

    //fighter1.bmpx = fighter1.x - 39;
    if (page == 1){
        iSetColor(20, 49, 96);
        iFilledRectangle(0, 0, screenX, screenY);
        showCloud();
        iSetColor(255, 255, 255);
        myplaneshape(fighter1.x, fighter1.y, fighter1.width, fighter1.length);
        //iShowBMP2(fighter1.bmpx , fighter1.y, "bmp\\basic player.bmp", 0);
        iSetColor(0, 255, 0);
        iText(scoreX, scoreY, itoa(score, str, 10), GLUT_BITMAP_9_BY_15);
        iText(scoreX - 75, scoreY, "Score :", GLUT_BITMAP_9_BY_15);
        iText(scoreX - 75, scoreY - 50 , "Life :", GLUT_BITMAP_9_BY_15);
        iText(scoreX, scoreY - 50, itoa(fighter1.life, strtemp, 10), GLUT_BITMAP_9_BY_15);
        iSetColor(255, 255, 255);
        showBullet();
        showEnemy();
        kill();
        collision();
        restart();
        enemybulletaction();
    }
    else if(page == 0){
        indexPage();
    }

}
/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my){
    //place your codes here
    if(page == 0 && mx >= enterX && mx <= enterX + enterLength && my >= enterY && my <= enterY + enterBreadth){
        mouselocation = 1;
    }
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
        if(b >= magazine){
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
        if(delay == 0){
            delay = 1;
            bullet[b].killingPower = 1;
            bullet[b].x = fighter1.x;
            bullet[b].y = fighter1.y + fighter1.length;
            b++;
            if(b >= magazine){
                b = 0;
            }
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

    iSetColor(0, 0, 255);
    for (i = 0; i < magazine; i++){
        if (bullet[i].killingPower){
            iFilledCircle(bullet[i].x, bullet[i].y, 5, 100);
            bullet[i].y += bullet[i].velocity;
        }
    }
    iSetColor(255, 255, 255);
}

void showEnemy(void){

    int i;
    //iSetColor(200, 200, 200);
    for (i = 0; i < ENEMY; i++){
        if (enemyFighter[i].existance){
            //iShowBMP2(enemyFighter[i].x , enemyFighter[i].y, "bmp\\basic enemy.bmp", 0);
            //iFilledRectangle(enemyFighter[i].x - enemyFighter[i].width/2, enemyFighter[i].y, enemyFighter[i].width, enemyFighter[i].length);
            enemyplaneshape(enemyFighter[i].x, enemyFighter[i].y, enemyFighter[i].width, enemyFighter[i].length);
            enemyFighter[i].y -= enemyFighter[i].velocity;
        }
    }
    iSetColor(255, 255, 255);
}

void kill(void){

    int i, j;
    for (i = 0 ; i < magazine; i++){
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
    enemyFighter[enemySerial].x = (rand() % (screenX - 80)) + 40;
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

void myplaneshape(int x, int y, int w, int l){
    double xa[] = {x - w/2, x, x + w/2};
    double ya[] = {y + 5, y + l, y + 5};
    int body = 20;
    int ellipsemin = 7.5;
    int ellipsemax = 15;

    //iFilledRectangle(x - w/2, y, w, l);
    iSetColor(255, 0, 0);
    iFilledPolygon(xa, ya, 3);
    iSetColor(255, 100, 0);
    iFilledRectangle(x - body/2, y , body, l + 20 );
    iFilledEllipse(x, y + l + 20, 10, 20);
    iSetColor(0, 0, 255);
    iFilledEllipse(x, y + l + 10, ellipsemin, ellipsemax);
    iSetColor(255, 255, 255);
}

void enemyplaneshape(int x, int y, int w, int l){
    double xa[] = {x - w/2, x, x + w/2};
    double ya[] = {y + l - 5 , y, y + l - 5};
    int body = 20;
    int ellipsemin = 7.5;
    int ellipsemax = 15;


    //iFilledRectangle(x - w/2, y, w, l);
    iSetColor(255, 0, 0);
    iFilledPolygon(xa, ya, 3);
    iSetColor(255, 255, 255);
    iSetColor(255, 100, 0);
    iFilledRectangle(x - body/2, y - 20 , body, l + 20 );
    iFilledEllipse(x, y - 20, 10, 20);
    iSetColor(0, 0, 255);
    iFilledEllipse(x, y - 10, ellipsemin, ellipsemax);
    iSetColor(255, 255, 255);
}

void fdelay(void){

    if (delay) delay = 0;

}

void enemyshoot(void){


    if (enemyFighter[enemyfireserial].existance){
        enemybullet[eb].killingPower = 1;
        enemybullet[eb].x = enemyFighter[enemyfireserial].x;
        enemybullet[eb].y = enemyFighter[enemyfireserial].y - enemyFighter[enemyfireserial].length;
        eb++;
    }
    if(eb >=ENEMYBULLET){
        eb = 0;
    }
    if(enemyfireserial >= ENEMY){
        enemyfireserial = 0;
    }
    enemyfireserial++;
}

void enemybulletaction(void){

    int i, k;
    iSetColor(255, 0, 0);
    for (k = 0; k < ENEMYBULLET; k++){
        if (enemybullet[k].killingPower){
            iFilledCircle(enemybullet[k].x, enemybullet[k].y, 5, 100);
            enemybullet[k].y -= enemybullet[k].velocity;
        }
    }
    for (i = 0 ; i < ENEMYBULLET; i++){
        if (enemybullet[i].x >=  fighter1.x - fighter1.width / 2 && enemybullet[i].x <= fighter1.x + fighter1.width / 2 && enemybullet[i].y >= fighter1.y && enemybullet[i].y <= fighter1.y + fighter1.length && enemybullet[i].killingPower){
            fighter1.life--;
            enemybullet[i].killingPower = 0;
        }
    }
    iSetColor(255, 255, 255);
}

void cloudcreate(void){

    cloud[cloudserial].existance = 1;
    cloud[cloudserial].radius = rand() % 200 + 100;
    cloud[cloudserial].x = rand() % screenX;
    cloud[cloudserial].y = screenY + 200;
    cloudserial++;
    if (cloudserial >= CLOUD) cloudserial = 0;
}

void showCloud(){

    int i;
    //iSetColor(200, 200, 200);
    iSetColor(255, 255, 255);
    for (i = 0; i < CLOUD; i++){
        if (cloud[i].existance){
            iFilledCircle(cloud[i].x, cloud[i].y, cloud[i].radius, 100);
            cloud[i].y -= cloud[i].velocity;
            //enemyplaneshape(enemyFighter[i].x, enemyFighter[i].y, enemyFighter[i].width, enemyFighter[i].length);
            //enemyFighter[i].y -= enemyFighter[i].velocity;
        }
    }
    iSetColor(255, 255, 255);
}

void indexPage(void){
    iSetColor(255, 255, 255);
    iText(titleX, titleY, "AIR FIGHTER", GLUT_BITMAP_TIMES_ROMAN_24);
    if(mouselocation == 0){
        iRectangle(enterX, enterY, enterLength, enterBreadth);
    }
    if(mouselocation == 1){
        iFilledRectangle(enterX, enterY, enterLength, enterBreadth);
    }
}

int main(){
    //place your own initialization codes here.
    //enemyFighter[0].x = 200;
    //enemyFighter[1].x = 100;
    //enemyFighter[2].x = 20;
    //enemyFighter[3].x = 150;
    page = 0;
    score = 0;
    enemySerial = 0;
    enemyfireserial = 0;
    cloudserial = 0;
    b = 0;
    eb = 0;
    delay = 0;
    fighter1.life = 3;
    if(page == 1){
        iSetTimer(7000, createEnemy);
        iSetTimer(1000, fdelay);
        iSetTimer(1000, enemyshoot);
        iSetTimer(20000, cloudcreate);
    }


    iInitialize(screenX, screenY, "SS - fighter");


    return 0;
}
