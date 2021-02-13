
#ifndef PASSAGER_H
#define PASSAGER_H

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

ptr_passager CreerPassager(int, chaine);

int SiListeVide(ptr_passager);

int TailleListe(ptr_passager);

ptr_passager AvoirDernierElementList(ptr_passager);

int ExistIdDansListe(int ,ptr_passager);

void AnnulerReservation(int ,ptr_passager *);

ptr_passager AjouterPassagerDansLaListe(ptr_passager ,listePassagers_t*);

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
