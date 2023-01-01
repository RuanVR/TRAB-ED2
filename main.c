#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    
    //Registrando nova pessoa
    int idade;
    int s = 1;
    char sexo;

    printf("Digite sua idade\n");
    scanf("%d", idade);

    //Confirma se o sexo é valido
    while (s == 1)
    {
        printf("Digite seu sexo: m - masculino | f - feminino\n");
        scanf("%s", sexo);

        if (sexo == 'm' || sexo == 'f')
        {
            sexo = 0;
        } 
        else
        {
            printf("Sexo invalido, digite novamente\n");
        }     
    }

   
    return 0;
}