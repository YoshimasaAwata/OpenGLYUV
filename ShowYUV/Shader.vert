#version 330 core

in vec3 position;
in vec2 vertexUV;
out vec2 uv;
uniform mat4 modelViewProj;

void main()
{
    vec4 v = vec4(position, 1);
    gl_Position = modelViewProj * v;
    uv = vertexUV;
}
