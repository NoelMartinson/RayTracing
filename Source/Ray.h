#pragma once
#include "Color.h"
#include <glm/vec3.hpp>

using glm::vec3;

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    Ray() = default;
    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin(origin), direction(direction) {
    }

    glm::vec3 at(float t) const { return origin + t * direction; }

    // If you want to keep operator*
    glm::vec3 operator*(float t) const { return at(t); }
};

struct raycastHit_t
{
    glm::vec3 point;    // point of ray hit
    glm::vec3 normal;   // normal of surface hit
    float distance = 0; // distance from ray origin to hit

    color3_t color;     // hit object material color
};
