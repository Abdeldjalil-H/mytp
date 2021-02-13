#include <stdio.h>
#include "quai.h"
#include "passager.h"
#include "train.h"

#define MaxTrain 20
#define MaxParkingRails 8
#define MapSize 20
int main()
{   

//Déclaration des structures de données
    train_t Trains[MaxTrain];// tableau de train 
    quai_t Quais[MaxParkingRails]; // tableau de quais 
    int NumTrain = 0;//Nombre de train qu'il y'a dans la gare
    int NumQuai = 0;// nombre de quais qu'il y'a dans la gare

    // matrice des destinations 
    chaine Destinations[MapSize][2];

    int NumDestinations= InitialiserLesDestinationsDisponibles(Destinations);

    // Ajout des trains
    NumTrain = AjouterTrain(Trains,NumTrain,15,"Tokyo");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Helsinki");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Helsinki");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Tokyo");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Berlin");
    NumTrain = AjouterTrain(Trains,NumTrain,8,"Nairobi");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Denver");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Nairobi");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Berlin");
    NumTrain = AjouterTrain(Trains,NumTrain,10,"Ouergla");


    // Ajouter les Quais
    NumQuai = AjouterQuais(Quais,NumQuai,"Q1",2,Trains, NumTrain);
    NumQuai = AjouterQuais(Quais,NumQuai,"El Moudjahid",1,Trains, NumTrain);
    NumQuai = AjouterQuais(Quais,NumQuai,"Roberto Carlos",1,Trains,NumTrain);

    // déclarer la liste des passagers en attente
    listePassagers_t ListeDesPassagerEnAttente;
    


    //Commencer la simulation 
    int NbrHeur = 0;
    while(1){
        // nous pouvons remplacer le 1 par un nombre d’itération bien précis !

        // afficher l’état des quais pour voir ou se trouve les train. 
        AfficherParkingRail(Quais,NumQuai); 
        NbrHeur++;
        printf("************Heure %d***********\n\n",NbrHeur);
        srand(time(NULL));// appeler la fonction random pour générer des nombres aléatoire de réservations et d’annulations 

        int NombreAleatoireDeReservations=rand()%10+5;
        int NombreAleatoireDAnulations=rand()%5;
        /*nous devons nous assurer que le nombres de reservations 
        soit strictement superieurs aux nombre d’annulations*/
        printf("Nombre de reservations : %d\n",NombreAleatoireDeReservations);
        printf("Nombre d'annulations : %d\n",NombreAleatoireDAnulations);

        for (int i=0;i<NombreAleatoireDeReservations;i++){
            int ChoisirUneDestinationAleatoire=rand()%(NumDestinations+1);
            /*réserver des places et ajouter des passagers dans 
            la liste d’attente, a ce stade, aucun passager n’est 
            dans le train, rien que la variable « place prises » 
            est incrémenter pour dire que les places sont reservées
            */
            ListeDesPassagerEnAttente = ReservationPlace(ListeDesPassagerEnAttente, Trains,NumTrain,Destinations[ChoisirUneDestinationAleatoire][0]);
        }


        for (int i=0;i<NombreAleatoireDAnulations;i++){
            int ChoisirUnIDPourAnulationAleatoire=rand()%TailleListe(ListeDesPassagerEnAttente);
            ListeDesPassagerEnAttente = AnnulerReservation(ListeDesPassagerEnAttente,ChoisirUnIDPourAnulationAleatoire);
            /*briser la liste chainée «ListeDesPassagersEnAttente» 
            et enlever les passagers qui souhaites annuler leurs 
            reservations.*/
        }

        printf("\n Nombre de passagers en attente %d\n",TailleListe(ListeDesPassagerEnAttente));
        AfficherPassagers(ListeDesPassagerEnAttente);
        //affichier l’état des passagers en attente avant embarquement et après que les réservations et annulations soient faites
        ListeDesPassagerEnAttente=Embarquement(Quais, NumQuai, ListeDesPassagerEnAttente, Destinations,NumDestinations, Trains,NumTrain );

        // Embarquer les passager ! 
        AfficherTrains(Trains,NumTrain);
        
        //afficher l’état des trains pour voir si ils ont pris des passagers avec eux.

        TrainEnMarche(Quais,NumQuai, Trains, NumTrain);
        // lancer les trains qui sont les premiers dans les quais
        printf("\n Nombre de passagers en attente après embarquement %d\n",TailleListe(ListeDesPassagerEnAttente));

        AfficherPassagers(ListeDesPassagerEnAttente);
        // afficher l’état des passagers en attente après embarquement, dans le cas ou votre programme marche correctement, il ne devrai y avoir aucun passager qui demande une destination qui vient d’être proposé par un train sur le départ sauf si le train est remplis a 100%.
        
        UpdateQuais( Quais, NumQuai, Trains, NumTrain );

        //Mettre a jour les quais en récupérant les train en attente et en avançant les tarins dans la pile pour proposer de nouvelle destinations.
        system("pause"); 
    }

    return 0;
}