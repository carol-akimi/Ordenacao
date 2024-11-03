#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void rearranjar_heap(int *heap, int tam_heap, int i, int *comp, int *trocas){
    int esq, dir, maior; 
    esq = 2*i + 1;
    dir = 2*1 + 2;
    maior = i; 
    (*comp)++; 
    if (esq < tam_heap && heap[esq] > heap[maior]){
        maior = esq; 
    }
    (*comp)++; 
    if (dir < tam_heap && heap[dir] > heap[maior]){
        maior = dir; 
    }
    if(maior != i){
        int aux = heap[maior];
        heap[maior] = heap[i];
        heap[i] = aux;
        (*trocas)++; 
        rearranjar_heap(heap, tam_heap, maior, comp, trocas);
    }
}

void construir_heap(int *heap, int tam_heap, int *comp, int *trocas){
    for (int i = (tam_heap/2) - 1; i >= 0; i--){
        rearranjar_heap(heap, tam_heap, i, comp, trocas); 
    }
}

void heap_sort(int *vet, int n, int *comp, int *trocas){
    construir_heap(vet, n, comp, trocas);
    for (int i = n; i >= 0; i--){
        int aux = vet[0]; 
        vet[0] = vet[i-1]; 
        vet[i-1] = aux;
        n--; 
        (*trocas)++; 
        rearranjar_heap(vet, n, 0, comp, trocas);  
    }
}

void imprimir_vetor(int *vet, int n){
    for (int i = 0; i < n; i++){
        printf("%d ", vet[i]); 
    }
    printf("\n"); 
}

int main(void){
    int n; 
    scanf("%d", &n);  
    int *vet = (int*) malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++){
        scanf("%d", &vet[i]); 
    }
    int comp = 0; int trocas = 0; 
    heap_sort(vet, n, &comp, &trocas); 
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
    imprimir_vetor(vet, n); 


}