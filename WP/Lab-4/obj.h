#ifndef _Objects.h_
#define _Objects.h_

#include <iostream>
#include <windows.h>
#include <cmath>
#define ID_TIMER 333

using namespace std;

class Objects
{

protected:
    COLORREF clr;
public:
    POINT center;
    int xSpeed,ySpeed;
    int counter=0;

    Objects(POINT center,const int &speed);
    bool Accelerate(const int& deltaSpeedX, const int& deltaSpeedY);
    bool Color(const COLORREF &clr);
    bool Collision(const RECT &rect);
    bool Shape(Objects &ob);
    virtual bool Move(const HDC &hdc, const RECT& rect,HBRUSH &hBrush) = 0;
};

class Circle : public Objects {
public:
    Circle(POINT center,const int &speed): Objects(center,speed)
    {

    }
    bool Move(const HDC &hdc,const RECT& rect,HBRUSH &hBrush);
};

bool Interaction(Objects &alfa,Objects &beta);
#endif
