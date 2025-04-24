#include <stdio.h>
#include <stdbool.h>

/*

Implementação de Adição Binária Usando Somador Completo
Este código implementa um somador binário que adiciona dois números binários de 4 bits usando a abordagem de circuito somador completo. Aqui está uma explicação de como funciona:

Entrada e Validação
O código aceita dois números binários de 4 bits como entradas de string (numero_a e numero_b)
Ele valida que ambas as entradas contêm apenas dígitos binários válidos (0 e 1)
Se inválido, solicita ao usuário que digite os números novamente
Os dígitos binários são convertidos em valores booleanos nos arrays bin_a e bin_b

Implementação do Somador Completo
O núcleo deste programa é a implementação do somador completo no loop. Um somador completo é um circuito digital que adiciona três bits: dois bits de entrada e um bit de carry-in, produzindo um bit de soma e um bit de carry-out.

Para cada posição de bit i:

xor1 = bin_a[i] ^ bin_b[i] - XOR dos dois bits de entrada (soma intermediária sem carry)
xor2 = xor1 ^ carry - XOR com o carry anterior para obter o bit de soma final
and1 = bin_a[i] & bin_b[i] - AND dos bits de entrada (gera carry se ambos forem 1)
and2 = xor1 & carry - AND da soma intermediária e do carry anterior
or = and1 | and2 - OR dos dois resultados AND para obter o novo bit de carry
carry = or - Armazena o carry para a próxima posição de bit
resposta[i] = xor2 - Armazena o bit de soma no array de resultado
O carry final é armazenado em resposta[4], que se torna o bit mais significativo do resultado.

Equivalente de Porta Lógica
Esta implementação modela a estrutura de hardware real de um circuito somador completo usando:

2 portas XOR (para cálculo de soma)
2 portas AND (para geração de carry)
1 porta OR (para combinar condições de carry)

Saída
O resultado é impresso em formato binário, começando pelo bit mais significativo (o carry) até o bit menos significativo.


Referências:
https://www.youtube.com/watch?v=wvJc9CZcvBc
https://en-m-wikipedia-org.translate.goog/wiki/Adder_(electronics)?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt&_x_tr_pto=tc

*/

int main(){
    char numero_a[5], numero_b[5];
    bool bin_a[4], bin_b[4], resposta[5];
    bool xor1, xor2, and1, and2, carry, or;
    /* 
    Recebe dois numeros binarios de 4 bits e armazena em numero_a e numero_b.
    O loop continua pedindo os numeros enquanto o usuario nao digitar 4 bits validos (0 ou 1).
    */
    int valido = 0;
    while ( ! valido ){
        printf("Digite o numero A em binario (apenas 0 e 1): ");
        scanf("%4s", numero_a);
        printf("Digite o numero B em binario (apenas 0 e 1): ");
        scanf("%4s", numero_b);
        
        // Verifica se o usuario digitou 4 bits validos (0 ou 1).
        valido = 1;
        for (int i = 0; i < 4; i++){
            if (!(numero_a[i] == '0' || numero_a[i] == '1') && !(numero_b[i] == '0' || numero_b[i] == '1')){
                valido = 0;
                printf("Entrada invalida, tente novamente.: %c %c\n", numero_a[i], numero_b[i]);
                break;
            }
        }
        // Se o usuario digitou 4 bits validos, 
        // armazena os numeros em bin_a e bin_b.
        for (int i = 0; i < 4; i++) {
            bin_a[3-i] = (numero_a[i] == '1');
            bin_b[3-i] = (numero_b[i] == '1');
        }
    }

    /*
    Realiza o calculo da soma binária (4 full adder)
    */
    carry = 0;
    for (int i = 0; i < 4; i++){
        xor1 = bin_a[i] ^ bin_b[i];
        xor2 = xor1 ^ carry;
        and1 = bin_a[i] & bin_b[i];
        and2 = xor1 & carry;
        or = and1 | and2;
        carry = or;
        resposta[i] = xor2; 
    }
    resposta[4] = carry; 
    for (int i = 4; i >= 0; i--){
        printf("%d", resposta[i] ? 1 : 0);
    }
}