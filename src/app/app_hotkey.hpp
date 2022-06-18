#ifndef APP_HOTKEY_HPP

#	define APP_HOTKEY_HPP

#   include "../cfg.hpp"

#   include "../sys/sys_keybod.hpp"

namespace gt {

    namespace app {

        struct hotkey_t {

        public:

            struct args_t { int number; const char* string; };

        public:

            using enum sys::keybod_t::kcode_t;

            using func_t = bool(*)(args_t);
            using code_t = sys::keybod_t::kcode_t;
            using mode_t = sys::keybod_t::kcode_t;

        public:

            mode_t mode;
            code_t code;
            func_t func;
            args_t args;

        };
    
        bool
            stop_work(hotkey_t::args_t args);

        namespace {

            using enum sys::keybod_t::kcode_t;

            hotkey_t hotkey_table[] = {

                {   KCODE_LEFT_CONTROL,     KCODE_X,    stop_work,      { 0, "" }       },
                {   KCODE_RIGHT_CONTROL,    KCODE_X,    stop_work,      { 0, "" }       },

            };

        }

    }

}

#endif /* APP_HOTKEY_HPP */