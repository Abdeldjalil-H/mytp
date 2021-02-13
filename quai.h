
#ifndef QUAI_H
#define QUAI_H

typedef struct quai{
    int id;
    listeTrain_t listeTrain;
    int premierTrain; //sommet de la pile
    int capacite;
}quai_t;

quai_t CreeUnParkingRail(int ,int);

int Empiler (train_t ,quai_t *);

train_t Depiler(quai_t *);

int PileVide(quai_t *);

int PileRemplie(quai_t);

#endif
