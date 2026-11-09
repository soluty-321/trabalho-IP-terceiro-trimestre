#ifndef CARTA_H

#define CARTA_H

typedef struct {
    int id;
    char tema[50];
    char nome[50];
    char grupo[50];
    char categoria[50];
    int atri1;
    int atri2;
    int atri3;
    int atri4;
    int especial;
} Carta;

#endif