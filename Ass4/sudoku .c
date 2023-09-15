/*
 *	Minos Stavrakakis - csd4120
 *	HY255 - Software Lab 2019
 *	Assignment 4
 */


#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <unistd.h>
#include <string.h>


/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
Grid_T sudoku_read(void)
{
    Grid_T newgr;
    int i=0,j,n;
    while(i<9){
        j = 0;
        while(j<9){
            scanf("%d",&n);
            grid_update_value(&newgr, i, j, n);
                j++;
        }
        if(j==9)
            i++;
    }
    return newgr;
}


/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g)
{
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            fprintf(s, "%d ", grid_read_value(g, i, j));
        }
        fprintf(s, "\n");
    }
}

/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g)
{
    int i,j,flag[10],n,k,l,zero=0;
    /*Row, Col check*/
    for(i=0;i<9;i++){
        /*Checking for duplicates in row*/
        for(j=1;j<10;j++)
            flag[j] = 0;

        for(j=0;j<9;j++){
            n = grid_read_value(g,i,j);
            if((flag[n]!=0)&&(n!=0)){
                fprintf(stderr,"Error: Duplicate emergence of "
                  "%d in row %d, col %d \n", n, i, j);
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
            /*added to flag unsolved sudoku*/
            } else if(n==0) {
                zero=1;
            }
        }
        /*Checking for duplicates in col*/
        for(j=1;j<10;j++)
            flag[j] = 0;

        for(j=0;j<9;j++){
            n = grid_read_value(g,j,i);
            if((flag[n]!=0)&&(n!=0)){
                fprintf(stderr,"Error: Duplicate emergence of "
                  "%d in row %d, col %d \n", n, j, i);
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
            /*added to flag unsolved sudoku*/
            } else if(n==0) {
                zero=1;
            }
        }
    }

    /*Subgrid check, traversing through each of 9*/
    for(i=0;i<9;i+=3){
      for(j=0;j<9;j+=3){

        /*Zeroing flag array with k this time, j is in use*/
        for(k=1;k<10;k++)
            flag[k] = 0;

        /*traversing through each of subgrid squares*/
        for(k=i;k<i+3;k++){
          for(l=j;l<j+3;l++){
              n = grid_read_value(g,k,l);
              if((flag[n]!=0)&&(n!=0)){
                fprintf(stderr,"Error: Duplicate emergence of "
                  "%d in subgrid %d,%d \n", n, i/3, j/3);
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
            }
          }
        }
      }
    }

    if(flag[0]==0)
        fprintf(stderr,"\nSudoku has no errors\n");

    if(zero)
        fprintf(stderr,"\nSudoku is unresolved\n");
    return;
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g)
{
    int i,j,flag[10],n,k,l;
    /*Row, Col check*/
    for(i=0;i<9;i++){
        /*Checking for duplicates in row*/
        for(j=1;j<10;j++)
            flag[j] = 0;

        for(j=0;j<9;j++){
            n = grid_read_value(g,i,j);
            if((flag[n]!=0)&&(n!=0)){
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
            /*added to flag unsolved sudoku*/
            } else if(n==0) {
                flag[0]=1;
            }
        }
        /*Checking for duplicates in col*/
        for(j=1;j<10;j++)
            flag[j] = 0;

        for(j=0;j<9;j++){
            n = grid_read_value(g,j,i);
            if((flag[n]!=0)&&(n!=0)){
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
             /*added to flag unsolved sudoku*/
            } else if(n==0) {
                flag[0]=1;
            }
        }
    }

    /*Subgrid check, traversing through each of 9*/
    for(i=0;i<9;i+=3){
      for(j=0;j<9;j+=3){

        /*Zeroing flag array with k this time, j is in use*/
        for(k=1;k<10;k++)
            flag[k] = 0;

        /*traversing through each of subgrid squares*/
        for(k=i;k<i+3;k++){
          for(l=j;l<j+3;l++){
              n = grid_read_value(g,k,l);
              if((flag[n]!=0)&&(n!=0)){
            /*flag[0] used as universal flag*/
                flag[0]=1;
            } else if(n!=0) {
                flag[n] = 1;
            }
          }
        }
      }
    }

    if(flag[0]==0)
      return 1;
    else
      return 0;
}

/* Generates possible choices for each blank(0) elmt taking into
   account the row, col and subgrid on which, elmt is placed */
static void sudoku_init_choices(Grid_T *g)
{
    int i,j,n,sgrid[9],k,l;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){

            if(grid_read_value(*g,i,j)==0){
                /*initialize elmt having every choice available*/
                for(n=1;n<10;n++)
                    grid_set_choice(g,i,j,n);
                grid_set_count(g,i,j);

                /*creating appropriate subgrid*/
                n=0;
                for(k=i-(i%3);k<(i-(i%3))+3;k++){
                  for(l=j-(j%3);l<(j-(j%3))+3;l++){
                    sgrid[n++] = grid_read_value(*g,k,l);
                  }
                }

                /*eliminate choices apearing in same row, col
                  and subgrid*/
                for(n=0;n<9;n++){
                    grid_remove_choice(g,i,j,grid_read_value(*g,i,n));
                    grid_remove_choice(g,i,j,grid_read_value(*g,n,j));
                    grid_remove_choice(g,i,j,sgrid[n]);
                }

            } else {
                grid_clear_count(g,i,j);
                for(n=1;n<10;n++){
                    grid_clear_choice(g,i,j,n);
                }
            }

        }
    }
}

/* Returns a possible unique choice */
static int sudoku_try_next(Grid_T g, int *row, int *col)
{
    int i,j,n,ccnt=10;
    srand(getpid());

    /*finding numbeer of least possible choices*/
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(ccnt>grid_read_count(g, i, j) &&
          grid_read_count(g, i, j)!=0)
            ccnt = grid_read_count(g, i, j);
      }
    }

    /*search randomly for an element w least possible choices*/
    while(ccnt!=10){
        i = rand()%9;
        j = rand()%9;
        if(grid_read_count(g, i, j)==ccnt){
            while(1){
                /*choose randomly from available choices*/
                n = (rand()%9)+1;
                if(grid_choice_is_valid(g, i, j, n)){
                    *row = i;
                    *col = j;
                    return n;
                }
            }
        }
    }
    /*case: grid has no available choices*/
    return 0;
}

/* Removes choice n from elt[i][j] and returns number of elt[i][j]
   possible chpoises */
static int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
    grid_remove_choice(g, i, j, n);
    grid_update_value(g, i, j, n);
    return grid_read_count(*g, i, j);
}

/* Eliminates choice n from rest row, col and subgrid*/
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
    int k,l;

    /*eliminate choice from elmt row, col*/
    for(k=0;k<9;k++){
        grid_remove_choice(g, r, k, n);
        grid_remove_choice(g, k, c, n);
    }

    /*eliminate choice from elmt subgrid*/
    for(k=r-(r%3);k<(r-(r%3))+3;k++){
      for(l=c-(c%3);l<(c-(c%3))+3;l++){
          grid_remove_choice(g, k, l, n);
      }
    }
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g)
{
    Grid_T tmp;
    int i,j,n;
    grid_set_unique(&g);

    sudoku_init_choices(&g);

    /*loop stops when no available choices*/
    while((n=sudoku_try_next(g, &i, &j))){

        /*tries next available choice and checks
          if choice was unique (if not 0, not unique*/
        if(sudoku_update_choice(&g,i,j,n)){
            grid_clear_unique(&g);

            tmp = sudoku_solve(g);
            /*check if solved*/
            if(sudoku_is_correct(tmp)){
                return tmp;
            } else {
                /*backtrack to 0 with lesser choices*/
                grid_update_value(&g,i,j,0);
            }

        /* unique choice path */
        } else {

            sudoku_eliminate_choice(&g,i,j,n);
        }
    }
    return g;
}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g)
{
    g = sudoku_solve(g);
    return (grid_read_unique(g));
}

/* Generates a random complete(solved) sudoku */
static Grid_T sudoku_generate_complete(void)
{
    Grid_T g;
    int i,j,k,n,tries=10;
    int legit[81] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,
                      4, 5, 6, 7, 8, 9, 1, 2, 3,
                      7, 8, 9, 1, 2, 3, 4, 5, 6,
                      2, 3, 4, 5, 6, 7, 8, 9, 1,
                      5, 6, 7, 8, 9, 1, 2, 3, 4,
                      8, 9, 1, 2, 3, 4, 5, 6, 7,
                      3, 4, 5, 6, 7, 8, 9, 1, 2,
                      6, 7, 8, 9, 1, 2, 3, 4, 5,
                      9, 1, 2, 3, 4, 5, 6, 7, 8 };

    /*10 tries to produce correct sudoku*/
    while(tries){
      /*zero all elmts*/
      for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            grid_update_value(&g, i, j, 0);
        }
      }
        sudoku_init_choices(&g);
        /*loop stops when no available choices*/
        while((n=sudoku_try_next(g, &i, &j))){

            grid_remove_choice(&g, i, j, n);
            grid_update_value(&g, i, j, n);
            /*remove choice from rest of sudoku*/
            sudoku_eliminate_choice(&g, i, j, n);

        }
        /*returns in case of correct sudoku*/
        if(sudoku_is_correct(g))
            return g;
    tries--;
    }

    /*if it gets here: no successful sudoku generated,
      returns pregenerated sudoku*/
      k=0;
      for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            grid_update_value(&g, i, j, legit[k++]);
        }
      }
      return g;
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. */
Grid_T sudoku_generate(int nelts)
{
    Grid_T g;
    int k,i,j;
    srand(getpid());

    /*assigns g a legit solved sudoku*/
    g = sudoku_generate_complete();
    k = 81-nelts;
    while(k){
        i = rand()%9;
        j = rand()%9;
        /*avoiding already zeroed elmts*/
        if(grid_read_value(g,i,j)!=0){

            grid_update_value(&g,i,j,0);
        }
        k--;
    }
    return g;
}

int main(int argc, char *argv[])
{
    Grid_T g;

    switch(argc){
        case 2:
            if(argv[1][0] == '-' &&
               argv[1][1] == 'c' &&
               argv[1][2] == '\0'){

		printf("New puzzle:\n");
                g = sudoku_read();
                sudoku_print(stderr,g);
                sudoku_print_errors(g);
            } else {printf("Unknown Input\n");}
            break;
        case 3:
            if(argv[1][0] == '-' &&
               argv[1][1] == 'g' &&
               argv[1][2] == '\0'){

                printf("New puzzle:\n");
                sudoku_print(stdout,
                  sudoku_generate(atoi(argv[2])));
            } else {printf("Unknown Input\n");}
            break;
        default:
            g = sudoku_read();
            sudoku_print(stderr,g);
            g = sudoku_solve(g);
            if(!sudoku_is_correct(g)){
                fprintf(stderr,"Sudoku has no solution\n");
            } else {
                if(sudoku_solution_is_unique(g))
                    fprintf(stderr,"Sudoku has unique solution\n");
                else fprintf(stderr,"Sudoku has multiple solutions\n");
            }
            sudoku_print(stderr,g);
    }

    return 0;
}
