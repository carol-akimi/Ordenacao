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

void RodarTestes(AlgOrdenacao** algoritmos){
    const char* alg_nomes[QTD_SORTS] = {
        "bubble", "selection", "insertion",
        "shell", "quick", "heap",
        "merge", "counting", "radix"
    };
    FILE* in = fopen("tests/tests.txt", "r");

    for(int i = 0; i < QTD_SORTS; i++){
        char outfilename[25];
        sprintf(outfilename, "result2/%s.csv", alg_nomes[i]);
        FILE* out = fopen(outfilename, "w");
        fprintf(out, "ordenação, n, tempo, comparações, trocas\n");

        for(int j = 0; j < QTD_TESTS; j++){
            char* testfilename = (char*) malloc(50);
            fscanf(in, " %s", testfilename); //le qual vai ser o arquivo teste
            FILE* input = fopen(testfilename, "r"); //abre o arquivo da vez

            int n;
            fscanf(input, "%d", &n);

            int *vet = (int*) malloc(n*sizeof(int));
            for(int i = 0; i < n; i++){
                fscanf(input, "%d", &vet[i]);
            }
            fclose(input);

            Dados dados_coletados = {0, 0};

            printf("Rodando %s sort... Teste %d/%d: %s\n", alg_nomes[i], j+1, QTD_TESTS, testfilename + 6);
        
            clock_t ini, fim;
            ini=clock();
            algoritmos[i](vet, n, &dados_coletados);
            fim=clock();
            free(vet);

            double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
            char* ordem = strtok(testfilename + 6, "/");

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

            fprintf(out, "%s, %d, %lf, %lld, %lld\n", ordem, n, tempo, dados_coletados.comp, dados_coletados.trocas);
            printf("Tempo do %s sort foi %lf s para %d elementos com distribuição '%s'\n\n", alg_nomes[i], tempo, n, ordem);

            free(testfilename);
        }
        fclose(out);
        rewind(in);
    }
    fclose(in);
}

void bubble_sort(int *vet, int n, Dados* bubble_data){
    for (int i = 0; i < n; i++){
        int troca = 0; 
        for (int j = 0; j < n - 1; j++){
            bubble_data->comp++;
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
                bubble_data->trocas++; 
            }
        }
        if(troca == 0)
            break; 
    }
}

void selection_sort(int *vet, int n, Dados* selection_data){
    for (int i = 0; i < n-1; i++){
        int min = i; 
        for (int j = i + 1; j < n; j++){
            selection_data->comp++; 
            if (vet[j] < vet[min])
                min = j; 
        }
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
        int x = vet[i]; 
        for (j = i - 1; j >= 0; j--){
            insertion_data->comp++; 
            if (vet[j] > x){
                vet[j+1] = vet[j]; 
                insertion_data->trocas++; 
            }else{
                break; 
            }
        }
        vet[j+1] = x;
    }
}

void shell_sort(int *vet, int inc[], int n, int n_inc, Dados* shell_data){ 
    int i, j; 
    int h; 
    for (int k = 0; k < n_inc; k++){ //vai iterar pelos elementos de inc
        h = inc[k]; 
        //inserção simples 
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
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim]); 
    do{
        while (vet[i] < pivo){
            i++; 
            quick_data->comp++; 
        }
        quick_data->comp++; //quando a condição falha 
        while (vet[j] > pivo){
            j--; 
            quick_data->comp++; 
        }
        quick_data->comp++; //quando a condição falha 
        if (i <= j){ //conto essa comparação?
            int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
            quick_data->trocas++; 
        }
    }while (i < j); 
        if (j > inicio)
            quick_sort(vet, inicio, j, quick_data); 
        if (i < fim)
            quick_sort(vet, i, fim, quick_data);
}

void rearranjar_heap(int *heap, int tam_heap, int i, Dados* heap_data){
    int esq, dir, maior, aux; 
    esq = 2*i + 1;
    dir = 2*i + 2;
    maior = i; 
    heap_data->comp++; 
    if ((esq < tam_heap) && (heap[esq] > heap[maior])){
        maior = esq; 
    }
    heap_data->comp++; 
    if ((dir < tam_heap) && (heap[dir] > heap[maior])){
        maior = dir; 
    }
    if(maior != i){
        aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        heap_data->trocas++; 
        rearranjar_heap(heap, tam_heap, maior, heap_data);
    }
}

//a quantidade comp e trocas é printado na main 
void construir_heap(int *heap, int tam_heap, Dados* heap_data){
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i, heap_data); 
    }
}

void heap_sort(int *vet, int n, Dados* heap_data){
    construir_heap(vet, n, heap_data); 
    int tam_heap = n, aux; 
    for (int i = n-1; i > 0; i--){
        aux = vet[0]; 
        vet[0] = vet[i]; 
        vet[i] = aux; 
        tam_heap--; 
        heap_data->trocas++; 
        rearranjar_heap(vet, tam_heap, 0, heap_data); 
    }
}

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
    if (inicio < fim){
        int meio = (inicio+fim)/2; 
        merge_sort(vet, inicio, meio, merge_data);
        merge_sort(vet, meio+1, fim, merge_data); 
        intercala(vet, inicio, meio, fim, merge_data); 
    }
}

int* contagem_de_menores(int *vet, int n, Dados* counting_data){
    int *posicao = (int*)calloc(n, sizeof(int));

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
    int *sorted = (int*)malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++)
        sorted[posicao[i]] = vet[i];

    return sorted;    
}

int digito(int num, int pos){
    for(int i=0; i<(pos-1); i++)
        num /= 10;

    return num % 10;
}

int* counting_sort(int *vet, int tam, int pos){
    int tipos[10] = {0};
    for(int i = 0; i < tam; i++)
        tipos[digito(vet[i], pos)]++;

    for(int i = 1; i < 10; i++)
        tipos[i] += tipos[i-1];

    int* sorted = malloc(tam * sizeof(int));

    for(int i = tam-1; i >= 0; i--){
        sorted[tipos[digito(vet[i], pos)]-1] = vet[i];
        tipos[digito(vet[i], pos)]--;
    }

    return sorted;
}

int* radix_sort(int *vet, int tam, Dados* radix_data){
    int ctrl=tam, maxdig=0;
    while(ctrl!=0){
    ctrl/=10;
    maxdig++;
    }

    for(int i = 1; i <= maxdig; i++)
        vet = counting_sort(vet, tam, i);

    return vet; 
}