#include "shader.h"

#include <glad/glad.h>

void atchshdr(char *fname, unsigned int shdtype, unsigned int progid) {
    unsigned int shdid = glCreateShader(shdtype);

    char *src = getshdr(fname);
    printf("%s\n", src);
    
    glShaderSource(shdid, 1, &src, NULL);
    glCompileShader(shdid);
    glAttachShader(progid, shdid);
    
}

char *getshdr(char *fname) {	
    FILE *file;
    char *buff;
    long fsize;
 
    file = fopen(fname, "r");
    
    if(file == NULL)
      return "ERR_FILE_NULL";
 
    fseek(file, 0L, SEEK_END);
    fsize = ftell(file);
 
    fseek(file, 0L, SEEK_SET);	
 
    buff = (char*)calloc(fsize, sizeof(char));	
 
    if(buff == NULL)
      return "ERR_BUFF_NULL";
 
    fread(buff, sizeof(char), fsize, file);
    fclose(file);
 
    return buff;
}
