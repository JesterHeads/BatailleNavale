
#include "stdio.h"
#include "math.h"

#define NbCase 8 /* dimension du tableau */

//Fonction pour définir un tableau et l'initialiser, c'est un tableau de booléen
int creerGrille[][] (int grilleJoueur[NbCase][NbCase], char prenomJoueur[])
{
    printf("Joueur %s veuillez placer vos bateaux, vous en avez 16", prenomJoueur);
    int nbBateau=16;//nombre de bateau par joueur.
    int nbBateauPlacer=0;
    int i,j;//variables utilisées pour parcourir les grilles.
    char response=''; //variable utilisée pour gérer la réponse du joueur s'il veut placer un bateau ou non.

    for (i = 0; i < NbCase; i++)//boucles imbriquées pour parcourir l'ensemble de la grille
    {
        for (j = 0; j < NbCase; j++)
        {
            if(nbBateauPlacer<nbBateau){ // on vérifie que le joueur a encore des bateaux à placer.
                printf("Voulez-vous placer un bateau sur cette case [%d][%d] ? Entrez Y pour Oui, N pour non",i,j);
                fflush(stdin);//nettoyage du buffer d'entrée clavier
                scanf("%c",&response);//on récupère la réponse du joueur
                if(response=='Y'){
                    grilleJoueur[i][j]=1;// on met la case a 1 pour dire qu'elle est occupée par un bateau
                }else{
                    grilleJoueur[i][j]=0;// on met la case a 0 pour dire qu'elle n'est pas occupée.
                }

            }
            printf("Vous n'avez plus de bateau");
            grilleJoueur[i][j]=0; // on met toutes les cases restantes a 0.
        }

    }
    return grilleJoueur;
}

void afficherTableau(int grilleJoueur[NbCase][NbCase]){
    int i,j;
    for(i=0;i<NbCase;i++){
        printf("{");//début de ligne
        for(j=0;j<NbCase;j++){
            if(j==7){// on test si on est a la fin de la ligne, dans ce cas on ne met pas de virgule après la case
                printf(" %d",grilleJoueur[i][j]);
            }
            else{
                printf(" %d ,",grilleJoueur[i][j]);
            }
        }
        printf("}\n");
    }
}

//Fonction qui met a jour la grille du joueur en fonction du coup de l'adversaire
//l= ligne et c=colonne , coordonnées de la case choisit
//nbBateauJoueur , nombre de bateau du joueur a mettre a jour
int toucherCouler(int grilleJoueur[][],int l, int c, int nbBateauJoueur){
    if(grilleJoueur[l][c]==1){ //on teste si la case est occupée
        printf("Touché !");
        grilleJoueur[l][c]==0;// si elle l'est on la met a 0 donc a FAUX
        nbBateauJoueur--;
        if(nbBateauJoueur==0){
            victory=1;
        }
    }else{
        printf("Raté !");
    }
}

int main(int argc, char *argv[])
{
    int victoire=0;//booléen qui servira a arreté le jeu en fonction de la victoire d'un des joueur.
    int ligne,colonne;
    int nbBateauJ1=16;
    int nbBateauJ2=16;

    char prenomJoueur1[30];
    char prenomJoueur2[30];
    printf("La bataille navale commence");
    printf("Joueur 1 quel est votre prenom ?");
    fgets(prenomJoueur,30,stdin);// on récupere le prenom du premier joueur
    int grilleJ1[8][8]=creerGrille(grilleJ1,prenomJoueur);//on crée sa grille
    printf("Joueur 2 quel est votre prenom ?");
        fflush(stdin);//on vide le buffer d'entrée clavier.
        fgets(prenomJoueur,30,stdin);//on récupere le prenom du second joueur
        int grilleJ2[8][8]=creerGrille(grilleJ2,prenomJoueur);//on crée sa grille
        //on affiche les grilles des 2 joueurs.
        afficherTableau(grilleJ1);
        afficherTableau(grilleJ2);

        //boucle while de jeu
        while(!victoire){
            printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7",prenomJoueur1);
            scanf("%d",ligne);
            printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7",prenomJoueur1);
            scanf("%d",colonne);
            toucherCouler(grilleJ2,ligne,colonne,nbBateauJ2);
            printf("d%",nbBateauJ2);

    }
}