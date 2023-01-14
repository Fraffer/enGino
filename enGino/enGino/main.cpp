#include <iostream>
#include <chrono>
#include <conio.h>
#include "vector3.h"
#include "shape.h"
#include "camera.h"
#include "quaternion.h"
#include "transform.h"
#include "scene.h"


using namespace enGino;

int main() {
    Scene s;
    s.populate(20);
    float time = .0f;
    char input = '.';

    Sphere* focus = nullptr;

    rayCasting(s.toWorld(), s.camera);

    while (true)
    {
         input = _getch();

        switch (input)
        {       
        case 'q':
            rayCasting(s.toWorld(), s.camera);
            break;
        case 'w':
            if (focus != nullptr) { focus->move(focus->transform.forwardVector(), 1.f); rayCasting(s.toView(focus->transform), s.camera); }
            break;
        case 'a':
            if (focus != nullptr) { focus->rotate(focus->transform.upVector(), -1.f); rayCasting(s.toView(focus->transform), s.camera); }
            break;
        case 's':
            if (focus != nullptr) { focus->move(focus->transform.forwardVector() * -1, 1.f); rayCasting(s.toView(focus->transform), s.camera); }
            break;
        case 'd':
            if (focus != nullptr) { focus->rotate(focus->transform.upVector() * 1, 1.f); rayCasting(s.toView(focus->transform), s.camera); }
            break;
        case '0':
            focus = &s.sceneElements[0];
            rayCasting(s.switchView(0), s.camera);
            break;
        case '1':
            focus = &s.sceneElements[1];
            rayCasting(s.switchView(1), s.camera);
            break;
        case '2':
            focus = &s.sceneElements[2];
            rayCasting(s.switchView(2), s.camera);
            break;
        case '3':
            focus = &s.sceneElements[3];
            rayCasting(s.switchView(3), s.camera);
            break;
        case '4':
            focus = &s.sceneElements[4];
            rayCasting(s.switchView(4), s.camera);
            break;
        case '5':
            focus = &s.sceneElements[5];
            rayCasting(s.switchView(5), s.camera);
            break;
        case '6':
            focus = &s.sceneElements[6];
            rayCasting(s.switchView(6), s.camera);
            break;
        case '7':
            focus = &s.sceneElements[7];
            rayCasting(s.switchView(7), s.camera);
            break;
        case '8':
            focus = &s.sceneElements[8];
            rayCasting(s.switchView(8), s.camera);
            break;
        case '9':
            focus = &s.sceneElements[9];
            rayCasting(s.switchView(9), s.camera);
            break;
        }
    }
}
