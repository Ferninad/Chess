#pragma once
#include "common.h"
#include "cmath"
#include "string"
// #include "piece.h"

class pawn : public piece{
    public:
        pawn(int x, int y, int color, int gridSize, SDL_Renderer *renderer);
        bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
        bool first = true;
    private:
        
};

pawn :: pawn(int ix, int iy, int pcolor, int gridSize, SDL_Renderer *renderer) : piece(ix, iy, pcolor, (pcolor == 0) ? "../Chess/wpawn.png" : "../Chess/bpawn.png", gridSize, renderer){
    
}

bool pawn :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(indexx == x && indexy == y)
        return false;
    if(abs(y/gridSize - indexy/gridSize) > 2)
        return false;
    if(abs(x/gridSize - indexx/gridSize) > 1)
        return false;
    if(color == 0){
        if(indexy >= y)
            return false;
        if(y/gridSize - indexy/gridSize == 2){
            if(first){
                if(indexx == x){
                    for(int i = 0; i < pieces.size(); i++){
                        if(pieces[i]->x == indexx && (pieces[i]->y/gridSize == (indexy/gridSize) || pieces[i]->y/gridSize == (indexy/gridSize)+1)){
                            return false;
                        }
                    }
                    first = false;
                    twopush = true;
                    return true;
                }
                else
                    return false;
            }
            else
                return false;
        }
        if(indexx == x){
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x == indexx && pieces[i]->y == indexy){
                    return false;
                }
            }
            return true;
        }
        else{
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x == indexx && pieces[i]->y == indexy){
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
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x == indexx && pieces[i]->y/gridSize == indexy/gridSize+1){
                    if(pieces[i]->imgsrc.find("pawn") != std::string::npos && pieces[i]->twopush){
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
            return false;
        }
    }
    else{
        if(indexy <= y)
            return false;
        if(y/gridSize - indexy/gridSize == -2){
            if(first){
                if(indexx == x){
                    for(int i = 0; i < pieces.size(); i++){
                        if(pieces[i]->x == indexx && (pieces[i]->y/gridSize == (indexy/gridSize) || pieces[i]->y/gridSize == (indexy/gridSize)-1)){
                            return false;
                        }
                    }
                    first = false;
                    twopush = true;
                    return true;
                }
                else
                    return false;
            }
            else
                return false;
        }
        if(indexx == x){
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x == indexx && pieces[i]->y == indexy){
                    return false;
                }
            }
            return true;
        }
        else{
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x == indexx && pieces[i]->y == indexy){
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
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x/gridSize == indexx/gridSize && pieces[i]->y/gridSize == indexy/gridSize-1){
                    if(pieces[i]->imgsrc.find("pawn") != std::string::npos && pieces[i]->twopush){
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
            return false;
        }
    }
    return true;
}

bool pawn :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    if(color == 0){
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x/gridSize == x/gridSize-1 || pieces[i]->x/gridSize == x/gridSize+1){
                if(pieces[i]->y/gridSize == y/gridSize-1 && pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                    return true;
                }
            }
        }
    }
    else{
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x/gridSize == x/gridSize-1 || pieces[i]->x/gridSize == x/gridSize+1){
                if(pieces[i]->y/gridSize == y/gridSize+1 && pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                    return true;
                }
            }
        }
    }
    return false;
}

bool pawn :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    if(color == 0){
        if(x/gridSize-1 == ix/gridSize || x/gridSize+1 == ix/gridSize){
            if(y/gridSize-1 == iy/gridSize){
                return true;
            }
        }
    }
    else{
        if(x/gridSize-1 == ix/gridSize || x/gridSize+1 == ix/gridSize){
            if(y/gridSize+1 == iy/gridSize){
                return true;
            }
        }
    }
    return false;
}