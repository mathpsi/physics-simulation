#include "shape.h"

#include <glad/glad.h>


/*   w
   +--------->x
   |      |
   |      | h
   |-------
   |
   y
*/

GLfloat unit_square[] = {
      .0f,   .0f, .0f,
      .0f, -1.0f, .0f,
     1.0f, -1.0f, .0f,
     1.0f,   .0f, .0f 
};

/* Index buffer */
GLuint indices_unit_square[] = {
    0, 1, 2,
    0, 3, 2
};



/* TODO: GenerateCircle function */

