#ifndef SYS_CURSOR_HPP

#   define SYS_CURSOR_HPP

#   include "../cfg.hpp"

#   include "../lib/lib_event.hpp"

namespace gt {

    namespace sys {

        class cursor_t {
        
        public:

            enum kcode_t : unsigned int {
                /* simple mouse button codes */
                KCODE_1     = 0,
                KCODE_2     = 1,
                KCODE_3     = 2,
                KCODE_4     = 3,
                KCODE_5     = 4,
                KCODE_6     = 5,
                KCODE_7     = 6,
                KCODE_8     = 7,
                /* the last kcode == count */
                KCODE_LAST  = 7,
                KCODE_COUNT = KCODE_LAST,
            };

            enum state_t : int {
                /* momental */
                STATE_RAISE = 0b00,
                STATE_PRESS = 0b01,
                /* continous */
                STATE_FREE  = 0b10,
                STATE_HELD  = 0b11,
                /* the last state == count */
                STATE_LAST  = 0b100,
                STATE_COUNT = STATE_LAST,
            };

            using this_t    = cursor_t;
            
            typedef struct button_t {
                
                double  coord_held_x;
                double  coord_held_y;
                
                double  coord_free_x;
                double  coord_free_y;

                state_t state;

            };
            
            class event_click_t : public lib::event_t_t<event_click_t> {
                
            public:

                event_click_t(kcode_t kcode, state_t state) :
                    kcode(kcode), state(state)
                {
                }

            public:

                const kcode_t   kcode;
                const state_t   state;

            };
            class event_coord_t : public lib::event_t_t<event_coord_t> {
                
            public:

                event_coord_t(double coord_x, double coord_y) :
                    coord_x(coord_x), coord_y(coord_y)
                {
                }
            
            public:

                const double    coord_x;
                const double    coord_y;

            };
            class event_scrol_t : public lib::event_t_t<event_scrol_t> {
                
            public:

                event_scrol_t(double scrol_x, double scrol_y) :
                    scrol_x(scrol_x), scrol_y(scrol_y)
                {
                }
            
            public:

                const double    scrol_x;
                const double    scrol_y;

            };

        public:

            inline button_t
            get_button(kcode_t kcode) const
            {
                return this->button_array[kcode];
            }
            inline state_t
            get_button_state(kcode_t kcode) const
            {
                return this->button_array[kcode].state;
            }
        
        public:

            bool
            init();
            bool
            work();
            bool
            quit();

            bool
            proc(event_click_t* event);
            bool
            proc(event_coord_t* event);
            bool
            proc(event_scrol_t* event);

        private:

            button_t*   button_array;
            
            double      coord_x;
            double      coord_y;

            double      scrol_x;
            double      scrol_y;

        };

    }

}

#endif /* SYS_CURSOR_HPP */