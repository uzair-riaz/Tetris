#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>
#include <stdlib.h>
#include <string>

class Graphics{
    SDL_Window* window;                                                         // pointer to the window to draw in
    SDL_Renderer* renderer;                                                     // pointer to the renderer used for drawing in the window
    public:
        Graphics();                                                             // instantiates the class setting the window and renderer pointer to NULL
        bool titleScreen(SDL_Window*,SDL_Renderer*);                            // called when the game starts and displays the title of the screen
        void draw(SDL_Window*,SDL_Renderer*,int**,int**,int,int,int,int,int);   // draws everything in the window using renderer, from board to blocks
        int mainMenu();                                                         // draws the main menu in the window using renderer when the game is started with
        int* optionsSubMenu();                                                  // called when options menu is selected from the main menu
        int helpSubMenu();                                                      // called when help menu is selected from the main menu
        int creditsSubMenu();                                                   // called when the credits menu is selected from the main menu
        std::string playerName();                                               // called when the game starts to prompt the player for his/her name
        virtual ~Graphics();                                                    // destroys the class instance
};

#endif // GRAPHICS_H
