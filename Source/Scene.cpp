#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include <iostream>
void Scene::Render(Framebuffer& framebuffer, const Camera& camera) {
    float maxDistance = 100.0f;

    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {

            glm::vec2 pixel{ x, y };
            glm::vec2 uv = pixel / glm::vec2(framebuffer.width, framebuffer.height);
            uv.y = 1.0f - uv.y;

            Ray ray = camera.GetRay(uv);

            raycastHit_t closestHit;
            float closest = maxDistance;
            bool hitAnything = false;

            for (auto& object : objects) {
                raycastHit_t hit;
                if (object->Hit(ray, 0.001f, closest, hit)) {
                    hitAnything = true;
                    closest = hit.distance;
                    closestHit = hit;
                }
            }

            if (hitAnything) {
                color3_t color = closestHit.normal * 0.5f + 0.5f;
                framebuffer.DrawPoint(x, y, ColorConvert(color));
            }
            else {
                color3_t sky = glm::mix(skyTop, skyBottom, uv.y);
                framebuffer.DrawPoint(x, y, ColorConvert(sky));
            }
        }
    }
}

void Scene::AddObject(std::unique_ptr<Object> object) {
	// add object to objects vector
	objects.push_back(std::move(object));
}
color3_t Scene::Trace(const Ray& ray, float minDistance, float maxDistance,
	raycastHit_t& raycastHit) {
	bool rayHit = false;
	float closestDistance = maxDistance;
	// check if scene objects are hit by the ray
	for (auto& object : objects) {
		// when checking objects don't include objects farther than closest hit
		// (starts at max distance)
		if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit
			// objects closer than closest distance)
			closestDistance = raycastHit.distance; // raycast hit distance
		}
	}
	// check if ray hit object
	if (rayHit) {
		// get material color of hit object
		color3_t color = raycastHit.color;
		return color;
	}
	// draw sky colors based on the ray y position
	glm::vec3 direction = glm::normalize(ray.direction);
	// shift direction y from -1 <-> 1 to 0 <-> 1
	float t = (direction.y + 1) * 0.5f;
	// interpolate between sky bottom (0) to sky top (1)
	color3_t color = glm::mix(skyBottom, skyTop, t);
	return color;
}