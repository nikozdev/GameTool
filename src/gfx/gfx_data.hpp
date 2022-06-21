#ifndef GFX_DATA_HPP

#	define GFX_DATA_HPP

namespace gt {

    namespace gfx {

        extern std::string vshader_source;
        extern std::string gshader_source;
        extern std::string pshader_source;

    }

}

static inline std::string gt::gfx::vshader_source = std::string(R"(
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

uniform vec2    uni_cam_coord;
uniform float   uni_cam_rotat;
uniform float   uni_cam_scale;
uniform float   uni_cam_ratio;

void main() {
    /*
    v1f_t scale = this->camera.scale;
    v1f_t ratio = this->camera.ratio;
                    
    v1f_t lside = -scale * ratio / 2.0f;
    v1f_t rside = +scale * ratio / 2.0f;
    v1f_t bside = -scale / 2.0f;
    v1f_t tside = +scale / 2.0f;
    v1f_t nside = -10.0f;
    v1f_t fside = +10.0f;
    m4f_t ortho(0.0);

    ortho[0][0] = +2.0f / (rside - lside);
    ortho[1][1] = +2.0f / (tside - bside);
    ortho[2][2] = -2.0f / (fside - nside);

    ortho[3][0] = - (rside + lside) / (lside - rside);
    ortho[3][1] = - (tside + bside) / (bside - tside);
    ortho[3][2] = - (fside + nside) / (fside - nside);

    ortho[3][3] = 1.0f;
    */                
    vec4 coord = vec4(
        vsi_vtx_coord.x - (vsi_vtx_pivot.x * vsi_vtx_scale.y),
        vsi_vtx_coord.y - (vsi_vtx_pivot.y * vsi_vtx_scale.y),
        0.0, 1.0
    );
    
    coord.x -= uni_cam_coord.x;
    coord.y -= uni_cam_coord.y;
    
    float rotat_cos = cos(radians(-uni_cam_rotat));
    float rotat_sin = sin(radians(-uni_cam_rotat));

    coord.x = coord.x * rotat_cos - coord.y * rotat_sin;
    coord.y = coord.x * rotat_sin + coord.y * rotat_cos;
    
    coord.x = coord.x / uni_cam_scale / uni_cam_ratio;
    coord.y = coord.y / uni_cam_scale;

    gl_Position = coord;
    
    vso.vtx_scale = vsi_vtx_scale;
    vso.tex_color = vsi_tex_color;
    vso.tex_coord = vsi_tex_coord;
    vso.tex_index = vsi_tex_index;

}
/* vertex */
)");
static inline std::string gt::gfx::gshader_source = std::string(R"(
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

uniform vec2    uni_cam_coord;
uniform float   uni_cam_rotat;
uniform float   uni_cam_scale;
uniform float   uni_cam_ratio;

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

    coord.x = signs.x * gsi[0].vtx_scale.x / uni_cam_ratio;
    coord.y = signs.y * gsi[0].vtx_scale.y;
    
    float rotat_cos = cos(radians(-uni_cam_rotat));
    float rotat_sin = sin(radians(-uni_cam_rotat));
    
    coord.x = coord.x * rotat_cos - coord.y * rotat_sin;
    coord.y = coord.x * rotat_sin + coord.y * rotat_cos;

    coord.x = coord.x / uni_cam_scale;
    coord.y = coord.y / uni_cam_scale;
    
    gl_Position = (gl_in[0].gl_Position + vec4(coord.x, coord.y, 0.0, 0.0));

    if (index % 2 == 0)         { coord.x = gsi[0].tex_coord.x; } else { coord.x = gsi[0].tex_coord.z; }
    if ((index / 2) % 2 == 0)   { coord.y = gsi[0].tex_coord.y; } else { coord.y = gsi[0].tex_coord.w; }

    gso.tex_color = gsi[0].tex_color;
    gso.tex_coord = vec2(coord.x, coord.y);
    gso.tex_index = gsi[0].tex_index;

    EmitVertex();
}
/* geometry */
)");
static inline std::string gt::gfx::pshader_source = std::string(R"(
#version 330 core

out vec4 pso_color;

in gso_t {

    vec4        tex_color;
    vec2        tex_coord;
    flat float  tex_index;

} psi;

#define TEX_COUNT )") + std::to_string(0x10) + std::string(R"(

uniform sampler2D   uni_tex_array[TEX_COUNT];

void main() {
    
    int tex_index = int(psi.tex_index);

    vec4 tex_pixel = texture(uni_tex_array[tex_index], psi.tex_coord);

    pso_color = tex_pixel * psi.tex_color;
    
}
/* pixel */
)");

#endif /* GFX_DATA_HPP */