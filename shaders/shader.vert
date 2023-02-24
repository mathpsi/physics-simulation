#version 400 core

layout (location = 0) in vec3 _pos;
uniform vec2 move;
uniform vec2 model_wh;
uniform float aspect_r;

void main() {    
    mat4 projection = mat4(
        1/aspect_r, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
    );

    mat4 model = mat4(
        model_wh.x, 0, 0, 0,
	0, model_wh.y, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
    );
    
    gl_Position = projection * ((model * vec4(_pos, 0.25f)) + vec4(move, 0.0f,  1.0f));
}
