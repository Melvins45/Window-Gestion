
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int main ( int argc, char** argv )
{
    SDL_Surface *ecran=NULL;
    SDL_Surface *zozor=NULL;
    SDL_Event event;
    bool continuer=true;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL ");
            exit(EXIT_FAILURE);
        }

    ecran=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    zozor=SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor,SDL_SRCCOLORKEY,SDL_MapRGB(zozor->format,0,0,255));
    SDL_Rect position;
    position.x=ecran->w/2 - zozor->w/2;
    position.y=ecran->h/2 - zozor->h/2;
    int pause=0;


    int i=0;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=false;
                break;
            case SDL_VIDEORESIZE:
                position.x=event.resize.w/2-zozor->w/2;
                position.y=event.resize.h/2-zozor->h/2;
                break;
            case SDL_ACTIVEEVENT:
                if ((event.active.state & SDL_APPACTIVE) == SDL_APPACTIVE)
                    {
                        if (event.active.gain == 0)/* La fenêtre a été réduite en barre des tâches */
                            pause = 1;
                        else if (event.active.gain == 1)
                        /* La fenêtre a été restaurée */
                            pause = 0;
                    }
                break;
        }
        SDL_BlitSurface(zozor,NULL,ecran,&position);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();
    return EXIT_SUCCESS;
}
