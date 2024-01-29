#ifndef rasterization_h
#define rasterization_h
#include "coordinate.h"
#include "rendering.h"
#include "cmath"
using namespace std;

class Rasterization
{
private:
    float scaleFactor;
    Coordinate* pixels;
    bool** screen;
    int xRange;
    int yRange;
    Coordinate* rescale(const Rendering& img){
        Coordinate* local = new Coordinate[8];
        for (int i=0; i<8; i++) {
            local[i] = {img.points[i].x*scaleFactor, img.points[i].y*scaleFactor, 0};
        }
        return local;
    }
    bool outOfScreen(int x, int y) {
        if (x+round(xRange/2.0)>xRange-1 || x+round(xRange/2.0)<0 || yRange-y-round(yRange/2.0)>yRange-1 || yRange-y-round(yRange/2.0)<0) return true;
        return false;
    }
    void drawLine(const Coordinate& a, const Coordinate& b) {
        if (a.x == b.x) { // vertical line
            Coordinate up, down;
            if (a.y<b.y) { down = a; up = b; }
            else { down = b; up = a; }
            for (int y = round(down.y); y <= round(up.y); y++){
                if (outOfScreen(a.x,y)) continue;
                screen[yRange-static_cast<int>(y+round(yRange/2.0))][static_cast<int>(round(a.x)+round(xRange/2.0))] = true;
            }
            return;
        }
        Coordinate left, right;
        if (a.x<b.x) { left = a; right = b; }
        else { left = b; right = a; }
        float slope = (right.y-left.y)/(right.x-left.x);
        if ((right.y-left.y)>=0) { // upward sloping
            if (slope<=1) { // gradual sloping
                float y = left.y;
                for (int x = round(left.x); x <= round(right.x); x++) {
                    y += slope;
                    if (outOfScreen(x,round(y))) continue;
                    screen[yRange-static_cast<int>(round(y)+round(yRange/2.0))][static_cast<int>(x+round(xRange/2.0))] = true;
                }
            }
            else { // steep sloping
                float slopeSteep = (right.x-left.x)/(right.y-left.y);
                float x = left.x;
                for (int y = round(left.y); y <= round(right.y); y++) {
                    x += slopeSteep;
                    if (outOfScreen(round(x),y)) continue;
                    screen[yRange-static_cast<int>(y+round(yRange/2.0))][static_cast<int>(round(x)+round(xRange/2.0))] = true;
                }
            }
        }
        else { // downward sloping
            if (slope>=-1) { // gradual sloping
                float y = left.y;
                for (int x = round(left.x); x <= round(right.x); x++) {
                    y += slope;
                    if (outOfScreen(x,round(y))) continue;
                    screen[yRange-static_cast<int>(round(y)+round(yRange/2.0))][static_cast<int>(x+round(xRange/2.0))] = true;
                }
            }
            else { // steep sloping
                float slopeSteep = (right.x-left.x)/(right.y-left.y);
                float x = left.x;
                for (int y = round(left.y); y >= round(right.y); y--) {
                    x -= slopeSteep;
                    if (outOfScreen(round(x),y)) continue;
                    screen[yRange-static_cast<int>(y+round(yRange/2.0))][static_cast<int>(round(x)+round(xRange/2.0))] = true;
                }
            }
        }
    }
public:
    Rasterization(const Rendering& image, const int resolutionX, const int resolutionY) {
        this->scaleFactor = 0.5*static_cast<float>(min(resolutionX, resolutionY)) / 2;
        this->pixels = rescale(image);
        this->screen = new bool*[resolutionY];
        this->xRange = resolutionX;
        this->yRange = resolutionY;
        for (int i=0; i<resolutionY; i++) {
            this->screen[i] = new bool[resolutionX];
            for (int j=0; j<resolutionX; j++) this->screen[i][j] = false;
        }
    }
    ~Rasterization(){
        delete [] pixels;
        for (int i=0; i<yRange; i++) {
            delete [] screen[i];
        }
        delete [] screen;
    }
    void printPixels(){
        cout << "List of PIXELS in 2D cartesian coordinate system:" << endl;
        for (int i=0; i<8; i++) {
            cout << "Pixel " << (i+1) << ": (" << pixels[i].x << "," << pixels[i].y << ")" << endl;
        }
    }
    void displayScreen(){
        drawLine(pixels[0], pixels[1]);
        drawLine(pixels[2], pixels[3]);
        drawLine(pixels[4], pixels[5]);
        drawLine(pixels[6], pixels[7]);
        drawLine(pixels[0], pixels[2]);
        drawLine(pixels[1], pixels[3]);
        drawLine(pixels[4], pixels[6]);
        drawLine(pixels[5], pixels[7]);
        drawLine(pixels[0], pixels[4]);
        drawLine(pixels[2], pixels[6]);
        drawLine(pixels[1], pixels[5]);
        drawLine(pixels[3], pixels[7]);
        cout << "Displaying on a screen with resolution " << xRange << "x" << yRange << ":" << endl;
        for (int i=0; i<yRange; i++) {
            for (int j=0; j<xRange; j++) {
                if (screen[i][j]) cout << "O ";
                else cout << ". ";
            }
            cout << endl;
        }
    }
};

#endif