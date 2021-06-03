#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

/*********************** Structures ************************/
typedef struct menu{
    SDL_Rect option1 ;    
    SDL_Rect option2 ;    
    SDL_Rect option3 ;       
    SDL_Rect retour ; 
}Menu;

typedef struct casePlateau{
    SDL_Rect rect;
    int estOccupee;
    char occupant;
    int x;
    int y;
}Case;

typedef struct piece{
    SDL_Rect image;
    Case *position;
    Case *position_precedente;
}Piece;

typedef struct plateau{
    Case bas;Case haut;
    Case l1_gauche;Case l1_milieu;Case l1_droite;
    Case l2_gauche;Case l2_milieu;Case l2_droite;
    Case l3_gauche;Case l3_milieu;Case l3_droite;
    Piece lievre;
    Piece chien_1;Piece chien_2;Piece chien_3;
    SDL_Rect main_joueur ;
    char tour_a;
}Plateau;


/*******************************Variables globales statiques********************/
extern char currentFenetre[50]; /*variable globale static qui permet de savoir la fenetre courante*/
extern Menu menuPrincipal;
extern int continuer;
extern Menu commencerUnePartie;
extern Menu mode2Joueurs;
extern Menu reglesJeu;
extern int joueurAvecMain;
extern Plateau pl;
extern int click_counter;
extern Case * caseDepart;
extern Case * caseArrivee;

/*******************************************************************************/

/* 
    Fonction qui initialise les zones des differents menus
*/
void menuInit(void);
/* 
    Fonction qui permet d'afficher le message d'accueil puis au bout de 1 seconde de passer au menu
*/
void transitionMenu (SDL_Window *,SDL_Renderer *);

/*
    Fonction qui permet de surligner les options sur une page lors du survol
*/
void hoverHandlerOptions(SDL_Window *,SDL_Renderer *,SDL_Point);

/*
    Fonction qui permet de gerer le selectionnement d'une option (transition vers la nouvelle page)
*/
void clickHandlerOptions(SDL_Window *,SDL_Renderer *,SDL_Point);


/*
    Fonction qui permet de changer d'écran 
*/
void switchScreen(SDL_Renderer*,char*,char*,int);


/*
    Fonction qui permet de charger une image  
*/
void loadImage(const char [], SDL_Renderer *, SDL_Rect *);

/* 
    Fonction qui permet d'intialiser le plateau de jeu 
*/
void initPartie(Plateau *, SDL_Renderer *);

/* Fonction qui permet de detecter la case concernée par un deplacement*/
Case * detectCase (SDL_Point);

/* Fonction qui permet de verifier la validité d'un deplacement*/
int verifDeplacement();

/* Fonction qui permet de depalcer une piece */
void deplacerCase(SDL_Renderer *);

/* Fonction qui permet de verifier si un joueur a gagner la partie*/
void verifGagnant(SDL_Renderer *);