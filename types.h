#ifndef TYPES_H
#define TYPES_H

#define MaxTrain 20
#define MaxParkingRails 8
#define MapSize 20

#define TAILLE_MAX_DE_QUAI 10

#define TAILLE_CHAINE 40

typedef char chaine[TAILLE_CHAINE];

typedef struct passager_t * ptr_passager;
typedef struct passager_t{
    int id;
    chaine destination;
    ptr_passager suivant;
}passager_t;

/*
On définie la liste par cette structure. 
On ajoute l'adresse de dernier éléments et la taille
pour rendre la complexité de Taille et avoirDernier en O(1).
*/
typedef struct{
    ptr_passager tete;
    int taille;
    ptr_passager dernier;
}listePassagers_t;

typedef struct train{
    int id;
    int capaciteMAX;
    int tauxDeRemplissage;
    listePassagers_t listeDesPassagers;
    chaine destination;
    int kmRestant;
    int vitesse;
}train_t;

//typedef train_t listeTrain_t[TAILLE_MAX_DE_QUAI];
#define ID_QUAI 40
typedef struct quai{
    char id[ID_QUAI];
    train_t listeDesTrains[TAILLE_MAX_DE_QUAI];
    int premierTrain; //sommet de la pile
    int capacite;
}quai_t;

#endif