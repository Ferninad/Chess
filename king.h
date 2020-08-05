#pragma once
#include "common.h"
#include "cmath"
#include "string"
// #include "piece.h"

class king : public piece{
    public:
        king(int x, int y, int color, int gridSize, SDL_Renderer *renderer);
        bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
        bool CheckCheck(int ignore, vector<piece*> &pieces, int draggedPiece, int turn, int &checkingPiece);
        bool first = true;
    private:

};

king :: king(int ix, int iy, int pcolor, int gridSize, SDL_Renderer *renderer) : piece(ix, iy, pcolor, (pcolor == 0) ? "../Chess/wking.png" : "../Chess/bking.png", gridSize, renderer){
    
}

bool king :: Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece){
    if(indexx == x && indexy == y)
        return false;
    if(first){
        if(abs(indexx/gridSize - x/gridSize) == 2 && indexy - y == 0){
            if(!checked){ 
                if(indexx < x){
                    int prevx = x;
                    x = x - gridSize;
                    if(CheckCheck(-1, pieces, draggedPiece, turn, checkingPiece)){
                        x = prevx;
                        return false;
                    }
                    x = prevx;
                    for(int i = x/gridSize-1; i >= 0; i--){
                        for(int j = 0; j < pieces.size(); j++){
                            if(i == 0){
                                if(pieces[j]->x == 0 && pieces[j]->y == y && pieces[j]->imgsrc.find("rook") != std::string::npos){
                                    pieces[j]->x = ((indexx/gridSize)+1)*gridSize;
                                    pieces[j]->dx = ((indexx/gridSize)+1)*gridSize;
                                    first = false;
                                    return true;
                                }
                            }
                            else if(pieces[j]->x/gridSize == i && pieces[j]->y == indexy){
                                return false;
                            }
                        }
                    }
                }
                else{
                    int prevx = x;
                    x = x + gridSize;
                    if(CheckCheck(-1, pieces, draggedPiece, turn, checkingPiece)){
                        x = prevx;
                        return false;
                    }
                    x = prevx;
                    for(int i = x/gridSize+1; i <= 7; i++){
                        for(int j = 0; j < pieces.size(); j++){
                            if(i == 7){
                                if(pieces[j]->x/gridSize == 7 && pieces[j]->y == y && pieces[j]->imgsrc.find("rook") != std::string::npos){
                                    pieces[j]->x = ((indexx/gridSize)-1)*gridSize;
                                    pieces[j]->dx = ((indexx/gridSize)-1)*gridSize;
                                    first = false;
                                    return true;
                                }
                            }
                            else if(pieces[j]->x/gridSize == i && pieces[j]->y == indexy){
                                return false;
                            }
                        }
                    }
                }
            }
            else
                return false;
        }
    }
    if(abs(indexx/gridSize - x/gridSize) > 1 || abs(indexy/gridSize - y/gridSize) > 1)
        return false;
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

bool king :: Checking(int ignore, vector<piece*> &pieces, int draggedPiece){
    for(int xoff = -1; xoff < 2; xoff++){
        for(int yoff = -1; yoff < 2; yoff++){
            if(!(xoff == 0 && yoff == 0)){
                for(int i = 0; i < pieces.size(); i++){
                    if(pieces[i]->x/gridSize == x/gridSize+xoff && pieces[i]->y/gridSize == y/gridSize+yoff){
                        if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color != color){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool king :: Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece){
    for(int xoff = -1; xoff < 2; xoff++){
        for(int yoff = -1; yoff < 2; yoff++){
            if(!(xoff == 0 && yoff == 0)){
                if(x/gridSize+xoff == ix/gridSize && y/gridSize+yoff == iy/gridSize){
                    return true;
                }
            }
        }
    }
    return false;
}

bool king :: CheckCheck(int ignore, vector<piece*> &pieces, int draggedPiece, int turn, int &checkingPiece){
    for(int i = 0; i < pieces.size(); i++){
        if(pieces[i]->color != turn && i != ignore){
            if(pieces[i]->Checking(ignore, pieces, draggedPiece)){
                cout << turn << " is checked" << endl;
                checkingPiece = i;
                cout << "piece at " << pieces[i]->x/gridSize << "\t" << pieces[i]->y/gridSize << endl;
                return true;
            }
        }
    }
    cout << turn << " is not checked" << endl;
    return false;
}