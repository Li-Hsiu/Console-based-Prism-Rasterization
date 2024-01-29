#ifndef rendering_h
#define rendering_h
#include "coordinate.h"
#include "prism.h"
using namespace std;

class Rendering
{
private:
    bool isAcute(const Coordinate& a, const Coordinate& b){
        if (a.x*b.x + a.y*b.y + a.z*b.z > 0) return true;
        else return false; 
    }
public:
    Coordinate* points;
    bool valid;
    Rendering(const Coordinate& camera, const Prism& target) {
        this->points = new Coordinate[8];
        this->valid = true;
        Coordinate cameraVector = {target.getCenter().x-camera.x, target.getCenter().y-camera.y, target.getCenter().z-camera.z};
        for (int i=0; i<8; i++) {
            Coordinate relative = {target.getVertices()[i].x-camera.x, target.getVertices()[i].y-camera.y, target.getVertices()[i].z-camera.z};
            if (!isAcute(cameraVector, relative)) valid = false;
            points[i] = {relative.x/relative.z, relative.y/relative.z, 0};
        }
    }
    ~Rendering(){
        delete [] points;
    }
    void printPoints() {
        cout << "List of POINTS in 2D cartesian coordinate system:" << endl;
        for (int i=0; i<8; i++) {
            cout << "Vertex " << (i+1) << ": (" << points[i].x << "," << points[i].y << ")" << endl;
        }
    }
};

#endif