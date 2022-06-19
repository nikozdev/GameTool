#ifndef GFX_LIB_HPP

#	define GFX_LIB_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_vector.hpp"

namespace gt {
    
    using dtype_t = enum_t;

    namespace gfx {
        /* how to render plane faces */
        typedef enum {
            FACEMODE_LINE,
            FACEMODE_FILL,
        } facemode_t;
        /**/
    }

    namespace gfx {
        /* shader uniform(constant) or vertex attribute pointer */
        typedef struct {
            /* index and string names */
            sbufr_t sname;
            index_t iname;
            /* data type and count and memory size (float, 3, sizeof(float)*3 for a vector with 3 floats) */
            dtype_t dtype;
            count_t count;
            msize_t msize;
            /* data offset - depends on the mapping containing this element */
            msize_t start;
            /**/
        } element_t;
        /* data mapping - just an array of elements */
        typedef struct {
            count_t     count;
            msize_t     msize;
            element_t*  mdata;
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
            /* vertex, index, shader buffers */
            buffer_t vbuffer, ibuffer, sbuffer;
            /**/
        } ilayout_t;
        /* texture for sprite per-pixel colors and framebuffers */
        typedef struct {
            /* graphics api handle */
            index_t index;
            /* pixel data */
            mbufr_t mbufr;
            /* image properties */
            count_t pixel_bytes;
            /**/
        } texture_t;
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
            shader_t    vshader, pshader, gshader;
            /* shader uniforms(constants) */
            mapping_t   mapping;
            /**/
        } materia_t;
        /* structure of structures for drawing */
        typedef struct {
            /* what to draw */
            ilayout_t ilayout;
            /* how to draw */
            materia_t materia;
            /**/
        } drawtool_t;

        /* framebuffer for off-screen rendering */
        typedef struct {
            /* graphics api handle */
            index_t     index;
            /* some parameters */
            v4s_t       viewport;
            /* color attachment where pixels are rendered */
            texture_t   colorbuf;
        } fmbuffer_t;

        /* graphics context state with needed variables and settings */
        typedef struct {
            /* how to draw plane faces */
            facemode_t  facemode;
            /* coordinates and size of the canvas */
            v4s_t       viewport;
            /* default framebuffer color */
            v4f_t       clearcol;
            /**/
        } state_t;

    }

    namespace gfx {

        typedef struct rect_t {
            /* vertex params */
            gt::v2f_t vtx_coord = { 0.0f, 0.0f };
            gt::v2f_t vtx_pivot = { 0.0f, 0.0f };
            gt::v2f_t vtx_scale = { 0.5f, 0.5f };
            /* texture params */
            gt::v4f_t tex_color = { 1.0, 1.0, 1.0, 1.0 };
            gt::v4f_t tex_coord = { 0.0, 0.0, 1.0, 1.0 };
            gt::v1s_t tex_index = { 0 };
            /**/
        } rect_t;

    }

    namespace gfx {
        /* get the memory size in bytes out of an enum type */
        extern msize_t
            get_dtype_msize(dtype_t dtype);
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