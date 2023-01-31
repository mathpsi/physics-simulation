#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

void AttachShader(char *file_name, GLuint shader_type, GLuint program_id) {
    GLuint shader_id = glCreateShader(shader_type);

    GLchar *source = GetShader(file_name);
    if (source[0] == 'E') { fprintf(stderr,"%s\n", source); }
    
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);

    /* 
     * Error handling 
     */
    GLint is_compiled;
    GLchar log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
    
    if (!is_compiled) {
        glGetShaderInfoLog(shader_id, 512, 0, log);
	fprintf(stderr, "%s\n", log);
    }
    
    glAttachShader(program_id, shader_id); 
}

char *GetShader(char *file_name) {	
    FILE *file;
    char *buff;
    long file_size;
 
    file = fopen(file_name, "r");
    
    if (file == NULL) { return "ERR_FILE_NULL"; }
 
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
 
    fseek(file, 0L, SEEK_SET);	
 
    buff = (char*)calloc(file_size, sizeof(char));	
 
    if (buff == NULL) { return "ERR_BUFF_NULL"; }
 
    fread(buff, sizeof(char), file_size, file);
    fclose(file);
 
    return buff;
}
