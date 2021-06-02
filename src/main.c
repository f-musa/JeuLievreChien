#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game.h"

/********************* Variables globales statiques ****************/
char currentFenetre[50]; /*variable globale static qui permet de savoir la fenetre courante*/
Menu menuPrincipal;
Menu commencerUnePartie;
Menu mode2Joueurs;
Menu reglesJeu;
int continuer;
char joueur1;
char joueur2;
Plateau pl;
/********************************************************************/

int main(int argc, char** argv){

    SDL_Window *window = NULL;     
    SDL_Renderer *renderer = NULL ;     
    SDL_Event event;
    continuer = 1;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
            fprintf(stderr,"Érreur SDL_Init : %s", SDL_GetError());
            goto Quit;
        }

    if(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer) != 0){
            fprintf(stderr, "Erreur SDL_CreateWindowRenderer : %s", SDL_GetError());
            goto Quit;
    }
    
    /*Affichage du message d'accueil et ransition vers le menu */
    transitionMenu(window,renderer);
    strcpy(currentFenetre,"menuPrincipal"); // Update la variable correspondant a la fenetre courante

    /* Menu Init */
    menuPrincipal.option1 = (SDL_Rect){111,168,550,84}; 
    menuPrincipal.option2 = (SDL_Rect){148,260,492,89};  
    menuPrincipal.option3 = (SDL_Rect){150,362,491,78};

    commencerUnePartie.option1 = (SDL_Rect){163,185,450,82};
    commencerUnePartie.option2 = (SDL_Rect){73,284,616,74};
    commencerUnePartie.retour = (SDL_Rect){7,496,156,62};
    
    reglesJeu.retour = (SDL_Rect) {13,494,167,64};
    
    mode2Joueurs.option1 = (SDL_Rect){300,285,182,66};
    mode2Joueurs.option2 = (SDL_Rect){303,376,180,68};
    mode2Joueurs.retour = (SDL_Rect){14,495,160,59};
    /***********/

    pl.bas.rect = (SDL_Rect){694,226,78,78};
    pl.l1_gauche.rect = (SDL_Rect){535,402,70,75};
    pl.l1_milieu.rect = (SDL_Rect){536,229,70,75};
    pl.l1_droite.rect = (SDL_Rect){530,50,82,83};
    pl.l2_gauche.rect = (SDL_Rect){359,397,84,88};
    pl.l2_milieu.rect = (SDL_Rect){359,225,82,82};
    pl.l2_droite.rect = (SDL_Rect){357,47,83,87};
    pl.l3_gauche.rect = (SDL_Rect){191,399,79,77};
    pl.l3_milieu.rect = (SDL_Rect){188,221,83,89};
    pl.l3_droite.rect = (SDL_Rect){190,51,82,85};
    pl.haut.rect = (SDL_Rect){23,220,91,92};
    pl.chien_1.position = &pl.haut; pl.chien_2.position = &pl.haut; pl.chien_3.position = &pl.haut;
    pl.lievre.position = &pl.haut;
    while(continuer)
    {
         while(SDL_PollEvent(&event)){
            SDL_Point p;      
            switch (event.type )
            {
                case SDL_QUIT:
                    continuer = 0;
                break;

                case SDL_MOUSEMOTION:
                    p.x = event.motion.x;
                    p.y = event.motion.y;
                    hoverHandlerOptions(window,renderer,p);
                    ;
                break;
                case SDL_MOUSEBUTTONDOWN :
                    p.x = event.button.x;
                    p.y = event.button.y;
                    clickHandlerOptions(window,renderer,p);
                break;
            }
        }
        sleep(1);
    }
    
    Quit :
    return 1;
}
