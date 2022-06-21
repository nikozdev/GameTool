#ifndef GFX_ENGINE_HPP

#   define GFX_ENGINE_HPP

#   include "../cfg.hpp"

#   include "gfx_lib.hpp"

#   include "../lib/lib_engine.hpp"
#   include "../lib/lib_event.hpp"
#   include "../lib/lib_file.hpp"

namespace gt {

    namespace gui { class tool_gfx_t; class tool_frame_t;  }

    namespace gfx {

        class engine_t : public lib::engine_t_t<engine_t> {

        public:

            using this_t = engine_t;
            using base_t = lib::engine_t_t<this_t>;

            using window_t = void*;
            using contex_t = void*;
            using device_t = void*;

            friend class gui::tool_gfx_t;
            friend class gui::tool_frame_t;

        public:

            bool
                set_point_size(float scale = 1.0f);
            bool
                set_lines_size(float scale = 1.0f);

            bool
                set_facemode(facemode_e facemode);

            bool
                set_viewport(int x, int y, int w, int h);

            bool
                set_clearcol(float r, float g, float b, float a);

            inline const fmbuffer_t*
                get_fmbuffer() const
            {
                return &this->fmbuffer;
            }
            inline const drawtool_t*
                get_drawtool() const
            {
                return &this->drawtool;
            }
            inline const camera_t*
                get_camera() const
            {
                return &this->camera;
            }

            inline const state_t*
                get_state() const
            {
                return &this->state;
            }
            inline const ginfo_t*
                get_ginfo() const
            {
                return &this->ginfo;
            }

            bool
                add_for_draw(const rect_t& rect);

        public:

            virtual bool
                init() override;
            virtual bool
                work() override;
            virtual bool
                quit() override;

            virtual bool
                proc(lib::event_a_t* event) override;
            
            bool
                draw();

            inline bool
                redo_fmbuffer()
            {
                return this->fmbuffer.index > 0
                    ? (this->quit_fmbuffer(&this->fmbuffer) ? this->init_fmbuffer(&this->fmbuffer) : false)
                    : (this->init_fmbuffer(&this->fmbuffer));
            }
            inline bool
                redo_drawtool()
            {
                return this->drawtool.ilayout.index > 0 && this->drawtool.materia.index > 0
                    ? (this->quit_drawtool(&this->drawtool) ? this->init_drawtool(&this->drawtool) : false)
                    : (this->init_drawtool(&this->drawtool));
            }

            bool
                load_texture(lib::fpath_t fpath, index_t index);

        private:

            bool
                init_fmbuffer(fmbuffer_t* fmbuffer);
            
            bool
                init_drawtool(drawtool_t* drawtool);
            
            bool
                init_ilayout(ilayout_t* ilayout);
            bool
                init_vbuffer(buffer_t* vbuffer);
            
            bool
                init_materia(materia_t* materia);
            bool
                init_texture(texture_t* texture);
            bool
                init_shader(shader_t* shader, shtype_e shtype);

        private:

            bool
                quit_fmbuffer(fmbuffer_t* fmbuffer);
            
            bool
                quit_drawtool(drawtool_t* drawtool);

            bool
                quit_ilayout(ilayout_t* ilayout);
            bool
                quit_vbuffer(buffer_t* vbuffer);

            bool
                quit_materia(materia_t* materia);
            bool
                quit_texture(texture_t* texture);
            bool
                quit_shader(shader_t* shader, shtype_e shtype);

        private:
            /* platform specific handles */
            window_t    window;
            contex_t    contex;
            device_t    device;
            /* global state objects */
            state_t     state;
            ginfo_t     ginfo;
            /* where to draw */
            fmbuffer_t  fmbuffer;
            /* what and how to draw */
            drawtool_t  drawtool;
            camera_t    camera;
        };

    }

}

#endif /* GFX_ENGINE_HPP */