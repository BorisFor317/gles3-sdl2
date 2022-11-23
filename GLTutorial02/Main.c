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
  // Generate buffer object names
  glGenBuffers(nBuffers, &vbo);
  // Bind a named buffer object
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // Creates and initializes a buffer object's data store
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

const GLuint TRIANGLE_VERTICES = 3;
typedef struct Triangle_s {
  Vertex vertices[TRIANGLE_VERTICES];
} Triangle;

GLuint createVBO(const Triangle* triangle) {
  return vboCreate(triangle->vertices, TRIANGLE_VERTICES);
}

GLboolean drawTriangle(const Triangle* triangle) {
  GLuint vbo = createVBO(triangle);
  if (!vbo) {
    return GL_FALSE;
  }
  // Set up for rendering the triangle (activate the VBO)
  GLuint positionIdx = 0;
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // Define an array of generic vertex attribute data
  glVertexAttribPointer(positionIdx, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (const GLvoid *)0);
  // Enable or disable a generic vertex attribute array
  glEnableVertexAttribArray(positionIdx);
  // Draw
  glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_VERTICES);

  return GL_TRUE;
};

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
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // red
  // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  // green
  // glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  // yellow
  // glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(window);

  GLuint shaderProg = shaderProgLoad("Gradient2D.vert", "Simple2D.frag");
  if (!shaderProg) {
    return EXIT_FAILURE;
  }

  // installs a current program as a part of current rendering state
  glUseProgram(shaderProg);

  // Create the triangle
  // const Triangle triangleBottom = {{{0.0f, -0.9f}, {0.9f, -0.1f}, {-0.9f, -0.1f}}};
  // drawTriangle(&triangleBottom);
  // const Triangle triangleTop = {{{0.9f, 0.1f},  {-0.9f, 0.1f}, {0.0f, 0.9f}}};
  // drawTriangle(&triangleTop);

  // GLuint triangleBottomVBO = createVBO(&triangleBottom);

  // Draw multiple triangles in one draw call
  // const Vertex vertices[] = {{0.0f, -0.9f}, {0.9f, -0.1f}, {-0.9f, -0.1f},
  //                            {0.9f, 0.1f},  {-0.9f, 0.1f}, {0.0f, 0.9f}};
  // GLuint numberOfVertices = sizeof(vertices) / sizeof(Vertex);
  // GLuint vbo = vboCreate(vertices, numberOfVertices);
  // if (vbo == 0) {
  //   return EXIT_FAILURE;
  // }

  // // Set up for rendering the triangle (activate the VBO)
  // GLuint positionIdx = 0;
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // // Define an array of generic vertex attribute data
  // glVertexAttribPointer(positionIdx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
  //                       (const GLvoid *)0);
  // // Enable or disable a generic vertex attribute array
  // glEnableVertexAttribArray(positionIdx);
  // // Draw
  // glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);

  const Triangle triangle = {{{0.0f, 1.0f}, {1.0f, -1.0f}, {-1.0f, -1.0f}}};
  drawTriangle(&triangle);

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
