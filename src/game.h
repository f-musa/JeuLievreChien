#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

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
}Plateau;

typedef struct menu{
    SDL_Rect option1 ;    
    SDL_Rect option2 ;    
    SDL_Rect option3 ;       
    SDL_Rect retour ; 
}Menu;

/*******************************Variables globales statiques********************/
extern char currentFenetre[50]; /*variable globale static qui permet de savoir la fenetre courante*/
extern Menu menuPrincipal;
extern int continuer;
extern Menu commencerUnePartie;
extern Menu mode2Joueurs;
extern Menu reglesJeu;
extern char joueur1;
extern char joueur2;
extern Plateau p;
/*******************************************************************************/

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

void initPlateau()