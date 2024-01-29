#ifndef prism_h
#define prism_h
#include "coordinate.h"
using namespace std;

class Prism{
private:
    Coordinate center;
    Coordinate* vertices;
    int coefficient(int i, int digit) {
        int binaryDigit = (i >> digit) & 1;
        if (!binaryDigit) return 1;
        else return -1;
    }
public:
    Prism(float xLength, float yLength, float zLength, Coordinate center={0,0,0}) {
        this->center = center;
        this->vertices = new Coordinate[8];
        for (int i=0; i<8; i++) {
            vertices[i].x = center.x + coefficient(i,0)*xLength/2;
            vertices[i].y = center.y + coefficient(i,1)*yLength/2;
            vertices[i].z = center.z + coefficient(i,2)*zLength/2;
        }
    }
    ~Prism(){
        delete [] vertices;
    }
    void setCenter(float x, float y, float z) {
        center = {x,y,z};
    }
    Coordinate getCenter() const {
        return center;
    }
    Coordinate* getVertices() const {
        return vertices;
    }
    void printVertices() {
        cout << "List of VERTICES in 3D cartesian coordinate system:" << endl;
        for (int i=0; i<8; i++) {
            cout << "Vertex " << (i+1) << ": (" << vertices[i].x << "," << vertices[i].y << "," << vertices[i].z << ")" << endl;
        }
    }
};

#endif