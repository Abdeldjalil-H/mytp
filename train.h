
#ifndef TRAIN_H
#define TRAIN_H

#define TAILLE_MAX_DE_QUAI 10

typedef struct train{
    int id;
    int capaciteMAX;
    int tauxDeRemplissage;
    listePassagers_t listeDesPassagers;
    chaine destination;
    int kmRestant;
    int vitesse;
}train_t;

typedef train_t listeTrain_t[TAILLE_MAX_DE_QUAI];

train_t CreerTrain(int, int, chaine);

train_t ViderTrain(train_t);

int AjouterTrain(train_t*, int, int, chaine);

int SiTrainRemplis(train_t);

void AfficherTrains(train_t*, int);

void MiseAJourTableauDesTrain(train_t, train_t*, int);
#endif
