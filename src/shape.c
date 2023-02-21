#include "shape.h"

#include <glad/glad.h>
#include <math.h>
#include <stdlib.h>

GLfloat *GenerateRectangle(GLfloat width, GLfloat height) {  
    GLfloat *rectangle = malloc(sizeof(GLfloat) * 18);

    /*   w
      +--------->x
      |      |
      |      | h
      |-------
      |
      y
    */
    
    
    rectangle[0] =  .0f;
    rectangle[1] =  .0f;
    rectangle[2] =  .0f;
    rectangle[3] =  .0f;
    rectangle[4] = -height;
    rectangle[5] =  .0f;
    rectangle[6] =  width;
    rectangle[7] = -height;
    rectangle[8] =  .0f;
  
    rectangle[9]  =  .0f;
    rectangle[10] =  .0f;
    rectangle[11] =  .0f;
    rectangle[12] =  width;
    rectangle[13] =  .0f;
    rectangle[14] =  .0f;
    rectangle[15] =  width;
    rectangle[16] = -height;
    rectangle[17] =  .0f;
    
    return rectangle;
}

/* TODO: GenerateCircle function */

void GetData(GLfloat *data, GLfloat *pointer) {
  data[0] = pointer[0];
  data[1] = pointer[1];
  data[2] = pointer[2];
  data[3] = pointer[3];
  data[4] = pointer[4];
  data[5] = pointer[5];
  data[6] = pointer[6];
  data[7] = pointer[7];
  data[8] = pointer[8];
  data[9] = pointer[9];
  data[10] = pointer[10];
  data[11] = pointer[11];
  data[12] = pointer[12];
  data[13] = pointer[13];
  data[14] = pointer[14];
  data[15] = pointer[15];
  data[16] = pointer[16];
  data[17] = pointer[17];
}
