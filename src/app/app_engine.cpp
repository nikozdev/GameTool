#ifndef APP_ENGINE_CPP

#   define APP_ENGINE_CPP

#   include "app_engine.hpp"
#   include "app_estate.hpp"

#   include "app_hotkey.hpp"

#   include "../sys/sys_engine.hpp"
#   include "../gfx/gfx_engine.hpp"
#   include "../gui/gui_engine.hpp"
#   include "../ecs/ecs_engine.hpp"

namespace gt {

    namespace app {

        bool
            engine_t::init()
        {
            this->timer.init();

            this->engine_array = {
                sys::engine_t::get(),
                gfx::engine_t::get(),
                gui::engine_t::get(),
                ecs::engine_t::get(),
            };

            for (index_t index = 0; index < this->engine_array.size(); index++) {
                
                auto engine = this->engine_array[index];
                
                GT_CHECK(engine->init(), "failed engine init!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

            }

            this->estate_array = {
                new estate_game_t()
            };

            for (index_t index = 0; index < this->estate_array.size(); index++) {

                auto estate = this->estate_array[index];

                GT_CHECK(estate->init(), "failed estate init!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

            }

            sys::engine_t::get()->get_window()->set_title("gametool");
            
            return this->play();
        }
        bool
        engine_t::work()
        {
            
            this->timer.work();

            auto keybod = sys::engine_t::get()->get_keybod();
            for (auto iter : hotkey_table) {

                if (keybod->vet_button_held(iter.mode) && keybod->vet_button_press(iter.code)) { iter.func(iter.args); }

            }

            for (index_t index = 0; index < this->estate_array.size(); index++) {

                auto estate = this->estate_array[index];

                GT_CHECK(estate->work(), "failed estate work!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

            }

            flag_t flag = this->get_flag();

            for (index_t index = 0; index < this->engine_array.size(); index++) {

                auto engine = this->engine_array[index];

                GT_CHECK(engine->work(), "failed engine work!", {
                    
                    GT_ELOGF("[index]=(%d)", index);
                    
                    return false;
                });
                
                flag &= engine->get_flag();
                if (flag == false) { break;  }

            }
            
            if (this->get_flag() ^ flag) { this->stop(); }

            return true;
        }
        bool
        engine_t::quit()
        {
            
            for (index_t count = this->estate_array.size(); count > 0; count--) {

                index_t index = count - 1;
                auto estate = this->estate_array[index];

                GT_CHECK(estate->quit(), "failed estate quit!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

                delete estate;
            }

            for (index_t count = this->engine_array.size(); count > 0; count--) {

                index_t index = count - 1;
                auto engine = this->engine_array[index];

                GT_CHECK(engine->quit(), "failed engine quit!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

            }

            this->timer.quit();

            return true;
        }

        bool
        engine_t::proc(lib::event_a_t* event)
        {

            for (index_t index = 0; index < this->engine_array.size(); index++) {

                auto engine = this->engine_array[index];

                GT_CHECK(engine->proc(event), "failed engine proc!", {

                    GT_ELOGF("[index]=(%d)", index);

                    return false;
                });

            }

            if (event->has_kind<sys::cursor_t::event_click_t>()) { return true; }
            if (event->has_kind<sys::cursor_t::event_coord_t>()) { return true; }
            if (event->has_kind<sys::cursor_t::event_scrol_t>()) { return true; }

            if (event->has_kind<sys::window_t::event_close_t>()) { return this->stop(); }
            if (event->has_kind<sys::window_t::event_sized_t>()) { return true; }
            if (event->has_kind<sys::window_t::event_moved_t>()) { return true; }
            
            if (event->has_kind<sys::keybod_t::event_t>()) { return true; }

            return true;
        }
    
    }

}

#endif /* APP_ENGINE_CPP */