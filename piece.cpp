#include "common.h"
#include "cmath"
#include "string"
#include "piece.h"

piece :: piece(){
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
}

piece :: piece(int ix, int iy, int pcolor, string src, int gSize, SDL_Renderer *renderer){
    x = ix;
    y = iy;
    dx = ix;
    dy = iy;
    color = pcolor;
    gridSize = gSize;
    imgsrc = src;
    img = IMG_LoadTexture(renderer, imgsrc.c_str());
}

piece :: ~piece(){
    SDL_DestroyTexture(img);
    img = nullptr;
}

void piece :: Promote(){

}

bool piece :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(x == indexx && y == indexy)
        return false;
    return true;
}

bool piece :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    return false;
}

bool piece :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    return false;
}