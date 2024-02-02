/*

TP2
FEITO POR NICOLAS HENRIQUE DIAS XAVIER;
MATRÍCULA: 2023059458.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTS QUE SERÃO USADOS -----------------------------------------------------------------------------

typedef struct lua{
    // Struct de cada lua
    char* nome; // Nome da lua
    int raio; // Raio da lua
} lua;

typedef struct planeta{
    // Struct de cada planeta
    char* nome; // Nome do planeta
    int raio; // Raio do planeta
    int num_luas; // Quantidade de luas do planeta
    lua* luas; // Vetor de luas do planeta
} planeta;

typedef struct sistema{
    // Struct de cada sistema solar
    int tempo; // Tempo de descoberta do sistema
    char* nome; // Nome do sistema
    int raio; // Raio do sistema
    int num_planetas; // Quantidade de planetas do sistema
    planeta* planetas; // Vetor de planetas do sistema solar
} sistema;

// FUNÇÕES DE MEMÓRIA ----------------------------------------------------------------------------------

void aloca_lua(lua* lua){
    // Essa função recebe um ponteiro para um struct lua e o preenche com as entradas digitadas
    char nome[101]; // Variável auxiliar para o nome
    scanf(" \t%s", nome); // Armazenando nome da lua
    lua->nome = (char*) malloc(strlen(nome)*sizeof(char)); // Alocando espaço do nome da lua
    strcpy(lua->nome, nome); // Copiando o nome armazenado para o struct lua

    scanf("%d", &lua->raio); // Armazenando raio da lua
}

void aloca_planeta(planeta* planeta){
    // Essa função recebe um ponteiro para um struct Planeta e o preenche com as entradas digitadas
    char nome[101]; // Variável auxiliar de nome
    scanf(" \t%s", nome); // Armazenando o nome do planeta
    planeta->nome = (char*) malloc(strlen(nome)*sizeof(char)); // Alocando espaço do nome do planeta
    strcpy(planeta->nome, nome); // Copiando o nome armazenado para o struct planeta

    scanf("%d", &planeta->raio); // Armazenando o raio do planeta

    scanf("%d", &planeta->num_luas); // Armazenando a quantidade de luas
    planeta->luas = (lua*) malloc(planeta->num_luas*sizeof(lua)); // Alocando espaço para cada uma das luas

    for(int i=0; i<planeta->num_luas; i++){ // Para cada uma das luas
        aloca_lua(&planeta->luas[i]); // Chamando a função que preenche uma lua
    }
}

void aloca_sistema(sistema* sistema){
    // Essa função recebe um ponteiro para um struct sistema e o preenche com as entradas digitadas
    scanf("%d", &sistema->tempo); // Armazenando tempo de descoberta
    
    char nome[101]; // Variável auxiliar de nome
    scanf(" %s", nome); // Armazenando nome do sistema solar
    sistema->nome = (char*) malloc(strlen(nome)*sizeof(char)); // Alocando espaço do nome do sistema solar
    strcpy(sistema->nome, nome); // Copiando o nome armazenado para o struct sistema
    
    scanf("%d", &sistema->raio); // Armazenando raio do sol do sistema solar

    scanf("%d", &sistema->num_planetas); // Armazenando quantidade de planetas
    sistema->planetas = (planeta*) malloc(sistema->num_planetas*sizeof(planeta)); // Alocando espaço para cada um dos planetas

    for(int i=0; i<sistema->num_planetas; i++){ // Para cada um dos planetas
        aloca_planeta(&sistema->planetas[i]); // Chamando a função que preenche um planeta
    }
}

void free_sistemas(sistema* sistemas){
    // Essa função recebe o vetor de sistemas solares e libera a memória de todos os vetores em cascata
    int num_sistemas = sizeof(sistemas)/(sizeof(sistema)); // Encontrando o tamanho do vetor

    for(int i=0; i<num_sistemas; i++){ // Para cada sistema solar
        for(int j=0; j<sistemas[i].num_planetas; j++){ // Para cada planeta no sistema solar
            for(int k=0; k<sistemas[i].planetas[j].num_luas; k++){ // Para cada lua no planeta
                free(sistemas[i].planetas[j].luas[k].nome); // Liberando a memória do nome da lua
            }
            free(sistemas[i].planetas[j].nome); // Liberando a memória do nome do planeta
            free(sistemas[i].planetas[j].luas); // Liberando a memória do vetor de luas
        }
        free(sistemas[i].planetas); // Liberando a memória do vetor de planetas
    }
    free(sistemas); // Liberando a memória do vetor de sistemas
}

// FUNÇÕES DE COMPARAÇÃO --------------------------------------------------------------------------------

planeta* maior_planeta(planeta* planetas){
    // Essa função recebe um ponteiro para um vetor de planetas e retorna o struct Planeta do planeta de maior raio

    int tamanho = sizeof(planetas)/sizeof(planeta); // Encontrando tamanho do vetor

    planeta* maior = &planetas[0]; // Inicializando a variável que guardará o endereço do maior planeta encontrado

    for (int i=0; i<tamanho; i++){ // Para cada planeta
        if(planetas[i].raio > maior->raio){
            // Se o raio do planeta i for maior do que o raio do maior planeta encontrado até então
            maior = &planetas[i]; // Atribuindo o endereço i do maior planeta
        }
    }
    return maior; // Retornando o maior planeta
}

int contar_luas(planeta* planetas){
    // Essa função recebe um ponteiro para um vetor de planetas e retorna a quantidade total de luas do sistema solar
    
    int tamanho = sizeof(planetas)/sizeof(planeta); // Encontrando o tamanho do vetor

    int cont_luas = 0; // Inicializando contador de luas

    for(int i=0; i<tamanho; i++){ // Para cada planeta
        cont_luas += planetas[i].num_luas; // Somando a quantidade de luas do planeta ao contador
    }

    return cont_luas; // Retornando o total de luas encontradas
}

lua* maior_lua(planeta* planetas){
    // Essa função recebe um ponteiro para um vetor de planetas e retorna o struct lua da maior lua encontrada

    int tamanho = sizeof(planetas)/sizeof(planeta); // Encontrando o tamanho do vetor
    
    lua* maior_lua = &planetas[0].luas[0]; // Inicializando variável que guardará o endereço da maior lua

    for (int i=0; i<tamanho; i++){ // Para cada um dos planetas
        for(int j=0; j<planetas[i].num_luas; j++){ // Para cada uma das luas de cada planeta
            if(planetas[i].luas[j].raio > maior_lua->raio){
                // Se o raio da lua j do planeta i for maior que o raio da maior lua encontrada até o momento
                maior_lua = &planetas[i].luas[j]; // Atribuindo o endereço da lua j do planeta i
            }
        }
    }

    return maior_lua; // Retornando struct da maior lua
}

int comparar_sistemas(sistema s1, sistema s2){
    // Essa função compara dois sistemas solares:
    // Se o primeiro for mais interessante, retorna 1;
    // Se o segundo for mais interessante, retorna 0

    // Primeiro critério: Qual dos sistemas possui um sol de maior raio
    if(s1.raio > s2.raio){return 1;}
    else if(s2.raio > s1.raio){return 0;}

    // Em caso de empate no critério 1
    // Segundo critério: Qual dos sistemas possui mais planetas
    if(s1.num_planetas > s2.num_planetas){return 1;}
    else if(s2.num_planetas > s1.num_planetas){return 0;}

    // Em caso de empate nos critérios 1 e 2
    // Terceiro critério: Qual dos sistemas possui o planeta com maior raio
    if(maior_planeta(s1.planetas)->raio > maior_planeta(s2.planetas)->raio){return 1;}
    else if(maior_planeta(s2.planetas)->raio > maior_planeta(s1.planetas)->raio){return 0;}

    // Em caso de empate nos critérios 1, 2 e 3
    // Quarto critério: Qual dos sistemas possui mais luas
    if(contar_luas(s1.planetas) > contar_luas(s2.planetas)){return 1;}
    else if(contar_luas(s2.planetas) > contar_luas(s1.planetas)){return 0;}

    // Em caso de empate nos critérios 1, 2, 3 e 4
    // Quinto critério: Qual dos sistemas possui a lua com maior raio
    if(maior_lua(s1.planetas)->raio > maior_lua(s2.planetas)->raio){return 1;}
    else if(maior_lua(s2.planetas)->raio > maior_lua(s1.planetas)->raio){return 0;}

    // Em caso de empate nos critérios 1, 2, 3, 4 e 5
    // Quinto critério: Qual dos sistemas possui um menor tempo de descoberta
    if(s1.tempo < s2.tempo){return 1;}
    else if(s2.tempo < s1.tempo){return 0;}
    
    // Em caso de empate em todos os critérios, apesar de impossível de acordo com o enunciado
    else{return -1;}
}

// FUNÇÕES DE ORDENAÇÃO ---------------------------------------------------------------------------------

void ritacao(sistema* sistemas, int inicio_esq, int fim_esq, int inicio_dir, int fim_dir){
    // Função que recebe as duas partes do vetor e ordena ele
    int tam_esq = fim_esq-inicio_esq; // Tamanho da primeira metade do vetor
    int tam_dir = fim_dir-inicio_dir; // Tamanho da segunda metade do vetor

    sistema* esquerda = (sistema*) malloc(tam_esq*sizeof(sistema)); // Alocando o espaço para a parte esquerda do vetor
    sistema* direita = (sistema*) malloc(tam_dir*sizeof(sistema)); // Alocando o espaço para a parte direita do vetor
    
    // Preenchendo a parte esquerda do vetor
    for(int i=0; i<tam_esq; i++){
        esquerda[i] = sistemas[inicio_esq+i];
    }

    // Preenchendo a parte direita do vetor
    for(int i=0; i<tam_dir; i++){
        direita[i] = sistemas[inicio_dir+i];
    }

    // Variáveis de posições que serão usadas para realocar os sistemas solares dentro do vetor 
    int i=0, j=0, k=inicio_esq;

    
    while(i<tam_esq && j<tam_dir){// Enquanto a repetição não chegar ao final de pelo menos uma das partes do vetor
        // Se o primeiro sistema for mais interessante que o segundo, essa função retorna 1(Verdadeiro)
        if(comparar_sistemas(esquerda[i], direita[j])){
            // Armazenando na posição k do vetor, o elemento de posição i da parte esquerda
            sistemas[k] = esquerda[i];
            i++; // Somando 1 para o próximo sistema solar
        }
        else{
            // Armazenando na posição k do vetor, o elemento de posição j da parte direita
            sistemas[k] = direita[j];
            j++; // Somando 1 para o próximo sistema solar
        }
        k++; // Somando 1 para preencher a próxima posição
    }

    
    while(i<tam_esq){ // Armazenando o resto dos sistemas da parte esquerda que ainda serão ordenados
        sistemas[k] = esquerda[i];
        i++;
        k++;
    }
    while(i<tam_dir){ // Armazenando o resto dos sistemas da parte direita que ainda serão ordenados
        sistemas[k] = direita[j];
        j++;
        k++;
    }
    
    free(esquerda); // Liberando a memória alocada para a parte esquerda do vetor
    free(direita); // Liberando a memória alocada para a parte direita do vetor
}

void bromero_sort(sistema* sistemas, int i_esq, int i_dir) {
    // Função recursiva que ordena os sistemas do vetor
    int tamanho = i_dir-i_esq; // Tamanho do vetor recebido
    if(tamanho==1){return;} // Se o vetor só tiver uma posição, nada é feito pois já é o ultimo nível da recursividade
    if(tamanho%2==1){ // Se o vetor possui tamanho impar...
        bromero_sort(sistemas, i_esq, i_dir-1); // Chamando a função recursivamente, descartando o ultimo sistema do vetor
        ritacao(sistemas, i_esq, i_dir-1, i_dir-1, i_dir); // Realocando os sistemas solares ordenadamente dentro do vetor
        return;
    }
    // Caso o tamanho do vetor seja par
    int i_meio = (i_esq+i_dir)/2; // Encontrando o meio do vetor para dividí-lo ao meio.
    bromero_sort(sistemas, i_esq, i_meio); // Chamando a função recursivamente com a metade à esquerda do vetor
    bromero_sort(sistemas, i_meio, i_dir); // Chamando a função recursivamente com a metade à direita do vetor
    ritacao(sistemas, i_esq, i_meio, i_meio, i_dir); // Realocando os sistemas solares ordenadamente dentro do vetor
}

// ------------------------------------------------------------------------------------------------------

int main(){
    int num_sistemas; // Variável que recebe a quantidade de sistemas solares que serão armazenados
    scanf("%d", &num_sistemas); // Guardando o valor digitado

    sistema* sistemas = (sistema*) malloc(num_sistemas*sizeof(sistema)); // Alocando o espaço dos sistemas solares

    for(int i=0; i<num_sistemas; i++){ // Repetição para cada um dos sistemas solares que serão armazenados
        aloca_sistema(&sistemas[i]); // Chamando a função que recebe e guarda os dados de cada sistema solar
    }

    // Chamando a função que ordena os sistemas do mais ao menos interessante com base nos critérios definidos no enunciado
    bromero_sort(sistemas, 0, num_sistemas);

    for(int i=0; i<num_sistemas; i++){ // Repetição para cada um dos sistemas solares ordenados
        printf("%s\n", sistemas[i].nome); // Imprimindo o nome de cada sistema solar
    }
    
    free_sistemas(sistemas); // Liberando a memória alocada para o vetor de sistemas solares
    return 0;
}