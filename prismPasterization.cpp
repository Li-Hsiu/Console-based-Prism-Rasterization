#include "prism.h"
#include "coordinate.h"
#include "rendering.h"
#include "rasterization.h"
using namespace std;

const int RESOLUTION_X = 100; // feel free to change
const int RESOLUTION_Y = 100;

int main(){
    float xlength, ylength, zlength;
    cout << "Enter the length along x-axis: ";
    cin >> xlength;
    cout << "Enter the length along y-axis: ";
    cin >> ylength;
    cout << "Enter the length along z-axis: ";
    cin >> zlength;
    Prism p(xlength, ylength, zlength);
    char isDefault;
    cout << "Use default center? Enter Y/N: ";
    cin >> isDefault;
    if (isDefault == 'N') {
        float xCenter, yCenter, zCenter;
        cout << "Enter the x coordinate for center: ";
        cin >> xCenter;
        cout << "Enter the y coordinate for center: ";
        cin >> yCenter;
        cout << "Enter the z coordinate for center: ";
        cin >> zCenter;
        p.setCenter(xCenter, yCenter, zCenter);
    }
    p.printVertices();
    float xCamera, yCamera, zCamera;
    cout << "Enter the x coordinate for center: ";
    cin >> xCamera;
    cout << "Enter the y coordinate for center: ";
    cin >> yCamera;
    cout << "Enter the z coordinate for center: ";
    cin >> zCamera;
    Rendering r({xCamera,yCamera,zCamera},p);
    if (r.valid == false) {
        cout << "Sorry, the prism you generated is either overlaps with the camera" << endl;
        cout << "or too meaningless to be displayed (i.e does not show on screen)." << endl;
        return 0;
    }
    r.printPoints();
    Rasterization i(r,RESOLUTION_X,RESOLUTION_Y);
    i.printPixels();
    i.displayScreen();
    return 0;
}