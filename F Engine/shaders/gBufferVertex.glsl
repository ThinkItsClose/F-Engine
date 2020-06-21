#version 400 core

layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec2 vs_textureCoordinate;
layout (location = 2) in vec3 vs_normal;
layout (location = 3) in vec3 vs_tangent;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec3 position;
out vec3 normal;
out vec2 textureCoordinate;

void main(){
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vs_position, 1.0);
    normal = mat3(transpose(inverse(ModelMatrix))) * vs_normal;
    position = vec3(ModelMatrix * vec4(vs_position, 1.0f));
    textureCoordinate = vs_textureCoordinate;
}