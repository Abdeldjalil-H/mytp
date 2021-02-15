#include "passager.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Cette fonction a pour objectif de créer un passager
ayant un identifiant et une destination particulière.
*/
ptr_passager CreerPassager(int id, chaine dest){
    ptr_passager p = (ptr_passager) malloc(sizeof(passager_t));
    if(p == NULL){
        printf("Error d'allocation, on ne peut pas creer un passager maintenemt.\n");
        return p;
    }
    p->id = id;
    strcpy(p->destination, dest);
    p->suivant = NULL;
    return p;
}

/*
Cette fonction teste si la liste des passagers est vide.
*/
int SiListeVide(listePassagers_t listePassagers){
   return (listePassagers.tete == NULL); 
}

/*
Cette fonction parcourt une liste et retourne son dernier élément.
*/
ptr_passager AvoirDernierElementList(listePassagers_t liste){
    return liste.dernier;
}
/*
Cette fonction vérifie si un ID existe dans la liste des passagers.
*/
int ExistIdDansListe(int id, listePassagers_t liste){
    ptr_passager p = liste.tete;

    while(p != NULL){
        if(p->id == id)
            return 1;
        p = p->suivant;
    }
    return 0;
}

/*
Cette fonction parcourt une liste et retourne sa taille.
*/
int TailleListe(listePassagers_t liste){
    return liste.taille;
}
/*
cette fonction supprime le suivant de p dans une 
liste des passagers 'liste' et met à jour le contenu
de 'liste'
*/
passager_t SupprimerTete(listePassagers_t *liste){
    if(liste->taille <= 1){
        free(liste->tete);
        liste->taille = 0;
        liste->dernier = NULL;
        return;
    }
    else{
        ptr_passager p = liste->tete;
        passager_t val = *p;
        liste->tete = liste->tete->suivant;
        free(p);
        liste->taille--;
        return val;
    }
    
}
passager_t SupprimerSuivant(ptr_passager p, listePassagers_t* liste){
    passager_t returnedPassager = *(p->suivant);
    ptr_passager q = p->suivant->suivant;
    free(p->suivant);
    p->suivant = q;
    liste->taille--;
    if(q == NULL) liste->dernier = p;
    return returnedPassager;
}
/*
cette fonction ajoute 'passagerAjoute' ou suivant de 'courant' 
dans une  liste des passagers 'liste' et met à jour le contenu
de 'liste'
*/
void AjouterSuivant(ptr_passager courant, listePassagers_t* liste, ptr_passager passagerAjoute){
    passagerAjoute->suivant = courant->suivant;
    courant->suivant = passagerAjoute;
    liste->taille++;
    if(passagerAjoute->suivant == NULL) liste->dernier = passagerAjoute;
}
void AjouterTete(listePassagers_t* liste, ptr_passager tete){
    liste->tete = tete;
    liste->taille++;
    liste->dernier = tete;
}
listePassagers_t CreerListePassagers(){
    listePassagers_t liste;
    liste.tete = NULL;
    liste.dernier = NULL;
    liste.taille = 0;
    return liste;
}
/*
Annuler une réservation tend à rechercher un ID dans une liste, extraire le passager de la liste et s’assurer que le chainage du parent avec l’enfant est assuré correctement.
*/
listePassagers_t AnnulerReservation(listePassagers_t liste, int id){
    ptr_passager p = liste.tete;
    if(p->id == id){
        SupprimerTete(&liste);
        return liste;
    }
    while((p->suivant != NULL) && (p->suivant->id != id)){
        p = p->suivant;
    }
    if (p->suivant != NULL){ //donc p->suivant->id = id
        SupprimerSuivant(p, &liste);
    }
    else
        printf("Passager de ID = %d n'est pas trouvé.\n",id);
    
    return liste;
}

/*
Après que la réservation soit faite, l’embarquement effectif du passager doit être réalisé en ajoutant le passager dans la liste des passagers du train. Cette fonction retourne une liste de passager et ajoute la structure Passager (passagerAAjouter) dans la liste.
*/
listePassagers_t AjouterPassagerDansLaListe(ptr_passager passagerAAjouter,listePassagers_t *liste){
    /*liste->dernier->suivant = passagerAAjouter;
    liste->dernier = liste->dernier->suivant;
    liste->dernier->suivant = NULL;
    liste->taille++;*/
    AjouterSuivant(liste->dernier, liste, passagerAAjouter);
    return *liste;
}
/*
Affiche un passager en énumérant ses propriétés. Identifiant, Destination 
*/
void AfficherPassagers(listePassagers_t liste){
    if(liste.taille == 0)
        printf("\n**Aucune reservation faite!**\n");
    else{
        ptr_passager p = liste.tete;
        printf("\n====Liste des réservations====\n");
        while (p != NULL){
            printf("Le passager avec l'ID %d a reservé la destination %s.\n",p->id,p->destination);
            p = p->suivant;
        }
        printf("\n");
    }
}
/*
Pour supprimer un passager de la liste des passagers en attente et le mettre dans la liste des passagers dans le train, cette fonction est extrêmement utile. Elle supprime un passager de la liste d’attente et le retourne pour que par la suite il soit ajouté dans la liste des passagers du train.
*/
passager_t SupprimerPassagerListeAttenteEtLeRetourner(listePassagers_t * liste, int id){

    if (liste->tete->id == id){
        return SupprimerTete(liste);
    }

    ptr_passager p;
    p = liste->tete;
    while((p->suivant) && (p->suivant->id != id)){
        p = p->suivant;
    }
 
    if(p->suivant != NULL) //donc p->suivant->id = id, on supprime le suivant
        return SupprimerSuivant(p, liste);
    else{
        printf("aucune suppression Faite !!! faite !");
        return;
    }
}

/*
Cette fonction a pour but de réserver une place d’un passager dans un train. 
Elle doit vérifier si la destination du passager et du train est la même. 
Elle doit aussi vérifier si il y’a de la place dans le train. 
Incrémenter le nombre de places prise dans le cas où la réservation est réussie.
*/
listePassagers_t ReservationPlace(listePassagers_t ListePassagers, train_t * Trains, int NumTrain, chaine Destination){

    int destinationTrouvee = 0;

    //Vérifier si la destination est disponible
    for (int i=0; i<NumTrain; i++)
        if ((!destinationTrouvee)&& (strcmp(Trains[i].destination,Destination) == 0)){
            destinationTrouvee = 1;
            break;
        }

    // ajouter dans la liste des passagers en attente d'embarquement
    if(destinationTrouvee){
        //Liste Vide, Création du premier élement
        if(ListePassagers.tete == NULL){
  
            ListePassagers = CreerListePassagers();
            AjouterTete(&ListePassagers, CreerPassager(0,Destination));
            return ListePassagers;
        }

        //Liste Non vide, aller au dernier element de la liste et ajouter un passager
        AjouterSuivant(ListePassagers.dernier, &ListePassagers, CreerPassager(ListePassagers.dernier->id + 1,Destination));
        
    }
    else //destination non trouvé
        printf("La destination %s n'est pas disponible dans notre gare\n",Destination);

    return ListePassagers;
}
