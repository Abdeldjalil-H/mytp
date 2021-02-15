
#ifndef QUAI_H
#define QUAI_H
#include "types.h"

quai_t CreerUnParkingRail(char* ,int);

int Empiler (train_t ,quai_t *);

train_t Depiler(quai_t *);

int PileVide(quai_t *);

int PileRemplie(quai_t);

quai_t TrouverDesTrainDisponible(quai_t, train_t*, int);

int AjouterQuais(quai_t*, int, chaine, int, train_t*, int);

void UpdateQuais(quai_t*, int, train_t*, int);

void AfficherParkingRail(quai_t*, int);
#endif
