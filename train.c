#include "train.h"
/*
Fonctions de création d’un train en attribuant les caractéristiques du train aux structures. 
*/
train_t CreerTrain(int id, int nbrPlaces, chaine dest){
    train_t t;
    t.id = id;
    t.capaciteMAX = nbrPlaces;
    t.destination = dest;
    t.kmRestant = -1;

    return t;
}

/*
Lorsqu’un train rentre d’un voyage, il doit être vidé des différents passagers (liste des passagers dans le train) ainsi que le nombre de places prises. 
*/
train_t ViderTrain(train_t t){
    t.kmRestant = -1;
    t.tauxDeRemplissage = 0;
    
    ptr_passager tmp, tete;
    tete = t.listeDesPassagers.tete;
    while(tete != NULL){
        tmp = tete;
        tete = tete->suivant;
        free(tmp);
    }
    t.listeDesPassagers.tete = NULL;
    
    return t;
}

/*
la fonction AjouterTrain crée et ajoute des trains dans 
une structure de tableau faite spécialement pour stocker 
les différentes instances de train.
*/
int AjouterTrain(train_t* trains, int id, int capacite, chaine dest){
    train_t t = CreerTrain(id, capacite, dest);
    trains[id] = t;

    return id + 1;
}

int SiTrainRemplis(train_t t){
    return (t.tauxDeRemplissage == t.capaciteMAX);
}

void AfficherTrains(train_t* Trains, int nbrTrains){

    printf("Il y'a %d trains dans la gare.\n\n", nbrTrains);
    for (int i=0;i<nbrTrains;i++){
        // calcul du pourcentage de remplissage
        float Pourcentage=((float)Trains[i].tauxDeRemplissage/(float)Trains[i].capaciteMAX)*100;
        if (Trains[i].kmRestant == -1)
            printf("Train ID= %d est disponible pour %s \n",Trains[i].id, Trains[i].destination);
        else if (Trains[i].kmRestant == 0)
            printf("Train ID= %d dans le quai, remplis a %.2f %%, en attente de départ vers %s \n",Trains[i].id,Pourcentage, Trains[i].destination);
        else
            printf("Train ID %d en Trajet passagers: %d, %.2f %%, ===== reste:%d Km ====> %s\n\n",Trains[i].id,Trains[i].tauxDeRemplissage,Pourcentage,Trains[i].kmRestant,Trains[i].destination);
    }
}

void MiseAJourTableauDesTrain(train_t TrainPourDepart,train_t* Trains,int NumTrain){
    for (int i=0; i < NumTrain;i++){
        if (TrainPourDepart.id == Trains[i].id){
            Trains[i] = TrainPourDepart;
            return;
        }
    }
}