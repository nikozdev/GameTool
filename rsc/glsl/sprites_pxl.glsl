#version 330 core

out vec4 pso_color;

in gso_t {

    vec4        tex_color;
    vec2        tex_coord;
    flat int    tex_index;

} psi;

#define TEX_COUNT   0x10

uniform sampler2D   uni_tex_index[TEX_COUNT];

void main() {
    
    vec4 tex_pixel = texture(uni_tex_index[psi.tex_index], psi.tex_coord);

    pso_color = tex_pixel * psi.tex_color;
    
}
/* pixel */