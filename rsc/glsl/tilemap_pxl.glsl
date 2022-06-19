#version 330 core

out vec4 pso_color;

in vec2 vso_vtx_coord;
in vec4 vso_vtx_color;
in vec2 vso_tex_coord;

uniform float uni_num_time;

void main() {
    
    float time_sin = sin(uni_num_time) / 2.0f + 1.0f;
    float time_cos = cos(uni_num_time) / 2.0f + 1.0f;
    
    pso_color = vec4(
        time_sin * vso_vtx_color.r,
        time_cos * vso_vtx_color.g,
        time_sin * vso_vtx_color.b,
        time_cos * vso_vtx_color.a
    );
    
}
/* pixel */