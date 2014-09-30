#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "myTable.h"
#include "Plane.h"

#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// Positions for two lights
float light0_pos[4] = {1, 2, 1, 1};
float light1_pos[4] = {5, 2, 3, 1};
float light2_pos[4] = {1, 3, -2, 1};
float light3_pos[4] = {12, 1, 2, 1};
float light4_pos[4] = {8, 8.5, 4, 1};
float light5_pos[4] = {0.5, 4, 7.5, 1};

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= {0,0,0,1.0};

// number of divisions
#define BOARD_A_DIVISIONS 30 // 1
#define BOARD_B_DIVISIONS 100

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = {0.2, 0.2, 0.2};
float shininessA = 120.f; // com shininess menor, a iluminação é mais "geral", com shininess maior, é mais localizada (ver exemplo da esfera da aula)

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 120.f;

// Coefficients for material for the floor
float ambDark[3] = {0.2, 0.2, 0.2};
float difDark[3] = {0.2, 0.2, 0.2};
float specDark[3] = {0.1, 0.1, 0.1};
float shininessDark = 10.f;

// Coefficients for material for the wall
float ambLight[3] = {0.6, 0.6, 0.6};
float difLight[3] = {0.7, 0.7, 0.7};
float specLight[3] = {0.6, 0.6, 0.6};
float shininessLight = 60.f;

float ambientNull[4]={0,0,0,1};
float ambient2[4]={0.7,0.7,0.7,1};
float yellow[4]={1,1,0,1};

// Coefficients for material for the chair
float ambBluePlastic[3] = {0, 0, 0.5};
float difBluePlastic[3] = {0.2, 0, 1};
float specBluePlastic[3] = {0.1, 0, 1};
float shininesBluePlastic = 230.f;

// Coefficients for material for the table
float ambTable[3] = {0.2, 0.2, 0.2};
float difTable[3] = {0.6, 0.6, 0.6};
float specTable[3] = {0.1, 0.1, 0.1};
float shininessTable = 10.0;

// Coefficients for material for the slides
float ambSlides[3] = {0.5, 0.5, 0.5};
float difSlides[3] = {0.6, 0.6, 0.6};
float specSlides[3] = {0.1, 0.1, 0.1};
float shininessSlides = 10.0;

// Coefficients for material for the slides
float ambBoard[3] = {0.5, 0.5, 0.5};
float difBoard[3] = {0.3, 0.3, 0.3};
float specBoard[3] = {0.5, 0.5, 0.5};
float shininessBoard = 200.0;


void LightingScene::init() 
{
  // Enables lighting computations
  glEnable(GL_LIGHTING);

  //glPolygonMode(GL_FRONT, GL_LINE); // meter isto se quiser ver as linhas do polígonos!!!

  // Sets up some lighting parameters
  // Computes lighting only using the front face normals and materials
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  

  // Define ambient light (do not confuse with ambient component of individual lights)
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);  

  // choose the shading moodle we want
  //glShadeModel(GL_FLAT);
  glShadeModel(GL_SMOOTH);

  // Declares and enables two lights, with null ambient component
  /*
  light0 = new CGFlight(GL_LIGHT0, light0_pos);
  light0->setKc(0.0); light0->setKl(0.2); light0->setKq(0.0);
  light0->disable();
  light0->enable();

  light1 = new CGFlight(GL_LIGHT1, light1_pos);
  light1->setKc(0.0); light1->setKl(0.2); light1->setKq(0.0);
  light1->disable();
  light1->enable();

  light2 = new CGFlight(GL_LIGHT2, light2_pos);
  light2->setKc(0.0); light2->setKl(0.2); light2->setKq(0.0);
  light2->disable();
  light2->enable();


  light3 = new CGFlight(GL_LIGHT3, light3_pos);
  light3->setKc(0.0); light3->setKl(0.2); light3->setKq(0.0);
  light3->disable();
  light3->enable();
  */
  light4 = new CGFlight(GL_LIGHT4, light4_pos);
  light4->setKc(0.0); light4->setKl(0.1); light4->setKq(0.0);
  light4->disable();
  light4->enable();

  light5 = new CGFlight(GL_LIGHT5, light5_pos);
  light5->setKc(0.0); light5->setKl(0.07); light5->setKq(0.0);
  light5->disable();
  light5->enable();

  // Uncomment below to enable normalization of lighting normal vectors
  glEnable (GL_NORMALIZE);

  //Declares materials
  materialA = new CGFappearance(ambA,difA,specA,shininessA);
  materialB = new CGFappearance(ambB,difB,specB,shininessB);
  dark = new CGFappearance(ambDark,difDark,specDark,shininessDark);
  light = new CGFappearance(ambLight,difLight,specLight,shininessLight);
  eletricBlue = new CGFappearance(ambBluePlastic, difBluePlastic, specBluePlastic, shininesBluePlastic);

  //Declares textures
  tableTexture = new CGFtexture("table.png");
  slideTexture = new CGFtexture("slides.png");
  boardTexture = new CGFtexture("board.png");
  windowTexture = new CGFtexture("window.png");
  floorTexture = new CGFtexture("floor.png");
  wallTexture = new CGFtexture("wall.png");
  marmoreTexture = new CGFtexture("marmore.png");

  //Declares materials with textures
  tableAppearance = new CGFappearance(ambTable, difTable, specTable, shininessTable);
  tableAppearance->setTexture(tableTexture);

  slidesAppearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);
  slidesAppearance->setTexture(slideTexture);

  boardAppearance = new CGFappearance(ambBoard, difBoard, specBoard, shininessBoard);
  boardAppearance->setTexture(boardTexture);

  windowAppearance = new CGFappearance(ambLight,difLight,specLight,shininessLight);
  windowAppearance->setTexture(windowTexture);
  windowAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);

  floorAppearance = new CGFappearance(ambLight,difLight,specLight,shininessLight);
  floorAppearance->setTexture(floorTexture);
  floorAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);

  wallAppearance = new CGFappearance(ambLight,difLight,specLight,shininessLight);
  wallAppearance->setTexture(wallTexture);
  wallAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);

  marmoreAppearance = new CGFappearance(ambLight,difLight,specLight,shininessLight);
  marmoreAppearance->setTexture(marmoreTexture);
  marmoreAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);

  //Declares scene elements
  table = new myDesk(tableAppearance, eletricBlue);
  wall = new Plane();
  boardA = new Plane(BOARD_A_DIVISIONS);
  boardB = new Plane(BOARD_B_DIVISIONS);
  cilindro1 = new myCylinder(20,20,true);
  cilindro2 = new myCylinder(20,20,false);
  lamp1 = new myLamp(15, 15, true);
  lamp2 = new myLamp(15, 15, false);
  lamp3 = new myLamp(20, 20, true);
  clock = new myClock(true);
  airPlane = new myPaperPlane();

  setUpdatePeriod(1000);
}

void LightingScene::display() 
{

  // ---- BEGIN Background, camera and axis setup

  // Clear image and depth buffer everytime we update the scene
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Initialize Model-View matrix as identity (no transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Apply transformations corresponding to the camera position relative to the origin
  CGFscene::activeCamera->applyView();

  //light0->draw();
  //light1->draw();
  //light2->draw();  
  //light3->draw();
  light4->draw();
  light5->draw();

  // Draw axis
  //axis.draw();

  // ---- END Background, camera and axis setup

  // ---- BEGIN Primitive drawing section

  int textureWidth, textureHeight;
  
  // Clock on the wall
  glPushMatrix();
  glTranslated(7.5,8,0);
  glRotated(180,0,1,0);
  glRotated(-90,1,0,0);
  clock->draw();
  glPopMatrix();
  
  // Paper plane
  glPushMatrix();
  glTranslated(13,4,8);
  glScaled(2,2,2);
  glRotated(180,0,1,0);
  light->apply();
  airPlane->draw();
  glPopMatrix();

  // Cilindro c/ smooth
  glPushMatrix();
  glTranslated(1,0,14);
  glScaled(1,5,1);
  marmoreAppearance->apply();
  cilindro1->draw();
  glPopMatrix();

  // Cilindro s/ smooth
  glPushMatrix();
  glTranslated(14,0,14);
  glScaled(1,5,1);
  marmoreAppearance->apply();
  cilindro2->draw();
  glPopMatrix();

  // Lamp c/ smooth
  glPushMatrix();
  glTranslated(8,0,3);
  tableAppearance->apply();
  lamp1->draw();
  glPopMatrix();

  // Lamp s/ smooth
  glPushMatrix();
  glTranslated(10,0,3);
  tableAppearance->apply();
  lamp2->draw();
  glPopMatrix();

  // Lamp do tecto
  glPushMatrix();
  glTranslated(8,8,4);
  light->apply();
  lamp3->draw();
  glPopMatrix();

  //First Table
  glPushMatrix();
  glTranslated(5,0,8);
  table->draw();
  glPopMatrix();

  //Second Table
  glPushMatrix();
  glTranslated(12,0,8);
  table->draw();
  glPopMatrix();

  //Floor ***********************
  glPushMatrix();
  glTranslated(7.5,0,7.5);
  glScaled(15,0.2,15);
  dark->apply();
  floorAppearance->apply();

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

  wall->repeatTexture(10,12);

  wall->draw();
  wall->resetTextureFit();
  glPopMatrix();

  //LeftWall ******************************
  glPushMatrix();
  glTranslated(0,4,7.5);
  glRotated(-90.0,0,0,1);
  glScaled(8,0.2,15);
  
  windowAppearance->apply();

  wall->setTextureSize(5,5,15,8);

  wall->rotateTexture();
  wall->draw();

  wall->resetTextureFit();
  glPopMatrix();

  //PlaneWall ****************************************
  glPushMatrix();
  glTranslated(7.5,4,0);
  glRotated(90.0,1,0,0);
  glScaled(15,0.2,8);
  wallAppearance->apply();
  wall->draw();
  glPopMatrix();

  // Board A ***********************************************
  glPushMatrix();
  glTranslated(4,4,0.2);
  glScaled(BOARD_WIDTH, BOARD_HEIGHT,1);
  glRotated(90.0,1,0,0);

  boardAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);
  slidesAppearance->apply();

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

  boardB->fitTexture(textureWidth, textureHeight, BOARD_WIDTH, BOARD_HEIGHT);

  boardA->draw();
  boardA->resetTextureFit();
  glPopMatrix();

  //PlaneB **********************************************************
  glPushMatrix();
  glTranslated(10.5,4,0.2);
  glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
  glRotated(90.0,1,0,0);

  boardAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);
  boardAppearance->apply();

  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

  boardB->fitTexture(textureWidth, textureHeight, BOARD_WIDTH, BOARD_HEIGHT);

  boardB->draw();
  boardB->resetTextureFit();
  glPopMatrix();

  // ---- END Primitive drawing section

  // We have been drawing in a memory area that is not visible - the back buffer, 
  // while the graphics card is showing the contents of another buffer - the front buffer
  // glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
  glutSwapBuffers();
}

void LightingScene::update (unsigned long arg) {
	clock->update(arg);
	airPlane->update(arg);
}

LightingScene::~LightingScene() 
{
  delete(light0);
  delete(light1);
  delete(light2);
  delete(light3);
  delete(light4);
  delete(light5);

  delete(table);
  delete(wall);
  delete(boardA);
  delete(boardB);
  delete(cilindro1);
  delete(cilindro2);
  delete(lamp1);
  delete(lamp2);

  delete(clock);
  delete(hourPointer);

  delete(materialA);
  delete(materialB);
  delete(dark);
  delete(light);
  delete(eletricBlue);

  delete(tableTexture);
  delete(slideTexture);
  delete(boardTexture);
  delete(windowTexture);
  delete(floorTexture);
  delete(wallTexture);

  delete(tableAppearance);
  delete(slidesAppearance);
  delete(boardAppearance);
  delete(windowAppearance);
  delete(wallAppearance);
}