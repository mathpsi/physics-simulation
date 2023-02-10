#version 400 core
layout (location = 0) in vec3 _pos;
uniform vec2 move;
void main() {
    gl_Position = vec4(_pos + vec3(move, 0.0f), 1.0f);
}
