#pragma once
#ifndef PIECE_H
#define PIECE_H
#include "common.h"
#include "cmath"
#include "string"

class piece{
    public:
        int dx;
        int dy;
        int x;
        int y;
        int color = 0; //0 is white
        bool twopush = false;
        int gridSize;
        string imgsrc;

        SDL_Texture *img = nullptr;
        
        piece();
        piece(int x, int y, int color, string src, int gridSize, SDL_Renderer *renderers);
        ~piece();
        virtual bool Check(int indexx, int indexy, bool capture, vector<piece*> &pieces, int &draggedPiece, bool checked, int turn, int &checkingPiece);
        virtual bool Checking(int ignore, vector<piece*> &pieces, int draggedPiece);
        virtual bool Attacking(int ix, int iy, vector<piece*> &pieces, int draggedPiece);
        void Promote();
    private:

};
#endif