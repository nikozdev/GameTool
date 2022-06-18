#ifndef GFX_HPP

#   define GFX_HPP

#   include "lib.hpp"

namespace gt {
    
    namespace gfx {
    
        class engine_t : public lib::engine_t<engine_t> {

        public:

            using this_t    = engine_t;
            using base_t    = lib::engine_t<this_t>;

            using window_t  = void*;
            using contex_t  = void*;
            using device_t  = void*;

        public:

            bool
            set_window(window_t& window);

        public:
        
            virtual bool
            init() override;
            bool
            work() override;
            bool
            quit() override;

            virtual bool
            proc(lib::event_t* event) override;

        private:

            window_t window;
            contex_t contex;
            device_t device;

        };

    }

}

#endif /* GFX_HPP */