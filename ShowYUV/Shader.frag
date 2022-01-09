#version 330 core

const mat4 TORGB = mat4(
    1.164f,  1.164f, 1.164f, 0.0f,
    0.0f,   -0.392f, 2.017f, 0.0f,
    1.596f, -0.813f, 0.0f,   0.0f,
    0.0f,    0.0f,   0.0f,   1.0f);
const vec4 DIFF = vec4(16.0f / 255, 128.0f / 255, 128.0f / 255, 0.0f);

in vec2 uv;
out vec4 color;

uniform sampler2D textureSamplerY;
uniform sampler2D textureSamplerU;
uniform sampler2D textureSamplerV;

void main()
{
    vec4 fy = texture(textureSamplerY, uv);
    vec4 fu = texture(textureSamplerU, uv);
    vec4 fv = texture(textureSamplerV, uv);
    vec4 yuv = vec4(fy.r, fu.r, fv.r, 1.0f);

    yuv -= DIFF;
    vec4 rgb = TORGB * yuv;
    color = clamp(rgb, 0.0f, 1.0f);
}
