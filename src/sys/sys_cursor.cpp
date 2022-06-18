#ifndef SYS_CURSOR_CPP

#   define SYS_CURSOR_CPP

#   include "sys_cursor.hpp"

namespace gt {

    namespace sys {
        
        bool
        cursor_t::init()
        {
            this->button_array = new button_t[KCODE_COUNT];
            ::memset(button_array, 0, sizeof(button_t)* KCODE_COUNT);

            return true;
        }
        bool
        cursor_t::work()
        {
            
            int index = 0;
            do {
                
            } while(++index < KCODE_COUNT);

            return true;
        }
        bool
        cursor_t::quit()
        {
            delete this->button_array;
            
            return true;
        }

        bool
        cursor_t::proc(event_coord_t* event)
        {
            return true;
        }
        bool
        cursor_t::proc(event_click_t* event)
        {
            return true;
        }
        bool
        cursor_t::proc(event_scrol_t* event)
        {
            return true;
        }

    }
    
}

#endif /* SYS_CPP */