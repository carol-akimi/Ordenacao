#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#define QTD_TESTS 28

typedef struct retorno1{
    long long unsigned int comp, trocas;
}Dados;

Dados bubble_sort(int *vet, int n){
    Dados bubble_data = {0, 0}; 
    for (int i = 0; i < n; i++){
        int troca = 0; 
        for (int j = 0; j < n - 1; j++){
            bubble_data.comp++;
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
                bubble_data.trocas++; 
            }
        }
        if(troca == 0)
            break; 
    }

    return bubble_data; 
}

Dados selection_sort(int *vet, int n){
    Dados selection_data = {0, 0};
    for (int i = 0; i < n-1; i++){
        int min = i; 
        for (int j = i + 1; j < n; j++){
            selection_data.comp++; 
            if (vet[j] < vet[min])
                min = j; 
        }
        if(i != min){
            int aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
            selection_data.trocas++; 
        }
    }
    
    return selection_data; 
}

Dados insertion_sort(int *vet, int n){
    Dados insertion_data = {0, 0}; 
    int j; 
    for (int i = 1; i < n; i++){
        int x = vet[i]; 
        for (j = i - 1; j >= 0; j--){
            insertion_data.comp++; 
            if (vet[j] > x){
                vet[j+1] = vet[j]; 
                insertion_data.trocas++; 
            }else{
                break; 
            }
        }
        vet[j+1] = x;
    }

    return insertion_data; 
}

Dados shell_sort(int *vet, int inc[], int n, int n_inc){
    Dados shell_data = {0, 0}; 
    int i, j; 
    int h; 
    for (int k = 0; k < n_inc; k++){ //vai iterar pelos elementos de inc
        h = inc[k]; 
        //inserção simples 
        for (i = h; i < n; i++){
            int x = vet[i]; 
            for (j = i - h; j >= 0; j -= h){
                shell_data.comp++;
                if (vet[j] > x){
                    vet[j+h] = vet[j]; 
                    shell_data.trocas++; 
                }else{
                    break; 
                }
            }
            vet[j+h] = x; 
        }
    }

    return shell_data; 
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
void quick_sort(int *vet, int inicio, int fim, Dados* quick_data){
    int i = inicio; 
    int j = fim; 
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim], vet); 
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

Dados contagem_de_menores(int *vet, int n){
    Dados menores_data = {0, 0};

    int *posicao = (int*)malloc(sizeof(int)*n); 
    //zerar o vetor posicao 
    for (int i = 0; i < n; i++){
        posicao[i] = 0; 
    }
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            menores_data.comp++; 
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
        
    return menores_data; 
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

Dados radixsort(int *vet, int tam){
    Dados radix_data = {0, 0};
    int ctrl=tam, maxdig=0;
    while(ctrl!=0){
    ctrl/=10;
    maxdig++;
    }

    for(int i = 1; i <= maxdig; i++)
        vet = counting_sort(vet, tam, i);

    return radix_data; 
}

void imprimir_vetor(int *vet, int n){
    for (int i = 0; i < n; i++){
        printf("%d ", vet[i]); 
    }
    printf("\n"); 
}



void testar(const char* algfilename){
    FILE* in = fopen("tests/tests.txt", "r");
    FILE* out=fopen(algfilename, "w");
    fprintf(out, "ordenação, n, tempo, comparações, trocas\n");

    for(int i=0; i<QTD_TESTS; i++){
        char* filename = (char*)malloc(50);
        fscanf(in, " %s", filename); //le qual vai ser o arquivo teste
        FILE* input=fopen(filename, "r"); //abre o arquivo da vez
        int n;
        fscanf(input, "%d", &n);
        int *vet = (int*) malloc(sizeof(int)*n);
        for(int i=0; i<n; i++){
            fscanf(input, "%d", &vet[i]);
        }
        fclose(input);
        Dados dados_coletados = {0, 0};
    
        clock_t ini, fim;
            ini=clock();
        //dados_coletados = bubble_sort(vet, n);
        //dados_coletados = selection_sort(vet, n);
        //dados_coletados = insertion_sort(vet, n);
            //int inc[] = {5, 3, 1};
        //dados_coletados = shell_sort(vet, inc, n, 3); 
        //quick_sort(vet, 0, n-1, &dados_coletados); 
        //heap_sort(vet, n, &dados_coletados); 
        //merge_sort(vet, 0, n-1, &dados_coletados); 
        //dados_coletados = contagem_de_menores(vet, n);
        //dados_coletados = radixsort(vet, n);
            fim=clock();
        free(vet);

        double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
        char* ordem=strtok(filename+6, "/");

        int tracker;
        if(i>7){
            double vet_tempos[5];
            long long unsigned int vet_comp[5], vet_trocas[5];
            if(i==8||i==13||i==18||i==23){
                tracker=i;
            }
            vet_tempos[(i-tracker)] = tempo;
            vet_comp[(i-tracker)] = dados_coletados.comp;
            vet_trocas[(i-tracker)] = dados_coletados.trocas;
            if((i-tracker)!=4)
                continue;
            for(int j=0; j<4; j++){
                tempo+=vet_tempos[j];
                dados_coletados.comp+=vet_comp[j];
                dados_coletados.trocas+=vet_trocas[j];
            }
            tempo/=5;
            dados_coletados.comp/=5;
            dados_coletados.trocas/=5;
        }

        fprintf(out, "%s, %d, %lf, %lld, %lld\n", ordem, n, tempo, dados_coletados.comp, dados_coletados.trocas);
        printf("%s took %lf s for %d %s elements\n\n", algfilename+8, tempo, n, filename+6);
    }

    fclose(in);
    fclose(out);
}

int main(void){
    testar("results/radix.csv");
}

// int testar2(void){
//     FILE* in = fopen("tests.txt", "r");
//         printf("opened the files file\n");
//     FILE* out=fopen("results.csv", "r+");
//         printf("opened results\n");
//     fseek(out, 0, SEEK_END);
//     /*Mudar para cada teste */fprintf(out, "bubble sort, ");

//     for(int i=0; i<QTD_TESTS; i++){
//         char* filename = (char*)malloc(35);
//         fscanf(in, " %s", filename); //le qual vai ser o arquivo teste
//             printf("FILE = %s\n", filename);
//         FILE* input=fopen(filename, "r"); //abre o arquivo da vez
//         int n;
//         fscanf(input, "%d", &n);
//             printf("n = %d\n", n);
//         int *vet = (int*) malloc(sizeof(int)*n);
//         for(int i=0; i<n; i++){
//             fscanf(input, "%d", &vet[i]);
//         }
//         fclose(input);
//         //imprimir_vetor(vet, n);
//         clock_t ini, fim;
//             ini=clock();
//         bubble_sort(vet, n);
//         // selection_sort(vet, n);
//         // insertion_sort(vet, n);
//         // int inc[] = {5, 3, 1};
//         // shell_sort(vet, inc, n, 3); 
//         // quick_sort(vet, 0, n-1); 
//         // heap_sort(vet, n); 
//         // merge_sort(vet, 0, n-1); 
//         // contagem_de_menores(vet, n); 
//         // radixsort(vet, n, n_dig); //rever isso
//             fim=clock();
//         free(vet);

//         double tempo=(double)(fim-ini)/CLOCKS_PER_SEC;
//         fprintf(out, "%lf, ", tempo);
//         printf("%d: bubble sort took %lf s for %d elements\n\n", i, tempo, n);
//     }
//     fprintf(out, "\n");

//     fclose(in);
//     fclose(out);
// }