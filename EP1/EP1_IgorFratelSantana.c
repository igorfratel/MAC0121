/*n.Igor Fratel Santana
 #9793565*/

#include <stdio.h>

/*Aplica Collatz ao numero x até chegar no valor 1 */
int aplicarFuncao (unsigned long int x)
{
	int cont = 0;
	while (x != 1) {
		/*Se x for par, divida por 2 */
        if (x % 2 == 0) {
        	x /= 2;
            cont++;
        }

        /*Se x for ímpar, multiplique por 3 e some 1 */
        else {
        	x = 3 * x + 1;
            x /= 2;
            cont += 2;
        }
    }
    return cont;
}

int main ()
{
	/*escolhi esse tipo de dado para evitar overflow*/
	unsigned long int i, f, j;
	/*Lê as entradas necessárias */
	printf ("Digite os valores inicial e final do intervalo: ");
	scanf ("%lu %lu", &i, &f);
	/*Aplica e exibe a função nos números do intervalo [i,f] */
	for (j = i; j <= f; j++)
		printf ("%d\n", aplicarFuncao(j));

	return 0;
}