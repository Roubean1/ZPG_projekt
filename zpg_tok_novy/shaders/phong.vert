#version 330 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 fragNormal;

void main() {
    fragPos = vec3(modelMatrix * vec4(vp, 1.0));
    fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;
    gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}