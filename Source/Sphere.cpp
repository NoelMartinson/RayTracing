#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
    // vector from sphere center to ray origin
    glm::vec3 oc = ray.origin - position;

    // quadratic coefficients for ray-sphere intersection
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - (radius * radius);

    // discriminant tells us if we have intersections
    float discriminant = (b * b) - (4.0f * a * c);

    if (discriminant >= 0.0f) {

        float sqrtDisc = sqrt(discriminant);

        // first (closest) root
        float t = (-b - sqrtDisc) / (2.0f * a);

        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;
            raycastHit.point = ray.origin + t * ray.direction;
            raycastHit.normal = (raycastHit.point - position) / radius;
            raycastHit.color = color;
            return true;
        }

        // second (farther) root
        t = (-b + sqrtDisc) / (2.0f * a);

        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;
            raycastHit.point = ray.origin + t * ray.direction;
            raycastHit.normal = (raycastHit.point - position) / radius;
            raycastHit.color = color;
            return true;
        }
    }

    return false;
}
