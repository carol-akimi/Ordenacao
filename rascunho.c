#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int mediana(int a, int b, int c, int *vet){
    if((a >= b && a <= c)||(a <= b && a >= c))
        return a;
    else if((b>=a && b<=c)||(b<=a && b >= c))
        return b;
    else
        return c;
}

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
        if (i <= j){ //conto essa comparação?
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
    quick_sort(vet, 0, n-1, &comp, &trocas); 
    printf("Quantidade de comparações: %d\n", comp); 
    printf("Quantidade de movimentações: %d\n", trocas); 
    imprimir_vetor(vet, n); 


}