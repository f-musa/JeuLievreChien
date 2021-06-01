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
                    //hoverHandlerOptions(window,renderer,p);
                    ;
                break;
                case SDL_MOUSEBUTTONDOWN :
                    p.x = event.button.x;
                    p.y = event.button.y;
                    clickHandlerOptions(window,renderer,p);
                break;
            }
        }
    }
    
    Quit :
    return 1;
}
