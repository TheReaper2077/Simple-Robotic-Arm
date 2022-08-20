#include <iostream>
#include <LucyRE/LucyRE.h>
#include <Lucy/Lucy.h>
#include <SDL2/SDL.h>
#include "Application.h"

int main(int argcount, char** args) {
	lucy::Engine engine;

	engine.AddInitializationSystem(InitApplication);
	engine.AddRuntimeSystem(UpdateApplication);
	engine.AddImGuiSystem(ImGuiApplication);

	engine.Init();
	engine.Mainloop();

	return 0;
}
