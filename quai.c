#include <stdio.h>
#include <string.h>
#include "quai.h"
#include "train.h"
#include "types.h"

/*
Cette fonction a pour objectif de créer un quai ayant une capacité maximum d’admission de train avec un id
*/
quai_t CreerUnParkingRail(char* id, int capacite){
    quai_t q;
    strcpy(q.id, id);
    q.capacite = capacite;
    q.premierTrain = -1;
    
    return q;
}

/*
Empiler un train qui arrive, à partir d’une destination particulière ou du stock des trains dans un quai particulier. 
On retourne si le train est empilé
*/
int Empiler (train_t train,quai_t *q){
    if (PileRemplie(*q)){
        return 0;
    }
    else{
        q->premierTrain++ ;
        q->listeDesTrains[q->premierTrain] = train;
        return 1;
    }
}

/*
Prendre un train d’un quai particulier et le retourner.
*/
train_t Depiler(quai_t *q){
    train_t t = q->listeDesTrains[q->premierTrain];
    q->premierTrain--;
    return t;
}


/*
Vérifie si la pile est vide
*/
int PileVide(quai_t *q){
    return (q->premierTrain == -1);
}

/*
Cette fonction vérifie si une pile est remplie ou non. 
*/
int PileRemplie(quai_t q){
    return (q.premierTrain == q.capacite);
}
/*
Rechercher des trains qui ne sont pas dans les quais
*/
quai_t TrouverDesTrainDisponible(quai_t q, train_t* Trains, int numTrain){
    for (int i=0;i<numTrain;i++){
        if((Trains[i].kmRestant == -1)&&(!PileRemplie(q))){
            Trains[i].kmRestant=0;//train dans le quai
            Empiler(Trains[i],&q);
        }
    }
    return q;
}

int AjouterQuais(quai_t * Quais,int NumQuai,chaine IdentifiantQuai, int capacity, train_t* Trains, int NumTrain){
    //creer un quai avec un identifiant et une capacité
    Quais[NumQuai]=CreerUnParkingRail(IdentifiantQuai,capacity);
    // rechercher des trains disponible pour remplir le quai 
    Quais[NumQuai] = TrouverDesTrainDisponible(Quais[NumQuai],Trains,NumTrain);

    return NumQuai+1;
}

void UpdateQuais(quai_t* Quais, int NumQuai,train_t* Trains, int NumTrain){
    for (int j=0;j<NumTrain;j++){
        for(int i=0;i<NumQuai;i++)
            if((Trains[j].kmRestant == -1))
                if(!PileRemplie(Quais[i])){
                    Trains[j].kmRestant = 0;
                    Empiler(Trains[j],&Quais[i]);
                }
    }
}

void AfficherParkingRail(quai_t* ParkingRails, int NumParkingRail){

    printf("Le nombre de Quais dans la gare est de %d\n \n",NumParkingRail);
    for (int i=0;i<NumParkingRail;i++){
        printf("Le nombre de train dans le quai %s est de %d \n",ParkingRails[i].id,ParkingRails[i].premierTrain+1);
        for (int j=ParkingRails[i].premierTrain;j>=0;j--)
            printf("le train ID=%d prendra le départ en %d position\n",ParkingRails[i].listeDesTrains[j].id,ParkingRails[i].premierTrain-j+1);
    }
}