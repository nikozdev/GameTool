#ifndef SYS_KEYBOD_CPP

#   define SYS_KEYBOD_CPP

#   include "sys_keybod.hpp"

namespace gt {

    namespace sys {

        bool
        keybod_t::init()
        {
            this->button_array = new button_t[KCODE_COUNT];
            ::memset(button_array, 0, sizeof(button_t) * KCODE_COUNT);

            return true;
        }
        bool
        keybod_t::work()
        {
            
            int index = 0;
            do {
                
                button_t* button = &this->button_array[index];
                button->times++;

            } while(++index < KCODE_COUNT);

            return true;
        }
        bool
        keybod_t::quit()
        {
            delete this->button_array;

            return true;
        }
        
        bool
        keybod_t::proc(event_t* event)
        {
            
            button_t* button = &button_array[event->kcode];
            if (button->state != event->state) {
                
                button->times = 0;
                button->state = event->state;
            
            }
            
            return true;
        }

    }

}

#endif /* SYS_KEYBOD_CPP */