#include <time.h>

#include "App.h"
#include "Engine.h"

int main(int argc, char *argv[]) {
	srand(time(NULL));
	Engine::Get().Load();
	App app(800, 600, true);
	app.Run();
	return 0;
}