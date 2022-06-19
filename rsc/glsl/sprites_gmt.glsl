#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vso_t {

    vec2        vtx_scale;
    vec4        tex_color;
    vec4        tex_coord;
    flat int    tex_index;

} gsi[];

out gso_t {
    
    vec4        tex_color;
    vec2        tex_coord;
    flat int    tex_index;

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
    if ((index / 2) % 2 == 0)   { signs.y = -1.0; } else { signs.y = +1.0; }

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