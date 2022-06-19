#ifndef GFX_ENGINE_HPP

#   define GFX_ENGINE_HPP

#   include "../cfg.hpp"

#   include "gfx_lib.hpp"

#   include "../lib/lib_event.hpp"

#   include "../lib/lib_engine.hpp"

namespace gt {

    namespace gfx {

        class engine_t : public lib::engine_t_t<engine_t> {

        public:

            using this_t = engine_t;
            using base_t = lib::engine_t_t<this_t>;

            using window_t = void*;
            using contex_t = void*;
            using device_t = void*;

        public:

            bool
                set_pixel_size(float scale = 1.0f);
            bool
                set_lines_size(float scale = 1.0f);

            bool
                set_facemode(facemode_t facemode);

            bool
                set_viewport(int x, int y, int w, int h);

            bool
                set_clear_color(float r, float g, float b, float a);

            inline const fmbuffer_t*
                get_fmbuffer() const
            {
                return &this->fmbuffer;
            }

        public:

            virtual bool
                init() override;
            virtual bool
                work() override;
            virtual bool
                quit() override;

            virtual bool
                proc(lib::event_a_t* event) override;

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
                    ? (this->quit_drawtool(&this->drawtool) ? this->init_fmbuffer(&this->fmbuffer) : false)
                    : (this->init_drawtool(&this->drawtool));
            }

        private:

            bool
                init_fmbuffer(fmbuffer_t* fmbuffer);
            bool
                quit_fmbuffer(fmbuffer_t* fmbuffer);

            bool
                init_drawtool(drawtool_t* drawtool);
            bool
                quit_drawtool(drawtool_t* drawtool);

        private:
            /* platform specific handles */
            window_t window;
            contex_t contex;
            device_t device;
            /* global state objects */
            state_t state;
            /* where to draw */
            fmbuffer_t fmbuffer;
            /* what and how to draw */
            drawtool_t drawtool;
            /**/
        };

    }

}

#endif /* GFX_ENGINE_HPP */