#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_uv;

void main()
{
    color = vec4(v_uv, 0.0, 1.0);
}
