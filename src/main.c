#include "shader.h"
#include "object.h"
#include "vector.h"
#include "physics.h"

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
    
    Object *object_1 = InitializeObject(vector2(-1.0f, -1.0f), circle, VECTOR2_NULL, 0.05f, yellow, renderer);
    Object *object_2 = InitializeObject(vector2(-0.5f, -0.5f), circle, VECTOR2_NULL, 0.05f, white, renderer);
    Object *object_3 = InitializeObject(vector2(0.5f, 0.5f), circle, VECTOR2_NULL, 0.05f, red, renderer);
    
    GLfloat aspect_ratio = 1920.0f/1080.0f; /* a=w/h */    
    GLuint aspect_ratio_location = glGetUniformLocation(program_id, "aspect_r");

    GLfloat time_current;
    GLfloat time_last = glfwGetTime();
    GLfloat time_delta;
    GLuint fps;

    object_1->rigidbody->velocity = vector2(0.5f, 0.5f);
    object_1->rigidbody->mass = object_2->rigidbody->mass = 1.0f;
    object_3->rigidbody->mass = 0.5f; object_3->rigidbody->velocity = vector2(-0.6f, -0.6f);
    
    do {
        /* FPS Counter */
        time_delta = 1.0f/(time_last - time_current);
        //printf("FPS: %f\n", time_delta);
	renderer->time_delta = 1.0f/time_delta;
	
	time_current = glfwGetTime();

        /* Projection matrix */
        glUniform1f(aspect_ratio_location, aspect_ratio);

	/* Physics simulation */
        SimulatePhysics(renderer);
	
	/* Rendering objects */
        RenderObjects(renderer, program_id);
	
	/* Swap buffers */
	glfwSwapBuffers(window);
	glfwPollEvents();
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glDeleteProgram(program_id); }
	time_last = glfwGetTime();
    } /* Check if the ESC key was pressed or the window was closed */
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0);
}
