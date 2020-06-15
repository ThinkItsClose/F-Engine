#version 400 core

in vec3 position;
in vec3 normal;

out vec4 FragColor;

void main(){
    // Very basic dot product lighting for now
    FragColor = vec4(vec3(clamp(dot(normal, normalize(vec3(2, 4, 3)-position)), 0, 0.8f)+0.1f), 1);
}