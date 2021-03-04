#include <stdio.h>

#include "Camera.h"
#include "Vec3D.h"
#include "Sphere.h"

int main() {
    Camera cam;

    struct Vec3D p1 = {1, 0, 0};
    struct Vec3D p2 = {0, 0, 0};

    printf("%f\n", cam.get_dist(p1, p2));

    struct Vec3D center = {2, 0, 1};
    struct Vec3D hit_point;
    struct Sphere sphere;
    sphere.position = center;
    sphere.radius = 1.0f;

    bool status = cam.raycast_sphere(sphere, p2, p1, &hit_point);

    printf("%d\n", status);
    printf("%f, %f, %f\n", hit_point.x, hit_point.y, hit_point.z);
}