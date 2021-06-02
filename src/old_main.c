#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/* Fermer la fenêtre */
void closeWindow(){
    bool isquit = false;
        SDL_Event event;
        while (!isquit) 
            if (SDL_PollEvent( & event)) 
                if (event.type == SDL_QUIT) 
                    isquit = true;
}

/* Fonction permettant de vérifier si un point appartient à un rectangle */
SDL_bool test(SDL_Point point, SDL_Rect rect){
    if(point.x >= rect.x && point.x <= (rect.x + rect.w) 
        && point.y >= rect.y && point.y <= (rect.y + rect.h))
            return SDL_TRUE;
        return SDL_FALSE;
}

/* Fonction permettant de changer la couleur de la fenêtre */
int setWindowColor(SDL_Renderer * renderer, SDL_Color color){
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

int main2(int argc, char** argv){

        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Texture *texture = NULL;
        int statut = EXIT_FAILURE;
        SDL_Color blanc = {200, 200, 200, 0};
        
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0 ){
            fprintf(stderr,"Érreur SDL_Init : %s", SDL_GetError());
            goto Quit;
        }

        if(SDL_CreateWindowAndRenderer(840, 680, SDL_WINDOW_SHOWN, &window, &renderer) != 0){
            fprintf(stderr, "Erreur SDL_CreateWindowRenderer : %s", SDL_GetError());
            goto Quit;
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
        if(texture == NULL){
            fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
            goto Quit;
        } 

        SDL_SetRenderDrawColor(renderer, blanc.r, blanc.g, blanc.b, blanc.a);
        SDL_RenderClear(renderer);

        SDL_Surface *tmp = NULL;
        tmp = SDL_LoadBMP("images/imagesBMP/accueil.bmp");
        if(tmp == NULL){
            fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
            goto Quit;
        }
        texture = SDL_CreateTextureFromSurface(renderer, tmp);

        if(texture == NULL){
            fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
            goto Quit;
        }

        SDL_Rect dstrect = { 0, 0, 840, 680};
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        /* SDL_Rect dstrect2 = { 150, 180, 100, 100};
        SDL_RenderCopy(renderer, texture, NULL, &dstrect2); */
        
        SDL_RenderPresent(renderer);

        statut = EXIT_SUCCESS;
        closeWindow();

Quit:
        if(tmp != NULL)
            SDL_FreeSurface(tmp);
        if(texture != NULL)
            SDL_DestroyTexture(texture);
        if(renderer != NULL)
            SDL_DestroyRenderer(renderer);
        if(window != NULL)
            SDL_DestroyWindow(window);

        SDL_Quit();

    return statut;   
}
