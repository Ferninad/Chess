#pragma once
#include "common.h"
#include "cmath"
#include "string"
// #include "piece.h"

class bishop : public piece{
    public:
        bishop(int x, int y, int color, int gridSize, SDL_Renderer *renderer);
        bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
    private:
        
};

bishop :: bishop(int ix, int iy, int pcolor, int gridSize, SDL_Renderer *renderer) : piece(ix, iy, pcolor, (pcolor == 0) ? "../Chess/wbishop.png" : "../Chess/bbishop.png", gridSize, renderer){
    
}

bool bishop :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(indexx == x && indexy == y)
        return false;
    else if(abs(indexx - x) != abs(indexy - y))
        return false;
    int xamount;
    int yamount;

    if(indexx > x)
        xamount = -1*gridSize;
    else
        xamount = 1*gridSize;
    if(indexy > y)
        yamount = -1*gridSize;
    else
        yamount = 1*gridSize;

    int ix = indexx+xamount;
    int iy = indexy+yamount;
    while(ix != x && iy != y){
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x == ix && pieces[i]->y == iy)
                return false;
        }
        ix += xamount;
        iy += yamount;
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

bool bishop :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    for(int xoff = -1; xoff <= 1; xoff+=2){
        for(int yoff = -1; yoff <= 1; yoff+=2){
            int ix = x/gridSize+xoff;
            int iy = y/gridSize+yoff;
            bool term = false;
            while(ix >= 0 && ix < 8 && iy >= 0 && iy < 8){
                for(int i = 0; i < pieces.size(); i++){
                    if(pieces[i]->x/gridSize == ix && pieces[i]->y/gridSize == iy && i != ignore){
                        if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                            return true;
                        }
                        else{
                            term = true;
                            i = pieces.size();
                        }
                    }
                }
                if(term) //breaks while because path doesn't check
                   break;
                
                ix += xoff;
                iy += yoff;
            }
        }
    }
    return false;
}

bool bishop :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    for(int xoff = -1; xoff <= 1; xoff+=2){
        for(int yoff = -1; yoff <= 1; yoff+=2){
            int ax = x/gridSize+xoff;
            int ay = y/gridSize+yoff;
            bool term = false;
            while(ax >= 0 && ax < 8 && ay >= 0 && ay < 8){
                if(ax == ix/gridSize && ay == iy/gridSize){
                    return true;
                }
                else{
                    for(int i = 0; i < pieces.size(); i++){
                        if(pieces[i]->x/gridSize == ax && pieces[i]->y/gridSize == ay){
                            i = pieces.size();
                            term = true;
                        }
                    }
                }
        
                if(term) //breaks while because path doesn't check
                   break;
                
                ax += xoff;
                ay += yoff;
            }
        }
    }
    return false;
}