#include "Graphics.h"

Graphics::Graphics():window(NULL),renderer(NULL){
}

Graphics::~Graphics(){
}

void Graphics::draw(SDL_Window* win,SDL_Renderer* ren,int** boardArr,int** blockArr,int boardHeight,int boardWidth,int blockHeight,int blockWidth,int score){
    static bool first=true;
    if(first && (window==NULL && renderer==NULL)){
        window=win;
        renderer=ren;
        first=false;
    }
    SDL_Surface *screen=SDL_GetWindowSurface(window);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Color color={30,0,30,0};
    char intToString[10];
    itoa(score,intToString,10);
    char *scoreStr="Score";
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",20);
    SDL_Surface *sc=TTF_RenderText_Solid(font,scoreStr,color);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,sc);
    SDL_Rect rect;
    rect.x=screen->w/2+100;
    rect.y=screen->h/4-50;
    rect.w=sc->w;
    rect.h=sc->h;
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_Surface *scoreSurface=TTF_RenderText_Solid(font,intToString,color);
    SDL_Texture *scoreTexture=SDL_CreateTextureFromSurface(renderer,scoreSurface);
    SDL_Rect scoreRect;
    scoreRect.x=screen->w/2+100;
    scoreRect.y=screen->h/4-25;
    scoreRect.w=scoreSurface->w;
    scoreRect.h=scoreSurface->h;
    SDL_RenderCopy(renderer,scoreTexture,NULL,&scoreRect);
    int x=0,y=0;
    for(int i=0;i<boardHeight;i++){
        for(int j=0;j<boardWidth;j++){
            if(boardArr[i][j]!=0){
                if(i==boardHeight-1 || j==0 || j==boardWidth-1){SDL_SetRenderDrawColor(renderer,30,0,30,0);}
                else{SDL_SetRenderDrawColor(renderer,112,0,152,0);}
                SDL_Rect boardRect;
                boardRect.h=10;
                boardRect.w=10;
                boardRect.x=screen->w/4+70+x;
                boardRect.y=screen->h/4-50+y;
                SDL_RenderFillRect(renderer,&boardRect);
            }
            x+=11;
        }
        y+=11;
        x=0;
    }

    char *blockStr="Next";
    SDL_Surface *blockSurface=TTF_RenderText_Solid(font,blockStr,color);
    SDL_Texture *blockTexture=SDL_CreateTextureFromSurface(renderer,blockSurface);
    SDL_Rect blockStrRect;
    blockStrRect.x=screen->w/2+110;
    blockStrRect.y=screen->h/2-30;
    blockStrRect.w=blockSurface->w;
    blockStrRect.h=blockSurface->h;
    SDL_RenderCopy(renderer,blockTexture,NULL,&blockStrRect);

    SDL_SetRenderDrawColor(renderer,112,0,152,0);
    x=y=0;
    for(int i=0;i<blockHeight;i++){
        for(int j=0;j<blockWidth;j++){
            if(blockArr[i][j]!=0){
                SDL_Rect blockRect;
                blockRect.w=10;
                blockRect.h=10;
                blockRect.x=screen->w/2+100+x;
                blockRect.y=screen->h/2+y;
                SDL_RenderFillRect(renderer,&blockRect);
            }
            x+=11;
        }
        y+=11;
        x=0;
    }

    SDL_RenderPresent(renderer);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(sc);
    SDL_FreeSurface(blockSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(blockTexture);
    SDL_Delay(100);
}

bool Graphics::titleScreen(SDL_Window* win,SDL_Renderer* ren){
    static bool first=true;
    if(first && (window==NULL && renderer==NULL)){
        window=win;
        renderer=ren;
        first=false;
    }
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Surface* screen=SDL_GetWindowSurface(window);
    TTF_Font *fontLarge=TTF_OpenFont("OpenSans-Bold.ttf",50);
    TTF_Font *fontSmall=TTF_OpenFont("OpenSans-Bold.ttf",20);
    char* tetris="Tetris";
    char* prompt="Press any key to continue...";
    SDL_Color color={0,0,0,0};
    SDL_Surface *surfaces[2];
    SDL_Texture *textures[2];
    SDL_Rect rects[2];
    surfaces[0]=TTF_RenderText_Solid(fontLarge,tetris,color);
    surfaces[1]=TTF_RenderText_Solid(fontSmall,prompt,color);
    textures[0]=SDL_CreateTextureFromSurface(renderer,surfaces[0]);
    textures[1]=SDL_CreateTextureFromSurface(renderer,surfaces[1]);
    rects[0].x=screen->w/2-surfaces[0]->w+50;
    rects[0].y=screen->h/2-surfaces[0]->h-50;
    rects[0].w=surfaces[0]->w;
    rects[0].h=surfaces[0]->h;
    rects[1].x=screen->w/2-surfaces[1]->w+120;
    rects[1].y=screen->h/2-surfaces[1]->h+70;
    rects[1].w=surfaces[1]->w;
    rects[1].h=surfaces[1]->h;
    SDL_FreeSurface(screen);
    SDL_RenderCopy(renderer,textures[0],NULL,&rects[0]);
    SDL_RenderCopy(renderer,textures[1],NULL,&rects[1]);

    SDL_Event event;
    while(true){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                SDL_FreeSurface(surfaces[0]);
                SDL_FreeSurface(surfaces[1]);
                SDL_DestroyTexture(textures[0]);
                SDL_DestroyTexture(textures[1]);
                return false;
            case SDL_MOUSEBUTTONDOWN:
                return true;
            case SDL_KEYDOWN:
                return true;
            }
        }
    }
}

int Graphics::mainMenu(){
    SDL_Surface* screen=SDL_GetWindowSurface(window);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",30);
    SDL_Color color={0,0,0,0};
    SDL_Color colorHover={255,0,0,0};
    int menuItems=5;
    char* menu[menuItems]={"Start Game","Options","Help","Credits","Exit"};
    SDL_Surface* surfaces[menuItems];
    SDL_Texture* textures[menuItems];
    SDL_Rect rects[menuItems];
    int y=0,width;
    for(int i=0;i<menuItems;i++){
        surfaces[i]=TTF_RenderText_Solid(font,menu[i],color);
        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
        if(i==0)
            width=surfaces[0]->w;
        rects[i].x=screen->w/2-width;
        rects[i].y=screen->h/2-surfaces[i]->h-70+y;
        rects[i].w=surfaces[i]->w;
        rects[i].h=surfaces[i]->h;
        SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
        y+=surfaces[i]->h+2;
    }
    SDL_FreeSurface(screen);

    SDL_Event event;
    while(true){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                for(int i=0;i<menuItems;i++){
                    SDL_FreeSurface(surfaces[i]);
                    surfaces[i]=NULL;
                    SDL_DestroyTexture(textures[i]);
                    textures[i]=NULL;
                }
                return menuItems;
            case SDL_MOUSEMOTION:
                for(int i=0;i<menuItems;i++){
                    if((event.motion.x>=rects[i].x && event.motion.x<=(rects[i].x+rects[i].w)) && (event.motion.y>=rects[i].y && event.motion.y<=(rects[i].y+rects[i].h))){
                        SDL_DestroyTexture(textures[i]);
                        SDL_FreeSurface(surfaces[i]);
                        surfaces[i]=TTF_RenderText_Solid(font,menu[i],colorHover);
                        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
                    }
                    else{
                        SDL_DestroyTexture(textures[i]);
                        SDL_FreeSurface(surfaces[i]);
                        surfaces[i]=TTF_RenderText_Solid(font,menu[i],color);
                        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
                    }
                    SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i=0;i<menuItems;i++){
                    if((event.button.x>=rects[i].x && event.button.x<=(rects[i].x+rects[i].w)) && (event.button.y>=rects[i].y && event.button.y<=(rects[i].y+rects[i].h)))
                        return i+1;
                }
            default:
                break;
            }
        }
    }
}

int Graphics::creditsSubMenu(){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Surface *screen=SDL_GetWindowSurface(window);
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",30);
    int numOfCredits=6;
    SDL_Color color={0,0,0,0};
    SDL_Color colorHover={255,0,0,0};
    char *credits[numOfCredits]={"Programmed By:","Syed Arsal Sohail","Muhammad Haneef","Saqib Ahmed Khan","Uzair Riaz Farooqui","Back"};
    SDL_Surface *surfaces[numOfCredits];
    SDL_Texture *textures[numOfCredits];
    SDL_Rect rects[numOfCredits];
    int y=0;
    for(int i=0;i<numOfCredits;i++){
        surfaces[i]=TTF_RenderText_Solid(font,credits[i],color);
        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
        rects[i].x=screen->w/2-surfaces[i]->w+100;
        rects[i].y=screen->h/2-100-surfaces[i]->h+y;
        rects[i].w=surfaces[i]->w;
        rects[i].h=surfaces[i]->h;
        SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
        y+=surfaces[i]->h+2;
    }
    SDL_FreeSurface(screen);

    SDL_Event event;
    while(true){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                for(int i=0;i<numOfCredits;i++){
                    SDL_FreeSurface(surfaces[i]);
                    surfaces[i]=NULL;
                    SDL_DestroyTexture(textures[i]);
                    textures[i]=NULL;
                }
                return 0;
            case SDL_MOUSEMOTION:
                if((event.motion.x>=rects[numOfCredits-1].x && event.motion.x<=(rects[numOfCredits-1].x+rects[numOfCredits-1].w)) && (event.motion.y>=rects[numOfCredits-1].y && event.motion.y<=(rects[numOfCredits-1].y+rects[numOfCredits-1].h))){
                    SDL_DestroyTexture(textures[numOfCredits-1]);
                    SDL_FreeSurface(surfaces[numOfCredits-1]);
                    surfaces[numOfCredits-1]=TTF_RenderText_Solid(font,credits[numOfCredits-1],colorHover);
                    textures[numOfCredits-1]=SDL_CreateTextureFromSurface(renderer,surfaces[numOfCredits-1]);
                }
                else{
                    SDL_DestroyTexture(textures[numOfCredits-1]);
                    SDL_FreeSurface(surfaces[numOfCredits-1]);
                    surfaces[numOfCredits-1]=TTF_RenderText_Solid(font,credits[numOfCredits-1],color);
                    textures[numOfCredits-1]=SDL_CreateTextureFromSurface(renderer,surfaces[numOfCredits-1]);
                }
                SDL_RenderCopy(renderer,textures[numOfCredits-1],NULL,&rects[numOfCredits-1]);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if((event.button.x>=rects[numOfCredits-1].x && event.button.x<=(rects[numOfCredits-1].x+rects[numOfCredits-1].w)) && (event.button.y>=rects[numOfCredits-1].y && event.button.y<=(rects[numOfCredits-1].y+rects[numOfCredits-1].h)))
                    return 1;
            }
        }
    }
}

int* Graphics::optionsSubMenu(){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",30);
    SDL_Surface *screen=SDL_GetWindowSurface(window);
    int numOfOptions=3;
    SDL_Color color={0,0,0,0};
    SDL_Color colorHover={255,0,0,0};
    char* options[numOfOptions]={"Sound : On","Level : Easy","Back"};
    char* optionsChange[numOfOptions]={"Sound : Off","Level : Hard","Back"};
    static bool toggled[3]={false,false,false};
    int selection[numOfOptions]={0,0,0};
    SDL_Surface *surfaces[numOfOptions];
    SDL_Surface *surfacesChange[numOfOptions];
    SDL_Texture *textures[numOfOptions];
    SDL_Texture *texturesChange[numOfOptions];
    SDL_Rect rects[numOfOptions];
    SDL_Rect rectsChange[numOfOptions];
    int y=0,yChange=0;
    for(int i=0;i<numOfOptions;i++){
        surfacesChange[i]=TTF_RenderText_Solid(font,optionsChange[i],color);
        texturesChange[i]=SDL_CreateTextureFromSurface(renderer,surfacesChange[i]);
        rectsChange[i].x=screen->w/2-surfacesChange[i]->w;
        rectsChange[i].y=screen->h/2-surfacesChange[i]->h+yChange;
        rectsChange[i].w=surfacesChange[i]->w;
        rectsChange[i].h=surfacesChange[i]->h;
        yChange+=surfacesChange[i]->h+2;
        surfaces[i]=TTF_RenderText_Solid(font,options[i],color);
        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
        rects[i].x=screen->w/2-surfaces[i]->w;
        rects[i].y=screen->h/2-surfaces[i]->h+y;
        rects[i].w=surfaces[i]->w;
        rects[i].h=surfaces[i]->h;
        y+=surfaces[i]->h+2;
    }
    for(int i=0;i<numOfOptions;i++){
        if(toggled[i]){
            SDL_FreeSurface(surfaces[i]);
            surfaces[i]=NULL;
            SDL_DestroyTexture(textures[i]);
            textures[i]=NULL;
            SDL_RenderCopy(renderer,texturesChange[i],NULL,&rectsChange[i]);
        }
        else{
            SDL_FreeSurface(surfacesChange[i]);
            surfacesChange[i]=NULL;
            SDL_DestroyTexture(texturesChange[i]);
            texturesChange[i]=NULL;
            SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
        }
    }
    SDL_FreeSurface(screen);

    SDL_Event event;
    while(true){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                for(int i=0;i<numOfOptions;i++){
                    SDL_FreeSurface(surfaces[i]);
                    surfaces[i]=NULL;
                    SDL_DestroyTexture(textures[i]);
                    textures[i]=NULL;
                    SDL_FreeSurface(surfacesChange[i]);
                    surfacesChange[i]=NULL;
                    SDL_DestroyTexture(texturesChange[i]);
                    texturesChange[i]=NULL;
                }
                selection[numOfOptions-1]=0;
                return selection;
            case SDL_MOUSEMOTION:
                for(int i=0;i<numOfOptions;i++){
                    if((event.motion.x>=rects[i].x && event.motion.x<=(rects[i].x+rects[i].w)) && (event.motion.y>=rects[i].y && event.motion.y<=(rects[i].y+rects[i].h))){
                        if(!toggled[i]){
                            if(textures[i]!=NULL)SDL_DestroyTexture(textures[i]);
                            if(surfaces[i]!=NULL)SDL_FreeSurface(surfaces[i]);
                            surfaces[i]=TTF_RenderText_Solid(font,options[i],colorHover);
                            textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
                            SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
                        }
                        else{
                            if(texturesChange[i]!=NULL)SDL_DestroyTexture(texturesChange[i]);
                            if(surfacesChange[i]!=NULL)SDL_FreeSurface(surfacesChange[i]);
                            surfacesChange[i]=TTF_RenderText_Solid(font,optionsChange[i],colorHover);
                            texturesChange[i]=SDL_CreateTextureFromSurface(renderer,surfacesChange[i]);
                            SDL_RenderCopy(renderer,texturesChange[i],NULL,&rectsChange[i]);
                        }
                    }
                    else{
                        if(!toggled[i]){
                            if(textures[i]!=NULL)SDL_DestroyTexture(textures[i]);
                            if(surfaces[i]!=NULL)SDL_FreeSurface(surfaces[i]);
                            surfaces[i]=TTF_RenderText_Solid(font,options[i],color);
                            textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
                            SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
                        }
                        else{
                            if(texturesChange[i]!=NULL)SDL_DestroyTexture(texturesChange[i]);
                            if(surfacesChange[i]!=NULL)SDL_FreeSurface(surfacesChange[i]);
                            surfacesChange[i]=TTF_RenderText_Solid(font,optionsChange[i],color);
                            texturesChange[i]=SDL_CreateTextureFromSurface(renderer,surfacesChange[i]);
                            SDL_RenderCopy(renderer,texturesChange[i],NULL,&rectsChange[i]);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i=0;i<numOfOptions;i++){
                    if((event.button.x>=rects[i].x && event.button.x<=(rects[i].x+rects[i].w)) && (event.button.y>=rects[i].y && event.button.y<=(rects[i].y+rects[i].h))){
                        if(i==numOfOptions-1)
                            return selection;
                        if(!toggled[i]){
                            toggled[i]=true;
                            if(textures[i]!=NULL)SDL_DestroyTexture(texturesChange[i]);
                            if(surfaces[i]!=NULL)SDL_FreeSurface(surfacesChange[i]);
                            surfacesChange[i]=TTF_RenderText_Solid(font,optionsChange[i],color);
                            texturesChange[i]=SDL_CreateTextureFromSurface(renderer,surfacesChange[i]);
                            if(i==0)selection[i]=1;
                            else if(i==1)selection[i]=2;
                            SDL_SetRenderDrawColor(renderer,255,255,255,255);
                            SDL_RenderClear(renderer);
                            for(int i=0;i<numOfOptions;i++){
                                if(toggled[i]){SDL_RenderCopy(renderer,texturesChange[i],NULL,&rectsChange[i]);}
                                else{SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);}
                            }
                        }
                        else if(toggled[i]){
                            toggled[i]=false;
                            if(textures[i]!=NULL)SDL_DestroyTexture(textures[i]);
                            if(surfaces[i]!=NULL)SDL_FreeSurface(surfaces[i]);
                            surfaces[i]=TTF_RenderText_Solid(font,options[i],color);
                            textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
                            if(i==0)selection[i]=1;
                            else if(i==1)selection[i]=2;
                            SDL_SetRenderDrawColor(renderer,255,255,255,255);
                            SDL_RenderClear(renderer);
                            for(int i=0;i<numOfOptions;i++){
                                if(toggled[i]){SDL_RenderCopy(renderer,texturesChange[i],NULL,&rectsChange[i]);}
                                else{SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);}
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}

int Graphics::helpSubMenu(){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",25);
    SDL_Color color={0,0,0,0};
    SDL_Color colorHover={255,0,0,0};
    SDL_Surface *screen=SDL_GetWindowSurface(window);
    SDL_Surface *surfaces[5];
    SDL_Texture *textures[5];
    SDL_Rect rects[5];
    char* help[4]={"Use the left and right arrow keys to move the blocks. Rotate the blocks using space bar.",
                    "Pressing the down arrow key will drop the block quickly. Your goal is to fill the rows",
                    "at the bottom. Each completed row will disappear, giving you more room to continue playing.",
                    "Your game is over if the falling blocks pile up to the top of the board."};
    char* backButton="Back";
    int y=0,width;
    for(int i=0;i<4;i++){
        surfaces[i]=TTF_RenderText_Solid(font,help[i],color);
        textures[i]=SDL_CreateTextureFromSurface(renderer,surfaces[i]);
        if(i==0)
            width=surfaces[i]->w;
        rects[i].x=screen->w-width-200;
        rects[i].y=screen->h/2-200+surfaces[i]->h+y;
        rects[i].w=surfaces[i]->w;
        rects[i].h=surfaces[i]->h;
        SDL_RenderCopy(renderer,textures[i],NULL,&rects[i]);
        y+=surfaces[i]->h+2;
    }
    surfaces[4]=TTF_RenderText_Solid(font,backButton,color);
    textures[4]=SDL_CreateTextureFromSurface(renderer,surfaces[4]);
    rects[4].x=screen->w-width-200;
    rects[4].y=screen->h/2-surfaces[4]->h+y;
    rects[4].w=surfaces[4]->w;
    rects[4].h=surfaces[4]->h;
    SDL_RenderCopy(renderer,textures[4],NULL,&rects[4]);
    SDL_FreeSurface(screen);

    SDL_Event event;
    while(true){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_MOUSEMOTION:
                if((event.motion.x>=rects[4].x && event.motion.x<=(rects[4].x+rects[4].w)) && (event.motion.y>=rects[4].y && event.motion.y<=(rects[4].y+rects[4].h))){
                    SDL_FreeSurface(surfaces[4]);
                    SDL_DestroyTexture(textures[4]);
                    surfaces[4]=TTF_RenderText_Solid(font,backButton,colorHover);
                    textures[4]=SDL_CreateTextureFromSurface(renderer,surfaces[4]);
                    SDL_RenderCopy(renderer,textures[4],NULL,&rects[4]);
                }
                else{
                    SDL_FreeSurface(surfaces[4]);
                    SDL_DestroyTexture(textures[4]);
                    surfaces[4]=TTF_RenderText_Solid(font,backButton,color);
                    textures[4]=SDL_CreateTextureFromSurface(renderer,surfaces[4]);
                    SDL_RenderCopy(renderer,textures[4],NULL,&rects[4]);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if((event.button.x>=rects[4].x && event.button.x<=(rects[4].x+rects[4].w)) && (event.button.y>=rects[4].y && event.button.y<=(rects[4].y+rects[4].h)))
                    return 1;
            }
        }
    }
}

std::string Graphics::playerName(){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Surface *screen=SDL_GetWindowSurface(window);
    TTF_Font *font=TTF_OpenFont("OpenSans-Bold.ttf",20);
    SDL_Color color={30,0,30,0};
    char* player="Enter your name: ";
    SDL_Surface *playerSurface=TTF_RenderText_Solid(font,player,color);
    SDL_Texture *playerTexture=SDL_CreateTextureFromSurface(renderer,playerSurface);
    SDL_Rect playerRect;
    playerRect.x=screen->w/4;
    playerRect.y=screen->h/2;
    playerRect.w=playerSurface->w;
    playerRect.h=playerSurface->h;
    SDL_RenderCopy(renderer,playerTexture,NULL,&playerRect);

    SDL_Event event;
    bool running=true;
    std::string inputStr;
    std::string temp;
    SDL_Surface *inputSurface=NULL;
    SDL_Texture *inputTexture=NULL;
    SDL_Rect inputRect;

    while(running){
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_RETURN || event.key.keysym.sym==SDLK_RETURN2){
                    if(inputStr.length()>0)
                        return inputStr;
                    else
                        running=false;
                }
                else{
                    if(event.key.keysym.sym!=SDLK_BACKSPACE){
                        inputStr+=(char)(event.key.keysym.sym);
                        char* input=new char[inputStr.length()+1];
                        strcpy(input,inputStr.c_str());
                        inputSurface=TTF_RenderText_Solid(font,input,color);
                        inputTexture=SDL_CreateTextureFromSurface(renderer,inputSurface);
                        inputRect.x=screen->w/2-50;
                        inputRect.y=screen->h/2;
                        inputRect.w=inputSurface->w;
                        inputRect.h=inputSurface->h;
                        SDL_RenderCopy(renderer,inputTexture,NULL,&inputRect);
                        SDL_FreeSurface(inputSurface);
                        SDL_DestroyTexture(inputTexture);
                        delete [] input;
                    }
                    else if(event.key.keysym.sym==SDLK_BACKSPACE && inputStr.length()>0){
                        char* input;
                        temp=inputStr.erase(inputStr.size()-1);
                        if(temp.length()>0){
                            inputStr=temp;
                            input=new char[inputStr.length()+1];
                            strcpy(input,inputStr.c_str());
                        }
                        else{
                            input=new char[1];
                            strcpy(input," ");
                        }
                        inputSurface=TTF_RenderText_Solid(font,input,color);
                        inputTexture=SDL_CreateTextureFromSurface(renderer,inputSurface);
                        inputRect.x=screen->w/2-50;
                        inputRect.y=screen->h/2;
                        inputRect.w=inputSurface->w;
                        inputRect.h=inputSurface->h;
                        SDL_SetRenderDrawColor(renderer,255,255,255,255);
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer,playerTexture,NULL,&playerRect);
                        SDL_RenderCopy(renderer,inputTexture,NULL,&inputRect);
                        SDL_FreeSurface(inputSurface);
                        SDL_DestroyTexture(inputTexture);
                        delete [] input;
                    }
                }
            break;
            }
        }
    }
}
