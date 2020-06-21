#version 400 core

in vec2 textureCoordinate;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

out vec4 FragColor;

void main(){
    // Very basic dot product lighting for now
    
    vec3 position = texture(gPosition, textureCoordinate).xyz;
    vec3 normal = texture(gNormal, textureCoordinate).xyz;
    vec4 albedo = texture(gAlbedo, textureCoordinate);

    float diffuse = clamp(dot(normal, normalize(vec3(2, 4, 2)-position)), 0, 1);
    FragColor = (albedo * vec4(vec3(diffuse), 1) * 0.9f) + (albedo * 0.1f);
    //FragColor = vec4(texture(gPosition, textureCoordinate));
}