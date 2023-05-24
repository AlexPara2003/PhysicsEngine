#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO); // initialize SDL

    // create a window
    SDL_Window* window = SDL_CreateWindow(
        "My SDL Window", // window title
        SDL_WINDOWPOS_CENTERED, // initial x position
        SDL_WINDOWPOS_CENTERED, // initial y position
        640, // width, in pixels
        480, // height, in pixels
        SDL_WINDOW_SHOWN // flags
    );

    // wait for user to close window
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // clean up and exit
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
