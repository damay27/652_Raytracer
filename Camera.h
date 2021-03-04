#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3D.h"
#include "Color.h"
#include "Sphere.h"

class Camera {

    private:
        struct Vec3D position;
        struct Vec3D rotation;
        unsigned int hRes, wRes;

    public:
        struct Color* render(struct Sphere* sphere_list, int sphere_count);
                        //    (struct Sphere sphere, struct Vec3 ray_start, struct Vec3 ray_direction, struct Vec3D* hit_point)
        bool raycast_sphere(struct Sphere sphere, struct Vec3D ray_start, struct Vec3D ray_direction, struct Vec3D *hit_point);
        float get_dist(struct Vec3D point_1, struct Vec3D point_2);
};

#endif