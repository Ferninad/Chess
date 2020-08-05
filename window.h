#pragma once
#include "common.h"
#include "cmath"
#include "string"

class win{
    public:
        SDL_Window *window;
        SDL_GLContext glContext;
        SDL_Surface *gScreenSurface = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Rect pos;

        int screenWidth;
        int screenHeight;

        win();
        win(int width, int height);
        ~win();
        bool Init();
        void CleanUp();
        void RenderImage(SDL_Texture *img, int posx, int posy, int width, int height);
        SDL_Texture* CreateTexture(string imgsrc);
};

win :: win(){
    screenWidth = 600;
    screenHeight = 600;
    // //Error Checking/Initialisation
    // if (!Init())
    // {
    //     printf("Failed to Initialize");
    //     return -1;
    // }

    // // Clear buffer with black background
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);

    // //Swap Render Buffers
    // SDL_GL_SwapWindow(window);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);
}

win :: win(int width, int height){
    screenWidth = width;
    screenHeight = height;
    //Error Checking/Initialisation
    if (!Init())
    {
        printf("Failed to Initialize");
        throw -1;
    }

    // Clear buffer with black background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Swap Render Buffers
    SDL_GL_SwapWindow(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

win :: ~win(){
    CleanUp();
}

bool win :: Init()
{
    if (SDL_Init(SDL_INIT_NOPARACHUTE & SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        //Specify OpenGL Version (4.2)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_Log("SDL Initialised");
    }

    //Create Window Instance
    window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth,
        screenHeight,   
        SDL_WINDOW_OPENGL);

    //Check that the window was succesfully created
    if (window == NULL)
    {
        //Print error, if null
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }
    else{
        gScreenSurface = SDL_GetWindowSurface(window);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Log("Window Successful Generated");
    }
    //Map OpenGL Context to Window
    glContext = SDL_GL_CreateContext(window);

    return true;
}

void win :: CleanUp()
{
    //Free up resources
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* win :: CreateTexture(string imgsrc){
    return IMG_LoadTexture(renderer, imgsrc.c_str());
}

void win :: RenderImage(SDL_Texture *img, int posx, int posy, int width, int height){
    int w, h; //image width and height
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    pos.x = posx; pos.y = posy; pos.w = width; pos.h = height;
    SDL_RenderCopy(renderer, img, NULL, &pos);
    img = nullptr;
}