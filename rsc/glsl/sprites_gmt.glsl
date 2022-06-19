#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vso_t {

    vec2        vtx_pivot;
    vec2        vtx_sizes;

    vec4        tex_color;
    vec4        tex_coord;
    flat int    tex_index;

} gsi[];

out gso_t {
    
    vec4        tex_color;
    vec2        tex_coord;
    flat int    tex_index;

} gso;

float coord_x;
float coord_y;

void makev(int index);

void main() {
    
    /* vertex0
    
    coord_x = -gsi[0].vtx_sizes.x;
    coord_y = -gsi[0].vtx_sizes.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord_x, coord_y, 0.0, 0.0);

    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(gsi[0].tex_coord.xy);
    gso.tex_index = gsi[0].tex_index;

    EmitVertex();
    */
    makev(0);

    /* vertex1

    coord_x = -gsi[0].vtx_sizes.x;
    coord_y = +gsi[0].vtx_sizes.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord_x, coord_y, 0.0, 0.0);
    
    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(gsi[0].tex_coord.xw);
    gso.tex_index = gsi[0].tex_index;

    EmitVertex();
    */
    makev(1);
    
    /* vertex2

    coord_x = +gsi[0].vtx_sizes.x;
    coord_y = -gsi[0].vtx_sizes.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord_x, coord_y, 0.0, 0.0);
    
    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(gsi[0].tex_coord.zy);
    gso.tex_index = gsi[0].tex_index;
    
    EmitVertex();
    */
    makev(2);
    
    /* vertex3

    coord_x = +gsi[0].vtx_sizes.x;
    coord_y = +gsi[0].vtx_sizes.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord_x, coord_y, 0.0, 0.0);
    
    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(gsi[0].tex_coord.zw);
    gso.tex_index = gsi[0].tex_index;
    
    EmitVertex();
    */
    makev(3);

    EndPrimitive();
}
void makev(int index) {
    
    float signx, signy;
    if (index % 2 == 0)         { signx = -1.0; } else { signx = +1.0; }
    if ((index / 2) % 2 == 0)   { signy = -1.0; } else { signy = +1.0; }

    coord_x = signx * 0.5; // gsi[0].vtx_sizes.x;
    coord_y = signy * 0.5; // gsi[0].vtx_sizes.y;

    gl_Position = gl_in[0].gl_Position + vec4(coord_x, coord_y, 0.0, 0.0);

    if (index % 2 == 0)         { coord_x = gsi[0].tex_coord.x; } else { coord_x = gsi[0].tex_coord.z; }
    if ((index / 2) % 2 == 0)   { coord_y = gsi[0].tex_coord.y; } else { coord_y = gsi[0].tex_coord.w; }

    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(coord_x, coord_y);
    gso.tex_index = gsi[0].tex_index;

    EmitVertex();
}
/* vertex */