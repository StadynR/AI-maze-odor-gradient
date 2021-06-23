//---------------------------------
//         RUTINA PLOT NET ITEMS    --    GRAFICA los parametros de la matriz Q 

//-----------------------------------------
void plot_maze(void)               ////       PLOT MAZE GRAPHICS
{
int i,j,sx,sy,x,y,color,scale;  //variables de navegación y dibujo
int temp; 
    
x = x_plot_maze;   
scale = square_size;
   
   for(i=0;i<rows;i++)  // 
     { 
      y=y_plot_maze;   
      sy = y+i*scale;  //navegación en y           
      for(j=0;j<columns;j++)
         {    
          sx = x+j*scale;   //navegación en x
          temp=R[i][j];  
          
          color=LIGHTGRAY; 
          if(temp<0) color=BLUE;          // WALL
          if(temp==0) color=RED;          // FLOOR    
          if(temp==100) color=YELLOW;     // TOP REWARD
          setcolor(color); 
          setfillstyle(SOLID_FILL,color); 
          bar(sx,sy,sx+scale,sy+scale); 
         }
     } 
 
}
//----------------------------------------------------------------------------------------
void plot_trail(void)               ////       PLOT MAZE GRAPHICS
{
    int color, agent_size=square_size-0;  
    int x,y;    
     
     int offset_x=0;   //   para centrar al agente en x
     int offset_y=0;   //   para centrar al agente en y
    
     x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
     y= y_plot_maze;   //   
       
    x_agent=x+column_agent*square_size;
    y_agent=y+row_agent*square_size;
    
    //captured_color=getpixel(x_agent,y_agent);   //  el sensor captura en una esquina
     
     setcolor(LIGHTRED); //  
     setfillstyle(SOLID_FILL,LIGHTRED);   
     bar(x_agent+offset_x,y_agent+offset_y,x_agent+agent_size,y_agent+agent_size);
}
//----------------------------------------------------------------------------------------
void plot_agent(void)
{
int agent_size=square_size-3;  //tamaño del agente
int x,y;    
    
int offset_x=5;   //   para centrar al agente en x
int offset_y=5;   //   para centrar al agente en y

 x= x_plot_maze;   //   para sincronizarse con el enviroment grafico
 y= y_plot_maze;   
   
    x_agent=x+column_agent*square_size;
    y_agent=y+row_agent*square_size;
    
    captured_color=getpixel(x_agent,y_agent);   //  el sensor captura en una esquina
 
 setcolor(CYAN); //  
 setfillstyle(SOLID_FILL,CYAN);   
 bar(x_agent+offset_x,y_agent+offset_y,x_agent+agent_size,y_agent+agent_size);   
    
}
//-------------------------------------------------------------



