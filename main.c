#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 101

typedef struct hash{
    int info;
    struct hash *prox;
}TH;

typedef TH *Hash[TAM_MAX];

int calcula_hash(int info, int tam){
    return info % tam;
}

void inicializa(Hash tab, int tam){
    for(int i = 0; i < tam; i++)
        tab[i] = NULL;
}

TH * aloca(int info){
    TH *novo = (TH*) malloc(sizeof(TH));
    novo->info = info;
    novo->prox = NULL;
    return novo;
}

void insere(Hash tab, int tam, int info){
    int pos = calcula_hash(info,tam);
    TH *p = tab[pos];
    TH *ant = NULL;
    while(p && p->info != info){
        ant = p;
        p = p->prox;
    }
    if(p){
        p->info = info;
        return;
    }
    TH * novo = aloca(info);
    if(!ant){
        tab[pos] = novo;
        return;
    }
    ant->prox = novo;
    return;
}

TH *busca(int tam, int info, Hash tab){
    TH *p = tab[calcula_hash(info,tam)];
    if(!p)
        return NULL;
    return p;
}

void libera(Hash tab, int tam){
    for(int i = 0; i< tam; i++){
        if(tab[i]){
            TH * aux = tab[i];
            TH * aux2 = aux;
            while(aux){
                aux = aux->prox;
                free(aux2);
                aux2 = aux;
            }
        }
    }
}

void retira(Hash tab, int info, int tam){
    TH * aux = busca(tam, info, tab);
    if(!aux)
        return;
    int pos = calcula_hash(info, tam);
    TH * ant;
    if(tab[pos] == aux){
        ant = tab[pos];
        tab[pos] = aux->prox;
        free(ant);
        return;
    }
    ant = tab[pos];
    while(ant->prox != aux)
        ant = ant->prox;
    ant->prox = aux->prox;
    free(aux);
    return;
}

void imprime(Hash tab, int m){
    for(int i = 0; i < m; i++){
        printf("%d: ", i);
        if(tab[i]){
            TH *p = tab[i];
            printf("\n");
            while(p){
                printf("\t%d\t%p\n", p->info, p->prox);
                p = p->prox;
            }
        }
        else printf("NULL\n");
    }
}

int main()
{

    Hash tab;
    inicializa(tab,TAM_MAX);

    int volta = 1, info;
    while(volta){
        printf("\nDigite o valor a ser inserido:");
        scanf("%d", &info);
        insere(tab,TAM_MAX, info);
        printf("HASH: %d", calcula_hash(info, TAM_MAX));
        printf("\n 0 - sair / 1 - inserir outro valor: ");
        scanf("%d", &volta);
    }
    imprime(tab, TAM_MAX);

    do{
        printf("\n\nDigite a info a ser excluida");
        scanf("%d", &info);
        retira(tab, info, TAM_MAX);
        printf("\n 0 - sair / 1 - inserir outro valor: ");
        scanf("%d", &volta);

    }while(volta);
    imprime(tab, TAM_MAX);

    libera(tab, TAM_MAX);

    return 0;
}
