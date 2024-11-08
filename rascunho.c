#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int *counting_sort(int *vet, int tam, int pos);
int digito(int num, int pos);
int numero_digitos(int* vet, int tam);

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

int main(void){
    int n; 
    scanf("%d", &n);  
    int *vet = (int*) malloc(sizeof(int)*n); 
    for (int i = 0; i < n; i++){
        scanf("%d", &vet[i]); 
    }
    int *sorted; 
    sorted = radixsort(vet, n, 2); 
    imprimir_vetor(sorted, n); 


}