#pragma once
#include "common.h"
#include "cmath"
#include "string"
// #include "piece.h"

class knight : public piece{
    public:
        knight(int x, int y, int color, int gridSize, SDL_Renderer *renderer);
        bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
    private:
        
};

knight :: knight(int ix, int iy, int pcolor, int gridSize, SDL_Renderer *renderer) : piece(ix, iy, pcolor, (pcolor == 0) ? "../Chess/wknight.png" : "../Chess/bknight.png", gridSize, renderer){
    
}

bool knight :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(indexx == x && indexy == y)
        return false;
    int cx = abs(indexx/gridSize - x/gridSize);
    int cy = abs(indexy/gridSize - y/gridSize);
    if((cx == 1 && cy == 2) || (cx == 2 && cy == 1)){

    }
    else{
        return false;
    }
    for(int i = 0; i < pieces.size(); i++){
        if(pieces[i]->x == indexx && pieces[i]->y == indexy){
            if(pieces[i]->color == color)
                return false;
            else{
                if(capture){
                    if(i < draggedPiece)
                        draggedPiece--;
                    delete pieces[i];
                    pieces[i] = nullptr;
                    pieces.erase(pieces.begin()+i);
                }
                return true;
            }
        }
    }
    return true;
}

bool knight :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    for(int i = 0; i < pieces.size(); i++){
        if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
            int xoff = abs(x/gridSize - pieces[i]->x/gridSize);
            int yoff = abs(y/gridSize - pieces[i]->y/gridSize);
            if((xoff == 1 && yoff == 2) || (xoff == 2 && yoff == 1)){
                return true;
            }
        }
    }
    return false;
}

bool knight :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    int xoff = abs(x/gridSize - ix/gridSize);
    int yoff = abs(y/gridSize - iy/gridSize);
    if(xoff == 1 && yoff == 2)
        return true;
    else if(xoff == 2 && yoff == 1)
        return true;
    else
        return false;
}