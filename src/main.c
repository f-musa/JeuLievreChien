#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <unistd.h>
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
    menuInit();
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
        sleep(1);
    }
    
    Quit :
    return 1;
}
