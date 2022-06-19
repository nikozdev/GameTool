#version 330 core

out vec4 pso_color;

in gso_t {

    vec4        tex_color;
    vec2        tex_coord;
    flat int    tex_index;

} psi;

uniform float       uni_num_time;

#define TEX_COUNT   10

uniform sampler2D   uni_tex_index_array[TEX_COUNT];

void main() {
    
    float time_sin = 1.0; /* sin(uni_num_time) / 2.0f + 1.0f; */
    float time_cos = 1.0; /* cos(uni_num_time) / 2.0f + 1.0f; */
    
    vec4 tex_color = texture(uni_tex_index_array[psi.tex_index], psi.tex_coord);

    pso_color = vec4(
        time_sin * psi.tex_color.r,
        time_cos * psi.tex_color.g,
        time_sin * psi.tex_color.b,
        time_cos * psi.tex_color.a
    );
    
}
/* pixel */