#ifndef coordinate_h
#define coordinate_h
#include <iostream>
using namespace std;

class Coordinate
{
public:
    float x;
    float y;
    float z;

    Coordinate(float x=0, float y=0, float z=0) : x(x), y(y), z(z){}
};

#endif