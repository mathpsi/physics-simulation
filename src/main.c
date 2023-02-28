#include "shader.h"
#include "object.h"
#include "vector.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

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
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Physiks", NULL, NULL);
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

    GLuint program_id; /* For handling program id */
    
    /* Creating program and shaders */
    program_id = glCreateProgram();

    /* TODO: make AttachShader better */
    AttachShader("../shaders/shader.vert", GL_VERTEX_SHADER, program_id); 
    AttachShader("../shaders/shader.frag", GL_FRAGMENT_SHADER, program_id);

    glLinkProgram(program_id);

    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Version: %s\n", glGetString(GL_VERSION));
    
    Renderer *renderer = InitializeRenderer(program_id);
    
    Object *object = InitializeObject(vector2(0.0f, 0.0f), rectangle, vector2(.05f, .05f), .0f, renderer);
    Object *object_2 = InitializeObject(vector2(0.0f, 0.0f), rectangle, vector2(.05f, .05f), .0f, renderer);
    Object *object_3 = InitializeObject(vector2(0.5f, 0.0f), rectangle, vector2(.1f, .05f), .0f, renderer);
    Object *object_4 = InitializeObject(vector2(0.5f, 0.5f), rectangle, vector2(.05f, .05f), .0f, renderer);
    
    Object *object_5 = InitializeObject(vector2(0.0f, -0.5f), circle, VECTOR2_NULL, 0.05f, renderer);
    Object *object_6 = InitializeObject(vector2(-0.5f, -0.5f), circle, VECTOR2_NULL, 0.05f, renderer);
    
    GLfloat x = -1.0f;
    GLfloat y_4 = 1.0f;

    GLfloat x_6 = -0.5f;

    GLfloat aspect_ratio = 1920.0f/1080.0f; /* a=w/h */    
    GLuint aspect_ratio_location = glGetUniformLocation(program_id, "aspect_r");

    GLfloat time_current;
    GLfloat time_last = glfwGetTime();
    GLuint frame;
    
    do {
        /* FPS Counter */
        frame++;
	time_current = glfwGetTime();

        if (time_current - time_last >= 1.0f) {
	    printf("FPS: %d\n", frame);
	    frame = 0; time_last += 1.0f;
	}

        /* Projection matrix */
        glUniform1f(aspect_ratio_location, aspect_ratio);

        object->position.x = x;
	object_4->position.y = y_4;
	object_6->position.x = x_6;
	
	x += 0.002f;
	x_6 += 0.001f; 
	y_4 -= 0.004f;
	
	if (x >= 1.0f) {
	    x = -1.0f;
	}

	if (y_4 <= -1.0f) {
	    y_4 = 1.0f;
	}

        if (x_6 >= 0.5f) {
	    x_6 = -0.5f;
	}
	
	/* Rendering objects */
        RenderObjects(renderer, program_id);
	
	/* Swap buffers */
	glfwSwapBuffers(window);
	glfwPollEvents();
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glDeleteProgram(program_id); }
    } /* Check if the ESC key was pressed or the window was closed */
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0);
}
