#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long posicion=hash(key,map->capacity);
    Pair *nuevoPar=createPair(key,value);
    if(map->buckets[posicion]==NULL)
    {
        map->buckets[posicion]=nuevoPar;
        map->size++;
        map->current=posicion;
    }
    else
    {
        int flag = 1;
        while(flag==1)
        {
            if(map->buckets[posicion]!=NULL && map->buckets[posicion]->key !=NULL)
            {
                posicion=(posicion+1)%map->capacity;
            }
            else
            {
                flag=0;
            }
        }
        map->buckets[posicion]=nuevoPar;
        map->size++;
        map->current=posicion;
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *mapa=(HashMap *)malloc(sizeof(HashMap));
    mapa->buckets = (Pair **)calloc(capacity,sizeof(Pair *));
    mapa->size=0;
    mapa->capacity=capacity;
    mapa->current=-1;
    int i;
    for(i=0;i<capacity;i++)
    {
        mapa->buckets[i]=NULL;
    }

    return mapa;
}

void eraseMap(HashMap * map,  char * key) {

}

Pair * searchMap(HashMap * map,  char * key) {   
    long posicion=hash(key,map->capacity);
    int flag=1;
    while(flag==1)
    {
        if(map->buckets[posicion]==NULL)
        {
            flag=0;
        }
        else
        {
            if(map->buckets[posicion]->key!=key)
            {
                posicion=(posicion+1)%map->capacity;
            }
            else
            {
                map->current=posicion;
                flag=3;
            }
        }
    }
    if(flag==0)
    {
        return NULL;
    }
    if(flag==3)
    {
        return map->buckets[posicion];
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
