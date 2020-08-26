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
out mat3 TBN;

out vec3 T;

void main(){

    vec3 T = normalize(vec3(ModelMatrix * vec4(vs_tangent, 0.0)));
    vec3 N = normalize(vec3(ModelMatrix * vec4(vs_normal, 0.0)));
    // re-orthogonalize T with respect to N
    T = normalize(T - dot(T, N) * N);
    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 B = cross(N, T);
    mat3 TBN = mat3(T, B, N);

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vs_position, 1.0);
    normal = vs_normal;//mat3(transpose(inverse(ModelMatrix))) * vs_normal;
    position = vec3(ModelMatrix * vec4(vs_position, 1.0f));
    textureCoordinate = vs_textureCoordinate;
}