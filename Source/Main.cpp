#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Random.h"

#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene;
	scene.SetSky({ 0.0f, 0.5f, 1.0f }, { 1.0f, 1.0f, 1.0f });
	auto sphere = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, color3_t{ 1, 0, 0 });
	scene.AddObject(std::move(sphere));

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}	

		while (scene.objects.size() < 10) {
			for (int i = 0; i < 1; i++) {
				glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });
				auto sphere = std::make_unique<Sphere>(position, 1.0f, color3_t{ 1, 0, 0 });
				scene.AddObject(std::move(sphere));
			}
		}

		framebuffer.Clear({ 0, 0, 0, 255 });
		scene.Render(framebuffer, camera);
		framebuffer.Update();
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}