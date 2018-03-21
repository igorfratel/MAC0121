/* n.Igor Fratel Santana
 * #9793565 */
#include <stdio.h>
#include <stdlib.h>
/* Funções da pilha (inicio). */
typedef struct 
{
    int *P,
        *pdir,
        topo_P,
        topo_pdir;
} pilha;

pilha *criaPilha (int tamanho_pilha)
{
    /* Recebe um inteiro tamanho_pilha positivo e aloca uma struct pilha. */
    pilha *minha_pilha;
    minha_pilha = malloc (sizeof(pilha));
    minha_pilha->P = calloc (tamanho_pilha, sizeof(int));
    minha_pilha->pdir = calloc (tamanho_pilha/2, sizeof(int));
    minha_pilha->topo_P = 0;
    minha_pilha->topo_pdir = 0;
    return minha_pilha;
}

void destroiPilha (pilha *minha_pilha)
{
    /* Recebe um ponteiro de pilha *minha_pilha e 
     * libera o espaço alocado para a pilha. */
    free (minha_pilha->P);
    free (minha_pilha->pdir);
    free (minha_pilha);
}

void empilha (pilha *minha_pilha, int i, int j, int dir)
{
    /* Recebe um ponteiro de pilha *minha_pilha e os inteiros i, j e dir, onde
     * i e j são não-negativos e 1 <= dir <= 4.
     * A função empilha os inteiros na pilha. 
     *        ____________________________
     * P     |_i1_|_j1_|_i2_|_j2_|_topo_P_|
     *        _________________________
     * pdir  |_dir1_|_dir2_|_topo_pdir_| */

    minha_pilha->pdir[minha_pilha->topo_pdir++] = dir;
    minha_pilha->P[minha_pilha->topo_P++] = i;
    minha_pilha->P[minha_pilha->topo_P++] = j;   
}

int pilhaVazia (pilha minha_pilha)
{
    /* Recebe uma pilha minha_pilha 
     * devolve 1 se ela estiver vazia ou 0 caso contrário. */
    int pilha_vazia = 0;
    if (minha_pilha.topo_P == 0) pilha_vazia = 1;
    return pilha_vazia;
}

void imprimePilha(pilha minha_pilha)
{
    /* Recebe uma pilha minha_pilha e imprime
     * os movimentos necessários para resolver o tabuleiro.
     * Os inteiros i e j declarados na função 
     * representam as coordenadas de uma peça que foi movida. */
    int cont, cont_dir, i, j, dir;
    cont = 0;
    for (cont_dir = 0; cont_dir < minha_pilha.topo_pdir; cont_dir++) {
        i = minha_pilha.P[cont];
        j = minha_pilha.P[cont+1];
        dir = minha_pilha.pdir[cont_dir];
        switch (dir) {
            case 1:
                printf("%d:%d-%d:%d\n", i, j, i - 2, j);
                break;
            case 2:
                printf("%d:%d-%d:%d\n", i, j, i, j + 2);
                break;  
            case 3:
                printf("%d:%d-%d:%d\n", i, j, i + 2, j);
                break;
            case 4:
                printf("%d:%d-%d:%d\n", i, j, i, j - 2);
                break;
        }
        cont = cont + 2;
    }
}
/* Funções da pilha (fim). */

/* Funções do tabuleiro (início). */
int **criaTab (int m, int n)
{
    /* Recebe inteiros positivos m e n e aloca um tabuleiro de dimensões mXn. */
    int **tab, i;
    tab = malloc (m*sizeof(int*));
    if (tab != NULL) {
        for (i = 0; i < m; i++) {
            tab[i] = malloc (n*sizeof(int));
            if (tab[i] == NULL) exit (1);
        }
        return tab;
    }
    else exit (1);
}

void destroiTab (int **tab, int m)
{
    /* Recebe um ponteiro de ponteiros para inteiro **tab e
     * um inteiro m > 0, onde
     * m é o número de linhas do tabuleiro.
     * Libera o espaço da memória usado pelo tabuleiro. */
    int i;
    for (i = 0; i < m; i++) 
        free (tab[i]);
    free(tab);
}

int **inverteTab (int **tab, int m, int n)
{
    /* Recebe um ponteiro de ponteiros para inteiro **tab e dois inteiros
     * positivos m e n e devolve um ponteiro de ponteiro para inteiro **tab_sol
     * que é o tabuleiro invertido (1 vira -1 e vice-versa). */
    int **tab_sol, i, j;
    tab_sol = criaTab (m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (tab[i][j] == 1) tab_sol[i][j] = -1;
            else if (tab[i][j] == -1) tab_sol[i][j] = 1;
        }
    }
    return tab_sol;
}

int podePular (int **tab, int m, int n, int coord[], int dir)
{
    /* Recebe um ponteiro de ponteiros para inteiro **tab, 
     * dois inteiros positivos m e n,
     * um vetor de inteiros coord[] com duas posições e um inteiro
     * dir, onde 1 <= dir <= 4.
     * Verifica se é possível movimentar a peça na direção contida em dir.
     * Retorna 1 se o movimento for possível e 0 caso contrário.
     * Movimentos(dir):
     *
     *
     *                   1
     *                   ^
     *                   |
     *              4 <-- --> 2
     *                   |
     *                   v
     *                   3
     */
    int c, i, j;
    c = 0;
    i = coord[0];
    j = coord[1];
    if (tab[i][j] != 1) return c;
    switch (dir) {
        case 1:
            if ((i > 1) && (tab[i-1][j] == 1) && (tab[i-2][j] == -1)) c=1;
            break;
        case 2:
            if ((j < n - 2) && (tab[i][j+1] == 1) && (tab[i][j+2] == -1)) c=1;
            break;
        case 3:
            if ((i < m - 2) && (tab[i+1][j] == 1) && (tab[i+2][j] == -1)) c=1;
            break;
        case 4:
            if ((j > 1) && (tab[i][j-1] == 1) && (tab[i][j-2] == -1)) c=1;
            break;          
    }
    return c;
}

int comparaTabs (int **tab, int **tab_sol, int m, int n)
{

    /* Recebe dois ponteiros de ponteiros para inteiro **tab e **tab_sol e
     * dois inteiros positivos m e n.
     * Retorna 1 se os dois tabuleiros forem idênticos e 0 caso contrário. 
     * Os tabuleiros devem ter as mesmas dimensões. */
    int i, j, c;
    i = 0;
    j = 0;
    c = 1;
    while ((i < m) && (c == 1)) {
        j = 0;
        while ((j < n) && (c == 1)) {
            if (tab[i][j] != tab_sol[i][j]) c=0;
            j++;
        }
        i++;
    }
    return c;
}
void movePeca (pilha *minha_pilha, int **tab, int coord[], int dir)
{
    /*Recebe um ponteiro de pilha minha_pilha,
     * um ponteiro de ponteiros para inteiro tab,
     * um vetor de inteiros coord[] com duas posições e
     * um inteiro dir, onde 1 <= dir <= 4
     * Empilha o código do movimento executado (dir) e
     * altera o tabuleiro de acordo com as regras do jogo. */
    int i, j;
    i = coord[0];
    j = coord[1]; 
    empilha (minha_pilha, i, j, dir);
    tab[i][j] = -1;
    switch (dir) {
        case 1:
            tab[i-1][j] = -1;
            tab[i-2][j] =  1;
            break;
        case 2:
            tab[i][j+1] = -1;
            tab[i][j+2] =  1;            
            break;
        case 3:
            tab[i+1][j] = -1;
            tab[i+2][j] =  1;
            break;
        case 4:
            tab[i][j-1] = -1;
            tab[i][j-2] =  1;
            break;
    }
}

void voltaMovimento (int **tab, int m, int n, pilha *minha_pilha, int coord[], int *dir)
{
    /* Recebe um ponteiro de ponteiros para inteiro **tab,
     * dois inteiros positivos m e n,
     * um ponteiro de pilha minha_pilha,
     * um vetor de inteiros coord[] com duas posições e
     * um ponteiro para inteiro *dir.
     * Desempilha o último movimento, desfaz suas alterações no tabuleiro,
     * preenche coord com as coordenadas da última peça movida e
     * preenche *dir com a direção do último movimento. */
    int i, j;
    j = minha_pilha->P[--minha_pilha->topo_P];
    i = minha_pilha->P[--minha_pilha->topo_P];
    *dir = minha_pilha->pdir[--minha_pilha->topo_pdir];
    tab[i][j] = 1;
    switch (*dir) {
        case 1:
            tab[i-1][j] = 1;
            tab[i-2][j] = -1;
            break;
        case 2:
            tab[i][j+1] = 1;
            tab[i][j+2] = -1;            
            break;
        case 3:
            tab[i+1][j] = 1;
            tab[i+2][j] = -1;
            break;
        case 4:
            tab[i][j-1] = 1;
            tab[i][j-2] = -1;
            break;
    }
    coord[0] = i;
    coord[1] = j;
}

int encontraPeca(int **tab, int m, int n, int coord[])
{
    /* Recebe um ponteiro de ponteiros para inteiro **tab,
     * dois inteiros positivos m e n e
     * um vetor de inteiros coord[] com duas posições. 
     * Preenche coord com as coordenadas da próxima
     * peça encontrada (se houver) no tabuleiro a partir da posição (m,n).
     * Retorna 1 se uma peça for encontrada e 0 caso contrário. */
    int i, j; 
    i = coord[0];
    j = coord[1];
    for (; i < m; i++) {
        for (; j < n; j++) {
            if (tab[i][j] == 1) {
                coord[0] = i;
                coord[1] = j;
                return 1;
            }
        }
        j = 0;
    }
    coord[0] = coord[1] = 0;
    return 0;
}

int contaBuracos(int **tab, int m, int n)
{
    int i, j, nburacos;
    nburacos = 0;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if (tab[i][j] == -1) nburacos++;
        }
    }
    return nburacos;
}

int restaUm(int **tab, int **tab_sol, pilha *minha_pilha, int m, int n, int coord[], int dir, int nburacos_sol)
{
    /* Recebe dois ponteiros de ponteiros para inteiros **tab e **tab_sol,
     * um ponteiro de pilha *minha_pilha,
     * dois inteiros positivos m e n,
     * um vetor de inteiros coord[] com duas posições e
     * um inteiro dir, onde 1 <= dir <= 4.
     * Realiza o algoritmo para solucionar o tabuleiro (vide relatório).
     * Retorna 1 se houver solução e 0 caso contrário. */

    int nburacos;
    nburacos = contaBuracos(tab, m, n);
    while ((nburacos != nburacos_sol)  || (!comparaTabs (tab, tab_sol, m, n))) {
        if(encontraPeca (tab, m, n, coord)) {
            if (podePular (tab, m, n, coord, dir)) {
                movePeca (minha_pilha , tab, coord, dir);                                        
                coord[0] = coord[1] = 0;                                         
                dir = 1;
                nburacos++;
            }    
            else if (dir < 4) dir++;
            else {    
                if (coord[1] < n - 1) coord[1]++;
                else if (coord[0] < m - 1) {
                    coord[0]++;
                    coord[1] = 0;
                }
                dir = 0;
            }
        }
        else {
             /*backtrack*/
            if (pilhaVazia (*minha_pilha)) {
                return 0;
            }
            voltaMovimento (tab, m, n, minha_pilha, coord, &dir);
            nburacos--;
            dir++;
        }
    }
    return 1;
}
/* Funções do tabuleiro (fim). */

int main ()
{
    pilha *minha_pilha;
    int m, n, i, j, tamanho_pilha, dir, nburacos_sol;
    int **tab, **tab_sol, coord[2];
    coord[0] = 0;
    coord[1] = 0;
    dir = 1;
    /* Cria o tabuleiro e seta os valores das celulas. */
    if (scanf ("%d %d", &m, &n) != 2) exit(1);
    tamanho_pilha = m*n*2;
    tab = criaTab (m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            if(!scanf ("%d", &tab[i][j])) exit(1);
    }
    /* Cria a pilha e o tabuleiro solução. */
    minha_pilha = criaPilha (tamanho_pilha);
    tab_sol = inverteTab (tab, m, n);
    nburacos_sol = contaBuracos (tab_sol, m, n);
    /* Se não houver solução, imprime "Impossivel".
     * Caso contrário, imprime a sequência de passos para a solução. */
    if (!restaUm(tab, tab_sol, minha_pilha, m, n, coord, dir, nburacos_sol))
        printf ("Impossivel\n");
    else imprimePilha (*minha_pilha);
    destroiPilha (minha_pilha);
    destroiTab (tab, m);
    return 0;
}