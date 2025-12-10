#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGUEUR_PISTE 20
#define LARGEUR_PISTE 10
#define VITESSE_PAS_LONG 1
#define VITESSE_PAS_LAT 1
#define DUREE_CYCLE_BASE 0.5
#define NORMALE "NORMALE"
#define URGENTE "URGENTE"
#define AVANCER "AVANCER"
#define RECULER "RECULER"
#define TOURNER_GAUCHE "TOURNER_GAUCHE"
#define TOURNER_DROITE "TOURNER_DROITE"
#define ARRET_URGENCE "ARRET_URGENCE"
void executer_commande(Commande c){
    if(strcmp(c.priorite,URGENTE)==0){
        printf("COMMANDE URGENTE : %s\n",c.type);
        temps_simulation+=DUREE_CYCLE_BASE;
        journaliser(&c,"EXECUTION URGENTE");
        afficher_interface();
        return;
    }}
void gerer_obstacle(float duree_tourner, float vitesse_tourner, float duree_avancer, float vitesse_avancer){
    Commande c;
    strcpy(c.type,TOURNER_DROITE); c.duree=duree_tourner; c.vitesse=vitesse_tourner; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,AVANCER); c.duree=duree_avancer; c.vitesse=vitesse_avancer; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,TOURNER_GAUCHE); c.duree=duree_tourner; c.vitesse=vitesse_tourner; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,AVANCER); c.duree=duree_avancer/2; c.vitesse=vitesse_avancer; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    printf("* Contournement de l'obstacle ajouté ***\n");
}
void ajouter_commandes_initiales(float duree_avancer, float vitesse_avancer, float duree_tourner, float vitesse_tourner){
    Commande c;
    strcpy(c.type,AVANCER); c.duree=duree_avancer; c.vitesse=vitesse_avancer; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,TOURNER_DROITE); c.duree=duree_tourner; c.vitesse=vitesse_tourner; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,AVANCER); c.duree=duree_avancer/2; c.vitesse=vitesse_avancer; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
    strcpy(c.type,TOURNER_GAUCHE); c.duree=duree_tourner; c.vitesse=vitesse_tourner; strcpy(c.priorite,NORMALE);
    ajouter_commande_normale(c);
}
int main(){
    init_file(&file_normale); init_file(&file_urgente);
    FILE *f=fopen("journal_robot.txt","w"); if(f){fprintf(f,"======= Journal Robot =======\n"); fclose(f);}
    float duree_avancer = 5, vitesse_avancer = 1;
    float duree_tourner = 2, vitesse_tourner = 1;
    ajouter_commandes_initiales(duree_avancer,vitesse_avancer,duree_tourner,vitesse_tourner);
    printf("=== Simulation Robot Début ===\n");
    const int MAX_CYCLES=50; int cycle=0;
    Commande c_exec;
    while((!file_vide(&file_normale)||!file_vide(&file_urgente)) && cycle<MAX_CYCLES){
        if(capteur_detecte_obstacle()){
            printf("*** OBSTACLE DETECTE ***\n");
            gerer_obstacle(duree_tourner,vitesse_tourner,duree_avancer,vitesse_avancer);
        }

        if(prendre_prochaine_commande(&c_exec)){
            executer_commande(c_exec);
        }
        cycle++;
    }

    if(cycle>=MAX_CYCLES) printf("=== Simulation arrêtée après %d cycles ===\n",MAX_CYCLES);
    else printf("=== Simulation Robot Terminé ===\n");

    return 0;
}
