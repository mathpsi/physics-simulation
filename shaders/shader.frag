#version 400 core

out vec4 color;
uniform vec3 new_color;

void main() {
    color = vec4(new_color, 1.0f);
} 
