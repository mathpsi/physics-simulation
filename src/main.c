#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* GLSL codes */
char *vssrc =
"#version 400 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main()                                            \
 {                                                      \
    gl_Position = vec4(inPosition, 1.0f);               \
 }";

char *fssrc =
"#version 400 core\n                                    \
 out vec4 fragColor;                                    \
 void main()                                            \
 {                                                      \
    fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);           \
 }";

/* Coordinates of triangle */
float vertices[] = {
    -0.5f,  0.0f, 0.0f,
     0.5f,  0.0f, 0.0f,
     0.0f,  0.5f, 0.0f 
}; 

unsigned int progid; // For handling program id
int main() {
    /* Initialize GLFW */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
	return -1;
    }
    //glfwWindowHint(GLFW_SAMPLES, 16); // Antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Prevent the old OpenGL 

    /* Create window */
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Physics Simulation", NULL, NULL);
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
    progid = glCreateProgram();
    unsigned int vertid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertid, 1, &vssrc, NULL);
    glCompileShader(vertid);

    unsigned int fragid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragid, 1, &fssrc, NULL);
    glCompileShader(fragid);

    glAttachShader(progid, vertid);
    glAttachShader(progid, fragid);

    glLinkProgram(progid);

    unsigned int vbo;
    unsigned int vao;

    glGenVertexArrays(1, &vao);
    
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(0);
    
    do {
       /* Clear the screen */
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

	/* Draw triangle */
	glUseProgram(progid);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	/* Swap buffers */
	glfwSwapBuffers(window);
	glfwPollEvents();
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glDeleteProgram(prog_id); }
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0);
}
