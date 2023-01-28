#include "shader.h"

#include <glad/glad.h>

void atchshdr(char *fname, unsigned int shdtype, unsigned int progid) {
    unsigned int shdid = glCreateShader(shdtype);

    char *src = getshdr(fname);
    if (src[0] == 'E') { fprintf(stderr,"%s\n", src); }
    
    glShaderSource(shdid, 1, &src, NULL);
    glCompileShader(shdid);

    /* Exception handling */
    int is_comp;
    char log[512];
    glGetShaderiv(shdid, GL_COMPILE_STATUS, &is_comp);
    
    if (!is_comp) {
        glGetShaderInfoLog(shdid, 512, 0, log);
	fprintf(stderr, "%s\n", log);
    }
    
    glAttachShader(progid, shdid);
    
}

char *getshdr(char *fname) {	
    FILE *file;
    char *buff;
    long fsize;
 
    file = fopen(fname, "r");
    
    if (file == NULL) { return "ERR_FILE_NULL" };
 
    fseek(file, 0L, SEEK_END);
    fsize = ftell(file);
 
    fseek(file, 0L, SEEK_SET);	
 
    buff = (char*)calloc(fsize, sizeof(char));	
 
    if (buff == NULL) { return "ERR_BUFF_NULL"; }
 
    fread(buff, sizeof(char), fsize, file);
    fclose(file);
 
    return buff;
}
