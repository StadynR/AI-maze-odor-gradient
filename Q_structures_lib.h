//===========================================================================
//  DEFINICION DE ESTRUCTURAS Q 
//========================================================================
//----------------------------------------------------------------------------------------------------     
void print_Q(void)
{
 int i,j;
    
    printf("This is the Q Matrix:\n \n");
    for(i = 0; i < rows; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << Q[i][j];   
		}
        cout << "\n";
	} 
    cout << "\n";
}
//-------------------------------------------------------------------------------------------
void print_R(void)
{
 int i,j;
    
    printf("This is the R Matrix:\n \n");
    for(i = 0; i < rows; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << R[i][j];   
		} 
        cout << "\n";
	} 
    cout << "\n";
}
//---------------------------------------------------------------------------------------------
void print_S(void)
{
 int i,j;
    
    printf("This is the S Matrix:\n \n");
    for(i = 0; i < rows; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << S[i][j];   
		}
        cout << "\n";
	} 
    cout << "\n";
}
//------------------------------------------------------------------------------------------------
void init_S(void)
{
 float lambda=10;    //  costante de decaimiento con la distancia
 //float N=1.0;         //   N : scent concentration in a given square
 float step=0.01;     // cuanto se avanza en cada loop  
 int i,j,k;
 
   for (i=0; i < rows; i++)
   for (j=0; j < columns; j++)
    {
     k = i + j;
     //k = sqrt(i*i+j*j);   // distancia pitagoras a coordenadas (0,0)
     if(R[i][j]!=-1) S[i][j]=100* exp(-lambda*step*k);  // concentracion % a esa distancia
    }   
    //   se consulta a la matriz R por lo tanto el gradiente sigue la ley de las paredes
}
//-------------------------------------------------------------
void print_C(void)
{
 int i,j;
    
    printf("This is the C Matrix:\n \n");
    for(i = 0; i < rows; i++)
        {
        for(j = 0; j < columns; j++)
            {
            cout << setw(5) << C[i][j];   
		}
        cout << "\n";
	} 
    cout << "\n";
}
//-----------------------------------------------------
void init_C(void)
{
   int i,j;
   for (i=0; i < rows; i++)
    for (j=0; j < columns; j++)
         C[i][j]=0; 
}
//-------------------------------------------------------------
void move_left(void)
{
 int temp;
    temp=getpixel(x_agent-square_size,y_agent);   // revisa cercania a la izquierda
    if(temp==4||temp==14) // movimiento válido
    {  
     x_agent=x_agent-square_size;
     column_agent--;
    }    
   C[row_agent][column_agent]++;
}
//--------------------------------------------------------------
void move_right(void)
{
 int temp;   
  temp=getpixel(x_agent+square_size,y_agent);   // revisa cercania a la derecha
  if(temp==4||temp==14)
     {
      x_agent=x_agent+square_size;
      column_agent++; 
     }  
  C[row_agent][column_agent]++;
    
}
//-------------------------------------------------------------
void move_up(void)
{
 int temp;
    temp=getpixel(x_agent,y_agent-square_size);   // revisa cercania arriba
    if(temp==4||temp==14)
    {
     y_agent=y_agent-square_size;
     row_agent--;
    }
 C[row_agent][column_agent]++;    
  
}
//-------------------------------------------------------------
void move_down(void)
{
 int temp;
   temp=getpixel(x_agent,y_agent+square_size);    // revisa cercania abajo
   if(temp==4||temp==14)
   {
    y_agent=y_agent+square_size; 
    row_agent++;
   } 
  C[row_agent][column_agent]++;   
}
//--------------------------------------------------------
void search_for_MAX(void) 
{

    sensor[0]= S[row_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0) sensor[0]=-1;           // desborde a la izquierda 
        
    sensor[1]= S[row_agent][column_agent+1];    // lee a derecha
    if(column_agent==columns-1) sensor[1]=-1;
    
    sensor[2]= S[row_agent-1][column_agent];    // lee arriba
    if(row_agent==0) sensor[2]=-1;
    
    sensor[3]= S[row_agent+1][column_agent];    // lee abjo
    if(row_agent==rows-1) sensor[3]=-1;

    MAX=sensor[0];
    for(int i = 0; i < 4; i++) if(sensor[i] >= MAX) { MAX=sensor[i];grad_pointer=i; }  // grad_pointer apunta al maximo valor
}
//-------------------------------------------------------
void Q_explore(void)  
{
 int temp;
 int i,j;     
 float max;
 
    
 randomize(); 
   episode=1; 
   do
    {
         do
         {
          i=random(rows);
          j=random(columns); 
          temp=R[i][j];             
         } while(temp==-1);    // el agente se ubica en estado inicial aleatorio con entrada diferente de -1   
 
         //row_agent=i;          // ubicamos al agente en la matriz
         //column_agent=j;  
         
         row_agent=i;          // ubicamos al agente en la matriz
         column_agent=i;  
         
         //cout <<" i : "<< i <<endl; 
         //cout <<" j : "<< j <<endl;
         
         plot_maze();
         plot_agent();             //  captured_color brings the sensor meassure result
                  
         do
          {  
           i=random(4);     // el agente se mueve a un nuevo estado aleatorio
      
           if(i==0) move_left();
           if(i==1) move_right(); 
           if(i==2) move_up();
           if(i==3) move_down(); 
               
           search_for_MAX();
           max=MAX;
               
           Q[row_agent][column_agent]= R[row_agent][column_agent]+ gamma*max;

           plot_maze();
           plot_agent();                     //  sensor captures color
           delay(1);
           //getch();
         }while(captured_color!=YELLOW);     //  hasta que capture recompensa maxima

        delay(100); 
        episode++;
        system("cls");
        print_R();
        print_Q();         
        cout <<" episode: "<< episode <<endl<<endl;  
    }while(episode<60);  // 40       
   
  salvar_Q();    
         
}     
//---------------------------------------------------------
void Q_exploit(void)  
{
 int i,j,k;    
 int temp; 
 //int max;
    
 randomize(); 
   do
    {
        init_C();
        int rep=0;  //número de pasos que da el agente
         do
         {
          i=random(rows);
          j=random(columns); 
          temp=R[i][j];             
         } while(temp==-1);    // el agente se ubica en estado inicial aleatorio con entrada diferente de -1   
 
         row_agent = i;
         column_agent = j;  
         plot_maze();
         plot_agent();
                  
         do
          { 
           search_for_MAX();       
           i = grad_pointer;          // el agente se mueve a un nuevo estado
           
           if(i==0) move_left();
           if(i==1) move_right(); 
           if(i==2) move_up();
           if(i==3) move_down();

           if(C[row_agent][column_agent] > 15){ //si ha pasado mucho por la misma casilla
               int cont = 0;
               do{
                   k = random(4);
                   if(k==0) move_left();
                   if(k==1) move_right(); 
                   if(k==2) move_up();
                   if(k==3) move_down();
                   cont++;
                }while(cont < 10);
            }

           plot_maze();
           plot_agent();                     //  sensor captures color
           delay(31);
           rep++;
         }while(captured_color!=YELLOW && rep < 200);     //hasta que capture recompensa maxima o haya tardado mucho

        print_S(); 
        print_C(); 
        delay(1000); 
    }while(1);      
    
    //cout <<" one problem solved-- " <<endl;    
}  
//--------------------------------------------------------

