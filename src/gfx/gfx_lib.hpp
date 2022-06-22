#ifndef GFX_LIB_HPP

#	define GFX_LIB_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_vector.hpp"
#   include "../lib/lib_matrix.hpp"

#   include "vector"

namespace gt {
    
    using dtype_t = enum_t;

    namespace gfx {
        /* how to render plane faces */
        typedef enum {
            FACEMODE_LINE,
            FACEMODE_FILL,
        } facemode_e;
        /* types of the shaders supported */
        typedef enum {
            SHTYPE_VERTEX,
            SHTYPE_PIXEL,
            SHTYPE_GEOMETRY,
        } shtype_e;
        /* mapping type */
        typedef enum {
            MATYPE_MATERIA,
            MATYPE_ILAYOUT,
        } matype_e;
        /**/
    }

    namespace gfx {
        /* shader uniform(constant) or vertex attribute pointer */
        typedef struct {
            /* index and string names */
            sbufr_t sname;
            index_t iname;
            /*
            data type, count, memory size, memory alignment
            (float, 3, sizeof(float)*3 for a vector with 3 floats)
            */
            dtype_t dtype;
            count_t count;
            msize_t msize;
            msize_t malig;
            /* data offset - depends on the mapping containing this element */
            msize_t start;
            /**/
        } element_t;
        /* data mapping - just an array of elements */
        typedef struct {
            count_t     count;
            msize_t     msize;
            element_t* mdata;
        } mapping_t;
        /* input layout (vertex array) */
        typedef struct {
            /* graphics api handle */
            index_t index;
            /* the actual data in bytes */
            mbufr_t mbufr;
            /* pointers to the beginning and the end of the buffer */
            mdata_t mhead;
            mdata_t mtail;
        } buffer_t;
        typedef struct {
            /* graphics api handle */
            index_t index;
            /* input layout (vertex array) attributes */
            mapping_t mapping;
            /* vertex buffer */
            buffer_t vbuffer;
            /**/
        } ilayout_t;
        /* texture for sprite per-pixel colors and framebuffers */
        typedef struct {
            /* graphics api handle */
            index_t index;
            /* pixel data */
            mbufr_t mbufr;
            /* image properties */
            v2u_t   sizes;
            count_t pixel_bytes;
            /**/
        } texture_t;
        /* samplers for texture configurations */
        typedef struct {
            /* graphics api handle */
            index_t index;
            /**/
        } sampler_t;
        /* just a dynamic array of textures and their samplers */
        typedef struct {
            count_t     count;
            texture_t*  texture_array;
            sampler_t*  sampler_array;
        } binding_t;
        typedef struct {
            /* graphics api handle */
            index_t index;
            /* source code */
            sbufr_t sbufr;
            /**/
        } shader_t;
        typedef struct {
            /* graphics api handle */
            index_t     index;
            /* vertex, pixel, geometry shader */
            shader_t    vshader, gshader, pshader;
            /* shader uniforms(constants) */
            mapping_t   mapping;
            /* textures + samplers */
            binding_t   binding;
            /* shader buffer for uniforms (or constants) */
            buffer_t    sbuffer;
            /**/
        } materia_t;
        /* structure of structures for drawing */
        typedef struct {
            /* what to draw */
            ilayout_t ilayout;
            /* how to draw */
            materia_t materia;
            /* */
        } drawtool_t;

        /* framebuffer for off-screen rendering */
        typedef struct fmbuffer_t {
            /* graphics api handle */
            index_t     index;
            /* some parameters */
            v4s_t       viewport;
            /* color attachment where pixels are rendered */
            texture_t   colorbuf;
        } fmbuffer_t;
    }
    
    namespace gfx {
        /* graphics context state with needed variables and settings */
        typedef struct {
            /* how to draw plane faces */
            facemode_e  facemode;
            /* coordinates and size of the canvas */
            v4s_t       viewport;
            /* default framebuffer color */
            v4f_t       clearcol;
            /* */
            v1f_t point_size;
            v1f_t lines_size;
        } state_t;
        /* additional information */
        typedef struct ginfo_t {
            /* render submission info */
            struct {
                count_t count;
            } drawcall;
            /* primities drawn */
            struct {
                count_t drawn_count;
                count_t store_count;
            } drawable;
            /* vertex buffer:
                - how much bytes does a single vertex contain
                - how many vertices do we have
            */
            struct {
                msize_t vsize;
                msize_t drawn_bytes;
                msize_t store_bytes;
            } vbuffer;
            /* texture atlas */
            struct {
                count_t count;
            } texture;
            /**/
        };
        /**/
    }

    namespace gfx {

        typedef struct line_t {
            
            struct {
                /* vertex params */
                v2f_t coord = { 0.0f, 0.0f };
                v4f_t color = { 1.0, 1.0, 1.0, 1.0 };
            } from, into;
            /* texture params */
            /**/
        } line_t;

        typedef struct rect_t {
            /* vertex params */
            v2f_t pivot = { 0.0f, 0.0f };
            v2f_t scale = { 0.5f, 0.5f };
            v2f_t coord = { 0.0f, 0.0f };
            /* texture params */
            v4f_t color = { 1.0f, 1.0f, 1.0f, 1.0f };
            v4f_t texuv = { 0.0f, 0.0f, 1.0f, 1.0f };
            v1f_t texid = { 0.0f };
            /**/
        } rect_t;

        typedef struct tile_t {

            v2s_t mapid;
            v2s_t texid;

        };
        typedef std::vector<tile_t> tiles_t;

        typedef struct grid_t {
            /* general setup */
            v1s_t   texid = { 0 };
            v4f_t   texuv = { 0.0f, 0.0f, 0.125f, 0.125f };
            v4f_t   color = { 1.0f, 1.0f, 1.0f, 1.0f };
            /* tilemap */
            v2f_t   scale = { 1.0f, 1.0f };
            tiles_t tiles = {};
            /**/
        } grid_t;

        typedef struct camera_t {
            /* orientation */
            v2f_t coord;
            v1f_t angle;
            /* viewpoint */
            v1f_t scale;
            v1f_t ratio;
        };
    }

    namespace gfx {
        /* get the memory size in bytes out of an enum type */
        extern msize_t
            get_dtype_msize(dtype_t dtype);
        /* get the aligned memory size in bytes out of an enum type */
        extern msize_t
            get_dtype_msize_align(dtype_t dtype);
        /* get the memory alignment in bytes out of an enum type */
        extern msize_t
            get_dtype_malig(dtype_t dtype);
        /* get the data type out of an enum type for a single element (like 1 float from v3f) */
        extern dtype_t
            get_dtype_item(dtype_t dtype);
        /* get count out of an enum type for the single element (like 1 float from v3f) */
        extern count_t
            get_dtype_count_item(dtype_t dtype);
        /* get the memory size in bytes out of an enum type for a single element (like 1 float from v3f) */
        extern msize_t
            get_dtype_msize_item(dtype_t dtype);
    }

}

#endif /* GFX_LIB_HPP */