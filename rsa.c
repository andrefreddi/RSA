#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int len = 0;
int text[100000];

// Menu
int menu(){
    
    int selection = 0;

    // Menu
    printf("\nMENU\n");
    printf("1. Crie chaves de criptografia e descriptografia\n");
    printf("2. Criptografar \n");
    printf("3. Descriptografar \n");
    printf("4. Sair \n");

    // Seleção
    printf("\n> ");
    scanf("%d", &selection);

    return selection;
}

// Encontre o maior divisor comum entre dois números
int gcd(int num1, int num2){
    int temp;

    while(num2 > 0){
      temp = num1 % num2;
      num1 = num2;
      num2 = temp;
    }
     
    return num1;
}

// d = (1/e) mod n
int mod_inverse(int u, int v)
{
    int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Etapa X1. Inicializar */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Lembre-se de iterações ímpar / par */
    iter = 1;
    /* Etapa X2. Loop enquanto v3! = 0 */
    while (v3 != 0)
    {
        /* Etapa X3. Dividir e "subtrair" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Trocar */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Certifique-se de que u3 = gcd (u, v) == 1 */
    if (u3 != 1)
        return 0;   /* Erro: Não existe inverso */
    /* Garanta um resultado positivo */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}



// Verifique se o número de entrada é um número primo ou não
bool check_prime(num){

    if(num == 0 || num == 1){
        return false;
    }

    // Retorne verdadeiro se o número só puder dividir 1 e ele mesmo
    for(int i = 2; i < num; i++){
        if (num % i == 0 && i != num){
            return false;
        }
    }
    
    return true;
}

// Verifique se a entrada e é válida
bool check_e(e, phi){

    // e e phi devem ter mdc de 1, 1 <e <phi
    if(gcd(e,phi) == 1 && e > 1 && e < phi){
        return true;
    } else{
        return false;
    }
}

// O Algoritmo de Exponenciação Modular
int MEA(int p, int e, int n){
 
  int r2 = 1;
  int r1 = 0;
  int Q = 0;
  int R = 0;
 
  while( e != 0 ){
     R = (e % 2);
     Q = ((e - R) / 2);
 
     r1 = ((p * p) % n);
 
       if(R == 1){
          r2 = ((r2 * p) % n);
       }
     p = r1;
     e = Q;
  }
return r2;
}

// Entrada recebida
void encode(e,n){
  int i = 0;

  int c = getchar();
  do{
    c = getchar();
    text[i] = MEA(c, e, n);
    len++;
    i++;
  }while(c != '\n');

  i = 0;  
  len -= 1;
  printf("\n*************************************\n");
  for(int i = 0; i < len; i++){ 
    printf("  Texto Criptografado C%d: %d\n", i+1, text[i]);
  }
printf("\n**\n > ");
  for(int i = 0; i < len; i++){ /* Imprimir a palavra criptografada e separada */
    printf("%d ", text[i]);
  }

}

void decode(d,n){
  printf("\n");

  for(int i = 0; i < len; i++){
    printf("Texto Criptografado C%d: ", i+1);
    scanf("%d", &text[i]);
    text[i] = MEA(text[i], d, n);
  }

  printf("\n*************************************");
  printf("\n   Texto Descriptografado: ");
  for(int i = 0; i < len; i++){
    printf("%c", text[i]);
  }
}

void clear_input(){
  // Limpa a matriz de texto
  memset(text,0,sizeof(text));
  len = 0;
}

int main(){

    int selection = 0;
    int p = 0; // Primo 1
    int q = 0; // Primo 2
    int n = 0; // n = primo1 * primo2;
    int e = 0; // Expoente público
    int d = 0; // d = (1/e) mod (phi)
    int phi = 0; // (primo1 - 1) * (primo2 - 1)

    bool valid_input = true;

    // Opções de menu
    while(selection != 5){

        int selection = menu();

        // Criar chave pública
        if(selection == 1){

            do{
              printf("\n Primeiro numero Primo: ");
              scanf("%d", &p);

              if(check_prime(p) == false){
                valid_input = false;

                printf(" O numero nao e primo! \n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);

            do{
              printf("\n Segundo numero Primo: ");
              scanf("%d", &q);

              if(check_prime(q) == false){
                valid_input = false;
                printf(" O numero nao e primo! \n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);
            
            n = p * q;
            phi = (p-1)*(q-1);
            


            do{
              printf("\n Numero expoente publico 'e': ");
              scanf("%d", &e);

              if(check_e(e,phi) == false){
                valid_input = false;
                printf(" O numero nao e compativel \n");
              } else {
                valid_input = true;
              }

            }while(valid_input == false);

            d = mod_inverse(e, phi);

            printf("\n*************************************\n");
            printf(" Chave de criptografia publica: \n");
            printf("    e = %d\n", e);
            printf("    n = %d\n", n);

            printf("\n");

            printf(" Chave de descriptografia privada: \n");
            printf("    d = %d\n", d);
            printf("    n = %d", n);
            printf("\n*************************************\n");
        } else if(selection == 2){
            printf("\n Insira a chave de criptografia publica: \n");
            printf(" Insira  o numero de 'e': ");
            scanf("%d", &e);
            printf(" Insira  o numero de 'n': ");
            scanf("%d", &n);

            printf("\n Insira o texto a ser criptografado: ");

            encode(e,n);
            
            printf("\n  Numero total de caracteres: %d", len);
            clear_input();
            printf("\n*************************************\n");
        } else if(selection == 3){
            printf("\n Insira a chave de descriptografia privada: \n");
            printf(" Insira  o numero de 'd': ");
            scanf("%d", &d);
            printf(" Insira  o numero de 'n': ");
            scanf("%d", &n);

            printf("\n Insira o numero de caracteres do texto criptografado: ");
            scanf("%d", &len);

            decode(d,n);
            clear_input();
            printf("\n*************************************\n");
        }else if(selection == 4){
            break;
        }
    }
}