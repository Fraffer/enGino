#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "transform.h"
#include "camera.h"
#include "shape.h"
#include "sphere.h"

namespace enGino
{
    class Scene {
    public:        
        Scene() : camera(Camera(2.0, 38, 38)) {}
        Scene(Camera& _c) : camera(_c) {}

        // fill the obj vector with GameObject randomly translated into the scene, but on the same height (y)
        void populate(int n) {
            for (int i = 0; i < n; i++) {
                Transform transform;
                transform.translate = Vector3::random(14) + Vector3(0, 0, 15);
                Sphere newShape(1, transform);               
                newShape.transform.translate.y = 0;
                sceneElements.push_back(newShape);
            }
        }

        // produces a vector of spheres in world space
        std::vector<Sphere> toWorld() const {
            std::vector<Sphere> res;
            res.clear();

            for (const Sphere& s : sceneElements) {
                res.push_back(apply(s.transform, s));
            }
            return res;
        }

        std::vector<Sphere> toView(Transform cameraTransform) const
        {
            std::vector<Sphere> res;
            res.clear();

            cameraTransform.invert();

            for (const Sphere& s : sceneElements) {
                res.push_back(apply(cameraTransform, s));
            }
            return res;
        }

        std::vector<Sphere> switchView(int index)
        {
            const Transform& t = sceneElements[index].transform;
            return toView(t);
        }

        Camera camera;
        std::vector<Sphere> sceneElements; // a set with GameObj (each with its own transform)
    };

    // ascii art: convert an intensity value (0 to 1) into a sequence of two chars
    const char* intensityToCstr(Scalar intensity) {
        switch (int(round(intensity * 8))) {
        case 0: return "  "; // darkest
        case 1: return " '";
        case 2: return " +";
        case 3: return " *";
        case 4: return " #";
        case 5: return "'#";
        case 6: return "+#";
        case 7: return "*#";
        case 8: return "##"; // lightest
        default:
        case 10: return "##";
        }
    }

    const char* lighting(Versor3 normal) {
        Versor3 lightDir = Versor3(1, 2, -2).normalized();
        // lambertian
        Scalar diffuse = dot(normal, lightDir);
        if (diffuse < 0) diffuse = 0;

        return intensityToCstr(diffuse);
    }

    void rayCasting(const std::vector<Sphere>& vec, Camera& camera) {
        std::string screenBuffer; // a string to get ready and print all at once

        for (int y = 0; y < camera.pixelDimY; y++) {
            for (int x = 0; x < camera.pixelDimX; x++) {
                Point3 hitPos;
                Point3 hitNorm;
                Scalar distMax = 1000.0;

                for (const Sphere& s : vec) {
                    rayCast(camera.primaryRay(x, y), s, hitPos, hitNorm, distMax);
                }

                screenBuffer += lighting(hitNorm);
            }
            screenBuffer += "\n";
        }
        std::cout << screenBuffer;
    }
} // end of namespace mgd