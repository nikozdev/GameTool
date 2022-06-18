#ifndef GFX_ENGINE_HPP

#   define GFX_ENGINE_HPP

#   include "../cfg.hpp"

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

                struct { int	x, y, w, h; } viewport;
                struct { float	r, g, b, a; } clear_color;

            } state;

        };

    }

}

#endif /* GFX_ENGINE_HPP */