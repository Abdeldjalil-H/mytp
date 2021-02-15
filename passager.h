
#ifndef PASSAGER_H
#define PASSAGER_H
#include "types.h"

ptr_passager CreerPassager(int, chaine);

int SiListeVide(listePassagers_t);

int TailleListe(listePassagers_t);

ptr_passager AvoirDernierElementList(listePassagers_t);

int ExistIdDansListe(int ,listePassagers_t);

listePassagers_t AnnulerReservation(listePassagers_t,int);

listePassagers_t AjouterPassagerDansLaListe(ptr_passager ,listePassagers_t*);

void AfficherPassagers(listePassagers_t);

passager_t SupprimerSuivant(ptr_passager, listePassagers_t*);

passager_t SupprimerPassagerListeAttenteEtLeRetourner(listePassagers_t*, int);

listePassagers_t ReservationPlace(listePassagers_t, train_t *, int , chaine);

listePassagers_t CreerListePassagers();

void AjouterTete(listePassagers_t*, ptr_passager);

void AjouterSuivant(ptr_passager, listePassagers_t*, ptr_passager);

passager_t SupprimerSuivant(ptr_passager, listePassagers_t*);

passager_t SupprimerTete(listePassagers_t *);
#endif
