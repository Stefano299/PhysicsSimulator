#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 nPos;
layout (location = 2) in mat4 model;

out vec3 vertexPos;
out vec3 normalPos;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*model*vec4(vPos, 1.0);
    vertexPos = vec3(model*vec4(vPos,1.0));
    normalPos = mat3(transpose(inverse(model)))*nPos;
}