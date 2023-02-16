#version 400 core

layout (location = 0) in vec3 _pos;
uniform vec2 move;
uniform float aspect_r;

void main() {    
    mat4 projection = mat4(
        1/aspect_r, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
    );
    
    gl_Position = projection * vec4(_pos + vec3(move, 0.0f), 1.0f);
}
