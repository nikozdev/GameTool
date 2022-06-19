#version 330 core

layout(location=0) in vec2  vsi_vtx_coord;
layout(location=1) in vec2  vsi_vtx_pivot;
layout(location=2) in vec2  vsi_vtx_scale;

layout(location=3) in vec4  vsi_tex_color;
layout(location=4) in vec4  vsi_tex_coord;
layout(location=5) in int   vsi_tex_index;

out vso_t {

    out vec2        vtx_scale;
    out vec4        tex_color;
    out vec4        tex_coord;
    out flat int    tex_index;

} vso;

void main() {
    
    gl_Position = vec4(
        vsi_vtx_coord.x - vsi_vtx_pivot.x,
        vsi_vtx_coord.y - vsi_vtx_pivot.y,
        0.0, 1.0
    );
    
    vso.vtx_scale = vsi_vtx_scale;
    vso.tex_color = vsi_tex_color;
    vso.tex_coord = vsi_tex_coord;
    vso.tex_index = vsi_tex_index;

}
/* vertex */