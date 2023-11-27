#include<windows.h>
#include <GL/glut.h>
#include<cstdio>
#include <math.h>
#include <vector>
#include <random>

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display window colour to black
	glMatrixMode(GL_PROJECTION);
    float aspect_ratio = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
		// Set projection parameters
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}
void drawFilledCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
void drawCloud(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
void displayScore();
void displayStartScreen();
void displayGameOverScreen();
void display();
void createCloud();
void sky();
int offset = 0;
int lane = 0;
int increase = 0;
int buildingOffset = 0;
int cloudt=0;
int dn=0;
int score = 0;
int state=1;
bool gameStarted = false; // Game state flag
bool gameOver = false;

float gwindowColor[3] = {187.0f/255.0f, 224.0f/255.0f, 248.0f/255.0f};
float sun[3] = {253.0f/255.0f,184.0f/255.0f,19.0f/255.0f};
float moon[3] = {246.0f/255.0f,241.0f/255.0f,213.0f/255.0f};
class Cars{
public:
    float x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,c1,c2,c3;
    int offsetx,offsety;
    Cars(float _x1,float _x2, float _x3,float _x4,float _x5,float _x6,float _y1,float _y2,float _y3,float _y4,float _offsetx,float _offsety,float _c1,float _c2,float _c3){
        x1 = _x1, x2 = _x2, x3 = _x3, x4 = _x4, x5 = _x5, x6 = _x6, y1 = _y1, y2 = _y2, y3 = _y3, y4 = _y4, offsetx = _offsetx, offsety = _offsety,c1 = _c1, c2 = _c2, c3 = _c3;
    }
    void makeCar(){
        glPushMatrix();

        glTranslatef(offsetx+offset,offsety,0);
        glColor3f(c1,c2,c3);
        glBegin(GL_POLYGON);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
        glVertex2f(x3,y2);
        glVertex2f(x4,y2);
        glVertex2f(x4,y3);
        glVertex2f(x3,y3);
        glVertex2f(x5,y4);
        glVertex2f(x6,y4);
        glEnd();

         glColor3f(224/255, 224/255, 224/255);
        glBegin(GL_POLYGON);
        glVertex2f(40*1.5,32*1.5);
        glVertex2f(37*1.5,25*1.5);
        glVertex2f(52*1.5,25*1.5);
        glVertex2f(52*1.5,32*1.5);
        glEnd();

         glColor3f(224/255, 224/255, 224/255);
        glBegin(GL_POLYGON);
        glVertex2f(61*1.5,32*1.5);
        glVertex2f(61*1.5,25*1.5);
        glVertex2f(78*1.5,25*1.5);
        glVertex2f(73*1.5,32*1.5);
        glEnd();

        glColor3f(1.0,0,0);
        drawFilledCircle(10,10,112,20);
        drawFilledCircle(10,10,53,20);
        glPopMatrix();

    }

    void makeMyCar(){
        glPushMatrix();
        glTranslatef(0.0, lane, 0.0);
        glColor3f(1.0, 1.0, 102/255);
        glBegin(GL_POLYGON);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
        glVertex2f(x3,y2);
        glVertex2f(x4,y2);
        glVertex2f(x4,y3);
        glVertex2f(x3,y3);
        glVertex2f(x5,y4);
        glVertex2f(x6,y4);
        glEnd();

         glColor3f(224/255, 224/255, 224/255);
        glBegin(GL_POLYGON);
        glVertex2f(40*1.5,32*1.5);
        glVertex2f(37*1.5,25*1.5);
        glVertex2f(52*1.5,25*1.5);
        glVertex2f(52*1.5,32*1.5);
        glEnd();

         glColor3f(224/255, 224/255, 224/255);
        glBegin(GL_POLYGON);
        glVertex2f(61*1.5,32*1.5);
        glVertex2f(61*1.5,25*1.5);
        glVertex2f(78*1.5,25*1.5);
        glVertex2f(73*1.5,32*1.5);
        glEnd();

        glColor3f(1.0,0,0);
        drawFilledCircle(10,10,112,20);
        drawFilledCircle(10,10,53,20);
        glPopMatrix();
    }
};

std:: vector<Cars> carsArray;
Cars myCar(28 * 1.5, 15 * 1.5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 0, 0,1,1,0);
int CreateCars(){
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 600, 0,0,0.5,0));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 1100, 80,0.5,0,0.8));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 1500, 80,0.5,0.7,0.8));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 1900, 0,1,0.5,0));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 2300, 80,0.3,0.5,1));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 2700, 0,1,0.5,0.4));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 3300, 80,1,0.5,0));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 3900, 0,1,0.5,0.8));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 4200, 80,1,0.0,0.8));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 4600, 0,1,0.0,0.8));
    carsArray.push_back(Cars(28 * 1.5, 15 * 1.5-5, 87 * 1.5, 101 * 1.5, 75 * 1.5, 37 * 1.5, 22 * 1.5, 13 * 1.5, 23 * 1.5, 37 * 1.5, 5950, 60,1,0.5,0.8));


}

bool checkCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2, int lane1, int lane2) {
    return (x1 < x2 + width2) &&
           (x1 + width1 > x2) &&
           (y1 + lane1-13 < y2 + height2 + lane2) &&
           (y1 + lane1 + height1 > y2 + lane2-13);
}



void callCars(){
    for (int i=0; i<carsArray.size(); i++){
        carsArray[i].makeCar();
    }	// Send graphics to display window

}



void updateRoad(int value){
    if(state==1) return;
    offset-=5;
    buildingOffset-=10;
    cloudt-=2;
    for (int i = 0; i < carsArray.size(); i++) {
        if (checkCollision(myCar.x1, myCar.y1, myCar.x4 - myCar.x1, myCar.y4 - myCar.y1,
                           carsArray[i].x1 + carsArray[i].offsetx + offset, carsArray[i].y1,
                           carsArray[i].x4 - carsArray[i].x1, carsArray[i].y4 - carsArray[i].y1,
                           lane, carsArray[i].offsety)) {
            // Collision detected, handle the collision as needed (e.g., end the game)
            // For now, we'll exit the program
            gameOver = true;
            break;
        }
    }
    std::vector<Cars>::iterator it = carsArray.begin();

    while(it!=carsArray.end()){
        Cars c = *it;
        if(c.x4+c.offsetx+offset<0){
            carsArray.erase(it);
            score++;
            break;
        }
        it++;
    }


    if(offset==-5000){
        CreateCars();						// Execute initialisation procedure
        increase+=5;
        offset = 0;
    }

       if(buildingOffset==-2180){
        buildingOffset=600;
        dn++;
        if(dn==3) dn=0;

    }

    if(cloudt==-500) cloudt=600;

    glutPostRedisplay();
    glutTimerFunc(1000/(30+increase), updateRoad, 0);
}

void road(){

    int rx1=(0+offset);
    int ry1=0;
    int rx2=5600+offset;
    int ry2 = 240;
    int ry3=65;
	//Set colour to black
	//right  side road
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(rx1,ry2);
    glVertex2f(rx1,ry1);
    glVertex2f(rx2,ry1);
    glVertex2f(rx2,ry2);
    glEnd();
	//Set colour to blue

        //divider
    glColor3f(1.0, 1.0, 1.0);

     glLineWidth(5);
     for (int i = 0; i <= 5600; i += 40) {
        glBegin(GL_LINES);
        glVertex2f(rx1 + i, ry3);
        glVertex2f(rx1 + i + 30, ry3);
        glEnd();
    }

}

void building(){
    //large building1 body 1
    float buildingLColor[13][3] = {
        {201.0f/255.0f,192.0f/255.0f,198.0f/255.0f},
        {24.0f/255.0f,164.0f/255.0f,164.0f/255.0f},
        {54.0f/255.0f,164.0f/255.0f,115.0f/255.0f},
        {201.0f/255.0f,192.0f/255.0f,198.0f/255.0f},
        {156.0f/255.0f,153.0f/255.0f,137.0f/255.0f},
        {190.0f/255.0f,186.0f/255.0f,190.0f/255.0f},
        {250.0f/255.0f,24.0f/255.0f,5.0f/255.0f},
        {54.0f/255.0f,164.0f/255.0f,115.0f/255.0f},
        {232.0f/255.0f, 166.0f/255.0f, 55.0f/255.0f},
        {212.0f/255.0f, 222.0f/255.0f, 30.0f/255.0f},
        {192.0f/255.0f, 216.0f/255.0f, 134.0f/255.0f},
        {190.0f/255.0f,186.0f/255.0f,190.0f/255.0f},
        {24.0f/255.0f,164.0f/255.0f,164.0f/255.0f},

    };

    float sideLColor[13][3] = {
        {172.0f/255.0f,168.0f/255.0f,180.0f/255.0f},
        {24.0f/255.0f, 168.0f/255.0f, 169.0f/255.0f},
        {54.0f/255.0f,164.0f/255.0f,111.0f/255.0f},
        {201.0f/255.0f,192.0f/255.0f,198.0f/255.0f},
        {156.0f/255.0f,153.0f/255.0f,137.0f/255.0f},
        {180.0f/255.0f,186.0f/255.0f,180.0f/255.0f},
        {240.0f/255.0f,24.0f/255.0f,5.0f/255.0f},
        {54.0f/255.0f,164.0f/255.0f,111.0f/255.0f},
        {222.0f/255.0f, 166.0f/255.0f, 51.0f/255.0f},
        {166.0f/255.0f, 172.0f/255.0f, 66.0f/255.0f},
        {163.0f/255.0f, 179.0f/255.0f, 123.0f/255.0f},
        {180.0f/255.0f,186.0f/255.0f,180.0f/255.0f},
        {24.0f/255.0f, 168.0f/255.0f, 169.0f/255.0f},

    };

    float tLx[13] = {0,130,290,390,520,640,790,910,1020,1160,1270,1400,1600};

        float buildingSColor[4][3] = {
        {192.0f/255.0f, 23.0f/255.0f, 132.0f/255.0f},
        {232.0f/255.0f, 166.0f/255.0f, 55.0f/255.0f},
        {212.0f/255.0f, 222.0f/255.0f, 30.0f/255.0f},
        {250.0f/255.0f,24.0f/255.0f,5.0f/255.0f}

    };

    float sideSColor[4][3] = {
        {255.0f/255.0f, 27.0f/255.0f, 77.0f/255.0f},
        {187.0f/255.0f, 135.0f/255.0f, 15.0f/255.0f},
        {166.0f/255.0f, 172.0f/255.0f, 66.0f/255.0f},
        {220.0f/255.0f,24.0f/255.0f,0.5f/255.0f}

    };

    float tSx[7] = {0,600,1300,1600};
    for(int i=0; i<13; i++){
        glPushMatrix();
        glTranslatef(tLx[i],0,0);
         //large building1 body 2
        glColor3f(buildingLColor[i][0],buildingLColor[i][1],buildingLColor[i][2]);
        int lbx1=30+buildingOffset,lbx2=120+buildingOffset,lby1=132,lby2=395;
        glBegin(GL_QUADS);
        glVertex2f(lbx1,lby2);
        glVertex2f(lbx1,lby1);
        glVertex2f(lbx2,lby1);
        glVertex2f(lbx2,lby2);
        glEnd();
        //side
        glColor3f(sideLColor[i][0],sideLColor[i][1],sideLColor[i][2]);
        int lbsx1=120+buildingOffset,lbsx2=130+buildingOffset,lbsy1=132,lbsy2=395,lbsy3=390;
        glBegin(GL_QUADS);
        glVertex2f(lbsx1,lbsy2);
        glVertex2f(lbsx1,lbsy1);
        glVertex2f(lbsx2,lbsy1);
        glVertex2f(lbsx2,lbsy3);
        glEnd();

        //janala
        glColor3fv(gwindowColor);
        int lbwx1=35+buildingOffset,lbwx2=55+buildingOffset,lbwy1=340,lbwy2=370;
        glBegin(GL_QUADS);
        glVertex2f(lbwx1,lbwy2);
        glVertex2f(lbwx1,lbwy1);
        glVertex2f(lbwx2,lbwy1);
        glVertex2f(lbwx2,lbwy2);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1+35,lbwy2);
        glVertex2f(lbwx1+35,lbwy1);
        glVertex2f(lbwx2+35,lbwy1);
        glVertex2f(lbwx2+35,lbwy2);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1,lbwy2-40);
        glVertex2f(lbwx1,lbwy1-40);
        glVertex2f(lbwx2,lbwy1-40);
        glVertex2f(lbwx2,lbwy2-40);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1+35,lbwy2-40);
        glVertex2f(lbwx1+35,lbwy1-40);
        glVertex2f(lbwx2+35,lbwy1-40);
        glVertex2f(lbwx2+35,lbwy2-40);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1+35,lbwy2-40-40);
        glVertex2f(lbwx1+35,lbwy1-40-40);
        glVertex2f(lbwx2+35,lbwy1-40-40);
        glVertex2f(lbwx2+35,lbwy2-40-40);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1+35,lbwy2-40-40-40);
        glVertex2f(lbwx1+35,lbwy1-40-40-40);
        glVertex2f(lbwx2+35,lbwy1-40-40-40);
        glVertex2f(lbwx2+35,lbwy2-40-40-40);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1,lbwy2-40-40);
        glVertex2f(lbwx1,lbwy1-40-40);
        glVertex2f(lbwx2,lbwy1-40-40);
        glVertex2f(lbwx2,lbwy2-40-40);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(lbwx1,lbwy2-40-40-40);
        glVertex2f(lbwx1,lbwy1-40-40-40);
        glVertex2f(lbwx2,lbwy1-40-40-40);
        glVertex2f(lbwx2,lbwy2-40-40-40);
        glEnd();
        glPopMatrix();

    }

    for(int i=0; i<4; i++){
       //small building 2
       //small building
    glPushMatrix();
    glTranslatef(tSx[i],0,0);
    glColor3f(buildingSColor[i][0],buildingSColor[i][1], buildingSColor[i][2]);
    int sbbx1=70+buildingOffset,sbbx2=200+buildingOffset,sbby1=132,sbby2=245;
    glBegin(GL_QUADS);
    glVertex2f(sbbx1,sbby2);
    glVertex2f(sbbx1,sbby1);
    glVertex2f(sbbx2,sbby1);
    glVertex2f(sbbx2,sbby2);
    glEnd();

    glColor3f(sideSColor[i][0],sideSColor[i][1],sideSColor[i][2]);
    int sbtx1=60+buildingOffset,sbtx2=210+buildingOffset,sbty1=245,sbty2=255;
    glBegin(GL_QUADS);
    glVertex2f(sbtx1,sbty2);
    glVertex2f(sbtx1,sbty1);
    glVertex2f(sbtx2,sbty1);
    glVertex2f(sbtx2,sbty2);
    glEnd();
    //door
    glColor3f(sideSColor[i][0],sideSColor[i][1],sideSColor[i][2]);
    int sbdx1=120+buildingOffset,sbdx2=145+buildingOffset,sbdy1=132,sbdy2=180;
    glBegin(GL_QUADS);
    glVertex2f(sbdx1,sbdy2);
    glVertex2f(sbdx1,sbdy1);
    glVertex2f(sbdx2,sbdy1);
    glVertex2f(sbdx2,sbdy2);
    glEnd();
    //windows
    glColor3fv(gwindowColor);
    int sbwx1=80+buildingOffset,sbwx2=100+buildingOffset,sbwy1=200,sbwy2=220;
    glBegin(GL_QUADS);
    glVertex2f(sbwx1,sbwy2);
    glVertex2f(sbwx1,sbwy1);
    glVertex2f(sbwx2,sbwy1);
    glVertex2f(sbwx2,sbwy2);
    glEnd();

    glColor3fv(gwindowColor);
    sbwx1=sbwx2+20,sbwx2=sbwx2+20+20,sbwy1=200,sbwy2=220;
    glBegin(GL_QUADS);
    glVertex2f(sbwx1,sbwy2);
    glVertex2f(sbwx1,sbwy1);
    glVertex2f(sbwx2,sbwy1);
    glVertex2f(sbwx2,sbwy2);
    glEnd();

    glColor3fv(gwindowColor);
    sbwx1=sbwx2+20,sbwx2=sbwx2+20+20,sbwy1=200,sbwy2=220;
    glBegin(GL_QUADS);
    glVertex2f(sbwx1,sbwy2);
    glVertex2f(sbwx1,sbwy1);
    glVertex2f(sbwx2,sbwy1);
    glVertex2f(sbwx2,sbwy2);
    glEnd();

    //top ar upr chad
    glColor3f(103.0f/255.0f, 104.0f/255.0f, 105.0f/255.0f);
    int sbtcx1=85+buildingOffset,sbtcx2=130+buildingOffset,sbtcy1=255,sbtcy2=280;
    glBegin(GL_QUADS);
    glVertex2f(sbtcx1,sbtcy2);
    glVertex2f(sbtcx1,sbtcy1);
    glVertex2f(sbtcx2,sbtcy1);
    glVertex2f(sbtcx2,sbtcy2);
    glEnd();

    //chad ar wall
    glColor3f(sideSColor[i][0],sideSColor[i][1],sideSColor[i][2]);
    int sbtcwx1=75+buildingOffset,sbtcwx2=140+buildingOffset,sbtcwy1=280,sbtcwy2=285;
    glBegin(GL_QUADS);
    glVertex2f(sbtcwx1,sbtcwy2);
    glVertex2f(sbtcwx1,sbtcwy1);
    glVertex2f(sbtcwx2,sbtcwy1);
    glVertex2f(sbtcwx2,sbtcwy2);
    glEnd();

    glPopMatrix();

    }

    float buildingBbColor[4][3] = {
        {197.0f/255.0f, 173.0f/255.0f, 255.0f/255.0f},
        {212.0f/255.0f, 222.0f/255.0f, 30.0f/255.0f},
        {190.0f/255.0f, 173.0f/255.0f, 25.0f/255.0f},
    };

    float buildingBsColor[4][3] = {
        {191.0f/255.0f, 246.0f/255.0f, 255.0f/255.0f},
        {212.0f/255.0f, 222.0f/255.0f, 30.0f/255.0f},
        {191.0f/255.0f, 246.0f/255.0f, 255.0f/255.0f},
    };

    float tBx[6] = {0,500,1000};
    for(int i=0; i<3; i++){
        glPushMatrix();
        glTranslatef(tBx[i],0,0);
            //3rd building
        glColor3fv(buildingBbColor[i]);
        int bbbx1=390+buildingOffset,bbbx2=590+buildingOffset,bbby1=132,bbby2=285;
        glBegin(GL_QUADS);
        glVertex2f(bbbx1,bbby2);
        glVertex2f(bbbx1,bbby1);
        glVertex2f(bbbx2,bbby1);
        glVertex2f(bbbx2,bbby2);
        glEnd();

        glColor3fv(buildingBsColor[i]);
        int bbtx1=380+buildingOffset,bbtx2=600+buildingOffset,bbty1=285,bbty2=295;
        glBegin(GL_QUADS);
        glVertex2f(bbtx1,bbty2);
        glVertex2f(bbtx1,bbty1);
        glVertex2f(bbtx2,bbty1);
        glVertex2f(bbtx2,bbty2);
        glEnd();
        //doroja
        glColor3f(191.0f/255.0f, 246.0f/255.0f, 255.0f/255.0f);
        int bbdx1=450+buildingOffset,bbdx2=530+buildingOffset,bbdy1=132,bbdy2=210;
        glBegin(GL_QUADS);
        glVertex2f(bbdx1,bbdy2);
        glVertex2f(bbdx1,bbdy1);
        glVertex2f(bbdx2,bbdy1);
        glVertex2f(bbdx2,bbdy2);
        glEnd();

        //janala
            glColor3fv(gwindowColor);
        int bbwx1=400+buildingOffset,bbwx2=430+buildingOffset,bbwy1=230,bbwy2=260;
        glBegin(GL_QUADS);
        glVertex2f(bbwx1,bbwy2);
        glVertex2f(bbwx1,bbwy1);
        glVertex2f(bbwx2,bbwy1);
        glVertex2f(bbwx2,bbwy2);
        glEnd();

        glColor3fv(gwindowColor);
        bbwx1=bbwx2+20,bbwx2=bbwx2+20+30, bbwy1=230,bbwy2=260;
        glBegin(GL_QUADS);
        glVertex2f(bbwx1,bbwy2);
        glVertex2f(bbwx1,bbwy1);
        glVertex2f(bbwx2,bbwy1);
        glVertex2f(bbwx2,bbwy2);
        glEnd();

            glColor3fv(gwindowColor);
        bbwx1=bbwx2+20,bbwx2=bbwx2+20+30, bbwy1=230,bbwy2=260;
        glBegin(GL_QUADS);
        glVertex2f(bbwx1,bbwy2);
        glVertex2f(bbwx1,bbwy1);
        glVertex2f(bbwx2,bbwy1);
        glVertex2f(bbwx2,bbwy2);
        glEnd();

        glColor3fv(gwindowColor);
        bbwx1=bbwx2+20,bbwx2=bbwx2+20+30, bbwy1=230,bbwy2=260;
        glBegin(GL_QUADS);
        glVertex2f(bbwx1,bbwy2);
        glVertex2f(bbwx1,bbwy1);
        glVertex2f(bbwx2,bbwy1);
        glVertex2f(bbwx2,bbwy2);
        glEnd();
    }

}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window
    road();
	// Draw a filled triangle
    glColor3f(1.0, 0.0, 0.0);  // Set the color to red
    myCar.makeMyCar();
    callCars();
    glPushMatrix();
    sky();
    building();
    glPopMatrix();

    displayScore();
    glFlush();

	// Process all OpenGL routines

}


void specialKeyHandler(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_DOWN:
            if(lane>0) lane-=2;
                break;
        case GLUT_KEY_UP:
            if(lane<80) lane+=2;
                break;
        // You can handle other special keys here as needed
    }
    glutPostRedisplay();  // Request redisplay to see the changes
}

void handleKeyPress(unsigned char key, int x, int y) {
    if (key == 13 && gameStarted==false) {  // ASCII code for Enter key
        // Handle Enter key press event
        gameStarted = true;
        state=0;
        glutTimerFunc(1000, updateRoad, 0);
    }
    else if(key==32 && gameOver){
        exit(0);
    }
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);						// Initalise GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	// Set display mode

	glutInitWindowPosition(100, 100);				// Set window position
	glutInitWindowSize(850, 550);					// Set window size
	glutCreateWindow("An Example OpenGL Program");	// Create display window

	init();
	CreateCars();						// Execute initialisation procedure
	glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
	glutSpecialFunc(specialKeyHandler);
	glutMainLoop();					// Display everything and wait

	return 0;
}

void drawFilledCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
     glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void drawCloud(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void createCloud(){


    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    drawCloud(40,40,100+cloudt, 470);
    drawCloud(40,40,150+cloudt, 460);
    drawCloud(35,35,140+cloudt, 510);
    drawCloud(35,35,170+cloudt, 460);
    drawCloud(40,40,300+cloudt, 350);
    drawCloud(40,40,350+cloudt, 340);
    drawCloud(35,35,330+cloudt, 390);
    drawCloud(25,25,440+cloudt, 450);
    drawCloud(30,30,480+cloudt, 450);
    drawCloud(20,20,520+cloudt, 450);
    drawCloud(25,25,560+cloudt, 550);
    drawCloud(30,30,600+cloudt, 550);
    drawCloud(20,20,640+cloudt, 550);

    glFlush();
}

void drawSUN() {
    glPushMatrix();
    if(dn<2)
    {
        glColor3fv(sun);
        drawCloud(50,50,180, 520);
    }
    else
    {
        glColor3fv(moon);
        drawCloud(50,50,180, 520);
    }
    glFlush();
}


void sky(){
    int rx1=0;
    int ry1=132;
    int rx2=5600;
    int ry2=600;
    if(dn<2){
       float topColor[] = {34.0f/255.0f, 143.0f/255.0f, 255.0f/255.0f};
       float bottomColor[] = {1.0f, 1.0f, 1.0f};

        gwindowColor[0] = 187.0f/255.0f;
        gwindowColor[1] = 224.0f/255.0f;
        gwindowColor[2] = 248.0f/255.0f;

        glColor3fv(topColor);
        glBegin(GL_QUADS);
        glVertex2f(rx2,ry2);
        glVertex2f(rx1,ry2);
        glColor3fv(bottomColor);
        glVertex2f(rx1,ry1);
        glVertex2f(rx2,ry1);

        glEnd();
        //glPushMatrix();
        drawSUN();
        createCloud();
        //glPopMatrix();
    }
    else{
        gwindowColor[0] = 245.0f/255.0f;
        gwindowColor[1] = 229.0f/255.0f;
        gwindowColor[2] = 77.0f/174.0f;
        float topColor[] = {62.0f/255.0f, 64.0f/255.0f, 58.0f/255.0f};
        float bottomColor[] = {0.0f, 0.0f, 0.0f};  // Black

        glColor3fv(topColor);
        glBegin(GL_QUADS);
        glVertex2f(rx2,ry2);
        glVertex2f(rx1,ry2);
        glColor3fv(bottomColor);
        glVertex2f(rx1,ry1);
        glVertex2f(rx2,ry1);
        glEnd();
        glPointSize(3.0);
        glColor3f(0.75, 0.75, 0.75); // You can adjust the size as needed
        drawSUN();
    // Set the color of the dots
    glColor3f(1.0, 1.0, 1.0); // Red dots in RGB color

    glBegin(GL_POINTS); // Begin drawing points

    // Specify the coordinates of the points
    glVertex2f(100, 500);
    glVertex2f(200, 550);
    glVertex2f(300, 500);
    glVertex2f(20, 500);
    glVertex2f(30, 530);
    glVertex2f(320, 580);
    glVertex2f(320, 580);
    glVertex2f(120, 520);
    glVertex2f(520, 580);
    glVertex2f(520, 580);
    glVertex2f(580, 550);
    glVertex2f(580, 580);
    glVertex2f(520, 510);
    glVertex2f(490, 580);
    glVertex2f(520, 380);
    glVertex2f(530, 480);
    glVertex2f(527, 540);
    glVertex2f(520, 540);
    glVertex2f(310, 570);
    glVertex2f(330, 560);
    glVertex2f(200, 580);
    // Add more points as needed

    glEnd(); // End drawing points
    }


}

void displayScore() {


    glColor3f(0.0, 1.0, 1.0); // White color
    glRasterPos2i(520, 570); // Position for the score text
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);

    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }

}

void displayStartScreen() {
    glColor3f(0.0, 1.0, 1.0); // White color
    glRasterPos2i(220, 350);
    std::string startText = "Press Enter to Start";
    for (char c : startText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void displayGameOverScreen() {
    glColor3f(0.0, 1.0, 1.0); // White color
    glRasterPos2i(280, 500);
    std::string gameOverText = "Game Over";
    for (char c : gameOverText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2i(286, 480);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2i(260, 455);
    std::string exitText = "Press Space to Exit";
    for (char c : exitText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    state=1;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameStarted) {
        displayStartScreen();
    } else if (gameOver) {
        displayGameOverScreen();
    } else {
        drawShapes();
    }

    glutSwapBuffers();
}



