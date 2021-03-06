#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include "game.h"

/*********************Variables globales statiques ****************/
char currentFenetre[50]; /*variable globale static qui permet de savoir la fenetre courante*/
Menu menuPrincipal;
Menu commencerUnePartie;
Menu mode2Joueurs;
Menu reglesJeu;
int continuer;
int joueurAvecMain;
Plateau pl;
int click_counter;
Case * caseDepart;
Case * caseArrivee;
/********************************************************************/

int main(int argc, char **argv)
{

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	click_counter = 0;
	caseArrivee = NULL;
	caseArrivee = NULL;
	continuer = 1;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Érreur SDL_Init : %s", SDL_GetError());
		goto Quit;
	}

	if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
	{
		fprintf(stderr, "Erreur SDL_CreateWindowRenderer : %s", SDL_GetError());
		goto Quit;
	}

	/*Affichage du message d'accueil et ransition vers le menu */
	transitionMenu(window, renderer);
	strcpy(currentFenetre, "menuPrincipal");	// Update la variable correspondant a la fenetre courante

	/*Menu Init */
	menuInit();
	/***********/

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_Point p;
			switch (event.type)
			{
				case SDL_QUIT:
					continuer = 0;
					break;

				case SDL_MOUSEMOTION:
					p.x = event.motion.x;
					p.y = event.motion.y;
                    //Ligne commenté pour raisons de performances
					//hoverHandlerOptions(window,renderer,p);
					;
					break;
				case SDL_MOUSEBUTTONDOWN:
					p.x = event.button.x;
					p.y = event.button.y;
					clickHandlerOptions(window, renderer, p);
					printf("click count : %d \n", click_counter);
					break;
			}
		}
	}
	Quit:
		return 1;
}