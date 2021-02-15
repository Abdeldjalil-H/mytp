#include "train.h"
#include "passager.h"
#include "quai.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Fonctions de création d’un train en attribuant les caractéristiques du train aux structures. 
*/
train_t CreerTrain(int id, int nbrPlaces, chaine dest){
    train_t t;
    t.id = id;
    t.capaciteMAX = nbrPlaces;
    strcpy(t.destination, dest);
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

void TrainEnMarche(quai_t* Quaies,int NumQuai, train_t* Trains, int NumTrain){
/* Vitesse constante pour tout les trains de 5 ! 
votre job est de la rendre dynamique en utilisant a 
la plce la variable Train[i].vitesse 
*/
    for (int i=0;i<NumTrain;i++){
        if(Trains[i].kmRestant == 5){
            Trains[i].kmRestant = Trains[i].kmRestant-5;
            int ChoixAleatoireQuai = rand()%(NumQuai);
            Trains[i]=ViderTrain(Trains[i]);

            if(Empiler(Trains[i], &Quaies[ChoixAleatoireQuai]))
                printf("Train Id=%d revient de %s rentre dans le Quai %s\n",Trains[i].id,Trains[i].destination,Quaies[ChoixAleatoireQuai].id);
            else{
                printf("\ntout les quaies sont remplis\n Train ID=%d en attente ",Trains[i].id);
                Trains[i].kmRestant=-1;
            }
        }
        else if(Trains[i].kmRestant>5)
            Trains[i].kmRestant=Trains[i].kmRestant-5;
    }
}

listePassagers_t Embarquement(quai_t* Quaies, int NumQuaie, listePassagers_t PassagerPretPourEmbarquement, chaine Destinations[MapSize][2], int NumDestination, train_t* Trains, int NumTrain){
    printf("Liste Des Prochains Departs\n");
    for (int i=0; i<NumQuaie ;i++){
        train_t TrainPourDepart = Depiler(&Quaies[i]);
        if(TrainPourDepart.id == -1)
            printf("Le quai %s est vide \n",Quaies[i].id);
        else{
        printf("Prochain train,ID=%d, a destination de %s dans le quai %s\n",TrainPourDepart.id,TrainPourDepart.destination,Quaies[i].id);

            //RécupérerLaDistance
            for(int i=0;i<(NumDestination+1);i++){
                if(strcmp(TrainPourDepart.destination,Destinations[i][0])==0){
                    TrainPourDepart.kmRestant = atoi(Destinations[i][1]);
                }
            }

            ptr_passager ParcourirPassager = PassagerPretPourEmbarquement.tete;
            while(ParcourirPassager != NULL){
                if((strcmp(ParcourirPassager->destination,TrainPourDepart.destination)==0)&&(!SiTrainRemplis(TrainPourDepart))){

                    //Enlever de la liste des passager en attente et le mettre dans la liste des passagers dans le train
                    passager_t PassagerTmp = SupprimerPassagerListeAttenteEtLeRetourner(&PassagerPretPourEmbarquement,ParcourirPassager->id);

                    //Le mettre dans le train

                    TrainPourDepart.listeDesPassagers = AjouterPassagerDansLaListe(&PassagerTmp, &TrainPourDepart.listeDesPassagers);
                    TrainPourDepart.tauxDeRemplissage = TrainPourDepart.tauxDeRemplissage+1;
                }
                ParcourirPassager=ParcourirPassager->suivant;
            }
            MiseAJourTableauDesTrain(TrainPourDepart,Trains,NumTrain);
        }
    }
    printf("\n");

    return PassagerPretPourEmbarquement;
}

int InitialiserLesDestinationsDisponibles(chaine Destinations[MapSize][2]){
    int n;
    printf("Combien de destinations sont disponible dans la gare?: ");
    scanf("%d",&n); gets();
    for(int i=0;i<n;i++){
        fgets(Destinations[i][0],TAILLE_CHAINE ,stdin);
        fgets(Destinations[i][1],TAILLE_CHAINE,stdin);
    }
    return n;
}
