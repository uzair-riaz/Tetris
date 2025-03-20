#include "Tetris.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window=SDL_CreateWindow("Tetris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1366,768,SDL_WINDOW_FULLSCREEN);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
    int choice=-1,*option;
    std::string name;
    bool optionMenu;
    Graphics start;
    Tetris game(window,renderer);
    bool gameStart=start.titleScreen(window,renderer);
    if(gameStart){
        while(choice){
            optionMenu=true;
            choice=start.mainMenu();
            switch(choice){
            case 1:
                name=start.playerName();
                game.setPlayerName(name);
                SDL_ShowCursor(0);
                game.startGame();
                SDL_ShowCursor(1);
                choice=-1;
                break;
            case 2:
                while(optionMenu){
                    option=start.optionsSubMenu();
                    if(option[2]==0)
                        optionMenu=false;
                    if(option[0]==1)
                        game.setSoundOn(!game.getSoundOn());
                    if(option[1]==2)
                        game.setLevel(!game.getLevel());
                }
                break;
            case 3:
                choice=start.helpSubMenu();
                break;
            case 4:
                choice=start.creditsSubMenu();
                break;
            case 5:
                choice=0;
                gameStart=false;
                break;
            default:
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
