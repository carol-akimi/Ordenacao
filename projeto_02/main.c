#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#define QTD_TESTS 28
#define QTD_SORTS 9

/* Estrutura para auxiliar a coleta dos dados */
typedef struct dados_{
    long long int comp, trocas;
} Dados;

/* Algoritmos de Ordenação */
void bubble_sort(int *vet, int n, Dados* bubble_data);
void selection_sort(int *vet, int n, Dados* selection_data);
void insertion_sort(int *vet, int n, Dados* insertion_data);
void shell_sort(int *vet, int inc[], int n, int n_inc, Dados* shell_data);
void quick_sort(int *vet, int inicio, int fim, Dados* quick_data);
void heap_sort(int *vet, int n, Dados* heap_data);
void merge_sort(int *vet, int inicio, int fim, Dados* merge_data);
int* contagem_de_menores(int *vet, int n, Dados* counting_data);
int* radix_sort(int *vet, int tam, Dados* radix_data);

/* Definição de ponteiro para uma função de ordenação generalizada */
typedef void AlgOrdenacao(int*, int, Dados*);

/* Funções "envelope" para as chamadas aos algoritmos que 
    levam parâmetros diferentes */
void shell_wrapper(int *vet, int n, Dados* shell_data){
    shell_sort(vet, (int[]){5, 3, 1}, n, 3, shell_data);
}
void quick_wrapper(int *vet, int n, Dados* quick_data){
    quick_sort(vet, 0, n-1, quick_data);
}
void merge_wrapper(int *vet, int n, Dados* merge_data){
    merge_sort(vet, 0, n-1, merge_data);
}
void counting_wrapper(int *vet, int n, Dados* counting_data){
    contagem_de_menores(vet, n, counting_data);
}
void radix_wrapper(int *vet, int n, Dados* radix_data){
    radix_sort(vet, n, radix_data);
}


void RodarTestes(AlgOrdenacao** algortitmos);

int main(void){

    /* Vetor de ponteiros para as funções de ordenação */
    AlgOrdenacao* algoritmos[QTD_SORTS] = {
        bubble_sort, selection_sort,
        insertion_sort, shell_wrapper,
        quick_wrapper, heap_sort,
        merge_wrapper, counting_wrapper,
        radix_wrapper
    };

    RodarTestes(algoritmos);
}

// Função que roda os testes e gera os arquivos com os resultados
void RodarTestes(AlgOrdenacao** algoritmos){
    // Vetor com os nomes dos sorts
    const char* alg_nomes[QTD_SORTS] = {
        "bubble", "selection", "insertion",
        "shell", "quick", "heap",
        "merge", "counting", "radix"
    };
    // Abre o arquivo com os nomes dos
    // arquivos com os inputs
    FILE* in = fopen("tests/tests.txt", "r");

    // Laço que itera por todas as funções do vetor 'algoritmos'
    for(int i = 0; i < QTD_SORTS; i++){
        // Cria a string que será o nome do arquivo de saída para
        // os resultados do algoritmo sendo executado
        char outfilename[25];
        sprintf(outfilename, "results/%s.csv", alg_nomes[i]);
        // Gera o arquivo de saída
        FILE* out = fopen(outfilename, "w");
        // Escreve a linha titular do arquivo csv
        fprintf(out, "ordenação, n, tempo, comparações, trocas\n");

        // Laço que faz rodar todos os arquivos de input
        for(int j = 0; j < QTD_TESTS; j++){
            char* testfilename = (char*) malloc(50);
            fscanf(in, " %s", testfilename); // Lê qual vai ser o arquivo teste
            FILE* input = fopen(testfilename, "r"); // Abre o arquivo da vez

            int n;
            // Primeiro valor do input é o tamanho do vetor
            fscanf(input, "%d", &n); 

            // Aloca o vetor e preenche
            int *vet = (int*) malloc(n*sizeof(int));
            for(int i = 0; i < n; i++){
                fscanf(input, "%d", &vet[i]);
            }
            fclose(input); // Fecha o arquivo de input

            // Inicializa a estrutura dos dados de trocas e comparações
            Dados dados_coletados = {0, 0};

            printf("Rodando %s sort... Teste %d/%d: %s\n", alg_nomes[i], j+1, QTD_TESTS, testfilename + 6);
        
            // Chama cada função do vetor e conta o tempo de execução
            clock_t ini, fim;
            ini=clock();
            algoritmos[i](vet, n, &dados_coletados);
            fim=clock();

            free(vet); // Libera a memória do vetor testado

            // Obtém o tempo total e o tipo de ordenação do vetor
            double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
            char* ordem = strtok(testfilename + 6, "/");

            /* Quando os testes são com vetores aleatórios, esse 
                mecanismo armazena os resultados e, ao fim do quinto 
                teste com o mesmo tamanho de vetor, calcula a média ~
                dos cinco resultados e escreve no arquivo */
            if(j > 7){
                int tracker;
                double vet_tempos[5];
                long long int vet_comp[5], vet_trocas[5];
                if(j == 8 || j == 13 || j == 18 || j == 23){
                    tracker = j;
                }
                vet_tempos[(j-tracker)] = tempo;
                vet_comp[(j-tracker)] = dados_coletados.comp;
                vet_trocas[(j-tracker)] = dados_coletados.trocas;
                if((j - tracker) != 4)
                    continue;
                for(int k = 0; k < 4; k++){
                    tempo += vet_tempos[k];
                    dados_coletados.comp += vet_comp[k];
                    dados_coletados.trocas += vet_trocas[k];
                }
                tempo /= 5;
                dados_coletados.comp /= 5;
                dados_coletados.trocas /= 5;
            }

            // Escreve os resultados no arquivo
            fprintf(out, "%s, %d, %lf, %lld, %lld\n", ordem, n, tempo, dados_coletados.comp, dados_coletados.trocas);

            printf("Tempo do %s sort foi %lf s para %d elementos com distribuição '%s'\n\n", alg_nomes[i], tempo, n, ordem);

            free(testfilename); // libera a memória da string
        }
        fclose(out); // Fecha o arquivo de saída
        rewind(in); // Volta o buffer para o início do arquivo com os testes
    }
    // Ao fim, fecha o arquivo com os arquivos de input
    fclose(in);
}

void bubble_sort(int *vet, int n, Dados* bubble_data){
    for (int i = 0; i < n; i++){
        int troca = 0; //sinaliza se alguma troca foi feita
        for (int j = 0; j < n - 1; j++){
            //compara de dois em dois elementos, troca se 
            //o seu sucessor está na ordem incorreta 
            bubble_data->comp++;
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
                bubble_data->trocas++; 
            }
        }
        //se não ocorreu nenhuma troca, o vetor está ordenado, encerra o laço
        if(troca == 0)
            break; 
    }
}

void selection_sort(int *vet, int n, Dados* selection_data){
    for (int i = 0; i < n-1; i++){
        int min = i; //armazena a posição do menor elemento
        for (int j = i + 1; j < n; j++){
            selection_data->comp++; 
            //busca se existe um elemento menor que o armazenado atualemente
            if (vet[j] < vet[min])
                min = j; 
        }
        //se um menor elemento é encontrado, há uma troca com o item de posição i
        if(i != min){
            int aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
            selection_data->trocas++; 
        }
    }
}

void insertion_sort(int *vet, int n, Dados* insertion_data){
    int j; 
    for (int i = 1; i < n; i++){
        //armazena o valor atual para que não seja perdido após as movimentações
        int x = vet[i]; 
        //os elementos maiores que x são movidos uma posição para frente
        for (j = i - 1; j >= 0; j--){
            insertion_data->comp++; 
            if (vet[j] > x){
                vet[j+1] = vet[j]; 
                insertion_data->trocas++; 
            }else{
                break; 
            }
        }
        //insere o elemento na posição correta, os elementos  
        //a esquerda dessa posição já estão ordenados
        vet[j+1] = x;
    }
}

void shell_sort(int *vet, int inc[], int n, int n_inc, Dados* shell_data){ 
    //inc é o vetor que armazena os intervalos que serão feitos as ordenações
    int i, j, h; 
    //itera pelos elementos de inc, que armazena as distâncias dos sub-conjuntos
    for (int k = 0; k < n_inc; k++){ //vai iterar pelos elementos de inc
        h = inc[k]; 
        //realiza uma inserção simples, mas os elementos estão 
        //separados por uma distância h 
        for (i = h; i < n; i++){
            int x = vet[i]; 
            for (j = i - h; j >= 0; j -= h){
                shell_data->comp++;
                if (vet[j] > x){
                    vet[j+h] = vet[j]; 
                    shell_data->trocas++; 
                }else{
                    break; 
                }
            }
            vet[j+h] = x; 
        }
    }
}

//Função devove a mediana dados três elementos
int mediana(int a, int b, int c){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

void quick_sort(int *vet, int inicio, int fim, Dados* quick_data){
    int i = inicio; 
    int j = fim;
    //o pivo é a mediana entre o elemento do inicio, meio e fim
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim]); 
    do{
        //organiza os elementos de forma que todos a esquerda
        //sejam menores e os da direita, maiores
        while (vet[i] < pivo){
            i++; 
            quick_data->comp++; 
        }
        quick_data->comp++; //quando a condição falha 
        while (vet[j] > pivo){
            j--; 
            quick_data->comp++; 
        }
        quick_data->comp++; 
        if (i <= j){
            //troca os elementos se o da direita é menor que um no lado esquerdo
            int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
            quick_data->trocas++; 
        }
    //para a iteração quando i e j se "cruzam"
    //chama recursivamente a função para cada metade do vetor
    }while (i < j); 
        if (j > inicio)
            quick_sort(vet, inicio, j, quick_data); 
        if (i < fim)
            quick_sort(vet, i, fim, quick_data);
}

//Função que rearranja a heap em uma heap máxima, raiz com o maior elemento
void rearranjar_heap(int *heap, int tam_heap, int i, Dados* heap_data){
    int esq, dir, maior, aux; 
    //índices para acessar os filhos da esquerda e direita
    esq = 2*i + 1;
    dir = 2*i + 2;
    maior = i; //armazena o índice do maior elemento 
    //verifica se estamos acessando um índice válido, se sim, verifica 
    //se existe um elemento maior que o que já está sendo armazenado 
    heap_data->comp++; 
    if ((esq < tam_heap) && (heap[esq] > heap[maior])){
        maior = esq; 
    }
    heap_data->comp++; 
    if ((dir < tam_heap) && (heap[dir] > heap[maior])){
        maior = dir; 
    }
    //realiza a troca dos elementos de posição maior e i 
    //chama recursivamente a função até que a heap esteja rearranjada
    if(maior != i){
        aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        heap_data->trocas++; 
        rearranjar_heap(heap, tam_heap, maior, heap_data);
    }
}

//Função que constrói uma heap máxima  
void construir_heap(int *heap, int tam_heap, Dados* heap_data){
    //rearranja todos os nós menos os nós folhas 
    //a cada chamada esses nós são raízes de heaps máximas
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i, heap_data); 
    }
}

void heap_sort(int *vet, int n, Dados* heap_data){
    //constrói a heap máxima
    construir_heap(vet, n, heap_data); 
    int tam_heap = n, aux; 
    //inverte de posição o nó raiz com o último nó da heap e rearranja 
    //a heap aṕos a troca, isso é feito n-1 vezes até que esteja ordenado
    for (int i = n-1; i > 0; i--){
        aux = vet[0]; 
        vet[0] = vet[i]; 
        vet[i] = aux; 
        tam_heap--; 
        heap_data->trocas++; 
        rearranjar_heap(vet, tam_heap, 0, heap_data); 
    }
}

//Função que faz a junção de dois subvetores, de forma que eles fiquem ordenados
void intercala(int *vet, int inicio, int meio, int fim, Dados* merge_data){
    int i, j, k;
    int n1, n2;
    //Tamanho dos vetores 
    n1 = meio - inicio + 1;
    n2 = fim - meio; 

    int L[n1+1], R[n2+1]; 

    //Preenchimento dos vetores 
    for (i = 0; i < n1; i++){
        L[i] = vet[inicio + i]; 
    }
    L[n1] = INT_MAX; //sentinela
    for (j = 0; j < n2; j++){
        R[j] = vet[meio + j + 1]; 
    } 
    R[n2] = INT_MAX;  //sentinela2

    i = 0; j = 0; 
    for (k = inicio; k <= fim; k++){
        //compara os elementos de cada metade e os organiza de forma ordenada no 
        //vetor vet. O sentinela garante que se um dos sub-vetores não tiver elementos,
        //o restante vai ser preenchido pelo outro sub-vetor
        merge_data->comp++; 
        if (L[i] <= R[j]){
            vet[k] = L[i]; 
            i++; 
            merge_data->trocas++;
        }else{
            vet[k] = R[j]; 
            j++; 
            merge_data->trocas++; 
        }
    }
}

void merge_sort(int *vet, int inicio, int fim, Dados* merge_data){
    //divide o vetor ao meio até que não seja mais possível e chama a função 
    //recursiva para cada metade do vetor, após as divisões a função intercala 
    //faz a junçã de forma ordenada
    if (inicio < fim){
        int meio = (inicio+fim)/2; 
        merge_sort(vet, inicio, meio, merge_data);
        merge_sort(vet, meio+1, fim, merge_data); 
        intercala(vet, inicio, meio, fim, merge_data); 
    }
}

int* contagem_de_menores(int *vet, int n, Dados* counting_data){
    //armazena quantos elementos são menores que o elemento daquela posição
    int *posicao = (int*)calloc(n, sizeof(int));
    //conta quantos elementos são menores que cada item
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            counting_data->comp++; 
            if (vet[i] < vet[j]){
                posicao[j]++; 
            }
            else{
                posicao[i]++;
            }   
        }
    }
    //vetor em que serão colocados os elementos ordenados
    int *sorted = (int*)malloc(sizeof(int)*n); 
    //o vetor sorted recebe o elemento no índice posicão[i], ou seja, 
    //considerando quantos elementos são menores que o analisado
    for (int i = 0; i < n; i++)
        sorted[posicao[i]] = vet[i];

    return sorted;    
}

//Função que devolve qual digito está na posição pos
int digito(int num, int pos){
    for(int i=0; i<(pos-1); i++)
        num /= 10;

    return num % 10;
}

int* counting_sort(int *vet, int tam, int pos){
    //cada índice corresponde a um número, e a quantidade que essa posição
    //armazena é a quantidade de vezes que esse número aparece no vetor
    //nesse caso, os números são apenas de 0-9
    int tipos[10] = {0};
    //conta quantos dígitos de cada número aparecem 
    for(int i = 0; i < tam; i++)
        tipos[digito(vet[i], pos)]++;
    //soma com a quantidade de vezes que o núemro anterior aparece para fornecer 
    //a posição certa em que esse número deve ocupar no vetor ordenado
    for(int i = 1; i < 10; i++)
        tipos[i] += tipos[i-1];
    //vetor ordenado
    int* sorted = malloc(tam * sizeof(int));
    //armazena os elementos no vetor ordenado de acordo com sua posição
    //determinada pelo vetor tipos, faz um decremento no vetor tipos,
    //pois a cada iteração temos menos um elemento daquele para ser inserido
    for(int i = tam-1; i >= 0; i--){
        sorted[tipos[digito(vet[i], pos)]-1] = vet[i];
        tipos[digito(vet[i], pos)]--;
    }

    return sorted;
}

int* radix_sort(int *vet, int tam, Dados* radix_data){
    //n_dig armazena a quantidade máxima de dígitos que cada número possui
    //loop que itera por todos os dígitos do número, os ordenado os ordenando
    //do mais ao menos significativo utilizando o algoritmo counting sort
    int ctrl=tam, maxdig=0;
    while(ctrl!=0){
    ctrl/=10;
    maxdig++;
    }

    for(int i = 1; i <= maxdig; i++)
        vet = counting_sort(vet, tam, i);

    return vet; 
}