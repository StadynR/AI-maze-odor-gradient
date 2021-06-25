void maze_1(void){
   int i,j,k;
   for (j=0; j<files;j++)
    for (i=0; i<columns; i++)
    {
     R[j][i]=random(2)-1; 
    }    
}

//-------------------------------------------------------
 
void maze_2(void){
   int i,j,k;
   for (j=0; j<files;j++)
    for (i=0; i<columns; i++)
    {
     R[j][i]=random(2)-1; 
    }    
}

//-------------------------------------------------------
 
void maze_3(void){
   int i,j,k;
   for (j=0; j<files;j++)
    for (i=0; i<columns; i++)
    {
     R[j][i]=random(2)-1; 
    }    
}

//-------------------------------------------------------
 
void random_chees(void){
    do{
        aux_x = random(files);
        aux_y = random(columns);
        if(R[aux_x][aux_y]==0){
            R[aux_x][aux_y] = 100;   
            //captured_chees++;
        }
    }while(R[aux_x][aux_y]<0);
} 


void init_R(void)
{
   int k;
   k = random(3);

   if (k == 0) maze_1();
   else if( k == 1) maze_2();
   else maze_3();
   random_chees(); //fill cheeses

}

