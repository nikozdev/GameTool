#ifndef GFX_ENGINE_HPP

#   define GFX_ENGINE_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_event.hpp"

#   include "../lib/lib_engine.hpp"

#   include "../lib/lib_vector.hpp"
#   include "../lib/lib_matrix.hpp"

namespace gt {

    namespace gfx {

        class engine_t : public lib::engine_t_t<engine_t> {

        public:

            using this_t = engine_t;
            using base_t = lib::engine_t_t<this_t>;

            using window_t = void*;
            using contex_t = void*;
            using device_t = void*;

            enum facemode_t : index_t {
                FACEMODE_LINE,
                FACEMODE_FILL,
            };

        public:

            bool
                set_facemode(facemode_t facemode);

            bool
                set_viewport(int x, int y, int w, int h);

            bool
                set_clear_color(float r, float g, float b, float a);

        public:

            virtual bool
                init() override;
            bool
                work() override;
            bool
                quit() override;

            virtual bool
                proc(lib::event_a_t* event) override;

        private:

            window_t window;
            contex_t contex;
            device_t device;

            struct {

                facemode_t  facemode;

                v4s_t viewport;

                v4f_t clear_color;

            } state;

        };

    }

}

#endif /* GFX_ENGINE_HPP */