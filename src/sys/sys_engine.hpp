#ifndef SYS_ENGINE_HPP

#   define SYS_ENGINE_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_event.hpp"

#   include "../lib/lib_engine.hpp"

#   include "sys_window.hpp"

namespace gt {

    namespace gui { class tool_sys_t; }
    
    namespace sys {

        class engine_t : public lib::engine_t_t<engine_t> {

        public:

            using this_t = engine_t;

            friend class gui::tool_sys_t;

        public:

            inline window_t*
            get_window()
            {
                return &this->window;
            }
            inline cursor_t*
            get_cursor()
            {
                return this->get_window()->get_cursor();
            }
            inline keybod_t*
            get_keybod()
            {
                return this->get_window()->get_keybod();
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

        private:

            window_t window;

        };

    }

}

#endif /* SYS_ENGINE_HPP */