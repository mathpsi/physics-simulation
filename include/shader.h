#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

void AttachShader(char *file_name, GLuint shader_type, GLuint program_id);
char *GetShader(char *file_name);

#endif
