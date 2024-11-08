#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void bubble_sort(int *vet, int n){
    int troca = 1; 
    for (int i = 0; i < n; i++){
        int troca = 0; 
        for (int j = 0; j < n - 1; j++){
            if (vet[j] > vet[j + 1]){
                int aux = vet[j]; 
                vet[j] = vet[j + 1]; 
                vet[j + 1] = aux; 
                troca = 1;
            }
        }
        if(troca == 0)
            break; 
    }
}

void selection_sort(int *vet, int n){
    for (int i = 0; i < n-1; i++){
        int min = i; 
        for (int j = i + 1; j < n; j++){
            if (vet[j] < vet[min])
                min = j; 
        }
        if(i != min){
            int aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
        }
    }
}

void insertion_sort(int *vet, int n){
    int j; 
    for (int i = 1; i < n; i++){
        int x = vet[i]; 
        for (j = i - 1; j >= 0 && vet[j] > x; j--){
            vet[j+1] = vet[j]; 
        }
        vet[j+1] = x; 
    }
}

void shell_sort(int *vet, int inc[], int n, int n_inc){
    int i, j; 
    int h; 
    for (int incre = 0; incre < n_inc; incre++){ //vai iterar pelos elementos de inc
        h = inc[incre]; 
        //inserção simples 
        for (i = h; i < n; i++){
            int x = vet[i]; 
            for (j = i - h; j >= 0 && vet[j] > x; j -= h){
                vet[j+h] = vet[j]; 
            }
            vet[j+h] = x; 
        }
    }

}

int mediana(int a, int b, int c, int *vet){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

void quick_sort(int *vet, int inicio, int fim){
    int i = inicio; 
    int j = fim; 
    int pivo = mediana(vet[inicio], vet[(inicio+fim)/2], vet[fim], vet); 
    do{
        while (vet[i] < pivo) i++; 
        while (vet[j] > pivo) j--;  
        if (i <= j){
            int aux = vet[i]; 
            vet[i] = vet[j]; 
            vet[j] = aux; 
            i++; 
            j--; 
        }
    }while (i < j); 
    if (j > inicio)
        quick_sort(vet, inicio, j); 
    if (i < fim)
        quick_sort(vet, i, fim);

}


void rearranjar_heap(int *heap, int tam_heap, int i){
    int esq, dir, maior; 
    esq = 2*i + 1;
    dir = 2*i + 2;
    maior = i; 
    if ((esq < tam_heap) && (heap[esq] > heap[maior])){
        maior = esq; 
    }
    if ((dir < tam_heap) && (heap[dir] > heap[maior])){
        maior = dir; 
    }
    if(maior != i){
        int aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        rearranjar_heap(heap, tam_heap, maior);
    }
}

void construir_heap(int *heap, int tam_heap){
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i); 
    }
}

void heap_sort(int *vet, int n){
    construir_heap(vet, n); 
    int tam_heap = n, aux; 
    for (int i = n-1; i > 0; i--){
        aux = vet[0]; 
        vet[0] = vet[i]; 
        vet[i] = aux; 
        tam_heap--; 
        rearranjar_heap(vet, tam_heap, 0); 
    }
}

void merge_sort(int *vet, int inicio, int fim){
    if (inicio < fim){
        int meio = (inicio+fim)/2; 
        merge_sort(vet, inicio, meio);
        merge_sort(vet, meio+1, fim); 
        intercala(vet, inicio, meio, fim); 
    }
}

void intercala(int *vet, int inicio, int meio, int fim){
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
        if (L[i] <= R[j]){
            vet[k] = L[i]; 
            i++; 
        }else{
            vet[k] = R[j]; 
            j++; 
        }
    }
}

int *contagem_de_menores(int *vet, int n){
    int *posicao = (int*)malloc(sizeof(int)*n); 
    //zerar o vetor posicao 
    for (int i = 0; i < n; i++){
        posicao[i] = 0; 
    }
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
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
    return sorted; 
}

int *radixsort(int *vet, int tam, int n_dig){
    //int n_dig = numero_digitos(vet, tam); 
    for(int i = 1; i <= n_dig; i++){
        vet = counting_sort(vet, tam, i);
    }
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

int main(void){
    int n; 

    printf("Tamanho do vetor:\n"); 
    scanf("%d", &n); 

    int *vet = (int*) malloc(sizeof(int)*n); 
    bubble_sort(vet, n);
    selection_sort(vet, n);
    insertion_sort(vet, n); 
    int inc[3] = {5, 3, 1}; 
    shell_sort(vet, inc, n, 3); 
    quick_sort(vet, 0, n-1); 
    heap_sort(vet, n); 
    merge_sort(vet, 0, n-1); 
    contagem_de_menores(vet, n); 
    radixsort(vet, n, 6); 

    imprimir_vetor(vet, n); 
    

}