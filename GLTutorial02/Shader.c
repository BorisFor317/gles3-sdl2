#include "Shader.h"

#include <SDL.h>
#include <SDL_opengles2.h>
#include <stdio.h>
#include <stdlib.h>

static size_t fileGetLength(FILE *file) {
  size_t length;

  size_t currPos = ftell(file);

  fseek(file, 0, SEEK_END);
  length = ftell(file);

  // return to the original position
  fseek(file, currPos, SEEK_SET);
}

/**
 * @brief Loads and compiles shader from a file
 *
 * @param filename the shader's filename
 * @param shaderType the shader type (e.g., GL_VERTEX_SHADER)
 * @return GLuint the shader's ID, or 0 if failed
 */
static GLuint shaderLoad(const char *filename, GLenum shaderType) {
  GLuint shader;
  {
    GLchar *shaderSrc;
    {
      FILE *file = fopen(filename, "r");
      if (!file) {
        SDL_Log("Can't open filename %s", filename);

        return 0;
      }

      size_t length = fileGetLength(file);

      shaderSrc = (GLchar *)calloc(length + 1, sizeof(GLchar));
      if (!shaderSrc) {
        SDL_Log("Out of memory when trying to read the file %s", filename);
        fclose(file);
        file = NULL;

        return 0;
      }

      fread(shaderSrc, sizeof(GLchar), length, file);
      fclose(file);
    }

    shader = glCreateShader(shaderType);
    glShaderSource(shader, sizeof(GLchar), (const GLchar **)&shaderSrc, NULL);
    free(shaderSrc);
  }

  glCompileShader(shader);
  GLint compileSucceeded = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSucceeded);

  if (!compileSucceeded) {
    // Compilation failed
    SDL_Log("Compilation of shader %s failed\n", filename);
    GLint logLength = 0;
    glGetShaderdiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    GLchar *errLog = (GLchar *)malloc(logLength);
    if (errLog) {
      glGetShaderInfoLog(shader, logLength, &logLength, errLog);
      SDL_Log("%s\n", errLog);
      free(errLog);
    } else {
      SDL_Log("Couldn't get shader log; out of memory\n");
    }

    glDeleteShader(shader);
    shader = 0;
  }

  return shader;
}

/**
 * @brief Destroys the shader
 *
 * @param shaderID shader's ID to destory
 */
static void shaderDestroy(GLuint shaderID) { glDeleteShader(shaderID); }

GLuint shaderProgLoad(const char *vertFilename, const char *fragFilename) {
  GLuint vertShader;
  GLuint fragShader;

  vertShader = shaderLoad(vertFilename, GL_VERTEX_SHADER);
  if (!vertShader) {
    SDL_Log("Couldn't load vertex shader: %s\n", vertFilename);
    return 0;
  }

  fragShader = shaderLoad(vertFilename, GL_FRAGMENT_SHADER);
  if (!fragShader) {
    SDL_Log("Couldn't load fragment shader: %s\n", fragFilename);
    shaderDestroy(vertShader);

    return 0;
  }

  GLuint shaderProg = glCreateProgram();
  if (shaderProg) {
    glAttachShader(shaderProg, vertShader);
    glAttachShader(shaderProg, fragShader);

    glLinkProgram(shaderProg);

    GLint linkingSucceeded = GL_FALSE;
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &linkingSucceeded);
    if (!linkingSucceeded) {
      SDL_Log("Linking shader failed (vert shader %s, frag shader: %s)\n",
              vertFilename, fragFilename);
      GLint logLength = 0;
      glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &logLength);
      GLchar *errLog = (GLchar *)malloc(logLength);
      if (errLog) {
        glGetProgramInfoLog(shaderProg, logLength, &logLength, errLog);
        SDL_Log("%s\n", errLog);
        free(errLog);
      } else {
        SDL_Log("Couldn't get shader link log; out of memory\n");
      }
      glDeleteProgram(shaderProg);
      return 0;
    }
  } else {
    SDL_Log("Couldn't create shader program\n");
  }

  shaderDestroy(vertShader);
  shaderDestroy(fragShader);

  return shaderProg;
}

void shaderProgDestroy(GLuint shaderProg) {
  glDeleteProgram(shaderProg);
}
