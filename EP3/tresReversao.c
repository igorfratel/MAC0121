#include <stdio.h>
#include <stdlib.h>

int *criaVetor (int *v, int n)
{
    /*Recebe um ponteiro de inteiro (vetor) e um inteiro positivo n (tamanho do vetor).
     *Devolve o vetor alocado com tamanho n. */ 
    v = malloc (n * sizeof(int));
    return v;
}

void rotacao (int *v, int i, int n, int *coords, int *p_coord)
{
    /*Recebe um ponteiro de inteiro v (vetor), um inteiro i tal que 0<=i<n, um inteiro positivo n (tamanho do vetor),
     *um ponteiro de inteiro (vetor) *coords e um ponteiro de inteiro *p_coord (primeira posição livre de  coords).
     *Realiza uma 3-rotação com início na posição v[i] e armazena i em coords[p_coord];
     *3-rotação:   
     * ___________       ___________
     *|_c_|_b_|_a_| ==> |_a_|_b_|_c_|  */

    int temp;
    coords[(*p_coord)++] = i;
    temp = v[i%n];
    v[i%n] = v[(i+2)%n];
    v[(i+2)%n] = temp;
}

void ordena_pares (int *v, int n, int *coords, int *p_coord)
{   
    /*Recebe um vetor v, um inteiro n (tamanho do vetor), um vetor coords e um ponteiro de inteiro 
     *p_coord (primeira posição livre de coords) 
     *Ordena os elementos em índice par entre si e os elementos de índice ímpar entre si. */
    int i, trocou = 1;
    while (trocou == 1){
        trocou = 0;
        for (i = 0; i < n - 2; i++){
            if (v[i] > v[i+2]){
                rotacao (v, i, n, coords, p_coord);
                trocou = 1;
            }
        }
    } 
}

int mod (int number, int mod)
{
    /*Recebe um inteiro number e um inteiro mod (positivo).
     *Realiza a operação "number módulo mod" e retorna o resultado. */
     if (number >= 0)
        return number % mod;
    else
        return number + mod * ((mod - number - 1)/mod);
} 

void ordena_menor (int *v, int n, int indice, int *coords, int *p_coord)
{
    /*Recebe os vetores v e coords, os inteiros n (tamanho de v) e indice e
     *o ponteiro de inteiro p_coords (primeira posição livre de coords.
     *Procura o elemento que deveria ocupar a posição coords[indice] em um
     *vetor ordenado e realiza as 3-rotações necessárias para que o elemento ocupe
     *essa posição. */
    int i, menor_tmp, n_reversoes = 1, menor = indice;
    for (i = indice; i < n - 1; i++) if (v[i] < v[menor]) menor = i;
    while ((menor != indice) && (n_reversoes < n)){
        if ((menor + 2 * n_reversoes)%n == indice){  
            for (i = 0; i < n_reversoes; i++){
                rotacao (v, menor, n, coords, p_coord);
                menor = (menor + 2)%n;
            }
            menor_tmp = mod ((menor - 2), n);
            for (i = n_reversoes - 1; i > 0; i--){
                rotacao (v, mod ((menor_tmp - 2), n), n, coords, p_coord);
                menor_tmp = mod ((menor_tmp - 2), n);
            }
        }
        else if (mod ((menor - 2 * n_reversoes), n) == indice){
            for (i = 0; i < n_reversoes; i++){
                rotacao (v, mod ((menor - 2),n), n, coords, p_coord);
                menor = mod ((menor - 2),n);
            }
            menor_tmp = (menor + 2)%n;
            for (i = n_reversoes - 1; i > 0; i--){
                rotacao (v, menor_tmp, n, coords, p_coord);
                menor_tmp = (menor_tmp + 2)%n;
            }
        }
        n_reversoes++;
    }
}

int ordenado (int *v, int n)
{
    /*Recebe um vetor v e um inteiro n (tamanho de v).
     *Retorna 1 se v estiver ordenado e 0 caso contrário. */
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++) 
            if (v[i] > v[j]) return 0;
    return 1;
}

int main ()
{
    int n, *v, *coords, p_coord, i, indice;
    if (scanf ("%d", &n) == 0) exit(1);;
    coords = criaVetor (coords, n * n);
    p_coord = 0;
    v = criaVetor (v, n);
    for (i = 0; i < n; i++)
        if (scanf ("%d", &v[i]) == 0) exit(1);
    indice = 0;
    while (1){
        ordena_pares (v, n, coords, &p_coord);
        if (ordenado (v, n) == 1){ 
            for (i = 0; i < p_coord; i++) printf ("%d\n", coords[i]);
            free (v);
            free (coords); 
            return 0;
        }
        else {
            if (n%2 == 0){
                printf ("Nao e possivel\n");
                free (v);
                free (coords); 
                return 0; 
            }               
            ordena_menor (v, n, indice, coords, &p_coord);
            indice++;
        }
    }     
}