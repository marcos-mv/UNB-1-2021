#include <stdio.h>

int add(int x, int y)
{

    int result;
    printf("Requisicao de adicao para %d e %d\n", x, y);
    result = x + y;
    return (result);
} /* fim funcao add */

int sub(int x, int y)
{
    int result;

    printf("Requisicao de subtracao para %d e %d\n", x, y);
    result = x - y;
    return (result);
} /* fim funcao sub */

int mul(int x, int y)
{
    int result;

    printf("Requisicao de multiplicao para %d e %d\n", x, y);
    result = x * y;
    return (result);
} /* fim funcao mul */

int div(int x, int y)
{
    int result;

    printf("Requisicao de divisao para %d e %d\n", x, y);
    result = x / y;
    return (result);
} /* fim funcao div */

int main(int argc, char *argv[])
{
    int x, y;

    if (argc != 3)
    {
        Fprintf(stderr, "Uso correto: %s num1 num2\n", argv[0]);
        exit(0);
    }

    /* Recupera os 2 operandos passados como argumento */
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, sub(x, y));
    printf("%d * %d = %d\n", x, y, mul(x, y));
    printf("%d / %d = %d\n", x, y, div(x, y));
    return (0);

} /* fim main */