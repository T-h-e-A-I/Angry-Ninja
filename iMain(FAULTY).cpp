#include "iGraphics.h"

int cut = 0;
int score=0;
double x = 100, y = 200, r = 15;
double vx = 0, vy = 0, g = 0;
double p,q;
double dt = 0.005;
int state = 0;
const int N = 50;
char bg[1][20]={"bg\\Background.bmp"};
int bgindex = 0;
char healthbar[7][100] = {"healthbar\\healthbar1.bmp","healthbar\\healthbar2.bmp","healthbar//healthbar3.bmp",
"healthbar\\healthbar4.bmp","healthbar\\healthbar5.bmp","healthbar\\healthbar6.bmp"};
int healthindex = 0;

struct object {
    int outside = 1;
    double x=135,y=60;
    bool thro = false;
    double vx=0,vy=0;
    double ax,ay;
    int type = 0;
    int r=255,g=255,b=255;
    int R = 50;
    int cut = 0;
    char s[40][40]={"fruit//rottenbanana1.bmp","fruit//rottenpear1.bmp",
    "fruit//rottenorange1.bmp","fruit//rottenapple1.bmp",
    "fruit//apple1.bmp","fruit//orange1.bmp",
    "fruit//pear1.bmp","fruit//melon1.bmp","fruit//banana1.bmp",
    "fruit//lemon1.bmp","fruit//Berry1.bmp","fruit//rottenbanana2.bmp","fruit//rottenpear2.bmp",
    "fruit//rottenorange2.bmp","fruit//rottenapple2.bmp",
    "fruit//apple2.bmp","fruit//orange2.bmp",
    "fruit//pear2.bmp","fruit//melon2.bmp","fruit//banana2.bmp",
    "fruit//lemon2.bmp","fruit//Berry2.bmp","shuriken1.bmp",
    "shuriken2.bmp","shuriken3.bmp"};
    int fruitno=23;
    void update() {
        x += vx * dt;
        y += vy * dt;
        vx += ax * dt;
        vy += ay * dt;
    }

    void draw() {
        iSetColor(r,g,b);
        if(type == 0) {
            //iFilledCircle(x,y,R);
        }
        if(fruitno < 22)
            iShowBMP2(x,y,s[fruitno],255);
        else
            iShowBMP2(x,y,s[fruitno],0);
    }
};

object obj[N];
object projectile;
struct ninja{
    char ninja[5][20] = {"ninja//0.bmp","ninja//01.bmp","ninja//1.bmp","ninja//2.bmp","ninja//3.bmp"};
    int x = 0;
    int y = 0;
    int i=0;
    void draw(){
            iShowBMP2(x,y,ninja[i],255);
    }
};
void reset_projectile() {
    projectile.x=135;
    projectile.y=60;
    projectile.vy=0;
    projectile.vx=0;
    projectile.ay=0;
    projectile.fruitno = 22+rand()%3;
}
void generate_objects() {
    srand(time(NULL));
    for(int i=0;i<N;i++) {
        obj[i].x = 300 + rand() % 700;
        obj[i].y = 500;
        obj[i].R = 15;
        obj[i].r = rand()%255;
        obj[i].g = rand()%255;
        obj[i].b = rand()%255;
        obj[i].vy = -rand()%500;
        obj[i].fruitno = rand()%11;
    }
}
double distance(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}
struct ninja ninja1;
void change(){
    if(projectile.thro == true){
            ninja1.i++;
            if(ninja1.i == 5){
                ninja1.i = 0;
                projectile.thro = false;
            }
    }
}

void iDraw()
{
    if(state == 0){
        iClear();
        iShowBMP(0,0,"bg1.bmp");
        iShowBMP2(670,30,"Titleash.bmp",0);
    }
    if(state == 1){
        iClear();


        for(int i=0;i<N;i++) {
            double d = distance(obj[i].x, obj[i].y, projectile.x, projectile.y);
            if(obj[i].cut == 0 && (d < obj[i].R + projectile.R)) {
                obj[i].fruitno += 11;
                obj[i].cut = 1;
                if(obj[i].fruitno >= 11 && obj[i].fruitno <= 14){
                    score -= 5;
                    healthindex++;
                }
                else
                    score += 10;

            }
        }

        projectile.update();
        if(projectile.x > 1000 or projectile.y < 0 or projectile.y > 500){
                projectile.outside = 1;
                reset_projectile();
        }
        for(int i=0;i<N;i++) obj[i].update();
        iClear();

        char s2[20] = "SCORE : ";
        char s[20];
        itoa(score,s,10);
        strcat(s2,s);

        //iShowBMP(0,0,"bg1.bmp");
        iShowBMP(0,0,"Background.bmp");
        iShowBMP(10,430,healthbar[healthindex]);
        iText(50,450,s2,GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0;i<N;i++) obj[i].draw();
        ninja1.draw();
        projectile.draw();
    }
    /*if(state == 3){
            char s2[20] = "YOUR FINAL SCORE : ";
            char s[20];
            itoa(score,s,10);
            strcat(s2,s);
            iShowBMP(0,0,"Background.bmp");
            iText(50,450,s2,GLUT_BITMAP_TIMES_ROMAN_24);
    }*/
}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(projectile.outside==1){
            projectile.thro = true;
            projectile.outside = 0;
            projectile.vy += 6*(my - projectile.y);
            projectile.vx += 6*(mx - projectile.x);
            projectile.ay = -2000;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(state == 0){
        if(key == 's'){
            state = 1;
        }
    }
    if(key == 'q')
    {
        exit(0);
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}


int main()
{
    generate_objects();
    iSetTimer(75,change);
    //place your own initialization codes here.
    iInitialize(1000, 500, "Angry Ninja");
    return 0;
}
