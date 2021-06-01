#include "game.h"


void transitionMenu (SDL_Window * window,SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP("images/imagesBMP/accueil.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); 
    SDL_Rect dstrect = { 0, 0, 800,600};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1500);
    tmp = SDL_LoadBMP("images/imagesBMP/menu.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); 
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
}

void switchScreen(SDL_Renderer* renderer,char*chemin,char*nomFenetre,int delay)
{
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(chemin);
    strcpy(currentFenetre,nomFenetre); /* On update le nom de la nouvelle fenetre */
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); 
    SDL_Rect dstrect = { 0, 0, 800,600};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_Delay(delay);
    SDL_RenderPresent(renderer);
}   

void hoverHandlerOptions(SDL_Window *window,SDL_Renderer *renderer,SDL_Point p)
  {
     // Gestion des Hover sur le menuPrincipal
     if(strstr(currentFenetre,"menuPrincipal")!=NULL)
     {    
         SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
         if (SDL_PointInRect(&p,&menuPrincipal.option1))
            {
            SDL_RenderDrawRect(renderer, &menuPrincipal.option1);
            SDL_RenderPresent(renderer);
            }
        else if(SDL_PointInRect(&p,&menuPrincipal.option2)) 
        {
            SDL_RenderDrawRect(renderer, &menuPrincipal.option2);
            SDL_RenderPresent(renderer);
        }
        else if(SDL_PointInRect(&p,&menuPrincipal.option3))
        {
            SDL_RenderDrawRect(renderer, &menuPrincipal.option3);
            SDL_RenderPresent(renderer);
        }    
    }
    // Gestion des Hover dans commencerUnePartie
    else if(strstr(currentFenetre,"commencerPartie")!=NULL)
     {
         SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
         if (SDL_PointInRect(&p,&commencerUnePartie.option1))
            {
            SDL_RenderDrawRect(renderer, &commencerUnePartie.option1);
            SDL_RenderPresent(renderer);
            }
        else if(SDL_PointInRect(&p,&commencerUnePartie.option2)) 
        {
            SDL_RenderDrawRect(renderer, &commencerUnePartie.option2);
            SDL_RenderPresent(renderer);
        }
        else if(SDL_PointInRect(&p,&commencerUnePartie.retour))
        {
            SDL_RenderDrawRect(renderer, &commencerUnePartie.retour);
            SDL_RenderPresent(renderer);
        }    
     }
     //Gestion des hover dans reglesDuJeu
     else if(strstr(currentFenetre,"reglesDuJeu")!=NULL)
     {
         SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
         if (SDL_PointInRect(&p,&reglesJeu.retour))
            {
            SDL_RenderDrawRect(renderer, &reglesJeu.retour);
            SDL_RenderPresent(renderer);
            }
     }
     //Gestion des hover dans 
     else if(strstr(currentFenetre,"mode2Joueurs")!=NULL)
     {  
         SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
         if (SDL_PointInRect(&p,&mode2Joueurs.option1))
            {
            SDL_RenderDrawRect(renderer, &mode2Joueurs.option1);
            SDL_RenderPresent(renderer);
           
            }
        else if(SDL_PointInRect(&p,&mode2Joueurs.option2)) 
        {
            SDL_RenderDrawRect(renderer, &mode2Joueurs.option2);
            SDL_RenderPresent(renderer);
        }
        else if(SDL_PointInRect(&p,&mode2Joueurs.retour))
        {
            SDL_RenderDrawRect(renderer, &mode2Joueurs.retour);
            SDL_RenderPresent(renderer);
           
        }  
     }
  }
  
  void clickHandlerOptions(SDL_Window *window,SDL_Renderer *renderer,SDL_Point p)
  {
     // Gestion des Clicks dans le menuPrincipal
     if(strstr(currentFenetre,"menuPrincipal")!=NULL)
     {  
         if (SDL_PointInRect(&p,&menuPrincipal.option1))
            {
            switchScreen(renderer,"images/imagesBMP/commencerUnePartie.bmp","commencerPartie",0);
            }
        else if(SDL_PointInRect(&p,&menuPrincipal.option2)) 
        {
            switchScreen(renderer,"images/imagesBMP/reglesDuJeu.bmp","reglesDuJeu",0);
        }
        else if(SDL_PointInRect(&p,&menuPrincipal.option3))
        {
            continuer = 0;
        } 
     }
     // Gestion des clicks dans commencerUnePartie
     else if(strstr(currentFenetre,"commencerPartie")!=NULL)
     {
         if (SDL_PointInRect(&p,&commencerUnePartie.option1))
            {
            switchScreen(renderer,"images/imagesBMP/mode2Joueurs.bmp","mode2Joueurs",0);
            }
        else if(SDL_PointInRect(&p,&commencerUnePartie.option2)) 
        {
            /*TODO remplacer par lien lorsque l'IA sera implémentée*/
            switchScreen(renderer,"images/imagesBMP/commencerUnePartie.bmp","commencerPartie",0);
        }
        else if(SDL_PointInRect(&p,&commencerUnePartie.retour))
        {
            switchScreen(renderer,"images/imagesBMP/menu.bmp","menuPrincipal",0);
        } 
     }
     // Gestion des clicks dans reglesDuJeu
     else if(strstr(currentFenetre,"reglesDuJeu")!=NULL)
     {
        if (SDL_PointInRect(&p,&reglesJeu.retour))
            {
            switchScreen(renderer,"images/imagesBMP/menu.bmp","menuPrincipal",0);
            }      
     }
     //Gestion des clicks dans mode2Joueurs
    else if(strstr(currentFenetre,"mode2Joueurs")!=NULL)
    {
         if (SDL_PointInRect(&p,&mode2Joueurs.option1))
            {
                //Joueur  est le lievre | Joueur 2 est le chien 
                //On affiche le recap et on passe vers la partie
                joueur1 = 'l';
                joueur2 = 'c';
                switchScreen(renderer,"images/imagesBMP/recapLievre.bmp","*",0);
                switchScreen(renderer,"images/imagesBMP/board.bmp","gameBoard",2000);


            } 
        else if(SDL_PointInRect(&p,&mode2Joueurs.option2)) 
        {
            //Joueur 1 est le chien | Joueur 2 est le lievre
                joueur1 = 'c';
                joueur2 = 'l';
                switchScreen(renderer,"images/imagesBMP/recapChien.bmp","*",0);
                switchScreen(renderer,"images/imagesBMP/board.bmp","gameBoard",2000);

        }
        else if(SDL_PointInRect(&p,&mode2Joueurs.retour))
        {
            switchScreen(renderer,"images/imagesBMP/commencerUnePartie.bmp","commencerPartie",0);
        } 
    }
  }