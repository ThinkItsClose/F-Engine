#version 400 core

in vec3 position;
in vec3 normal;
in vec2 textureCoordinate;

uniform sampler2D albedoMap;

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

void main(){
    // Very basic dot product lighting for now
    //FragColor = vec4(vec3(clamp(dot(normal, normalize(vec3(2, 4, 3)-position)), 0, 0.8f)+0.1f), 1);
    //vec4 texCol = ;
    //float diffuse = clamp(dot(normal, normalize(vec3(0, 4, 0)-position)), 0, 1);
    //FragColor = (texCol * vec4(vec3(diffuse), 1) * 0.9f) + (texCol * 0.1f);
    //FragColor = vec4(normal, 1);

    // store the fragment position vector in the first gbuffer texture
    gPosition = vec4(position, 1);
    // also store the per-fragment normals into the gbuffer
    gNormal = vec4(normalize(normal), 1);
    // and the diffuse per-fragment color
    gAlbedoSpec = texture(albedoMap, textureCoordinate);
}