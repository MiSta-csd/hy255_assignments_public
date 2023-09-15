/* Minos Stavrakakis - csd4120 */
#include <stdio.h>
#include <stdlib.h>


void initializeISOMatrix(char iso[256][3])
{

    int i;
    char upper[24] = {'A','V','G','D','E','Z','H','8','I','K','L','M','N','K','O','P','R','S','T','Y','F','X','P','W'};
    char lower[24] = {'a','v','g','d','e','z','h','8','i','k','l','m','n','k','o','p','r','s','t','y','f','x','p','w'};

    /* initialize all matrix elements */
    for(i=0;i<256;i++){
        iso[i][0] = (char) i;
        iso[i][1] = '\0';
        iso[i][2] = '\0';
    }

    /* match greek capital letters */
    for(i=193;i<210;i++){
        iso[i][0] = upper[i-193];
    }
    /* skipping (dec) 210 position of ISO8859-7 | "empty" */
    for(i=211;i<218;i++){
        iso[i][0] = upper[i-194];
    }


    /* match greek lowercase letters */
    for(i=225;i<242;i++){
        iso[i][0] = lower[i-225];
    }
    /* matching (dec) 242 position of ISO8859-7 | "sigma final" */
    iso[242][0] = 's';
    /* matching rest of greek lowercase letters */
    for(i=243;i<250;i++){
        iso[i][0] = lower[i-226];
    }


    /* match greek XI/xi & PSI/psi */
    iso[206][1] = 'S';
    iso[238][1] = 's';

    iso[216][1] = 'S';
    iso[248][1] = 's';

    /* match greek tonal & separating letters */
    iso[182][0] = (char) 39;
    iso[182][1] = 'A';
    iso[184][0] = (char) 39;
    iso[184][1] = 'E';
    iso[185][0] = (char) 39;
    iso[185][1] = 'H';
    iso[186][0] = (char) 39;
    iso[186][1] = 'I';
    iso[188][0] = (char) 39;
    iso[188][1] = 'O';
    iso[190][0] = (char) 39;
    iso[190][1] = 'Y';
    iso[191][0] = (char) 39;
    iso[191][1] = 'W';
    iso[192][0] = 'i';
    iso[192][1] = (char) 39;
    iso[192][2] = '"';


    iso[218][0] = 'I';
    iso[218][1] = '"';
    iso[219][0] = 'Y';
    iso[219][1] = '"';

    iso[220][0] = 'a';
    iso[220][1] = (char) 39;
    iso[221][0] = 'e';
    iso[221][1] = (char) 39;
    iso[222][0] = 'h';
    iso[222][1] = (char) 39;
    iso[223][0] = 'i';
    iso[223][1] = (char) 39;
    iso[224][0] = 'y';
    iso[224][1] = (char) 39;
    iso[224][2] = '"';

    iso[250][0] = 'i';
    iso[250][1] = '"';
    iso[251][0] = 'y';
    iso[251][1] = '"';
    iso[252][0] = 'o';
    iso[252][1] = (char) 39;
    iso[253][0] = 'y';
    iso[253][1] = (char) 39;
    iso[254][0] = 'w';
    iso[254][1] = (char) 39;


}

void printISO(int c){

    char iso[256][3];
    initializeISOMatrix(iso);

    putchar(iso[c][0]);

    if(iso[c][1] != '\0')
        putchar(iso[c][1]);

    if(iso[c][2] != '\0')
        putchar(iso[c][2]);

}


typedef enum state { def, M, N, m, n } state;

/* Global variable */
state st;

state def_state(int c)
{
    switch(c) {
        case 204 :              /* greek capital M letter */
                    return M;
                    break;
        case 205 :              /* greek capital N letter */
                    return N;
                    break;
        case 236 :              /* greek lowercase m letter */
                    return m;
                    break;
        case 237 :              /* greek lowercase n letter */
                    return n;
                    break;
        default :               /* print & return def */
                    printISO(c);
                    return def;
                    break;
    }
}

state M_upper(int c)
{
    switch(c) {
        case 204 :                  /* greek capital M letter */
                    printISO(204);
                    return M;
                    break;
        case 205 :                  /* greek capital N letter */
                    printISO(204);
                    return N;
                    break;
        case 208 :                  /* greek capital PI letter */
                    printISO(66);   /* prints B returns to def state*/
                    return def;
                    break;
        case 236 :                  /* greek lowercase m letter */
                    printISO(204);
                    return m;
                    break;
        case 237 :                  /* greek lowercase n letter */
                    printISO(204);
                    return n;
                    break;
        case 240 :                  /* greek lowercase pi letter */
                    printISO(66);   /* prints B returns to def state */
                    return def;
                    break;
        default :
                    printISO(204);
                    printISO(c);
                    return def;
                    break;
    }
}

state N_upper(int c)
{
    switch(c) {
        case 204 :                  /* greek capital M letter */
                    printISO(205);
                    return M;
                    break;
        case 205 :                  /* greek capital N letter */
                    printISO(205);
                    return N;
                    break;
        case 212 :                  /* greek capital TAU letter */
                    printISO(68);   /* prints D returns to def state*/
                    return def;
                    break;
        case 236 :                  /* greek lowercase m letter */
                    printISO(205);
                    return m;
                    break;
        case 237 :                  /* greek lowercase n letter */
                    printISO(205);
                    return n;
                    break;
        case 244 :                  /* greek lowercase tau letter */
                    printISO(68);   /* prints D returns to def state */
                    return def;
                    break;
        default :
                    printISO(205);
                    printISO(c);
                    return def;
                    break;
    }
}

state m_lower(int c)
{
    switch(c) {
        case 204 :                  /* greek capital M letter */
                    printISO(109);
                    return M;
                    break;
        case 205 :                  /* greek capital N letter */
                    printISO(109);
                    return N;
                    break;
        case 208 :                  /* greek capital PI letter */
                    printISO(66);   /* prints B returns to def state*/
                    return def;
                    break;
        case 236 :                  /* greek lowercase m letter */
                    printISO(109);
                    return m;
                    break;
        case 237 :                  /* greek lowercase n letter */
                    printISO(109);
                    return n;
                    break;
        case 240 :                  /* greek lowercase pi letter */
                    printISO(98);   /* prints b returns to def state */
                    return def;
                    break;
        default :
                    printISO(109);
                    printISO(c);
                    return def;
                    break;
    }
}

state n_lower(int c)
{
    switch(c) {
        case 204 :                  /* greek capital M letter */
                    printISO(110);
                    return M;
                    break;
        case 205 :                  /* greek capital N letter */
                    printISO(110);
                    return N;
                    break;
        case 212 :                  /* greek capital TAU letter */
                    printISO(68);   /* prints D returns to def state*/
                    return def;
                    break;
        case 236 :                  /* greek lowercase m letter */
                    printISO(110);
                    return m;
                    break;
        case 237 :                  /* greek lowercase n letter */
                    printISO(110);
                    return n;
                    break;
        case 244 :                  /* greek lowercase tau letter */
                    printISO(100);   /* prints d returns to def state */
                    return def;
                    break;
        default :
                    printISO(110);
                    printISO(c);
                    return def;
                    break;
    }
}

/*  Not Used because  pointer to function seems
    a more elegant solution. Also it gives bonus :p */
state FSM (state st, int c)
{
    switch(st) {

        case M :
                    return M_upper(c);
                    break;
        case N :
                    return N_upper(c);
                    break;
        case m :
                    return m_lower(c);
                    break;
        case n :
                    return n_lower(c);
                    break;
        default :
                    return def_state(c);
                    break;
    }
}

/* array of pointers to functions */
state (*actions[]) (int c) = {def_state, M_upper, N_upper, m_lower, n_lower};

int main()
{

    int c;
    st = def;

    /* Not used but working */
    /*
    while((c=getchar())!= EOF){

        st = FSM(st,c);
    }
    */

    while((c=getchar())!= EOF){
        st = (actions[st])(c);
    }

    /*printf("\nTest Success!\nExiting programm...\n");*/
    return 0;
}
