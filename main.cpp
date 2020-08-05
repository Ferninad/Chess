#include "common.h"
#include "cmath"
#include "string"
#include "board.h"

void Run(win &gmwin);

int main()
{
    win gmwin = win(600, 600);

    Run(gmwin);

    gmwin.~win();
    return 0;
}

void Run(win &gmwin)
{
    bool gameLoop = true;
    srand(time(NULL));

    board cboard = board(gmwin.screenWidth, gmwin.screenHeight, &gmwin);
    cboard.SetBoard();
    board cboard2 = board(gmwin.screenWidth, gmwin.screenHeight, &gmwin);
    cboard2.SetBoard();
    board *playboard = &cboard;

    SDL_GetMouseState(&playboard->mx, &playboard->my);
    playboard->DrawGrid();
    playboard->RenderPieces(true);
    while (gameLoop)
    {   
        SDL_RenderPresent(gmwin.renderer);
        playboard->pmx = playboard->mx;
        playboard->pmy = playboard->my;
        SDL_GetMouseState(&playboard->mx, &playboard->my);
        playboard->px = playboard->mx / playboard->gridSize;
        playboard->py = playboard->my / playboard->gridSize;
        
        if(playboard->dragging){
            playboard->DrawGrid();
            playboard->RenderPieces(false);
            playboard->pieces[playboard->draggedPiece]->dx = playboard->mx - playboard->gridSize/2;
            playboard->pieces[playboard->draggedPiece]->dy = playboard->my - playboard->gridSize/2;
            playboard->DrawGrid();
            playboard->RenderPieces(true);
        }
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameLoop = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    playboard->LeftClick();
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT){
                    playboard->LeftRelease();
                }
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        gameLoop = false;
                        break;
                    case SDLK_a:
                        playboard->debug = true;
                        for(int i = 0; i < 8; i++){
                            for(int j = 0; j < 8; j++){
                                bool p = false;
                                for(int k = 0; k < playboard->pieces.size(); k++){
                                    if(playboard->pieces[k]->x/playboard->gridSize == j && playboard->pieces[k]->y/playboard->gridSize == i){
                                        cout << k << "\t";
                                        p = true;
                                    }
                                }
                                if(!p)
                                    cout << "_\t";
                            }
                            cout << endl << endl;
                        }
                        break;
                    case SDLK_SPACE:
                        if(!playboard->dragging){
                            if(playboard == &cboard){
                                playboard = &cboard2;
                            }
                            else if(playboard == &cboard2){
                                playboard = &cboard;
                            }
                            cout << playboard->pieces.size() << endl;;
                            playboard->DrawGrid();
                            playboard->RenderPieces(true);
                            cout << "switch" << endl;
                        }
                    default:
                        break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym){
                    default:
                        break;
                }
            }
        }
    }
}