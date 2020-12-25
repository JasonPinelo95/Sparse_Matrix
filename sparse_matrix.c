#include <stdio.h>
#include <stdlib.h>

/*Linked List Node Structure*/

struct listNode{
    int info;
    int row;
    int column;
    struct listNode* nextRow;
    struct listNode* nextColumn;
};

/* PROTOTYPES */
void createMatrix(struct listNode** startPtr, int rows, int columns);
void addRowNode(struct listNode* startPtr, int row, int column, int info);
void addColNode(struct listNode* startPtr, int row, int column, int info);
void insert(struct listNode* startPtr,int row, int column, int info);
void printRow(struct listNode* startPtr, int row, int number_columns);
void printMatrix(struct listNode* startPtr, int number_rows,int number_columns);
int delete(struct listNode* startPtr,int row, int column);
int locate(struct listNode* startPtr,int row, int column);
int assign(struct listNode* startPtr, int row, int column, int info);
int read(struct listNode* startPtr, int row, int column);
struct listNode* sum(struct listNode* startPtr_0,struct listNode* startPtr_1,int* size_0,int* size_1);
struct listNode* product(struct listNode* startPtr_0,struct listNode* startPtr_1,int* size_0,int* size_1);

int main(void){
    struct listNode** startPtr=NULL;
    struct listNode* startPtr_0=NULL;
    struct listNode* startPtr_1=NULL;
    struct listNode* sum_startPtr=NULL;
    struct listNode* prod_startPtr=NULL;
    int size_0[2]={}; // Size of the first matrix
    int size_1[2]={}; // Size of the second matrix
    int* size; //Auxiliar pointer that I use to point the size(array)
    int option; 
    int row, column, info; //Parametros a pasar a la funcion insert
    int select_matrix;

    /*First Matrix*/
    printf("***ENTER THE SIZE FOR THE FIRST MATRIX***\n\n");
    printf("Enter the number of rows: "); scanf(" %d,",size_0);
    printf("Enter the number of columns: "); scanf(" %d",size_0+1);
    createMatrix(&startPtr_0,size_0[0],size_0[1]);

    /*Second Matrix*/
    printf("***ENTER THE SIZE FOR THE SECOND MATRIX***\n\n");
    printf("Enter the number of rows: "); scanf(" %d,",size_1);
    printf("Enter the number of columns: "); scanf(" %d",size_1+1);
    createMatrix(&startPtr_1,size_1[0],size_1[1]);

    do{ 
        printf("Which Matrix: "); scanf(" %d",&select_matrix);
        if(select_matrix==1){
            startPtr=&startPtr_0;
            size=size_0;
        }
        if(select_matrix==2){
            startPtr=&startPtr_1;
            size=size_1;
        }

        printf("\t\t\t\t**SPARSE MATRIX**\n\n");
        printf("\t\tOPTIONS\n\n");
        printf("\t\t1 - Print Matrix\n");
        printf("\t\t2 - Insert an element\n");
        printf("\t\t3 - Delete an element\n");
        printf("\t\t4 - Assign info\n");
        printf("\t\t5 - Read Info\n");
        printf("\t\t6 - Exit\n\n");
        printf("\t\tEnter your option: "); scanf(" %d",&option);
        printf("\n");
        if(option<1 || option>6) printf("No valid option!!\n");
        if(option==1) printMatrix(*startPtr,size[0],size[1]);
        if(option==2){ 
            printf("Enter porsition (row,column): "); scanf(" %d,%d",&row,&column);
            if(row>size[0] || column>size[1]){
                printf("Out of range!\n");
            }
            else if(locate(*startPtr,row,column)==1){
                printf("There is an element in that position use [Assign] to change its value\n");
            }
            else{
            printf("Enter the data: "); scanf(" %d",&info);
            insert(*startPtr,row,column,info);  
            }
        }
        if(option==3){
            printf("Enter porsition (row,column): "); scanf(" %d,%d",&row,&column);
            if(row>size[0] || column>size[1]){
                printf("Out of range!\n");
            }
            else if(locate(*startPtr,row,column)==0){
                printf("There is no element in that position\n");
            }
            else{
                printf("Deleted value: %d\n",delete(*startPtr,row,column));
            }
        }
        if(option==4){
            printf("Enter porsition (row,column): "); scanf(" %d,%d",&row,&column);
            if(row>size[0] || column>size[1]){
                printf("Out of range!\n");
            }
            else{
                printf("Enter the data: "); scanf(" %d",&info);
                if(assign(*startPtr,row,column,info)==0)
                    printf("Node does not exist");
            }
            
        }

        if(option==5){
            printf("Enter porsition (row,column): "); scanf(" %d,%d",&row,&column);
            if(row>size[0] || column>size[1]){
                printf("Out of range!\n");
            }
            else{
                printf("Data: %d\n",read(*startPtr,row,column));
            }

        }

        printf("\n");
        printf("Press [Enter] key to continue.\n");
        while(getchar()!='\n');
        getchar(); 
        system("clear");
    } while(option!=6);

    //GENERATING SUM
    
    printf("***SUM OF MATRIXES***\n");
    sum_startPtr=sum(startPtr_0,startPtr_1,size_0,size_1);
    if(sum_startPtr!=NULL)
        printMatrix(sum_startPtr,size_0[0],size_0[1]);

    //GENERATING MULT

    printf("***MATRIX PRODUCT***\n");
    prod_startPtr=product(startPtr_0,startPtr_1,size_0,size_1);
    if(prod_startPtr!=NULL)
        printMatrix(prod_startPtr,size_0[0],size_1[1]);
        

    return 0;
}

void addRowNode(struct listNode* startPtr, int row, int column, int info){
    /*This function adds an element in the same ROW*/

    struct listNode* currentPtr=startPtr;
    struct listNode* newNode=malloc(sizeof(struct listNode));
    if(newNode==NULL){
        printf("%d not inserted. No memory available. \n", info);
        return;}

    newNode->info=info;
    newNode->row=row;
    newNode->column=column;
    newNode->nextRow=newNode;
    newNode->nextColumn=newNode;

    while(currentPtr->nextColumn!=startPtr)  //Searching the last node in row
        currentPtr=currentPtr->nextColumn;

    currentPtr->nextColumn=newNode;
    newNode->nextColumn=startPtr;

}

void addColNode(struct listNode* startPtr, int row, int column, int info){
    /*This function adds an element in the same column*/

    struct listNode* currentPtr=startPtr;
    struct listNode* newNode=malloc(sizeof(struct listNode));
    if(newNode==NULL){
        printf("%d not inserted. No memory available. \n", info);
        return;}

    newNode->info=info;
    newNode->row=row;
    newNode->column=column;
    newNode->nextRow=newNode;
    newNode->nextColumn=newNode;

    while(currentPtr->nextRow!=startPtr) //Searching the last node in column
        currentPtr=currentPtr->nextRow;

    currentPtr->nextRow=newNode;
    newNode->nextRow=startPtr;    
}

void createMatrix(struct listNode** startPtr, int rows, int columns ){
    if(*startPtr!=NULL){                                    //Validates that there is no currently a            
        printf("Not possible to create a new matrix");      // a matrix
        return;
    }
    
    int i; //Auxiliar variable to be used in the for loops
           // that are going to create the extra row and column
    struct listNode* headPtr=malloc(sizeof(struct listNode));

    if(headPtr==NULL){
        printf("No memory available. \n");
        return;}
    
    headPtr->row=0;            //initializing values
    headPtr->column=0;
    headPtr->nextRow=headPtr;
    headPtr->nextColumn=headPtr;
    
    *startPtr=headPtr; //Linking startPtr with head of matrix, that is the element 0,0

    for(i=1;i<=columns;i++){
        addRowNode(*startPtr,0,i,0);
    }

    for(i=1;i<=rows;i++){
        addColNode(*startPtr,i,0,0);
    }
}

void insert(struct listNode* startPtr,int row, int column, int info){
    //Agregar validaciones para cuando el elemento ya existe o para cuando 
    //la fila o columna estan fuera del rango!!!!!!!!!!!!!!!!1!!!!!

    struct listNode* newNode=malloc(sizeof(struct listNode));
    struct listNode* currentPtr;
    struct listNode* rowPtr=startPtr;  //puntero para guardar la cabecera de la fila
    struct listNode* colPtr=startPtr;  //puntero para guardar la cabecera de la columna
    int i;
    /* Variables auxiliares para guardar las direcciones que se van a modificar*/
    struct listNode* previousNextRowPtr;
    struct listNode* previousNextColPtr;

    if(newNode==NULL){
        printf("%d not inserted. No memory available. \n", info);
        return;}
    
    newNode->info=info;
    newNode->row=row;
    newNode->column=column;
    newNode->nextRow=NULL;
    newNode->nextColumn=NULL;

    for(i=1;i<=row;i++) //buscame la fila en la que quiero poner mi nodo
        rowPtr=rowPtr->nextRow; //un poco innecesario usar rowPtr, puede usar el mismo currentPtr

    for(i=1;i<=column;i++)
        colPtr=colPtr->nextColumn;

    
    //Aquí ya tengo las cabeceras de la fila y la columna;

    currentPtr=rowPtr; //while para posicionarme en el elemento anterior de la fila
    
    while((currentPtr->nextColumn)->column<column && currentPtr->nextColumn!=rowPtr){ 
        currentPtr=currentPtr->nextColumn;
    }

    //Conectando con la fila

    previousNextColPtr=currentPtr->nextColumn;
    currentPtr->nextColumn=newNode;
    newNode->nextColumn=previousNextColPtr;

    currentPtr=colPtr; //while para posicionarme en el elemento anterior de la col

    while((currentPtr->nextRow)->row<row && currentPtr->nextRow!=colPtr){
        currentPtr=currentPtr->nextRow;
    }

    //Conectando con la columna

    previousNextRowPtr=currentPtr->nextRow;
    currentPtr->nextRow=newNode;
    newNode->nextRow=previousNextRowPtr;
}

void printRow(struct listNode* startPtr, int row, int number_columns){

    struct listNode* rowPtr=startPtr;
    struct listNode* currentPtr;
    int i;
    int j;

    for(i=1;i<=row;i++) //buscame la fila que quiero imprimir
        rowPtr=rowPtr->nextRow;

    if(rowPtr->nextColumn==rowPtr){ //Si esta vacía la fila imprimeme puros espacios vacios y termina
        for(i=1;i<=number_columns;i++)
            printf("_ ");
        printf("\n");
        return;
    }

    currentPtr=rowPtr->nextColumn;
    i=1; //ahora mi contador me va a servir para contar los nodos en la fila

    while(currentPtr!=rowPtr){
        if(currentPtr->column>i){                 //Estas lineas me sirven para imprimir los espacios
            for(j=i;j<currentPtr->column;j++){     //vacios que esten antes del numero a imprimir
                printf("_ ");       
                i++;
            }
        }                                         //
        
        printf("%d ", currentPtr->info);
        i++;

        if(currentPtr->nextColumn==rowPtr){       //Lo mismo pero para los vacios despues;
            for(j=currentPtr->column;j<number_columns;j++){
                printf("_ ");
            }
        }

        currentPtr=currentPtr->nextColumn;   
    }
    printf("\n");
}

void printMatrix(struct listNode* startPtr, int number_rows,int number_columns){
    int i;
    for(i=1;i<=number_rows;i++){
        printRow(startPtr,i,number_columns);
    }
}

int delete(struct listNode* startPtr,int row, int column){
    struct listNode* DeletedPtr;
    struct listNode* currentPtr;
    struct listNode* rowPtr=startPtr;  //puntero para guardar la cabecera de la fila
    struct listNode* colPtr=startPtr;  //puntero para guardar la cabecera de la columna
    int i;
    int deleted_value;
    /* Variables auxiliares para guardar las direcciones que se van a modificar*/

    for(i=1;i<=row;i++) //buscame la fila del nodo que quiero eliminar
        rowPtr=rowPtr->nextRow;

    for(i=1;i<=column;i++) //buscame la columna del nodo que quiero eliminar
        colPtr=colPtr->nextColumn;
    
    // Posicioname en el nodo anterior de la fila para modificar sus apuntadores

    currentPtr=rowPtr;

    while((currentPtr->nextColumn)->column!=column){
        currentPtr=currentPtr->nextColumn;
    }
    
    DeletedPtr=currentPtr->nextColumn;
    currentPtr->nextColumn=DeletedPtr->nextColumn; //asgine el apuntador next column al nodo anterior

    // Posicioname en el nodo anterior de la columna para modificar sus apuntadores

    currentPtr=colPtr;

    while((currentPtr->nextRow)->row!=row){
        currentPtr=currentPtr->nextRow;
    }

    currentPtr->nextRow=DeletedPtr->nextRow;

    deleted_value=DeletedPtr->info; //guardo el valor que quiero borrar antes de borrar

    free(DeletedPtr);

    return(deleted_value);
}

int locate(struct listNode* startPtr,int row, int column){
    struct listNode* rowPtr=startPtr;  //puntero para guardar la cabecera de la fila
    struct listNode* currentPtr;
    int i;

    for(i=1;i<=row;i++) //buscame la fila del nodo que quiero encontrar
        rowPtr=rowPtr->nextRow;

    currentPtr=rowPtr;

    while(currentPtr->nextColumn!=rowPtr){
        if((currentPtr->nextColumn)->column==column){
            return(1);
        }
        currentPtr=currentPtr->nextColumn;
    }

    return(0);    
}

int assign(struct listNode* startPtr, int row, int column, int info){
    if(locate(startPtr,row,column)==0)
        return 0;
    
    struct listNode* rowPtr=startPtr;  //puntero para guardar la cabecera de la fila
    struct listNode* currentPtr;
    int i;

    for(i=1;i<=row;i++) //buscame la fila del nodo que quiero encontrar
        rowPtr=rowPtr->nextRow;
    
    currentPtr=rowPtr;

    while(currentPtr->column!=column)
        currentPtr=currentPtr->nextColumn;
    
    currentPtr->info=info;

    return(1);
}

int read(struct listNode* startPtr, int row, int column){
    if(locate(startPtr,row,column)==0)
        return 0;
    
    struct listNode* rowPtr=startPtr;  //puntero para guardar la cabecera de la fila
    struct listNode* currentPtr;
    int i;

    for(i=1;i<=row;i++) //buscame la fila del nodo que quiero encontrar
        rowPtr=rowPtr->nextRow;
    
    currentPtr=rowPtr;

    while(currentPtr->column!=column)
        currentPtr=currentPtr->nextColumn;
    
    return(currentPtr->info);

}

struct listNode* sum(struct listNode* startPtr_0,struct listNode* startPtr_1,int* size_0,int* size_1){
    //Validar que las matrices sean del mismo tamaño
    if(*(size_0)!=*(size_1) || *(size_0+1)!=*(size_1+1)){
        printf("Incompatibale Matrixes to sum\n");
        return NULL;
    }

    struct listNode* startPtr=NULL;
    int i,j,suma;

    createMatrix(&startPtr,*(size_0),*(size_0+1));
    for(i=1;i<=*(size_0);i++){
        for(j=1;j<=*(size_0+1);j++){
            suma=read(startPtr_0,i,j)+read(startPtr_1,i,j);
            if(suma!=0){
                insert(startPtr,i,j,suma);
            }
        }
    }

    return(startPtr);
}

struct listNode* product(struct listNode* startPtr_0,struct listNode* startPtr_1,int* size_0,int* size_1){
    if(*(size_0+1)!=*(size_1)){
        printf("Incompatible Matrixes to mult\n");
        return NULL;
    }

    struct listNode* startPtr=NULL;
    int i,j,k,suma;
    createMatrix(&startPtr,*(size_0),*(size_1+1));
    for(i=1;i<=*(size_1+1);i++){
        for(j=1;j<=*(size_0);j++){
            suma=0;
            for(k=1;k<=*(size_0+1);k++){
                suma+=read(startPtr_0,j,k)*read(startPtr_1,k,i);
            }
            if(suma!=0)
                insert(startPtr,j,i,suma);    
        }
    }

    return(startPtr);

}
