#include "iGraphics.h"
#include<time.h>

//moushover
POINT cursor;
RECT rect;
HWND hwnd;
TCHAR title[500];
int mh;
double mousehoverx;
double mousehovery;

//button
int toggle_button = 0;
int toggle_sound = 0;
int toggle_basket = 0;
int toggle_pause = 0;
char button[6][50] = {"button//fruitbasket0.bmp","button//fruitbasket1.bmp"
,"button//soundon.bmp","button//soundoff.bmp",
"button//pause.bmp","button//play.bmp"
};

int musicon = 1;

int cut = 0;
int healthbary = 0;
int score=0;
double x = 100, y = 200, r = 15;
double vx = 0, vy = 0, g = 0;
double p,q;
double dt = 0.005;
int state = 0;
const int N = 20;
char bg[1][20]={"bg\\Background.bmp"};
int bgindex = 0;
char healthbar[7][100] = {"healthbar\\healthbar1.bmp","healthbar\\healthbar2.bmp","healthbar//healthbar3.bmp",
"healthbar\\healthbar4.bmp","healthbar\\healthbar5.bmp","healthbar\\healthbar6.bmp"};
int healthindex = 0;


struct object {
    int outside = 1;
    double x=40,y=40;
    bool thro = false;
    double vx=0,vy=0;
    double ax,ay;
    int type = 0;
    int r=255,g=255,b=255;
    int R = 50;
    int cut = 0;
    double x1,x2,x3,y1,y2,y3;
    double vx2,vx3,vx1,vy2,vy3,vy1;
    char s[40][40]={"fruit//rottenbanana1.bmp","fruit//rottenpear1.bmp",
    "fruit//rottenorange1.bmp","fruit//rottenapple1.bmp",
    "fruit//apple1.bmp","fruit//orange1.bmp",
    "fruit//pear1.bmp","fruit//melon1.bmp","fruit//banana1.bmp",
    "fruit//lemon1.bmp","fruit//Berry1.bmp","fruit//rottenbanana2.bmp","fruit//rottenpear2.bmp",
    "fruit//rottenorange2.bmp","fruit//rottenapple2.bmp",
    "fruit//apple2.bmp","fruit//orange2.bmp",
    "fruit//pear2.bmp","fruit//melon2.bmp","fruit//banana2.bmp",
    "fruit//lemon2.bmp","fruit//Berry2.bmp","shuriken1.bmp",
    "shuriken2.bmp","shuriken3.bmp","gift//heart1 (3).bmp","gift//heart2 (3).bmp",
"gift//heart3 (3).bmp","gift//heart4 (3).bmp","gift//heart5 (3).bmp",
"gift//heart6 (3).bmp"};
    char shuriken[8][40] ={"shuriken//1.bmp","shuriken//2.bmp",
    "shuriken//3.bmp","shuriken//4.bmp","shuriken//5.bmp","shuriken//6.bmp",
    "shuriken//7.bmp"};
    char shuriken2[7][40] ={"shuriken2//0.bmp","shuriken2//1.bmp","shuriken2//2.bmp",
    "shuriken2//3.bmp","shuriken2//4.bmp","shuriken2//5.bmp"};
    int fruitno=23;
    void update() {
        x += vx * dt;
        y += vy * dt;
        vx += ax * dt;
        vy += ay * dt;
        x1 += vx1 * dt;
        y1 += vy1 * dt;
        vx1 += ax * dt;
        vy1 += ay * dt;
        x2 += vx2 * dt;
        y2 += vy2 * dt;
        vx2 += ax * dt;
        vy2 += ay * dt;
        x3 += vx3 * dt;
        y3 += vy3 * dt;
        vx3 += ax * dt;
        vy3 += ay * dt;
    }
    int dt3 = 0.05;
    void draw() {
        iSetColor(r,g,b);
        if(type == 0) {
            //iFilledCircle(x,y,R);
        }
        if(fruitno < 11)
            iShowBMP2(x,y,s[fruitno],255);
        if(fruitno < 22 && fruitno > 11){
            iShowBMP2(x+10,y,s[fruitno],255);
            x1 = x1 + vx1*dt3+.5*ax*dt3*dt3;
            y1 = y1 +vy1*dt3+.5*ay*dt3*dt3;
            iShowBMP2(x1,y1,s[fruitno],255);
            x2 = x2 + vx2*dt3+.5*ax*dt3*dt3;
            y2 = y2 +vy2*dt3+.5*ay*dt3*dt3;
            iShowBMP2(x2,y2,s[fruitno],255);
            x3 = x3 + vx3*dt3+.5*ax*dt3*dt3;
            y3 = y3 +vy3*dt3+.5*ay*dt3*dt3;
            iShowBMP2(x3,y3,s[fruitno],255);
            dt3 += 0.05;
        }
        if(fruitno ==  22 || fruitno == 23 || fruitno == 24 || fruitno == 25)
            iShowBMP2(x,y,s[fruitno],0);
            //if(fruitno == 25) printf("in draw");
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
int projturn = 0;
int projthrow = 0;
int projno;
void projectile_draw(){
        if(projno == 1){
            if(projthrow == 0)
                iShowBMP2(projectile.x,projectile.y,projectile.shuriken[0],0);
            else
                iShowBMP2(projectile.x,projectile.y,projectile.shuriken[projturn],0);
            if(toggle_pause == 0){
                projturn++;
            }
            if(projturn == 7)
                projturn = 0;
        }
        if(projno == 0){
            if(projthrow == 0)
                iShowBMP2(projectile.x,projectile.y,projectile.shuriken2[0],0);
            else
                iShowBMP2(projectile.x,projectile.y,projectile.shuriken2[projturn],0);
            if(toggle_pause == 0){
                projturn++;
            }
            if(projturn == 5)
                    projturn = 0;

        }
}

void reset_projectile() {
    srand(time(NULL));
    projno = rand()%2;
    projturn = 0;
    projectile.x=40;
    projectile.y=40;
    projectile.vy=0;
    projectile.vx=0;
    projectile.ay=0;
    projectile.fruitno = 22+rand()%3;
}
int maximum = -501;
int minvelo = 0;
int ayinit = -(score/100)*100;
int hearton = 0;
int heartno;
void generate_objects() {
        srand(time(NULL));
        minvelo = 0;
        maximum = -501;
        for(int i = 0;i<N;i++) {
            ayinit = -(score/100)*200;
            obj[i].cut = 0;
            obj[i].x = 5*(60 + rand() % 140);
            obj[i].y = 10*(40+ rand()%10);
            obj[i].R = 15;
            obj[i].r = rand()%255;
            obj[i].g = rand()%255;
            obj[i].b = rand()%255;
            obj[i].vy = -50-rand()%500;
            obj[i].ay += ayinit-rand()%100;
            if(obj[i].vy > maximum){
                maximum = obj[i].vy;
                minvelo = i;
            }
            int d = rand()%100;
            if(d % 20 == 0){
                obj[i].fruitno = 25;
                hearton = 1;
                heartno = i;
                //printf("in heart\n");
            }
            else
                obj[i].fruitno = d%11;


    }
}
double distance(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}
struct ninja ninja1;
void change(){
    if(projectile.thro == true && toggle_pause == 0){
            ninja1.i++;
            if(ninja1.i == 5){
                ninja1.i = 0;
                projectile.thro = false;
            }
    }
    /*if(hearton == 1){
        for(int k = 25;k < 31;k++ ){
            iShowBMP2(obj[heartno].x,obj[heartno].y,obj[heartno].s[k],0);
            if(k == 30 ) k = 25;
            if(obj[heartno].y < 0)  hearton = 0;
        }
    }*/
}

void button_draw(){
    if(toggle_basket == 0){
        iShowBMP2(40,375,button[0],255);
    }
    if(toggle_basket == 1){
        iShowBMP2(40,375,button[1],255);
    }
    if(toggle_sound == 0){
        iShowBMP2(90,375,button[2],255);
    }
    if(toggle_sound == 1){
        iShowBMP2(90,375,button[3],255);
    }
    if(toggle_pause == 0){
        iShowBMP2(140,375,button[4],255);
    }
    if(toggle_pause == 1){
        iShowBMP2(140,375,button[5],255);
    }
}
double tx  = projectile.x;
double ty = projectile.y;
int dt2 = 0;
void trajectory_draw(int vx,int vy){
    double ax,ay;
    ay = -2000;
    ax = 0;
    int i;
    iSetColor(255,255,255);
    if(!projthrow){
        for(i = 0;i < 1000;i++){
            tx += vx * dt;
            ty += vy * dt;
            vx += ax * dt;
            vy += ay * dt;
            dt2 = dt2+0.005;
            iFilledCircle(tx+30,ty+30,2);
            if(tx> 1000 || ty > 500){
                    dt2 = 0;
                    tx  = projectile.x;
                    ty = projectile.y;
                    break;
            }
        }
    }
}


void iDraw()
{
    if(state == 0){

        iClear();

        //hovercode

        for(mh = 0; mh < 10;mh++){
            GetWindowText(GetForegroundWindow(),title,500);
        }

        hwnd = FindWindow(NULL,title);
        GetWindowRect(hwnd,&rect);

        GetCursorPos(&cursor);

        mousehoverx = (cursor.x-rect.left)-8;
        mousehovery = ((rect.bottom-rect.top)+(rect.top-cursor.y))-8;
        //printf(" mouseposx : %d, mouseposy : %d\n",mousehoverx,mousehovery);
        //mousehoverend

        iShowBMP(0,0,"bg1.bmp");
        iShowBMP2(670,30,"Titleash.bmp",0);
        iSetColor(255,255,255);
        iText(10,10,"PRESS S TO START",GLUT_BITMAP_9_BY_15);
    }
    if(state == 1){

        if(obj[minvelo].y <= 0){
            minvelo = 0;
            generate_objects();
        }
        iClear();
        //hovercode

        for(mh = 0; mh < 10;mh++){
            GetWindowText(GetForegroundWindow(),title,500);
        }

        hwnd = FindWindow(NULL,title);
        GetWindowRect(hwnd,&rect);

        GetCursorPos(&cursor);

        mousehoverx = (cursor.x-rect.left)-8;
        mousehovery = ((rect.bottom-rect.top)+(rect.top-cursor.y))-8;

        if(mousehoverx > 40 && mousehoverx < 85 && mousehovery > 375 && mousehovery < 415){
            toggle_button = 1;
            toggle_basket = 1;
        }
        else if(mousehoverx > 90 && mousehoverx < 135 && mousehovery > 375 && mousehovery < 413){
            toggle_button = 1;
            /*if(toggle_sound == 1) toggle_sound = 0;
            else if(toggle_button == 0) toggle_sound = 1;
            */
        }
        else if(mousehoverx > 140 && mousehoverx < 185 && mousehovery > 375 && mousehovery < 413){
            toggle_button = 1;
            /*if(toggle_sound == 1) toggle_sound = 0;
            else if(toggle_button == 0) toggle_sound = 1;
            */
        }
        else{
            toggle_button = 0;
            toggle_basket = 0;
        }
        //printf(" mouseposx : %d, mouseposy : %d\n",mousehoverx,mousehovery);
        //mousehoverend
    for(int i=0;i<N;i++) {
            double d = distance(obj[i].x, obj[i].y, projectile.x, projectile.y);
            if(obj[i].cut == 0 && (d < obj[i].R + projectile.R)) {
                obj[i].fruitno += 11;
                obj[i].cut = 1;
                obj[i].vy1 = -150-rand()%500;
                obj[i].vy2 = -150-rand()%500;
                obj[i].vy3 = -150-rand()%500;
                obj[i].vx1 = rand()%100;
                obj[i].vx2 = -rand()%100;
                obj[i].vx3 = -rand()%100;
                obj[i].y1 = obj[i].y+10;
                obj[i].y2 = obj[i].y1;
                obj[i].y3 = obj[i].y1-10;
                obj[i].x1 = obj[i].x ;
                obj[i].x2 = obj[i].x-10;
                obj[i].x3 = obj[i].x;
                if(obj[i].fruitno >= 11 && obj[i].fruitno <= 14){
                    if(musicon){
                        PlaySound("fruitcut.wav",NULL, SND_ASYNC);
                    }
                    score -= 5;
                    healthindex++;
                }
                if(obj[i].fruitno == 36){
                    if(musicon){
                        PlaySound("bonus.wav",NULL, SND_ASYNC);
                    }
                    if(healthindex != 0 && healthindex != 1){
                        //printf("in");
                        healthindex =  healthindex - 2;
                    }
                }
                else{
                    if(musicon){
                        PlaySound("fruitcut.wav",NULL, SND_ASYNC);
                    }
                    score += 10;
                }
            }
        }
        if(!toggle_pause){
            projectile.update();
        }
        if(projectile.x > 1000 or projectile.y < 0 or projectile.y > 500){
                projectile.outside = 1;
                projthrow = 0;
                reset_projectile();
        }
        if(!toggle_pause){
            for(int i=0;i<N;i++){
                    obj[i].update();
            }
        }
        iClear();

        char s2[20] = "SCORE : ";
        char s[20];
        itoa(score,s,10);
        strcat(s2,s);

        //iShowBMP(0,0,"bg1.bmp");
        iShowBMP(0,0,"Background.bmp");
        if(healthindex < 10){
            healthbary = healthindex/2;
            iShowBMP2(10,430,healthbar[healthbary],255);
        }
        else{
                state = 3;
                if(musicon){
                    musicon = 0;
                    PlaySound("Game-over.wav",NULL, SND_ASYNC);
                    musicon = 1;
                }
        }
        iSetColor(255,255,255);
        iText(50,453,s2,GLUT_BITMAP_TIMES_ROMAN_24);
        //siText(200,10,"PRESS N FOR NEW FRUITS",GLUT_BITMAP_9_BY_15);
        for(int i=0;i<N;i++) obj[i].draw();
        if(toggle_pause == 0){
            trajectory_draw(8*(mousehoverx-40),8*(mousehovery-40));
        }
        ninja1.draw();
        button_draw();
        projectile_draw();
        //gift[0].update();
        //gift_draw();
    }
    if(state == 3){

            char s2[20] = "YOUR FINAL SCORE : ";
            char s[20];
            itoa(score,s,10);
            strcat(s2,s);

            iShowBMP(0,0,"Background.bmp");
            iShowBMP2(200,200,"gameover.bmp",0);
            iText(350,180,s2,GLUT_BITMAP_TIMES_ROMAN_24);
        }
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
        if(projectile.outside==1 && toggle_button == 0){
            if(musicon && toggle_pause == 0){
                PlaySound("throw.wav",NULL, SND_ASYNC);
            }
            projthrow = 1;
            projectile.thro = true;
            projectile.outside = 0;
            projectile.vx += 8*(mx - projectile.x);
            projectile.vy += 8*(my - projectile.y);
            //printf("%lf %lf\n",projectile.vx,projectile.vy);
            //printf("%d %d\n",8*(mousehoverx-projectile.x),8*(mousehovery));

            projectile.ay = -2000;

        }
        if(mx > 40 && mx < 85 && my > 375 && my < 415){
            if(toggle_pause == 0){
                generate_objects();
            }
        }
        if(mx > 90 && mx < 135 && my > 375 && my < 413){
            if(musicon) musicon = 0;
            else if(!musicon) musicon =1;
            if(toggle_sound == 1) toggle_sound = 0;
            else if(toggle_sound == 0) toggle_sound = 1;
        }
        if(mx > 140 && mx < 185 && my > 375 && my < 413){
            if(toggle_pause == 1) toggle_pause = 0;
            else if(toggle_pause == 0) toggle_pause = 1;
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
            if(musicon){
                    musicon = 0;
                    PlaySound("Game-start.wav",NULL, SND_ASYNC);
                    musicon = 1;
                }
        }
    }
    if(state == 1){
        if(key == 'n' || key == 'N'){
            generate_objects();
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
    iSetTimer(100,projectile_draw);
    iSetTimer(75,change);
    //place your own initialization codes here.
    iInitialize(1000, 500, "Angry Ninja");
    return 0;
}
