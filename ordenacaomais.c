#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define QTD_TEST 28
#include <limits.h>

void bubble_sort(int *vet, int n){
    int comp = 0; int trocas = 0; 
    for (int i = 0; i < n; i++){
        int troca = 0; 
        for (int j = 0; j < n - i - 1; j++){
            comp++;
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
                trocas++; 
            }
        }
        if(troca == 0){
            break; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void selection_sort(int *vet, int n){
    int comp = 0; int trocas = 0; 
    for (int i = 0; i < n-1; i++){
        int min = i; 
        for (int j = i + 1; j < n; j++){
            comp++; 
            if (vet[j] < vet[min])
                min = j; 
        }
        if(i != min){
            int aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
            trocas++; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void insertion_sort(int *vet, int n){
    int comp = 0; int trocas = 0; 
    int j; 
    for (int i = 1; i < n; i++){
        int x = vet[i]; 
        for (j = i - 1; j >= 0; j--){
            comp++; 
            if (vet[j] > x){
                vet[j+1] = vet[j]; 
                trocas++; 
            }else{
                break; 
            }
        }
        vet[j+1] = x;
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

void shell_sort(int *vet, int inc[], int n, int n_inc){
    int comp = 0; int trocas = 0; 
    int i, j; 
    int h; 
    for (int k = 0; k < n_inc; k++){ //vai iterar pelos elementos de inc
        h = inc[k]; 
        //inserção simples 
        for (i = h; i < n; i++){
            int x = vet[i]; 
            for (j = i - h; j >= 0; j -= h){
                comp++;
                if (vet[j] > x){
                    vet[j+h] = vet[j]; 
                    trocas++; 
                }else{
                    break; 
                }
            }
            vet[j+h] = x; 
        }
    }
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
}

int mediana(int a, int b, int c, int *vet){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

//a quantidade comp e trocas é printado na main 
void quick_sort(int *vet, int inicio, int fim, int *comp, int *trocas){
    int i = inicio; 
    int j = fim; 
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim], vet); 
    do{
        while (vet[i] < pivo){
            i++; 
            (*comp)++; 
        }
        (*comp)++; //quando a condição falha 
        while (vet[j] > pivo){
            j--; 
            (*comp)++; 
        }
        (*comp)++; //quando a condição falha 
        if (i <= j){ 
            int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
            (*trocas)++; 
        }
    }while (i < j); 
        if (j > inicio)
            quick_sort(vet, inicio, j, comp, trocas); 
        if (i < fim)
            quick_sort(vet, i, fim, comp, trocas);
}

void rearranjar_heap(int *heap, int tam_heap, int i, int *comp, int *trocas){
    int esq, dir, maior, aux; 
    esq = 2*i + 1;
    dir = 2*i + 2;
    maior = i; 
    (*comp)++; 
    if ((esq < tam_heap) && (heap[esq] > heap[maior])){
        maior = esq; 
    }
    (*comp)++; 
    if ((dir < tam_heap) && (heap[dir] > heap[maior])){
        maior = dir; 
    }
    if(maior != i){
        aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        (*trocas)++; 
        rearranjar_heap(heap, tam_heap, maior, comp, trocas);
    }
}

//a quantidade comp e trocas é printado na main 
void construir_heap(int *heap, int tam_heap, int *comp, int *trocas){
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i, comp, trocas); 
    }
}

void heap_sort(int *vet, int n, int *comp, int *trocas){
    construir_heap(vet, n, comp, trocas); 
    int tam_heap = n, aux; 
    for (int i = n-1; i > 0; i--){
        aux = vet[0]; 
        vet[0] = vet[i]; 
        vet[i] = aux; 
        tam_heap--; 
        (*trocas)++; 
        rearranjar_heap(vet, tam_heap, 0, comp, trocas); 
    }
}

void intercala(int *vet, int inicio, int meio, int fim, int *comp, int *trocas){
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
        (*comp)++; 
        if (L[i] <= R[j]){
            vet[k] = L[i]; 
            i++; 
        }else{
            vet[k] = R[j]; 
            j++; 
        }
    }
}

void merge_sort(int *vet, int inicio, int fim, int *comp, int *trocas){
    if (inicio < fim){
        int meio = (inicio+fim)/2; 
        merge_sort(vet, inicio, meio, comp, trocas);
        merge_sort(vet, meio+1, fim, comp, trocas); 
        intercala(vet, inicio, meio, fim, comp, trocas); 
    }
}

int *contagem_de_menores(int *vet, int n){
    int comp = 0, trocas = 0; 
    int *posicao = (int*)malloc(sizeof(int)*n); 
    //zerar o vetor posicao 
    for (int i = 0; i < n; i++){
        posicao[i] = 0; 
    }
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            comp++; 
            if (vet[i] < vet[j]){
                posicao[j]++; 
            }
            else{
                posicao[i]++;
            }   
        }
    }
    int *sorted = (int*)malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++){
        sorted[posicao[i]] = vet[i]; 
    }    
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
    return sorted; 
}


int *radixsort(int *vet, int tam, int n_dig){
    //int n_dig = numero_digitos(vet, tam); 
    for(int i = 1; i <= n_dig; i++){
        vet = counting_sort(vet, tam, i);
    }
    printf("Quantidade de comparações: 0\n"); 
    printf("Quantidade de movimentações: 0\n"); 
    return vet; 
}

int *counting_sort(int *vet, int tam, int pos){
    int tipos[10] = {0};
    for(int i = 0; i < tam; i++){
        tipos[digito(vet[i], pos)]++;
    }
    for(int i = 1; i < 10; i++)
        tipos[i] += tipos[i-1];

    int* sorted = malloc(tam * sizeof(int));

    for(int i = tam-1; i >= 0; i--){
        sorted[tipos[digito(vet[i], pos)]-1] = vet[i];
        tipos[digito(vet[i], pos)]--;
    }

    free(vet);
    return sorted;
}

int digito(int num, int pos){
    for(int i=0; i<(pos-1); i++)
        num /= 10;

    return num % 10;
}

void imprimir_vetor(int *vet, int n){
    for (int i = 0; i < n; i++){
        printf("%d ", vet[i]); 
    }
    printf("\n"); 
}

// int main(void){
//     int n; 

//     printf("Tamanho do vetor:\n"); 
//     scanf("%d", &n); 

//     int *vet = (int*) malloc(sizeof(int)*n);
    // printf("Tamanho do vetor:\n"); 
    // scanf("%d", &n); 
    
    // int *vet = (int*) malloc(sizeof(int)*n); 
    // bubble_sort(vet, n);
    // selection_sort(vet, n);
    // insertion_sort(vet, n); 
    // int inc[] = {5, 3, 1};
    // shell_sort(vet, inc, n, 3); 
    // quick_sort(vet, 0, n-1); 
    // heap_sort(vet, n); 
    // merge_sort(vet, 0, n-1); 
    // contagem_de_menores(vet, n); 
    // radixsort(vet, n, 6); //rever isso 

//     clock_t ini, fim;
//     ini=clock();
//     bubble_sort(vet, n);
//     selection_sort(vet, n);
//     insertion_sort(vet, n); 
//     int inc[] = {5, 3, 1};
//     shell_sort(vet, inc, n, 3); 
//     quick_sort(vet, 0, n-1); 
//     heap_sort(vet, n); 
//     merge_sort(vet, 0, n-1); 
//     contagem_de_menores(vet, n); 
//     radixsort(vet, n, n_dig); //rever isso
//     fim=clock();

//     imprimir_vetor(vet, n); 
    
//     double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
//     FILE* f=fopen("results.csv", "r+");
//     fprintf(f, "%lf\n", tempo)

// }

int main(int argc, char* argv[]){
    FILE* in = fopen(argv[1], "r");
    FILE* out=fopen("results.csv", "r+");
    for(int i=0; i<QTD_TEST; i++){
        const char* filename;
        fscanf(in, " %s", filename); //le qual vai ser o arquivo teste
        FILE* input=fopen(filename, "r"); //abre o arquivo da vez
        int n;
        fscanf(input, "%d", &n);
        int *vet = (int*) malloc(sizeof(int)*n);
        for(int i=0; i<n; i++){
            fscanf(input, "%d", &vet[i]);
        }
        fclose(input);
        //imprimir_vetor(vet, n);
        clock_t ini, fim;
            ini=clock();
        bubble_sort(vet, n);
        // selection_sort(vet, n);
        // insertion_sort(vet, n);
        // int inc[] = {5, 3, 1};
        // shell_sort(vet, inc, n, 3); 
        // quick_sort(vet, 0, n-1); 
        // heap_sort(vet, n); 
        // merge_sort(vet, 0, n-1); 
        // contagem_de_menores(vet, n); 
        // radixsort(vet, n, n_dig); //rever isso
            fim=clock();
        free(vet);

        double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
        fprintf(out, "%lf, ", tempo);
        printf("%d: BUBBLE SORT TOOK %lf s for %d elements\n", i, tempo, n);
    }
    fprintf(out, "\n");

    fclose(in);
    fclose(out);
}