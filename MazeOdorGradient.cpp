 /************************ Maze Odor Gradient.cpp **********************************

Group Project of Artificial Intelligence 

July 22 2021
/*********************************************************************/ 
//
//  Students name:  Stadyn, Samantha, Arianna Washington
//
//------------------------------------------------------------------------------------------------
// GLOBALS

   
#define  files 45
#define  columns 75     //       size of the graphic maze   

int b_flag;
int stop;
char dummy[1];
//--
char key, color;

int x_agent, y_agent;

int x_plot_maze=30;
int y_plot_maze=30;

int square_size=50-33;        //
int captured_color;


//const int qSize = 6;
const float gamma = 0.8;

int R[files][columns];
int S[files][columns];    //
int C[files][columns];    //

int screen_image[files][columns];   //   presence  in pixels of the agent  and environment in the screen. Alter_ego  

int currentState;   
int episode;  

int move_flag;

int file_agent;    // file
int column_agent;  // column

int file_NPC;    // file
int column_NPC;  // column

int sensor[4];
int MAX;
int grad_pointer;

int path[500][2];
int visited[500][2];
int unvisited[4][2];
int cont;
int stcont;
int mov;
bool no_unvisited = false;

int aux_x, aux_y;
int player_captured_color;

//----------------------------------------)))
//    end globals
//----------------------------------------)))
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip.h>
#include <windows.h>



#include "plot_maze_items.h"
#include "Q_structures_lib.h"
#include "all_possible_mazes.h"        


//******************* variables globales ***************************************/
using namespace std;


//-----------------------------------------
//    inicia el modo grafico             
//-------------------------------------    
void grafico(void)
{
    int    GraphDriver;  /* The Graphics device driver */
    int    GraphMode;    /* The Graphics mode value */
    int    ErrorCode;    /* Reports any graphics errors */
   
    initgraph(&GraphDriver, &GraphMode, "");

    ErrorCode = graphresult();            /* Read result of initialization*/
    if( ErrorCode != grOk )              /* Error occured during init    */
    {
       printf(" Graphics System Error: %s", grapherrormsg( ErrorCode ) );
       exit( 1 );
    }
}
//-------------------------------------  
void erase_screen(void)
{
    setcolor(LIGHTGRAY);
    bar(0,0,2400,900);  
}
//-------------------------------------------------------


void loadingBar()
{

    system("color 0A");

    char a = 177, b = 219;
  
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t + Loading...\n\n");
    printf("\t\t\t\t\t");
  
    for (int i = 0; i < 26; i++)
        printf("%c", a);

    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) {
        printf("%c", b);
        Sleep(100);
    }

    system("cls");

    printf("\t\t Maze Gradiend Odor\n");


}

void Start_Message(void){
  
  moveto(0,250); 
  settextstyle(4,0,4); 
  setcolor(GREEN);
  outtext("Welcome to the Maze Gradiend Program ");


  moveto(0,300); 
  settextstyle(9,0,4); 
  setcolor(GREEN);
  outtext("Maximize the window size ");

  loadingBar();

  erase_screen();

  moveto(600,0); 
  settextstyle(9,0,2); 
  setcolor(WHITE);
  outtext(" Maze Gradiend Program  ");

} 

//-------------------------------------------------------------
void loop(void)  //                                                           loop  !!                        &&&/&&/&&/////
{

    plot_maze();
    plot_agent();
    print_R();
    print_S();   //  gradiente de olor
    print_C();   //  matriz de calor
    
    cout <<" ready to exploit-- " <<endl; 
     
    getch();        
    Q_exploit();
  
}   
//------------------------------------------------------
//===================================================================================================
void main(void)
{ 
    int rand_seed=37;     // 26
    int temp;
    char str[10];  
    grafico();
    setcolor(LIGHTGRAY);
    bar(0,0,2400,900);  

    srand(rand_seed);   

    file_agent=0;               
    column_agent=0;             

    Start_Message();       // Messegae of welcome

    init_R();                  //We get a random MAZE
    init_S();


    x_agent=x_plot_maze;   //  x_agent:  coordinate x of agent in the screen    
    y_agent=y_plot_maze;   //  y_agent:  coordinate y of agent in the screen  

    plot_maze();
    plot_agent();

    //print_R();

    //load_Q();    // carga el conocimiento Policy
    //print_Q();
    //getch();

    stop=0;

    /*
    moveto(120,0);  // PRINT SCORE
    setcolor(WHITE);
    outtext("Score: ");
    outtextxy(175,0,gcvt(score,6,str)); 
    loop();*/

    do {
       //play_flag=0; 
       key=getch();
       switch (key) {

            /*                        
           case 'w':          {
                               move_up();
                               check_reward();
                               plot_all(); 
                               loop();                             
                              } 
           break;     
           case ' ':          {          
                               stop=stop^1;
                               loop();
                              }                                     
           break; */
                              
            case 'R': case 'r':  {
                                   init_R();
                                   init_S();
                                   loop();
                                 }
            break;                     
            
            default:
                init_S();
                loop();
         }
   } while ((key!='x')&&(key!='X'));

   closegraph();
   clrscr();
}

//---------------------------------------
/*
BLACK        ³  0  ³ Yes ³ Yes
BLUE         ³  1  ³ Yes ³ Yes
GREEN        ³  2  ³ Yes ³ Yes
CYAN         ³  3  ³ Yes ³ Yes
RED          ³  4  ³ Yes ³ Yes
MAGENTA      ³  5  ³ Yes ³ Yes
BROWN        ³  6  ³ Yes ³ Yes
LIGHTGRAY    ³  7  ³ Yes ³ Yes
DARKGRAY     ³  8  ³ No  ³ Yes
LIGHTBLUE    ³  9  ³ No  ³ Yes
LIGHTGREEN   ³ 10  ³ No  ³ Yes
LIGHTCYAN    ³ 11  ³ No  ³ Yes
LIGHTRED     ³ 12  ³ No  ³ Yes
LIGHTMAGENTA ³ 13  ³ No  ³ Yes
YELLOW       ³ 14  ³ No  ³ Yes
WHITE        ³ 15  ³ No  ³ Yes

----------------------------------------------------------------
     if(x<0)    { x=0; if( heat<100) heat++;}     
     if(y<35)    { y=35; if( heat<100) heat++;}  
     if(x>640) { x=640; if( heat<100) heat++;}  //  x>1200 : full pantalla 
     if(y>470) { y=470; if( heat<100) heat++;}   // y>720 : full pantalla 
         
//--------------------------------------------------

************************ basic_robot.cpp ***************************
desarrollado usando Dev-C++ IDE V4.9.8.4 GNU / MinGW / GNU gcc
                    Sc1 IDE / BCC5.5
                    version orginal por Oscar Chang
*********************************************************************/

