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
    long posicion=hash(key,map->capacity);
    if(searchMap(map,key)!=NULL)
    {
        if(is_equal(map->buckets[posicion]->key,key)==1)
        {
            map->buckets[posicion]->key=NULL;
            map->size--;
        }
        else
        {
            long flag=1;
            while(flag==1)
            {
                if(map->buckets[posicion]==NULL)
                {
                    flag=2;
                }
                if(is_equal(map->buckets[posicion]->key,key)==1)
                {
                    map->buckets[posicion]->key=NULL;
                    map->size--;
                    flag=0;
                }
                else
                {
                    posicion=(posicion+1)%map->capacity;
                }
            }
        }
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    long posicion=hash(key,map->capacity);
    int flag=1;
    if(is_equal(map->buckets[posicion]->key,key)==1)
    {
        map->current=posicion;
        return map->buckets[posicion];
    }
    else
    {
        while(flag==1)
        {
            if(map->buckets[posicion]==NULL)
            {
                return NULL;
            }
            if(is_equal(map->buckets[posicion]->key,key)==1)
            {
                map->current=posicion;
                return map->buckets[posicion];
            }
            else
            {
                posicion=(posicion+1)%map->capacity;
            }
        }
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    if(map->buckets[0] != NULL && map->buckets[0]->key!=NULL)
    {
        map->current=0;
        return map->buckets[0];
    }
    else
    {
        long flag=1;
        long i =1;
        while(flag==1)
        {
            if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
            {
                map->current=i;
                return map->buckets[i];
            }
            else
            {
                i=(i+1)%map->capacity;
                if(i==0)
                {
                    map->current=i;
                    return NULL;
                }
            }
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    long aux;
    if(map->buckets[map->current+1]!=NULL && map->buckets[map->current+1]->key!=NULL)
    {
        aux=map->current+1;
        map->current++;
        return map->buckets[aux];
    }
    else
    {
        long flag = 1;
        long i=map->current+2;
        while(flag==1)
        {
            if(map->buckets[i]!=NULL || map->buckets[i]->key!=NULL)
            {
                map->current=i;
                return map->buckets[i];
            }
            else
            {
                if(i==map->capacity-1)
                {
                    map->current=i;
                    return NULL;
                }
                i=(i+1)%map->capacity;
            }
        }

    }
    return NULL;
}
