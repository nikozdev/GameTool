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

layout(location=0) in vec2  vsi_pivot;
layout(location=1) in vec2  vsi_scale;
layout(location=2) in vec2  vsi_coord;

layout(location=3) in vec4  vsi_color;
layout(location=4) in vec4  vsi_texuv;
layout(location=5) in float vsi_texid;

out vso_t {

    out vec2    scale;
    out vec4    color;
    out vec4    texuv;
    out float   texid;

} vso;

uniform vec2    uni_coord;
uniform float   uni_angle;
uniform float   uni_scale;
uniform float   uni_ratio;

void main() {

    vec4 coord = vec4(
        vsi_coord.x - (vsi_pivot.x * vsi_scale.y),
        vsi_coord.y - (vsi_pivot.y * vsi_scale.y),
        0.0, 1.0
    );
    
    coord.x += uni_coord.x;
    coord.y += uni_coord.y;
    
    float angle_cos = cos(radians(uni_angle));
    float angle_sin = sin(radians(uni_angle));

    coord.x = coord.x * angle_cos - coord.y * angle_sin;
    coord.y = coord.x * angle_sin + coord.y * angle_cos;
    
    coord.x = coord.x * uni_scale * uni_ratio;
    coord.y = coord.y * uni_scale;

    gl_Position = coord;
    
    vso.scale = vsi_scale / 2.0f;
    vso.color = vsi_color;
    vso.texuv = vsi_texuv;
    vso.texid = vsi_texid;

}
/* vertex */
)");
static inline std::string gt::gfx::gshader_source = std::string(R"(
#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vso_t {

    vec2    scale;
    vec4    color;
    vec4    texuv;
    float   texid;

} gsi[];

out gso_t {
    
    vec4        color;
    vec2        texuv;
    flat float  texid;

} gso;

uniform vec2    uni_coord;
uniform float   uni_angle;
uniform float   uni_scale;
uniform float   uni_ratio;

void makev(int index);

void main() {
    
    makev(0);
    makev(1);
    makev(2);
    makev(3);

    EndPrimitive();
}

void makev(int index) {
    
    vec2 coord, signs;
    
    if (index % 2 == 0)         { signs.x = -1.0; } else { signs.x = +1.0; }
    if ((index / 2) % 2 == 0)   { signs.y = +1.0; } else { signs.y = -1.0; }
    
    coord.x = signs.x * gsi[0].scale.x * uni_ratio;
    coord.y = signs.y * gsi[0].scale.y;
    
    float angle_cos = cos(radians(uni_angle));
    float angle_sin = sin(radians(uni_angle));
    
    coord.x = coord.x * angle_cos - coord.y * angle_sin;
    coord.y = coord.x * angle_sin + coord.y * angle_cos;
    
    coord.x = coord.x * uni_scale;
    coord.y = coord.y * uni_scale;
    
    gl_Position = (gl_in[0].gl_Position + vec4(coord.x, coord.y, 0.0, 0.0));
    
    vec2 texuv;
    
    if (index % 2 == 0)         { texuv.x = gsi[0].texuv.x; } else { texuv.x = gsi[0].texuv.z; }
    if ((index / 2) % 2 == 0)   { texuv.y = gsi[0].texuv.y; } else { texuv.y = gsi[0].texuv.w; }
    
    gso.color = gsi[0].color;
    gso.texuv = texuv;
    gso.texid = gsi[0].texid;

    EmitVertex();
}
/* geometry */
)");
static inline std::string gt::gfx::pshader_source = std::string(R"(
#version 330 core

out vec4 pso_color;

in gso_t {

    vec4        color;
    vec2        texuv;
    flat float  texid;

} psi;

#define TEX_COUNT )") + std::to_string(0x10) + std::string(R"(

uniform sampler2D   uni_texid[TEX_COUNT];

void main() {
    
    int texid = int(psi.texid);

    vec4 pixel = texture(uni_texid[texid], psi.texuv);

    pso_color = pixel * psi.color;
    
}
/* pixel */
)");

#endif /* GFX_DATA_HPP */