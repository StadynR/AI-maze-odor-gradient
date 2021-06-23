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
     k = sqrt(i*i+j*j);   // distancia pitagoras a coordenadas (0,0)
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
//------------------------------------------------------------
void print_visited(){
    cout << "Visited: ";
    for(int i = 0; i <= cont; i++){
        cout << "[" << visited[i][0] << ", " << visited[i][1] << "] ";
    }
    cout << endl;
}
//------------------------------------------------------------
void print_path(){
    cout << "Path: ";
    for(int i = 0; i <= cont; i++){
        cout << "[" << path[i][0] << ", " << path[i][1] << "] ";
    }
    cout << endl;
}
//------------------------------------------------------------
void print_unvisited(){
    cout << "Unvisited: ";
    for(int i = 0; i < 4; i++){
        cout << "[" << unvisited[i][0] << ", " << unvisited[i][1] << "] ";
    }
    cout << endl;
}
//------------------------------------------------------------
void clear_visited(){
    for(int i = 0; i <= cont; i++){
        visited[i][0] = -1;
        visited[i][1] = -1;
    }
}
//------------------------------------------------------------
void clear_path(){
    for(int i = 0; i <= stcont; i++){
        path[i][0] = -1;
        path[i][1] = -1;
    }
}
//------------------------------------------------------------
void move_left(void)
{
 int temp;
    temp=getpixel(x_agent-square_size,y_agent);   // revisa cercania a la izquierda
    if(temp==4||temp==14||temp==12) // movimiento v�lido
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
  if(temp==4||temp==14||temp==12)
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
    if(temp==4||temp==14||temp==12)
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
   if(temp==4||temp==14||temp==12)
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
//-------------------------------------------------------------
void search_for_MAX_unvisited(void) 
{
    int row, col;
    
    for (int i = 0; i < 4; i++)
    {
        row = unvisited[i][0];
        col = unvisited[i][1];
        sensor[i] = S[row][col];    
        if(row==-1 && col==-1) sensor[i]=-1; 
    }

    MAX=sensor[0];
    for(int i = 0; i < 4; i++) if(sensor[i] >= MAX) { MAX=sensor[i];grad_pointer=i; }  // grad_pointer apunta al maximo valor
}
//-------------------------------------------------------------
bool not_visited(int row, int col) 
{ 
    bool f = true;
    
    for(int i = 0; i < cont; i++){
        if(visited[i][0] == row && visited[i][1] == col)
            f = false;
    }
    
    return f;
}
//-------------------------------------------------------------
void get_unvisited_neighbors() 
{ 
    no_unvisited = true;
    int temp;
    
    //cout << "row: " << row_agent << " col: " << column_agent << endl;
    
    temp = R[row_agent][column_agent-1];
    if(column_agent == 0) temp = -1;
    if(temp != -1 && not_visited(row_agent, column_agent-1)){
        //cout << "R left: " << temp << endl;
        unvisited[0][0] = row_agent; 
        unvisited[0][1] = column_agent-1; 
        no_unvisited = false;
    }
    
    temp = R[row_agent][column_agent+1];
    if(column_agent == columns-1) temp = -1;
    if(temp != -1 && not_visited(row_agent, column_agent+1)){ 
        //cout << "R right: " << temp << endl;
        unvisited[1][0] = row_agent; 
        unvisited[1][1] = column_agent+1; 
        no_unvisited = false;
    }
    
    temp = R[row_agent-1][column_agent];
    if(row_agent == 0) temp = -1;
    if(temp != -1 && not_visited(row_agent-1, column_agent)){ 
        //cout << "R up: " << temp << endl;
        unvisited[2][0] = row_agent-1; 
        unvisited[2][1] = column_agent;
        no_unvisited = false;
    }
    
    temp = R[row_agent+1][column_agent];
    if(row_agent == rows-1) temp = -1;
    if(temp != -1 && not_visited(row_agent+1, column_agent)){ 
        //cout << "R down: " << temp << endl;
        unvisited[3][0] = row_agent+1; 
        unvisited[3][1] = column_agent; 
        no_unvisited = false;
    }

}
//------------------------------------------------------------
void backtrack() 
{ 
    int temp;
    
    //cout << "brow: " << row_agent << " bcol: " << column_agent << endl;
    
    temp = R[row_agent][column_agent-1];
    if(column_agent == 0) temp = -1;
    if(temp != -1 && row_agent == path[stcont][0] && column_agent-1 == path[stcont][1]){
        //cout << "Backtrack left: " << temp << endl;
        mov = 0;
        return;
    }
    
    temp = R[row_agent][column_agent+1];
    if(column_agent == columns-1) temp = -1;
    if(temp != -1 && row_agent == path[stcont][0] && column_agent+1 == path[stcont][1]){ 
        //cout << "Backtrack right: " << temp << endl;
        mov = 1;
        return;
    }
    
    temp = R[row_agent-1][column_agent];
    if(row_agent == 0) temp = -1;
    if(temp != -1 && row_agent-1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack up: " << temp << endl;
        mov = 2;
        return;
    }
    
    temp = R[row_agent+1][column_agent];
    if(row_agent == rows-1) temp = -1;
    if(temp != -1 && row_agent+1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack down: " << temp << endl;
        mov = 3;
        return;
    }
}
//------------------------------------------------------------
void DFS(){
        
     for(int i = 0; i < 4; i++){
         unvisited[i][0] = -1;
         unvisited[i][1] = -1;
     }
     //cout << "Stack pos: " << stcont << " , row: " << row_agent << " , col: " << column_agent << endl;
     //print_visited();
     get_unvisited_neighbors();
     //print_unvisited();
     if(no_unvisited){
         stcont--;
         cont++;
         visited[cont][0] = path[stcont][0];
         visited[cont][1] = path[stcont][1];
         
         backtrack();
         
         //plot_trail();
     }
     else{
         cont++;
         stcont++;
         search_for_MAX_unvisited();       
         mov = grad_pointer;          // el agente se mueve a un nuevo estado
         path[stcont][0] = unvisited[mov][0];
         path[stcont][1] = unvisited[mov][1];
         visited[cont][0] = unvisited[mov][0];
         visited[cont][1] = unvisited[mov][1];
             
         //plot_trail();
         }
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
        int rep=0;  //n�mero de pasos que da el agente
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
         
         clear_visited();
         clear_path();
         cont = 0;
         stcont = 0;
           
         path[stcont][0] = row_agent;
         path[stcont][1] = column_agent;
         visited[cont][0] = row_agent;
         visited[cont][1] = column_agent;
                  
         do
          { 
           
           DFS();

           /*if(C[row_agent][column_agent] > 15){ //si ha pasado mucho por la misma casilla
               int cont = 0;
               do{
                   k = random(4);
                   if(k==0) move_left();
                   if(k==1) move_right(); 
                   if(k==2) move_up();
                   if(k==3) move_down();
                   cont++;
                }while(cont < 10);
            }*/
           if(mov==0) move_left();
           if(mov==1) move_right(); 
           if(mov==2) move_up();
           if(mov==3) move_down(); 
              
           plot_maze();
           plot_agent();                     //  sensor captures color
           delay(31);
           rep++;
         }while(captured_color!=YELLOW && rep < 200);     //hasta que capture recompensa maxima o haya tardado mucho

        print_visited();
        print_S(); 
        print_C(); 
        delay(1000);
        //getch();
    }while(1);      
    
    //cout <<" one problem solved-- " <<endl;    
}  
//--------------------------------------------------------
