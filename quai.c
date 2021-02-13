#include "quai.h"
#include "train.h"


/*
Cette fonction a pour objectif de créer un quai ayant une capacité maximum d’admission de train avec un id
*/
quai_t CreeUnParkingRail(int id ,int capacite){
    quai_t q;
    q.id = id;
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
        q->listeTrain[q->premierTrain]=train;
        return 1;
    }
}

/*
Prendre un train d’un quai particulier et le retourner.
*/
train_t Depiler(quai_t *q){
    train_t t = q->listeTrain[q->premierTrain];
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
