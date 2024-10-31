#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void bubble_sort(int *vet, int n){
    int comp = 0; int trocas = 0; 
    for (int i = 0; i < n; i++){
        int troca = 0; 
        for (int j = 0; j < n - 1; j++){
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

    bubble_sort(vet, n);
    imprimir_vetor(vet, n); 
    

}