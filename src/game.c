#include "game.h"

void menuInit()
{
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
}
void loadImage(const char path[], SDL_Renderer *renderer,SDL_Rect * rect)
{
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(path);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); 
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_RenderPresent(renderer);
}

void initPartie(Plateau * pl, SDL_Renderer * renderer)
{
    /* Definition des zones correspondants aux differentes cases */
    pl->bas.rect = (SDL_Rect){697,224,72,75};
    pl->l1_gauche.rect = (SDL_Rect){534,396,70,76};
    pl->l1_milieu.rect = (SDL_Rect){534,225,72,69};
    pl->l1_droite.rect = (SDL_Rect){535,51,70,75};
    pl->l2_gauche.rect = (SDL_Rect){366,397,69,74};
    pl->l2_milieu.rect = (SDL_Rect){364,225,70,72};
    pl->l2_droite.rect = (SDL_Rect){366,52,69,73};
    pl->l3_gauche.rect = (SDL_Rect){196,394,69,75};
    pl->l3_milieu.rect = (SDL_Rect){196,225,70,74};
    pl->l3_droite.rect = (SDL_Rect){193,53,72,74};
    pl->main_joueur = (SDL_Rect){278,530,282,62 };
    pl->haut.rect = (SDL_Rect){31,224,72,74};
    /* Coordonnees correspondants aux differents plateaux */
    pl->bas.x = 2; pl->bas.y = 0;
    pl->l1_gauche.x = 1; pl->l1_gauche.y = -1;
    pl->l1_milieu.x = 1; pl->l1_milieu.y = 0;
    pl->l1_droite.x = 1; pl->l1_droite.y = 1;
    pl->l2_gauche.x = 0; pl->l2_gauche.y = -1;
    pl->l2_milieu.x = 0; pl->l2_milieu.y = 0;
    pl->l2_droite.x = 0; pl->l2_droite.y = 1;
    pl->l3_gauche.x = -1; pl->l3_gauche.y = -1;
    pl->l3_milieu.x = -1; pl->l3_milieu.y = 0;
    pl->l3_droite.x = -1; pl->l3_droite.y = 1;
    pl->haut.x = -2 ; pl->haut.y = 0 ;
    
    /* Affectation des positions des differentes pieces */
    pl->chien_1.position = &pl->haut; pl->chien_1.position_precedente = &pl->haut; 
    pl->chien_2.position = &pl->l3_droite; pl->chien_2.position_precedente = &pl->l3_droite; 
    pl->chien_3.position = &pl->l3_gauche; pl->chien_3.position_precedente = &pl->l3_gauche; 
    pl->lievre.position = &pl->bas; pl->lievre.position_precedente = &pl->bas;
    pl->bas.occupant = 'l'; pl->haut.occupant = 'c' ;
    pl->l3_droite.occupant = 'c';pl->l3_gauche.occupant ='c';      
    /* Definition des statuts (occupee ou pas) des differentes cases */ 
    pl->bas.estOccupee = 1;pl->haut.estOccupee = 1;pl->l3_droite.estOccupee = 1;
    pl->l3_gauche.estOccupee = 1;pl->l3_milieu.estOccupee = 0;pl->l1_milieu.estOccupee = 0;
    pl->l1_gauche.estOccupee = 0;pl->l1_droite.estOccupee = 0;pl->l2_milieu.estOccupee = 0;
    pl->l2_gauche.estOccupee = 0;pl->l2_droite.estOccupee = 0;
    /* Chargement des images des differentes pieces */
    loadImage("images/imagesBMP/chien.bmp",renderer,&pl->chien_1.position->rect) ;   
    loadImage("images/imagesBMP/chien.bmp",renderer,&pl->chien_2.position->rect) ;   
    loadImage("images/imagesBMP/chien.bmp",renderer,&pl->chien_3.position->rect) ;   
    loadImage("images/imagesBMP/lievre.bmp",renderer,&pl->lievre.position->rect) ;
    if (joueurAvecMain == 1)
        loadImage("images/imagesBMP/Main_Joueur1.bmp",renderer,&pl->main_joueur) ;
    else 
        loadImage("images/imagesBMP/Main_Joueur2.bmp",renderer,&pl->main_joueur) ;
    pl->tour_a = 'c';
       
    SDL_RenderPresent(renderer);
}
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
  Case * detectCase (SDL_Point p)
  { 
      Case * c = NULL;
      if(SDL_PointInRect(&p,&pl.bas.rect))
        c = &pl.bas;
      else 
        if(SDL_PointInRect(&p,&pl.haut.rect))
        c = &pl.haut;
      else 
        if(SDL_PointInRect(&p,&pl.l1_droite.rect))
        c = &pl.l1_droite;
      else 
        if(SDL_PointInRect(&p,&pl.l1_gauche.rect))
        c = &pl.l1_gauche;
      else 
        if(SDL_PointInRect(&p,&pl.l1_milieu.rect))
        c = &pl.l1_milieu;
      else 
        if(SDL_PointInRect(&p,&pl.l2_droite.rect))
        c = &pl.l2_droite;
      else 
        if(SDL_PointInRect(&p,&pl.l2_gauche.rect))
        c = &pl.l2_gauche;
      else 
        if(SDL_PointInRect(&p,&pl.l2_milieu.rect))
        c = &pl.l2_milieu;
      else 
        if(SDL_PointInRect(&p,&pl.l3_droite.rect))
        c = &pl.l3_droite;
      else 
        if(SDL_PointInRect(&p,&pl.l3_gauche.rect))
        c = &pl.l3_gauche;
      else 
        if(SDL_PointInRect(&p,&pl.l3_milieu.rect))
        c = &pl.l3_milieu;
        //Quand le click n'est pas dans une case on reintialise le mouvement
     else{
            printf("Deplacement non autorisee\n");
             click_counter = 0;
             caseArrivee =NULL;
             caseDepart = NULL;
     }
    return c;
  }
  int verifDeplacement()
  {
      printf("verif ");
      int x1 = caseDepart->x;int y1 = caseDepart->y;
      int x2 = caseArrivee->x;int y2 = caseArrivee->y;
      printf("Case Depart : %d %d \t Case Arrivee : %d %d \n",x1,y1,x2,y2);
      // On verifie que la case de depart est bien occuppe et que la case d'arrivée est bien vide
      if (!(caseDepart->estOccupee==1 && caseArrivee->estOccupee==0))
        {
          return 0;
        }         
      int autorisee = 0;
      /*Verifiaction des deplacements;*/
      
      //Depalcement des chiens 
      if (pl.tour_a == 'c')
      {
          
          //On verifie que la case de depart contient bien un chien
          if(caseDepart->occupant!='c') return 0;
          //Si le mouvement est un mouvement en arriere on renvoie faux
          if(x2<x1) {
              printf("Deplacement non autorisee\n");
              return 0;
          }
      }
      // Deplacement du lievre
      else{
          //On verifie que la case de depart contient bien un lievre
          if(caseDepart->occupant!='l') {
              printf("Deplacement non autorisee\n");
              return 0;
          }
      }
     // On verifie si le mouvement est d'une unité en diagonale , en abscisse ou en ordonée
        autorisee = ((abs(x1-x2) == abs(y1-y2))          || // mouvement diagonale
                     (abs(x1-x2) == 1 && abs(y1-y2) ==0) || // mouvement horizontale
                     (x1 == x2 && abs(y1-y2) ==1))         // mouvement verticale 
          ;
         // Condition supplémentaire pour les deplacements diagonaux
         if(abs(x1-x2) == abs(y1-y2))
         {
            if ( ! (
                   ((x1==0 && y1 ==0)||(x2==0 && y2 ==0)) ||
                   ((x1==2 && y1 ==0)||(x2==2 && y2 ==0)) ||
                   ((x1==-2 && y1 ==0)||(x2==-2 && y2 ==0))
                   )
              ) autorisee = 0;
         }
         
         if(!autorisee) {
             printf("Deplacement non autorisee\n");   
         }
         return autorisee;   
  }
  void deplacerPiece(SDL_Renderer *r)
  {
      if(caseDepart->occupant == 'c')
      {
        loadImage("images/imagesBMP/chien.bmp",r,&caseArrivee->rect);
        caseArrivee->occupant='c';
        // On change la valeur de la position du chien qui s'est déplacé 
        if (pl.chien_1.position == caseDepart)
            pl.chien_1.position = caseArrivee;
        else if (pl.chien_2.position == caseDepart)
            pl.chien_2.position = caseArrivee;
        else 
            pl.chien_3.position = caseArrivee;
      }
      else{
        loadImage("images/imagesBMP/lievre.bmp",r,&caseArrivee->rect);
        caseArrivee->occupant = 'l';
        pl.lievre.position = caseArrivee;
      }
     SDL_SetRenderDrawColor(r, 255, 255,255,0);                  
     SDL_RenderFillRect(r,&caseDepart->rect);
     caseDepart->occupant='n';
     caseDepart->estOccupee=0;
     caseArrivee->estOccupee=1;
     SDL_RenderPresent(r);
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
                joueurAvecMain = 2;
                switchScreen(renderer,"images/imagesBMP/recapLievre.bmp","*",0);
                switchScreen(renderer,"images/imagesBMP/board2.bmp","gameBoard",2000);
                initPartie(&pl,renderer);
                pl.tour_a = 'c';
            } 
        else if(SDL_PointInRect(&p,&mode2Joueurs.option2)) 
        {
            //Joueur 1 est le chien | Joueur 2 est le lievre
                joueurAvecMain = 1;
                switchScreen(renderer,"images/imagesBMP/recapChien.bmp","*",0);
                switchScreen(renderer,"images/imagesBMP/board1.bmp","gameBoard",2000);
                initPartie(&pl,renderer);
                pl.tour_a = 'c';
        }
        else if(SDL_PointInRect(&p,&mode2Joueurs.retour))
        {
            switchScreen(renderer,"images/imagesBMP/commencerUnePartie.bmp","commencerPartie",0);
        } 
    }
    else if(strstr(currentFenetre,"gameBoard")!=NULL)
    {
        
        if (detectCase(p)!=NULL) click_counter++;
         
         
        if (click_counter == 2)
            caseArrivee = detectCase(p);
        else if(click_counter == 1)
            caseDepart = detectCase(p);
        
        if(caseDepart !=NULL && caseArrivee !=NULL )
        {
            if(verifDeplacement())
            {
            deplacerPiece(renderer);
            //On donne la main au joueurSuivant et on modifie l'affichage
            SDL_SetRenderDrawColor(renderer, 0, 0,0,0);                  
            SDL_RenderFillRect(renderer,&pl.main_joueur);
            if(joueurAvecMain == 1){
               loadImage("images/imagesBMP/Main_Joueur2.bmp",renderer,&pl.main_joueur) ;
               joueurAvecMain = 2;
            }  
            else {
               loadImage("images/imagesBMP/Main_Joueur1.bmp",renderer,&pl.main_joueur) ; 
               joueurAvecMain = 1;
            }
            pl.tour_a = (pl.tour_a == 'c') ?  'l' :  'c';

            }
            else 
                printf("Deplacement non autorisee\n");
            click_counter = 0;
            caseArrivee =NULL;
            caseDepart = NULL;                        
        }
        
        
        
    }
  }

 void verifGagnant()
 {
     // On verifie si les chiens ont gagnes

 }

