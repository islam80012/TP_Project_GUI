#include <stdio.h>
#include <stdlib.h>

void echange(int *a,int *b){
    int tmp =*a;
    *a = *b;
    *b = tmp;
}

void triSelection(int taille , int T[]){

    for(int i=0;i<taille-1;i++){
        int min_idx = i;
        for(int j=i+1;j<taille;j++){
            if(T[j]<T[min_idx])
                min_idx=j;
        }
        echange(&T[min_idx],&T[i]);
    }
}

void afficher(int T[],int taille){
    for(int i=0;i<taille;i++){
        printf("%d ",T[i]);
    }
    printf("\n");
}
int main(){
    int taille = 6;
    int T[] = {20,12,10,35,25,0};
    printf("T initial : ");
    afficher(T,taille);
    triSelection(taille,T);
    printf("T trie dans lordre croissant: ");
    afficher(T,taille);
}
