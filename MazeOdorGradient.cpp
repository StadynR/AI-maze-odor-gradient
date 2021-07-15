 /************************ Maze Odor Gradient.cpp **********************************

Group Project of Artificial Intelligence 

July 22 2021
/*********************************************************************/ 
//
//  Students name:  Stadyn Román, Samantha Quintachala, Arianna Armijos, Washington Pijal
//
//------------------------------------------------------------------------------------------------
// GLOBALS
   
#define  files 28
#define  columns 70    //       size of the graphic maze   

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

int path[files*columns*3][2];
int visited[files*columns][2];
int cont;
int stcont;
int mov;

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

    printf("\t\t Maze Gradient Odor\n");


}

void Start_Message(void){
  
  moveto(0,250); 
  settextstyle(4,0,4); 
  setcolor(GREEN);
  outtext("Welcome to the Maze Gradient Program ");


  moveto(0,300); 
  settextstyle(9,0,4); 
  setcolor(GREEN);
  outtext("Maximize the window size ");

  //loadingBar();

  erase_screen();

  moveto(600,0); 
  settextstyle(9,0,2); 
  setcolor(WHITE);
  outtext(" Maze Gradient Program  ");

}
//-------------------------------------------------------------
void loop(void)  //                                                           loop  !!                        &&&/&&/&&/////
{

    plot_maze();
    plot_agent();
    print_R();
    print_S();   //  gradiente de olor
    
    cout <<" ready to exploit-- " <<endl; 
     
    //getch();        
    Q_exploit();
  
}   
//------------------------------------------------------
void choose(void)
{
        //erase_screen();
        
    
        moveto(40,400); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want to restart the environment? Press 'R' "); 
        
        moveto(20,550); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want change the cheese position? Press 'C' "); 
        
        moveto(50,500); 
        settextstyle(4,0,4); 
        setcolor(GREEN);
        outtext(" Do you want change the maze? Press 'M' ");         
        
        do{
            key=getch();
            switch(key){
                case 'R': case 'r':  
                {
                    init_R();
                    random_chees();
                    init_S();
                    random_agent();
                    plot_maze();
                    plot_agent();
                } break;
                case'C': case 'c':
                {
                    random_chees();
                    init_S();
                    plot_maze();
                    plot_agent();
                } break;
                case'M': case 'm':
                {
                    init_R();
                    init_S();
                    plot_maze();
                    plot_agent();
                    //random_chees();
                } break;
                case'A': case 'a':
                {
                    random_agent();
                    plot_maze();
                    plot_agent();
                    //random_chees();
                } break;
                case ' ':
                {
                    loop();
                    random_agent();
                }
            }
        }while(key!='x' && key!='X');
}
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

    randomize();

    //file_agent=0;               
    //column_agent=0;             

    Start_Message();       // Messegae of welcome
    
    init_R();                  //We get a random MAZE
    random_chees();
    init_S();
    random_agent();

    x_agent=x_plot_maze;   //  x_agent:  coordinate x of agent in the screen    
    y_agent=y_plot_maze;   //  y_agent:  coordinate y of agent in the screen  

    print_R();
    print_S();   //  gradiente de olor
    plot_maze();
    plot_agent();
    plot_olor_gradient();
    
    stop=0;
    //loop();
    choose();

    /*
    moveto(120,0);  // PRINT SCORE
    setcolor(WHITE);
    outtext("Score: ");
    outtextxy(175,0,gcvt(score,6,str)); 
    loop();

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
           break; 
                              
            case 'R': case 'r':  {
                                   init_R();
                                   init_S();
                                   random_agent();
                                   plot_maze();
                                   plot_agent();
                                 }
            break;                     
            
            default:
                loop();
         }
   } while ((key!='x')&&(key!='X'));*/

   closegraph();
   clrscr();
}

//---------------------------------------
/*
BLACK        Â³  0  Â³ Yes Â³ Yes
BLUE         Â³  1  Â³ Yes Â³ Yes
GREEN        Â³  2  Â³ Yes Â³ Yes
CYAN         Â³  3  Â³ Yes Â³ Yes
RED          Â³  4  Â³ Yes Â³ Yes
MAGENTA      Â³  5  Â³ Yes Â³ Yes
BROWN        Â³  6  Â³ Yes Â³ Yes
LIGHTGRAY    Â³  7  Â³ Yes Â³ Yes
DARKGRAY     Â³  8  Â³ No  Â³ Yes
LIGHTBLUE    Â³  9  Â³ No  Â³ Yes
LIGHTGREEN   Â³ 10  Â³ No  Â³ Yes
LIGHTCYAN    Â³ 11  Â³ No  Â³ Yes
LIGHTRED     Â³ 12  Â³ No  Â³ Yes
LIGHTMAGENTA Â³ 13  Â³ No  Â³ Yes
YELLOW       Â³ 14  Â³ No  Â³ Yes
WHITE        Â³ 15  Â³ No  Â³ Yes

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

