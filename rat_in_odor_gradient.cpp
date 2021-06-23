 /************************ top_eye_flop.cpp **********************************
Basic agent in maze
Yachay Tech University
Artificial Intelligence Lab
Prof Oscar Chang

May 27, 2021
/*********************************************************************/ 
//
//  Student name:  ____________________
//
//------------------------------------------------------------------------------------------------
// GLOBALS

   
#define  rows 21
#define  columns 21       //size of the graphic maze   

int b_flag;
int stop;
char dummy[1];
//--
char key, color;

int x_agent, y_agent;

int x_plot_maze=30;
int y_plot_maze=30;

int square_size=21;         //Tamaño de cuadro para dibujar
int captured_color;

const float gamma = 0.8;

int Q[rows][columns];    //Matriz Q
int S[rows][columns];    //Matriz S de olor
int C[rows][columns];    //Matriz C de calor (veces que el agente ha pasado por la misma casilla)

int episode;  

int row_agent;    // file
int column_agent;  // column

int sensor[4];
int MAX;
int grad_pointer;

int cell[2];
int path[500][2];
int visited[500][2];
int unvisited[4][2];
int cont;
int stcont;
int mov;
bool no_unvisited = false;


int R[rows][columns] = 
        {    
            //0       1      2      3     4       5      6      7      8       9     10    11     12      13     14    15     16    17     18    19    20 
            {100, 0,  0,  0, -1,  0,  0, -1,  0,  0,  0,  0,  0,   0,  0,  0, -1, -1,  0,  0,  0},           // 0 
            {-1, -1, -1,  0, -1,  0,  0, -1,  0, -1, -1, -1, -1,  -1, -1,  0, -1, -1,  0, -1, -1},           // 1 
            { 0,  0, -1,  0, -1, -1,  0, -1,  0,  0,  0,  0,  0,  -1, -1,  0,  0,  0,  0, -1, -1},           // 2 
            { 0, -1, -1,  0,  0,  0,  0, -1, -1, -1, -1,  0, -1,  -1, -1,  0, -1, -1, -1, -1, -1},           // 3 
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -1, -1,  0, -1, -1, -1, -1, -1},           // 4 
            {-1, -1, -1, -1,  0,  0, -1, -1,  0, -1, -1, -1, -1,   0,  0,  0,  0,  0,  0,  0,  0},           // 5 
            { 0,  0,  0,  0,  0,  0, -1,  0,  0,  0,  0,  0, -1,  -1,  0, -1, -1, -1, -1, -1,  0},           // 6 
            { 0, -1,  0, -1,  0, -1, -1,  0, -1, -1, -1,  0,  0,   0,  0, -1, -1,  0, -1,  0,  0},           // 7 
            { 0, -1,  0, -1,  0,  0, -1,  0, -1,  0, -1,  0, -1,  -1, -1,  0,  0,  0, -1,  0, -1},           // 8 
            { 0, -1, -1, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  -1, -1, -1,  0, -1, -1,  0, -1},           // 9 
            { 0,  0,  0,  0, -1,  0,  0,  0, -1,  0, -1,  0,  0,   0, -1, -1,  0,  0, -1,  0, -1},           // 10 
            {-1, -1, -1,  0,  0,  0, -1,  0, -1,  0, -1,  0,  0,   0,  0,  0,  0,  0,  0,  0,  0},           // 11 
            { 0,  0,  0,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0,  -1, -1, -1, -1, -1, -1, -1,  0},           // 12 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 13 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 14 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 15 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 16 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 17 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 18 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 19 
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},           // 20 
        };
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


#include "read_write_Q_matrix.h"
#include "plot_maze_items.h"
#include "Q_structures_lib.h"


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
   setfillstyle(SOLID_FILL,LIGHTGRAY);     
   bar(150,100,350,300) ;         
   floodfill(255,205,BLACK);    
}
//-------------------------------------------------------------
void loop(void){                                                            
   
   while(1)
    { 
        
     print_R();
     print_S();   //  gradiente de olor
     print_C();   //  matriz de calor
   
     cout <<" ready to exploit-- " <<endl; 
     
     getch();        
     Q_exploit();   
     
     if(kbhit()) break;
     if(stop)break;
    }
    
}    
//===================================================================================================
void main(void)
{ 
  int rand_seed=37;     
    
    grafico();
    setcolor(LIGHTGRAY);
    bar(0,0,1400,900);  
    
    srand(rand_seed);   
    
    row_agent = 0;                // row of agent in matrix R, S and C
    column_agent = 0;             // column of agent in matrix R, S and C
   
    x_agent = x_plot_maze;   //  x_agent:  coordinate x of agent in the screen    
    y_agent = y_plot_maze;   //  y_agent:  coordinate y of agent in the screen  
    
    plot_maze();
    init_S();    
    //load_Q();
    //print_Q();
    
    stop=1;
    
    loop();
    
    do {
       //play_flag=0; 
       key=getch();
       switch (key) {                             
            case ' ':{                     //-------    HERE  ! !!!!!!!!!!!!!!!!         !!!!!!!!!!!!1
                stop=stop^1;
                loop();
            }
            break;                       

           case 'p': case 'P': {
                                stop=1;    
                                //print_console_aux();                
                                //seed_learns();  //  OJO  no presenta los Targets apropiados          
                                loop();                              
                               }
	       break;    
           
           default:
               loop();
         }
   } while ((key!='x')&&(key!='X'));

   closegraph();
   clrscr();
}

//----------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------

************************ basic_robot.cpp ***************************
desarrollado usando Dev-C++ IDE V4.9.8.4 GNU / MinGW / GNU gcc
                    Sc1 IDE / BCC5.5
                    version orginal por Oscar Chang
*********************************************************************/

