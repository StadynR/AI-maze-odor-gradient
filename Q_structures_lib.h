//===========================================================================
//  DEFINICION DE ESTRUCTURAS Q 
//========================================================================
//----------------------------------------------------------------------------------------------------     
void print_R(void)
{
 int i,j;
    
    printf("This is the R Matrix:\n \n");
    for(i = 0; i < files; i++)
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
    for(i = 0; i < files; i++)
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
 float lambda=100;    //  costante de decaimiento con la distancia --- ESTO SE MODIFICA PARA DISMINUIR EL GRADIENTE
 //float N=1.0;         //   N : scent concentration in a given square
 float step=0.01;     // cuanto se avanza en cada loop  
 int k, distx, disty;
 
   for (int i=0; i < files; i++)
   for (int j=0; j < columns; j++)
    S[i][j]=-1;
    
   for (int i=0; i < files; i++)
   for (int j=0; j < columns; j++)
    {
     disty = i-file_cheese;
     distx = j-column_cheese;
     k = sqrt(distx*distx+disty*disty);   // distancia pitagoras a coordenadas (0,0)
     if(R[i][j]!=-1) S[i][j]=100* exp(-lambda*step*k);  // concentracion % a esa distancia
    }   
    //   se consulta a la matriz R por lo tanto el gradiente sigue la ley de las paredes
}
//-------------------------------------------------------------
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
    for(int i = 0; i <= stcont; i++){
        cout << "[" << path[i][0] << ", " << path[i][1] << "] ";
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
    if(temp!=BLACK) // movimiento v??lido
    {  
     x_agent=x_agent-square_size;
     column_agent--;
    }    
}
//--------------------------------------------------------------
void move_right(void)
{
 int temp;   
  temp=getpixel(x_agent+square_size,y_agent);   // revisa cercania a la derecha
  if(temp!=BLACK)
     {
      x_agent=x_agent+square_size;
      column_agent++; 
     }  
}
//-------------------------------------------------------------
void move_up(void)
{
 int temp;
    temp=getpixel(x_agent,y_agent-square_size);   // revisa cercania arriba
    if(temp!=BLACK)
    {
     y_agent=y_agent-square_size;
     file_agent--;
    }  
}
//-------------------------------------------------------------
void move_down(void)
{
 int temp;
   temp=getpixel(x_agent,y_agent+square_size);    // revisa cercania abajo
   if(temp!=BLACK)
   {
    y_agent=y_agent+square_size; 
    file_agent++;
   }   
}
//-------------------------------------------------------------
bool no_unvisited() 
{ 
    bool f = true;
    
    for(int i = 0; i < 4; i++){
        if(sensor[i] != -1){
            f = false; 
            break;
        }
    }
    
    return f;
}
//------------------------------------------------------------
bool already_visited(int row, int col) 
{ 
    bool f = false;
    
    for(int i = 0; i < cont; i++){
        if(visited[i][0] == row && visited[i][1] == col){
            f = true; 
            break;
        }
    }
    
    return f;
}
//--------------------------------------------------------
void search_for_MAX_unvisited(void) 
{
 int i,j, sum = 0, r, lim_l, lim_r;
    
    sensor[0]= S[file_agent][column_agent-1];    // lee  a izquierda
    if(column_agent==0 || already_visited(file_agent, column_agent-1)) sensor[0]=-1;            // desborde a la izquierd  
        
    sensor[1]= S[file_agent][column_agent+1];    // lee a  derecha
    if(column_agent==columns-1 || already_visited(file_agent, column_agent+1)) sensor[1]=-1;
    
    sensor[2]= S[file_agent-1][column_agent];    // lee arriba
    if(file_agent==0 || already_visited(file_agent-1, column_agent)) sensor[2]=-1;
    
    sensor[3]= S[file_agent+1][column_agent];    // lee abjo
    if(file_agent==files-1 || already_visited(file_agent+1, column_agent)) sensor[3]=-1;

    //MAX=sensor[0];
    //for(i=0;i<4;i++) if(sensor[i]>=MAX) {MAX=sensor[i];grad_pointer=i;}  // grad_pointer apunta al maximo valor (no markov)
    
    if(no_unvisited()) MAX = -1;
    else{
        for(i=0;i<4;i++){
        if(sensor[i] != -1)
            sum+=sensor[i];
        }
        if(sum > 1) r = random(sum); else r = 0;
        lim_l = 0;
        for(i=0;i<4;i++){ 
            if(sensor[i]!=-1){
                lim_r = sensor[i] + lim_l;
                if(r >= lim_l && r <= lim_r){
                    MAX=sensor[i];
                    grad_pointer = i;
                    break;
                }
                lim_l = lim_r;
            }
        }
    }
}
//------------------------------------------------------------
void backtrack() 
{ 
    int temp;
    
    //cout << "bfile: " << file_agent << " bcol: " << column_agent << endl;
    
    temp = R[file_agent][column_agent-1];
    if(column_agent == 0) temp = -1;
    if(temp != -1 && file_agent == path[stcont][0] && column_agent-1 == path[stcont][1]){
        //cout << "Backtrack left: " << temp << endl;
        mov = 0;
        return;
    }
    
    temp = R[file_agent][column_agent+1];
    if(column_agent == columns-1) temp = -1;
    if(temp != -1 && file_agent == path[stcont][0] && column_agent+1 == path[stcont][1]){ 
        //cout << "Backtrack right: " << temp << endl;
        mov = 1;
        return;
    }
    
    temp = R[file_agent-1][column_agent];
    if(file_agent == 0) temp = -1;
    if(temp != -1 && file_agent-1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack up: " << temp << endl;
        mov = 2;
        return;
    }
    
    temp = R[file_agent+1][column_agent];
    if(file_agent == files-1) temp = -1;
    if(temp != -1 && file_agent+1 == path[stcont][0] && column_agent == path[stcont][1]){ 
        //cout << "Backtrack down: " << temp << endl;
        mov = 3;
        return;
    }
}
//------------------------------------------------------------
void DFS(){
      
     path[stcont][0] = file_agent;
     path[stcont][1] = column_agent;
     visited[cont][0] = file_agent;
     visited[cont][1] = column_agent;    
    
     search_for_MAX_unvisited();
     if (MAX == -1){
         stcont--;
         cont++;
         backtrack();
     }
     else{
         cont++;
         stcont++;       
         mov = grad_pointer;  // el agente se mueve a un nuevo estado
         }
} 
//-----------------------------------
void random_agent(void){
    int i, j;
    do{
        i = random(files);
        j = random(columns);
        if(R[i][j]==0 || R[i][j]==100){ //if it is not in the wall or in the 
            file_agent=i;           
            column_agent=j;  
        }
    }while(R[i][j]<0); 
} 
//---------------------------------------------------------

void random_cheese(void){
    int i, j;
    do{
        i = random(files);
        j = random(columns);
        if(R[i][j]==0 || R[i][j]==100){ //if it is not in the wall or in the 
            file_cheese=i;           
            column_cheese=j;  
        }
    }while(R[i][j]<0); 
} 
//---------------------------------------------------------
void Q_exploit(void)  
{
    
     randomize(); 

     //plot_maze();
     plot_agent();
     
     clear_visited();
     clear_path();
     cont = 0;
     stcont = 0;
              
     do
      {
          
       DFS();
        
       plot_trail();              
       if(mov==0) move_left();
       if(mov==1) move_right(); 
       if(mov==2) move_up();
       if(mov==3) move_down();
       
       //plot_maze();
       plot_agent();                     //  sensor captures color
       if(kbhit())
        {
            key=getch();
            if(key=='P' || key=='p')
                    getch();
        }
       delay(31);
     }while(captured_color!=YELLOW);     //hasta que capture recompensa maxima o haya tardado mucho

    print_visited();
    print_path();
    plot_path();
    print_S();     
    
    //cout <<" one problem solved-- " <<endl;    
}  
//--------------------------------------------------------

