#include "Shader.h"
#include <GLES3/gl3.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#include <stdio.h>
#include <stdlib.h>

// const unsigned int DISP_WIDTH = 640;
// const unsigned int DISP_HEIGHT = 480;
const unsigned int DISP_WIDTH = 800;
const unsigned int DISP_HEIGHT = 600;

typedef struct Vertex_s {
  float position[2];
} Vertex;

GLuint vboCreate(const Vertex *vertices, GLuint numVertices) {
  GLuint vbo;
  int nBuffers = 1;
  glGenBuffers(nBuffers, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vertices,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    // Failed
    glDeleteBuffers(nBuffers, &vbo);
    SDL_Log("Creating vbo failed, code %u\n", err);
    vbo = 0;
  }

  return vbo;
}

/**
 * @brief Frees the vbo
 *
 * @param vbo the VBO's name
 */
void vboFree(GLuint vbo) { glDeleteBuffers(1, &vbo); }

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
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  // green
  // glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  // yellow
  // glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(window);

  GLuint shaderProg = shaderProgLoad("Simple2D.vert", "Simple2D.frag");
  if (!shaderProg) {
    return EXIT_FAILURE;
  }

  glUseProgram(shaderProg);

  // Create the triangle
  const Vertex vertices[] = {{0.0f, -0.9f}, {0.9f, 0.9f}, {-0.9f, 0.9f}};
  GLsizei numVertices = sizeof(vertices) / sizeof(Vertex);
  GLuint triangleVBO = vboCreate(vertices, numVertices);
  printf("OK %d", triangleVBO);
  if (triangleVBO == 0) {
    return EXIT_FAILURE;
  }

  // Set up for rendering the triangle (activate the VBO)

  GLuint positionIdx = 0;
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glVertexAttribPointer(positionIdx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (const GLvoid *)0);
                      
  glEnableVertexAttribArray(positionIdx);

  // Draw
  glDrawArrays(GL_TRIANGLES, 0, numVertices);

  // Update the window
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
