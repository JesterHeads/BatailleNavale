
#include "stdio.h"
#include "math.h"
#include <windows.h>

#define NbCase 8 /* dimension du tableau */

//Fonction pour d�finir un tableau et l'initialiser, c'est un tableau de bool�en
void creerGrille (int grilleJoueur[][NbCase], char prenomJoueur[])
{
    printf("Joueur %s veuillez placer vos bateaux, vous en avez 16.", prenomJoueur);
    int nbBateau=16;//nombre de bateau par joueur.
    int nbBateauPlacer=0;// nombre de bateau que le joueur a deja plac� .
    int i,j;//variables utilis�es pour parcourir les grilles.
    char response=' '; //variable utilis�e pour g�rer la r�ponse du joueur s'il veut placer un bateau ou non.

    for (i = 0; i < NbCase; i++)//boucles imbriqu�es pour parcourir l'ensemble de la grille
    {
        for (j = 0; j < NbCase; j++)
        {
            if(nbBateauPlacer<nbBateau){ // on v�rifie que le joueur a encore des bateaux � placer.
                printf("Voulez-vous placer un bateau sur cette case [%d][%d] ? Entrez Y pour Oui, N pour non \n",i,j);
                fflush(stdin);//nettoyage du buffer d'entr�e clavier
                scanf("%c",&response);//on r�cup�re la r�ponse du joueur
                if(response=='y'){
                    grilleJoueur[i][j]=1;// on met la case a 1 pour dire qu'elle est occup�e par un bateau
                    nbBateauPlacer++;
                    if(nbBateauPlacer==16){
                         printf("Vous n'avez plus de bateau � placer \n");
                    }
                }else{
                    grilleJoueur[i][j]=0;// on met la case a 0 pour dire qu'elle n'est pas occup�e.
                }

            } else {
                 grilleJoueur[i][j]=0; // on met toutes les cases restantes a 0.
            }
        }
    }
}

//Fonction qui affiche les grilles de jeu
//le parametre gameOn nous servira a definir un affichage different si le jeu a commencer ou non
// cad si le jeu a commenc�, les cases seront "cach�es"
void afficherTableau(int grilleJoueur[][NbCase], int gameOn){
    int i,j;
    for(i=0;i<NbCase;i++){
        printf("{");//d�but de ligne
        for(j=0;j<NbCase;j++){
            if(j==7){// on test si on est a la fin de la ligne, dans ce cas on ne met pas de virgule apr�s la case
                if(gameOn){// si le jeu est lanc�
                    if(grilleJoueur[i][j]==2){
                        printf("0");//on affiche un 0 pour dire que le bateau est coul� sur la grille .
                    }else if(grilleJoueur[i][j]==-2){//si c'est une case vide qui a �t� jou�e
                        printf("0");// on affiche �galement un 0 pour dire que la case est vide est qu'elle a ete jou�e
                    }else{// si la case n'a pas encore �t� jou�e
                        printf("~");// on utilise le charactere ~ pour cach� les cases non jou�es.
                    }
                }else{// si le jeu n'est pas lanc� on affiche le contenu de la grille
                    printf(" %d",grilleJoueur[i][j]);
                }
            }else{//si on est pas a la fin d'une ligne
                if(gameOn){//si le jeu est lanc�
                    if(grilleJoueur[i][j]==2){ //si la case est un bateau coul�
                        printf(" 0 ,");//on affiche 0 pour indiqu� que la case contient un bateau coul�
                    }else if(grilleJoueur[i][j]==-2){//si c'est une case vide qui a �t� jou�e
                        printf(" 0 ,");
                    }else{
                        printf(" ~ ,");//on utilise le charactere ~ pour cach� les cases non jou�es.
                    }
                }else{// le jeu n'est pas lanc�
                    printf(" %d ,",grilleJoueur[i][j]); // on affiche le contenu de la grille
                }
            }
        }
        printf("}\n");// on arrive a la fin d'une ligne et on passe a la suivante
    }
    printf("\n");// fin de l'affichage
}

//Fonction qui met a jour la grille du joueur en fonction du coup de l'adversaire
//l= ligne et c=colonne , coordonn�es de la case choisit
//nbBateauJoueur , nombre de bateau du joueur a mettre a jour
int toucherCouler(int grilleJoueur[][NbCase],int l, int c, int *nbBateauJoueur){
    int toucher = 0;
    if(grilleJoueur[l][c]==1){ //on teste si la case est occup�e
        printf("Touch� !\n");
        grilleJoueur[l][c]=2;// si elle l'est on la met a 2 et non a 0 pour differencier les cases vides des cases avec un bateau coul�
        *nbBateauJoueur -= 1;// on d�cremente le nombre de bateau du joueur adverse
        afficherTableau(grilleJoueur,1);//on affiche la grille du jouer=ur adverse pour continuer la partie
        toucher=1;
    }else{
        printf("Rat� !\n");
        grilleJoueur[l][c]=-2;// on met la case a -2 pour indiquer quelle a deja ete jou�.
        afficherTableau(grilleJoueur,1);//on affiche la grille du jouer=ur adverse pour continuer la partie
    }
    return toucher;
}

int main(int argc, char *argv[])
{
    int victoire=0;//bool�en qui servira a arret� le jeu en fonction de la victoire d'un des joueur.
    int ligne,colonne;
    int nbBateauJ1=16;
    int nbBateauJ2=16;
    int grilleJ1[8][8];
    int grilleJ2[8][8];
    int toucher=0;

    char prenomJoueur1[30];
    char prenomJoueur2[30];
    printf("La bataille navale commence\n");
    printf("Joueur 1 quel est votre prenom ?\n");
    fgets(prenomJoueur1,30,stdin);// on r�cupere le prenom du premier joueur
    creerGrille(grilleJ1,prenomJoueur1);//on cr�e sa grille
    afficherTableau(grilleJ1,0);
    Sleep(3000);// on laisse la grille du J1 afficher pendant 5 seconde
    system("cls");//on efface la console pour que le joueur 2 ne voit aps la grille adverse
    printf("Joueur 2 quel est votre prenom ?\n");
    fflush(stdin);//on vide le buffer d'entr�e clavier.
    fgets(prenomJoueur2,30,stdin);//on r�cupere le prenom du second joueur
    creerGrille(grilleJ2,prenomJoueur2);//on cr�e sa grille
    afficherTableau(grilleJ2,0);
    Sleep(3000);// on laisse la grille du J1 afficher pendant 5 seconde
    system("cls");
        //boucle while de jeu
        while(victoire==0){// tant que les deux joueurs ont au moins 1 bateaux chacun en jeu, on continue.
            printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur1);
            scanf("%d",&ligne);
            printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur1);
            scanf("%d",&colonne);
            toucher =toucherCouler(grilleJ2,ligne,colonne,&nbBateauJ2);// on appelle la fonction qui gere les differents coups
            while(toucher){
                printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur1);
                scanf("%d",&ligne);
                printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur1);
                scanf("%d",&colonne);
                toucher=toucherCouler(grilleJ2,ligne,colonne,&nbBateauJ2);
                printf("%s il vous reste %d bateaux \n",prenomJoueur2,nbBateauJ2);
                if(nbBateauJ2==0){
                    toucher=0;
                    victoire=1;
                }
            }
            if(!victoire){
                //on passe au tour du joueur 2
                printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur2);
                scanf("%d",&ligne);
                printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur2);
                scanf("%d",&colonne);
                toucher =toucherCouler(grilleJ1,ligne,colonne,&nbBateauJ1);// on appelle la fonction qui va gerer les different coups
                while(toucher){
                    printf("%s il vous reste %d bateaux \n",prenomJoueur1,nbBateauJ1);
                    printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur2);
                    scanf("%d",&ligne);
                    printf("%s veuillez selectionner la ligne, entrez un numero entre 0 et 7\n",prenomJoueur2);
                    scanf("%d",&colonne);
                    toucher=toucherCouler(grilleJ1,ligne,colonne,&nbBateauJ1);
                    if(nbBateauJ1==0){
                        toucher=0;
                        victoire=1;
                    }
                }
            }
    }
    if(nbBateauJ1==0){
        printf("F�licitation %s, vous avez gagn�",prenomJoueur2);
    }else{
        printf("F�licitation %s, vous avez gagn�",prenomJoueur1);
    }
}
