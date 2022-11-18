#include <GLES3/gl3.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#include <stdio.h>
#include <stdlib.h>

// const unsigned int DISP_WIDTH = 640;
// const unsigned int DISP_HEIGHT = 480;
const unsigned int DISP_WIDTH = 800;
const unsigned int DISP_HEIGHT = 600;

int main(int argc, char *argv[]) {
  // The window
  SDL_Window *window = NULL;

  // The opengl context
  SDL_GLContext context = NULL;

  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL couldn't initialize! SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  atexit(SDL_Quit);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window = SDL_CreateWindow("GLES3 + SDL2 tutorial 01", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, DISP_WIDTH, DISP_HEIGHT,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Couldn't create the main window", NULL);
    return EXIT_FAILURE;
  }

  context = SDL_GL_CreateContext(window);
  if (!context) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Couldn't create an OpenGL context", NULL);
    return EXIT_FAILURE;
  }

  // black
  // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // red
  // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  // green
  // glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  // yellow
  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(window);

  int quit = 0;
  while (!quit) {
    SDL_Event event;
    if (SDL_WaitEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }
  }

  printf("return 0\n");
  return 0;
}
