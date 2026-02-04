#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_uv;

uniform sampler2D u_texture;

void main()
{
    vec4 tex_color = texture(u_texture, v_uv);
    color = tex_color;
}
