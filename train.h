
#ifndef TRAIN_H
#define TRAIN_H

#include "types.h"

train_t CreerTrain(int, int, chaine);

train_t ViderTrain(train_t);

int AjouterTrain(train_t*, int, int, chaine);

int SiTrainRemplis(train_t);

void AfficherTrains(train_t*, int);

void MiseAJourTableauDesTrain(train_t, train_t*, int);

void TrainEnMarche(quai_t*,int, train_t*, int);

//listePassagers_t Embarquement(quai_t*, int, listePassagers_t, chaine**, int, train_t*, int);
listePassagers_t Embarquement(quai_t*, int, listePassagers_t, chaine Destinations[MapSize][2], int, train_t*, int);
#endif
