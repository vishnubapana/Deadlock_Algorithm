/***************************************************************************
* File:        main.c
* Author:      Venkata Bapanapalli
* Procedures:
*   request_matrix    - opens the request matrix file and puts the matrix
*                       into a 2d dynamic array.
*   allocation_matrix - opens the allocation matrix file and puts the matrix
*                       into a 2d dynamic array.
*   resource_vector   - opens the resource vector file and puts the vector
*                       into a dynamic array.
*   available_vector  - opens the available vector file and puts the vector
*                       into a dynamic array.
*   main              - runs the deadlock algorithm using the matrices and
*                       vectors, and prints what processes are deadlocked.
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/***************************************************************************
* void request_matrix(int ** mat, int row, int col)
* Author:       Venkata Bapanapalli
* Date:         8 March 2020
* Description:  Reads the request matrix file and populates a dynamic 2d 
*               array with the contents from the file.
*
* Parameters:
*   mat    I/P    int**  A dynamic 2d array, holds file contents.
*   row    I/P    int    Number of rows(processes) passed on command line.
*   col    I/P    int    Number of colunms(resources) passed on command line.
**************************************************************************/
void request_matrix(int ** mat, int row, int col)
{
    int i,j;
    char name[20];
    printf("\nEnter the request matrix file name: \n");  //get file name from user
    scanf("%s", name);
    FILE *file;
    file=fopen(name, "r");                               //opens file as read only
    for(i = 0; i < row; i++)                             //traverse through the rows
    {
        for(j = 0; j < col; j++)                         //traverse trough the columns
        {
            if (!fscanf(file, "%d", &mat[i][j]))         //check for data in file and put into matrix
                break;
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    fclose(file);                                        //close file
}
/***************************************************************************
* void allocation_matrix(int ** mat, int row, int col)
* Author:       Venkata Bapanapalli
* Date:         8 March 2020
* Description:  Reads the allocation matrix file and populates a dynamic 2d 
*               array with the contents from the file.
*
* Parameters:
*   mat    I/P    int**  A dynamic 2d array, holds file contents.
*   row    I/P    int    Number of rows(processes) passed on command line.
*   col    I/P    int    Number of colunms(resources) passed on command line.
**************************************************************************/
void allocation_matrix(int ** mat, int row, int col)
{
    int i,j;
    char name[20];
    printf("\nEnter the allocation matrix file name: \n");  //get file name from user
    scanf("%s", name);
    FILE *file;
    file=fopen(name, "r");                                  //opens file as read only           
    for(i = 0; i < row; i++)                                //traverses through the rows
    {
        for(j = 0; j < col; j++)                            //traverses through the columns
        {
            if (!fscanf(file, "%d", &mat[i][j]))            //check for data in file and put into matrix
                break;

            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    fclose(file);                                           //close file
}
/***************************************************************************
* void resource_vector(int* mat, int col)
* Author:       Venkata Bapanapalli
* Date:         8 March 2020
* Description:  Reads the resource vector file and populates a dynamic 
*               array with the contents from the file.
*
* Parameters:
*   mat    I/P    int*  A dynamic array, holds file contents.
*   col    I/P    int   Number of colunms(resources) passed on command line.
**************************************************************************/
void resource_vector(int* mat, int col)
{
    int i;
    char name[20];
    printf("\nEnter the resource vector file name: \n");  //get file name from user
    scanf("%s", name);
    FILE *file;
    file = fopen(name,"r");                               //opens file as ready only
    for(i = 0; i < col; ++i)                              //traverses through the columns
    {
        if (!fscanf(file, "%d", &mat[i]))                 //check for data in file and put into vector
            break;
        printf("%d ", mat[i]);
    }
    printf("\n");
    fclose(file);                                          //closes file
}
/***************************************************************************
* void available_vector(int* mat, int col)
* Author:       Venkata Bapanapalli
* Date:         8 March 2020
* Description:  Reads the available vector file and populates a dynamic 
*               array with the contents from the file.
*
* Parameters:
*   mat    I/P    int*  A dynamic array, holds file contents.
*   col    I/P    int   Number of colunms(resources) passed on command line.
**************************************************************************/
void available_vector(int* mat, int col)
{
    int i;
    char name[20];
    printf("\nEnter the available vector file name: \n");  //get file name from user
    scanf("%s", name);
    FILE *file;
    file = fopen(name,"r");                                //opens file as read only
    for(i = 0; i < col; ++i)                               //traverses through the columns
    {
        if (!fscanf(file, "%d", &mat[i]))                  //check for data in file as put into vector
            break;
        printf("%d ", mat[i]);
    }
    printf("\n");
    fclose(file);                                          //closes file
}
/***************************************************************************
* int main(int argc, char *argv[])
* Author:       Venkata Bapanapalli
* Date:         8 March 2020
* Description:  Creates 2 matrices for request and allocation, creates 2 
*               vectors for resource and available. Using functions populate
*               the matricies and vectors, and then use them to perform the 
*               deadlock algorithm.
*
* Parameters:
*   argc    I/P    int      Number of arguments on the command line.
*   argv    I/P    char *[] The arguments on the command line.
**************************************************************************/
int main(int argc, char *argv[])                          
{
    int i,j;
    int row = atoi(argv[1]);                         //first command line argument for number of processes
    int col = atoi(argv[2]);                         //second command line argument for number of resources
    int tot = row*col;
    int** req = malloc(tot*sizeof(int*));            //request matrix dynamic 2d array
    int** all = malloc(tot*sizeof(int*));            //allocation matrix dynamic 2d array
    int* res = malloc(tot*sizeof(int));              //resource vector dynamic array
    int* ava = malloc(tot*sizeof(int));              //available vector dynamic array
    int* mark = malloc(tot*sizeof(int));             //marked vector dynamic array
    int* w = malloc(tot*sizeof(int));                //w vector dynamic array
    //sets matrices using malloc function
    for(i=0;i<row;++i)                               
    {
        req[i]=malloc(tot*sizeof(int));
        all[i]=malloc(tot*sizeof(int));
    }
    //calls functions to fill matrices and vectors with data in files
    request_matrix(req, row, col);                   
    allocation_matrix(all, row, col);
    resource_vector(res, col);
    available_vector(ava, col);
    //runs the deadlock algorithm, marks the processes that dont use any resources
    for(i=0;i<row;i++)
    {
        int count=0;
        for(j=0;j<col;j++)
        {
            if(all[i][j]==0)
                count++;
            else
                break;
        }
        if(count==col)
            mark[i]=1;
    }
    //sets w vector equal to available vector
    for(j=0;j<col;j++)
        w[j]=ava[j];
    //determines whether a process can be processed based on 
    //resource size and marks if it can be processed
    for(i=0;i<row;i++)
    {
        int canbeprocessed=0;
        if(mark[i]!=1)
        {
            for(j=0;j<col;j++)
            {
                if(req[i][j]<=w[j])
                    canbeprocessed=1;
                else
                {
                    canbeprocessed=0;
                    break;
                }
            }
            if(canbeprocessed)
            {
                mark[i]=1;

                for(j=0;j<col;j++)
                    w[j]+=all[i][j];
            }
        }
    }
    int deadlock=0;
    //all unmarked processes are considered deadlocked
    for(i=0;i<row;i++)
        if(mark[i]!=1)
        {
            deadlock=1;
            printf("Process %d is deadlocked.\n",(i+1));    //prints the deadlocked processes
        }
    if(deadlock)                                            //prints a statement if no deadlocks are found
        printf("Deadlock(s) detected!\n");
    else
        printf("\n No Deadlocks detected!");
    return 0;
}