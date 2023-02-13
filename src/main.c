#include "shader.h"
#include "object.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLuint program_id; /* For handling program id */
int main() {
    /* Initialize GLFW */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
	    return -1;
    }
    //glfwWindowHint(GLFW_SAMPLES, 16); /* Antialiasing */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); /* OpenGL 4 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* To make MacOS happy */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* Prevent the old OpenGL */

    /* Create window */
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Physics Simulation", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
    	glfwTerminate();
    	return -1;
    }

    /* Initialize GLAD */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
	    return -1;
    }
     
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    /* Creating program and shaders */
    program_id = glCreateProgram();

    /* TODO: make AttachShader better */
    AttachShader("../shaders/shader.vert", GL_VERTEX_SHADER, program_id); 
    AttachShader("../shaders/shader.frag", GL_FRAGMENT_SHADER, program_id);

    glLinkProgram(program_id);
    
    Renderer *renderer = InitializeRenderer(program_id);
    
    Object *object = InitializeObject(0.0f, 0.0f, square, renderer);
    
    Object *object_2 = InitializeObject(0.0f, 0.0f, square, renderer);

    Object *object_3 = InitializeObject(0.5f, 0.0f, square, renderer);

    Object *object_4 = InitializeObject(0.5f, 0.5f, square, renderer);
    
    GLfloat x = -1.0f;
    
    do {
        object->x = x;
        RenderObjects(renderer, program_id);
	x += 0.005f;
	if (x >= 1.0f) {
	    x = -1.0f;
	}
	/* Swap buffers */
	glfwSwapBuffers(window);
	glfwPollEvents();
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glDeleteProgram(program_id); }
    } /* Check if the ESC key was pressed or the window was closed */
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0);
}
