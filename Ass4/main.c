#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    int i;
    Grid_T g;


    g = sudoku_read();
    sudoku_print(stdout, g);

    return 0;
}
