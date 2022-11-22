#ifndef SHADER_H
#define SHADER_H

#include <GLES3/gl3.h>

/**
 * @brief 
 * 
 * 
 * 
 */

/**
 * @brief Loads a vertex and fragment shader from the disk and
 * compiles (& links) them into shader program.
 * It will render any errors to the console.
 * 
 * @param vertFilename filename for the vertex shader
 * @param fragFilename filename for the fragment shader
 * @return GLuint the shader program's ID, or 0 if failed
 */
GLuint shaderProgLoad(const char *vertFilename, const char *fragFilename);

/**
 * @brief Destroys a shader program.
 * 
 * @param shaderProg shader program ID to destroy
 */
void shaderProgDestroy(GLuint shaderProg);

#endif // SHADER_H
