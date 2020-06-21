#version 400 core

layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec2 vs_textureCoordinate;

out vec2 textureCoordinate;

void main(){
    textureCoordinate = vs_textureCoordinate;

    // Times the position by 2 because in the quad primitive class it is only 1 unit length across whereas the screen is double that
    gl_Position = vec4(vs_position*vec3(2, 2, 1), 1.0);
}