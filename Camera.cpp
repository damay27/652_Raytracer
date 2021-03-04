#include "Camera.h"
#include "Vec3D.h"
#include "Sphere.h"

#include <math.h>

bool Camera::raycast_sphere(struct Sphere sphere, struct Vec3D ray_start, struct Vec3D ray_direction, struct Vec3D* hit_point) {
    float a = sqrt(ray_direction.x - ray_start.x) + sqrt(ray_direction.y - ray_start.y) + sqrt(ray_direction.z - ray_start.z);
    
    float b = (ray_direction.x - ray_start.x) * (ray_start.x - sphere.position.x);
    b += (ray_direction.y - ray_start.y) * (ray_start.y - sphere.position.y);
    b += (ray_direction.z - ray_start.z) * (ray_start.z - sphere.position.z);
    b *= 2;
    
    float c = sphere.position.x * sphere.position.x + sphere.position.y * sphere.position.y + sphere.position.z * sphere.position.z;
    c += ray_start.x * ray_start.x + ray_start.y * ray_start.y + ray_start.z * ray_start.z;
    c -= 2 * (sphere.position.x * ray_start.x + sphere.position.y * ray_start.y + sphere.position.z * ray_start.z);
    c -= sphere.radius * sphere.radius;

    float x = b*b - 4*a*c;
    float u;

    //Ray does not hit
    if(x < 0) {
        return false;
    }
    //Ray is tangent
    else if(abs(x) < .0000001) {
        u = ( -b + sqrt(b*b - 4 * a * c) ) / (2 * a);
        struct Vec3D point;
        point.x = u * ray_direction.x + ray_start.x;
        point.y = u * ray_direction.y + ray_start.y;
        point.z = u * ray_direction.z + ray_start.z;

        *hit_point = point;
        return true;
    }
    //Ray hits the sphere in two places
    else {
        u = ( -b + sqrt(b*b - 4 * a * c) ) / (2 * a);
        struct Vec3D point_1;
        point_1.x = u * ray_direction.x + ray_start.x;
        point_1.y = u * ray_direction.y + ray_start.y;
        point_1.z = u * ray_direction.z + ray_start.z;

        u = ( -b - sqrt(b*b - 4 * a * c) ) / (2 * a);
        struct Vec3D point_2;
        point_2.x = u * ray_direction.x + ray_start.x;
        point_2.y = u * ray_direction.y + ray_start.y;
        point_2.z = u * ray_direction.z + ray_start.z;

        float dist_1 = this->get_dist(ray_start, point_1);
        float dist_2 = this->get_dist(ray_start, point_2);

        if(dist_1 < dist_2) {
            *hit_point = point_1;
        }
        else {
            *hit_point = point_2;
        }

        return true;

    }
}

float Camera::get_dist(struct Vec3D point_1, struct Vec3D point_2) {
    float x = point_1.x - point_2.x;
    float y = point_1.y - point_2.y;
    float z = point_1.z - point_2.z;

    return sqrt(x*x + y*y + z*z);
}