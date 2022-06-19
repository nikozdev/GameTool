#version 330 core

layout(location=0) in vec2 vsi_vtx_coord;
layout(location=1) in vec4 vsi_vtx_color;
layout(location=2) in vec2 vsi_tex_coord;

out vec2 vso_vtx_coord;
out vec4 vso_vtx_color;
out vec2 vso_tex_coord;

void main() {
    
    gl_Position = vec4(vsi_vtx_coord.x, vsi_vtx_coord.y, 0.0, 1.0);
    
    vso_vtx_coord = vsi_vtx_coord;
    vso_vtx_color = vsi_vtx_color;
    vso_tex_coord = vsi_tex_coord;

}
/* vertex */