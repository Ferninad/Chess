#pragma once
#include "window.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class board{
    public:
        win *gmwin;
        vector<piece*> pieces;
        int boardWidth;
        int boardHeight;
        int gridSize;
        int draggedPiece = 0;
        int mx, my, pmx, pmy, px, py;
        bool dragging = false;
        bool checked = false;
        bool pro = false;
        int turn = 0;
        int checkingPiece;
        bool debug = false;
        
        board(int screenWidth, int screenHeight, win *gmwin);
        void LeftClick();
        void LeftRelease();
        void SetBoard();
        void Cturn();
        bool CheckCheck(int ignore);
        void Promote();
        void DrawGrid();
        void RenderPieces(bool draw);
};

board :: board(int screenWidth, int screenHeight, win *gamewin){
    gmwin = gamewin;
    boardWidth = screenWidth;
    boardHeight = screenHeight;
    gridSize = screenWidth/8;
}

void board :: DrawGrid(){
    int startcolor = 0;
    for(int i = 0; i < boardWidth; i += gridSize){
        int color = startcolor;
        for(int j = 0; j < boardHeight; j += gridSize){
            if(color == 0){
                SDL_SetRenderDrawColor(gmwin->renderer, 144, 161, 171, 255);
                color = 1;
            }
            else{
                SDL_SetRenderDrawColor(gmwin->renderer, 18, 58, 87, 255);
                color = 0;
            }
            if(dragging){
                if(abs(i/gridSize - (pieces[draggedPiece]->dx+gridSize/2)/gridSize) <= 1 && abs(j/gridSize - (pieces[draggedPiece]->dy+gridSize/2)/gridSize) <= 1){
                    gmwin->pos.x = i;
                    gmwin->pos.y = j;
                    gmwin->pos.w = gridSize;
                    gmwin->pos.h = gridSize;
                    SDL_RenderFillRect(gmwin->renderer, &gmwin->pos);
                }
            }
            else{
                gmwin->pos.x = i;
                gmwin->pos.y = j;
                gmwin->pos.w = gridSize;
                gmwin->pos.h = gridSize;
                SDL_RenderFillRect(gmwin->renderer, &gmwin->pos);
            }
        }
        if(startcolor == 0)
            startcolor = 1;
        else
            startcolor = 0;
    }
}

void board :: LeftClick(){
    if(pro){
        if(px == pieces[draggedPiece]->x/gridSize){
            if(pieces[draggedPiece]->y == 0){
                if(py == 0){
                    pieces.insert(pieces.begin()+draggedPiece, new queen(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 1){
                    pieces.insert(pieces.begin()+draggedPiece, new rook(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 2){
                    pieces.insert(pieces.begin()+draggedPiece, new knight(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 3){
                    pieces.insert(pieces.begin()+draggedPiece, new bishop(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
            }
            else if(pieces[draggedPiece]->y == 7*gridSize){
                if(py == 4){
                    pieces.insert(pieces.begin()+draggedPiece, new queen(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 5){
                    pieces.insert(pieces.begin()+draggedPiece, new rook(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 6){
                    pieces.insert(pieces.begin()+draggedPiece, new knight(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
                else if(py == 7){
                    pieces.insert(pieces.begin()+draggedPiece, new bishop(pieces[draggedPiece]->x, pieces[draggedPiece]->y, pieces[draggedPiece]->color, gridSize, gmwin->renderer));
                    delete pieces[draggedPiece+1];
                    pieces[draggedPiece+1] = nullptr;
                    pieces.erase(pieces.begin()+draggedPiece+1);
                    pro = false;
                    Cturn();
                }
            }
        }
    }
    else if(!dragging){
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->x/gridSize == px && pieces[i]->y/gridSize == py && pieces[i]->color == turn){
                dragging = true;
                draggedPiece = i;
            }
        }
    }
}

void board :: LeftRelease(){
    if(dragging){
        int prevx = pieces[draggedPiece]->x;
        int prevy = pieces[draggedPiece]->y;
        pieces[draggedPiece]->x = px*gridSize;
        pieces[draggedPiece]->y = py*gridSize;
        if(dragging){ //checks if moving piece is check
            int pignore = -1;
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->x/gridSize == px && pieces[i]->y/gridSize == py && pieces[i]->color != turn){
                    pignore = i;
                    i = pieces.size();
                }
            }
            if(CheckCheck(pignore)){
                if(debug)
                    cout << "moving puts in check" << endl;
                pieces[draggedPiece]->x = prevx;
                pieces[draggedPiece]->y = prevy;
                pieces[draggedPiece]->dx = pieces[draggedPiece]->x;
                pieces[draggedPiece]->dy = pieces[draggedPiece]->y;
                dragging = false;
                DrawGrid();
                RenderPieces(true);
            }
        }
        if(dragging){
            pieces[draggedPiece]->x = prevx;
            pieces[draggedPiece]->y = prevy;
        }
        if(dragging && pieces[draggedPiece]->Check(px*gridSize, py*gridSize, true, pieces, draggedPiece, checked, turn, checkingPiece)){ //checks if valid move
            if(debug)
                cout << "valid move" << endl;
            pieces[draggedPiece]->x = px*gridSize;
            pieces[draggedPiece]->y = py*gridSize;
            pieces[draggedPiece]->dx = px*gridSize;
            pieces[draggedPiece]->dy = py*gridSize;
            dragging = false;
            DrawGrid();
            RenderPieces(true);
            if(pieces[draggedPiece]->imgsrc.find("pawn") != std::string::npos && (pieces[draggedPiece]->y == 0 || pieces[draggedPiece]->y == 7*gridSize))
                Promote();
            else{
                Cturn();
            }
        }
        else if(dragging){ //invalid move
            if(debug)
                cout << "invalid move" << endl;
            pieces[draggedPiece]->dx = pieces[draggedPiece]->x;
            pieces[draggedPiece]->dy = pieces[draggedPiece]->y;
            dragging = false;
            DrawGrid();
            RenderPieces(true);
        }
        draggedPiece = -1;
    }
}

void board :: Promote(){
    pro = true;
    if(pieces[draggedPiece]->y == 0){
        gmwin->pos.x = pieces[draggedPiece]->x;
        gmwin->pos.y = pieces[draggedPiece]->y;
        gmwin->pos.w = gridSize;
        gmwin->pos.h = gridSize*4;
        SDL_SetRenderDrawColor(gmwin->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gmwin->renderer, &gmwin->pos);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/wqueen.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/wrook.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y+gridSize, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/wknight.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y+gridSize*2, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/wbishop.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y+gridSize*3, gridSize, gridSize);
    }
    else{
        gmwin->pos.x = pieces[draggedPiece]->x;
        gmwin->pos.y = pieces[draggedPiece]->y-gridSize*3;
        gmwin->pos.w = gridSize;
        gmwin->pos.h = gridSize*4;
        SDL_SetRenderDrawColor(gmwin->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gmwin->renderer, &gmwin->pos);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/bqueen.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y-gridSize*3, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/brook.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y-gridSize*2, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/bknight.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y-gridSize, gridSize, gridSize);
        gmwin->RenderImage(gmwin->CreateTexture("../Chess/bbishop.png"), pieces[draggedPiece]->x, pieces[draggedPiece]->y, gridSize, gridSize);
    }
}

void board :: RenderPieces(bool draw){
    for(int i = 0; i < pieces.size(); i++){
        if(i != draggedPiece){
            if(dragging){
                if(abs(pieces[i]->x/gridSize - (pieces[draggedPiece]->dx+gridSize/2)/gridSize) <= 1 && abs(pieces[i]->y/gridSize - (pieces[draggedPiece]->dy+gridSize/2)/gridSize) <= 1){
                    gmwin->RenderImage(pieces[i]->img, pieces[i]->dx, pieces[i]->dy, pieces[i]->gridSize, pieces[i]->gridSize);
                }
            }
            else{
                gmwin->RenderImage(pieces[i]->img, pieces[i]->dx, pieces[i]->dy, pieces[i]->gridSize, pieces[i]->gridSize);
            }
        }
    }
    if(draw && draggedPiece != -1)
        gmwin->RenderImage(pieces[draggedPiece]->img, pieces[draggedPiece]->dx, pieces[draggedPiece]->dy, pieces[draggedPiece]->gridSize, pieces[draggedPiece]->gridSize);
}

bool board :: CheckCheck(int ignore){
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

void board :: Cturn(){
    if(turn == 0)
        turn = 1;
    else if(turn == 1)
        turn = 0;
    checked = CheckCheck(-1);
    if(checked){
        int king;
        for(int i = 0; i < pieces.size(); i++){
            if(pieces[i]->imgsrc.find("king") != std::string::npos && pieces[i]->color == turn){
                king = i;
                i = pieces.size();
            }
        }
        bool kingEscapes = false;
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                int nx = pieces[king]->x/gridSize+i;
                int ny = pieces[king]->y/gridSize+j;
                if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && !(i == 0 && j == 0)){
                    if(pieces[king]->Check(nx*gridSize, ny*gridSize, false, pieces, draggedPiece, checked, turn, checkingPiece)){ //checks if valid move
                        int prevx = pieces[king]->x;
                        int prevy = pieces[king]->y;
                        pieces[king]->x = nx*gridSize;
                        pieces[king]->y = ny*gridSize;
                        int pignore = -1;   //checks if moving piece is check
                        for(int k = 0; k < pieces.size(); k++){
                            if(pieces[k]->x/gridSize == nx && pieces[k]->y/gridSize == ny && pieces[k]->color != turn){
                                pignore = k;
                                k = pieces.size();
                            }
                        }
                        if(!CheckCheck(pignore)){ //king can escape check
                            cout << "king escapes to " << nx << "\t" << ny << endl;
                            kingEscapes = true;
                        }
                        pieces[king]->x = prevx;
                        pieces[king]->y = prevy;
                    }
                }
                if(kingEscapes){
                    i = 2;
                    j = 2;
                    break;
                }
            }
        }
        if(!kingEscapes){ //rip you have to check capturing and blocking checker
            cout << "king is trapped" << endl;
            vector<int> checking;
            for(int i = 0; i < pieces.size(); i++){
                if(pieces[i]->color != turn){
                    if(pieces[i]->Checking(-1, pieces, draggedPiece)){
                        checking.push_back(i);
                    }
                }
            }
            if(checking.size() > 1){ //if king cant escape and more than 1 piece is checking it's checkmate
                cout << "Checkmate!" << endl;
            }
            else if(pieces[checking[0]]->imgsrc.find("pawn") != std::string::npos || pieces[checking[0]]->imgsrc.find("knight") != std::string::npos){ //if checking piece is a pawn or knight just need to check if you can legally capture the pawn 
                bool checkmate = true;
                for(int j = 0; j < pieces.size(); j++){
                    if(pieces[j]->imgsrc.find("king") == std::string::npos && pieces[j]->color == turn){
                        if(pieces[j]->Check(pieces[checking[0]]->x, pieces[checking[0]]->y, false, pieces, draggedPiece, checked, turn, checkingPiece)){ //checks if valid move
                            int prevx = pieces[j]->x;
                            int prevy = pieces[j]->y;
                            pieces[j]->x = pieces[checking[0]]->x;
                            pieces[j]->y = pieces[checking[0]]->y;
                            int pignore = checking[0];   //checks if moving piece is check
                            if(!CheckCheck(pignore)){ //king can escape check
                                checkmate = false;
                                cout << "not Checkmate! " << j << " can capture checker" << endl;
                            }
                            pieces[j]->x = prevx;
                            pieces[j]->y = prevy;
                        }
                    }
                    if(checkmate == false)
                        j = pieces.size();
                }
                if(checkmate)
                    cout << "Checkmate!" << endl;
            }
            else{
                bool checkmate = true;
                int offx = pieces[king]->x/gridSize-pieces[checking[0]]->x/gridSize;
                int offy = pieces[king]->y/gridSize-pieces[checking[0]]->y/gridSize;
                if(offx > 0)
                    offx = 1*gridSize;
                else if(offx < 0)
                    offx = -1*gridSize;
                if(offy > 0)
                    offy = 1*gridSize;
                else if(offy < 0)
                    offy = -1*gridSize;
                for(int j = 0; j < pieces.size(); j++){
                    if(pieces[j]->imgsrc.find("king") == std::string::npos && pieces[j]->color == turn){
                        int ax = pieces[checking[0]]->x;
                        int ay = pieces[checking[0]]->y;
                        while(ax != pieces[king]->x || ay != pieces[king]->y){
                            if(pieces[j]->Check(ax, ay, false, pieces, draggedPiece, checked, turn, checkingPiece)){ //checks if valid move
                                int prevx = pieces[j]->x;
                                int prevy = pieces[j]->y;
                                pieces[j]->x = ax;
                                pieces[j]->y = ay;
                                int pignore = checking[0];   //checks if moving piece is check
                                if(!CheckCheck(pignore)){ //king can escape check
                                    checkmate = false;
                                    cout << "not Checkmate! " << j << " can capture or checker" << endl;
                                }
                                pieces[j]->x = prevx;
                                pieces[j]->y = prevy;
                            }
                            if(checkmate == false){
                                ax = pieces[king]->x;
                                ay = pieces[king]->y;
                                j = pieces.size();
                            }
                            else{
                                ax += offx;
                                ay += offy;
                            }
                        } 
                    }
                }
                if(checkmate)
                    cout << "Checkmate!" << endl;
            }
        }
    }
}

void board :: SetBoard(){
    pieces.push_back(new rook(0*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new knight(1*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new bishop(2*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new queen(3*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new king(4*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new bishop(5*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new knight(6*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));
    pieces.push_back(new rook(7*gridSize, 7*gridSize, 0, gridSize, gmwin->renderer));

    for(int i = 0; i < 8; i++){
        pieces.push_back(new pawn(i*gridSize, 6*gridSize, 0, gridSize, gmwin->renderer));
    }

    pieces.push_back(new rook(0*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new knight(1*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new bishop(2*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new queen(3*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new king(4*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new bishop(5*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new knight(6*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));
    pieces.push_back(new rook(7*gridSize, 0*gridSize, 1, gridSize, gmwin->renderer));

    for(int i = 0; i < 8; i++){
        pieces.push_back(new pawn(i*gridSize, 1*gridSize, 1, gridSize, gmwin->renderer));
    }
}