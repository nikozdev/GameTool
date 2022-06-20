#ifndef GFX_DATA_HPP

#	define GFX_DATA_HPP

namespace gt {

    namespace gfx {

        extern const char* vshader_source;
        extern const char* gshader_source;
        extern const char* pshader_source;

    }

}

const char* gt::gfx::vshader_source = R"(
#version 330 core

layout(location=0) in vec2  vsi_vtx_coord;
layout(location=1) in vec2  vsi_vtx_pivot;
layout(location=2) in vec2  vsi_vtx_scale;

layout(location=3) in vec4  vsi_tex_color;
layout(location=4) in vec4  vsi_tex_coord;
layout(location=5) in float vsi_tex_index;

out vso_t {

    out vec2        vtx_scale;
    out vec4        tex_color;
    out vec4        tex_coord;
    out flat float  tex_index;

} vso;

void main() {
    
    gl_Position = vec4(
        vsi_vtx_coord.x - vsi_vtx_pivot.x * vsi_vtx_scale.y,
        vsi_vtx_coord.y - vsi_vtx_pivot.y * vsi_vtx_scale.y,
        0.0, 1.0
    );
    
    vso.vtx_scale = vsi_vtx_scale;
    vso.tex_color = vsi_tex_color;
    vso.tex_coord = vsi_tex_coord;
    vso.tex_index = vsi_tex_index;

}
/* vertex */
)";
const char* gt::gfx::gshader_source = R"(
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vso_t {

    vec2        vtx_scale;
    vec4        tex_color;
    vec4        tex_coord;
    flat float  tex_index;

} gsi[];

out gso_t {
    
    vec4        tex_color;
    vec2        tex_coord;
    flat float  tex_index;

} gso;

vec2 coord, signs;

void makev(int index);

void main() {
    
    makev(0);
    makev(1);
    makev(2);
    makev(3);

    EndPrimitive();
}

void makev(int index) {
    
    if (index % 2 == 0)         { signs.x = -1.0; } else { signs.x = +1.0; }
    if ((index / 2) % 2 == 0)   { signs.y = +1.0; } else { signs.y = -1.0; }

    coord.x = signs.x * gsi[0].vtx_scale.x;
    coord.y = signs.y * gsi[0].vtx_scale.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord.x, coord.y, 0.0, 0.0);

    if (index % 2 == 0)         { coord.x = gsi[0].tex_coord.x; } else { coord.x = gsi[0].tex_coord.z; }
    if ((index / 2) % 2 == 0)   { coord.y = gsi[0].tex_coord.y; } else { coord.y = gsi[0].tex_coord.w; }

    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(coord.x, coord.y);
    gso.tex_index = gsi[0].tex_index;

    EmitVertex();
}
/* geometry */
)";
const char* gt::gfx::pshader_source = R"(
#version 330 core

out vec4 pso_color;

in gso_t {

    vec4        tex_color;
    vec2        tex_coord;
    flat float  tex_index;

} psi;

#define TEX_COUNT   0x10

uniform sampler2D   uni_tex_array[TEX_COUNT];

void main() {
    
    int tex_index = int(psi.tex_index);

    vec4 tex_pixel = texture(uni_tex_array[tex_index], psi.tex_coord);

    pso_color = tex_pixel * psi.tex_color;
    
}
/* pixel */
)";

#endif /* GFX_DATA_HPP */