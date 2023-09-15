/*
 *	Minos Stavrakakis - csd4120
 *	HY255 - Software Lab 2019
 *	Assignment 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "grid.h"
#include <assert.h>

#if 0
typedef struct grid_s {
  int unique;      /* if 1 after solving, puzzle has unique solution */
  struct {
    int val;       /* value of element i,j */
    struct {
      int count;   /* number of possible choices for element i,j */
      int num[10]; /* map of choices: num[k]==1 if k is a valid choice
                      for element i,j, else num[k]=0 */
    } choices;     /* struct choices is used while solving the
		      puzzle and is otherwise undefined */
  } elts[9][9];    /* sudoku grid elements; 0<=i,j<=9 */
} Grid_T;
#endif


/* update value of i,j to n */
void grid_update_value(Grid_T *g, int i, int j, int n)
{
	assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));
	assert((n>=0)&&(n<=9));

    g->elts[i][j].val = n;

    return;
}


/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j)
{
	/*assert(g);*/
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));

	return g.elts[i][j].val;
}


/* set (to 1) or clear (to 0) choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));
	assert((n>=0)&&(n<=9));

	g->elts[i][j].choices.num[n] = 1;

	return;
}
void grid_clear_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));
	assert((n>=0)&&(n<=9));

	g->elts[i][j].choices.num[n] = 0;

	return;
}


/* true if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n)
{
    /*assert(g);*/
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));
    assert((n>=0)&&(n<=9));

    if(g.elts[i][j].choices.num[n]==1)
        return 1;
    else
        return 0;
}


/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n)
{
    assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));
	assert((n>=0)&&(n<=9));

    if(grid_choice_is_valid(*g, i, j, n)){
        grid_clear_choice(g, i, j, n);
        g->elts[i][j].choices.count--;
    }

    return;
}


/* return count, set (to 9), or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j)
{
    assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));

    return g.elts[i][j].choices.count;
}
void grid_set_count(Grid_T *g, int i, int j)
{
    assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));

	g->elts[i][j].choices.count = 9;

	return;
}
void grid_clear_count(Grid_T *g, int i, int j)
{
    assert(g);
	assert((i>=0)&&(i<9));
	assert((j>=0)&&(j<9));

	g->elts[i][j].choices.count = 0;

	return;
}


/* return val, set (to 1), or clear (to 0) unique flag for g */
int grid_read_unique(Grid_T g)
{
    return g.unique;
}
void grid_set_unique(Grid_T *g)
{
    assert(g);
    g->unique = 1;
    return;
}
void grid_clear_unique(Grid_T *g)
{
    assert(g);
    g->unique = 0;
    return;
}

