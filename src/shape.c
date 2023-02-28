#include "shape.h"
#include "vector.h"

#include <glad/glad.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

GLfloat *GenerateCircle(GLfloat radius, int quality) {
    GLfloat double_pi = 2.0f * PI;
    GLfloat angle = double_pi/quality;
    GLfloat *vertices = malloc(sizeof(GLfloat) * quality * 4);
    
    vertices[0] = vertices[1] = vertices[2] = .0f;
    for (int i = 0; i < quality + 2; i++) {
        vertices[(i * 3) + 3] = cos(angle * i) * radius;
        vertices[(i * 3) + 4] = sin(angle * i) * radius;
	vertices[(i * 3) + 5] = .0f;
    }
    return vertices;
}

GLuint *GenerateCircleIndices(int quality) {
    GLuint *indices = malloc(sizeof(GLfloat) * quality * 3);

    for (int i = 0; i < quality; i++) {
        indices[(i * 3)] = 0;
        indices[(i * 3) + 1] = i + 1;
	indices[(i * 3) + 2] = i + 2;
    }

    return indices;
}

